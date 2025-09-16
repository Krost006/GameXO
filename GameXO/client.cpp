#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Net.h>
#include <Game.h>
#include <QueryMaker.h>

//#pragma comment(lib, "Ws2_32.lib")

namespace client {

    //sockaddr_in server_addr{};
    //SOCKET client_fd;



    int main() {
        std::string username;
        std::cout << "Enter your name:\n";
        std::cin >> username;
        int port = 8081;
        std::cout << "Input port:\n";
        std::cin >> port;
        ClientSocket soc(port);
        //create_soc();
        soc.set_server("127.0.0.1", 8080);
        std::string msg = query::makeHello(username);
        soc.send_msg(msg);
        std::string ans = soc.recieve();

        Field f(3);

        while (1) {
            std::cout << "Input coordinates:";
            int x =-1, y=-1;
            std::cin >> x >> y;
            soc.send_msg(query::makeTurn(x, y));

            std::string ans = soc.recieve();
            std::cout << "Server says: " << ans << "\n";
            auto q = query::get(ans);

            if (q[0] == "turn") {
                f.setPosition(stoi(q[1]), stoi(q[2]), q[3][0]);
                f.print();
                std::cout << "-------\n";
            }
            else if (q[0] == "QE") {
                std::cout << "Wrong query:\n" << ans << "\n";
            }
            else {
                std::cout << "Server answer error:\n" << ans << "\n";
            }
            std::cout << '\n';
        }
        std::cin >> username;
        return 0;
    }

    
}