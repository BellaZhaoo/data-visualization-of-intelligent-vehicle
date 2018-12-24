#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpc++/grpc++.h>

#ifdef BAZEL_BUILD
#include "examples/protos/auto_interface.grpc.pb.h"
#else
#include "auto_interface.grpc.pb.h"
#endif
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using autointerface::HelloRequest;
//using autointerface::HelloReply;
using autointerface::AutoInterface;

// Logic and data behind the server's behavior.

HelloRequest MakeHelloRequest(int lengthofplan,float lanelx,
                        float lanely,float stoplanedis,float pathpoints,float pathpointx) {
  HelloRequest n;
  n.set_lengthofplan(lengthofplan);
  n.set_lanelx(lanelx);
  n.set_lanely(lanely);
  n.set_stoplanedis(stoplanedis);
  n.set_pathpoints(pathpoints);
  n.set_pathpointx(pathpointx);
  //n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
  return n;
}


class GreeterServiceImpl final : public AutoInterface::Service {

  Status SayHello(ServerContext* context,
                   ServerReaderWriter<HelloRequest, HelloRequest>* stream) override {
    std::vector<HelloRequest> received_notes;
    /*std::thread writer([stream]() {
      std::vector<HelloRequest> notesagain{
        //MakeHelloRequest(2,1,1,1.0,1, 2),
        //MakeHelloRequest(2,1,1,2.0,1, 3),
        //MakeHelloRequest(2,1,1,3.0,1, 4),
        MakeHelloRequest(2,1,1,4.0,1, 5)};
      //for (const HelloRequest& noteagain : notesagain) {
        const HelloRequest& noteagain = notesagain[1];
        std::cout << "Sending message " << noteagain.lengthofplan()<< noteagain.lanelx()<< noteagain.lanely()<< noteagain.stoplanedis()
                  << noteagain.pathpoints()<< noteagain.pathpointx()  << std::endl;
        stream->Write(noteagain);
        stream->WritesDone();
       //}
      //stream->Write(noteagain);
      
      
    });*/
    



    HelloRequest note;
    while (stream->Read(&note)) {

        std::cout << "Got message " 
                  << note.lengthofplan()<< note.lanelx()<< note.lanely()<< note.stoplanedis()
                  << note.pathpoints()<< note.pathpointx()  << std::endl;
        stream->Write(note);
        /*std::cout << "Got message "  << note.lengthOfPlan()
                  << note.lanelx()<< note.lanely() << note.StopLaneDis()
                  << note.pathPoints()<< note.pathPointx() << std::endl;*/
      //}
      received_notes.push_back(note);
    }

    return Status::OK;
  }

};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

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
