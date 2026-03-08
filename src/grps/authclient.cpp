#include "authclient.h"


bool AuthClient::registerUser(const std::string& username,
                  const std::string& password,
                  std::string& message)
{
    auth::RegisterRequest request;
    request.set_username(username);
    request.set_password(password);

    auth::RegisterReply reply;
    grpc::ClientContext context;

    grpc::Status status = stub_->Register(&context, request, &reply);

    if (status.ok()) {
        message = reply.message();
        return reply.success();
    } else {
        message = status.error_message();
        return false;
    }
}

bool AuthClient::loginUser(const std::string& username,
               const std::string& password,
               std::string& token,
               std::string& refreshToken,
               std::string& message)
{
    auth::LoginRequest request;
    request.set_username(username);
    request.set_password(password);

    auth::LoginResponse reply;
    grpc::ClientContext context;

    grpc::Status status = stub_->Login(&context, request, &reply);

    if (status.ok()) {
        token = reply.token();
        refreshToken = reply.refresh_token();
        message = "login successful";
        return true;
    } else {
        message = status.error_message();
        return false;
    }
}
