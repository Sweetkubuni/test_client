#ifndef CONTROL_HPP
#define CONTROL_HPP
#include "threadsafe_queue.hpp"
#include  <memory>
#include  <thread>
#include <functional>
class control
{
    protected:
	threadsafe::queue< std::string > out_mq;
	threadsafe::queue< std::string > in_mq;
	std::unique_ptr<std::thread> th;
	bool keep_alive;
	void run();
	public:
        control();
        ~control();
        std::shared_ptr<std::string> receive();
        void notify(const std::string & msg);
        void send(const std::string & msg);
};
#endif // CONTROL_HPP


