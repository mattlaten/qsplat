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

    ofstream outfile;
    outfile.open((str + ".qs").c_str());

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
            model.splats[v].normal += normal;
            model.splats[w].normal += normal;

            //compute splat width
            float distuv = uv.mag();
            float distuw = uw.mag();
            float distvw = vw.mag();

            model.splats[u].size = max(max(model.splats[u].size, distuv), distuw);
            model.splats[v].size = max(max(model.splats[v].size, distuv), distvw);
            model.splats[w].size = max(max(model.splats[w].size, distvw), distuw);
        }
        
        outfile <<  "center_x center_y center_z normal_x normal_y normal_z size" << endl;

        for (int i = 0; i < num_verts; ++i) {
            model.splats[i].size /= 2;
            model.splats[i].normal /= model.splats[i].normal.mag();

            //write to disk
            splat s = model.splats[i];
            outfile << s.center.x << " " << s.center.y << " " << s.center.z << " ";
            outfile << s.normal.x << " " << s.normal.y << " " << s.normal.z << " ";
            outfile << s.size << endl;
        }
    }
    file.close();
    outfile.close();
}
