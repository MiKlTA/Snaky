#ifndef H_CLIENT
#define H_CLIENT



#include <thread>
#include <vector>
#include <list>

#include "winsock2.h"

#include "Log.h"



class Client
{
    
public:
    struct Message
    {
        const char *message;
        int length;
    };
    
    static Client * inst();
    static Client * inst(std::string addr, unsigned int port);
    
    void connect(std::string addr, unsigned int port);
    std::string getAddress() {return m_address;};
    
    Message * takeMessage(bool &closed);
    void sendMessage(const char *message, int length);
    
    bool isConnected() {return m_isConnected;};
    
    static int packetSize() {return 1024;};
    
private:
    Client(std::string addr, unsigned int port);
    ~Client();
    
    static Client *m_instance;
    
    SOCKET m_serverSocket;
    bool m_socketIsCreated;
    std::string m_address;
    bool m_isConnected;
    
    std::list<Message> m_messageBuffer;
    
    static void printError(std::string msg);
};



#endif // H_CLIENT
