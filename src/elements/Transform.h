#pragma once
#include <string>
#include <array>
#include <sstream>
#include <cmath>
#include <regex>
#include <stack>

// Dummy transform parser (for now just stores string)
class Transform {
public:
    Transform();
    static Transform identity();
    static Transform translate(float tx, float ty);
    static Transform scale(float sx, float sy);
    static Transform rotate(float degrees);
    static Transform rotate(float degrees, float cx, float cy);
    static Transform fromString(const std::string& svgTransformStr);

    Transform operator*(const Transform& other) const;
    std::array<float, 9> getMatrix() const;

private:
    std::array<float, 9> m;

    static Transform multiply(const Transform& a, const Transform& b);
};