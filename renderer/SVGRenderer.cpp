// src/SVGRenderer.cpp
#include "SVGRenderer.h"
#include "ColorUtils.h"
#include <fstream>
#include <iomanip>
#include <sstream>

void SVGRenderer::initialize(int width, int height)
{
    svgContent.str("");
    svgContent.clear();
    defsEmitted = false;

    svgContent << R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)" << "\n"
        << R"(<svg width=")" << width
        << R"(" height=")" << height
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
    emitDefsIfNeeded();
    svgContent << R"(  <circle cx=")" << x << R"(" cy=")" << y
               << R"(" r=")" << radius
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawSquare(float x, float y, float size)
{
    emitDefsIfNeeded();
    svgContent << R"(  <rect x=")" << x << R"(" y=")" << y
               << R"(" width=")" << size << R"(" height=")" << size
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawRectangle(float x, float y, float width, float height)
{
    emitDefsIfNeeded();
    svgContent << R"(  <rect x=")" << x << R"(" y=")" << y
        << R"(" width=")" << width << R"(" height=")" << height
        << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    emitDefsIfNeeded();
    svgContent << R"(  <polygon points=")"
               << x1 << "," << y1 << " "
               << x2 << "," << y2 << " "
               << x3 << "," << y3
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawEllipse(float centerX, float centerY, float radiusX, float radiusY)
{
    emitDefsIfNeeded();
    svgContent << R"(  <ellipse cx=")" << centerX << R"(" cy=")" << centerY
               << R"(" rx=")" << radiusX << R"(" ry=")" << radiusY
               << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
               << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}



void SVGRenderer::drawLine(const Point2D& p1, const Point2D& p2)
{
    emitDefsIfNeeded();
    svgContent << R"(  <line x1=")" << p1.x << R"(" y1=")" << p1.y
        << R"(" x2=")" << p2.x << R"(" y2=")" << p2.y
        << R"(" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"("/>)" << "\n";
}

void SVGRenderer::drawPolyline(const std::vector<Point2D>& points)
{
    emitDefsIfNeeded();
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
    emitDefsIfNeeded();
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
    emitDefsIfNeeded();
    svgContent << R"(  <text x=")" << x << R"(" y=")" << y
        << R"(" font-family=")" << typeface << R"(" font-size=")" << fontSize
        << R"(" fill=")" << fillColor << R"(" stroke=")" << strokeColor
        << R"(" stroke-width=")" << strokeWidth << R"(">)";
    svgContent << textContent << R"(</text>)" << "\n";
}

void SVGRenderer::drawPath(const std::vector<PathCommand>& segments, unsigned long fillColour, unsigned long strokeColour, float fillOpacity, float strokeOpacity, float strokeWidth)
{
    emitDefsIfNeeded();
    svgContent << R"(  <path d=")";

    for (const auto& cmd : segments) {
        char letter;
        switch (cmd.type) {
        case PathCommandType::MoveTo:           letter = cmd.relative ? 'm' : 'M'; break;
        case PathCommandType::LineTo:           letter = cmd.relative ? 'l' : 'L'; break;
        case PathCommandType::CubicBezier:      letter = cmd.relative ? 'c' : 'C'; break;
        case PathCommandType::QuadraticBezier:  letter = cmd.relative ? 'q' : 'Q'; break;
        case PathCommandType::HorizontalLineTo: letter = cmd.relative ? 'h' : 'H'; break;
        case PathCommandType::VerticalLineTo:   letter = cmd.relative ? 'v' : 'V'; break;
        case PathCommandType::ClosePath:        letter = 'Z'; break;
        default:                                letter = '?'; break;
        }

        svgContent << letter;

        // Only print coordinates if the command has any points
        for (const auto& pt : cmd.points) {
            svgContent << ' ' << pt.x << ',' << pt.y;
        }

        svgContent << ' ';
    }

    svgContent << R"(" fill=")" << rgbaToSVGColour(fillColour)
        << R"(" stroke=")" << rgbaToSVGColour(strokeColour)
        << R"(" fill-opacity=")" << fillOpacity
        << R"(" stroke-opacity=")" << strokeOpacity
        << R"(" stroke-width=")" << strokeWidth
        << R"(" />)" << "\n";

    std::cout << "SVGRenderer path fill = " << rgbaToSVGColour(fillColour)
        << ", stroke = " << rgbaToSVGColour(strokeColour) << std::endl;
}

void SVGRenderer::setFillColor(int r, int g, int b, int a) // Updated signature
{
    currentfillColor = (r << 24) | (g << 16) | (b << 8) | a;
    fillColor = rgbtoHex(r, g, b, a);
}

void SVGRenderer::setStrokeColor(int r, int g, int b, int a)
{
    currentStrokeColor = (r << 24) | (g << 16) | (b << 8) | a;
    strokeColor = rgbtoHex(r, g, b, a);
}

void SVGRenderer::setStrokeWidth(float width)
{
    strokeWidth = width;
}

void SVGRenderer::setFillOpacity(float opacity)
{
    currentFillOpacity = opacity;
}

void SVGRenderer::setStrokeOpacity(float opacity)
{
    currentStrokeOpacity = opacity;
}

void SVGRenderer::drawPath(const std::string& dStr)
{
    emitDefsIfNeeded();
    SVGPath path(dStr);
    path.setDefaultFillColour(currentfillColor);
    path.setDefaultStrokeColour(currentStrokeColor);
    path.setDefaultStrokeWidth(strokeWidth);
    path.setDefaultFillOpacity(currentFillOpacity);
    path.setDefaultStrokeOpacity(currentStrokeOpacity);
    path.render(this);


}

void SVGRenderer::drawLinearGradient(const string& id, const Point2D& P1, const Point2D& P2, const vector<pair<float, string>>& stops)
{
    defsContent << "  <linearGradient id=\"" << id << "\" "
        << "x1=\"" << P1.x << "%\" y1=\"" << P1.y << "%\" "
        << "x2=\"" << P2.x << "%\" y2=\"" << P2.y << "%\">\n";
    for (auto& stop : stops) {
        defsContent << "    <stop offset=\"" << stop.first * 100.0f << "%\" "
            << "stop-color=\"" << stop.second << "\" />\n";
    }
    defsContent << "  </linearGradient>\n";
}

void SVGRenderer::drawRadialGradient(const string& id, const Point2D& centre, float r, const vector<pair<float, string>>& stops)
{
    defsContent << "  <radialGradient id=\"" << id << "\" "
        << "cx=\"" << centre.x << "%\" cy=\"" << centre.y << "%\" r=\"" << r << "%\">\n";
    for (auto& stop : stops) {
        defsContent << "    <stop offset=\"" << stop.first * 100 << "%\" "
            << "stop-color=\"" << stop.second << "\" />\n";
    }
    defsContent << "  </radialGradient>\n";
}

void SVGRenderer::setFillGradient(const string& gradientId)
{
    setFillColor(std::string("url(#") + gradientId + ")");
}

void SVGRenderer::setStrokeGradient(const string& gradientId)
{
    setStrokeColor(std::string("url(#") + gradientId + ")");
}

void SVGRenderer::setFillColor(const std::string& css)
{
    currentfillColor = 0;
    fillColor = css;
}

void SVGRenderer::setStrokeColor(const std::string& css)
{
    currentStrokeColor = 0;
    strokeColor = css;
}

void SVGRenderer::emitDefsIfNeeded()
{
    if (!defsEmitted && !defsContent.str().empty()) {
        svgContent << "  <defs>\n" << defsContent.str() << "  </defs>\n";
        defsEmitted = true;
    }
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
