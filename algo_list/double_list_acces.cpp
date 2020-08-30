#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <time.h>
#include <chrono>
void linear_loop_vector(std::vector<float> &list_a, std::vector<float> &list_b, int max, bool pertinent);
void random_loop_vector(std::vector<float> &list_a ,std::vector<float> &list_b, int max, bool pertinent);

void build_list_vec(std::vector<float> &list_a, std::vector<float> &list_b, std::default_random_engine &generator, int num);
void build_list_map(std::map<int,float> &list_a, std::map<int,float> &list_b, std::default_random_engine &generator, int num);







int main() {
	int num = 1000;
	std::vector<float> list_vec_a;
	std::vector<float> list_vec_b;
	std::map<int,float> list_map_a;
	std::map<int,float> list_map_b;

	std::random_device seed;
	std::default_random_engine generator(seed());


	build_list_vec(list_vec_a, list_vec_b, generator, num);
	build_list_map(list_map_a, list_map_b, generator, num);


	int max = 1;

	std::cout << "\ncount all vctor succes: " << std::endl;
	linear_loop_vector(list_vec_a, list_vec_b, max, false);
	random_loop_vector(list_vec_a, list_vec_b, max,false);
	// std::cout << "\nstop at first vector success: " << std::endl;
	linear_loop_vector(list_vec_a, list_vec_b, max, true);
	random_loop_vector(list_vec_a, list_vec_b, max, true);

}


void build_list_map(std::map<int,float> &list_a, std::map<int,float> &list_b, std::default_random_engine &generator, int num) {
	auto start = std::chrono::system_clock::now();
	for(int i = 0 ; i < num ; i++) {
		std::uniform_real_distribution<float> gen_rand_float(0,100);
		float val_a = gen_rand_float(generator);
		float val_b = gen_rand_float(generator);
		list_a.insert(std::pair<int,float>(0,val_a));
		list_b.insert(std::pair<int,float>(0,val_b));
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "build map list in: " << elapsed_seconds.count() << std::endl;
}



void build_list_vec(std::vector<float> &list_a, std::vector<float> &list_b, std::default_random_engine &generator, int num) {
	auto start = std::chrono::system_clock::now();
	for(int i = 0 ; i < num ; i++) {
		std::uniform_real_distribution<float> gen_rand_float(0,100);
		float val_a = gen_rand_float(generator);
		float val_b = gen_rand_float(generator);
		list_a.push_back(val_a);
		list_b.push_back(val_b);
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "build vector list in: " << elapsed_seconds.count() << std::endl;
}

















/**
* vector loop
*/
void random_loop_vector(std::vector<float> &list_a ,std::vector<float> &list_b, int max, bool pertinent) {
	int bingo = 0;
	int iteration = 0;
	int max_iter = list_a.size() * list_b.size();
	auto start = std::chrono::system_clock::now();

	std::random_device seed;
	std::default_random_engine generator(seed());
	std::uniform_int_distribution<int> gen_rand_int(0,list_a.size() - 1);
	for(int i = 0 ; i < max_iter ; i++) {
		iteration++;	
		int index_a = gen_rand_int(generator);
		int index_b = gen_rand_int(generator);
		float a = list_a.at(index_a);
		float b = list_b.at(index_b);
		float dist = abs(a - b);
		if(dist < max) {
			bingo++;
			if(pertinent) {
				break;
			}
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "random loop in: " << elapsed_seconds.count() << std::endl;
	std::cout << "bingo: " << bingo << std::endl;
	std::cout << "iteration: " << iteration << std::endl;
}


void linear_loop_vector(std::vector<float> &list_a, std::vector<float> &list_b, int max, bool pertinent) {
	bool succes_is = false;

	int bingo = 0;
	int iteration = 0;
	auto start = std::chrono::system_clock::now();
	for(int i = 0 ; i < list_a.size() ; i++) {
		iteration++;
		for(int k = 0 ; k < list_b.size() ; k++) {
			iteration++;
			float a = list_a.at(i);
			float b = list_b.at(k);
			float dist = abs(a - b);
			if(dist < max) {
				succes_is = true;
				bingo++;
				if(pertinent) {
					break;
				}
			}
		}
		if(succes_is && pertinent)
			break;
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "linear loop in: " << elapsed_seconds.count() << std::endl;
	std::cout << "bingo: " << bingo << std::endl;
	std::cout << "iteration: " << iteration << std::endl;
}