#include "ColorUtils.h"


unsigned long parseColorString(const std::string& str, unsigned long fallback)
{
    // Handle hex: "#rrggbb"
    if (str[0] == '#' && (str.length() == 7 || str.length() == 4)) {
        unsigned int r = 0, g = 0, b = 0;
        if (str.length() == 7) {
            std::stringstream ss;
            ss << std::hex << str.substr(1, 2); ss >> r;
            ss.clear(); ss.str(""); ss << std::hex << str.substr(3, 2); ss >> g;
            ss.clear(); ss.str(""); ss << std::hex << str.substr(5, 2); ss >> b;
        }
        else {
            r = std::stoi(str.substr(1, 1), nullptr, 16) * 17;
            g = std::stoi(str.substr(2, 1), nullptr, 16) * 17;
            b = std::stoi(str.substr(3, 1), nullptr, 16) * 17;
        }
        return (r << 24) | (g << 16) | (b << 8) | 0xFF;
    }

    // Handle rgb(...) syntax
    std::regex rgbRegex(R"(rgb\s*\(\s*(\d+)[,\s]+(\d+)[,\s]+(\d+)\s*\))");
    std::smatch match;
    if (std::regex_match(str, match, rgbRegex)) {
        int r = std::stoi(match[1]);
        int g = std::stoi(match[2]);
        int b = std::stoi(match[3]);
        return (r << 24) | (g << 16) | (b << 8) | 0xFF;
    }

    // Handle named colours (e.g., "red", "black")
    static std::unordered_map<std::string, unsigned long> namedColours = {
        {"black", 0x000000FF}, {"white", 0xFFFFFFFF}, {"red", 0xFF0000FF},
        {"green", 0x00FF00FF}, {"blue", 0x0000FFFF}, {"yellow", 0xFFFF00FF},
        {"cyan", 0x00FFFFFF}, {"magenta", 0xFF00FFFF}
        // ... add more as needed
    };

    auto it = namedColours.find(str);
    if (it != namedColours.end()) return it->second;

    // Unknown format → return fallback
    return fallback;
}

void getRGBAFromULong(unsigned long colour, int& r, int& g, int& b, int& a)
{

    r = (colour >> 24) & 0xFF;
    g = (colour >> 16) & 0xFF;
    b = (colour >> 8) & 0xFF;
    a = colour & 0xFF;
}

std::string rgbaToSVGColour(unsigned long colour)
{
    int r, g, b, a;
    getRGBAFromULong(colour, r, g, b, a);

    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}

std::string rgbtoHex(int r, int g, int b, int a)
{
    std::stringstream ss;
    ss << "#" << std::hex << std::setfill('0')
        << std::setw(2) << r
        << std::setw(2) << g
        << std::setw(2) << b;
    // Only append alpha if it's not fully opaque
    if (a < 255)
    {
        ss << std::setw(2) << a;
    }
    return ss.str();
}

std::string rgbaToHex(unsigned long colour)
{
    int r, g, b, a;
    getRGBAFromULong(colour, r, g, b, a);
    return rgbtoHex(r, g, b, a);
}