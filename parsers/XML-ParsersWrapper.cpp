#include "XML-ParsersWrapper.h"
#include <iostream>
#include <sstream>

namespace SVGParser
{
    XMLParserWrapper::XMLParserWrapper() {}

    XMLParserWrapper::~XMLParserWrapper() {}

    bool XMLParserWrapper::loadFile(const std::string& filePath) {
        pugi::xml_parse_result result = m_doc.load_file(filePath.c_str());
        if (!result) {
            std::cerr << "XMLParserWrapper: Failed to load XML file: " << filePath << ". Error: " << result.description() << std::endl;
            return false;
        }
        return true;
    }

    bool XMLParserWrapper::loadString(const std::string& xmlString) {
        pugi::xml_parse_result result = m_doc.load_string(xmlString.c_str());
        if (!result) {
            std::cerr << "XMLParserWrapper: Failed to load XML string. Error: " << result.description() << std::endl;
            return false;
        }
        return true;
    }

    pugi::xml_node XMLParserWrapper::getRootNode() const {
        return m_doc.child("svg"); // The original element is SVG
    }

    std::string XMLParserWrapper::getAttributeString(const pugi::xml_node& node, const std::string& attrName, const std::string& defaultValue) const {
        return node.attribute(attrName.c_str()).as_string(defaultValue.c_str());
    }

    float XMLParserWrapper::getAttributeFloat(const pugi::xml_node& node, const std::string& attrName, float defaultValue) const {
        return node.attribute(attrName.c_str()).as_float(defaultValue);
    }

    // Directly reads the colour in unsigned long form. Whenever try to read, use "0x" + the RGB-A code in hex form.
    unsigned long XMLParserWrapper::getAttributeColor(const pugi::xml_node& node, const std::string& attrName, unsigned long defaultValue) const {
        return node.attribute(attrName.c_str()).as_uint(defaultValue);
    }

    std::vector<pugi::xml_node> XMLParserWrapper::getChildNodes(const pugi::xml_node& node) const {
        std::vector<pugi::xml_node> children;
        for (pugi::xml_node child : node.children()) {
            children.push_back(child);
        }
        return children;
    }
} // namespace SVGParser