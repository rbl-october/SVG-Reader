#ifndef XML_PARSERS_WRAPPER_H
#define XML_PARSERS_WRAPPER_H

#include <string>
#include <vector>
#include "pugixml.hpp"

namespace SVGParser
{
    class XMLParserWrapper {
    private:
        pugi::xml_document m_doc;

    public:
        XMLParserWrapper();
        ~XMLParserWrapper();
       
        // Load XML document from file
        bool loadFile(const std::string& filePath);

        // Load XML document from strings in the memory
        bool loadString(const std::string& xmlString);

        // The original node of the doc
        pugi::xml_node getRootNode() const;

        // Properties as strings
        std::string getAttributeString(const pugi::xml_node& node, const std::string& attrName, const std::string& defaultValue = "") const;

        // Property values as floats
        float getAttributeFloat(const pugi::xml_node& node, const std::string& attrName, float defaultValue = 0.0f) const;

        // Colour value properties unsigned long RGBA
        unsigned long getAttributeColor(const pugi::xml_node& node, const std::string& attrName, unsigned long defaultValue = 0x000000FF) const;

        // Children of nodes in XML
        std::vector<pugi::xml_node> getChildNodes(const pugi::xml_node& node) const;
    };
} // namespace SVGParser

#endif // XML_PARSERS_WRAPPER_H