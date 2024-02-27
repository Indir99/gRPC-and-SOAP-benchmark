#include "SoapMessageCreator.h"

namespace Domain {

void InitializeLibrary(){
    xercesc::XMLPlatformUtils::Initialize();
}

void DeinitializeLibrary(){
    xercesc::XMLPlatformUtils::Terminate();
}

std::string PrepareSimpleSoapMessage() {
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);

    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);

    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);

    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);

    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    // Create a child element
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);

    xercesc::DOMElement* Probe = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:Probe"));
    Body->appendChild(Probe);

    xercesc::DOMElement* ProbeType = xmlDoc->createElement(xercesc::XMLString::transcode("mb:Type"));
    Probe->appendChild(ProbeType);

    xercesc::DOMText* TypeName = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceName));
    ProbeType->appendChild(TypeName);

    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);

        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};

        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

} // Domain
