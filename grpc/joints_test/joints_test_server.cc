#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "joints_test.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using jointstest::JointsRequest;
using jointstest::JointsPosition;
using jointstest::JointsTest;

// Logic and data behind the server's behavior.
class JointsTestServiceImpl final : public JointsTest::Service {

  Status GetJointsPosition(ServerContext* context, const JointsRequest* request,
                  JointsPosition* reply) override {

    reply->set_j1(45);
    reply->set_j2(90);
    reply->set_j3(135);
    reply->set_j4(180);
    reply->set_j5(225);
    reply->set_j6(270);

	return Status::OK;
  }

};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  JointsTestServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
