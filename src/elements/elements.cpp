#include "elements.h"
#include "..\renderer\IRenderer.h"
#include <iostream>

Point2D::Point2D(float x, float y) : x(x), y(y) {}

SVGElements::~SVGElements() {}

void SVGElements::setFillColour(unsigned long colour) {
    fillColour = colour;
}

void SVGElements::setStrokeColour(unsigned long colour) {
    strokeColour = colour;
}

void SVGElements::setStrokeWidth(float width) {
    strokeWidth = width;
}

SVGEllipse::SVGEllipse(const Point2D& c, float rx, float ry)
    : centre(c), radiusX(rx), radiusY(ry) {}

void SVGEllipse::setCentre(const Point2D& o) {
    centre = o;
}

void SVGEllipse::setRadii(float rX, float rY) {
    radiusX = rX;
    radiusY = rY;
}

void SVGEllipse::render(IRenderer* renderer) {
    int r, g, b, a;
    getRGBAFromULong(fillColour, r, g, b, a);
    renderer->setFillColor(r, g, b, a);
    getRGBAFromULong(strokeColour, r, g, b, a);
    renderer->setStrokeColor(r, g, b, a);
    renderer->setStrokeWidth(strokeWidth);
    renderer->drawEllipse(centre.x, centre.y, radiusX, radiusY);
}

SVGCircle::SVGCircle(const Point2D& c, float r)
    : SVGEllipse(c, r, r), radius(r) {}

void SVGCircle::setCentre(const Point2D& o) {
    centre = o;
}

void SVGCircle::setRadius(float r) {
    radius = r;
    radiusX = radiusY = r;
}

void SVGCircle::render(IRenderer* renderer) {
    int r, g, b, a;
    getRGBAFromULong(fillColour, r, g, b, a);
    renderer->setFillColor(r, g, b, a);
    getRGBAFromULong(strokeColour, r, g, b, a);
    renderer->setStrokeColor(r, g, b, a);
    renderer->setStrokeWidth(strokeWidth);
    renderer->drawCircle(centre.x, centre.y, radius);
}

SVGRectangle::SVGRectangle(const Point2D& tl, float len, float wid)
    : topLeft(tl), length(len), width(wid) {}

void SVGRectangle::setTopLeft(const Point2D& A) {
    topLeft = A;
}

void SVGRectangle::setWidthLength(float len, float wid) {
    length = len;
    width = wid;
}

void SVGRectangle::render(IRenderer* renderer) {
    int r, g, b, a;

    getRGBAFromULong(fillColour, r, g, b, a);
    renderer->setFillColor(r, g, b, a);
    getRGBAFromULong(strokeColour, r, g, b, a);
    renderer->setStrokeColor(r, g, b, a);
    renderer->setStrokeWidth(strokeWidth);
    renderer->drawRectangle(topLeft.x, topLeft.y, length, width);
}

SVGLine::SVGLine(const Point2D& p1, const Point2D& p2)
    : pointStart(p1), pointEnd(p2) {}

void SVGLine::setLine(const Point2D& p1, const Point2D& p2) {
    pointStart = p1;
    pointEnd = p2;
}

void SVGLine::render(IRenderer* renderer) {
    int r, g, b, a;
    getRGBAFromULong(fillColour, r, g, b, a);
    renderer->setFillColor(r, g, b, a);
    getRGBAFromULong(strokeColour, r, g, b, a);
    renderer->setStrokeColor(r, g, b, a);
    renderer->setStrokeWidth(strokeWidth);
    renderer->drawLine(pointStart, pointEnd);
}

SVGPolyline::SVGPolyline(const std::vector<Point2D>& pts)
    : ptsList(pts) {}

void SVGPolyline::render(IRenderer* renderer) {
    int r, g, b, a;
    getRGBAFromULong(fillColour, r, g, b, a);
    renderer->setFillColor(r, g, b, a);
    getRGBAFromULong(strokeColour, r, g, b, a);
    renderer->setStrokeColor(r, g, b, a);
    renderer->drawPolyline(ptsList);
}

SVGPolygon::SVGPolygon(const std::vector<Point2D>& pts)
    : ptsList(pts) {}

void SVGPolygon::render(IRenderer* renderer) {
    int r, g, b, a;
    getRGBAFromULong(fillColour, r, g, b, a);
    renderer->setFillColor(r, g, b, a);
    getRGBAFromULong(strokeColour, r, g, b, a);
    renderer->setStrokeColor(r, g, b, a);
    renderer->drawPolygon(ptsList);
}

SVGText::SVGText(const Point2D& coord, const std::string& txt, int fs, const std::string& tf)
    : coordinates(coord), text(txt), fontSize(fs), typeface(tf) {}

void SVGText::setText(const std::string& txt) {
    text = txt;
}

void SVGText::setFS(int size) {
    fontSize = size;
}

void SVGText::setTypeface(const std::string& tf) {
    typeface = tf;
}

void SVGText::render(IRenderer* renderer) {
    int r, g, b, a;
    getRGBAFromULong(fillColour, r, g, b, a);
    renderer->setFillColor(r, g, b, a);
    renderer->drawText(coordinates.x, coordinates.y, text, fontSize, typeface);
}

void getRGBAFromULong(unsigned long colour, int& r, int& g, int& b, int& a)
{
    r = (colour >> 24) & 0xFF;
    g = (colour >> 16) & 0xFF;
    b = (colour >> 8) & 0xFF;
    a = colour & 0xFF;
}
