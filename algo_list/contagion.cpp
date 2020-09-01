#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
// #include <pair>

void contagion_linear(std::vector<std::pair<int,float>*> &infected_list, 
											std::vector<std::pair<int,float>*> &safe_list);

void contagion_rand(std::vector<std::pair<int,float>*> &infected_list, 
										std::vector<std::pair<int,float>*> &safe_list,
										int max_iteration);
struct xorshift128_state {
	uint32_t x, y, z, w;
};
uint32_t xor128(struct xorshift128_state &state);

void set_random_list(std::vector<std::pair<int,float>> &list, int num_infected, int length);
void set_sub_list_ptr(std::vector<std::pair<int,float>> &list, 
											std::vector<std::pair<int,float>*> &infected_list, 
											std::vector<std::pair<int,float>*> &safe_list);




int random_int(int max);
int random_int(int min, int max, std::default_random_engine &generator);
float random(float max);
float random(float min, float max, std::default_random_engine &generator);

void test_content(std::vector<std::pair<int,float>> &list, 
									std::vector<std::pair<int,float>*> &infected_list, 
									std::vector<std::pair<int,float>*> &safe_list);
template <typename T>
void end_time(T start, unsigned int num_access) {
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << " for " << num_access << " access" <<std::endl;
}



int main() {
	int num = 100000;
	int num_infected = 3000;
	int round = 1;

	std::vector<std::pair<int,float>> list;
	std::vector<std::pair<int,float>*> infected_list;
	std::vector<std::pair<int,float>*> safe_list;


	std::cout << "LINEAR ITERATION" << std::endl;
	set_random_list(list, num_infected, num);
	set_sub_list_ptr(list, infected_list, safe_list);
	test_content(list, infected_list, safe_list);
	for(int i = 0 ; i < round ; i++) {
		contagion_linear(infected_list, safe_list);
		set_sub_list_ptr(list, infected_list, safe_list);
		test_content(list, infected_list, safe_list);
	}
  
  std::cout << "RANDOM ITERATION" << std::endl;
  set_random_list(list, num_infected, num);
	set_sub_list_ptr(list, infected_list, safe_list);
	test_content(list, infected_list, safe_list);
	for(int i = 0 ; i < round ; i++) {
		int max_iter = infected_list.size() * safe_list.size();
		contagion_rand(infected_list, safe_list, max_iter);
		set_sub_list_ptr(list, infected_list, safe_list);
		test_content(list, infected_list, safe_list);
	}
}




void contagion_linear(std::vector<std::pair<int,float>*> &infected_list, 
											std::vector<std::pair<int,float>*> &safe_list) {
	auto start = std::chrono::system_clock::now();
	unsigned int iter = 0;
	float dist_max = 0.0001;

	for(int i = 0 ; i < infected_list.size() ; i++) {
		iter++;
		float pos_a = infected_list.at(i)->second;
		for(int j = 0 ; j < safe_list.size() ; j++) {
			std::pair<int,float>*  host = safe_list.at(j);
			float pos_b = host->second;
			iter++;
			if(abs(pos_b - pos_a) < dist_max) {
				host->first = 1;
			}
		}
	}
	end_time(start, iter);
}

void contagion_rand(std::vector<std::pair<int,float>*> &infected_list, 
										std::vector<std::pair<int,float>*> &safe_list,
										int max_iteration) {
	auto start = std::chrono::system_clock::now();
	
	float dist_max = 0.0001;
	xorshift128_state state_inf;
	state_inf.x = static_cast<uint32_t>(random_int(UINT_MAX));
	state_inf.y = static_cast<uint32_t>(random_int(UINT_MAX));
	state_inf.z = static_cast<uint32_t>(random_int(UINT_MAX));
	state_inf.w = static_cast<uint32_t>(random_int(UINT_MAX));
	xorshift128_state state_saf;
	state_saf.x = static_cast<uint32_t>(random_int(UINT_MAX));
	state_saf.y = static_cast<uint32_t>(random_int(UINT_MAX));
	state_saf.z = static_cast<uint32_t>(random_int(UINT_MAX));
	state_saf.w = static_cast<uint32_t>(random_int(UINT_MAX));
	int len_inf = infected_list.size();
	int len_saf = safe_list.size();
	
	unsigned int iter = 0;
	while(iter < max_iteration) {
	//for(int i = 0 ; i < max_iteration ; i++) {
		int index_inf = floor((xor128(state_inf) / static_cast<float>(UINT_MAX)) * len_inf);
		int index_saf = floor((xor128(state_saf) / static_cast<float>(UINT_MAX)) * len_saf);
		float pos_inf = infected_list.at(index_inf)->second;
		std::pair<int,float>*  host = safe_list.at(index_saf);
		float pos_safe = host->second;
		if(abs(pos_inf - pos_safe) < dist_max) {
			host->first = 1;
		}
		iter++;
	}
	end_time(start, iter);
}


uint32_t xor128(struct xorshift128_state &state) {
	static uint32_t x = state.x;
	static uint32_t y = state.y;
	static uint32_t z = state.z;
	static uint32_t w = state.w;
	uint32_t t;
	t = x ^ (x << 11);
	x = y; 
	y = z;
	z = w;
	return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}







// test
void test_content(std::vector<std::pair<int,float>> &list, 
									std::vector<std::pair<int,float>*> &infected_list, 
										std::vector<std::pair<int,float>*> &safe_list) {

	// std::cout << "list.size(): " << list.size() << std::endl;
	std::cout << "infected_list.size(): " << infected_list.size() << std::endl;
	std::cout << "safe_list.size(): " << safe_list.size() << std::endl;

	// int target_index = 0;
	// list.at(target_index).first = -1;
	// std::pair<int,float>*  host = infected_list.at(target_index);
	// std::cout << "host->first: " << host->first << std::endl; // indirect style
	// host->first = 3;
	// std::cout << "(*infected_list.at(target_index)).first: " << (*infected_list.at(target_index)).first << std::endl; // c style
	// std::cout << "infected_list.at(target_index)->first: " << infected_list.at(target_index)->first << std::endl; // c++ style
	// std::cout << "list.at(target_index).first: " << list.at(target_index).first << std::endl;

}



// utils
void set_random_list(std::vector<std::pair<int,float>> &list, int num_infected, int length) {
	float range = 1.0f;
	list.clear();
	for(int i = 0 ; i < length ; i++) {
		int infected = 0;
		if(i < num_infected)
			infected = 1;
		std::pair<int,float> host(infected,random(range));
		list.push_back(host);
	}
}

void set_sub_list_ptr(std::vector<std::pair<int,float>> &list, 
											std::vector<std::pair<int,float>*> &infected_list, 
											std::vector<std::pair<int,float>*> &safe_list) {
	infected_list.clear();
	safe_list.clear();
	int length = list.size();
	for(int i = 0 ; i < length ; i++) {
		std::pair<int,float>* host = &list.at(i);
		if(host->first == 1) {
			infected_list.push_back(host);
		} else {
			safe_list.push_back(host);
		}
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


float random(float max) {
	std::random_device seed;
	std::default_random_engine gen(seed());
	return random(0, max, gen);
}

float random(float min, float max, std::default_random_engine &generator) {
	std::uniform_real_distribution<float> gen_rand_float(min,max);
	return gen_rand_float(generator); 
}