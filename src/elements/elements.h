#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <string>
#include <vector>
#include <memory>
#include "Transform.h"

using std::string;
using std::vector;
using std::unique_ptr;


class IRenderer;

void getRGBAFromULong(unsigned long colour, int& r, int& g, int& b, int& a);

std::string rgbaToSVGColour(unsigned long colour);


struct Point2D {
    float x, y;
    Point2D(float x = 0, float y = 0);
};

class SVGElements {
public:
    unsigned long fillColour = 0x000000ff, strokeColour = 0x000000ff;
    float fillOpacity = 1.0f, strokeOpacity = 1.0f;
    float strokeWidth = 1.0f;

    virtual ~SVGElements();
    virtual void render(IRenderer* renderer) = 0;

    void setDefaultFillColour(unsigned long colour);
    void setDefaultStrokeColour(unsigned long colour);
    void setDefaultStrokeWidth(float width);
    void setDefaultFillOpacity(float opacity);
    void setDefaultStrokeOpacity(float opacity);
    void setTransform(const string& transformStr);

protected:
    string transformStr;
};

class SVGEllipse : public SVGElements {
public:
    Point2D centre;
    float radiusX, radiusY;

    SVGEllipse(const Point2D& centre, float radiusX, float radiusY);
    void setCentre(const Point2D& o);
    void setRadii(float rX, float rY);
    void render(IRenderer* renderer) override;
};

class SVGCircle : public SVGEllipse {
public:
    float radius;

    SVGCircle(const Point2D& centre, float radius);
    void setCentre(const Point2D& o);
    void setRadius(float r);
    void render(IRenderer* renderer) override;
};

class SVGRectangle : public SVGElements {
public:
    Point2D topLeft;
    float width, length;

    SVGRectangle(const Point2D& topLeft, float length, float width);
    void setTopLeft(const Point2D& A);
    void setWidthLength(float length, float width);
    void render(IRenderer* renderer) override;
};

class SVGLine : public SVGElements {
public:
    Point2D pointStart, pointEnd;

    SVGLine(const Point2D& p1, const Point2D& p2);
    void setLine(const Point2D& p1, const Point2D& p2);
    void render(IRenderer* renderer) override;
};

class SVGPolyline : public SVGElements {
public:
    std::vector<Point2D> ptsList;

    SVGPolyline(const std::vector<Point2D>& ptsList);
    void render(IRenderer* renderer) override;
};

class SVGPolygon : public SVGElements {
protected:
    std::vector<Point2D> ptsList;

public:
    SVGPolygon(const std::vector<Point2D>& ptsList);
    void render(IRenderer* renderer) override;
};

class SVGText : public SVGElements {
public:
    Point2D coordinates;
    std::string text;
    int fontSize;
    std::string typeface;
    std::string fontFilePath;

    SVGText(const Point2D& coordinates, const std::string& text, int fontSize, const std::string& typeface, const std::string& fontFilePath);
    void setText(const std::string& txt);
    void setFS(int size);
    void setTypeface(const std::string& typeface);
    void render(IRenderer* renderer) override;
};

class SVGGroup : public SVGElements {
public:
    void addChild(unique_ptr<SVGElements> child);
    void render(IRenderer* renderer) override;

private:
    vector<unique_ptr<SVGElements>>children;
};

enum class PathCommandType { MoveTo, LineTo, CubicBezier, QuadraticBezier, HorizontalLineTo, VerticalLineTo, ClosePath };

struct PathCommand {
    PathCommandType type;
    bool relative;
    std::vector<Point2D> points;
};

std::vector<PathCommand> parsePathData(const std::string& dStr);


class SVGPath: public SVGElements {
public:
    std::string d;
    std::vector<PathCommand> segments;

    SVGPath(const std::string& d);
    void setPathData(const std::string& d);
    void render(IRenderer* renderer) override;
};
#endif // ELEMENTS_H
