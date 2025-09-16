#pragma once

#include <vector>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>


class Field {
private:
	int size;
	std::vector<std::vector<char>> field;
	char check();
public:
	Field();
	Field(int s);
	//bool setSize(int n = 3);
	char setPosition(int x, int y, char ch);
	void print();
	int getSize();
	std::string toString();
};

class Player {
private:
	//long long id;
	std::string name = "";
	SOCKET socket {};
public:
	Player() {};
	Player(SOCKET sc);
	Player(SOCKET sc, std::string name);
	//Player(long long n);
	//Player(std::string n);
	SOCKET getSOCKET();
};

class Team {
private:
	int id;
	char teamChar;
	std::vector<Player> players;
	int currentQueue = 0;
public:
	Team();
	Team(char c);
	bool setChar(char c);
	char getChar();
	bool setId(long long n);
	SOCKET addPlayer(Player p);
	char setPosition();
};

class Room {
private:
	Field f;
	std::vector<Team> teams;
	int currentQueue = 0;
public:
	Room(int s);
	bool addPlayer(Player p, int team_id);
	char setPosition(int x, int y);
	void print();
	char getChar();
};