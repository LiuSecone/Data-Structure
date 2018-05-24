#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

struct data {
    int weight;
    int value;
};

void bag(const std::string &file_name) {
    std::ifstream input(file_name);
    if (!input) {
        std::cout << "Can not open file: " << file_name << std::endl;
        return;
    }
    std::cout << file_name << std::endl;
    int total_weight;
    input >> total_weight;
    int temp;
    std::vector<int> temp_vec;
    while (input >> temp) {
        temp_vec.push_back(temp);
    }
    input.close();
    std::vector<struct data> things(temp_vec.size() >> 1);
    for (unsigned i = 0; i < temp_vec.size() >> 1; ++i) {
        things[i].weight = temp_vec[i];
        things[i].value = temp_vec[i + (temp_vec.size() >> 1)];
    }
    std::vector<std::vector<int>> dp_map(things.size(), std::vector<int>(total_weight + 1, 0));
    for (int i = 0; i < static_cast<int>(things.size()); ++i) {
        for (int j = 1; j <= total_weight; ++j) {
            if (i == 0) {
                if (things[i].weight <= j) {
                    dp_map[i][j] = things[i].value;
                }
            }
            else {
                if (things[i].weight <= j) {
                    dp_map[i][j] = std::max(dp_map[i - 1][j], dp_map[i - 1][j - things[i].weight] + things[i].value);
                }
                else {
                    dp_map[i][j] = dp_map[i - 1][j];
                }
            }
        }
    }
    std::vector<int> ans_stack;
    int i = things.size() - 1;
    int j = total_weight;
    while (i != -1 && j != 0) {
        if (i == 0) {
            if (things[i].weight <= j) {
                ans_stack.push_back(i);
                j -= things[i].weight;
                --i;
            }
        }
        else {
            if (things[i].weight <= j) {
                if (dp_map[i - 1][j] < dp_map[i - 1][j - things[i].weight] + things[i].value) {
                    ans_stack.push_back(i);
                    j -= things[i].weight;
                    --i;
                }
                else {
                    --i;
                }
            }
            else {
                --i;
            }
        }
    }
    int sum_weight = 0;
    while (!ans_stack.empty()) {
        sum_weight += things[ans_stack.back()].weight;
        std::cout << ans_stack.back() << ' ';
        ans_stack.pop_back();
    }
    std::cout << std::endl << "Weigth: " << sum_weight << std::endl;
    std::cout << "Value: " << dp_map[things.size() - 1][total_weight] << std::endl;
    return;
}
int main() {
    bag("1.txt");
    bag("2.txt");
    system("pause");
    return 0;
}