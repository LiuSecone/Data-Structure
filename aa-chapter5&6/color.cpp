#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <chrono>
#include <mutex>

#define INF 0x3f3f3f3f

int scaned_point = 0;

std::vector<std::vector<double>> get_data(const int num) {
    std::vector<std::vector<double>> data(num, std::vector<double>(num, -1));
    const auto file_name = std::to_string(num) + ".txt";
    std::ifstream input(file_name);
    if (!input) {
        std::cout << "Can not open file: " << file_name << std::endl;
        return data;
    }
    for (auto i = 0; i < num; ++i) {
        for (auto j = 0; j < num; ++j) {
            input >> data[i][j];
            if (data[i][j] == -1) {
                data[i][j] = INF;
            }
        }
    }
    return data;
}

bool dfs(const std::vector<std::vector<double>> &data, const int cur_point, std::vector<int> &point_color) {
    ++scaned_point;
    if (cur_point == data.size()) {
        return true;
    }
    std::set<int> around_color;
    for (auto iter = data[cur_point].begin(); iter != data[cur_point].end(); ++iter) {
        if (*iter != INF) {
            around_color.insert(point_color[iter - data[cur_point].begin()]);
        }
    }
    for (auto cur_color = 1; cur_color <= static_cast<int>(data.size()); ++cur_color) {
        if (around_color.count(cur_color) == 0) {
            point_color[cur_point] = cur_color;
            if (dfs(data, cur_point + 1, point_color) && point_color[data.size() - 1] != 0) {
                return true;
            }
        }
    }
    point_color[cur_point] = 0;
    return false;

}

void color(const std::vector<std::vector<double>> &data) {
    scaned_point = 0;
    std::vector<int> point_color(data.size(), 0);
    const auto start = std::chrono::system_clock::now();
    dfs(data, 0, point_color);
    const auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::set<int> all_color;
    for (auto iter = point_color.begin(); iter != point_color.end(); ++iter) {
        all_color.insert(*iter);
    }
    std::cout << "Size: " << data.size() << "  m: " << all_color.size() << "  L: " << scaned_point << "  T: ";
    std::cout << static_cast<double>(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den << "s" << std::endl;
    for (auto i : point_color) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;
    return;
}

int main() {
    const auto data22 = get_data(22);
    const auto data42 = get_data(42);
    color(data22);
    color(data42);
    system("pause");
    return 0;
}