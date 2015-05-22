#include "opengl.hpp"
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

bool loadOBJ(const char* path,
             std::vector<glm::vec3>& out_vertices,
             std::vector<glm::vec2>& out_uvs,
             std::vector<glm::vec3>& out_normals) {
    std::vector<unsigned int> v_vertex_idx;
    std::vector<unsigned int> v_uv_idx;
    std::vector<unsigned int> v_normal_idx;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    FILE* file;

    std::cout << "Loading OBJ file " << path << "..." << std::endl;
    file = std::fopen(path, "r");
    if (file == NULL ) {
        std::cerr << "Impossible to open the file !" << std::endl;
        return false;
    }
    while (1) {
        char line_header[128];
        int  res = fscanf(file, "%s", line_header);

        if (res == EOF) {
            break;
        }
        if (std::strcmp(line_header, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &(vertex.x), &(vertex.y), &(vertex.z));
            temp_vertices.push_back(vertex);
        } else if (std::strcmp(line_header, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &(uv.x), &(uv.y));
            temp_uvs.push_back(uv);
        } else if (std::strcmp(line_header, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &(normal.x), &(normal.y), &(normal.z));
            temp_normals.push_back(normal);
        } else if (std::strcmp( line_header, "f") == 0) {
            std::string vertex1;
            std::string vertex2;
            std::string vertex3;
            unsigned int vertex_idx[3];
            unsigned int uv_idx[3];
            unsigned int normal_idx[3];
            int          matches;

            matches = std::fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                  &(vertex_idx[0]), &(uv_idx[0]), &(normal_idx[0]),
                                  &(vertex_idx[1]), &(uv_idx[1]), &(normal_idx[1]),
                                  &(vertex_idx[2]), &(uv_idx[2]), &(normal_idx[2]));
            if (matches != 9) {
                std::cerr << "File can't be read by our simple parser: Try exporting with other options" << std::endl;
                return false;
            }
            for (unsigned int i = 0; i < 3; ++(i)) {
                v_vertex_idx.push_back(vertex_idx[i]);
                v_uv_idx.push_back(uv_idx[i]);
                v_normal_idx.push_back(normal_idx[i]);
            }
        } else {
            char garbage_buffer[1000];
            fgets(garbage_buffer, 1000, file);
        }
    }

    for (unsigned int i = 0; i < v_vertex_idx.size(); ++(i)) {
        out_vertices.push_back(temp_vertices[v_vertex_idx[i] - 1]);
        out_uvs     .push_back(temp_uvs[v_uv_idx[i] - 1]);
        out_normals .push_back(temp_normals[v_normal_idx[i] - 1]);
    }

    return true;
}
