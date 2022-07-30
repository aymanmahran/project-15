#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <bits/stdc++.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Utils {
    public:
        static json readJson(string path);
        static void writeJson(string path, json data);
};

json Utils::readJson(string path) {
    ifstream file(path);
    if(!file.is_open()) return NULL;
    json data = json::parse(file);
    return data;
}

void Utils::writeJson(string path, json data) {

    ofstream output(path);
    output << setw(4) << data << endl;
}

#endif
