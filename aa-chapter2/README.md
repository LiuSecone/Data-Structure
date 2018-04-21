# 算法设计与分析 第2章

#### 2016211308班 2016211352号 刘思聪

---

## 合并、快速排序实验

### 实验结果

> Qs1、Qs2、递归合并三项，前者为时间，单位为ms，后者为递归深度。

|编号|长度|组号|DD|ADD|Qs1|Qs2|递归合并|非递归合并|
|---|---|---|---|---|---|---|---|---|
|1|2000|1|3036|1|0.0008/1|0.0036/2|0.8375/12|1.0094/12|
|2|2000|1|24766|12|0.0007/1|0.0056/5|0.7846/12|0.7593/12|
|3|2000|1|225188|112|0.0075/7|0.0095/7|1.005/12|1.2516/12|
|4|2000|1|910715|455|0.0509/21|0.0715/22|0.9039/12|0.9035/12|
|5|2000|1|1005288|502|0.1051/19|0.1043/18|1.1785/12|0.9477/12|
|6|5000|2|11491|2|0.002/1|0.0075/3|2.2985/14|1.9532/14|
|7|5000|2|167275|33|0.0016/1|0.0273/4|2.0495/14|1.9335/14|
|8|5000|2|1399402|279|0.002/1|0.0126/3|1.9998/14|2.1776/14|
|9|5000|2|5637831|1127|0.1817/21|0.2141/21|2.3257/14|1.8671/14|
|10|5000|2|6181618|1236|0.2564/22|0.252/24|1.9887/14|2.1018/14|
|11|10000|3|37749|3|0.0036/1|0.0118/3|3.9443/15|4.1406/15|
|12|10000|3|644699|64|0.0032/1|0.013/3|4.819/15|4.1699/15|
|13|10000|3|5906046|590|0.0213/1|0.053/11|3.855/15|4.1536/15|
|14|10000|3|22400354|2240|0.3868/24|0.2978/22|4.2616/15|3.6761/15|
|15|10000|3|25171709|2517|0.7044/31|0.5424/25|3.9253/15|3.8965/15|
|16|15000|4|116872|7|0.0047/1|0.0166/3|6.9178/15|5.5727/15|
|17|15000|4|1597883|106|0.0047/1|0.0277/6|5.9291/15|6.0283/15|
|18|15000|4|12614636|840|0.0051/1|0.0766/9|5.6854/15|5.3136/15|
|19|15000|4|50630144|3375|0.0043/1|0.337/21|5.6174/15|6.5608/15|
|20|15000|4|56788531|3785|0.8123/28|0.7771/33|5.4598/15|6.5477/15|
|21|20000|5|300896|15|0.0059/1|0.0213/3|8.0277/16|7.5856/16|
|22|20000|5|2563322|128|0.0067/1|0.0249/3|8.0099/16|7.3822/16|
|23|20000|5|22657537|1132|0.0071/1|0.1154/12|7.8961/16|7.8977/16|
|24|20000|5|90758969|4537|0.8277/27|0.3686/24|7.8981/16|7.4539/16|
|25|20000|5|100284366|5014|1.3246/32|1.3803/30|7.5018/16|7.0977/16|
|26|30000|6|642539|21|0.0091/1|0.0285/3|12.3797/16|11.9748/16|
|27|30000|6|5760660|192|0.0103/1|0.0352/3|12.5267/16|11.6235/16|
|28|30000|6|51761785|1725|0.0095/1|0.1122/13|13.4715/16|11.6334/16|
|29|30000|6|201918728|6730|1.1141/24|1.1035/27|11.5323/16|10.9938/16|
|30|30000|6|223217104|7440|1.6482/29|1.8979/29|11.7926/16|11.5477/16|

### 运行结果截图

![运行结果截图](./1.png)

### 结果总结

