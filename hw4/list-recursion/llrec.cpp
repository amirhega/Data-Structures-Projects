#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {

	Node* curr = head;
	if(curr != NULL) {

		if(curr->val > pivot) {
			head = head->next;
			llpush_back(larger, curr);
		} else {
			head = head->next;
			llpush_back(smaller, curr);
		}


		llpivot(head, smaller, larger, pivot);
	} 

	//CHECK IF SMALLER?LARGR HAVE TO BE NULL
}

void llpush_back(Node* &head, Node* &curr) {

	if(head == NULL) {
		head = curr;
		head->next = NULL;
	} else {
		curr->next = head;
		head = curr;
	}
}
