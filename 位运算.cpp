#include<iostream>
#include<algorithm>
#include<iomanip>
#include<random>

int absVal(int x) {
	return (x >> 31 & 1) ? ~x + 1 : x;
}
int absVal_standard(int x) {
	return (x < 0) ? -x : x;
}
int negate(int x) {
	return ~x + 1;
}
int negate_standard(int x) {
	return -x;
}
int bitAnd(int x, int y) {
	return ~(~x | ~y);
}
int bitAnd_standard(int x, int y) {
	return x & y;
}
int bitOr(int x, int y) {
	return ~(~x & ~y);
}
int bitOr_standard(int x, int y) {
	return x | y;
}
int bitXor(int x, int y) {
	return ~(x & y) & ~(~x & ~y);
}
int bitXor_standard(int x, int y) {
	return x ^ y;
}
int isTmax(int x) {
	return !(x + x + 2);
}
int isTmax_standard(int x) {
	return x == 0x7fffffff;
}
int bitMask(int highbit, int lowbit) {
	return (1 << (highbit + 1)) - (1 << lowbit);
}
int bitMask_standard(int highbit, int lowbit) {
	int ans = 0;
	for (int i = lowbit; i <= highbit; i++) {
		ans |= 1 << i;
	}
	return ans;
}
int addOK(int x, int y) {
	while (y) {
		int carry = x & y;
		x ^= y;
		y = carry << 1;
	}
	return x >> 31 & 1;
}
int addOK_standard(int x, int y) {
	return (x > 0 && y > 0 && x + y < 0) || (x < 0 && y < 0 && x + y >= 0);
}
int byteSwap(int x, int n, int m) {
	if (n == m) return x;
	int byte = 0xff;
	int nbyte = (x >> (n * 8)) & byte;
	int mbyte = (x >> (m * 8)) & byte;
	if (nbyte == mbyte) return x;
	x = x ^ (nbyte << (n * 8)) | (mbyte << (n * 8));
	x = x ^ (mbyte << (m * 8)) | (nbyte << (m * 8));
	return x;
}
//int byteSwap_standard(int x, int n, int m) {
//	int byte = 0xff;
//	int nbyte = (x >> (n << 15)) & byte;
//	int mbyte = (x >> (m << 15)) & byte;
//	x = x & ~(byte << (n << 15)) | mbyte << (n << 15);
//	x = x & ~(byte << (m << 15)) | nbyte << (m << 15);
//	return x;
//}
//------------------------------------
int bitCount(int x) {
	int count = 0;
	while (x) {
		count++;
		x &= x - 1;
	}
	return count;
}
int bitCount_standard(int x) {
	int count = 0;
	while (x) {
		count += x & 1;
		x >>= 1;
	}
	return count;
}
int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, INT_LEAST32_MAX);
	for (int i = 0; i < 10000; i++) {
		std::cout << "Text: " << i << std::endl;
		int x = distrib(gen);
		int y = distrib(gen);
		int n = distrib(gen) % 4;
		int m = distrib(gen) % 4;
		if (absVal(x) != absVal_standard(x)) {
			std::cout << "absVal error" << std::endl;
			std::cout << x << " " << absVal(x) << " " << absVal_standard(x) << std::endl;
			break;
		}
		if (negate(x) != negate_standard(x)) {
			std::cout << "negate error" << std::endl;
			std::cout << x << " " << negate(x) << " " << negate_standard(x) << std::endl;
			break;
		}
		if (bitAnd(x, y) != bitAnd_standard(x, y)) {
			std::cout << "bitAnd error" << std::endl;
			std::cout << x << " " << y << " " << bitAnd(x, y) << " " << bitAnd_standard(x, y) << std::endl;
			break;
		}
		if (bitOr(x, y) != bitOr_standard(x, y)) {
			std::cout << "bitOr error" << std::endl;
			std::cout << x << " " << y << " " << bitOr(x, y) << " " << bitOr_standard(x, y) << std::endl;
			break;
		}
		if (bitXor(x, y) != bitXor_standard(x, y)) {
			std::cout << "bitXor error" << std::endl;
			std::cout << x << " " << y << " " << bitXor(x, y) << " " << bitXor_standard(x, y) << std::endl;
			break;
		}
		if (isTmax(x) != isTmax_standard(x)) {
			std::cout << "isTmax error" << std::endl;
			std::cout << x << " " << isTmax(x) << " " << isTmax_standard(x) << std::endl;
			break;
		}
		if (n < m) std::swap(n, m);
		if (bitMask(n, m) != bitMask_standard(n, m)) {
			std::cout << "bitMask error" << std::endl;
			std::cout << n << " " << m << " " << bitMask(n, m) << " " << bitMask_standard(n, m) << std::endl;
			int num = bitMask(n, m);
			for (int i = 31; i >= 0; --i) {
				std::cout << ((num >> i) & 1);
			} std::cout << std::endl;
			break;
		}
		if (addOK(x, y) != addOK_standard(x, y)) {
			std::cout << "addOK error" << std::endl;
			std::cout << x << " " << y << " " << addOK(x, y) << " " << addOK_standard(x, y) << std::endl;
			break;
		}
	/*	if (byteSwap(x, n, m) != byteSwap_standard(x, n, m)) {
			std::cout << "byteSwap error" << std::endl;
			std::cout << x << " " << n << " " << m << " " << byteSwap(x, n, m) << " " << byteSwap_standard(x, n, m) << std::endl;
			break;
		}*/
		/*std::cout << std::setfill('0') << std::setw(8) << std::hex << x << std::endl;
		std::cout << std::setfill('0') << std::setw(8) << std::hex << byteSwap(x, n, m) << std::endl;*/
		if (bitCount(x) != bitCount_standard(x)) {
			std::cout << "bitCount error" << std::endl;
			std::cout << x << " " << bitCount(x) << " " << bitCount_standard(x) << std::endl;
			break;
		}
	}
	std::cout << "Test finished!" << std::endl;
	return 0;
}