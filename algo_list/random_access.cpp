#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
#include <limits>
// #include <pair>

void set_random_list(std::vector<float> &list, int length);
int random_int(int max);
int random_int(int min, int max, std::default_random_engine &generator);
float random(float max);
float random(float min, float max, std::default_random_engine &generator);

struct xorshift128_state {
	uint32_t x, y, z, w;
};

uint32_t xor128(struct xorshift128_state &state);

template <typename T>
void end_time(T start, int num_access) {
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << " for " << num_access << " access" <<std::endl;
}





int main() {
	int length = 100000;
	int num_infected = 1;

	std::vector<float> list;
	set_random_list(list, length);

	std::cout << "\nRANDOM ACCESS with seed creation at each iteration" << std::endl;
	auto start = std::chrono::system_clock::now();
	for(int i = 0 ; i < length ; i++) {
		int index = random_int(length -1);
		float elem = list.at(index);
	}
	end_time(start, length);

	std::cout << "\nRANDOM ACCESS with seed at the begin" << std::endl;
	start = std::chrono::system_clock::now();
	std::random_device seed;
	std::default_random_engine gen(seed());
	for(int i = 0 ; i < length ; i++) {
		int index = random_int(0, length -1, gen);
		float elem = list.at(index);
	}
	end_time(start, length);

	std::cout << "\nRANDOM XOR128 ACCESS with seed at the begin" << std::endl;
	start = std::chrono::system_clock::now();
	xorshift128_state state;
	state.x = static_cast<uint32_t>(random_int(UINT_MAX));
	state.y = static_cast<uint32_t>(random_int(UINT_MAX));
	state.z = static_cast<uint32_t>(random_int(UINT_MAX));
	state.w = static_cast<uint32_t>(random_int(UINT_MAX));
	for(int i = 0 ; i < length ; i++) {
		int index = floor((xor128(state) / static_cast<float>(UINT_MAX)) * length);
		float elem = list.at(index);
	}
	end_time(start, length);

	std::cout << "\nLINEAR ACCESS" << std::endl;
	start = std::chrono::system_clock::now();
	for(int i = 0 ; i < length ; i++) {
		float elem = list.at(i);
	}
	end_time(start, length);

	return(0);
}



















// utils
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



void set_random_list(std::vector<float> &list, int length) {
	float range = 1.0f;
	for(int i = 0; i < length ; i++) {
		list.push_back(random(range));
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