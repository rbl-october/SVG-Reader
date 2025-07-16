#include "SVG-Parsers.h"

#include <iostream>
#include <sstream>
#include <algorithm> // For std::remove
#include <map>       // For named colours in parseColorString (if used)

// Using declarations to simplify code within the namespace
using pugi::xml_node;
using pugi::xml_attribute;

namespace SVGParser
{
    // Helper function to trim whitespace from a string
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r\f\v");
        if (std::string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(first, (last - first + 1));
    }

    SVGParser::SVGParser() {}

    SVGParser::~SVGParser() {
        clearElements();
    }

    bool SVGParser::parse(const std::string& source, bool isFilePath) {
        clearElements(); // Clear elements before parsing

        bool success = false;
        if (isFilePath) {
            success = m_xmlParser.loadFile(source);
        }
        else {
            success = m_xmlParser.loadString(source);
        }

        if (!success) {
            return false;
        }

        xml_node svgNode = m_xmlParser.getRootNode();
        if (!svgNode) {
            std::cerr << "SVGParser: Could not find root <svg> element." << std::endl;
            return false;
        }

        for (xml_node child : svgNode.children()) {
            std::unique_ptr<SVGElements> element = parseSVGElement(child);
            if (element) {
                m_svgElements.push_back(std::move(element));
            }
        }
        return true;
    }

    const std::vector<std::unique_ptr<SVGElements>>& SVGParser::getSVGElements() const {
        return m_svgElements;
    }

    void SVGParser::clearElements() {
        m_svgElements.clear(); // std::unique_ptr automatically clears the memory
    }

    void SVGParser::parseCommonAttributes(const xml_node& xmlNode, SVGElements* svgElement) {
        // Colour & opacity
        svgElement->setFillColour(m_xmlParser.getAttributeColor(xmlNode, "fill", 0x000000FF)); // Default black
        svgElement->setStrokeColour(m_xmlParser.getAttributeColor(xmlNode, "stroke", 0x00000000)); // Default transparent (no stroke)

        // Opacity is an attribute
        // SVG Spec: fill-opacity and stroke-opacity is a float, ranging from 0-1
        svgElement->fillOpacity = m_xmlParser.getAttributeFloat(xmlNode, "fill-opacity", 1.0f);
        svgElement->strokeOpacity = m_xmlParser.getAttributeFloat(xmlNode, "stroke-opacity", 1.0f);

        // Width of stroke
        svgElement->setStrokeWidth(m_xmlParser.getAttributeFloat(xmlNode, "stroke-width", 0.0f));
    }

    std::vector<Point2D> SVGParser::parsePointsString(const std::string& pointsString) {
        std::vector<Point2D> points;
        std::stringstream ss(pointsString);
        std::string segment;

        while (std::getline(ss, segment, ' ')) {
            std::string cleaned_segment = trim(segment); // Trim whitespace
            if (cleaned_segment.empty()) continue;

            std::replace(cleaned_segment.begin(), cleaned_segment.end(), ',', ' '); // Replace comma with space
            std::stringstream ss_point(cleaned_segment);
            float x, y;
            if (ss_point >> x >> y) {
                points.push_back(Point2D(x, y));
            }
            else {
                std::cerr << "SVGParser: Warning - Invalid point format in points string: " << segment << std::endl;
            }
        }
        return points;
    }

    std::unique_ptr<SVGElements> SVGParser::parseRectangleAttributes(const xml_node& xmlNode) {
        float x = m_xmlParser.getAttributeFloat(xmlNode, "x", 0.0f);
        float y = m_xmlParser.getAttributeFloat(xmlNode, "y", 0.0f);
        float width = m_xmlParser.getAttributeFloat(xmlNode, "width", 0.0f);
        float height = m_xmlParser.getAttributeFloat(xmlNode, "height", 0.0f); // elements.h dùng 'length'

        auto rect = std::make_unique<SVGRectangle>(Point2D(x, y), height, width);
        parseCommonAttributes(xmlNode, rect.get());
        return rect;
    }

    std::unique_ptr<SVGElements> SVGParser::parseCircleAttributes(const xml_node& xmlNode) {
        float cx = m_xmlParser.getAttributeFloat(xmlNode, "cx", 0.0f);
        float cy = m_xmlParser.getAttributeFloat(xmlNode, "cy", 0.0f);
        float r = m_xmlParser.getAttributeFloat(xmlNode, "r", 0.0f);

        auto circle = std::make_unique<SVGCircle>(Point2D(cx, cy), r);
        parseCommonAttributes(xmlNode, circle.get());
        return circle;
    }

