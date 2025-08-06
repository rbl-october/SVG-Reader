// Transform.cpp
#include "Transform.h"
#include <cmath>
#include <sstream>
#include <regex>
#include <vector>
#include <iostream>

Transform::Transform() : m{ 1,0,0, 0,1,0, 0,0,1 } {}

Transform Transform::identity() {
    return Transform();
}

Transform Transform::translate(float tx, float ty) {
    Transform t;
    t.m = { 1, 0, tx,
            0, 1, ty,
            0, 0, 1 };
    return t;
}

Transform Transform::scale(float sx, float sy) {
    Transform t;
    t.m = { sx, 0,  0,
            0,  sy, 0,
            0,  0,  1 };
    return t;
}

Transform Transform::rotate(float degrees) {
    float rad = degrees * 3.1415926535f / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    Transform t;
    t.m = { c, -s, 0,
            s,  c, 0,
            0,  0, 1 };
    return t;
}

Transform Transform::rotate(float degrees, float cx, float cy) {
    return translate(cx, cy) * rotate(degrees) * translate(-cx, -cy);
}

Transform Transform::operator*(const Transform& other) const {
    return multiply(*this, other);
}

Transform Transform::multiply(const Transform& a, const Transform& b) {
    Transform r;
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            r.m[row * 3 + col] = 0;
            for (int k = 0; k < 3; ++k)
                r.m[row * 3 + col] += a.m[row * 3 + k] * b.m[k * 3 + col];
        }
    return r;
}

std::array<float, 9> Transform::getMatrix() const {
    return m;
}

Transform Transform::fromString(const std::string& svgTransformStr) {
    Transform result = Transform::identity();

    std::regex regexCommand(R"((\w+)\s*\(([^)]+)\))");
    auto begin = std::sregex_iterator(svgTransformStr.begin(), svgTransformStr.end(), regexCommand);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;
        std::string command = match[1];
        std::string argsStr = match[2];

        std::vector<float> args;
        std::stringstream ss(argsStr);
        std::string token;

        while (std::getline(ss, token, ',')) {
            std::stringstream st(token);
            float value;
            st >> value;
            if (!st.fail())
                args.push_back(value);
        }

        if (command == "translate") {
            float tx = args.size() > 0 ? args[0] : 0;
            float ty = args.size() > 1 ? args[1] : 0;
            result = result * Transform::translate(tx, ty);
        }
        else if (command == "scale") {
            float sx = args.size() > 0 ? args[0] : 1;
            float sy = args.size() > 1 ? args[1] : sx;
            result = result * Transform::scale(sx, sy);
        }
        else if (command == "rotate") {
            float angle = args.size() > 0 ? args[0] : 0;
            if (args.size() == 3) {
                result = result * Transform::rotate(angle, args[1], args[2]);
            }
            else {
                result = result * Transform::rotate(angle);
            }
        }
        else {
            std::cerr << "[Transform] Unknown transform: " << command << "\n";
        }
    }

    return result;
}
