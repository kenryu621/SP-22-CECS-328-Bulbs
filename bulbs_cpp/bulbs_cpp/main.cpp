#include <iostream>
#include <vector>
#include "StudentSolver.h"

int main() {
	std::vector<int> vec1 = { -4,-4,-1 };
	std::vector<int> vec2 = { 13,-9,-14 };
	std::vector<int> vec3 = { 4,-7,-2 };
	std::vector<int> vec4 = { -2,6,3 };
	std::vector<int> vec5 = { -4,-3,-6 };
	std::vector<int> vec6 = { 7,11,-10 };
	std::vector<int> vec7 = { 4,-7,6 };
	std::vector<int> vec8 = { 5,6,4 };
	std::vector<int> vec9 = { 10,14,-9 };
	std::vector<int> vec10 = { -6,-8,11 };
	std::vector<std::vector<int>> final_vec;
	final_vec.push_back(vec1);
	final_vec.push_back(vec2);
	final_vec.push_back(vec3);
	final_vec.push_back(vec4);
	final_vec.push_back(vec5);
	final_vec.push_back(vec6);
	final_vec.push_back(vec7);
	final_vec.push_back(vec8);
	final_vec.push_back(vec9);
	final_vec.push_back(vec10);
	for (std::vector<int> vec : final_vec) {
		for (int num : vec) {
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
	std::vector<bool> omg = StudentSolver::solve(final_vec);
	int i = 0;
	std::cout << std::endl;
	for (bool om : omg) {
		std::cout << om << " ";
	}
	std::cout << std::endl;
	return 0;
}