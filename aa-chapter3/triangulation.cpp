#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define PI 3.14159265
#define R 6.371229*1e6

struct node {
    int id;
    double longitude, latitude, k_dist;
    bool operator< (const node &exp) const {
        if (this->longitude != exp.longitude) {
            return this->longitude < exp.longitude;
        }
        else {
            return this->latitude < exp.latitude;
        }
    }
};

void get_data(std::vector<struct node> &data, const std::string &file_name) {
    std::ifstream input(file_name);
    if (!input) {
        std::cout << "Can not open file: " << file_name << std::endl;
        return;
    }
    struct node temp;
    while (input >> temp.id >> temp.longitude >> temp.latitude >> temp.k_dist) {
        data.push_back(temp);
    }
    input.close();
    return;
}

double get_rad(double d) {
    return (d * PI / 180);
}

double get_dist(const struct node &d1, const struct node &d2) {
    double lat1 = d1.latitude;
    double lat2 = d2.latitude;
    double lon1 = d1.longitude;
    double lon2 = d2.longitude;
    double rad_lat_1 = get_rad(lat1);
    double rad_lat_2 = get_rad(lat2);
    double a = rad_lat_1 - rad_lat_2;
    double b = get_rad(lon1) - get_rad(lon2);
    double dist = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(rad_lat_1)*cos(rad_lat_2)*pow(sin(b / 2), 2)));
    dist = dist * R;
    return dist;
}

double get_c(const struct node &a, const struct node &b, const struct node &c) {
    return get_dist(a, b) + get_dist(b, c) + get_dist(a, c);
}

void trace_back(const std::vector<std::vector<int>> &s, int i, int j) {
    if (j - i >= 1) {
        std::cout << i - 1 << ' ' << s[i][j] << ' ' << j << std::endl;
        trace_back(s, i, s[i][j]);
        trace_back(s, s[i][j] + 1, j);
    }
    return;
}

void triangulation(const std::vector<struct node> &data) {
    std::vector<std::vector<double>> t(data.size(), std::vector<double>(data.size(), 0));
    std::vector<std::vector<int>> s(data.size(), std::vector<int>(data.size(), 0));
    for (unsigned slot = 1; slot < data.size(); ++slot) {
        for (unsigned i = 1; i + slot < data.size(); ++i) {
            auto j = i + slot;
            t[i][j] = t[i + 1][j] + get_c(data[i - 1], data[i], data[j]);
            s[i][j] = i;
            for (unsigned k = i + 1; k < j; ++k) {
                auto temp_sum_c = get_c(data[i - 1], data[k], data[j]) + t[i][k] + t[k + 1][j];
                if (t[i][j] > temp_sum_c) {
                    t[i][j] = temp_sum_c;
                    s[i][j] = k;
                }
            }
        }
    }
    std::cout << t[1][data.size() - 1] << std::endl;
    trace_back(s, 1, data.size() - 1);
    return;
}

int main() {
    std::vector<struct node> data1, data2;
    get_data(data1, "21.txt");
    get_data(data2, "29.txt");
    triangulation(data1);
    triangulation(data2);
    system("pause");
    return 0;
}