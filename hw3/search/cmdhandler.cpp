#include "cmdhandler.h"
#include "util.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler()
{

}

PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}


///my work

AndHandler::AndHandler() 
{

}

AndHandler::AndHandler(Handler* next)
    : Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";

}

Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
   // cout << "IN AND";
    vector<string> andSet;
    string terms, term;
    getline(instr, terms);
    stringstream ss(terms);

    ss >> term;
    while(term != "") {
        andSet.push_back(conv_to_lower(term));
        term = "";
        ss >> term;
    }
    WebPageSet wps = eng->search(andSet, &combiner_);
    display_hits(wps, ostr);
    return HANDLER_OK;
    
}


OrHandler::OrHandler() 
{

}

OrHandler::OrHandler(Handler* next)
    : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";

}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> orSet;
    string terms, term;
    getline(instr, terms);
    stringstream ss2(terms);

    ss2 >> term;
    while(term != "") {
        orSet.push_back(conv_to_lower(term));
        term = "";
        ss2 >> term;
    }
    display_hits(eng->search(orSet, &combiner_), ostr);
    return HANDLER_OK;
    
}


DiffHandler::DiffHandler() 
{

}

DiffHandler::DiffHandler(Handler* next)
    : Handler(next)
{

}

bool DiffHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";

}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> diffSet;
    string terms, term;
    getline(instr, terms);
    stringstream ss2(terms);

    ss2 >> term;
    while(term != "") {
        diffSet.push_back(conv_to_lower(term));
        term = "";
        ss2 >> term;
    }
    display_hits(eng->search(diffSet, &combiner_), ostr);
    return HANDLER_OK;
    
}


IncomingHandler::IncomingHandler() 
{

}

IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}

bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";

}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string term;
    getline(instr, term);
    stringstream ss2(term);

    ss2 >> term;
    if(eng->retrieve_page(term) != NULL) {
        ostr << eng->retrieve_page(term)->incoming_links().size() << std::endl;
        for (set<WebPage*>::iterator it = eng->retrieve_page(term)->incoming_links().begin(); it != eng->retrieve_page(term)->incoming_links().end(); ++it) {
            ostr << (*it)->filename() << std::endl;
        }
        return HANDLER_OK;
    } else {
        return HANDLER_ERROR;
    }
    
}


OutgoingHandler::OutgoingHandler() 
{

}

OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}

bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";

}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
   
    string term;
    getline(instr, term);
    stringstream ss2(term);

    ss2 >> term;
    if(eng->retrieve_page(term) != NULL) {
        ostr << eng->retrieve_page(term)->outgoing_links().size() << std::endl;
        for (set<WebPage*>::iterator it = eng->retrieve_page(term)->outgoing_links().begin(); it != eng->retrieve_page(term)->outgoing_links().end(); ++it) {
            ostr << (*it)->filename() << std::endl;
        }
        return HANDLER_OK;
    } else {
        return HANDLER_ERROR;
    }
    
}





