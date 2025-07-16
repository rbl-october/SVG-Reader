#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <string>
#include <vector>

class IRenderer;

void getRGBAFromULong(unsigned long colour, int& r, int& g, int& b, int& a);

struct Point2D {
    float x, y;
    Point2D(float x = 0, float y = 0);
};

class SVGElements {
public:
    unsigned long fillColour, strokeColour;
    float fillOpacity, strokeOpacity;
    float strokeWidth;

    virtual ~SVGElements();
    virtual void render(IRenderer* renderer) = 0;

    void setFillColour(unsigned long colour);
    void setStrokeColour(unsigned long colour);
    void setStrokeWidth(float width);
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

    SVGText(const Point2D& coordinates, const std::string& text, int fontSize, const std::string& typeface);
    void setText(const std::string& txt);
    void setFS(int size);
    void setTypeface(const std::string& typeface);
    void render(IRenderer* renderer) override;
};

#endif // ELEMENTS_H
