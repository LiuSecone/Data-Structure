#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#define REPEAT_TIMES 5

std::vector<int> creat_unsort_number(int length, int chaos_degree) {
    std::uniform_int_distribution<unsigned> u1(0, 30000);
    std::default_random_engine e;
    std::vector<int> unsort_number;
    for (int i = 0; i < length; ++i) {
        unsort_number.push_back(u1(e));
    }
    std:sort(unsort_number.begin(), unsort_number.end());
    std::uniform_int_distribution<unsigned> u(0, length - 1);
    int switch_times = static_cast<int>(length * pow(10, chaos_degree - 3));
    for (int i = 0; i < switch_times; ++i) {
        int swap1 = u(e);
        int swap2 = u(e);
        //std::cout << swap1 << ' ' << swap2 << std::endl;
        auto temp = unsort_number[swap1];
        unsort_number[swap1] = unsort_number[swap2];
        unsort_number[swap2] = temp;
    }
    return unsort_number;
}

void print_arr(const std::vector<int> &arr) {
    for (auto i : arr) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

int bipartite(std::vector<int> &unsort_number, int l, int r) {
    if (l == r) return 0;
    int mid = (l + r) >> 1;
    int dd = bipartite(unsort_number, l, mid) + bipartite(unsort_number, mid + 1, r);
    std::vector<int> tempvec1, tempvec2;
    for (auto i = l; i <= mid; ++i) {
        tempvec1.push_back(unsort_number[i]);
    }
    for (auto i = mid + 1; i <= r; ++i) {
        tempvec2.push_back(unsort_number[i]);
    }
    for (auto i = r; i >= l && tempvec1.size() && tempvec2.size(); --i) {
        if (tempvec1.back() > tempvec2.back()) {
            dd += static_cast<int>(tempvec2.size());
            unsort_number[i] = tempvec1.back();
            tempvec1.pop_back();
        }
        else {
            unsort_number[i] = tempvec2.back();
            tempvec2.pop_back();
        }
    }
    int i = l;
    for (auto &iter : tempvec1) {
        unsort_number[i] = iter;
        ++i;
    }
    for (auto &iter : tempvec2) {
        unsort_number[i] = iter;
        ++i;
    }
    return dd;
}

int get_dd(std::vector<int> &unsort_number) {
    int dd = 0;
    dd = bipartite(unsort_number, 0, unsort_number.size() - 1);
    return dd;
}

int quick_sort_1(std::vector<int> &arr, int l, int r) {
    if (l >= r) {
        return 1;
    }
    int i = l;
    int j = r;
    int mid = arr[l];
    bool flag = true;
    while (i < j) {
        while (i < j && arr[j] >= mid) {
            --j;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] <= mid) {
            ++i;
        }
        arr[j] = arr[i];
        if (i < j) {
            flag = false;
        }
    }
    arr[i] = mid;
    if (flag) {
        return 1;
    }
    int depth_l = quick_sort_1(arr, l, i - 1);
    int depth_r = quick_sort_1(arr, i + 1, r);
    return depth_l > depth_r ? depth_l + 1 : depth_r + 1;
}

int quick_sort_2(std::vector<int> &arr, int l, int r) {
    if (l >= r) {
        return 1;
    }
    int i = l;
    int j = r;
    std::uniform_int_distribution<unsigned> u(l, r);
    std::default_random_engine e;
    std::swap(arr[u(e)], arr[l]);
    int mid = arr[l];
    while (i < j) {
        while (i < j && arr[j] >= mid) {
            --j;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] <= mid) {
            ++i;
        }
        arr[j] = arr[i];
    }
    arr[i] = mid;
    int depth_l = quick_sort_1(arr, l, i - 1);
    int depth_r = quick_sort_1(arr, i + 1, r);
    return depth_l > depth_r ? depth_l + 1 : depth_r + 1;
}

