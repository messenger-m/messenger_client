#include "authclient.h"
#include <QDebug>


bool AuthClient::registerUser(const std::string& username,
                  const std::string& password)
{
    auth::RegisterRequest request;
    request.set_username(username);
    request.set_password(password);

    auth::RegisterReply reply;
    grpc::ClientContext context;

    grpc::Status status = stub_->Register(&context, request, &reply);

    if (status.ok()) {
        return reply.success();
    } else {
        return false;
    }
}

bool AuthClient::loginUser(const std::string& username,
               const std::string& password
               )
{
    auth::LoginRequest request;
    request.set_username(username);
    request.set_password(password);

    auth::LoginResponse reply;
    grpc::ClientContext context;

    grpc::Status status = stub_->Login(&context, request, &reply);

    if (status.ok()) {
        qDebug() << reply.token();
        return true;
    } else {
        qDebug() << reply.token();
        return false;
    }
}
