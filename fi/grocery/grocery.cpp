//
// You must provide your implementation of maxGroceryBox() and all
// helper functions in this file.
//

#include "grocery.h"

// You may prototype helper functions here and implement them below

bool weightHelper(const std::vector<GItem>& inventory, int weight_limit, std::vector<GItem> curr, int index, std::vector<GItem>& max, std::vector<int>& ind);
int getValue(const std::vector<GItem>& item);
int getWeight(const std::vector<GItem>& item);
bool isIn(int j, std::vector<int>& curr);


std::vector<GItem> maxGroceryBox(const std::vector<GItem>& inventory, int weight_limit)
{
    // TODO implement!
    std::vector<GItem> curr;
    std::vector<GItem> max;
    std::vector<int> ind;
    weightHelper(inventory, weight_limit, curr, 0, max, ind);
    return max;


}


bool weightHelper(const std::vector<GItem>& inventory, int weight_limit, std::vector<GItem> curr, int index, std::vector<GItem>& max, std::vector<int>& ind) {

	if(curr.size() > inventory.size()) return false;
	if(getWeight(curr) > weight_limit) return false;
	if(getWeight(curr) == weight_limit) {
		max = curr;
		return true;
	}
	if(getValue(curr) > getValue(max)) {
		max = curr;
	}
	
	else {
		for(unsigned int i = index; i < inventory.size(); i++) {
			bool temp = false;
			if(!isIn(i, ind)) {
				curr.push_back(inventory[i]);
				ind.push_back(i);
				temp = true;
			}
			
			weightHelper(inventory, weight_limit, curr, index+1, max, ind);
			if(temp) {
				curr.pop_back();
				ind.pop_back();
			}
		}
	}
		return false;

}

int getValue(const std::vector<GItem>& item) {

	if(item.size() == 0) return 0;
	int sum = 0, temp;
	for(unsigned int i = 0; i < item.size(); i++) {
		temp = item[i].value;
		sum += temp;
	}

	return sum;
}


int getWeight(const std::vector<GItem>& item) {

	if(item.size() == 0) return 0;
	int sum = 0, temp;
	for(unsigned int i = 0; i < item.size(); i++) {
		temp = item[i].weight;
		sum += temp;
	}

	return sum;
}

bool isIn(int j, std::vector<int>& ind) {



	for(unsigned int i = 0; i < ind.size(); i++) {

		if(j == ind[i]) return true;
	}

	return false;

}
