#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key, Value>* x);
    void rotateRight(AVLNode<Key, Value>* x);
    void insertFix(AVLNode<Key, Value>* node, AVLNode<Key, Value>* parent);
    void removeFix(AVLNode<Key, Value>* node, char diff);



};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(this->empty()) {
        AVLNode<Key, Value>* root = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
        this->root_ =  root;
    } else {
        bool temp =  true;
        Key key = new_item.first;
        AVLNode<Key, Value> *curr = static_cast<AVLNode<Key,Value>*>(this->root_);
        while(temp) {
            //if bigger than the curr, go right
            if(key > curr->getKey()) {
                //create new node if NULL
                if(curr->getRight() == NULL) {

                    AVLNode<Key, Value>* node = new AVLNode<Key, Value>(key, new_item.second, curr);
                    curr->setRight(node);

                    //update balance
                    //means the parent now has two children
                    if(curr->getBalance() == -1 || curr->getBalance() == 1) {
                        curr->setBalance(0);
                    }

                    //parent has one child now which adds a level
                    else {
                        //we add it to the right, meaning parents right is bigger than left
                        curr->setBalance(1);
                        insertFix(node, curr);
                    }


                    temp  = false;
                } else {
                    curr = curr->getRight();
                }
            } //go left  if less than curr
            else if(key < curr->getKey()) {
                //if spot available
                if(curr->getLeft() == NULL) {

                    AVLNode<Key, Value>* node = new AVLNode<Key, Value>(key, new_item.second, curr);
                    curr->setLeft(node);

                    //update balance
                    //means the parent now has two children
                    if(curr->getBalance() == -1 || curr->getBalance() == 1) {
                        curr->setBalance(0);
                    }

                    //parent has one child now which adds a level
                    else {
                        //we add it to the left, meaning parents right is smaller than left
                        curr->setBalance(-1);
                        insertFix(node, curr);
                    }


                    temp  = false;
                } else {
                    curr = curr->getLeft();
                }
            }  //if equal 
            else {
                curr->setValue(new_item.second);
                temp = false;
            }
        }
    }

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key,Value>*>(this->root_);
    bool right = true;

    if(curr == NULL) {
        return;
    }

    //iterate until we find the tree
    while(curr->getKey() != key) {
        //node is not found
        if(curr->getLeft() == NULL && curr->getRight() == NULL) {
            return;
        } //key is to the right
        else if(key > curr->getKey()) {
            //it exists
            if(curr->getRight() != NULL) {
                curr = curr->getRight();
            } //key is not in tree  
            else {
                return;
            }
        } //key is to the left
        else if(key < curr->getKey()) {
            //it exists
            if(curr->getLeft() != NULL) {
                curr = curr->getLeft();
            } //key is not in tree  
            else {
                return;
            }
        }
    }




    //if node has two children
    if(curr->getLeft() != NULL && curr->getRight() != NULL) {
        AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->predecessor(curr));
        this->nodeSwap(curr, temp);
        //swap can have at most one child. for pred it would be a left child
        if(curr->getLeft() != NULL) {
            if(this->isRightChild(curr, curr->getParent())) {
                right = true;
                curr->getParent()->setRight(curr->getLeft());
                curr->getLeft()->setParent(curr->getParent());
            } else {
                right = false;
                curr->getParent()->setLeft(curr->getLeft());
                curr->getLeft()->setParent(curr->getParent());
            }
        } 
        //node that needs to be removed has no child
        else if(this->isLeftChild(curr, curr->getParent())) {
            right = false;
            curr->getParent()->setLeft(NULL);
        } else {
            right = true;
            curr->getParent()->setRight(NULL);
        }
        //curr->getParent()->set = NULL;
        

    } //NO CHILD
    else if(curr->getLeft() == NULL && curr->getRight() == NULL) {
        if(curr->getParent() != NULL) {
            if(this->isRightChild(curr, curr->getParent())) {
                right = true;
                curr->getParent()->setRight(NULL);
            } else {
                right = false;
                curr->getParent()->setLeft(NULL);
            }
        } else {
            delete curr;
            this->root_ = NULL;
            return;
        }
        

    } //one child
    else {
        //if one child is left node
        if(curr->getLeft() != NULL) {
            if(curr->getParent() == NULL) {
                this->root_ = curr->getLeft();
                curr->getLeft()->setParent(NULL);
                delete curr;
                return;
            }
            if(this->isRightChild(curr, curr->getParent())) {
                right = true;
                curr->getParent()->setRight(curr->getLeft());
                curr->getLeft()->setParent(curr->getParent());
            } else {
                right = false;
                curr->getParent()->setLeft(curr->getLeft());
                curr->getLeft()->setParent(curr->getParent());
            }
        } 
        //if one child is right child
        else {
            if(curr->getParent() == NULL) {
                this->root_ = curr->getRight();
                curr->getRight()->setParent(NULL);
                delete curr;
                return;
            }
            if(this->isRightChild(curr, curr->getParent())) {
                right = true;
                curr->getParent()->setRight(curr->getRight());
                curr->getRight()->setParent(curr->getParent());
            } else {
                right = false;
                curr->getParent()->setLeft(curr->getRight());
                curr->getRight()->setParent(curr->getParent());
            }
        }
    }

    int diff = 0;
    AVLNode<Key, Value>* currParent;
    if(curr != NULL) {
        currParent = curr->getParent();
        if(right) {
            diff = -1;
        } else {
            diff = 1;
        }
    }
    delete curr;
    curr = NULL;

    removeFix(currParent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

/*
*       x
*        \
*          y 
*           \
*            z
*/
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* x) {

    AVLNode<Key, Value>* temp = x->getRight();
    AVLNode<Key, Value>* yChild;
    if(x->getRight() != NULL) {
        yChild = x->getRight()->getLeft();
    } else {
        yChild = NULL;
    }

    //if node is root
    if(x == this->root_) {
        //this is just in case the right child does not exist
        if(x->getRight() != NULL) {
            this->root_ = temp;
            //set y parent to NULL
            if(temp != NULL) {
                temp->setParent(NULL);
            }
        } 

    }

    //if x is a left child
    else if(this->isLeftChild(x, x->getParent())) {
        if(temp != NULL) {
            temp->setParent(x->getParent());
        }
        x->getParent()->setLeft(temp);
    }

    //if x is a right child
    else {
        if(temp != NULL) {
            temp->setParent(x->getParent());
        }
        x->getParent()->setRight(temp);
    }



    //set X's parent to Y
    //Set Y's child to X
    x->setParent(temp);
    if(temp != NULL) {
        temp->setLeft(x);
    }

    //if Y's left child exists, set it's parent to be x
    //set X's right child to be Y's left child
    if(yChild != NULL) {
        yChild->setParent(x);
    }
    x->setRight(yChild);
    
}



