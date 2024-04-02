#include "Client.h"


GrpcClient::GrpcClient(const grpc::string& target,
                       ClientInfo clInfo)
{
    m_channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
    m_stub = TestService::NewStub(m_channel);
    m_clientInfo = clInfo;
}

void GrpcClient::SendProbe() {
    grpc::ClientContext context;
    ProbeMsg request{m_clientInfo.probeMsg};
    ProbeMsgResponse response;
    grpc::Status status = m_stub->Probe(&context, request, &response);
//    std::cout<<"*** Client received following answer (Probe message) ***"<<std::endl;
    std::cout<<"    Device name: "<<response.medicalservername() <<std::endl;
//    std::cout<<"    Device id: "<<response.medicalserverid() <<std::endl;
//    std::cout<<"    Probe match value: ";
//    if(response.probematch()) {
//        std::cout<<"true "<<std::endl;
//    } else {
//        std::cout<<"false "<<std::endl;
//    }
}

void GrpcClient::SendTherapyData() {
    grpc::ClientContext context;
    TherapyData request{PrepareTherapyData("P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started")};
    TherapyData response;
    grpc::Status status = m_stub->TherapyDataMessage(&context, request, &response);
    std::cout<<"    Patient ID: " << response.patientid() << std::endl;
    std::cout<<"    Patient name: " << response.patientfirstname() << std::endl;
    std::cout<<"    Patient last name: " << response.patientlastname() << std::endl;
    std::cout<<"    Doctor ID: " << response.doctorid() << std::endl;
    std::cout<<"    Doctor name: " << response.doctorfirstname() << std::endl;
    std::cout<<"    Doctor last name: " << response.doctorlastname() << std::endl;
    std::cout<<"    Therpay name: " << response.therapyname() << std::endl;
    std::cout<<"    Therapy status: " << response.therapystatus() << std::endl;
    std::cout<<"    Time: " << response.currenttime() << std::endl;
}

void GrpcClient::SendTherapyList() {
    grpc::ClientContext context;
    TherapyList request;
    TherapyList response;
    TherapyData thData = PrepareTherapyData("P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started");
    *request.add_therapies() = thData;
    TherapyData thData2 = PrepareTherapyData("P002", "Tony", "Stark", "D012", "Alex", "Bolton", "Medication C", "Started");
    *request.add_therapies() = thData2;
    grpc::Status status = m_stub->TherapyListMessage(&context, request, &response);
    for(const TherapyData& thData : response.therapies()) {
        std::cout<<"    Patient ID: " << thData.patientid() << std::endl;
        std::cout<<"    Patient name: " << thData.patientfirstname() << std::endl;
        std::cout<<"    Patient last name: " << thData.patientlastname() << std::endl;
        std::cout<<"    Doctor ID: " << thData.doctorid() << std::endl;
        std::cout<<"    Doctor name: " << thData.doctorfirstname() << std::endl;
        std::cout<<"    Doctor last name: " << thData.doctorlastname() << std::endl;
        std::cout<<"    Therpay name: " << thData.therapyname() << std::endl;
        std::cout<<"    Therapy status: " << thData.therapystatus() << std::endl;
        std::cout<<"    Time: " << thData.currenttime() << std::endl;
    }
}

