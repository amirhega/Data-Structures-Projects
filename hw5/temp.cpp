#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
int main(int argc, char* argv[])
{
     std::vector<std::vector<bool> > aMatrix;
   
    for(int i = 0; i < 5; i++) {
        for(int  j = 0; j < 5; j++) {
            aMatrix[j].push_back(false);
        }
    }


    return 0;
}

