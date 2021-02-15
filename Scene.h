//
// Created by dimasya on 09.01.2021.
//

#ifndef SHAD_CPP0_SCENE_H
#define SHAD_CPP0_SCENE_H


#include <Triangle.h>
#include <fstream>
#include <sstream>
#include "Material.h"
#include "Vertex.h"
#include "Triangle.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Shape.h"

class Scene {
public:
    Scene() {
    }

    bool Load(std::string obj_filename) {
        std::vector<Vector3D> points;
        std::vector<Vector3D> normals;
        std::unordered_map<std::string, size_t> materials;

        std::ifstream obj_in(obj_filename);

        std::string cur_str;
        Material* cur_mtl = nullptr;
        while (obj_in && obj_in >> cur_str) {
            if (cur_str == "mtllib") {
                obj_in >> cur_str;
                size_t sep_idx = obj_filename.find_last_of("/\\");
                materials = LoadMaterials(
                    obj_filename.substr(0, sep_idx + 1) + cur_str);
            } else if(cur_str == "usemtl"){
                obj_in >> cur_str;
                cur_mtl = &materials_[materials[cur_str]];
            } else if(cur_str == "v"){
                points.push_back(Vector3D());
                obj_in >> points[points.size() - 1];
            } else if(cur_str == "vt"){

            } else if(cur_str == "vn"){
                normals.push_back(Vector3D());
                obj_in >> normals[normals.size() - 1];
            } else if(cur_str == "f"){
                ParsePolygon(points, normals, obj_in, cur_mtl);
            } else if(cur_str == "S"){
                Vector3D center;
                double radius;
                obj_in >> center >> radius;
                Sphere* s = new Sphere(radius, center, cur_mtl);
                shapes_.push_back(s);
            } else if(cur_str == "P"){
                Vector3D point;
                Vector3D color;

                obj_in >> point >> color;
                lights_.emplace_back(point, color);
            } else if (cur_str[0] == '#'){
                getline(obj_in, cur_str);
            }

    }
        return true;
    }

    void ParsePolygon(const std::vector<Vector3D>& points,
                      const std::vector<Vector3D>& normals,
                      std::ifstream& obj_in, Material* cur_mtl) {
        std::stringstream stream;
        std::string buff;
        std::getline(obj_in, buff);
        stream << buff;
        buff.clear();

        std::array<std::array<int, 3>, 3> triangle;


        for(int cnt = 0; stream >> buff; ++cnt){
            int v_idx, vn_idx, vt_idx;
            size_t sep1 = buff.find('/', 0);
            size_t sep2 = buff.find('/', sep1 + 1);

            v_idx = std::stoi(buff);
            v_idx = (v_idx < 0) ? points.size() + v_idx : --v_idx;

            if (sep1 == std::string::npos){
                vt_idx = -1;
                vn_idx = -1;
            } else if(sep2 == std::string::npos){
                vn_idx = -1;
                vt_idx = std::stoi(buff.substr(sep1 + 1));
                // TODO : Добавить текстуры и пересчитать индекс
            } else{
                vn_idx = std::stoi(buff.substr(sep2 + 1));
                vn_idx = (vn_idx < 0) ? normals.size() + vn_idx : --vn_idx;
                vt_idx = (sep2 == sep1 + 1) ? -1 : std::stoi(buff.substr(sep1 + 1));
                // TODO : Добавить текстуры и пересчитать индекс
            }

            if (cnt == 0){
                triangle[2][0] = v_idx;
                triangle[2][1] = vt_idx;
                triangle[2][2] = vn_idx;
            }

            triangle[cnt % 2][0] = v_idx;
            triangle[cnt % 2][1] = vt_idx;
            triangle[cnt % 2][2] = vn_idx;
            if (cnt >= 2){
                Triangle* t;
                if (vn_idx == -1 && vt_idx == -1) {
                    t = new Triangle{Vertex(points[triangle[0][0]]),
                                     Vertex(points[triangle[1][0]]),
                                     Vertex(points[triangle[2][0]]), cur_mtl};
                } else {
                    t = new Triangle{Vertex(points[triangle[0][0]], normals[triangle[0][2]]),
                                     Vertex(points[triangle[1][0]], normals[triangle[1][2]]),
                                     Vertex(points[triangle[2][0]], normals[triangle[2][2]]), cur_mtl};

                }


                shapes_.push_back(t);
            }
        }
    }

    std::unordered_map<std::string, size_t> LoadMaterials(std::string mtl_filename) {
        std::ifstream mtl_in(mtl_filename);
        std::unordered_map<std::string, size_t> res;

        std::string cur_str, cur_material_name;
        Material cur_material;
        while (mtl_in >> cur_str) {
            if (cur_str == "newmtl") {
                if (!cur_material_name.empty()){
                    materials_.push_back(cur_material);
                    res[cur_material_name] = materials_.size() - 1;
                }

                cur_material = Material();
                mtl_in >> cur_material_name;
            } else if (cur_str == "Ka") {
                mtl_in >> cur_material.Ka;
            } else if (cur_str == "Kd") {
                mtl_in >> cur_material.Kd;
            } else if (cur_str == "Ks") {
                mtl_in >> cur_material.Ks;
            } else if (cur_str == "Ke") {
                mtl_in >> cur_material.Ke;
            } else if (cur_str == "Ns") {
                mtl_in >> cur_material.Ns;
            } else if (cur_str == "Ni") {
                mtl_in >> cur_material.Ni;
            } else if (cur_str == "Tr") {
                mtl_in >> cur_material.Tr;
            } else if (cur_str == "d") {
                mtl_in >> cur_material.Tr;
                cur_material.Tr = 1 - cur_material.Tr;
            } else if (cur_str == "illum") {
                int illum;
                mtl_in >> illum;
                cur_material.illum = illum > 2;
            } else if (cur_str[0] == '#'){
                getline(mtl_in, cur_str);
            }
        }
        materials_.push_back(cur_material);
        res[cur_material_name] = materials_.size() - 1;
        return res;
    }

    const std::vector<Shape*>& GetObjects() const{
        return shapes_;
    }

    const std::vector<LightSource>& GetLights() const{
        return lights_;
    }

    ~Scene(){
        for (int i = 0; i < shapes_.size(); ++i) {
            delete shapes_[i];
        }
    }
private:
    std::vector<Shape*> shapes_;
    std::vector<LightSource> lights_;
    std::vector<Material> materials_;

};



#endif  // SHAD_CPP0_SCENE_H
