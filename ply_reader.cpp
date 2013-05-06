#include "ply_reader.h"
#include <iostream>
#include <fstream>

using namespace std;

ply_model ply_reader::read(string str) {
    ifstream file;
    file.open(str.c_str());
    string line;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
        }
    }
    cout << "DONE" << endl;
    file.close();
    return ply_model();
}
