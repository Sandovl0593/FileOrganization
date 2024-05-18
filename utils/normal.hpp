#include <cstring>
#include <iostream>

using namespace std;

long long parseLongLong(const string& str) {
    if (str == "NA" || str.empty()) {
        return 0;
    }
    return stoll(str);
}

double parseDouble(const string& str) {
    if (str == "NA" || str.empty()) {
        return 0.0;
    }
    return stod(str);
}