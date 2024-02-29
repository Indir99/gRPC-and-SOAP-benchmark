#include <myproto/TestFile.grpc.pb.h>
#include <myproto/TestFile.pb.h>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "ServerInfo.h"

class GrpcServer final : public TestService::Service {
public:
    GrpcServer(ServerInformation serverInfo)
        : m_serverInfo{serverInfo} {}

    virtual ::grpc::Status Probe(::grpc::ServerContext* context,
                                 const ::ProbeMsg* request,
                                 ::ProbeMsgResponse* response) override;

private:
    bool ValidateDevice(const ::ProbeMsg* data);
    bool ValidateDeviceById(int id);

    ServerInformation m_serverInfo;
};


