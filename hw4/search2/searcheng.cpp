#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "util.h"

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

// std::string extract_extension(const std::string& filename) 
// {
//     size_t idx = filename.rfind(".");
//     if (idx == std::string::npos) {
//         return std::string();
//     }
//     return filename.substr(idx + 1);
// }


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

        extensions_.insert(make_pair(extension, parser));
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
            } else {
                WebPageSet temp;
                searchSet = combiner->combine(searchSet, temp);
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



/**
 * Performs the PageRank algorithm on the webpages in the input set
 * [TO BE WRITTEN]
 *
 * @param[in] in_pages
 *   Unexpanded candidate set of webpages to run the PageRank algorithm on
 *
 * @return vector of pairs of webpage pointers and their PageRank score
 */
std::vector<std::pair<WebPage*, double> > SearchEng::pageRank(const WebPageSet& in_pages) {

    WebPageSet currOutgoing;
    WebPageSet currIncoming;
    WebPageSet expandedCandidate;
    WebPageSet inPages = in_pages;
    WebPage* pages;
    WebPage* it2;

    //for every page in given query set
    for(set<WebPage*>::iterator curr = inPages.begin(); curr != inPages.end(); curr++) {
        pages = *curr;
        //adds queried page to expanded set
        expandedCandidate.insert(pages);
        //adds self loop to outgoing and incoming
        pages->add_incoming_link(pages);
        pages->add_outgoing_link(pages);


        currOutgoing = pages->outgoing_links();
        //adds quried pages outgoing links to expanded set
        for(set<WebPage*>::iterator it = currOutgoing.begin(); it != currOutgoing.end(); it++) {
            //make sure not to add same node twice to candidate set
            //add self loop as well
            if(expandedCandidate.find(*it) == expandedCandidate.end()) {
                expandedCandidate.insert(*it);
                it2 = *it;
                it2->add_incoming_link(*it);
                it2->add_outgoing_link(*it);
            }
        }


        currIncoming = pages->incoming_links();
        //adds quried pages incoming links to expanded set
        for(set<WebPage*>::iterator it = currIncoming.begin(); it != currIncoming.end(); it++) {
            //make sure not to add same node twice to candidate set
            //add self loop as well
            if(expandedCandidate.find(*it) == expandedCandidate.end()) {
                expandedCandidate.insert(*it);
                it2 = *it;
                it2->add_incoming_link(*it);
                it2->add_outgoing_link(*it);
            }
        }

    }


    vector< pair<WebPage*, double> > finalProb;
    int n = expandedCandidate.size();
    double epsilon = 0.15;
    int t = 20;
    map<WebPage*, double> probs;
    map<WebPage*, double> newProb;


    double firstProb = 1.0 / (double)n;
    //sets prob of all to 1 /n
    for(set<WebPage*>::iterator page = expandedCandidate.begin(); page != expandedCandidate.end(); page++) {
        probs.insert(make_pair(*page, firstProb));
    }

    //on the t iteration
    for(int i = 1; i <= t; i++) {

        newProb.clear();

        //prob of every node
        for(map<WebPage*, double>::iterator nodes = probs.begin(); nodes != probs.end(); nodes++) {
            double p = 0;
            WebPage* node = nodes->first;

            //using formula: for every uncoming link of it
            for(set<WebPage*>::iterator it = node->incoming_links().begin(); it != node->incoming_links().end(); it++) {
                int dp = dPlus(*it, expandedCandidate);
                p += (probs.find(*it)->second * (1.0 / (double)dp));
            }

            //multiply sigma by .85
            p *= .85;
            p += (epsilon * firstProb);
            newProb.insert(make_pair(nodes->first, p));


        }
        //update prob every iteration
        probs = newProb;
    }


    for(set<WebPage*>::iterator page = expandedCandidate.begin(); page != expandedCandidate.end(); page++) {
        finalProb.push_back(make_pair(*page, probs.find(*page)->second) );
    }

    return finalProb;
}


int SearchEng::dPlus(WebPage* node, WebPageSet& expandedCandidate) {

    int count = 0;

    //counts number of outgoing links for given node
    for(set<WebPage*>::iterator it = node->outgoing_links().begin(); it != node->outgoing_links().end(); it++) {
        if(expandedCandidate.find(*it) != expandedCandidate.end()) {
            count++;
        }
    }

    return count;
}


int SearchEng::dMinus(WebPage* node, WebPageSet& expandedCandidate) {

    int count = 0;

    //counts number of incoming links for given node
    for(set<WebPage*>::iterator it = node->incoming_links().begin(); it != node->incoming_links().end(); it++) {
        if(expandedCandidate.find(*it) != expandedCandidate.end()) {
            count++;
        }
    }

    return count;
}





