#pragma once

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include "ClientInfo.h"
#include <myproto/TestFile.pb.h>
#include <myproto/TestFile.grpc.pb.h>

class GrpcClient {
public:
    GrpcClient(const grpc::string& target,
               ClientInfo clInfo);

    void SendProbe();
private:
    std::unique_ptr<TestService::Stub> m_stub;
    std::shared_ptr<grpc::Channel> m_channel;
    ClientInfo m_clientInfo;
};

