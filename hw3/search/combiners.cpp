#include "searcheng.h"
using namespace std;


// Place your function implementations for your derived
// WebPageSetCombiner classes here


WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    
    WebPageSet wSet;
    for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); it++) {
        if(setB.find(*it) != setB.end()) {
            wSet.insert(*it);
        }
    }
    andSet = wSet;
    return andSet;
}


WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
	WebPageSet orSet;

	for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); it++) {
        orSet.insert(*it);
    }

    for(set<WebPage*>::iterator it2 = setB.begin(); it2 != setB.end(); it2++) {
        if(orSet.find(*it2) == orSet.end()) {
        	orSet.insert(*it2);
        }
    }

    return orSet;

}


WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
	WebPageSet diffSet, bSet = setB;

	for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); it++) {
        diffSet.insert(*it);
    }

    for(set<WebPage*>::iterator it2 = bSet.begin(); it2 != bSet.end(); it2++) {
        if(diffSet.find(*it2) != diffSet.end()) {
        	diffSet.erase(*it2);
        }
    }

    return diffSet;

}



