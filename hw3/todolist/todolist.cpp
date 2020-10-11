#include <stdexcept>
#include "todolist.h"


DailyTodoList::DailyTodoList()
{
    data_ = new Item * [5];
    cap_ = 5;
    priorityHead_ = NULL;
    for(size_t i = 0; i < 5; i++) {
        data_[i] = NULL;
    }
    // [TO BE COMPLETED]
    //===========================
    // Add any addition code here
    tail = NULL;
    numP = 0;

    
}

DailyTodoList::~DailyTodoList() {

    //remove each to do liist first
    for(size_t i = 0; i < cap_; i++) {
        while(data_[i] != NULL) {
            remove(i, 0);
        }
    }
    delete [] data_;

}



void DailyTodoList::push_back(size_t dayIndex, const std::string& val, bool highPriority)
{
    if (dayIndex < cap_)
    {
        this->insert(dayIndex, this->numItemsOnDay(dayIndex), val, highPriority);
    }
    else 
    {
        this->insert(dayIndex, 0, val, highPriority);
    }
    
}

void DailyTodoList::insert(size_t dayIndex, size_t loc, const std::string& val, bool highPriority) {

    //meant for resizing
    if(dayIndex >= cap_) {
        //allocate a new array to deep copy
        Item** temp = new Item*[2*dayIndex];
        for(size_t i = 0; i < 2*dayIndex; i++) {
            temp[i] = NULL;
        }

        
        //set the  elements equal in the new array
        for(size_t i = 0; i < cap_; i++) {
            // if it has a todolist or not
            if(data_[i] != NULL) {
                temp[i] = data_[i];
            } else {
                temp[i] = NULL;
            }
        }
        cap_ = 2*dayIndex;
        delete [] data_;
        data_ = temp;

    } 

    
        Item* temp1 = new Item(val, NULL, NULL);
        addHighPriority(highPriority, val, temp1);
        Item* iBefore = NULL;
        //returns item before
        //item right before is NULL if loc 0
        if(loc == 0) {
            iBefore = NULL;
        } else {
            iBefore = data_[dayIndex];
            size_t i = 1;
            //make sure it is not out of range and move to next item
            while(i < loc) {
                if(iBefore != NULL) {
                    iBefore = iBefore->nextItem;
                    i++;
                } else {
                    delete temp1;
                    invalidLocation(false);
                }
            }
        }

        //if loc is 0
        if(iBefore == NULL) {
            temp1->nextItem = data_[dayIndex];
            data_[dayIndex] = temp1;
        } 
        //if only one item
        else if(iBefore->nextItem == NULL) {
            iBefore->nextItem = temp1;
        } else {
            temp1->nextItem = iBefore->nextItem;
            iBefore->nextItem = temp1;
        }
}


void DailyTodoList::remove(size_t dayIndex, size_t loc) {

    if(dayIndex < 0 || dayIndex >= cap_) {
        throw std::out_of_range("Invalid remove");
    }
    //if not empty
    if(!empty(dayIndex)) { 
        bool highPriority =  false;
        Item* iBefore = listItem(dayIndex, loc, false, NULL);
        Item* pBefore = NULL;
        //make sure something is in the head
        if(priorityHead_ != NULL) {
            //first item
            if(iBefore == NULL) {
                //check if it  is priority
                if(data_[dayIndex] == priorityHead_|| data_[dayIndex] == tail || data_[dayIndex]->nextPriorityItem != NULL) {
                    highPriority = true;
                    pBefore = listItem(dayIndex, loc, true, data_[dayIndex]);
                    numP--;
                }
            } //if highpriority is true 
            else if(iBefore->nextItem == tail || iBefore->nextItem == priorityHead_) {
                highPriority = true;
                pBefore = listItem(dayIndex, loc, true, iBefore->nextItem);
                numP--;
            } else if(iBefore->nextItem != NULL) {
                if(iBefore->nextItem->nextPriorityItem != NULL) {
                    highPriority = true;
                    pBefore = listItem(dayIndex, loc, true, iBefore->nextItem);
                    numP--;
                }
            }
        }
        //if highpriority
        if(highPriority) {
            //same logic as item linked list remove
            if(pBefore == NULL) {
                if(priorityHead_->nextPriorityItem != NULL) {
                    priorityHead_ = priorityHead_->nextPriorityItem;
                } else {
                    priorityHead_ = NULL;
                    tail = NULL;
                }
            } else if(pBefore->nextPriorityItem->nextPriorityItem == NULL) {
                pBefore->nextPriorityItem = NULL;
            } else {
                Item* temp = pBefore->nextPriorityItem;
                pBefore->nextPriorityItem = temp->nextPriorityItem;
                temp->nextPriorityItem = NULL;
            }
        }
        //if first item
        if(iBefore == NULL) {
            Item* curr = data_[dayIndex];
            if(curr != NULL) {
                if(data_[dayIndex]->nextItem == NULL) data_[dayIndex] = NULL;
                else data_[dayIndex] = data_[dayIndex]->nextItem;
                delete curr;
            }
            
        } //if only one item 
        else if(iBefore->nextItem->nextItem == NULL) {
            delete iBefore->nextItem;
            iBefore->nextItem = NULL;
        } else {
            Item* temp = iBefore->nextItem;
            iBefore->nextItem = temp->nextItem;
            delete temp;
        }
        
    } else {
        throw std::out_of_range("Invalid remove");
    }
}

