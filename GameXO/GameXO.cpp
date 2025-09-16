// GameXO.cpp: определяет точку входа для приложения.
//

#include "GameXO.h"
#include <Game.h>
#include <Net.h>
#include "client.cpp"
#include <QueryMaker.h>
#include <thread>
#include <mutex>
#include <memory>

std::mutex mu;
bool working = 1;

WSADATA wsaData;

std::vector<WSAPOLLFD> fds;

void serverWork(std::string ans) {
	Room r(3);
	ServerSocket s(8080);
	r.print();

	Player p;
	auto cl = s.list();
	while (1) {

		auto ans = s.recieve(cl);
		std::cout << "Recieved: " << ans << '\n';
		return;

		auto parsedAns = query::get(ans);

		if (parsedAns[0] == "hello") {
			p = Player(cl, parsedAns[1]);
			r.addPlayer(p, 0);
			s.send_msg(p.getSOCKET(), "hello");
		}
		else if (parsedAns[0] == "turn") {
			auto ch = r.setPosition(std::stoi(parsedAns[1]), std::stoi(parsedAns[2]));
			r.print();
			std::cout << "-------\n";
			s.send_msg(p.getSOCKET(), query::makeTurn(stoi(parsedAns[1]), stoi(parsedAns[2]), ch));
		}
		else {
			std::cout << "Querrry error:\n";
			for (auto i : parsedAns) {
				std::cout << i << "\n";
			}

			s.send_msg(p.getSOCKET(), "QE");
		}
	}
}

void listenConnections(std::shared_ptr<ServerSocket> s) {
	while (working) {
		auto fd = s->list();
		{
			std::lock_guard<std::mutex> lock(mu);
			fds.push_back(WSAPOLLFD{ fd, POLLIN});
		}

	}

}

int main()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//cout << "Hello CMake." << endl;
	
	int flag = 0;
	std::cin >> flag;
	if (flag == 1) {		
		//serverWork();

		
		ServerSocket s(8080);
		//std::cout << POLLRDNORM;
		/*for (int i = 0; i < 2; i++) {
			fds.push_back(WSAPOLLFD{});
			auto cl = s.list();
			fds.back().fd = cl;
			fds.back().events = POLLIN;
		}*/
		auto ptr = std::make_shared<ServerSocket>(s);
		std::thread connectionListener(listenConnections, ptr);

		std::string buf(1024,' ');
		//fds.push_back(WSAPOLLFD{});

		//fds.push_back(WSAPOLLFD{0, POLLIN});
		fds = {};

		while (1) {
			if (fds.size() > 0) {
				int res = WSAPoll(fds.data(), fds.size(), 5000);

				std::cout << res << "\n";

				if (res > 0) {
					for (int i = 0; i < fds.size(); ++i) {
						if (fds[i].revents == POLLRDNORM) {
							//std::cout << i-> << " " << fds[i].revents << "\n";
							int n = recv(fds[i].fd, buf.data(), int(std::size(buf)), 0);
							buf = buf.substr(0, n);
							std::cout << buf << "\n\n";
							auto parsedAns = query::get(buf);
							if (parsedAns[0] == "hello") {
								//p = Player(cl, parsedAns[1]);
								//r.addPlayer(p, 0);
								s.send_msg(fds[i].fd, "hello");
							}
							else if (parsedAns[0] == "turn") {
								//auto ch = r.setPosition(std::stoi(parsedAns[1]), std::stoi(parsedAns[2]));
								//r.print();
								std::cout << fds[i].fd << " turn " << parsedAns[1] << " " << parsedAns[2] << "\n-------\n";
								s.send_msg(fds[i].fd, query::makeTurn(stoi(parsedAns[1]), stoi(parsedAns[2]), 'Y'));
							}
							else {
								s.send_msg(fds[i].fd, "Smth wrong");
							}
						}
						/*else if (i->revents == 3) {
							int n = recv(i->fd, buf.data(), int(std::size(buf)), 0);
							std::cout << "Three variant " << i->fd << " " << i->revents << "\n";
						}*/
						else if (fds[i].revents == 3 || fds[i].revents == POLLHUP || fds[i].revents == POLLERR || fds[i].revents == POLLNVAL) {
							//int n = recv(i->fd, buf.data(), int(std::size(buf)), 0);
							std::lock_guard<std::mutex> lock(mu);
							std::cout << "Bye-bye " << fds[i].fd <<" "<< fds[i].revents << "\n";
							//auto tmp = i - 1;
							fds.erase(fds.begin()+i);
							//i = tmp;
						}
						else {
							//int n = recv(i->fd, buf.data(), int(std::size(buf)), 0);
							std::cout << "Else variant " << fds[i].fd <<" " << fds[i].revents << "\n";
						}
					}
				}
			}

		}

		connectionListener.join();

	}
	else {
		client::main();
	}
	std::cin >> flag;
	WSACleanup();
	return 0;
}
