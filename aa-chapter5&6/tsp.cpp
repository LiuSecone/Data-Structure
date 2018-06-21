#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <queue>
#include <functional>

#define INF 0x3f3f3f3f

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

void dfs(const std::vector<std::vector<double>> &data, const int &start_point, const int &cur_point, std::vector<int> &cur_path, const double &cur_dist, std::vector<int> &path, double &dist, int &scaned_point) {
    ++scaned_point;
    if (cur_dist >= dist) {
        return;
    }
    if (cur_path.size() == data.size() && cur_dist + data[start_point][cur_point] < dist) {
        cur_path.push_back(start_point);
        path = cur_path;
        dist = cur_dist + data[start_point][cur_point];
        cur_path.pop_back();
        return;
    }
    std::vector<bool> visited(data.size(), false);
    for (auto i : cur_path) {
        visited[i] = true;
    }
    for (auto iter = data[cur_point].begin(); iter != data[cur_point].end(); ++iter) {
        const auto next_point = static_cast<int>(iter - data[cur_point].begin());
        if (*iter != INF && !visited[next_point]) {
            cur_path.push_back(next_point);
            dfs(data, start_point, next_point, cur_path, cur_dist + *iter, path, dist, scaned_point);
            cur_path.pop_back();
        }
    }
}

struct point {
    int cur_point;
    double dist;
    double lower_bound;
    double rest_cost;
    std::vector<int> path;
    bool operator > (const point &exp) const {
        return this->lower_bound > exp.lower_bound;
    }
};

void branch(const std::vector<std::vector<double>> &data, const int &start_point, std::vector<int> &path, double &dist, int &scaned_point) {
    std::vector<double> bound(data.size(), INF);
    double bound_sum = 0;
    for (auto j = data.begin(), end_j = data.end(); j != end_j; ++j) {
        double min = INF;
        for(auto iter = j->begin(), end_iter = j->end(); iter != end_iter; ++iter) {
            if (*iter < min) {
                min = *iter;
            }
        }
        bound[j - data.begin()] = min;
        bound_sum += min;
    }
    std::priority_queue<struct point, std::vector<point>, std::greater<point>> prio_q;
    path.push_back(start_point);
    prio_q.push(point{ start_point, 0, bound_sum, bound_sum, path });
    while (!prio_q.empty()) {
        ++scaned_point;
        auto cur = prio_q.top();
        prio_q.pop();
        if (cur.path.size() == data.size()) {
            if (cur.dist + data[cur.cur_point][start_point] < dist) {
                dist = cur.dist + data[cur.cur_point][start_point];
                path = cur.path;
                path.push_back(start_point);
            }
        }
        else {
            if (cur.dist < dist) {
                std::vector<bool> visited(data.size(), false);
                for (auto i : cur.path) {
                    visited[i] = true;
                }
                for (auto iter = data[cur.cur_point].begin(), end_iter = data[cur.cur_point].end(); iter != end_iter; ++iter) {
                    const auto next_point = static_cast<int>(iter - data[cur.cur_point].begin());
                    const auto lower_bound = cur.dist + *iter + cur.rest_cost - bound[cur.cur_point];
                    if (*iter != INF && !visited[next_point] && lower_bound < dist) {
                        cur.path.push_back(next_point);
                        prio_q.push(point{ next_point, cur.dist + *iter, lower_bound, cur.rest_cost - bound[cur.cur_point], cur.path });
                        cur.path.pop_back();
                    }
                }
            }
        }
    }
    return;
}

void output(const std::string &name, const std::vector<int> &path, const double &dist, const int &scaned_point, const double seconds) {
    std::cout << name << ": " << std::endl << "Path:";
    for (auto iter = path.begin(); iter != path.end(); ++iter) {
        std::cout << *iter;
        if (iter != path.end() - 1) {
            std::cout << "->";
        }
    }
    std::cout << std::endl;
    std::cout << "Dist: " << dist << "  L: " << scaned_point << "  T: ";
    std::cout << seconds * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "s" << std::endl;
}

void tsp(const std::vector<std::vector<double>> &data, const int start_point) {
    std::cout << "Size: " << data.size() << std::endl;
    auto scaned_point = 0;
    double dist = INF;
    std::vector<int> path;
    path.push_back(start_point);
    auto cur_path = path;
    auto start = std::chrono::system_clock::now();
    dfs(data, start_point, start_point, cur_path, 0, path, dist, scaned_point);
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    output("DFS", path, dist, scaned_point, static_cast<double>(duration.count()));

    scaned_point = 0;
    path.clear();
    dist = INF;
    start = std::chrono::system_clock::now();
    branch(data, start_point, path, dist, scaned_point);
    end = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    output("Branch and Bound", path, dist, scaned_point, static_cast<double>(duration.count()));
    std::cout << std::endl;
    return;
}

int main() {
    const auto data15 = get_data(15);
    const auto data20 = get_data(20);
    tsp(data15, 12);
    tsp(data20, 17);
    system("pause");
    return 0;
}