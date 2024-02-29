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

bool GrpcServer::ValidateDevice(const ::ProbeMsg* data) {
    //TODO: Consider other ways of validation
    return ValidateDeviceById(data->medicaldeviceid());
}
bool GrpcServer::ValidateDeviceById(int id){
    // TODO: Add validation
    return true;
}
