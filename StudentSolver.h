#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "StudentSolver.h"

static std::vector<bool> int_to_bool(int num, int bottom_m, int top_m) {
	std::vector<bool> possible_answer(top_m, false);
	while (num > 0) {
		possible_answer[--top_m] = num % 2;
		num = num / 2;
	}
	return possible_answer;
}

static std::vector<std::vector<bool>> recurrsive(int bottom_m, int top_m, std::vector<std::vector<int>> bulbs) {
	int middle_m = top_m - ((top_m - bottom_m + 1) / 2);
	if (top_m - bottom_m > 10) {
		std::vector<std::vector<int>> left_m_bulbs;
		std::vector<std::vector<int>> right_m_bulbs;
		for (std::vector<int> row : bulbs) {
			bool left_flag = false, right_flag = false, wrong_flag = false;
			for (int bulb : row) {
				if (abs(bulb) <= middle_m && abs(bulb) >= bottom_m)
					left_flag = true;
				else if (abs(bulb) >= middle_m + 1 && abs(bulb) <= top_m)
					right_flag = true;
				else
					wrong_flag = true;
			}
			if (wrong_flag || (left_flag && right_flag))
				continue;
			else if (!wrong_flag && left_flag)
				left_m_bulbs.push_back(row);
			else if (!wrong_flag && right_flag)
				right_m_bulbs.push_back(row);
		}
		std::vector<std::vector<bool>> left_possible_bools = recurrsive(bottom_m, middle_m, left_m_bulbs);
		std::vector<std::vector<bool>> right_possible_bools = recurrsive(middle_m + 1, top_m, right_m_bulbs);
		std::vector<std::vector<bool>> filtered_possible_answer;
		int b_count = 0;
		for (std::vector<bool> left_bools : left_possible_bools) {
			for (std::vector<bool> right_bools : right_possible_bools) {
				std::vector<bool> test;
				test.reserve(right_bools.size());
				test.insert(test.end(), left_bools.begin(), left_bools.end());
				test.insert(test.end(), right_bools.begin() + left_bools.size(), right_bools.end());
				for (bool test_piece : test) {
					std::cout << test_piece << " ";
				}
				++b_count;
				std::cout << std::endl;
				bool workable = true;
				for (std::vector<int> row : bulbs) {
					bool all_off_flag = true;
					for (int bulb : row) {
						bool light_status = test[abs(bulb) - 1];
						if (bulb < 0)
							light_status = !light_status;
						if (light_status == true) {
							all_off_flag = false;
							break;
						}
					}
					if (all_off_flag) {
						workable = false;
						break;
					}
				}
				if (workable)
					filtered_possible_answer.push_back(test);
			}
		}
		std::cout << b_count << std::endl;
		std::cout << "----------" << std::endl;
		int a_count = 0;
		for (std::vector<bool> omg : filtered_possible_answer) {
			for (bool om : omg) {
				std::cout << om << " ";
			}
			++a_count;
			std::cout << std::endl;
		}
		std::cout << a_count << std::endl;
		return filtered_possible_answer;
	}
	else {
		std::vector<std::vector<bool>> possible_answer_list;
		std::cout << bottom_m << " " << middle_m << " " << top_m << std::endl;
		for (std::vector<int> row : bulbs) {
			for (int bulb : row) {
				std::cout << bulb << " ";
			}
			std::cout << std::endl;
		}
		for (int i = 0; i < (std::pow(2, top_m - bottom_m + 1)); i++) {
			std::vector<bool> possiblility = int_to_bool(i, middle_m, top_m);
			bool workable = true;
			for (std::vector<int> row : bulbs) {
				bool all_off_flag = true;
				for (int bulb : row) {
					bool light_status = possiblility[abs(bulb) - 1];
					if (bulb < 0)
						light_status = !light_status;
					if (light_status == true) {
						all_off_flag = false;
						break;
					}
				}
				if (all_off_flag) {
					workable = false;
					break;
				}
			}
			if (workable)
				possible_answer_list.push_back(possiblility);
		}
		return possible_answer_list;
	}
}

static std::vector<bool> solve(std::vector<std::vector<int>> bulbs) {
	int m = 0;
	for (std::vector<int> row : bulbs)
		for (int bulb : row)
			if (abs(bulb) > m) m = abs(bulb);
	return recurrsive(1, m, bulbs)[0];
}