void merge(std::vector<int> &arr, int l, int mid, int r) {
    std::vector<int> buffer;
    auto i_end = arr.begin() + mid + 1;
    auto j_end = arr.begin() + r + 1;
    auto i = arr.begin() + l;
    auto j = arr.begin() + mid + 1;
    while (i != i_end && j != j_end) {
        if (*i < *j) {
            buffer.push_back(*i);
            ++i;
        }
        else {
            buffer.push_back(*j);
            ++j;
        }
    }
    while (i != i_end) {
        buffer.push_back(*i);
        ++i;
    }
    while (j != j_end) {
        buffer.push_back(*j);
        ++j;
    }
    int k = l;
    for (auto buff : buffer) {
        arr[l] = buff;
        ++l;
    }
    return;
}

int merge_sort_recursion(std::vector<int> &arr, int l, int r) {
    if (l == r) {
        return 1;
    }
    int mid = (l + r) >> 1;
    int depth_l = merge_sort_recursion(arr, l, mid);
    int depth_r = merge_sort_recursion(arr, mid + 1, r);
    merge(arr, l, mid, r);
    return depth_l > depth_r ? depth_l + 1 : depth_r + 1;
}

void merge_sort_nonrecursion(std::vector<int> &arr) {
    int step = 1;
    int length = arr.size();
    while (step < length) {
        for (int i = 0; i < length - step; i += step * 2) {
            merge(arr, i, i + step - 1, length < i + 2 * step? length - 1 : i + 2 * step - 1);
        }
        step = step << 1;
    }
}

int main() {
    std::vector<int> length_list = { 2000, 5000, 10000, 15000, 20000, 30000 };
    std::vector<std::vector<double>> result;
    for (auto length_list_iter = length_list.begin(); length_list_iter != length_list.end(); ++length_list_iter) {
        int length = *length_list_iter;
        std::vector<double> n_result(8);
        n_result[0] = length;
        n_result[1] = length_list_iter - length_list.begin() + 1;
        for (int times = 0; times < REPEAT_TIMES; ++times) {
            auto unsort_number_backup = creat_unsort_number(length, times);
            auto unsort_number = unsort_number_backup;
            int disorder_degree = get_dd(unsort_number);
            int average_disorder_degree = static_cast<int>(disorder_degree / length);
            n_result[2] += disorder_degree;
            n_result[3] += average_disorder_degree;

            //quick sort 1
            unsort_number = unsort_number_backup;
            auto start = std::chrono::system_clock::now();
            int depth = quick_sort_1(unsort_number, 0, unsort_number.size() - 1);
            auto end = std::chrono::system_clock::now();
            int depth1 = depth;
            double time1 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));
            n_result[4] += time1;

            //quick sort 2
            unsort_number = unsort_number_backup;
            start = std::chrono::system_clock::now();
            depth = quick_sort_2(unsort_number, 0, unsort_number.size() - 1);
            end = std::chrono::system_clock::now();
            int depth2 = depth;
            double time2 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));
            n_result[5] += time2;

            //merge sort recursion
            unsort_number = unsort_number_backup;
            start = std::chrono::system_clock::now();
            depth = merge_sort_recursion(unsort_number, 0, unsort_number.size() - 1);
            end = std::chrono::system_clock::now();
            int depth3 = depth;
            double time3 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));
            n_result[6] += time3;

            //merge sort non-recursion
            unsort_number = unsort_number_backup;
            start = std::chrono::system_clock::now();
            merge_sort_nonrecursion(unsort_number);
            end = std::chrono::system_clock::now();
            int depth4 = depth;
            double time4 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));
            n_result[7] += time4;

            std::cout << "|"
                << (length_list_iter - length_list.begin()) * REPEAT_TIMES + times + 1 << "|"
                << length << "|"
                << length_list_iter - length_list.begin() + 1 << "|"
                << disorder_degree << "|"
                << average_disorder_degree << "|"
                << time1 << "/" << depth1 << "|"
                << time2 << "/" << depth2 << "|"
                << time3 << "/" << depth3 << "|"
                << time4 << "/" << depth4 << "|";
            std::cout << std::endl;
        }
        for (auto iter = n_result.begin() + 3; iter != n_result.end(); ++iter) {
            *iter /= REPEAT_TIMES;
        }
        result.push_back(n_result);
    }
    std::cout << std::endl;
    for (auto j : result) {
        for (auto i : j) {
            std::cout << "|" << i;
        }
        std::cout << "|" << std::endl;
    }
    system("pause");
    return 0;
}