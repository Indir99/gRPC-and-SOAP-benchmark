#include "Server.h"

::grpc::Status GrpcServer::Probe(::grpc::ServerContext* context,
                                 const ::ProbeMsg* request,
                                 ::ProbeMsgResponse* response) {

    //std::cout<<" Device id: " << request->medicaldeviceid() << std::endl;
    std::cout<<"    Device name: "<< request->medicaldevicename() << std::endl;
    //std::cout<<"    Device type:" << request->medicaldevicetype() << std::endl;
    //bool probeMatch{ValidateDevice(request)};
    response->set_medicalserverid(m_serverInfo.serverId);
    response->set_medicalservername(m_serverInfo.serverName);
    response->set_probematch(true);
    return ::grpc::Status::OK;
}

::grpc::Status GrpcServer::TherapyDataMessage(::grpc::ServerContext* context,
                                              const ::TherapyData* request,
                                              ::TherapyData* response) {
    std::cout<<"    Patient ID: " << request->patientid() << std::endl;
    std::cout<<"    Patient name: " << request->patientfirstname() << std::endl;
    std::cout<<"    Patient last name: " << request->patientlastname() << std::endl;
    std::cout<<"    Doctor ID: " << request->doctorid() << std::endl;
    std::cout<<"    Doctor name: " << request->doctorfirstname() << std::endl;
    std::cout<<"    Doctor last name: " << request->doctorlastname() << std::endl;
    std::cout<<"    Therpay name: " << request->therapyname() << std::endl;
    std::cout<<"    Therapy status: " << request->therapystatus() << std::endl;
    std::cout<<"    Time: " << request->currenttime() << std::endl;
    PrepareTherapyData(response, "P001", "John", "Johanson", "D001", "Mark", "Waston", "Medication A", "Started");
    return ::grpc::Status::OK;
}

::grpc::Status GrpcServer::TherapyListMessage(::grpc::ServerContext* context,
                                              const ::TherapyList* request,
                                              ::TherapyList* response) {

    for(const TherapyData& thData : request->therapies()) {
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
    PrepareTherapyList(response);
    return ::grpc::Status::OK;
}


bool GrpcServer::ValidateDevice(const ::ProbeMsg* data) {
    //TODO: Consider other ways of validation
    return ValidateDeviceById(data->medicaldeviceid());
}
bool GrpcServer::ValidateDeviceById(int id){
    // TODO: Add validation
    return true;
}
