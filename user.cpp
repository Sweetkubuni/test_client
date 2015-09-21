
#include "user.hpp"
#ifndef MAX_BYTES_RECIEVE
#define MAX_BYTES_RECIEVE 1000
#endif // MAX_BYTES_RECIEVE
#include <sys/types.h>
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <unistd.h> /* for close() */
#define NOTHING_RECIEVED 0
user::user(int new_sockfd, char new_delim)
{
    sockfd = new_sockfd;
    delim = new_delim;
    has_disconnected = false;
}

int user::send_msg(const std::string & msg)
{
    out_buffer.append(msg);
    if(out_buffer.size() > 0)
    {
        int sent = send(sockfd,out_buffer.c_str(),out_buffer.length(),0);
        if( sent == - 1 ) { return -1;}
        out_buffer.erase(0,sent);
        return out_buffer.length();
    }
    return 1;
}

bool user::recieve( std::string & revc_msg)
{
    char data[MAX_BYTES_RECIEVE];

    /* Further Improvement : I could use recvmmsg - receive multiple messages on a socket
       link for more information : http://man7.org/linux/man-pages/man2/recvmmsg.2.html
    */
    int len = recv(sockfd,data,MAX_BYTES_RECIEVE,0);
    if( len == NOTHING_RECIEVED)
    {
        has_disconnected = true;
        return false;
    }
    in_buffer.append(data, len);
    std::size_t pos = in_buffer.find_first_of(delim);
    if( pos != std::string::npos)
    {
        revc_msg = in_buffer.substr (0, pos + 1 );
        return true;
    }
    return false;
}

bool user::disconnected()
{
    return has_disconnected;
}

user::~user()
{
   close(sockfd) ;
}

