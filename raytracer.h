#pragma once

#include <image.h>
#include <camera_options.h>
#include <render_options.h>
#include <string>
#include <Scene.h>
#include "Sphere.h"
#include "CameraTransformer.h"

const Shape* GetMinShape(const Scene&, const Ray&, double* = nullptr);
Vector3D CalcRay(const Ray&, const Scene&, int, int, bool = false);
double FindMaxRGB(const std::vector<Vector3D>&);
Image ToneAndGammaCorrection(const std::vector<Vector3D>&, const CameraOptions&);

std::pair<Vector3D, Vector3D> Reflect(const Ray& ray, const Scene& scene, int depth, int max_depth,
                                      const Vector3D& norm, const Vector3D& point);
const double kEps = 1e-3;

Image Render(const std::string& filename, const CameraOptions& camera_options,
             const RenderOptions& render_options) {
    Scene scene;
    scene.Load(filename);

    CameraTransformer camera_transformer(camera_options);
    std::vector<Vector3D> image(camera_options.screen_width * camera_options.screen_height);

    for (int i = 0; i < camera_options.screen_height; i++) {
        for (int j = 0; j < camera_options.screen_width; j++) {
            auto ray = camera_transformer.GetRay(j, i);

            image[i * camera_options.screen_width + j] =
                CalcRay(ray, scene, 0, render_options.depth);
        }
    }

    return ToneAndGammaCorrection(image, camera_options);
}

Image ToneAndGammaCorrection(const std::vector<Vector3D>& image, const CameraOptions& options) {
    double c = FindMaxRGB(image);
    c = c * c;
    Image res(options.screen_width, options.screen_height);

    for (int i = 0; i < options.screen_height; ++i) {
        for (int j = 0; j < options.screen_width; ++j) {
            const auto& item = image[i * options.screen_width + j];

            double r = item.x * (1 + item.x / c) / (1 + item.x);
            double g = item.y * (1 + item.y / c) / (1 + item.y);
            double b = item.z * (1 + item.z / c) / (1 + item.z);

            res.SetPixel(RGB(std::pow(r, 1.0 / 2.2) * 255, std::pow(g, 1.0 / 2.2) * 255,
                             std::pow(b, 1.0 / 2.2) * 255),
                         i, j);
        }
    }
    return res;
}

double FindMaxRGB(const std::vector<Vector3D>& image) {
    double result = 0;
    for (const auto& item : image) {
        result = std::max(std::max(item.x, item.y), std::max(item.z, result));
    }

    return result;
}

const Shape* GetMinShape(const Scene& scene, const Ray& ray, double* distance) {
    double min_dist = std::numeric_limits<double>().max();
    const Shape* result = nullptr;

    for (const auto& obj : scene.GetObjects()) {
        double cur_dist;
        if (obj->Intersect(ray, &cur_dist) && cur_dist < min_dist) {
            min_dist = cur_dist;
            result = obj;
        }
    }

    if (distance != nullptr) {
        *distance = min_dist;
    }
    return result;
}

Vector3D CalcRay(const Ray& ray, const Scene& scene, int depth, int max_depth, bool inside) {
    if (depth == max_depth) {
        return Vector3D();
    }
    Vector3D res;
    const Shape* obj = GetMinShape(scene, ray);

    if (obj == nullptr) {
        return Vector3D();
    }

    Vector3D surface_point = obj->GetSurfacePoint(ray);
    Vector3D norm = obj->GetNorm(surface_point);
    if (norm * ray.direction > 0) {
        norm = -norm;
    }

    Vector3D point = surface_point + kEps * norm;

    Vector3D light_diffuse = {0, 0, 0};
    Vector3D light_specular = {0, 0, 0};

    if (obj->IsReflecting()) {
        if (!inside) {
            auto reflect_res = Reflect(ray, scene, depth, max_depth, norm, point);
            light_diffuse += reflect_res.first;
            light_specular += reflect_res.second;
        }
        double cur_tr = (inside) ? 1 : obj->GetTr();
        if (cur_tr != 0) {
            double refract_coef = (inside) ? obj->GetNi() : 1. / obj->GetNi();
            double cos = -norm * ray.direction;
            Vector3D refract_dir = refract_coef * ray.direction +
                                   (refract_coef * cos -
                                    std::sqrt(1 - refract_coef * refract_coef * (1 - cos * cos))) *
                                       norm;
            Vector3D refract_rgb =
                CalcRay(Ray(point - 2 * kEps * norm, refract_dir),
                        scene, depth + 1, max_depth, inside ^ obj->GetInsideFlag());

            res += refract_rgb * cur_tr;
        }
    }

    for (const auto& light : scene.GetLights()) {
        Vector3D light_dir = light.point - point;
        Ray to_light(point, light_dir);

        double cos = to_light.direction * norm;
        if (cos <= 0) {
            continue;
        }
        double dist;
        auto min_tr = GetMinShape(scene, to_light, &dist);
        if (min_tr == nullptr || light_dir.GetModule() < dist) {
            light_diffuse += light.rgb * cos;
            Vector3D vr = (2 * cos * norm - to_light.direction);
            light_specular += (-ray.direction * vr > 0)
                                  ? light.rgb * std::pow((-ray.direction) * vr, obj->GetNs())
                                  : Vector3D();
        }
    }
    res += obj->GetPointColor(surface_point, light_diffuse, light_specular);
    return res;
}
std::pair<Vector3D, Vector3D> Reflect(const Ray& ray, const Scene& scene, int depth, int max_depth,
                                      const Vector3D& norm, const Vector3D& point) {
    Vector3D reflect_dir = 2 * (-ray.direction * norm) * norm + ray.direction;
    Ray to_reflect(point, reflect_dir);
    Vector3D reflect_rgb = CalcRay(to_reflect, scene, depth + 1, max_depth);
    double cos = to_reflect.direction * norm;
    return {reflect_rgb * cos, reflect_rgb};
}
