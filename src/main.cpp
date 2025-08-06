#include <iostream>
#include "SVGRenderer.h"
#include "SFMLRenderer.h"

using namespace std;
int main()
{
	// SVG Renderer
	SVGRenderer svg;
	svg.initialize(800, 600);
	
/*
	// A rectangle with a yellow star
	svg.setFillColor(218, 37, 29);
	svg.drawRectangle(150, 150, 720, 480);

	svg.setFillColor(255, 255, 0);
	svg.drawPolygon({
	{400.0f, 200.0f},  // 0 - top (outer)
	{423.5f, 261.8f},  // 1 - inner
	{490.2f, 261.8f},  // 2 - outer
	{438.2f, 305.1f},  // 3 - inner
	{454.1f, 376.4f},  // 4 - outer
	{400.0f, 336.4f},  // 5 - inner
	{345.9f, 376.4f},  // 6 - outer
	{361.8f, 305.1f},  // 7 - inner
	{309.8f, 261.8f},  // 8 - outer
	{376.5f, 261.8f}   // 9 - inner
		});
*/
/*	// A Venn diagram

	svg.setFillColor(255, 255, 255);
	svg.setStrokeColor(16, 16, 16);
	svg.setFillOpacity(0.0f);

	svg.drawRectangle(210, 140, 400, 300); // Step 1: Draw the outline for the rect

	svg.setFillColor(255, 0, 0);
	svg.setStrokeColor(16, 16, 16);
	svg.setFillOpacity(0.25f);

	svg.drawCircle(400, 300, 100); // Step 2: Draw the red circle

	svg.setFillColor(0, 255, 0);
	svg.setStrokeColor(16, 16, 16);
	svg.setFillOpacity(0.25f);

	svg.drawCircle(450, 300, 100); // Step 2: Draw the green circle

	svg.setFillColor(0, 0, 255);
	svg.setStrokeColor(16, 16, 16);
	svg.setFillOpacity(0.25f);

	svg.drawCircle(425, 340, 100); // Step 2: Draw the blue circle

	svg.setFillColor(16, 16, 16);
	svg.setStrokeWidth(0);
	svg.drawText(225, 180, "Tribute to John Venn", 16, "Dense", "../image/Dense.ttf");
*/
/*	// A cubic Bézier
	svg.setStrokeColor(255, 0, 0);
	svg.setStrokeWidth(4.0f);
	svg.setFillOpacity(0);
	svg.drawLine({100, 300}, {200, 100}); // Red line #1

	svg.setStrokeColor(255, 0, 0);
	svg.setStrokeWidth(4.0f);
	svg.setFillOpacity(0);
	svg.drawLine({ 200, 100 }, { 300, 300 }); // Red line #2

	svg.setStrokeColor(0, 255, 0);
	svg.setStrokeWidth(4.0f);
	svg.setFillOpacity(0);
	svg.drawLine({ 150, 200 }, { 250, 200 }); // Green line

	svg.setStrokeColor(0, 0, 255);
	svg.setStrokeWidth(4.0f);
	svg.setFillOpacity(0);
	svg.drawPath("M 100 300 C 150 200 250 200 300 300"); // The curve itself
*/
/*
	// A snowman
	svg.setStrokeColor(16, 16, 16);
	svg.setStrokeWidth(2);
	svg.setFillColor(236, 236, 236);
	svg.drawCircle(250, 200, 100); // His body

	svg.setStrokeColor(16, 16, 16);
	svg.setStrokeWidth(2);
	svg.setFillColor(236, 236, 236);
	svg.drawCircle(250, 400, 150); // His head

	svg.setStrokeColor(16, 16, 16);
	svg.setStrokeWidth(2);
	svg.setFillColor(240, 81, 33);
	svg.drawTriangle(250, 190, 180, 200, 250, 210); // His carrot nose

	svg.setStrokeColor(16, 16, 16);
	svg.setStrokeWidth(2);
	svg.setFillColor(255,255,255);
	svg.drawCircle(215, 170, 10); // His left eye

	svg.setStrokeColor(16, 16, 16);
	svg.setStrokeWidth(2);
	svg.setFillColor(255, 255, 255);
	svg.drawCircle(265, 170, 10); // His right eye
*/



	svg.setFillColor(140, 175, 200); // nền chung
	svg.saveToFile("../image/example.svg");
	
	std::cout << "Rendered all shapes to SVG and PNG files" << std::endl;

}
