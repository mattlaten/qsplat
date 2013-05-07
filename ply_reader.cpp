#include "ply_reader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

void ply_reader::read(string str, splat_model & model) {
    ifstream file;
    file.open(str.c_str());
    string line;

    int num_verts = 0;
    int num_faces = 0;

    if (file.is_open()) {
        while (line != "end_header") {
            getline(file,line);
            istringstream iss(line);
            string sub;
            iss >> sub;
            if (sub == "element") {
                iss >> sub;
                if (sub == "vertex") {
                    iss >> num_verts;
                } else {
                    iss >> num_faces;
                }
            }

        }
        cout << num_verts << " " << num_faces << endl;
        for (int i = 0; i < num_verts; ++i) {
            splat s;
            getline(file, line);
            istringstream iss(line);
            iss >> s.center.x >> s.center.y >> s.center.z;
            if (i < 10)
               cout << s.center.x << " " << s.center.y << " " << s.center.z << endl; 
            model.splats.push_back(s);
        }

        int num [num_verts];

        for (int i = 0; i < num_faces; ++i) {
            //compute normals 
            getline(file, line);
            istringstream iss(line);
            int num, u, v, w;
            iss >> num >> u >> v >> w; 
            //model.splats[u].v -
            //compute splat width
        }
        //while (file.good()) {
        //}
    }
    cout << "DONE" << endl;
    file.close();
}
