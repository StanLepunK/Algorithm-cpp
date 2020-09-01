#include <iostream>
#include <limits>
// https://en.wikipedia.org/wiki/George_Marsaglia
// https://en.wikipedia.org/wiki/Xorshift
struct xorshift128_state {
	uint32_t x, y, z, w;
};
// nice value ???

// state->x = 123456789;
// state->y = 362436069;
// state->z = 521288629;
// state->w = 88675123;


uint32_t xor128(struct xorshift128_state *state) {
	static uint32_t x = state->x;
	static uint32_t y = state->y;
	static uint32_t z = state->z;
	static uint32_t w = state->w;
	uint32_t t;
	t = x ^ (x << 11);   
	x = y; 
	y = z; 
	z = w;
	return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}


int main() {
	std::cout << "\nxor128 random" << std::endl;
	xorshift128_state *state;
	state->x = 1;
	state->y = 2;
	state->z = 3;
	state->w = 4;

	for(int i = 0 ; i < 10 ; i++) {
		std::cout << xor128(state) << std::endl;
	}


	std::cout << "\nxor128 random to normal" << std::endl;
	state->x = 123456789;
	state->y = 362436069;
	state->z = 521288629;
	state->w = 88675123;
	for(int i = 0 ; i < 100 ; i++) {
		std::cout << xor128(state) / static_cast<float>(UINT_MAX) << std::endl;
	}


}