#include "SoapMessageCreator.h"
#include <chrono>

namespace Domain {

void InitializeLibrary(){
    xercesc::XMLPlatformUtils::Initialize();
}

void DeinitializeLibrary(){
    xercesc::XMLPlatformUtils::Terminate();
}

std::string PrepareProbeMessage() {
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

std::string PrepareProbeMatchMessage(){
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

    xercesc::DOMElement* ProbeMatch = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                              xercesc::XMLString::transcode("mb:ProbeMatch"));
    Body->appendChild(ProbeMatch);

    xercesc::DOMElement* ProbeMatchType = xmlDoc->createElement(xercesc::XMLString::transcode("mb:Type"));
    ProbeMatch->appendChild(ProbeMatchType);

    xercesc::DOMText* TypeName = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceName));
    ProbeMatchType->appendChild(TypeName);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);

        //std::cout << xercesc::XMLString::transcode(xmlString) << std::endl;

        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};

        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

std::string PrepareTherapyMessage(std::string patientID,
                                  std::string patientFirstName,
                                  std::string patientLastName,
                                  std::string doctorID,
                                  std::string doctorFirstName,
                                  std::string doctorLastName,
                                  std::string therapyName,
                                  std::string therapyStatus)
{
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();
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
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* TherapyData = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:TherapyData"));
    Body->appendChild(TherapyData);
    xercesc::DOMElement* patID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientID"));
    TherapyData->appendChild(patID);
    xercesc::DOMText* idValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientID.data()));
    patID->appendChild(idValue);

    xercesc::DOMElement* patFirstName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientFirstName"));
    TherapyData->appendChild(patFirstName);
    xercesc::DOMText* firstNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientFirstName.data()));
    patFirstName->appendChild(firstNameValue);

    xercesc::DOMElement* patLasttName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientLastName"));
    TherapyData->appendChild(patLasttName);
    xercesc::DOMText* lastNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientLastName.data()));
    patLasttName->appendChild(lastNameValue);

    xercesc::DOMElement* docID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:DoctorID"));
    TherapyData->appendChild(docID);
    xercesc::DOMText* docidValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(doctorID.data()));
    docID->appendChild(docidValue);

    xercesc::DOMElement* docFirstName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorFirstName"));
    TherapyData->appendChild(docFirstName);
    xercesc::DOMText* docFirstNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(doctorFirstName.data()));
    docFirstName->appendChild(docFirstNameValue);

    xercesc::DOMElement* docLasttName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorLastName"));
    TherapyData->appendChild(docLasttName);
    xercesc::DOMText* docLastNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(doctorLastName.data()));
    docLasttName->appendChild(docLastNameValue);

    xercesc::DOMElement* patTherapyName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                  xercesc::XMLString::transcode("mb:TherapyName"));
    TherapyData->appendChild(patTherapyName);
    xercesc::DOMText* therapyNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(therapyName.data()));
    patTherapyName->appendChild(therapyNameValue);

    xercesc::DOMElement* patTherapyStatus = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                    xercesc::XMLString::transcode("mb:TherapyStatus"));
    TherapyData->appendChild(patTherapyStatus);
    xercesc::DOMText* therapyStatusValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(therapyStatus.data()));
    patTherapyStatus->appendChild(therapyStatusValue);

    // Get current time
    auto currentTime = std::chrono::system_clock::now();
    // Convert the time point to a time_t (seconds since epoch)
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    // Format the time as a string
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    // Store the formatted time in a std::string
    std::string formattedTime(timeBuffer);

    xercesc::DOMElement* currTime = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                            xercesc::XMLString::transcode("mb:CurrentTime"));
    TherapyData->appendChild(currTime);
    xercesc::DOMText* currTimeValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(formattedTime.data()));
    currTime->appendChild(currTimeValue);

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

