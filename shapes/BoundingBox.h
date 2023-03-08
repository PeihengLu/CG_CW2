/*
 * BoundingBox.h
 *
 *
 */
#pragma 1

#ifndef BBX_H_
#define BBX_H_

#include <vector>
#include <math/geometry.h>

namespace rt{


class BoundingBox {
    public:
        Vec3f min_point;
        Vec3f max_point;

        BoundingBox();
        BoundingBox(const Vec3f minP, const Vec3f maxP);
        bool intersect(Vec3f rayOrigin, Vec3f rayDirection) const;
        BoundingBox* extend_bounding_box(BoundingBox* box);

        Vec3f getCenter() {
            Vec3f center = max_point + min_point;
            center /= 2;
            return center;
        }

        int getLongestAxis() {
            float max = 0;
            int maxAxis = -1;

            for (int axis = 0; axis < 3; axis++) {
                if (max_point[axis] - min_point[axis] > max) {
                    max = max_point[axis] - min_point[axis];
                    maxAxis = axis;
                }
            }
        }

        ~BoundingBox();
};

BoundingBox* merge_bounding_box(const std::vector<BoundingBox*>& boxes);
}

#endif BBX_H_