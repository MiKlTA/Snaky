#ifndef H_SERVER
#define H_SERVER



#include <thread>
#include <vector>
#include <list>

#include "winsock2.h"

#include "Log.h"



class Server
{
    
public:
    struct Client
    {
        SOCKET socket;
        sockaddr_in sa;
    };
    struct Message
    {
        Client target;
        char *message;
        int length;
    };
    struct Data
    {
        char *data;
        int size;
    };
    
    static Server * inst();
    static Server * inst(unsigned int port);
    
    void reciveMessages(bool &closed);
    sockaddr_in acceptConnections(bool &accepted);
    
    Message * takeMessage();
    void sendMessage(const char *message, int length);
    
    static int packetSize() {return 1024;};
    
private:
    Server(unsigned int port);
    
    static Server *m_instance;
    
    SOCKET m_lsn;
    std::vector<Client> m_clients;
    
    std::list<Data> m_messageBuffer;
    std::list<Message *> m_messages;
    
    static void printError(std::string msg);
};



#endif // H_SERVER
