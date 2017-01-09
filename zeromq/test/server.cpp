#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        std::string rq = std::string(static_cast<char*>(request.data()), request.size());
        std::cout << "Received: "<< rq << std::endl;

        //  Do some 'work'
        sleep(2);
        std::cout << "Sending...OK "<< std::endl;

        //  Send reply back to client
        zmq::message_t reply (2);
        memcpy (reply.data (), "OK", 2);
        socket.send (reply);
    }
    return 0;
}
