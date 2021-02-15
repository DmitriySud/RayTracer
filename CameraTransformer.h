//
// Created by dimasya on 16.01.2021.
//

#ifndef SHAD_CPP0_CAMERATRANSFORMER_H
#define SHAD_CPP0_CAMERATRANSFORMER_H

#include "camera_options.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "Ray.h"
#include <cmath>

class CameraTransformer {
public:
    explicit CameraTransformer(const CameraOptions& camera_options)
        : cam_op_(&camera_options),
          camera_to_word_(Matrix44(Vector3D(camera_options.look_from),
                                   Vector3D(camera_options.look_to))),
          scale_(std::tan(camera_options.fov * 0.5)),
          image_aspect_ratio_(camera_options.screen_width * 1.0 / camera_options.screen_height) {
    }

    Ray GetRay(int width, int height) const {
        double x = (2 * (width + 0.5) / cam_op_->screen_width - 1) * scale_ * image_aspect_ratio_,
               y = (2 * (height + 0.5) / cam_op_->screen_height - 1) * scale_;
        Vector3D direct = camera_to_word_.MultDir(Vector3D(x, y, -1));
        return Ray(camera_to_word_.MultVec(Vector3D()), direct);
    }

private:
    const CameraOptions* cam_op_;
    Matrix44 camera_to_word_;
    double scale_;
    double image_aspect_ratio_;
};

#endif  // SHAD_CPP0_CAMERATRANSFORMER_H
