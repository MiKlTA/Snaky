#include <iostream>
#include <thread>

#include "src/Initializer.h"

//#include "engine/Server.h"
//#include "engine/Client.h"



//void recvMsgClient(Client *client)
//{
//    while (true)
//    {
//        Log::inst()->printLog(-1);
//        Sleep(1);
        
//        bool closed;
//        Client::Message *msg = client->takeMessage(closed);
//        if (closed)
//        {
//            std::cout << "connection lost" << std::endl;
//            break;
//        }
//        if (msg == nullptr) continue;
//        if (msg->length == 0) continue;
        
//        std::cout << "| "
//                  << client->getAddress()
//                  << " |: "
//                  << std::string(msg->message, msg->length) << std::endl;
        
//        delete[] msg->message;
//        delete msg;
//    }
//}

//void recvMsgServer(Server *server)
//{
//    while (true)
//    {
//        Log::inst()->printLog(-1);
//        Sleep(1);
        
//        bool accepted;
//        sockaddr_in sa = server->acceptConnections(accepted);
//        if (accepted)
//        {
//            std::cout << "| " << inet_ntoa(sa.sin_addr)
//                      << " |: connected!"<< std::endl;
//        }
        
//        bool closed;
//        server->reciveMessages(closed);
//        if (closed)
//        {
//            std::cout << "connection lost" << std::endl;
//        }
//        Server::Message *msg = server->takeMessage();
//        if (msg == nullptr) continue;
//        if (msg->length == 0) continue;
        
//        std::cout << "| "
//                  << inet_ntoa(msg->target.sa.sin_addr)
//                  << " |: "
//                  << std::string(msg->message, msg->length) << std::endl;
        
//        delete[] msg->message;
//        delete msg;
//    }
//}



int main()
{
    std::cout << "Made by Nikitka: https://github.com/MiKlTA" << std::endl;
    
    
    
    Initializer::init()->startGameCycle();
    
    
    
//    std::cout << "please enter \"s\" if you want to become a server, or "
//                 "\"c\" if you want to become a client" << std::endl;
//      
//    std::string in;
//    while (!(in == "c" || in == "s"))
//    {
//        std::cin >> in;
//    }
    
//    if (in == "c")
//    {
//        std::string address;
//        int port;
//        std::cout << "enter address (0 = 127.0.0.1): ";
//        std::cin >> address;
//        std::cout << "enter port (0 = 1234): ";
//        std::cin >> port;
//        Client::inst(
//                    address == "0" ? "127.0.0.1" : address,
//                    port == 0 ? 1234 : port
//                     );
        
//        std::thread th(recvMsgClient, Client::inst());
        
//        while (in != "cls")
//        {
//            std::cin >> in;
            
//            Client::inst()->sendMessage(in.c_str(), in.size());
//        }
//    }
//    else if (in == "s")
//    {
//        int port;
//        std::cout << "enter port (0 = 1234): ";
//        std::cin >> port;
//        Server::inst(port == 0 ? 1234 : port);
        
//        std::thread th(recvMsgServer, Server::inst());
        
//        while (in != "cls")
//        {
//            std::cin >> in;
            
//            Server::inst()->sendMessage(in.c_str(), in.size());
//        }
//    }
    
    
    
    
    std::cout << "borks!" << std::endl;
    return 0;
}