    std::unique_ptr<SVGElements> SVGParser::parseEllipseAttributes(const xml_node& xmlNode) {
        float cx = m_xmlParser.getAttributeFloat(xmlNode, "cx", 0.0f);
        float cy = m_xmlParser.getAttributeFloat(xmlNode, "cy", 0.0f);
        float rx = m_xmlParser.getAttributeFloat(xmlNode, "rx", 0.0f);
        float ry = m_xmlParser.getAttributeFloat(xmlNode, "ry", 0.0f);

        auto ellipse = std::make_unique<SVGEllipse>(Point2D(cx, cy), rx, ry);
        parseCommonAttributes(xmlNode, ellipse.get());
        return ellipse;
    }

    std::unique_ptr<SVGElements> SVGParser::parseLineAttributes(const xml_node& xmlNode) {
        float x1 = m_xmlParser.getAttributeFloat(xmlNode, "x1", 0.0f);
        float y1 = m_xmlParser.getAttributeFloat(xmlNode, "y1", 0.0f);
        float x2 = m_xmlParser.getAttributeFloat(xmlNode, "x2", 0.0f);
        float y2 = m_xmlParser.getAttributeFloat(xmlNode, "y2", 0.0f);

        auto line = std::make_unique<SVGLine>(Point2D(x1, y1), Point2D(x2, y2));
        parseCommonAttributes(xmlNode, line.get());
        return line;
    }

    std::unique_ptr<SVGElements> SVGParser::parsePolylineAttributes(const xml_node& xmlNode) {
        std::string pointsStr = m_xmlParser.getAttributeString(xmlNode, "points");
        std::vector<Point2D> points = parsePointsString(pointsStr);

        auto polyline = std::make_unique<SVGPolyline>(points);
        parseCommonAttributes(xmlNode, polyline.get());
        return polyline;
    }

    std::unique_ptr<SVGElements> SVGParser::parsePolygonAttributes(const xml_node& xmlNode) {
        std::string pointsStr = m_xmlParser.getAttributeString(xmlNode, "points");
        std::vector<Point2D> points = parsePointsString(pointsStr);

        auto polygon = std::make_unique<SVGPolygon>(points);
        parseCommonAttributes(xmlNode, polygon.get());
        return polygon;
    }

    std::unique_ptr<SVGElements> SVGParser::parseTextAttributes(const xml_node& xmlNode) {
        float x = m_xmlParser.getAttributeFloat(xmlNode, "x", 0.0f);
        float y = m_xmlParser.getAttributeFloat(xmlNode, "y", 0.0f);
        std::string textContent = xmlNode.text().get(); // Lấy nội dung văn bản bên trong thẻ
        int fontSize = static_cast<int>(m_xmlParser.getAttributeFloat(xmlNode, "font-size", 16.0f)); // Default font size
        std::string typeface = m_xmlParser.getAttributeString(xmlNode, "font-family", "Arial"); // Default font family

        auto text = std::make_unique<SVGText>(Point2D(x, y), textContent, fontSize, typeface);
        parseCommonAttributes(xmlNode, text.get());
        return text;
    }

    std::unique_ptr<SVGElements> SVGParser::parseSVGElement(const xml_node& xmlNode) {
        std::string nodeName = xmlNode.name();

        if (nodeName == "rect") {
            return parseRectangleAttributes(xmlNode);
        }
        else if (nodeName == "circle") {
            return parseCircleAttributes(xmlNode);
        }
        else if (nodeName == "ellipse") {
            return parseEllipseAttributes(xmlNode);
        }
        else if (nodeName == "line") {
            return parseLineAttributes(xmlNode);
        }
        else if (nodeName == "polyline") {
            return parsePolylineAttributes(xmlNode);
        }
        else if (nodeName == "polygon") {
            return parsePolygonAttributes(xmlNode);
        }
        else if (nodeName == "text") {
            return parseTextAttributes(xmlNode);
        }
        // Add more SVG refs if needed

        std::cerr << "SVGParser: Warning - Unhandled SVG element: " << nodeName << std::endl;
        return nullptr;
    }
} // namespace SVGParser