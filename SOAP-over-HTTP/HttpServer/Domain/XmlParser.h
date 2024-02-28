#pragma once

#include "XmlHandler.h"
#include "XmlStructures.h"
#include "SoapMessageCreator.h"
#include <xercesc/framework/MemBufInputSource.hpp>
#include <memory>

namespace Domain {

class XmlParser{
public:
    XmlParser();

    void ParseMessage(std::string_view message);

    static void ParseXmlMessage(std::string_view message);

    void PrintParsedElements();

    template<typename T>
    void GetHeaderData(T& data);

    void GetProbeMatchData(ProbeMatchData& probe);

    void GetProbeData(ProbeData& probe);

private:
    std::unique_ptr<XmlHandler> m_handlerPtr;
    std::unique_ptr<xercesc::SAX2XMLReader> m_parserPtr;
};

} // ApplicationLogic
