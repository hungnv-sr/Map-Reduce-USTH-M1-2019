#ifndef PARSER_H
#define PARSER_H

#include <distribution.h>
#include <NormalDistribution.h>
#include <uniformdistribution.h>
#include <exponentialdistribution.h>
#include <stack>
#include <map>
using std::stack;

struct ParserException : public std::exception {
private:
    QString msg;

public:
    ParserException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};


class Parser
{

    int binNumber;
    double lowerBound, upperBound;

    bool isNumber(QChar c) {
        return c>='0' && c<='9';
    }

    bool isParen(QChar c) {
        return c=='(' || c==')';
    }

    bool isDist(QChar c) {
        if (c=='U' || c=='E' || c=='N' || c=='G') return true;
    }

    bool isOperator(QChar c) {
        return c=='+' || c=='-' || c=='*' || c=='/';
    }

    bool isVocab(QChar c) {
        if (isNumber(c)) return true;
        if (isParen(c)) return true;
        if (isDist(c)) return true;
        if (isOperator(c)) return true;
        if (c==',' || c=='.') return true;        
        return false;
    }

    QString normalize(QString s) {
        s = s.toUpper();
        return s.remove(' ');
    }

    bool balancedBracket(QString s) {
        unsigned cnt = 0;
        for (int i=0; i<s.length(); i++) {
            if (s[i]=='(') cnt += 1;
            else if (s[i]==')') cnt -= 1;
            if (cnt < 0) return false;
        }
        if (cnt > 0) return false;
        return true;
    }

    bool validString(QString s) {
        for (int i=0; i<s.length();i++) if (!isVocab(s[i])) return false;
        if (!balancedBracket(s)) return false;
        return true;
    }

    //---------------
    int precedence(QChar op) {
        if (op=='+' || op=='-') return 1;
        if (op=='*' || op=='/') return 2;
        return 0;
    }

    Distribution applyOp(QChar op, const Distribution& a, const Distribution & b) {
        if (op=='+') return a + b;
        if (op=='-') return a - b;
        if (op=='*') return a * b;
        if (op=='/') return a / b;
        throw ParserException(QString("ApplyOp: unknown operator '%c'").arg(op));
    }

    //-------------------------------------------------
    Distribution createDistribution(QChar distType, std::vector<double> params) {
        Distribution nonsense(0,0,0);
        if (distType=='U') {
            if (!UniformDistribution::validParams(binNumber, lowerBound, upperBound, params)) return nonsense;
            return UniformDistribution(binNumber, lowerBound, upperBound, params[0], params[1]);
        }

        if (distType=='N') {
            if (!NormalDistribution::validParams(binNumber, lowerBound, upperBound, params)) return nonsense;
            return NormalDistribution(binNumber, lowerBound, upperBound, params[0], params[1]);
        }

        if (distType=='E') {
            if (!ExponentialDistribution::validParams(binNumber, lowerBound, upperBound, params)) return nonsense;
            return ExponentialDistribution(binNumber, lowerBound, upperBound, params[0]);
        }

        return nonsense;
    }

    //---------------------------------------
    // parseExpression(str): parse expression using shunting yard

    Distribution parseDist(const QString& s, int pos, int& returnPos) {
        std::vector<double> params;
        int i, j, n;
        Distribution nonsense(0,0,0);

        n = s.length();
        if (s[pos+1]!='(') return nonsense;
        if (pos+2 >= n) return nonsense;

        i = pos+2;
        while (i < n) {
            j = i;
            while (j<n && (s[j]!=',' && s[j]!=')')) j++;
            if (j==n) return nonsense; // can't find , or )
            if (j==i) return nonsense; // invalid input cases such as: ,, ; ,) ; () ; (,

            QString number = s.mid(i, j-i); // get substring from i->j-1
            params.push_back(number.toDouble());
            i = j+1;
            if (s[j]==')') break;
        }

        returnPos = i-1;
        return createDistribution(s[pos], params);
    }

    // get 2 operands from stack and apply operator

    bool stackApplyOp(QChar op, stack<Distribution>& valueStack) {
        if (valueStack.size() < 2) return false; // fail
        Distribution valueRight = valueStack.top();
        valueStack.pop();
        Distribution valueLeft = valueStack.top();
        valueStack.pop();

        valueStack.push(applyOp(op, valueLeft, valueRight));
        return true; // success
    }

    Distribution parseExpression(QString s) {
        int i, n;
        Distribution nonsense(0,0,0);
        Distribution result(binNumber, lowerBound, upperBound);
        stack<Distribution> valueStack;
        stack<QChar> operatorStack;


        if (s.length()==0) return nonsense;
        s = normalize(s);
        if (!validString(s)) return nonsense;

        n = s.length();
        i = 0;
        while (i<n) {
            if (isNumber(s[i])) {
                return nonsense; // stand-alone number is wrong.
            }

            // is an operand
            if (isDist(s[i])) {
                Distribution dist = parseDist(s, i, i);
                if (!dist.valid()) {
                    return nonsense;
                }
                valueStack.push(dist);
            }
            else
            if (s[i]=='(') operatorStack.push(s[i]);
            else
            if (s[i]==')') {
                while (operatorStack.top()!='(') {
                    QChar op = operatorStack.top();
                    operatorStack.pop();

                    if (!stackApplyOp(op, valueStack)) {
                        return nonsense;
                    }
                }

                if (operatorStack.top()!='(') {
                    return nonsense;
                }
                operatorStack.pop(); // pop the '(' out
            }
            else
            if (isOperator(s[i])) {
                QChar thisOp = s[i];
                while (!operatorStack.empty() && precedence(operatorStack.top()) >= thisOp) {
                    QChar op = operatorStack.top();
                    operatorStack.pop();

                    if (!stackApplyOp(op, valueStack)) {
                        return nonsense;
                    }
                }
                operatorStack.push(thisOp);
            }

            i++;
        }

        while (!operatorStack.empty()) {
            QChar op = operatorStack.top();
            operatorStack.pop();

            if (!stackApplyOp(op, valueStack)) return nonsense;
        }

        if (operatorStack.size() > 0) return nonsense;
        if (valueStack.size() != 1) return nonsense;
        valueStack.top().normalize();
        return valueStack.top();
    }


public:
    Parser() {
        binNumber = 0;
        lowerBound = 0;
        upperBound = 0;
    }

    Parser(long long newBinNumber, double newLowerBound, double newUpperBound) {
        if (newBinNumber <= 1)
            throw ParserException("Constructor: newBinNumber <= 1");

        if (newLowerBound >= newUpperBound)
            throw ParserException("Constructor: newLowerBound >= newUpperBound");

        binNumber = newBinNumber;
        lowerBound = newLowerBound;
        upperBound = newUpperBound;              
    }

    bool valid() {
        return binNumber > 1 && lowerBound < upperBound;
    }

    Distribution string2dist(QString s) {
        if (!valid())
            throw ParserException("String2Dist: parser is not initialized");
        return parseExpression(s);
    }

    static bool validParams(long long binNumber, double lowerBound, double upperBound) {
        return binNumber > 1 && lowerBound < upperBound;
    }


    //--------------------------------------------------
    static void parserTest() {
        Parser parser(10,0,10);
        QString str = "U(3,7) + N(1,2) + E(3)";
        Distribution dist = parser.parseExpression(str);
        qDebug() << dist.valid() << "\n";

        str = "U(5,4)";
        qDebug() << parser.parseExpression(str).valid() << "\n";

        str = "U(5,4) * N(1,2)";
        qDebug() << parser.parseExpression(str).valid() << "\n";
    }
};

#endif // PARSER_H
