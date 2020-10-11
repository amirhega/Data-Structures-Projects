#include "expr-reader.h"
#include "expr-ops.h"
#include <sstream>
#include <iostream>

using namespace std;
/*-----------------------------------------------------------------------------
 *  Implement the following functions below.
 *  Processing of each (sub)expression must be recursive (i.e. loops
 *    may only be used to iterate through the child vector of the given node).
 *  You may define recursive helper functions to adapt the function signatures.
 *    However, only exprPrinter likely needs a helper function.
 ----------------------------------------------------------------------------*/

void exprPrinter(std::ostream& ostr, Node* n)
{
	//use IN ORDER TRAVESAL

	//no ouput if root is null
	if(n == NULL) {
		return;
	}

	if(!n->children.empty()) {

		//every internal node will have a ( )
		ostr << "( ";

		for(unsigned int i = 0; i < n->children.size(); i++) {
			//process child
			exprPrinter(ostr, n->children[i]);

			//print parent only its not gone to the final child
			if(i < n->children.size() - 1) {
				ostr << n->val << " ";
			}
		}
		ostr << ") ";
	} //its a leaf/number
	else {
		ostr << n->val << " ";
	}

}


int exprSolver(Node* n)
{
    /* Should never be called on NULL expression -- Do Not Modify */
    if(n == NULL ) {
        throw std::logic_error("Can't solve a NULL expression");
    }

    //use PRE-ORDER TRAVERSAL
    if(!n->children.empty()) {
    	int temp = exprSolver(n->children[0]);

    	//for each child node
		for(unsigned int i = 1; i < n->children.size(); i++) {
			//process child
			if(n->val == "+") {
				temp += exprSolver(n->children[i]);
			} else if(n->val == "-") {
				temp -= exprSolver(n->children[i]);
			} else if(n->val == "*") {
				temp *= exprSolver(n->children[i]);
			} else if(n->val == "/") {
				temp /= exprSolver(n->children[i]);
			}

		}
		return temp;
	} //its a leaf/number

	stringstream ss(n->val);
	int value;
	ss >> value;
	return value;
}

bool exprIsValid(Node* n)
{
	//use POST ORDER TRAVERSAL

	//base case if n is null
	if(n == NULL) {
		throw std::logic_error("Node is Null");
	}

	//base case: has no children
	if(n->children.empty()) {
		for(unsigned int k = 0; k < n->val.size(); k++) {
			if(!isdigit(n->val[k])) {
				return false;
			}
		}
	}

	//recursive case: go down tree all the way to left
	if(!n->children.empty()) {
		//for every child
		for(unsigned int i = 0; i < n->children.size(); i++) {
			bool valid = exprIsValid(n->children[i]);
			if(!valid) {
				return false;
			}
		}
	}

	return true;

}
