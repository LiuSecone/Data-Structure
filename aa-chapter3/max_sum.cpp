#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

void get_data(std::vector<int> &data, const std::string &file_name) {
    std::ifstream input(file_name);
    if (!input) {
        std::cout << "Can not open file: " << file_name << std::endl;
        return;
    }
    int temp;
    while (input >> temp) {
        data.push_back(temp);
    }
    input.close();
    return;
}

void max_sum(const std::vector<int> &data) {
    std::vector<int> dp_map(data.size(), 0);
    dp_map[0] = data[0];
    auto ans = 0;
    for (auto i = 1; i < static_cast<int>(dp_map.size()); ++i) {
        dp_map[i] = std::max(dp_map[i - 1] + data[i], data[i]);
        if (dp_map[ans] < dp_map[i]) {
            ans = i;
        }
    }
    std::cout << "Max Number:" << dp_map[ans] << std::endl;
    int range_l, range_r;
    range_r = ans;
    while (dp_map[ans] >= 0) {
        --ans;
    }
    ++ans;
    range_l = ans;
    std::cout << "From: " << range_l << " to " << range_r << std::endl;
    std::cout << std::endl;
    return;
}

void brute(const std::vector<int> &data) {
    int max = data[0];
    int l = 0, r = 0;
    for (auto i = data.begin(); i != data.end(); ++i) {
        for (auto j = i; j != data.end(); ++j) {
            int sum = 0;
            for (auto k = i; k <= j; ++k) {
                sum += *k;
            }
            if (sum > max) {
                max = sum;
                l = i - data.begin();
                r = j - data.begin();
            }
        }
    }
    std::cout << "Brute Force: " << max << ' ' << l << ' ' << r << std::endl;
    std::cout << std::endl;
    return;
}

int main() {
    std::vector<int> data1, data2;
    get_data(data1, "max_sum1.txt");
    get_data(data2, "max_sum2.txt");
    max_sum(data1);
    max_sum(data2);
    brute(data1);
    brute(data2);
    system("pause");
    return 0;
}