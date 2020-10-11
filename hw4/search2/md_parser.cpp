#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;


void MDParser::parse(std::string filename, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if(!wfile) {
        throw invalid_argument("Bad webpage filename in MDParser::parse()");
    }

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = wfile.get();

    // Continue reading from the file until input fails.
    while(!wfile.fail())
    {
        // Logic for parsing a normal term.
        if(state == NORMALTEXT)
        {
            // ADD YOUR CODE HERE
            //if its not LINKTEXT
            if(c != '[') {
                //if its an alpha or num or else new term needs to be created
                if(isalnum(c)) {
                    term += c;
                } else {
                    if(term != "") {
                        allSearchableTerms.insert(conv_to_lower(term));
                        term = "";
                    }
                }
            } else {
                state = LINKTEXT;
            }


        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // ADD YOUR CODE HERE
            //if not end of anchor_text
            if(c != ']') {
                //if its an alpha or num or else new term needs to be created
                if(isalnum(c)) {
                    term += c;
                } else {
                    if(term != "") {
                        allSearchableTerms.insert(conv_to_lower(term));
                        term = "";
                    }
                }
            } else {
                state = ISLINK;
                allSearchableTerms.insert(conv_to_lower(term));
                term = "";
            }




        }
        else if( state == ISLINK )
        {
            // ADD YOUR CODE HERE
            if(c != '(') {
                state = NORMALTEXT;
                if(isalnum(c)) {
                    term += c;
                }
            } else {
                state = LINKURL;
                link = "";
            }




        }
        // Else we are in the LINKURL state.
        else
        {
            // ADD YOUR CODE HERE
            if(c != ')') {
                link += c;
            } else {
                allOutgoingLinks.insert(conv_to_lower(link));
                link = "";
                state = NORMALTEXT;
            }


        }
        // Attempt to get another character from the file.
        c = wfile.get();
    }
    // ADD ANY REMAINING CODE HERE
    //if there is something left in term
    if(term != "") {
        allSearchableTerms.insert(conv_to_lower(term));
    }


    // Close the file.
    wfile.close();
}




void MDParser::crawl(const std::map<std::string, PageParser*>& parsers, std::string filename, std::set<std::string>& processed, std::ostream& ofile) {
    
    //if page exists
    ifstream ifile(filename.c_str());
    if(!ifile.fail()) {

        //get what type of file it is
        string ext = extract_extension(filename);
        //if there is a matching extension and file has not been processed already
        if(parsers.find(ext) != parsers.end() && (processed.find(filename) == processed.end())) {
            ofile << filename << endl;
            processed.insert(filename);
            //parse only for links, will be recursive
            // Attempts to open the file.
            ifstream wfile(filename.c_str());
            if(wfile) {
            

                // The initial state is parsing a normal term.
                PARSE_STATE_T state = NORMALTEXT;

                // Initialize the current term and link as empty strings.
                string term = "";
                string link = "";

                // Get the first character from the file.
                char c = wfile.get();

                // Continue reading from the file until input fails.
                while(!wfile.fail())
                {
                    // Logic for parsing a normal term.
                    if(state == NORMALTEXT)
                    {
                        // ADD YOUR CODE HERE
                        //if its not LINKTEXT
                        if(c != '[') {
                            //if its an alpha or num or else new term needs to be created
                            if(isalnum(c)) {
                                term += c;
                            } else {
                                if(term != "") {
                                   // allSearchableTerms.insert(conv_to_lower(term));
                                    term = "";
                                }
                            }
                        } else {
                            state = LINKTEXT;
                        }


                    }
                    // Logic for parsing a link.
                    else if (state == LINKTEXT)
                    {
                        // ADD YOUR CODE HERE
                        //if not end of anchor_text
                        if(c != ']') {
                            //if its an alpha or num or else new term needs to be created
                            if(isalnum(c)) {
                                term += c;
                            } else {
                                if(term != "") {
                                   // allSearchableTerms.insert(conv_to_lower(term));
                                    term = "";
                                }
                            }
                        } else {
                            state = ISLINK;
                           // allSearchableTerms.insert(conv_to_lower(term));
                            term = "";
                        }

                    }
                    else if( state == ISLINK )
                    {
                        // ADD YOUR CODE HERE
                        if(c != '(') {
                            state = NORMALTEXT;
                            if(isalnum(c)) {
                                term += c;
                            }
                        } else {
                            state = LINKURL;
                            link = "";
                        }




                    }
                    // Else we are in the LINKURL state.
                    else
                    {
                        // ADD YOUR CODE HERE
                        if(c != ')') {
                            link += c;
                        } else {
                            //recursively crawl using DFS
                            crawl(parsers, link, processed, ofile);
                            link = "";
                            state = NORMALTEXT;
                        }


                    }
                    // Attempt to get another character from the file.
                    c = wfile.get();
                }
                // ADD ANY REMAINING CODE HERE




                // Close the file.
                wfile.close();
            }
            //parsers.find(ext)->second->newParse(parsers, filename, processed, ofile);
        }
    }
}


