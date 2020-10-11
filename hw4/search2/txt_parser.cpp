#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "txt_parser.h"
#include "util.h"

using namespace std;


void TXTParser::parse(std::string filename, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if (!wfile) {
        throw std::invalid_argument("Bad webpage filename in TXTParser::parse()");
    }

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    // No links are present in a text parser
    allOutgoingLinks.clear();

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = wfile.get();

    // Continue reading from the file until input fails.
    while(!wfile.fail())
    {
        // Is c a character to split terms?
        if (!isalnum(c))
        {
            // If we have a term to add, convert it to a standard case and add it
            if(term != "")
            {
                term = conv_to_lower(term);
                allSearchableTerms.insert(term);
            }
            term = "";
        }
        // Otherwise we continually add to the end of the current term.
        else
        {
            term += c;
        }

        // Attempt to get another character from the file.
        c = wfile.get();
    }
    // Since the last term in the file may not have punctuation, there may be a valid term in
    // the "term" variable, so we need to insert it into the allSearchableTerms set.
    if(term != "")
    {
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }
    // Close the file.
    wfile.close();
}

std::string TXTParser::display_text(std::string filename)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if (!wfile) {
        throw std::invalid_argument("Bad webpage filename in TXTParser::parse()");
    }
    std::string retval;

    char c = wfile.get();

    // Continue reading from the file until input fails.
    while (!wfile.fail()) {
        retval += c;
        c = wfile.get();
    }
    return retval;
}


void TXTParser::crawl(const std::map<std::string, PageParser*>& parsers, std::string filename, std::set<std::string>& processed, std::ostream& ofile) {

    ifstream ifile(filename.c_str());
    if(!ifile.fail()) {
        

        //get what type of file it is
        string ext = extract_extension(filename);
        //if there is a matching extension and file has not been processed already
        if(parsers.find(ext) != parsers.end() && (processed.find(filename) == processed.end())) {
            ofile << filename << endl;
            processed.insert(filename);
            //no outgoing links since it is a txt
        }
    }
}

// void TXTParser::newParse(const std::map<std::string, PageParser*>& parsers,
//                   std::string filename, 
//                   std::set<std::string>& processed,
//                   std::ostream& ofile) {}