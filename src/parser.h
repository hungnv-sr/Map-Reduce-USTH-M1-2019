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
        return c>='0' && c<='48';
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
            if (params.size()!=2) return nonsense;
            return UniformDistribution(binNumber, lowerBound, upperBound, params[0], params[1]);
        }

        if (distType=='N') {
            if (params.size()!=2) return nonsense;
            return NormalDistribution(binNumber, lowerBound, upperBound, params[0], params[1]);
        }

        if (distType=='E') {
            if (params.size()!=1) return nonsense;
            return ExponentialDistribution(binNumber, lowerBound, upperBound, params[0]);
        }

        return nonsense;
    }

    Distribution parseDist(const QString& s, int pos, int& returnPos) {
        std::vector<double> params;
        int i, j, n;
        Distribution nonsense(0,0,0);

        if (s[pos+1]!='(') return nonsense;

        n = s.length();
        i = pos+2;
        while (i < n) {
            j = i;
            while (j<n && (s[j]!=',' && s[j]!=')')) j++;
            if (j==n) return nonsense; // can't find , or )
            if (j==i+1) return nonsense; // invalid input cases such as: ,, ; ,) ; () ; (,

            QString number = s.mid(i, j-i); // get substring from i->j-1
            params.push_back(number.toDouble());
            i = j+1;
            if (s[j]==')') break;
        }

        returnPos = i-1;
        return createDistribution(s[pos], params);
    }

    //---------------------------------------
    // parse expression using shunting yard

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

        s = normalize(s);
        if (!validString(s)) return nonsense;

        n = s.length();
        while (i<n) {
            if (isNumber(s[i])) return nonsense; // stand-alone number is wrong.

            // is an operand
            if (isDist(s[i])) {
                Distribution dist = parseDist(s, i, i);
                if (!dist.valid()) return nonsense;
                valueStack.push(dist);
            }

            if (s[i]=='(') operatorStack.push(s[i]);

            if (s[i]==')') {
                if (operatorStack.empty()) return nonsense;

                while (operatorStack.top()!='(') {
                    QChar op = operatorStack.top();
                    operatorStack.pop();

                    if (!stackApplyOp(op, valueStack)) return nonsense;
                }
                operatorStack.pop(); // pop the '(' out
            }

            if (isOperator(s[i])) {
                QChar thisOp;
                while (!operatorStack.empty() && precedence(operatorStack.top()) >= thisOp) {
                    QChar op = operatorStack.top();
                    operatorStack.pop();

                    if (!stackApplyOp(op, valueStack)) return nonsense;
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
        if (valueStack.size() > 1) return nonsense;
        return valueStack.top();
    }


public:
    Parser(long long newBinNumber, double newLowerBound, double newUpperBound) {
        binNumber = newBinNumber;
        lowerBound = newLowerBound;
        upperBound = newUpperBound;
    }

    Distribution string2dist(QString s) {
        return parseExpression(s);
    }

};

#endif // PARSER_H
