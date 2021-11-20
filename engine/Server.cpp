#include "Server.h"



Server *Server::m_instance = nullptr;



Server * Server::inst()
{
    return inst(1234);
}

Server * Server::inst(unsigned int port)
{
    if (m_instance == nullptr)
    {
        m_instance = new Server(port);
    }
    return m_instance;
}



void Server::reciveMessages(bool &closed)
{
//    closed = false;
    
//    for (auto ci = m_clients.begin(); ci != m_clients.end(); ++ci)
//    {
//        char *buf = new char[msgSize()];
//        int actualSize = recv(ci->socket, buf, msgSize(), 0);
//        if (WSAGetLastError() == WSAEWOULDBLOCK)
//        {
//            delete[] buf;
//            return ;
//        }
//        if (actualSize == SOCKET_ERROR)
//        {
//            closed = true;
//            m_clients.erase(ci); // !!!
            
//            printError("message receiving");
//            delete[] buf;
//            return;
//        }
//        m_messages.push_back(new Message{*ci, buf, actualSize});
//    }
}

sockaddr_in Server::acceptConnections(bool &accepted)
{
//    accepted = false;
    
//    Client c;
//    int size = sizeof(c.sa);
//    c.socket = accept(m_lsn, reinterpret_cast<sockaddr *>(&c.sa), &size);
//    if (WSAGetLastError() == WSAEWOULDBLOCK)
//    {
//        return {};
//    }
//    if (c.socket == INVALID_SOCKET)
//    {
//        printError("socket listening");
//        return {};
//    }
//    m_clients.push_back(c);
    
//    unsigned long l = 1;
//    if (ioctlsocket(c.socket, FIONBIO, &l) == SOCKET_ERROR)
//    {
//        printError("ioctlsocket(...)");
//        return {};
//    }
    
//    accepted = true;
//    return c.sa;
}



Server::Message * Server::takeMessage()
{
    if (m_messages.empty()) return nullptr;
    
    Message *msg = m_messages.front();
    m_messages.pop_front();
    return msg;
}

void Server::sendMessage(const char *message, int length)
{
    // TODO: receiving and sending messages
//    int shift = 0;
//    while (length > packetSize())
//    {
//        char *buf = new char[packetSize()];
//        memcpy(buf, &message[shift * packetSize()], packetSize());
//        m_messageBuffer.push_back(Data{buf, packetSize()});
        
//        length -= packetSize();
//        ++shift;
//    }
//    char *buf = new char[length];
//    memcpy(buf, &message[shift * packetSize()], length);
//    m_messageBuffer.push_back(Data{buf, length});
    
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



Server::Server(unsigned int port)
    : m_lsn(),
      m_clients(),
      
      m_messageBuffer(),
      m_messages()
{
    WSADATA wsaData;
    
    if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsaData)))
    {
        printError("WSA init");
        return;
    }
    
    m_lsn = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.S_un.S_addr = INADDR_ANY;
    sa.sin_port = htons(port);
    
    if (
            bind(m_lsn, reinterpret_cast<sockaddr *>(&sa), sizeof(sa))
            == SOCKET_ERROR
            )
    {
        printError("socket binding");
        return;
    }
    
    unsigned long l = 1;
    if (ioctlsocket(m_lsn, FIONBIO, &l) == SOCKET_ERROR)
    {
        printError("ioctlsocket(...)");
        return;
    }
    
    if (::listen(m_lsn, 1000) == SOCKET_ERROR)
    {
        printError("socket listening");
        return;
    }
}



void Server::printError(std::string msg)
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
