#include "searcheng.h"
#include "combiners.h"
using namespace std;


// Place your function implementations for your derived
// WebPageSetCombiner classes here

//all same as homework 3
WebPageSet ANDWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    
    WebPageSet andSet;
    //for every term in setA
    for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); it++) {
        //if terms is in both sets
        if(setB.find(*it) != setB.end()) {
            andSet.insert(*it);
        }
    }
    return andSet;
}


WebPageSet ORWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
	WebPageSet orSet;

    //add all of a to orset
	for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); it++) {
        orSet.insert(*it);
    }

    for(set<WebPage*>::iterator it2 = setB.begin(); it2 != setB.end(); it2++) {
        //if not already in or set
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



