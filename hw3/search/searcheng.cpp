#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

std::string extract_extension(const std::string& filename);


SearchEng::SearchEng(PageParser* noExtensionParser)
{
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    // Add additional code if necessary
    //defaultParser_;


}


void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

std::string extract_extension(const std::string& filename) 
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


//I wrote below
SearchEng::~SearchEng() {
    for(map<string, PageParser*>::iterator it = extensions_.begin(); it != extensions_.end(); ++it) {
        delete it->second;
    }

    for(map<string, WebPage*>::iterator it2 = webPages_.begin(); it2 != webPages_.end(); ++it2) {
        delete it2->second;
    }

    delete noExtensionParser_;
}



void SearchEng::register_parser(const std::string& extension, PageParser* parser) {

    //if(extensions_.find(extension) != extensions_.end()) {
        extensions_.insert(make_pair(extension, parser));
    //}
    /*//md
    if(extension == ".md") {
        parser = new MDParser;
        extensions_.insert(make_pair(extension, parser));
    } //txt
    else if(extension == ".txt") {
        parser = new TXTParser;
        extensions_.insert(make_pair(extension, parser));
    } //else no extension (for this assignment) chec
    else {
        //check if only for "" or for all others
        parser = new TXTParser;
        extensions_.insert(make_pair(extension, parser));
    } */
}


void SearchEng::read_page(const std::string& filename) {

    //get what type of file it is and register the parser
    string ext = extract_extension(filename);
    if(extensions_.find(ext) == extensions_.end()) {
        throw std::logic_error("No parser found");
    }
    //check if this needs to be done
   

    WebPage* page;
    //see if webpage has been created or not yet
    if(webPages_.find(filename) == webPages_.end()) {
        //add it to the set of WebPages we have
        //create new page
        page = new WebPage(filename);
        webPages_.insert(make_pair(filename, page));
    } else {
        page = webPages_.find(filename)->second;
    }
   
    //parse the webpage
    set<string> searchTerm;
    set<string> outgoingLinks;
    extensions_.find(ext)->second->parse(filename, searchTerm, outgoingLinks);
    page->all_terms(searchTerm);

    //goes through each term in this page
    for(set<string>::iterator termsIT = page->all_terms().begin(); termsIT != page->all_terms().end(); ++termsIT) {
        //checks if the current term is in the total terms map
        if(termsWebPages_.find(*termsIT) != termsWebPages_.end()) {
            termsWebPages_.find(*termsIT)->second.insert(page);
        } //else we add the term to the map
        else {
            //create new WebPageSet to associate with the term
            WebPageSet newWebSet;
            newWebSet.insert(page);
            termsWebPages_.insert(make_pair(*termsIT, newWebSet));
        }
    } //else we find duplaicate web page ??


    for(set<string>::iterator linksIT = outgoingLinks.begin(); linksIT != outgoingLinks.end(); ++linksIT) {
        //check if we should find duplicate links
        //add link to outgoing
        if(webPages_.find(*linksIT) != webPages_.end()) {
            page->add_outgoing_link(webPages_.find(*linksIT)->second);
        } //else create/allocate new web page
        else {
            //create new page with that name
            WebPage* newPage = new WebPage(*linksIT);
            webPages_.insert(make_pair(*linksIT, newPage));
            page->add_outgoing_link(newPage);
        }

        //check if linked page exists
        if(webPages_.find(*linksIT) != webPages_.end()) {
            webPages_.find(*linksIT)->second->add_incoming_link(page);
        } //else create/allocate new web page
        else {
            //create new page with that name
            WebPage* newPage = new WebPage(*linksIT);
            newPage->add_incoming_link(newPage);

            //add to all webpages

            //add to searchable map
            webPages_.insert(make_pair(*linksIT, newPage));
        }
    }
}





/**
     * Uses the given search terms and combiner to find the set of webpages
     *  that match the query
     * [TO BE WRITTEN]
     *
     * @param[in] terms
     *   words/terms to search for
     * @param[in] combiner
     *   Combiner object that implements the strategy for combining the
     *   pages that contain each term (i.e. AND, OR, DIFF, etc.)
     *
     * @return Set of webpages matching the query*/
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const {

   
    WebPageSet searchSet;
    if(terms.size() > 0) {
        if(termsWebPages_.find(terms[0]) != termsWebPages_.end()) {
            //can i set them equal?
            searchSet = termsWebPages_.find(terms[0])->second;
        }



        for(unsigned int i = 1; i < terms.size(); i++) {
            if(termsWebPages_.find(terms[i]) != termsWebPages_.end()) {
                searchSet = combiner->combine(searchSet, termsWebPages_.find(terms[i])->second);
            }
        }
    }
  

    return searchSet;

}


WebPage* SearchEng::retrieve_page(const std::string& page_name) const {

    if(webPages_.find(page_name) != webPages_.end()) {
        return webPages_.find(page_name)->second;
        
    }

    return NULL;
}


void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const {

    if(retrieve_page(page_name) != NULL) {
        ostr << extensions_.find(extract_extension(page_name))->second->display_text(page_name);
    } else {
        throw std::invalid_argument("No page found");
    } 
    //second throw
}