size_t DailyTodoList::numDays() const {
    return cap_;
}

size_t DailyTodoList::numItemsOnDay(size_t dayIndex) const {

    //if in range
    if(dayIndex < cap_) {
        Item* temp = data_[dayIndex];
        size_t counter = 0;
        //if empty
        if(empty(dayIndex)) {
            return 0;
        }
        //while not the last item
        while(temp != NULL) {
            counter++;
            temp = temp->nextItem;
        }
        return counter;
    }
    else {
        throw std::out_of_range("Invalid day index");
    }
}

bool DailyTodoList::empty(size_t dayIndex) const {

    if(dayIndex < 0 ||  dayIndex >= cap_) {
        throw std::out_of_range("Invalid day index");
    }
    return data_[dayIndex] == NULL;
}

const std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc) const {

    Item* temp = NULL;
    if(loc < 0) {
        throw std::out_of_range("Location not valid");
    }
    //if only one item
    if(loc == 0) {
        //it there is an item there
        if(data_[dayIndex] != NULL) {
            temp = data_[dayIndex];
        } else {
            throw std::out_of_range("Location not valid");
        }
    } else {
        temp = data_[dayIndex];
        size_t i = 0;
        while(i < loc) {
            if(temp->nextItem != NULL) {
                temp = temp->nextItem;
                
            } else {
                throw std::out_of_range("Location not valid");
            }
            i++;
        }
    }
    return temp->val;

}

std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc) {

    Item* temp = listItem(dayIndex, loc, false, NULL);
    if(dayIndex < 0 || dayIndex >= cap_) {
        throw std::out_of_range("Location not valid");
    }
    //if first item
    if(temp == NULL) {
        //if there is not an item 
        if(data_[dayIndex] == NULL) {
            throw std::out_of_range("Location not valid");
        } else {
            return data_[dayIndex]->val;
        }
    }
    return temp->nextItem->val;
}


size_t DailyTodoList::numPriorityItems() const {
    return numP;
}

const std::string& DailyTodoList::getPriorityVal(size_t priorityLoc) const {
    
    if(priorityLoc < 0 || priorityLoc >= numPriorityItems()) {
        throw std::out_of_range("Invalid remove");
    }
    //if its the first item
    if(priorityLoc == 0) {
       if(priorityHead_ == NULL) {
            throw std::out_of_range("Invalid remove");
       } else {
        return priorityHead_->val;
       }
    }
    size_t i = 0;
    Item* temp = priorityHead_;
    //until we find the priority value
    while(i != priorityLoc) {
        if(temp != NULL) {
            temp =  temp->nextPriorityItem;
            i++;
        } else {
            throw std::out_of_range("Invalid remove");
        }
    }
    return temp->val;
}

DailyTodoList::Item* DailyTodoList::listItem(size_t dayIndex, size_t loc, bool highPriority, Item* location) {

    Item* temp = NULL;
    if(loc < 0) {
        invalidLocation(false);
    }


    //return the item right before the item we need
    if(!highPriority) {

        if(loc == 0) {
            return NULL;
        } else {
            temp = data_[dayIndex];
            size_t i = 1;
            while(i < loc) {
                if(temp != NULL) {
                    temp = temp->nextItem;
                    i++;
                } else {
                    invalidLocation(false);
                }
            }
        }

        return temp;

    } //return the high priority item before the item we need 
    else {

        temp = priorityHead_;
        if(temp == location) {
            return NULL;
        }
        //until we get the item
        while(temp->nextPriorityItem != location) {
            if(temp->nextPriorityItem != location) {
                temp = temp->nextPriorityItem;
            }
        }

        return temp;
    }
}


void DailyTodoList::addHighPriority(bool highPriority, std::string v, Item* temp) {

    // add high priority item using linked in logic
    if(highPriority) {
        if(priorityHead_ == NULL) {
            priorityHead_ = temp;
            tail = temp;
        } else {
            tail->nextPriorityItem = temp;
            tail = temp;
        }
        numP++;
    } 
}


void DailyTodoList::invalidLocation(bool valid) {

    
    if(!valid) {
        throw std::out_of_range("Location not valid");
    }
}