std::string PrepareTherapyListMessage() {
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();
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
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* TherapyList = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:TherapyList"));
    Body->appendChild(TherapyList);

    xercesc::DOMElement* TherapyData = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:TherapyData"));
    TherapyList->appendChild(TherapyData);
    xercesc::DOMElement* patID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientID"));
    TherapyData->appendChild(patID);
    xercesc::DOMText* idValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("P001"));
    patID->appendChild(idValue);

    xercesc::DOMElement* patFirstName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientFirstName"));
    TherapyData->appendChild(patFirstName);
    xercesc::DOMText* firstNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("John"));
    patFirstName->appendChild(firstNameValue);

    xercesc::DOMElement* patLasttName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientLastName"));
    TherapyData->appendChild(patLasttName);
    xercesc::DOMText* lastNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("Johanson"));
    patLasttName->appendChild(lastNameValue);

    xercesc::DOMElement* docID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:DoctorID"));
    TherapyData->appendChild(docID);
    xercesc::DOMText* docidValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("D001"));
    docID->appendChild(docidValue);

    xercesc::DOMElement* docFirstName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorFirstName"));
    TherapyData->appendChild(docFirstName);
    xercesc::DOMText* docFirstNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("Mark"));
    docFirstName->appendChild(docFirstNameValue);

    xercesc::DOMElement* docLasttName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorLastName"));
    TherapyData->appendChild(docLasttName);
    xercesc::DOMText* docLastNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("Waston"));
    docLasttName->appendChild(docLastNameValue);

    xercesc::DOMElement* patTherapyName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                  xercesc::XMLString::transcode("mb:TherapyName"));
    TherapyData->appendChild(patTherapyName);
    xercesc::DOMText* therapyNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("Medication A"));
    patTherapyName->appendChild(therapyNameValue);

    xercesc::DOMElement* patTherapyStatus = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                    xercesc::XMLString::transcode("mb:TherapyStatus"));
    TherapyData->appendChild(patTherapyStatus);
    xercesc::DOMText* therapyStatusValue = xmlDoc->createTextNode(xercesc::XMLString::transcode("Started"));
    patTherapyStatus->appendChild(therapyStatusValue);

    // Get current time
    auto currentTime = std::chrono::system_clock::now();
    // Convert the time point to a time_t (seconds since epoch)
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    // Format the time as a string
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    // Store the formatted time in a std::string
    std::string formattedTime(timeBuffer);

    xercesc::DOMElement* currTime = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                            xercesc::XMLString::transcode("mb:CurrentTime"));
    TherapyData->appendChild(currTime);
    xercesc::DOMText* currTimeValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(formattedTime.data()));
    currTime->appendChild(currTimeValue);

    // second therapy
    xercesc::DOMElement* TherapyData2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:TherapyData"));
    TherapyList->appendChild(TherapyData2);
    xercesc::DOMElement* patID2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientID"));
    TherapyData2->appendChild(patID2);
    xercesc::DOMText* idValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("P002"));
    patID2->appendChild(idValue2);

    xercesc::DOMElement* patFirstName2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientFirstName"));
    TherapyData2->appendChild(patFirstName2);
    xercesc::DOMText* firstNameValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("Tony"));
    patFirstName2->appendChild(firstNameValue2);

    xercesc::DOMElement* patLasttName2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientLastName"));
    TherapyData2->appendChild(patLasttName2);
    xercesc::DOMText* lastNameValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("Stark"));
    patLasttName2->appendChild(lastNameValue2);

    xercesc::DOMElement* docID2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:DoctorID"));
    TherapyData2->appendChild(docID2);
    xercesc::DOMText* docidValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("D012"));
    docID2->appendChild(docidValue2);

    xercesc::DOMElement* docFirstName2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorFirstName"));
    TherapyData2->appendChild(docFirstName2);
    xercesc::DOMText* docFirstNameValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("Alex"));
    docFirstName2->appendChild(docFirstNameValue2);

    xercesc::DOMElement* docLasttName2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorLastName"));
    TherapyData2->appendChild(docLasttName2);
    xercesc::DOMText* docLastNameValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("Bolton"));
    docLasttName2->appendChild(docLastNameValue2);

    xercesc::DOMElement* patTherapyName2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                  xercesc::XMLString::transcode("mb:TherapyName"));
    TherapyData2->appendChild(patTherapyName2);
    xercesc::DOMText* therapyNameValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("Medication C"));
    patTherapyName2->appendChild(therapyNameValue2);

    xercesc::DOMElement* patTherapyStatus2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                    xercesc::XMLString::transcode("mb:TherapyStatus"));
    TherapyData2->appendChild(patTherapyStatus2);
    xercesc::DOMText* therapyStatusValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode("Started"));
    patTherapyStatus2->appendChild(therapyStatusValue2);

    // Get current time
    auto currentTime2 = std::chrono::system_clock::now();
    // Convert the time point to a time_t (seconds since epoch)
    std::time_t currentTimeT2 = std::chrono::system_clock::to_time_t(currentTime2);
    // Format the time as a string
    char timeBuffer2[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT2));
    // Store the formatted time in a std::string
    std::string formattedTime2(timeBuffer2);

    xercesc::DOMElement* currTime2 = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                            xercesc::XMLString::transcode("mb:CurrentTime"));
    TherapyData2->appendChild(currTime2);
    xercesc::DOMText* currTimeValue2 = xmlDoc->createTextNode(xercesc::XMLString::transcode(formattedTime.data()));
    currTime2->appendChild(currTimeValue2);





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
