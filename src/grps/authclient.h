#ifndef AUTHCLIENT_H
#define AUTHCLIENT_H

#include <memory>
#include <grpcpp/grpcpp.h>
#include "auth.grpc.pb.h"

class AuthClient
{
public:
    explicit AuthClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(auth::AuthService::NewStub(channel)) {}

    bool registerUser(const std::string& username,
                      const std::string& password,
                      std::string& message);

bool loginUser(const std::string& username,
               const std::string& password,
               std::string& token,
               std::string& refreshToken,
                   std::string& message);

private:
    std::unique_ptr<auth::AuthService::Stub> stub_;
};

#endif // AUTHCLIENT_H
