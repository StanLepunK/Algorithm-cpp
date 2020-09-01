#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
// #include <pair>

void set_random_list(std::vector<std::pair<int,float>> &list, int num_infected, int length);
int random_int(int max);
int random_int(int min, int max, std::default_random_engine &generator);
float random(float max);
float random(float min, float max, std::default_random_engine &generator);

int main() {
	int num = 1000;
	int num_infected = 1;

	std::vector<std::pair<int,float>> list;
	set_random_list(list, num_infected, num);


}


















// utils
void set_random_list(std::vector<std::pair<int,float>> &list, int num_infected, int length) {
	float range = 1.0f;
	for(int i = 0; i < length ; i++) {
		int infected = 0;
		if(i < num_infected)
			infected = 1;
		std::pair<int,float> host(infected,random(range));
		list.push_back(host);
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