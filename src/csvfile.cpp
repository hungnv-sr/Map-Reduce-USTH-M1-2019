#include "csvfile.h"
using std::vector;
int main()
{
    vector<int> vect;  
     
    vect.push_back(1); 
    vect.push_back(2); 
    vect.push_back(3);
    try{
        csvfile csv("test.csv");
        // should have some header
        int line = 1; // in case we need 1 more line for header, csv<< line++
        for(int i = 0; i < vect.size(); ++i){
            csv << line << vect[i];
        }
        csv << endrow;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    return ;
}