#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <regex>
#include <unordered_map>

// Chuyển chuỗi màu SVG thành unsigned long kiểu 0xRRGGBBAA
unsigned long parseColorString(const std::string& str, unsigned long fallback = 0x000000FF);

// Nếu cần: các hàm đã có
void getRGBAFromULong(unsigned long colour, int& r, int& g, int& b, int& a);
std::string rgbaToSVGColour(unsigned long colour);
std::string rgbaToHex(unsigned long colour);
std::string rgbtoHex(int r, int g, int b, int a = 255);

#endif // COLOR_UTILS_H
