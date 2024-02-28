#include "XmlHandler.h"

namespace Domain {

void XmlHandler::startElement(const XMLCh* const uri,
                              const XMLCh* const localName,
                              const XMLCh* const qname,
                              const xercesc::Attributes& attrs)
{
    // Convert XMLCh strings to char strings for printing
    char* uriStr = xercesc::XMLString::transcode(uri);
    char* localNameStr = xercesc::XMLString::transcode(localName);
    char* qnameStr = xercesc::XMLString::transcode(qname);

    m_currentElement = qnameStr;

    // Print attributes, if any
    for (XMLSize_t i = 0; i < attrs.getLength(); ++i) {
        char* attrName = xercesc::XMLString::transcode(attrs.getLocalName(i));
        char* attrValue = xercesc::XMLString::transcode(attrs.getValue(i));
        //std::cout << "  Attribute: " << attrName << " = " << attrValue << std::endl;
        xercesc::XMLString::release(&attrName);
        xercesc::XMLString::release(&attrValue);
    }

    // Release memory
    xercesc::XMLString::release(&uriStr);
    xercesc::XMLString::release(&localNameStr);
    xercesc::XMLString::release(&qnameStr);
}

void XmlHandler::endElement(const XMLCh* const uri,
                            const XMLCh* const localName,
                            const XMLCh* const qname)
{
    char* uriStr = xercesc::XMLString::transcode(uri);
    char* localNameStr = xercesc::XMLString::transcode(localName);
    char* qnameStr = xercesc::XMLString::transcode(qname);

    xercesc::XMLString::release(&uriStr);
    xercesc::XMLString::release(&localNameStr);
    xercesc::XMLString::release(&qnameStr);
}

void XmlHandler::characters(const XMLCh* const chars,
                            const XMLSize_t length)
{
    char* charData = xercesc::XMLString::transcode(chars);
    m_currentValue = charData;
    m_xmlElementsVector.emplace_back(std::move(m_currentElement), std::move(m_currentValue));
    xercesc::XMLString::release(&charData);
}

}
