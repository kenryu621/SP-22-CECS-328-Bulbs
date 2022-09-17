#include "StudentSolver.h"

std::vector<bool> int_to_bool(int num, int top_m, int bottom_m) {
	std::vector<bool> possible_answer(top_m - bottom_m + 1, false);
	while (num > 0) {
		possible_answer[top_m - bottom_m++] = num % 2;
		num = num / 2;
	}
	return possible_answer;
}

bool workable_possibility(std::vector<std::vector<int>> bulbs, std::vector<bool> wire_set, int bottom_m) {
	bool workable = true;
	for (std::vector<int> row : bulbs) {
		bool all_off_flag = true;
		for (int bulb : row) {
			bool light_status = wire_set[abs(bulb) - bottom_m];
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
	return workable;
}

std::vector<std::vector<bool>> split_m(int bottom_m, int top_m, std::vector<std::vector<int>> bulbs) {
	int middle_m = top_m - ((top_m - bottom_m + 1) / 2);
	std::vector<std::vector<bool>> filtered_possible_answer;
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
				if (wrong_flag || (left_flag && right_flag))
					break;
			}
			if (wrong_flag || (left_flag && right_flag))
				continue;
			else if (!wrong_flag && left_flag)
				left_m_bulbs.push_back(row);
			else if (!wrong_flag && right_flag)
				right_m_bulbs.push_back(row);
		}
		std::vector<std::vector<bool>> left_possible_bools = split_m(bottom_m, middle_m, left_m_bulbs);
		std::vector<std::vector<bool>> right_possible_bools = split_m(middle_m + 1, top_m, right_m_bulbs);
		std::vector<bool> test;
		for (std::vector<bool> left_bools : left_possible_bools) {
			for (std::vector<bool> right_bools : right_possible_bools) {
				test.clear();
				test.insert(test.begin(), left_bools.begin(), left_bools.end());
				test.insert(test.end(), right_bools.begin(), right_bools.end());
				if (workable_possibility(bulbs, test, bottom_m))
					filtered_possible_answer.push_back(test);
			}
		}
	}
	else {
		for (int i = 0; i < (std::pow(2, top_m - bottom_m + 1)); i++) {
			std::vector<bool> possiblility = int_to_bool(i, top_m, bottom_m);
			if (workable_possibility(bulbs, possiblility, bottom_m))
				filtered_possible_answer.push_back(possiblility);
		}
	}
	return filtered_possible_answer;
}

std::vector<bool> StudentSolver::solve(std::vector<std::vector<int>> bulbs) {
	int m = 0;
	for (std::vector<int> row : bulbs)
		for (int bulb : row)
			if (abs(bulb) > m) m = abs(bulb);
	return split_m(1, m, bulbs)[0];
}
