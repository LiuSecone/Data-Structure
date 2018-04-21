#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct data {
    int id;
    double longitude, latitude, k_dist;
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

int decrease_and_conquer(std::vector<struct data> data, int l, int r, int pos) {
    if (l == r) {
        std::cout << "ID: " << data[l].id << " K_dist: " << data[l].k_dist;
        return 1;
    }
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
    return pos <= i ? decrease_and_conquer(data, l, i, pos) + 1 : decrease_and_conquer(data, i + 1, r, pos) + 1;
}

int bipartite(std::vector<struct data> data, int l, int r, int pos) {
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
    return pos < i ? bipartite(data, l, i - 1, pos) + 1 : bipartite(data, i + 1, r, pos) +   1;
}

int trisection(std::vector<struct data> data, int l, int r, int pos) {
    if (l == r) {
        std::cout << "ID: " << data[l].id << " K_dist: " << data[l].k_dist;
        return 1;
    }
    int i = l;
    int j = r;
    auto m1 = data[l];
    auto m2 = data[l + 1];
    if (m1.k_dist > m2.k_dist) {
        std::swap(m1, m2);
    }
    std::vector<struct data> list1, list2, list3;
    for (auto iter = data.begin() + l; iter != data.begin() + r + 1; ++iter) {
        if (iter->k_dist < m1.k_dist) {
            list1.push_back(*iter);
        }
        else {
            if (iter->k_dist > m2.k_dist) {
                list3.push_back(*iter);
            }
            if (iter->k_dist > m1.k_dist && iter->k_dist < m2.k_dist) {
                list2.push_back(*iter);
            }
        }
    }
    auto iter = data.begin() + l;
    for (auto i : list1) {
        *iter = i;
        ++iter;
    }
    *iter = m1;
    auto pos_m1 = iter - data.begin();
    ++iter;
    for (auto i : list2) {
        *iter = i;
        ++iter;
    }
    *iter = m2;
    auto pos_m2 = iter - data.begin();
    ++iter;
    for (auto i : list3) {
        *iter = i;
        ++iter;
    }
    if (pos_m1 == pos) {
        std::cout << "ID: " << m1.id << " K_dist: " << m1.k_dist;
        return 1;
    }
    if (pos_m2 == pos) {
        std::cout << "ID: " << m2.id << " K_dist: " << m2.k_dist;
        return 1;
    }
    if (pos < pos_m1) {
        return trisection(data, l, pos_m1 - 1, pos) + 1;
    }
    else {
        if (pos > pos_m2) {
            return trisection(data, pos_m2 + 1, r, pos) + 1;
        }
        else {
            return trisection(data, pos_m1, pos_m2, pos) + 1;
        }
    }
}

int main() {
    std::vector<struct data> raw_data = get_data("data.txt");
    std::vector<int> selection_list = { 1, 5, 50, static_cast<int>(raw_data.size()) };
    for (auto selection_number : selection_list) {
        std::cout << selection_number << std::endl;
        auto data = raw_data;
        std::cout << " Depth: " << decrease_and_conquer(data, 0, data.size() - 1, selection_number - 1) << std::endl;
        data = raw_data;
        std::cout << " Depth: " << bipartite(data, 0, data.size() - 1, selection_number - 1) << std::endl;
        data = raw_data;
        std::cout << " Depth: " << trisection(data, 0, data.size() - 1, selection_number - 1) << std::endl;
        std::cout << std::endl;
    }
    system("pause");
    return 0;
}