#include "Net.h"

Socket::Socket(int port) {
    this->port = port;
    // 1. Инициализация Winsock
    /*int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result) {
        std::cerr << "WSAStartup was wrong: " << result << "\n";
        return;
    }*/

    // 2. Создаём сокет
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd == INVALID_SOCKET) {
        std::cerr << "Error: socket\n";
        //WSACleanup();
        return;
    }

    // 3. Настраиваем адрес
    //sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    // 4. Привязываем сокет
    if (bind(socket_fd, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Error: bind\n";
        closesocket(socket_fd);
        //WSACleanup();
        return;
    }
}

Socket::Socket(SOCKET soc) {
    socket_fd = soc;
}

SOCKET ServerSocket::list() {
    // 5. Запускаем в режим прослушивания
    if (listen(socket_fd, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error: listen\n";
        closesocket(socket_fd);
        //WSACleanup();
        return INVALID_SOCKET;
    }

    std::cout << "Server started on 127.0.0.1:" << port<<"\n";
    SOCKET client_fd = accept(socket_fd, nullptr, nullptr);
    if (client_fd == INVALID_SOCKET) {
        std::cerr << "Error: accept\n";
        closesocket(socket_fd);
        //WSACleanup();
        return INVALID_SOCKET;
    }

    SOCKET ans = client_fd;

    return ans;
}

std::string Socket::recieve(SOCKET soc) {
    std::cout << "Recieving\n";
    char buffer[1024];
    char nullBuffer[] = {"None"};
    std::string ans(1024, ' ');
    int bytes = recv(soc, (char*)ans.data(), ans.size(), 0);
    //std::cout << "Full answer is:" << ans << "\n";
    if (bytes <= 0) 
        return nullBuffer; // клиент закрыл соединение
    //std::string ans = std::string(buffer);
    ans = ans.substr(0, bytes);
    //buffer[bytes] = '\0';
    //std::cout << bytes << " Recieved: " << buffer << "\n";
    //std::cout<< bytes << " Recieved: " << ans << "\n";
    return ans;
}

void ServerSocket::send_msg(SOCKET soc, std::string msg){
    send(soc, msg.data(), msg.size(), 0);
}

SOCKET ServerSocket::data() {
    return this->socket_fd;
}

Socket::~Socket() {
    //closesocket(client_fd);
    closesocket(socket_fd);
    //WSACleanup();

    std::cout << "Server stoped\n";
}

void ClientSocket::set_server(std::string ip, int port) {
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    PCSTR tmp = ip.data();
    
    inet_pton(AF_INET, tmp, &addr.sin_addr);

    if (connect(socket_fd, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Error: connect\n";
        closesocket(socket_fd);
        //WSACleanup();
        return;
    }
    std::cout << "Server connected!\n";
}

void ClientSocket::send_msg(std::string msg) {
    send(socket_fd, msg.data(), msg.size(), 0);
}

std::string ClientSocket::recieve() {
    return Socket::recieve(socket_fd);
};

ClientSocket::~ClientSocket() {
    //this->send_msg("bye");
}
