/*
*
*       @file:  client.cpp
*
*
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "user.hpp"
#include "control.hpp"
#include <stdexcept>
#include <memory>
#include <fstream>
using namespace std;

int main( int argc, char ** argv )
{
	int clientfd;

	/*
		Note : you must apply the following arguments with the program
		./client port  ip
		e.g :
		./client 6881 208.67.222.222
	*/
	try
	{
        if( argc == 3 )
        {
            if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                throw runtime_error("error: could not set sock");
            }
            struct sockaddr_in serv_addr;
            memset(&serv_addr, '0', sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(stoi(argv[1],nullptr));
            if(inet_pton(AF_INET, argv[2], &serv_addr.sin_addr)<=0)
            {
                throw runtime_error("error: could not get ip");
            }

            if( connect(clientfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
               throw runtime_error("error: could not connect");
            }

            bool keep_alive = true;
            user client(clientfd,'\n');
            control panel;
            while(keep_alive)
            {
                shared_ptr<std::string> resp = panel.receive();
                if(resp)
                {
                    if( resp->find("KILL") !=std::string::npos )
                    {
                        keep_alive = false;
                        continue;
                    }
                    client.send_msg(resp());
                }
                string data;
                if(client.recieve(data))
                {
                  string msg("RESP ");
                  msg.append(data);
                  panel.notify(data);
                }
            }
            panel.notify("KILLT");
        }
	}
	catch (runtime_error & ex)
	{
	  ofstream myfile;
	  myfile.open("error.txt", ios::out | ios::app);
	  myfile <<ex.what();
	  myfile.close();
	}
	return 0;
}
