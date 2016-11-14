#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "joints_test.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using jointstest::JointsRequest;
using jointstest::JointsPosition;
using jointstest::JointsTest;

class JointsTestClient {
 public:
  JointsTestClient(std::shared_ptr<Channel> channel)
      : stub_(JointsTest::NewStub(channel)) {}

  // Assambles the client's payload, sends it and presents the response back
  // from the server.
  std::string GetJointsPosition(const bool& check) {
    // Data we are sending to the server.
    JointsRequest request;
    request.set_request(check);
	if(check) std::cout << "Check joints: TRUE" << std::endl;
	else std::cout << "Check joints: FALSE" << std::endl;
    // Container for the data we expect from the server.
    JointsPosition jointsPositions;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->GetJointsPosition(&context, request, &jointsPositions);

    // Act upon its status.
    if (status.ok()) {
		
		std::cout << "\nj1: " << jointsPositions.j1()
				  << "\nj2: " << jointsPositions.j2() 
				  << "\nj3: " << jointsPositions.j3() 
				  << "\nj4: " << jointsPositions.j4() 
				  << "\nj5: " << jointsPositions.j5() 
				  << "\nj6: " << jointsPositions.j6() << std::endl;
      return "OK";
    } else {
      std::cout << status.error_code() << "Error :" << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<JointsTest::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  JointsTestClient JointsTest(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::cout << "---------------Position Test START-------------------- " << std::endl;

  JointsTest.GetJointsPosition(true);

  std::cout << "---------------Position Test END-------------------- " << std::endl;

  return 0;
}
