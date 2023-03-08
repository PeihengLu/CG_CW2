/*
 * BVH.cpp
 *
 *
 */
#include "BVH.h"


namespace rt{


    BVH::BVH(const std::vector<Shape*>& shapes) {
        this->bbox = compute_bounding_box(shapes);
        this->shapes = shapes;

        if (shapes.size() == 1) { //leaf node
            printf("leaf node\n");
            this->left = nullptr;
            this->right = nullptr;
            return;
        }

        //TODO sort the shapes into clusters using midpoint heuristic
        std::vector<Shape*> leftShapes;
        std::vector<Shape*> rightShapes;

        // find the longest axis of the bbox to the split on
        // int axis = this->bbox->getLongestAxis();
        int axis = 1;
        float mid = (this->bbox->max_point[axis] + this->bbox->min_point[axis]) / 2;

        for (auto shape: shapes) {
            if (shape->getBoundingBox()->getCenter()[axis] <= mid) {
                leftShapes.push_back(shape);
            } else {
                rightShapes.push_back(shape);
            }
        }

        std::cout<<"number of shapes in left node: "<<std::to_string(leftShapes.size())<<std::endl;
        std::cout<<"number of shapes in right node: "<<std::to_string(rightShapes.size())<<std::endl;

        if (leftShapes.size() == 0 || rightShapes.size() == 0) { // this is a leaf node
            printf("leaf node\n");
            this->left = nullptr;
            this->right = nullptr;
            return;
        }

        this->left = new BVH(leftShapes);
        this->right = new BVH(rightShapes);
        printf("splitting\n");
    }

    // check if a ray intersect with the bounding box of BVH node
    std::tuple<bool, Hit> BVH::intersect(Ray ray){
        Hit h;

        return std::make_tuple(this->bbox->intersect(ray.origin, ray.rayDirection), h);
    }


    std::tuple<bool, Hit, Shape*> BVH::testIntersect(Ray ray){
        bool hit=false;
        Hit h;
        Shape* s;
        if (!std::get<0>(this->intersect(ray))) {
            return std::make_tuple(false, h, s);
        }

        if (this->left == nullptr && this->right == nullptr) { // leafnode
            // printf("testing leaf node\n");
            // std::cout<<"number of shapes in node: "<<std::to_string(this->shapes.size())<<std::endl;

            float minDist = 1000000.0f;
            // test intersection with all shapes in node
            for (auto shape: this->shapes) {
                // printf("testing shapes\n");
                std::tuple<bool, Hit> result = shape->intersect(ray);
                if (std::get<0>(result)) {
                    // printf("hit\n");
                    hit = true;
                    if (ray.raytype==SHADOW) {
                        return std::make_tuple(true, h, s);
                    }
                    if (std::get<1>(result).distanceToOrigin < minDist) { // closer to origin
                        // printf("closer\n");
                        h = std::get<1>(result);
                        s = shape;
                        minDist = h.distanceToOrigin;
                    }
                }
            }
            return std::make_tuple(hit, h, s);
        }

        // printf("continues\n");

        if (this->left != nullptr) {
            std::tuple<bool, Hit, Shape*> leftResult = left->testIntersect(ray);
            if (std::get<0>(leftResult)) {
                // printf("left intersect\n");
                hit = true;
                h = std::get<1>(leftResult);
                s = std::get<2>(leftResult);
            }
        }

        if (this->right != nullptr) {
            // printf("test left\n");
            std::tuple<bool, Hit, Shape*> rightResult = right->testIntersect(ray);
            if (std::get<0>(rightResult)) {
                // printf("right intersect\n");
                if (!hit) {
                    hit = true;
                    h = std::get<1>(rightResult);
                    s = std::get<2>(rightResult);
                } else {
                    if (h.distanceToOrigin > std::get<1>(rightResult).distanceToOrigin) {
                        h = std::get<1>(rightResult);
                        s = std::get<2>(rightResult);
                    }
                }
            } 
        }

        return std::make_tuple(hit, h, s);
    }
} //namespace rt


