#include <iostream>
#include "SVGRenderer.h"
#include "SFMLRenderer.h"

using namespace std;
int main()
{
    // SVG Renderer
    SVGRenderer svg;
    svg.initialize(800, 600);
    svg.setFillColor(255, 0, 0);
    svg.drawCircle(200, 200, 50);
    svg.setFillColor(0, 255, 0);
    svg.drawSquare(400, 300, 100);
    svg.setFillColor(0, 0, 255);
    svg.drawTriangle(100, 500, 300, 500, 200, 300);
    svg.setFillColor(255, 255, 0);
    svg.drawEllipse(600, 400, 80, 40);
    svg.saveToFile("image/example.svg");

    // SFML Renderer
    SFMLRenderer sfml;
    sfml.initialize(800, 600);
    sfml.setFillColor(255, 0, 0, 255);
    sfml.drawCircle(200, 200, 50);
    sfml.setFillColor(0, 255, 0, 255);
    sfml.drawSquare(400, 300, 100);
    sfml.setFillColor(0, 0, 255, 255);
    sfml.drawTriangle(100, 500, 300, 500, 200, 300);
    sfml.setFillColor(255, 255, 0, 255);
    sfml.drawEllipse(600, 400, 80, 40);
    sfml.saveToFile("image/shapes.png");

    cout << "Rendered shapes to SVG and PNG files" << endl;
    return 0;
}
