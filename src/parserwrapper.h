#ifndef DISTRIBUTIONGENERATOR_H
#define DISTRIBUTIONGENERATOR_H

#include <ifloat.h>
#include <distribution.h>
#include <randomgenerator.h>
#include <vector>
#include <parser.h>
#include <fstream>

class ParserWrapper : public QObject
{
    Q_OBJECT

    Parser parser;
public:
    ParserWrapper(long long newBinNumber, double lowerBound, double upperBound);

    ParserWrapper(Parser newParser);

    Distribution parseDistribution(QString distStr);

public slots:
    void slotParseDistribution(QString distStr);

signals:
    void signalParseFinish(const Distribution &distribution);

    void signalAlert(QString alert);
};

#endif // DISTRIBUTIONGENERATOR_H
