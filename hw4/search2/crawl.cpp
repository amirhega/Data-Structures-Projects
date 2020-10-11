#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "md_parser.h"
#include "txt_parser.h"
#include "util.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Must provide an index file and output file" << endl;
        return 1;
    }

    // ---------------------- [TO BE COMPLETED] -------------------------------

    map<string, PageParser*> parsers;
    set<string> processed;
    PageParser* txt = new TXTParser();
    parsers.insert(make_pair("txt", txt));

    PageParser* md = new MDParser();
    parsers.insert(make_pair("md", md));

    ifstream ifile(argv[1]);
    ofstream out_file(argv[2]);
 
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << argv[2] << endl;
    }

    // Parse all the files using crawl function
    string filename;
    while(ifile >> filename) {
    	string ext = extract_extension(filename);
        //if extension has been registered
    	if(parsers.find(ext) != parsers.end()) {
    		parsers.find(ext)->second->crawl(parsers, filename, processed, out_file);
    	}
    }


    delete txt;
    delete md;

    



    
    // You may add cleanup code here if necessary

    return 0;
}
