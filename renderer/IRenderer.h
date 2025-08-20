// include/IRenderer.h
#pragma once
#include <vector>
#include <utility>
#include <string>
#include "..\src\elements\elements.h"

using namespace std;
class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual void initialize(int width, int height) = 0;
    virtual void saveToFile(const string &filepath) = 0;

    // Drawing methods
    virtual void drawCircle(float x, float y, float radius) = 0;
    virtual void drawSquare(float x, float y, float size) = 0;
    virtual void drawRectangle(float x, float y, float width, float height) = 0;
    virtual void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) = 0;
    virtual void drawEllipse(float centerX, float centerY, float radiusX, float radiusY) = 0;
    virtual void drawLine(const Point2D& p1, const Point2D& p2) = 0;
    virtual void drawPolyline(const vector<Point2D>& points) = 0;
    virtual void drawPolygon(const vector<Point2D>& points) = 0;
    virtual void drawText(float x, float y, const string& textContent, int fontSize, const string& typeface, const string& fontFilePath) = 0;
    virtual void drawPath(const vector<PathCommand>& segments, unsigned long fillColour, unsigned long strokeColour, float fillOpacity, float strokeOpacity, float strokeWidth) = 0;
    virtual void drawPath(const string& dStr) = 0;
    virtual void drawLinearGradient(const string& id, const Point2D& P1, const Point2D& P2, const vector<pair<float, string>>& stops) = 0;
    virtual void drawRadialGradient(const string& id, const Point2D&centre, float r, const vector<pair<float, string>>& stops) = 0;


    // Property setting methods
    virtual void setFillColor(int r, int g, int b, int a = 255) = 0;
    virtual void setStrokeColor(int r, int g, int b, int a = 255) = 0;
    virtual void setStrokeWidth(float width) = 0;
    virtual void setFillGradient(const string& gradientId) = 0;
    virtual void setStrokeGradient(const string& gradientId) = 0;
    virtual void setFillColor(const std::string& css) = 0;
    virtual void setStrokeColor(const std::string& css) = 0;

    // New methods for transformations & grouping
    virtual void pushTransform(const string& transformStr) = 0;
    virtual void popTransform() = 0;

    virtual void beginGroup() = 0;
    virtual void endGroup() = 0;
};