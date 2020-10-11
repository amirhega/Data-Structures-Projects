#include <iostream>
#include <fstream>
#include "../bst-avl/avlbst.h"
#include <sstream>
#include <map>
#include <vector>

using namespace std;


typedef AVLTree<char, int> ANSWER_MAP_T;
void printSolution(ANSWER_MAP_T& answer, std::ostream& ostr);
vector<vector<char> > readFile(std::istream& myFile, string file, unsigned int& numCountry, unsigned int& rows, unsigned int& cols);
bool isValid(int num, unsigned int row, unsigned int col, vector<vector<char>>& countries, ANSWER_MAP_T& colors, map<char, vector<char>>& neighbors);
bool colorize(unsigned int row, unsigned int col, vector<vector<char>>& countries, ANSWER_MAP_T& colors, map<char, vector<char>>& neighbors);
bool notInVec(std::vector<char> v, char k);


int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Please supply a map input file and output filename" << endl;
        return 1;
    }
    // COMPLETE main()

    std::ifstream myFile(argv[1]);
    std::ofstream ofile(argv[2]);

    unsigned int numCountry, rows, cols;
    vector<vector<char> > countries = readFile(myFile, argv[1], numCountry, rows, cols);
    ANSWER_MAP_T colors;
    map<char, vector<char> > neighbors;
    
    //makes adjacency list for neighbors
    for(unsigned int i = 0; i < countries.size(); ++i) {
        
        for(unsigned int j = 0; j < countries[0].size(); ++j) {
            vector<char> temp;
            if(colors.find(countries[i][j]) == colors.end()) {
                neighbors.insert(make_pair(countries[i][j], temp));
            }

            //UP NEIHBHORS
            if(i > 0) {
                if(countries[i-1][j] != countries[i][j]) {
                    if(notInVec(neighbors.find(countries[i][j])->second, countries[i-1][j])) {
                        neighbors.find(countries[i][j])->second.push_back(countries[i-1][j]);
                    }
                }
            } 


            //DOWN NEIHBHORS
            if(i+1 < countries.size()) {
                if(countries[i+1][j] != countries[i][j]) {
                    if(notInVec(neighbors.find(countries[i][j])->second, countries[i+1][j])) {
                        neighbors.find(countries[i][j])->second.push_back(countries[i+1][j]);
                    }
                }
            } 

            //LEFT NEIHBHORS
            if(j > 0) {
                if(countries[i][j-1] != countries[i][j]) {
                    if(notInVec(neighbors.find(countries[i][j])->second, countries[i][j-1])) {
                        neighbors.find(countries[i][j])->second.push_back(countries[i][j-1]);
                    }
                }
            } 

            //LEFT NEIHBHORS
            if(j < countries[0].size()-1) {
                if(countries[i][j+1] != countries[i][j]) {
                    if(notInVec(neighbors.find(countries[i][j])->second, countries[i][j+1])) {
                        neighbors.find(countries[i][j])->second.push_back(countries[i][j+1]);
                    }
                }
            }
        }
    }

    // Call printSolution to output the answers to the output file
    if(colorize(0,0,countries, colors, neighbors))
        printSolution(colors, ofile);

    return 0;
}

bool notInVec(std::vector<char> v, char k) {

    for(unsigned int i = 0; i < v.size(); ++i) {
        if(k == v[i]) return false;
    }
    return true;
}


bool colorize(unsigned int row, unsigned int col, vector<vector<char> >& countries, ANSWER_MAP_T& colors, map<char, vector<char>>& neighbors) {

    //have gone through whole map
    if(row == countries.size()) return true;

    //go to next row if we reach end of col
    if(col == countries[0].size()) return colorize(row+1, 0, countries, colors, neighbors);

    //if the country is already colored
    if(colors.find(countries[row][col]) != colors.end()) return colorize(row, col+1, countries, colors, neighbors);

    else {
        for(int i = 1; i <= 4; ++i) {
            if(isValid(i, row, col, countries, colors, neighbors)) {
                colors.insert(make_pair(countries[row][col], i));
                bool status = colorize(row, col+1, countries, colors, neighbors);
                if(status) return true;
                colors.remove(countries[row][col]);
            }
        }

        return false;
    }

}


bool isValid(int num, unsigned int row, unsigned int col, vector<vector<char>>& countries, ANSWER_MAP_T& colors, map<char, vector<char>>& neighbors) {

    //checks if neighbors has the same number
    vector<char> temp = neighbors.find(countries[row][col])->second;
    for(unsigned int i = 0; i < temp.size(); ++i) {
        if(colors.find(temp[i]) != colors.end()) {
            if(colors.find(temp[i])->second  == num) return false;
        }
    }
    return true;
}


vector<vector<char> > readFile(std::istream& myFile, string file, unsigned int& numCountry, unsigned int& rows, unsigned int& cols) {

    

    myFile >> numCountry;
    myFile >> rows;
    myFile >> cols;

    vector<vector<char>> countries; 

    //reads map into vector
    for(unsigned int i = 0; i < rows; i++) {
        vector<char> temp;
        countries.push_back(temp);
        for(unsigned int j = 0; j < cols; j++) {
            char val;
            myFile >> val;
            countries[i].push_back(val);
        }
    }
    
    return countries;


}


void printSolution(ANSWER_MAP_T& answer, std::ostream& os)
{   
    //change back
    for(ANSWER_MAP_T::iterator it = answer.begin();
            it!= answer.end();
            ++it) {
        os << it->first << " " << it->second << endl;
    }
}

                                                               