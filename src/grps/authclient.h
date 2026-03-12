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
                      const std::string& password
                      );

    bool loginUser(const std::string& username,
                   const std::string& password
                    );

    std::string getToken();

private:
    std::unique_ptr<auth::AuthService::Stub> stub_;
    std::string token;
};

#endif // AUTHCLIENT_H
