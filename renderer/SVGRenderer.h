// include/SVGRenderer.h
#pragma once
#include "IRenderer.h"
#include "ColorUtils.h"
#include <sstream>
#include <iomanip>

class SVGRenderer : public IRenderer
{
public:
    void initialize(int width, int height) override;
    void saveToFile(const std::string &filepath) override;

    void drawCircle(float x, float y, float radius) override;
    void drawSquare(float x, float y, float size) override;
    void drawRectangle(float x, float y, float width, float height) override;
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) override;
    void drawEllipse(float centerX, float centerY, float radiusX, float radiusY) override;
    void drawLine(const Point2D& p1, const Point2D& p2) override;
    void drawPolyline(const std::vector<Point2D>& points) override;
    void drawPolygon(const std::vector<Point2D>& points) override;
    void drawText(float x, float y, const std::string& textContent, int fontSize, const std::string& typeface, const std::string& fontFilePath) override;
    void drawPath(const std::vector<PathCommand>& segments, unsigned long fillColour, unsigned long strokeColour, float fillOpacity, float strokeOpacity, float strokeWidth) override;
    void pushTransform(const string& transformStr) override;
    void popTransform() override;
    void beginGroup() override;
    void endGroup() override;
    void setFillColor(int r, int g, int b, int a = 255) override;
    void setStrokeColor(int r, int g, int b, int a = 255) override;
    void setStrokeWidth(float width) override;
    void setFillOpacity(float opacity);
    void setStrokeOpacity(float opacity);
    void drawPath(const std::string& dStr) override;
    void drawLinearGradient(const string& id, const Point2D& P1, const Point2D& P2, const vector<pair<float, string>>& stops) override;
    void drawRadialGradient(const string& id, const Point2D& centre, float r, const vector<pair<float, string>>& stops) override;
    void setFillGradient(const string& gradientId) override;
    void setStrokeGradient(const string& gradientId) override;
    void setFillColor(const string& css) override;
    void setStrokeColor(const string& css) override;

private:
    stringstream svgContent;
    ostringstream defsContent;
    string fillColor;
    string strokeColor;
    bool defsEmitted = false;
    void emitDefsIfNeeded();
    float strokeWidth = 1.0f;
    float currentFillOpacity = 1.0f;
    float currentStrokeOpacity = 1.0f;
    unsigned long currentfillColor = 0x000000ff;
    unsigned long currentStrokeColor = 0x000000ff;
};