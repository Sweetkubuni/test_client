
#ifndef USER_HPP
#define USER_HPP
#include  <string>
class user
{
    protected:
    int sockfd;
    std::string in_buffer;
    std::string out_buffer;
    bool has_disconnected;
    char delim;
   public:
       user(int new_sockfd, char new_delim);
       ~user();
        int send_msg(const std::string & msg);
       bool recieve( std::string & revc_msg);
       bool disconnected();
};
#endif // USER_HPP
