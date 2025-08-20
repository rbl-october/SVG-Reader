#include <iostream>
#include "SVGRenderer.h"
#include "SFMLRenderer.h"

using namespace std;
int main()
{
	SVGRenderer svg;
	svg.initialize(800, 600);

	svg.drawLinearGradient("grad1", { 0, 0 }, { 100, 0 }, {
		{0.0f, "#ff0000"},
		{1.0f, "#0000ff"}
		});


	svg.setFillGradient("grad1");
	svg.setStrokeColor(0, 0, 0, 255);
	svg.setStrokeWidth(3.0f);

	svg.drawRectangle(50, 50, 200, 100);

	svg.setFillColor(140, 175, 200); // nền chung
	svg.saveToFile("../image/example.svg");
	
	std::cout << "Rendered all shapes to SVG and PNG files" << endl;

}
