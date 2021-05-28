#pragma once

#include "vector"
#include "object.h"
#include "material.h"

class Scene
{
private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Material>> materials;
public:
    Scene(){}
    void add(std::shared_ptr<Object> obj){
        objects.push_back(obj);
    }
    std::shared_ptr<Object> get(size_t i){
        return objects[i];
    }

    bool get_hit(const Ray& ray, double t_min, double t_max,  Hit& hit){
        Hit temp_hit;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& obj: objects) {
            if (obj->hit_test(ray, t_min, closest_so_far, temp_hit)) {
                hit_anything = true;
                closest_so_far = temp_hit.t;
                hit = temp_hit;
            }
        }

        return hit_anything;
    }

};
