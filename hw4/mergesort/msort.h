#include <vector>
#include <iostream>
#include <cmath>

/**
 * Performs mergesort on the provided vector using
 * the Compare object, comp, to peform ALL comparisons
 *
 * Must run in O(n*log(n))
 */
template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp );

template <class T, class Compare >
void sort(std::vector<T>& list, Compare& comp);

template <class T, class Compare >
void merge(std::vector<T>& list, std::vector<T>& left, std::vector<T>& right, Compare& comp);

template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp ) {

	sort(list, comp);
}


template <class T, class Compare >
void sort(std::vector<T>& list, Compare& comp) {
	if(list.size() > 1) {
		//int m = floor((left+right)/2);
		int m = list.size()/2;
		typename std::vector<T> left(m, list[0]);
		typename std::vector<T> right(list.size()-m, list[0]);
		for(int i = 0; i < m; i++) {
			left[i] = list[i];
		}

		for(unsigned int i = 0; i < list.size() - m; i++) {
			right[i] = list[i+m];
		}
		// for(unsigned int k=0; k < list.size(); k++) {
		// 	std::cout << list[k] << " ";
		// //list[k+1] = temp[k];

		// }

		// std::cout << std::endl;
		// std::cout << "m: " << m << std::endl;

		sort(left, comp);
		sort(right, comp);
		// for(unsigned int k=0; k < list.size(); k++) {
		// 	std::cout << list[k] << " ";
		// //list[k+1] = temp[k];

		// }
		// std::cout  << std::endl;
		merge(list, left, right, comp);
	}
}


template <class T, class Compare >
void merge(std::vector<T>& list, std::vector<T>& left, std::vector<T>& right, Compare& comp) {

	// typename std::vector<T> temp(right, 0);
	// unsigned int s1 = 1, e1 = m, s2 = m+1, e2 = right;

	// while(s1 < e1 && s2 < e2) {
	// 	if(comp(list[s1], list[s2])) {
	// 		temp.push_back(list[s1]);
	// 		s1++;
	// 	} else {
	// 		temp.push_back(list[s2]);
	// 		s2++;
	// 	}
	// }

	// while(s1 < e1) {
	// 	temp.push_back(list[s1++]);
	// 	//s1++;
	// } 

	// while(s2 < e2) {
	// 	temp.push_back(list[s2++]);
	// 	//s2++;
	// }
	
	// for (unsigned int i = 0; i < temp.size() && left+i < e2; i++)	{
	// 	list[left+i] = temp[i];
	// } 

	// while(s1 < e1 && s2 < e2){
	// if(input[s1] < input[s2]){
	// result.push_back(input[s1++]);
	// }
	// else {
	// result.push_back(input[s2++]);
	// }
	// }
	// while(s1 < e1){
	// result.push_back(input[s1++]);
	// }
	// while(s2 < e2){
	// result.push_back(input[s2++]);
	// }
	// typename std::vector<T> temp(right, 0);
	// int i = 1;
	// int j = m+1;
	// int k = 0;

	// while(i <= m || j <= right) {

	// 	if(i <= m && (j > right || comp(list[i], list[j]))) {
	// 		//smallest is on left
	// 		temp[k] = list[i];
	// 		i++;
	// 		k++;
	// 	} else {
	// 		temp[k] = list[j];
	// 		j++;
	// 		k++;
	// 	}
	// }

	// // for (unsigned int i = 0; i < temp.size() && left+i < m; i++)	{
	// // 	list[i+1] = temp[i];
	// // } 
	// for(k=0; k < right + 1 - 1; k++) {
	// 	//std::cout << temp[k] << std::endl;
	// 	list[k+1] = temp[k];
	// } 

	unsigned int i = 0;
	unsigned int j = 0;
	int k = 0;

	while(i < left.size() || j < right.size()) {

		if(i < left.size() && (j >= right.size() || comp(left[i], right[j]))) {
			//smallest is on left
			list[k] = left[i];
			i++;
			k++;
		} else {
			list[k] = right[j];
			j++;
			k++;
		}
	}





}

