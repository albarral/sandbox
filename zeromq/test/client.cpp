//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    while(true){
        zmq::message_t request (9);
        memcpy (request.data (), "Is it OK?", 9);
        std::cout << "Sending...Is it ok? " << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        std::string rpl = std::string(static_cast<char*>(reply.data()), reply.size());
        std::cout << "Received: " << rpl << std::endl;

        sleep(10);
    }
    return 0;
}