template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* x) {

    AVLNode<Key, Value>* temp = x->getLeft();
    AVLNode<Key, Value>* yChild;
    if(x->getLeft() != NULL) {
        yChild = x->getLeft()->getRight();
    } else {
        yChild = NULL;
    }

    //if node is root
    if(x == this->root_) {
        //this is just in case the right child does not exist
        if(x->getLeft() != NULL) {
            this->root_ = temp;
            //set y parent to NULL
            if(temp != NULL) {
                temp->setParent(NULL);
            }
        } 

    }

    //if x is a left child
    else if(this->isLeftChild(x, x->getParent())) {

        if(temp != NULL) {
            temp->setParent(x->getParent());
        }
        x->getParent()->setLeft(temp);
    }

    //if x is a right child
    else {
        if(temp != NULL) {
            temp->setParent(x->getParent());
        }
        x->getParent()->setRight(temp);
    }



    //set X's parent to Y
    //Set Y's child to X
    x->setParent(temp);
    if(temp != NULL) {
        temp->setRight(x);
    }

    //if Y's right child exists, set it's parent to be x
    //set X's left child to be Y's right child
    if(yChild != NULL) {
        yChild->setParent(x);
    }
    x->setLeft(yChild);
    
}


template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* node, AVLNode<Key, Value>* parent) {

    if(parent == NULL) return;
    if(parent->getParent() == NULL) return;

    AVLNode<Key, Value>* grandParent = parent->getParent();
    
    if(this->isLeftChild(parent, parent->getParent())) {
        grandParent->setBalance(grandParent->getBalance() -1);

        //CASE 1
        if(grandParent->getBalance() == 0) {
            return;
        } 

        //CASE 2
        else if(grandParent->getBalance() == -1) {
            insertFix(parent, grandParent);
        }

        //CASE 3
        else if(grandParent->getBalance() == -2) {

            //zig zig
            if(this->isLeftChild(node, parent)) {
                rotateRight(grandParent);
                parent->setBalance(0);
                grandParent->setBalance(0);
            } 

            //zig zag
            else if(this->isRightChild(node, parent)) {
                rotateLeft(parent);
                rotateRight(grandParent);

                if(node->getBalance() == -1) {
                    parent->setBalance(0);
                    grandParent->setBalance(1);
                    node->setBalance(0);
                }

                else if(node->getBalance() == 0) {
                    parent->setBalance(0);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }

                else if(node->getBalance() == 1) {
                    parent->setBalance(-1);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }
            }

        }
    }



    //if parent is right child
    else {
         grandParent->setBalance(grandParent->getBalance() + 1);

        //CASE 1
        if(grandParent->getBalance() == 0) {
            return;
        } 

        //CASE 2
        else if(grandParent->getBalance() == 1) {
            insertFix(parent, grandParent);
        }

        //CASE 3
        else if(grandParent->getBalance() == 2) {

            //zig zig
            if(this->isRightChild(node, parent)) {
                rotateLeft(grandParent);
                parent->setBalance(0);
                grandParent->setBalance(0);
            } 

            //zig zag
            else if(this->isLeftChild(node, parent)) {
                rotateRight(parent);
                rotateLeft(grandParent);

                if(node->getBalance() == 1) {
                    parent->setBalance(0);
                    grandParent->setBalance(-1);
                    node->setBalance(0);
                }

                else if(node->getBalance() == 0) {
                    parent->setBalance(0);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }

                else if(node->getBalance() == -1) {
                    parent->setBalance(1);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }
            }

        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, char diff) {

    if(node == NULL) return;

    AVLNode<Key, Value>* parent = node->getParent();
    char nDiff = 0;

    if(parent != NULL) {
        if(this->isLeftChild(node, parent)) {
            nDiff = 1;
        } else {
            nDiff = -1;
        }

        //parent->setBalance(parent->getBalance() + nDiff);
    } 



    //IF DIFF = -1
    if(diff == -1) {

        AVLNode<Key, Value>* child = node->getLeft();

        //CASE 1
        if((node->getBalance() + diff) == -2) {

            if(child->getBalance() == -1) {
                rotateRight(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, nDiff);
            }

            else if(child->getBalance() == 0) {
                rotateRight(node);
                node->setBalance(-1);
                child->setBalance(1);
            }

            //zig zag
            else if(child->getBalance() == 1) {
                AVLNode<Key, Value>* temp = child->getRight();
                char tempB = temp->getBalance();

                rotateLeft(child);
                rotateRight(node);

                if(tempB == 1) {
                    node->setBalance(0);
                    child->setBalance(-1);
                    temp->setBalance(0);
                }

                if(tempB == 0) {
                    node->setBalance(0);
                    child->setBalance(0);
                    temp->setBalance(0);
                }

                if(tempB == -1) {
                    node->setBalance(1);
                    child->setBalance(0);
                    temp->setBalance(0);
                }

                removeFix(parent, nDiff);
            }
        }

        //CASE 2
        else if((node->getBalance() + diff) == -1) {
            node->setBalance(-1);
        }

        //CASE 3
        else if((node->getBalance() + diff) == 0) {
            node->setBalance(0);
            removeFix(parent, nDiff);
        }
    }

    
    //DIFF = 1
    else {

        AVLNode<Key, Value>* child = node->getRight();

        //CASE 1
        if((node->getBalance() + diff) == 2) {

            if(child->getBalance() == 1) {
                rotateLeft(node);
                node->setBalance(0);
                child->setBalance(0);
                removeFix(parent, nDiff);
            }

            else if(child->getBalance() == 0) {
                rotateLeft(node);
                node->setBalance(1);
                child->setBalance(-1);
            }

            //zig zag
            else if(child->getBalance() == -1) {
                AVLNode<Key, Value>* temp = child->getLeft();
                char tempB = temp->getBalance();

                rotateRight(child);
                rotateLeft(node);

                if(tempB == -1) {
                    node->setBalance(0);
                    child->setBalance(1);
                    temp->setBalance(0);
                }

                if(tempB == 0) {
                    node->setBalance(0);
                    child->setBalance(0);
                    temp->setBalance(0);
                }

                if(tempB == 1) {
                    node->setBalance(-1);
                    child->setBalance(0);
                    temp->setBalance(0);
                }

                removeFix(parent, nDiff);
            }
        }

        //CASE 2
        else if((node->getBalance() + diff) == 1) {
            node->setBalance(1);
        }

        //CASE 3
        else if((node->getBalance() + diff) == 0) {
            node->setBalance(0);
            removeFix(parent, nDiff);
        }

    }
}







#endif
