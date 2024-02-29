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

