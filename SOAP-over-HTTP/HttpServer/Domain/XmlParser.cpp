#include "XmlParser.h"

namespace Domain {

XmlParser::XmlParser() {
    m_handlerPtr = std::make_unique<XmlHandler>();
    m_parserPtr = std::unique_ptr<xercesc::SAX2XMLReader>(xercesc::XMLReaderFactory::createXMLReader());
    m_parserPtr->setContentHandler(m_handlerPtr.get());
    m_parserPtr->setErrorHandler(m_handlerPtr.get());
}

void XmlParser::ParseMessage(std::string_view message){
    // Create a MemBufInputSource from the string
    std::unique_ptr<xercesc::MemBufInputSource> inputSource(new xercesc::MemBufInputSource(
        reinterpret_cast<const XMLByte*>(message.data()), message.size(), "xmlData", false));
    m_parserPtr->parse(*inputSource);
}
void XmlParser::ParseXmlMessage(std::string_view message) {
    XmlParser parser;
    parser.ParseMessage(message);
}

void XmlParser::PrintParsedElements(){
    std::cout<<" Parsred elements: "<<std::endl;
    for(const auto& element : m_handlerPtr->m_xmlElementsVector){
        std::cout<<"Element: "<< element.m_elementName<<", Value: "<< element.m_elementValue<<std::endl;
    }
}
template<typename T>
void XmlParser::GetHeaderData(T& data){
    for(const auto& element : m_handlerPtr->m_xmlElementsVector){
        if(element.m_elementName == AddressName){
            data.header.senderAddress = element.m_elementValue;
        }
        else if(element.m_elementName == ToName) {
            data.header.receiverAddress = element.m_elementValue;
        }
    }
}

void XmlParser::GetProbeData(ProbeData& probe){
    GetHeaderData(probe);
    for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
        if(element.m_elementName == "mb:Type") {
            probe.deviceName = element.m_elementValue;
        }
    }
}

void XmlParser::GetProbeMatchData(ProbeMatchData& probe){
    GetHeaderData(probe);
    for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
        if(element.m_elementName == "mb:Type") {
            probe.deviceName = element.m_elementValue;
        }
    }
}

} // Domain
