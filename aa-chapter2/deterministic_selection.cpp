#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

struct data {
    int id;
    double longitude, latitude, k_dist;
    bool operator< (const data &exp) const {
        return this->k_dist < exp.k_dist;
    }

    bool operator== (const data &exp) const {
        return this->id == exp.id;
    }

};

std::vector<struct data> get_data(std::string file_name){
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
    return data;
}

struct data select_bipartite(std::vector<struct data> data, int l, int r, int pos) {
    if (r - l <= 75) {
        std::sort(data.begin() + l, data.begin() + r + 1);
        return data[pos];
    }
    auto iter_mid = data.begin() + l;
    for (auto iter = data.begin() + l; iter + 4 < data.begin() + r + 1; iter += 5) {
        std::sort(iter, iter + 5);
        std::swap(*(iter + 2), *iter_mid);
        ++iter_mid;
    }
    //std::sort(data.begin() + l, iter_mid);
    struct data mid = select_bipartite(data, l, iter_mid - data.begin() - 1, (iter_mid - data.begin() - l) / 2 + l);
    int mid_no;
    for (auto iter = data.begin() + l; iter != data.begin() + (iter_mid - data.begin()); ++iter) {
        if (*iter == mid) {
            mid_no = iter - data.begin();
            break;
        }
    }
    std::swap(data[l], data[mid_no]);
    int i = l;
    int j = r;
    auto m = data[l];
    while (i < j) {
        while (i < j && data[j].k_dist >= m.k_dist) {
            --j;
        }
        data[i] = data[j];
        while (i < j && data[i].k_dist <= m.k_dist) {
            ++i;
        }
        data[j] = data[i];
    }
    data[i] = m;
    return pos <= i ? select_bipartite(data, l, i, pos) : select_bipartite(data, i + 1, r, pos);
}

int bipartite(std::vector<struct data> data, int l, int r, int pos) {
    if (r - l <= 75) {
        std::sort(data.begin() + l, data.begin() + r + 1);
        std::cout << "ID: " << data[pos].id << " K_dist: " << data[pos].k_dist;
        return 1;
    }
    auto iter_mid = data.begin() + l;
    for (auto iter = data.begin() + l; iter + 4 < data.begin() + r + 1; iter += 5) {
        std::sort(iter, iter + 5);
        std::swap(*(iter + 2), *iter_mid);
        ++iter_mid;
    }
    //std::sort(data.begin() + l, iter_mid);
    struct data mid = select_bipartite(data, l, iter_mid - data.begin() - 1, (iter_mid - data.begin() - l) / 2 + l);
    int mid_no;
    for (auto iter = data.begin() + l; iter != data.begin() + (iter_mid - data.begin()); ++iter) {
        if (*iter == mid) {
            mid_no = iter - data.begin();
            break;
        }
    }
    std::swap(data[l], data[mid_no]);
    int i = l;
    int j = r;
    auto m = data[l];
    while (i < j) {
        while (i < j && data[j].k_dist >= m.k_dist) {
            --j;
        }
        data[i] = data[j];
        while (i < j && data[i].k_dist <= m.k_dist) {
            ++i;
        }
        data[j] = data[i];
    }
    data[i] = m;
    return pos <= i ? bipartite(data, l, i, pos) + 1 : bipartite(data, i + 1, r, pos) + 1;
}

int trisection(std::vector<struct data> data, int l, int r, int pos) {
    if (r - l <= 75) {
        std::sort(data.begin() + l, data.begin() + r + 1);
        std::cout << "ID: " << data[pos].id << " K_dist: " << data[pos].k_dist;
        return 1;
    }
    auto iter_mid = data.begin() + l;
    for (auto iter = data.begin() + l; iter + 4 < data.begin() + r + 1; iter += 5) {
        std::sort(iter, iter + 5);
        std::swap(*(iter + 2), *iter_mid);
        ++iter_mid;
    }
    //std::sort(data.begin() + l, iter_mid);
    struct data mid = select_bipartite(data, l, iter_mid - data.begin() - 1, (iter_mid - data.begin() - l) / 2 + l);
    int mid_no;
    for (auto iter = data.begin() + l; iter != data.begin() + (iter_mid - data.begin()); ++iter) {
        if (*iter == mid) {
            mid_no = iter - data.begin();
            break;
        }
    }
    std::swap(data[l], data[mid_no]);
    int i = l;
    int j = r;
    auto m = data[l];
    while (i < j) {
        while (i < j && data[j].k_dist >= m.k_dist) {
            --j;
        }
        data[i] = data[j];
        while (i < j && data[i].k_dist <= m.k_dist) {
            ++i;
        }
        data[j] = data[i];
    }
    data[i] = m;
    if (i == pos) {
        std::cout << "ID: " << m.id << " K_dist: " << m.k_dist;
        return 1;
    }
    return pos < i ? trisection(data, l, i - 1, pos) + 1 : trisection(data, i + 1, r, pos) + 1;
}

int main() {
    std::vector<struct data> raw_data = get_data("data.txt");
    std::vector<int> selection_list = { 1, 5, 50, static_cast<int>(raw_data.size()) };
    for (auto selection_number : selection_list) {
        std::cout << selection_number << std::endl;
        auto data = raw_data;
        std::cout << " Depth: " << bipartite(data, 0, data.size() - 1, selection_number - 1) << std::endl;
        data = raw_data;
        std::cout << " Depth: " << trisection(data, 0, data.size() - 1, selection_number - 1) << std::endl;
        //data = raw_data;
        //std::cout << select_bipartite(data, 0, data.size() - 1, selection_number - 1).k_dist << std::endl;
        std::cout << std::endl;
    }
    system("pause");
    return 0;
}