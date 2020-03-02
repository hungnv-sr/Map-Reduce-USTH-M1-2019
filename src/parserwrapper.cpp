#include "parserwrapper.h"

ParserWrapper::ParserWrapper(long long newBinNumber, double lowerBound, double upperBound)
    : parser(newBinNumber, lowerBound, upperBound)
{

}

ParserWrapper::ParserWrapper(Parser newParser) : parser(newParser)
{

}

Distribution ParserWrapper::parseDistribution(QString distStr) {
    return parser.string2dist(distStr);
}

void ParserWrapper::slotParseDistribution(QString dist) {
    Distribution distribution = parser.string2dist(dist);
    emit signalParseFinish(distribution);
}
