#include "elements.h"
#include "..\renderer\IRenderer.h"
#include <iostream>

Point2D::Point2D(float x, float y) : x(x), y(y) {}

SVGElements::~SVGElements() {}

void SVGElements::setDefaultFillColour(unsigned long colour) {
    fillColour = colour;
}

void SVGElements::setDefaultStrokeColour(unsigned long colour) {
    strokeColour = colour;
}

void SVGElements::setDefaultStrokeWidth(float width) {
    strokeWidth = width;
}

void SVGElements::setDefaultFillOpacity(float opacity) {
    fillOpacity = opacity;
}

void SVGElements::setDefaultStrokeOpacity(float opacity) {
    strokeOpacity = opacity;
}

void SVGElements::setTransform(const string& t)
{
    transformStr = t;
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

SVGText::SVGText(const Point2D& coord, const std::string& txt, int fs, const std::string& tf, const std::string&ffp)
    : coordinates(coord), text(txt), fontSize(fs), typeface(tf), fontFilePath(ffp) {}

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
    renderer->drawText(coordinates.x, coordinates.y, text, fontSize, typeface, fontFilePath);
}


std::vector<PathCommand> parsePathData(const std::string& dStr) {
    std::vector<PathCommand> segments;
    std::stringstream ss(dStr);
    char cmd;
    float x, y;
    bool relative;

    while (ss >> cmd) {
        relative = islower(cmd);
        PathCommandType type;

        switch (tolower(cmd)) {
        case 'm': type = PathCommandType::MoveTo; break;
        case 'l': type = PathCommandType::LineTo; break;
        case 'h': type = PathCommandType::HorizontalLineTo; break;
        case 'v': type = PathCommandType::VerticalLineTo; break;
        case 'c': type = PathCommandType::CubicBezier; break;
        case 'q': type = PathCommandType::QuadraticBezier; break;
        case 'z': case 'Z':
            segments.push_back({ PathCommandType::ClosePath, false, {} });
            continue;
        default:
            std::cerr << "Unsupported path command: " << cmd << "\n";
            continue;
        }

        PathCommand segment{ type, relative, {} };
        int ptsNeeded = (type == PathCommandType::CubicBezier) ? 3 :
            (type == PathCommandType::QuadraticBezier) ? 2 : 1;

        for (int i = 0; i < ptsNeeded; ++i) {
            ss >> x >> y;
            segment.points.push_back({ x, y });
        }

        segments.push_back(segment);
    }

    return segments;
}

SVGPath::SVGPath(const std::string& dStr) : d(dStr) {
    segments = parsePathData(dStr);
}

void SVGPath::setPathData(const std::string& dStr) {
    d = dStr;
    segments = parsePathData(dStr);
}

void SVGPath::render(IRenderer* renderer) {
    std::cout << "SVGPath fill: " << fillColour << ", stroke: " << strokeColour << std::endl;
    renderer->drawPath(segments, fillColour, strokeColour, fillOpacity, strokeOpacity, strokeWidth);
}


void SVGGroup::addChild(unique_ptr<SVGElements> child)
{
    children.push_back(move(child));
}

void SVGGroup::render(IRenderer* renderer)
{
    renderer->beginGroup();
    if (!transformStr.empty()) renderer->pushTransform(transformStr);
    for (auto& child : children) {
        child->render(renderer);
    }
    if (!transformStr.empty()) renderer->popTransform();
    renderer->endGroup();
}
