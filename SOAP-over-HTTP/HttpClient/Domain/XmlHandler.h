#pragma once

#include <iostream>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <vector>

namespace Domain {

class XmlHandler : public xercesc::DefaultHandler {

private:

    struct XmlElementInfo{
        template<typename ElementName_TYPE, typename ElementValue_Type>
        XmlElementInfo(ElementName_TYPE&& name, ElementValue_Type&& value) :
            m_elementName{std::forward<ElementName_TYPE>(name)},
            m_elementValue{std::forward<ElementValue_Type>(value)}{
        }
        std::string m_elementName;
        std::string m_elementValue;
    };

    // Overriding startElement and endElement to handle XML elements
    void startElement(const XMLCh* const uri,
                      const XMLCh* const localName,
                      const XMLCh* const qname,
                      const xercesc::Attributes& attrs) override;

    void endElement(const XMLCh* const uri,
                    const XMLCh* const localName,
                    const XMLCh* const qname) override;

    // Override characters() to handle character data
    void characters(const XMLCh* const chars,
                    const XMLSize_t length) override;

public:
    std::vector<XmlElementInfo> m_xmlElementsVector;
    std::string m_currentElement;
    std::string m_currentValue;
};

} // Domain
