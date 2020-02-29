#include "csvfile.h"

using std::vector;

void outputFile(string filename, vector<Result> arr) {
    int n = arr.size();
    vector<string> algoNames;
    vector<MatAlgo> algoTypes;
    std::map<MatAlgo, bool> mp;

    mp.clear();
    algoTypes.clear();
    algoNames.clear();

    for (int i=0; i<n;i++) {
        if (!mp[arr[i].algoUsed]) {
            mp[arr[i].algoUsed] = 1;
            algoTypes.push_back(arr[i].algoUsed);
            if (arr[i].algoUsed==LINEAR) algoNames.push_back("LINEAR");
            else if (arr[i].algoUsed==SPLIT_MERGE) algoNames.push_back("SPLIT_MERGE");
        }
    }
    try
    {
        csvfile fo(filename.c_str());

        fo << algoTypes.size() << endrow;
        for (int t=0; t<algoTypes.size(); t++) fo << algoNames[t];
        fo << endrow;

        for (unsigned t=0; t<algoTypes.size(); t++) {
            double mean = 0;
            int nSample = 0;

            for (int i=0;i<n;i++) if (arr[i].algoUsed==algoTypes[i]) {
                mean = mean + double(arr[i].value);
                nSample++;
            }
            mean = mean/nSample;

            double variance = 0;
            for (int i=0;i<n;i++) if (arr[i].algoUsed==algoTypes[i]) {
                variance = variance + double((arr[i].value - mean)*(arr[i].value - mean));
            }
            variance = variance / nSample;

            fo << mean  << variance << sqrt(variance) << endrow;
            for (int i=0; i<n; i++) if (arr[i].algoUsed==algoTypes[i]) fo << double(arr[i].value);
            fo << endrow;
        }
        fo.close();
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception was thrown: " << ex.what() << std::endl;
    }
}