* 当问题规模相同，序列内容不变的时候，一般来说效率`Qs`>`Qs2`>`非递归归并`>`递归归并`。虽然两种排序方式都为*O(nlog(n))*，但是显然快速排序的常数小于归并排序。虽然在当前的数据下`Qs1`的效率大于`Qs2`，但是`Qs1`在逆序等情况下会发生退化，效率显著降低。

* 当问题规模不变的情况下，随着数组的混乱程度增加，问题求解时间普遍并无太大变化。`Qs1`因为每次总是选择第一个作为轴心，因此当混乱程序较小的时候，速度相对会快一些。

* 当问题规模不同的情况下，数组混乱都取平均值。因为问题求解的复杂度为*O(nlog(n))*，可以看到时间会显著增加。

### 代码

```c
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
    for (auto length_list_iter = length_list.begin(); length_list_iter != length_list.end(); ++length_list_iter) {
        int length = *length_list_iter;
        for (int times = 0; times < REPEAT_TIMES; ++times) {
            auto unsort_number_backup = creat_unsort_number(length, times);
            auto unsort_number = unsort_number_backup;
            int disorder_degree = get_dd(unsort_number);
            int average_disorder_degree = static_cast<int>(disorder_degree / length);

            //quick sort 1
            unsort_number = unsort_number_backup;
            auto start = std::chrono::system_clock::now();
            int depth = quick_sort_1(unsort_number, 0, unsort_number.size() - 1);
            auto end = std::chrono::system_clock::now();
            int depth1 = depth;
            double time1 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));

            //quick sort 2
            unsort_number = unsort_number_backup;
            start = std::chrono::system_clock::now();
            depth = quick_sort_2(unsort_number, 0, unsort_number.size() - 1);
            end = std::chrono::system_clock::now();
            int depth2 = depth;
            double time2 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));

            //merge sort recursion
            unsort_number = unsort_number_backup;
            start = std::chrono::system_clock::now();
            depth = merge_sort_recursion(unsort_number, 0, unsort_number.size() - 1);
            end = std::chrono::system_clock::now();
            int depth3 = depth;
            double time3 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));

            //merge sort non-recursion
            unsort_number = unsort_number_backup;
            start = std::chrono::system_clock::now();
            merge_sort_nonrecursion(unsort_number);
            end = std::chrono::system_clock::now();
            int depth4 = depth;
            double time4 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * std::pow(10, -6));

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
    }
    system("pause");
    return 0;
}
```

---

## 线性时间选择

### 实验结果

> 表中的`一分为二`和`一分为三`分别对应PPT中相应的算法。`分为三块`是对一分为三进行改进，取两个中枢，将区间分为三块的做法。

|查找编号|ID|k_dist|一分为二|一分为三|分为三块|
|---|---|---|---|---|---|
|1|568030|103.075|5|4|7|
|5|567883|126.096|9|7|6|
|50|568074|208.475|15|14|11|
|1033|568313|2735.8|13|8|4|

### 运行结果截图

> 每一组从上往下依次是：`一分为二`、`一分为三`、`分为三块`。

![运行结果截图](./2.png)

### 结果总结

* 在这个数据中，每次划分区间总是选择第一个（或者第一个与第二个）可以看出`一分为二`，`一分为三``，`分为三块`的递归深度明显依次减小。因为划分的块数更多有利于将子问题更加细化。
* `一分为三`，划分的第二个区间总是只有一个。而取两个中枢，将区间`分为三块`的做法，可以将划分区间长度更加相近，从而减小了递归的深度。

### 代码

```c++
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
```

---

## 平面最近点对

### 实验结果

> 点对编号为两串数字，表示两个基站的`ENodeBID`编号。

|第i近点对|点对编号|距离|
|---|---|---|
|1|568471 568849|0|
|2|567389 566803|5.75234|

### 运行结果截图

![运行结果截图](./3.png)

### 结果总结

* 在这个问题中，使用分治策略可以十分明显的提高问题解决的速度。当问题规模更大时，这个速度的差距将会变得更加明显。

### 代码

``` c++
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
```