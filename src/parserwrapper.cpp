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
    try {
        Distribution distribution = parser.string2dist(dist);
        emit signalParseFinish(distribution);
    }
    catch (SamplingException samplingException) {
        emit signalAlert("Distribution requires too high accuracy. Please try another.");
        emit signalParseFinish(Distribution(0,0,0));
    }
    catch (std::underflow_error) {
        emit signalAlert("Distribution requires too high accuracy. Please try another number.");
        emit signalParseFinish(Distribution(0,0,0));
    }
    catch (std::overflow_error) {
        emit signalAlert("Distribution requires too high accuracy. Please try another.");
        emit signalParseFinish(Distribution(0,0,0));
    }
}
