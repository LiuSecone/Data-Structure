#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

#define PI 3.14159265
#define R 6.371229*1e6

double get_dist(const struct pair &);

struct data {
    int id;
    double longitude, latitude, k_dist;
    bool operator< (const data &exp) const {
        if (this->longitude != exp.longitude) {
            return this->longitude < exp.longitude;
        }
        else {
            return this->latitude < exp.latitude;
        }
    }
};

struct pair {
    struct data p1, p2;
    bool operator< (const struct pair &exp) const {
        return get_dist(*this) < get_dist(exp);
    }
    void output() {
        std::cout << p1.id << " " << p2.id << " " << get_dist(*this) << std::endl;
    }
};

double get_rad(double d) {
    return (d * PI / 180);
}

double get_dist(const struct data &d1, const struct data &d2) {
    double lat1 = d1.latitude;
    double lat2 = d2.latitude;
    double lon1 = d1.longitude;
    double lon2 = d2.longitude;
    double radLat1 = get_rad(lat1);
    double radLat2 = get_rad(lat2);
    double a = radLat1 - radLat2;
    double b = get_rad(lon1) - get_rad(lon2);
    double dist = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
    dist = dist * R;
    return dist;
}

double get_dist(const struct pair &p) {
    return get_dist(p.p1, p.p2);
}

double get_intercept(const struct data &data, double d) {
    struct data temp;
    temp.longitude = d;
    temp.latitude = data.latitude;
    return get_dist(data, temp);
}

std::vector<struct data> get_data(std::string file_name) {
    struct data temp;
    std::vector<struct data> data;
    std::ifstream input(file_name);
    if (!input) {
        std::cout << "Can not open file: " << file_name << std::endl;
    }
    int num;
    input >> num;
    for (int i = 0; i < num; ++i) {
        input >> temp.id >> temp.longitude >> temp.latitude >> temp.k_dist;
        data.push_back(temp);
    }
    std::sort(data.begin(), data.end());
    return data;
}

std::vector<struct pair> bipartite(const std::vector<struct data> &data, int l, int r) {
    if (r - l <= 2) {
        auto end = data.begin() + r + 1;
        std::vector<struct pair> ans;
        for (auto i = data.begin() + l; i != end; ++i) {
            for (auto j = i + 1; j != end; ++j) {
                struct pair pair;
                pair.p1 = *i;
                pair.p2 = *j;
                ans.push_back(pair);
            }
        }
        return ans;
    }
    int mid = (l + r) >> 1;
    auto ans_l = bipartite(data, l, mid);
    auto ans_r = bipartite(data, mid + 1, r);
    for (auto i : ans_r) {
        ans_l.push_back(i);
    }
    std::sort(ans_l.begin(), ans_l.end());
    double dist = get_dist(ans_l[0]);
    auto left = mid;
    auto right = mid;
    while (left > l && get_intercept(data[left], data[mid].longitude) < dist) {
        --left;
    }
    while (right < r && get_intercept(data[right], data[mid].longitude) < dist) {
        ++right;
    }
    auto end = data.begin() + right + 1;
    for (auto i = data.begin() + left; i != end; ++i) {
        for (auto j = i + 1; j != end; ++j) {
            struct pair temp;
            temp.p1 = *i;
            temp.p2 = *j;
            ans_l.push_back(temp);
        }
    }
    std::sort(ans_l.begin(), ans_l.end());
    auto ans = { ans_l[0], ans_l[1] };
    return ans;
}

int main() {
    std::vector<struct data> data = get_data("data.txt");
    
    std::cout << "O(nlogn) Bipartite: " << std::endl;
    auto ans = bipartite(data, 0, data.size() - 1);
    ans[0].output();
    ans[1].output();
    std::cout << std::endl;

    //check O(n^2). passed
    std::cout << "O(n^2) Brute Force: " << std::endl;
    ans.clear();
    for (auto i = data.begin(); i != data.end(); ++i) {
        for (auto j = i + 1; j != data.end(); ++j) {
            struct pair temp;
            temp.p1 = *i;
            temp.p2 = *j;
            ans.push_back(temp);
        }
    }
    std::sort(ans.begin(), ans.end());
    ans[0].output();
    ans[1].output();
    system("pause");
    return 0;
}