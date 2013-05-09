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
            if (i == 0) {
                model.min_val.set(s.center.x, s.center.y, s.center.z);
                model.max_val.set(s.center.x, s.center.y, s.center.z);
            }

            model.min_val.min_set(s.center.x, s.center.y, s.center.z);
            model.max_val.max_set(s.center.x, s.center.y, s.center.z);

            model.splats.push_back(s);
        }

        //int num [num_verts];

        for (int i = 0; i < num_faces; ++i) {
            //compute normals 
            getline(file, line);
            istringstream iss(line);
            int temp, u, v, w;
            iss >> temp >> u >> v >> w; 
            vertex uv = model.splats[u].center - model.splats[v].center;
            vertex uw = model.splats[u].center - model.splats[w].center;
            vertex vw = model.splats[v].center - model.splats[w].center; 
            vertex normal = (uv).cross(uw);
            model.splats[u].normal += normal;
            //++num[u];
            model.splats[v].normal += normal;
            //++num[v];
            model.splats[w].normal += normal;
            //++num[w];

            //compute splat width
            float distuv = uv.mag();
            float distuw = uw.mag();
            float distvw = vw.mag();

            model.splats[u].size = max(max(model.splats[u].size, distuv), distuw);
            model.splats[v].size = max(max(model.splats[v].size, distuv), distvw);
            model.splats[w].size = max(max(model.splats[w].size, distvw), distuw);
        }

        for (int i = 0; i < num_verts; ++i) {
            model.splats[i].size /= 2;
            //model.splats[i].normal /= num[i];
            //cout << model.splats[i].normal.x << " " << model.splats[i].normal.y << " " << model.splats[i].normal.z << endl;
            //cout << model.splats[i].normal.mag() << endl;
            model.splats[i].normal /= model.splats[i].normal.mag();
            //cout << model.splats[i].normal.x << " " << model.splats[i].normal.y << " " << model.splats[i].normal.z << endl;
        }
    }
    cout << "DONE" << endl;
    file.close();
}