// void MDParser::newParse(const std::map<std::string, PageParser*>& parsers, std::string filename, std::set<std::string>& processed, std::ostream& ofile)
// {
//     // Attempts to open the file.
//     ifstream wfile(filename.c_str());
//     if(wfile) {
    

//         // The initial state is parsing a normal term.
//         PARSE_STATE_T state = NORMALTEXT;

//         // Initialize the current term and link as empty strings.
//         string term = "";
//         string link = "";

//         // Get the first character from the file.
//         char c = wfile.get();

//         // Continue reading from the file until input fails.
//         while(!wfile.fail())
//         {
//             // Logic for parsing a normal term.
//             if(state == NORMALTEXT)
//             {
//                 // ADD YOUR CODE HERE
//                 //if its not LINKTEXT
//                 if(c != '[') {
//                     //if its an alpha or num or else new term needs to be created
//                     if(isalnum(c)) {
//                         term += c;
//                     } else {
//                         if(term != "") {
//                            // allSearchableTerms.insert(conv_to_lower(term));
//                             term = "";
//                         }
//                     }
//                 } else {
//                     state = LINKTEXT;
//                 }


//             }
//             // Logic for parsing a link.
//             else if (state == LINKTEXT)
//             {
//                 // ADD YOUR CODE HERE
//                 //if not end of anchor_text
//                 if(c != ']') {
//                     //if its an alpha or num or else new term needs to be created
//                     if(isalnum(c)) {
//                         term += c;
//                     } else {
//                         if(term != "") {
//                            // allSearchableTerms.insert(conv_to_lower(term));
//                             term = "";
//                         }
//                     }
//                 } else {
//                     state = ISLINK;
//                    // allSearchableTerms.insert(conv_to_lower(term));
//                     term = "";
//                 }

//             }
//             else if( state == ISLINK )
//             {
//                 // ADD YOUR CODE HERE
//                 if(c != '(') {
//                     state = NORMALTEXT;
//                     if(isalnum(c)) {
//                         term += c;
//                     }
//                 } else {
//                     state = LINKURL;
//                     link = "";
//                 }




//             }
//             // Else we are in the LINKURL state.
//             else
//             {
//                 // ADD YOUR CODE HERE
//                 if(c != ')') {
//                     link += c;
//                 } else {
//                     //recursively crawl using DFS
//                     crawl(parsers, link, processed, ofile);
//                     link = "";
//                     state = NORMALTEXT;
//                 }


//             }
//             // Attempt to get another character from the file.
//             c = wfile.get();
//         }
//         // ADD ANY REMAINING CODE HERE




//         // Close the file.
//         wfile.close();
//     }
// }







std::string MDParser::display_text(std::string filename)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if (!wfile) {
        throw std::invalid_argument("Bad webpage filename in TXTParser::parse()");
    }
    std::string retval;

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    char c = wfile.get();

    // Continue reading from the file until input fails.
    while (!wfile.fail()) {
        // Logic for parsing a normal term.
        if (state == NORMALTEXT)
        {
            // The moment we hit a bracket, we input our current working term
            // into the allSearchableTerms set, reset the current term, and move into
            // parsing a link.
            if (c == '[')
            {
                state = LINKTEXT;
            }
            retval += c;
        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // When we hit the closing bracket, then we must be finished getting the link.
            if (c == ']')
            {
                state = ISLINK;
            }
            retval += c;
        }
        else if (state == ISLINK) {
            if (c == '(') {
                state = LINKURL;
            }
            else
            {
                state = NORMALTEXT;
                retval += c;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            // When we hit a closing parenthese then we are done, and the link can be inserted.
            if (c == ')')
            {
                state = NORMALTEXT;
            }
        }
        c = wfile.get();
    }
    return retval;
}


