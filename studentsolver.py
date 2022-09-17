# 有可能一行三个灯都是在false list里面 这样永远都不能sort掉 必须选一个灯来永不可进false list
import random

def solve(bulbs):
    print(bulbs)
    sorted, false_list,cant_be_false, m = False, [],[], 0
    while(sorted is not True):
        temp_light_off_rows, sorted = [], True
        for row in bulbs:
            light_on = False
            for bulb in row:
                num = bulb if abs(bulb) not in false_list else -bulb
                if num > 0:
                    light_on = True
                if abs(bulb) > m:
                    m = abs(bulb)
            if light_on is False:
                temp_light_off_rows.append(row)
                sorted = False
        if sorted is False:
            find_dup_list = []
            for row in temp_light_off_rows:
                for bulb in row:
                    if abs(bulb) not in find_dup_list:
                        find_dup_list.append(abs(bulb))
                    else:
                        if abs(bulb) not in cant_be_false:
                            false_list.append(abs(bulb))
                            print(false_list)
            for row in temp_light_off_rows:
                fixed = False
                for bulb in row:
                    num = bulb if abs(bulb) not in false_list else -(bulb)
                    if num > 0:
                        fixed = True
                        break
                if fixed is False:
                    three_bulbs_in_false_list = True
                    for bulb in row:
                        if abs(bulb) not in false_list and abs(bulb) not in cant_be_false:
                            false_list.append(abs(bulb))
                            print(false_list)
                            three_bulbs_in_false_list = False
                            break
                    if three_bulbs_in_false_list is True:
                        for bulb in row:
                            if abs(bulb) in false_list:
                                false_list.remove(abs(bulb))
                                cant_be_false.append(abs(bulb))
                                break
                        # false_list.remove(abs(bulb))
                        # cant_be_false.append(abs(bulb))
                        print(false_list)
                        temp_value = row[0]
                        row[0] = row[1]
                        row[1] = row[2]
                        row[2] = temp_value
                        # false_list.pop(0)
                        # print(false_list)
    arr_of_bool = [True] * m
    for i in range(0, m, 1):
        if (i + 1) in false_list:
            arr_of_bool[i] = False
    return arr_of_bool


# test = [[-4, -4, -1], [13, 9, -14], [4, -7, -2], [-2, 6, 3], [-6, -8, 11],
#         [-4, -3, -6], [7, 11, -10], [4, -7, 6], [5, 6, 4], [10, 14, -9]]
# print(solve(test))
# test2 = [[-1, -2, -3], [1, -2, -3], [1, 2, -3], [1, 2, 3]]
# print(solve(test2))
# test3 = []
# for i in range(1000):
#     temp_test_to_add = []
#     for j in range(3):
#         num = random.randrange(1, 1000, 1)
#         if random.randrange(1, 1000, 1) % 2 == 1:
#             num = -num
#         temp_test_to_add.append(num)
#     test3.append(temp_test_to_add)
# print(solve(test3))
