#include "Client.h"



Client *Client::m_instance = nullptr;



Client * Client::inst()
{
    return inst("127.0.0.1", 1234);
}

Client * Client::inst(std::string address, unsigned int port)
{
    if (m_instance == nullptr)
    {
        m_instance = new Client(address, port);
    }
    return m_instance;
}



void Client::connect(std::string addr, unsigned int port)
{
    if (m_socketIsCreated) closesocket(m_serverSocket);
    
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    m_socketIsCreated = true;
    
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
    sa.sin_port = htons(port);
    
    if (
            ::connect(
                m_serverSocket, reinterpret_cast<sockaddr *>(&sa), sizeof(sa)
                     ) == SOCKET_ERROR
            )
    {
        printError("socket binding");
        return;
    }
    
    unsigned long l = 1;
    if (ioctlsocket(m_serverSocket, FIONBIO, &l) == SOCKET_ERROR)
    {
        printError("ioctlsocket(...)");
        return;
    }
    
    m_isConnected = true;
}



Client::Message * Client::takeMessage(bool &closed)
{
    // TODO: receiving and sending messages
//    if (!m_isConnected)
//    {
//        closed = true;
//        return nullptr;
//    }
    
//    closed = false;
//    char *buf = new char[packetSize()];
//    int actualSize = recv(m_serverSocket, buf, msgSize(), 0);
//    if (WSAGetLastError() == WSAEWOULDBLOCK)
//    {
//        delete[] buf;
//        return nullptr;
//    }
//    if (actualSize < 0)
//    {
//        closed = true;
        
//        printError("message receiving");
//        delete[] buf;
//        return nullptr;
//    }
    
//    return new Message{buf, actualSize};
}

void Client::sendMessage(const char *message, int length)
{
//    int shift = 0;
//    while (length > packetSize())
//    {
//        char *buf = new char[packetSize()];
//        memcpy(buf, &message[shift * packetSize()], packetSize());
//        m_messageBuffer.push_back(Message{buf, packetSize()});
        
//        length -= packetSize();
//        ++shift;
//    }
//    char *buf = new char[length];
//    memcpy(buf, &message[shift * packetSize()], length);
//    m_messageBuffer.push_back(Message{buf, length});
    
//    if (m_messageBuffer.empty()) return;
//    for (auto cl : m_clients)
//    {
//        Data d = m_messageBuffer.front();
//        m_messageBuffer.pop_front();
//        if (send(cl.socket, d.data, d.size, 0) == SOCKET_ERROR)
//        {
//            printError("sending error");
//            return;
//        }
//        delete[] d.data;
//    }
}



// private:



Client::Client(std::string address, unsigned int port)
    : m_serverSocket(),
      m_socketIsCreated(false),
      m_address(address),
      m_isConnected(false)
{
    WSADATA wsaData;
    
    if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsaData)))
    {
        printError("WSA init");
        return;
    }
    
    connect(address, port);
}

Client::~Client()
{
    closesocket(m_serverSocket);
}



void Client::printError(std::string msg)
{
    int error = 0;
    error = WSAGetLastError();
    Log::inst()->error(
                std::string("during the work of winsock (")
                + msg
                + std::string("), an error occurred with the code: ")
                + std::to_string(error)
               );
    return;
}
