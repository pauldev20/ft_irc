
#ifndef BOT_HPP
#define BOT_HPP

#include <string>

class Bot
{
	private:
		int		_fd;
	public:
				Bot();
				~Bot();
		void	run(int port, std::string pass, std::string nick);
};

#endif