/**
* count matching pair and put in the pointer list
* 2020-2020
* v 0.0.1
* clang++ -std=c++11 pair_ptr.cpp && ./a.out
*/
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
#include <cmath>


template <typename T>
void end_time(T start) {
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << std::endl;
}

void set_random_list(std::vector<float> &list, int length);
void set_static_list(std::vector<float> &list);

float random(float max);
float random(float min, float max, std::default_random_engine &generator);

int pair_linear_ptr(std::vector<float> &list, std::vector<std::pair<float*,float*>> &pair_list, float dist, bool unique_is);
void show_pair_ptr(std::vector<std::pair<float*,float*>> &pair_list);

int main() {
	bool show_pair_is = false;
	bool short_list_is = false;
	int length = 100000;

	std::vector<float> list;
	std::vector<std::pair<float*,float*>> pair_list_ptr;

	// setting
	if(short_list_is)
		set_static_list(list);
	else
		set_random_list(list, length);

	// algo
	float dist = 0.01f;

	auto start = std::chrono::system_clock::now();
	int num_pair = pair_linear_ptr(list, pair_list_ptr, dist, true);
	std::cout << "UNIQUES PAIRS: "  << num_pair << " for " << list.size() << " elements" << std::endl;
	if(show_pair_is)
		show_pair_ptr(pair_list_ptr);
	end_time(start);

	pair_list_ptr.clear();
	start = std::chrono::system_clock::now();
	num_pair = pair_linear_ptr(list, pair_list_ptr, dist, false);
	std::cout << "\nALL PAIRS: "  << num_pair << " for " << list.size() << " elements" << std::endl;
	if(show_pair_is)
		show_pair_ptr(pair_list_ptr);
	end_time(start);

	return (0);
}

int pair_linear_ptr(std::vector<float> &list, std::vector<std::pair<float*,float*>> &pair_list, float dist, bool unique_is) {
	int count = 0;

	// create a pointer copy list
	std::vector<float*> temp;
	for(int i = 0 ; i < list.size() ; i++) {
		temp.push_back(&list.at(i));
	}

	
	for(int i = 0 ; i < list.size() ; i++) {
		float *a = &list.at(i);
		if(temp.size() > 0) {
			// no comparaison with itself
			temp.erase(temp.begin()); 
			for(int j = 0 ; j < temp.size() ; j++) {
				float *b = temp.at(j);
				float abs_diff = abs(*a-*b);
				if(abs_diff < dist) {
					std::pair<float*,float*> p(a,b);
					pair_list.push_back(p);
					count++;
					// erase the succes element to avoid an other pair with the winner.
				  if(unique_is) {
				  	temp.erase(temp.begin() + j);
				  	break;
				  }
				}
			}
		}
	}
	return count;
}



// utils
void show_pair_ptr(std::vector<std::pair<float*,float*>> &pair_list) {
	for(std::pair<float*,float*> p : pair_list) {
		std::cout << *p.first << " / " << *p.second << std::endl;
	}
}

void set_static_list (std::vector<float> &list) {
	float arg[] = {0.101f, 0.1f, 0.15f, 0.25f, 0.50f, 0.9f, 0.999f, 1.0f, 1.001f};
	// int length = (sizeof(arg)/ sizeof(float));
	int length = (sizeof(arg)/ sizeof(*arg));
	std::cout << "length static list: " << length << std::endl;
	list.assign(arg,arg+length);
}

void set_random_list(std::vector<float> &list, int length) {
	float range = 1.0f;
	for(int i = 0; i < length ; i++) {
		list.push_back(random(range));
	}
}

float random(float max) {
	std::random_device seed;
	std::default_random_engine gen(seed());
	return random(0, max, gen);
}

float random(float min, float max, std::default_random_engine &generator) {
	std::uniform_real_distribution<float> gen_rand_float(min,max);
	return gen_rand_float(generator); 
}



