/**
* O   L    A  U   P       S
* ONE LIST && USE POINTER SUB-LISTS
*
* DISPATCH
* v 0.0.1
* 2020-2020
* split a list into sub-lists according to the state of the items
*
* 
*/
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
/**
* HEADER
*/
void dispatch(std::vector<int> &list, std::vector<int*> &sub_0, std::vector<int*> &sub_1, std::vector<int*> &sub_2);
void set_random_list(std::vector<int> &list, int num_states, int length);

int random_int(int max);
int random_int(int min, int max, std::default_random_engine &generator);


template <typename T>
void end_time(T start, unsigned int num_access) {
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << " for " << num_access << " access" <<std::endl;
}


/**
* MAIN
*/
int main() {
	int length = 100000;
	int num_states = 3;
	std::vector<int> list;
	std::vector<int*> sublist_0, sublist_1, sublist_2;

	set_random_list(list, num_states, length);
	dispatch(list, sublist_0, sublist_1, sublist_2);
	std::cout << "list.size(): " << list.size() << std::endl;
	std::cout << "sublist_0.size(): " << sublist_0.size() << std::endl;
	std::cout << "sublist_1.size(): " << sublist_1.size() << std::endl;
	std::cout << "sublist_2.size(): " << sublist_2.size() << std::endl;

	for(int i = 0 ; i < list.size() / 2 ; i++) {
		list.at(i) = 0 ;
	}
	dispatch(list, sublist_0, sublist_1, sublist_2);
	std::cout << "list.size(): " << list.size() << std::endl;
	std::cout << "sublist_0.size(): " << sublist_0.size() << std::endl;
	std::cout << "sublist_1.size(): " << sublist_1.size() << std::endl;
	std::cout << "sublist_2.size(): " << sublist_2.size() << std::endl;
}

/**
* FUNCTION
*/
void dispatch(std::vector<int> &list, std::vector<int*> &sub_0, std::vector<int*> &sub_1, std::vector<int*> &sub_2) {
	sub_0.clear();
	sub_1.clear();
	sub_2.clear();
	int length = list.size();
	for(int i = 0 ; i < length ; i++) {
		int *elem = &list.at(i);
		if(*elem == 0) {
			sub_0.push_back(elem);
		} else if(*elem == 1) {
			sub_1.push_back(elem);
		} else if(*elem == 2) {
			sub_2.push_back(elem);
		}
	}
}


/**
* UTILS
*/
void set_random_list(std::vector<int> &list, int num_states, int length) {
	list.clear();
	for(int i = 0 ; i < length ; i++) {
		int state = random_int(num_states -1);
		list.push_back(state);
	}
}


int random_int(int max) {
	std::random_device seed;
	std::default_random_engine gen(seed());
	return random_int(0, max, gen);
}

int random_int(int min, int max, std::default_random_engine &generator) {
	std::uniform_int_distribution<int> gen_rand_int(min,max);
	return gen_rand_int(generator); 
}