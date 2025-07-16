// src/SFMLRenderer.cpp
#include "SFMLRenderer.h"
#include <cmath>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void SFMLRenderer::initialize(int width, int height) {
    renderTexture.create(width, height);
    renderTexture.clear(sf::Color::White);
    fillColor = sf::Color::Black;
    strokeColor = sf::Color::Black;
    strokeWidth = 1.0f;
    renderTexture.display();

}

void SFMLRenderer::drawCircle(float x, float y, float radius)
{
    drawEllipseShape(x, y, radius, radius);
}

void SFMLRenderer::drawSquare(float x, float y, float size)
{
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(x, y);
    square.setFillColor(fillColor);
    square.setOutlineColor(strokeColor);
    square.setOutlineThickness(strokeWidth);
    renderTexture.draw(square);
}

void SFMLRenderer::drawRectangle(float x, float y, float width, float height)
{
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(fillColor);
    rect.setOutlineColor(strokeColor);
    rect.setOutlineThickness(strokeWidth);
    renderTexture.draw(rect);
}

void SFMLRenderer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(x1, y1));
    triangle.setPoint(1, sf::Vector2f(x2, y2));
    triangle.setPoint(2, sf::Vector2f(x3, y3));
    triangle.setFillColor(fillColor);
    triangle.setOutlineColor(strokeColor);
    triangle.setOutlineThickness(strokeWidth);
    renderTexture.draw(triangle);
}

void SFMLRenderer::drawEllipse(float centerX, float centerY, float radiusX, float radiusY)
{
    drawEllipseShape(centerX, centerY, radiusX, radiusY);
}

void SFMLRenderer::drawLine(const Point2D& p1, const Point2D& p2)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(p1.x, p1.y), strokeColor),
        sf::Vertex(sf::Vector2f(p2.x, p2.y), strokeColor)
    };
    renderTexture.draw(line, 2, sf::Lines);
}

void SFMLRenderer::drawEllipseShape(float centerX, float centerY, float radiusX, float radiusY)
{
    // SFML không có ellipse shape mặc định nên phải tạo xấp xỉ
    const int pointCount = 30;
    sf::ConvexShape ellipse;
    ellipse.setPointCount(pointCount);

    for (int i = 0; i < pointCount; ++i)
    {
        float angle = 2 * M_PI * i / pointCount;
        float x = centerX + radiusX * cos(angle);
        float y = centerY + radiusY * sin(angle);
        ellipse.setPoint(i, sf::Vector2f(x, y));
    }

    ellipse.setFillColor(fillColor);
    ellipse.setOutlineColor(strokeColor);
    ellipse.setOutlineThickness(strokeWidth);
    renderTexture.draw(ellipse);
}

void SFMLRenderer::drawPolyline(const std::vector<Point2D>& points)
{
    if (points.size() < 2) return;

    sf::VertexArray polyline(sf::LinesStrip, points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        polyline[i].position = sf::Vector2f(points[i].x, points[i].y);
        polyline[i].color = strokeColor;
    }
    renderTexture.draw(polyline);
}

void SFMLRenderer::drawPolygon(const std::vector<Point2D>& points)
{
    if (points.size() < 3) return;

    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
    }
    polygon.setFillColor(fillColor);
    polygon.setOutlineColor(strokeColor);
    polygon.setOutlineThickness(strokeWidth);
    renderTexture.draw(polygon);
}

void SFMLRenderer::drawText(float x, float y, const std::string& textContent, int fontSize, const std::string& typeface)
{
    static sf::Font font;
    if (!font.loadFromFile("Dense.ttf"))
    {
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(textContent);
    text.setCharacterSize(fontSize);
    text.setFillColor(fillColor);
    text.setOutlineColor(strokeColor);
    text.setOutlineThickness(strokeWidth);
    text.setPosition(x, y);
    renderTexture.draw(text);
}

void SFMLRenderer::setFillColor(int r, int g, int b, int a) {
    fillColor = sf::Color(r, g, b, a);
}
void SFMLRenderer::setStrokeColor(int r, int g, int b, int a) {
    strokeColor = sf::Color(r, g, b, a);
}
void SFMLRenderer::setStrokeWidth(float width) {
    strokeWidth = width;
}

void SFMLRenderer::saveToFile(const std::string &filepath) {
    sf::Texture texture = renderTexture.getTexture();
    sf::Image image = texture.copyToImage();
    if (!image.saveToFile(filepath)) {
        throw std::runtime_error("Failed to save image to file: " + filepath);
    }
}