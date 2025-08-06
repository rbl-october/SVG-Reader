// src/SVGRenderer.cpp
#include "SVGRenderer.h"
#include <fstream>
#include <iomanip>
#include <sstream>

void SVGRenderer::initialize(int width, int height)
{
    svgContent.str(""); // Clear any existing content
    svgContent << R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)" << "\n"
               << R"(<svg width=")" << width << R"(" height=")" << height
               << R"(" xmlns="http://www.w3.org/2000/svg">)" << "\n";
}

void SVGRenderer::saveToFile(const std::string &filepath)
{
    svgContent << R"(</svg>)";
    std::ofstream outFile(filepath);
    if (outFile.is_open())
    {
        outFile << svgContent.str();
        outFile.close();
    }
}

void SVGRenderer::drawCircle(float x, float y, float radius)
{
    svgContent << R"(  <circle cx=")" << x << R"(" cy=")" << y
               << R"(" r=")" << radius
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawSquare(float x, float y, float size)
{
    svgContent << R"(  <rect x=")" << x << R"(" y=")" << y
               << R"(" width=")" << size << R"(" height=")" << size
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawRectangle(float x, float y, float width, float height)
{
    svgContent << R"(  <rect x=")" << x << R"(" y=")" << y
        << R"(" width=")" << width << R"(" height=")" << height
        << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    svgContent << R"(  <polygon points=")"
               << x1 << "," << y1 << " "
               << x2 << "," << y2 << " "
               << x3 << "," << y3
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawEllipse(float centerX, float centerY, float radiusX, float radiusY)
{
    svgContent << R"(  <ellipse cx=")" << centerX << R"(" cy=")" << centerY
               << R"(" rx=")" << radiusX << R"(" ry=")" << radiusY
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}



void SVGRenderer::drawLine(const Point2D& p1, const Point2D& p2)
{
    svgContent << R"(  <line x1=")" << p1.x << R"(" y1=")" << p1.y
        << R"(" x2=")" << p2.x << R"(" y2=")" << p2.y
        << R"(" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawPolyline(const std::vector<Point2D>& points)
{
    svgContent << R"(  <polyline points=")";
    for (size_t i = 0; i < points.size(); ++i) {
        svgContent << points[i].x << "," << points[i].y;
        if (i < points.size() - 1) {
            svgContent << " ";
        }
    }
    svgContent << R"(" fill="none" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawPolygon(const std::vector<Point2D>& points)
{
    svgContent << R"(  <polygon points=")";
    for (size_t i = 0; i < points.size(); ++i) {
        svgContent << points[i].x << "," << points[i].y;
        if (i < points.size() - 1) {
            svgContent << " ";
        }
    }
    svgContent << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawText(float x, float y, const std::string& textContent, int fontSize, const std::string& typeface, const std::string& fontFilePath)
{
    svgContent << R"(  <text x=")" << x << R"(" y=")" << y
        << R"(" font-family=")" << typeface << R"(" font-size=")" << fontSize
        << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"(">)";
    svgContent << textContent << R"(</text>)" << "\n";
}

void SVGRenderer::drawPath(const std::vector<PathCommand>& segments, unsigned long fillColour, unsigned long strokeColour, float fillOpacity, float strokeOpacity, float strokeWidth)
{
    svgContent << R"(  <path d=")";
    for (const auto& cmd : segments) {
        char letter;
        switch (cmd.type) {
        case PathCommandType::MoveTo: letter = cmd.relative ? 'm' : 'M'; break;
        case PathCommandType::LineTo: letter = cmd.relative ? 'l' : 'L'; break;
        case PathCommandType::CubicBezier: letter = cmd.relative ? 'c' : 'C'; break;
        case PathCommandType::QuadraticBezier: letter = cmd.relative ? 'q' : 'Q'; break;
        case PathCommandType::HorizontalLineTo: letter = cmd.relative ? 'h' : 'H'; break;
        case PathCommandType::VerticalLineTo: letter = cmd.relative ? 'v' : 'V'; break;
        case PathCommandType::ClosePath: letter = 'Z'; break;
        }

        svgContent << letter;

        for (const auto& pt : cmd.points) {
            svgContent << ' ' << pt.x << ',' << pt.y;
        }

        svgContent << ' ';
    }

    svgContent << R"(" fill=")" << fillColour
        << R"(" stroke=")" << strokeColour
        << R"(" fill-opacity=")" << fillOpacity
        << R"(" stroke-opacity=")" << strokeOpacity
        << R"(" stroke-width=")" << strokeWidth
        << R"(" />)" << "\n";
}

void SVGRenderer::setFillColor(int r, int g, int b, int a) // Updated signature
{
    fillColor = rgbtoHex(r, g, b, a);
}

void SVGRenderer::setStrokeColor(int r, int g, int b, int a)
{
    strokeColor = rgbtoHex(r, g, b, a);
}

void SVGRenderer::setStrokeWidth(float width)
{
    strokeWidth = width;
}

void SVGRenderer::drawPath(const std::string& dStr)
{
    SVGPath path(dStr);
    path.render(this);
}

std::string SVGRenderer::rgbtoHex(int r, int g, int b, int a)
{
    std::stringstream ss;
    ss << "#" << std::hex << std::setfill('0')
        << std::setw(2) << r
        << std::setw(2) << g
        << std::setw(2) << b;
    // Only append alpha if it's not fully opaque
    if (a < 255)
    {
        ss << std::setw(2) << a;
    }
    return ss.str();
}

std::stack<bool> groupOpenStack;

void SVGRenderer::pushTransform(const string& transformStr) {
    svgContent << R"(  <g transform=")" << '"' << transformStr << '"' << R"(>")" << "\n";
    groupOpenStack.push(true);
}

void SVGRenderer::popTransform() {
    if (!groupOpenStack.empty() && groupOpenStack.top()) {
        svgContent << R"(  </g>)" << "\n";
        groupOpenStack.pop();
    }
}

void SVGRenderer::beginGroup() {
    groupOpenStack.push(false); // nhóm không có transform
    svgContent << R"(  <g>)" << "\n";
}

void SVGRenderer::endGroup() {
    if (!groupOpenStack.empty()) {
        svgContent << R"(  </g>)" << "\n";
        groupOpenStack.pop();
    }
}
