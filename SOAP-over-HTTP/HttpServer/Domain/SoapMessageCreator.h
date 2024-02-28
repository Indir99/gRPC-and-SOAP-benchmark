#pragma once

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>

namespace Domain {

constexpr char ThisDeviceAddress[]{"http://127.0.0.1:38876"};
constexpr char ThisDeviceName[]{"Https-Client-For-Testing"};

constexpr char SoapNameSpaceUri[]{"http://soap-example.com/namespace"};
constexpr char WsAddressingUri[]{"http://soap-example.com/addressing"};
constexpr char BodyUri[]{"http://soap-example.com/bodycontent"};
constexpr char SoapEnvelopeName[]{"soap:Envelope"};
constexpr char SoapHeaderName[]{"soap:Header"};
constexpr char SoapBodyName[]{"soap:Body"};
constexpr char AddressName[]{"wsa:Address"};
constexpr char ToName[]{"wsa:To"};

void InitializeLibrary();
void DeinitializeLibrary();

std::string PrepareProbeMessage();
std::string PrepareProbeMatchMessage();

} // Domain
