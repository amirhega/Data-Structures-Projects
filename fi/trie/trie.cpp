//
// Students: write your trie implementation below.
//

#include "trie.h"

//----------------------------------------------
// DO NOT MODIFY THE CONSTRUCTOR OR DESTRUCTOR.
//----------------------------------------------

SparseTrie::SparseTrie()
{
    // DO NOT MODIFY.
    // The root node is always present and represents an
    // empty string. It should never be removed until
    // the destructor runs.
    root = new TNode('\0', false);
}

SparseTrie::~SparseTrie()
{
    // LEAVE BLANK. Don't worry about deallocation.
}

void SparseTrie::insert(std::string key) {

	TNode* curr = root;

	if(key.size() == 0) {
		root->terminal =true;
		return;

	}

	char cKey[key.size() + 1];
	for(unsigned int i = 0; i < key.size(); i++) {
		cKey[i] = key[i];
	}

	cKey[key.size()] = -1;
	int i = 0;

	if(root->children == NULL) {
		root->children = new TNode(cKey[i], false);
		i++;
		curr = root->children;
	}


	while(cKey[i] != -1) {

		if(curr->children == NULL) {
			curr->children = new TNode(cKey[i], false);
			i++;
			curr = curr->children;
		}

		else if(curr->children != NULL) {
			curr = curr->children;
			TNode* temp = getNext(curr, cKey[i]);
			if(temp != NULL) {
				curr = temp;
				i++;
			} else {
				while(curr->next != NULL) {
					curr = curr->next;
				}
				curr->next = new TNode(cKey[i], false);
				curr = curr->next;
				i++;
			}
		}

	}

	curr->terminal = true;
}

TNode* SparseTrie::getNext(TNode* curr, char val) {

	while(curr != NULL) {
		
		if(curr->letter == val) {
			break;
		} else {
			curr = curr->next;
		}
		
	}
	return curr;
}

bool SparseTrie::contains(std::string key) {

	TNode* curr = root;

	if(key == "") return root->terminal;

	char cKey[key.size() + 1];
	for(unsigned int i = 0; i < key.size(); i++) {
		cKey[i] = key[i];
	}

	cKey[key.size()] = -1;
	int i = 0;

	while(cKey[i] != -1) {

		if(curr->children == NULL) {
			return false;
		}

		else if(curr->children != NULL) {
			curr = curr->children;
			TNode* temp = getNext(curr, cKey[i]);
			if(temp != NULL) {
				curr = temp;
				i++;
			} else {
				return false;
			}
		}
	}

	return curr->terminal;

}





// struct TNode {
//     char letter;   // next letter in the key
//                    //  Indicates which child this node corresponds to
//                    //  from its parent
//     bool terminal; // true if this node is a terminal node
//     TNode* children, *next; // head pointer to children and sibling linked lists

//     // Constructor for convenience
//     TNode(char myletter, bool isTerminalNode=false, TNode* mynext=nullptr) :
//         letter(myletter), terminal(isTerminalNode), children(nullptr), next(mynext)
//     { }

// };

