#ifndef SVG_PARSERS_H
#define SVG_PARSERS_H

#include <vector>
#include <string>
#include <memory> // For std::unique_ptr

#include "XML-ParsersWrapper.h"      // Bao gồm XMLParserWrapper
#include "../src/elements/elements.h"    // Bao gồm elements.h của bạn
#include "../renderer/IRenderer.h"       // Bao gồm IRenderer.h

namespace SVGParser
{
    class SVGParser {
    private:
        XMLParserWrapper m_xmlParser;
        std::vector<std::unique_ptr<SVGElements>> m_svgElements;

        // Helper to analyse common attributes of elements
        void parseCommonAttributes(const pugi::xml_node& xmlNode, SVGElements* svgElement);

        // Helper to analyse a string to a vector of Point2Ds
        std::vector<Point2D> parsePointsString(const std::string& pointsString);

        // Other helper to analyse and parse attributes
        std::unique_ptr<SVGElements> parseRectangleAttributes(const pugi::xml_node& xmlNode);
        std::unique_ptr<SVGElements> parseCircleAttributes(const pugi::xml_node& xmlNode);
        std::unique_ptr<SVGElements> parseEllipseAttributes(const pugi::xml_node& xmlNode);
        std::unique_ptr<SVGElements> parseLineAttributes(const pugi::xml_node& xmlNode);
        std::unique_ptr<SVGElements> parsePolylineAttributes(const pugi::xml_node& xmlNode);
        std::unique_ptr<SVGElements> parsePolygonAttributes(const pugi::xml_node& xmlNode);
        std::unique_ptr<SVGElements> parseTextAttributes(const pugi::xml_node& xmlNode);

        // To sort dispatches of elements
        std::unique_ptr<SVGElements> parseSVGElement(const pugi::xml_node& xmlNode);

    public:
        SVGParser();
        ~SVGParser();

        // To analyse the SVG doc from file/string
        bool parse(const std::string& source, bool isFilePath = true);

        // Take analysed vectors of SVGElements
        const std::vector<std::unique_ptr<SVGElements>>& getSVGElements() const;

        // Delete parsed elements
        void clearElements();
    };
} // namespace SVGParser

#endif // SVG_PARSERS_H