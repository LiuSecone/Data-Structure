#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define LENGTH 2000

void get_string(std::string &a, std::string &b, std::string &c, std::string &d) {
    std::ifstream input("lcs.txt");
    if (!input) {
        std::cout << "Can not open file." << std::endl;
        return;
    }
    std::string temp;
    input >> temp;
    input >> a;
    input >> temp;
    input >> b;
    input >> temp;
    input >> c;
    input >> temp;
    input >> d;
    input.close();
    return;
}

void lcs(const std::string &str1, const std::string &str2) {
    std::vector<std::vector<int>> dp_map(LENGTH, std::vector<int>(LENGTH, 0));
    for (unsigned int i = 1; i <= str1.length(); ++i) {
        for (unsigned int j = 1; j <= str2.length(); ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp_map[i][j] = dp_map[i - 1][j - 1] + 1;
            }
            else {
                if (dp_map[i][j - 1] > dp_map[i - 1][j]) {
                    dp_map[i][j] = dp_map[i][j - 1];
                }
                else {
                    dp_map[i][j] = dp_map[i - 1][j];
                }
            }
        }
    }
    std::cout << dp_map[str1.length()][str2.length()] << std::endl;
    std::string ans;
    auto i = str1.length();
    auto j = str2.length();
    while (i != 0 && j != 0) {
        if (str1[i - 1] == str2[j - 1]) {
            ans = str1[i - 1] + ans;
            --i;
            --j;
        }
        else {
            if (dp_map[i][j - 1] > dp_map[i - 1][j]) {
                --j;
            }
            else {
                --i;
            }
        }
    }
    std::cout << ans << std::endl;
    return;
}

int main() {
    std::string a, b, c, d;
    get_string(a, b, c, d);
    lcs(a, b);
    lcs(c, d);
    lcs(a, d);
    lcs(c, b);
    system("pause");
    return 0;
}