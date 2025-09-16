#include "Game.h"
#include <iostream>

//Field realization
Field::Field() {
	size = 3;
}

Field::Field(int s) {
	size = s;
	field = std::vector<std::vector<char>>(s, std::vector<char>(s, '*'));
}

char Field::check() {
	char ans = '*';

	for (int i = 0; i < size; i++) {
		bool row = 1;
		for (int j = 1; j < size; j++) {
			if (field[i][j - 1] != field[i][j]) {
				row = 0;
				break;
			}
		}
		if (row) {
			return field[i][1];
		}
	}

	for (int i = 0; i < size; i++) {
		bool col = 1;
		for (int j = 1; j < size; j++) {
			if (field[j - 1][i] != field[j][i]) {
				col = 0;
				break;
			}
		}
		if (col) {
			return field[1][i];
		}
	}

	bool diag = 1;
	for (int i = 1; i < size; i++) {
		if (field[i - 1][i - 1] != field[i][i]) {
			diag = 0;
		}
	}
	if (diag) {
		return field[0][0];
	}

	diag = 1;
	for (int i = 1; i < size; i++) {
		if (field[i - 1][size - i] != field[i][i]) {
			diag = 0;
		}
	}
	if (diag) {
		return field[0][size - 1];
	}

	return ans;
}

char Field::setPosition(int x, int y, char ch) {
	field[x][y] = ch;
	return check();
}

void Field::print() {
	for (auto& i : field) {
		for (auto& j : i) {
			std::cout << j;
		}

		std::cout << "\n";
	}
}

int Field::getSize() {
	return size;
}

std::string Field::toString() {
	std::string ans = std::to_string(size) + ':';
	for (auto& c : field) {
		ans += std::string(c.begin(), c.end());
	}

	return ans;
}

//Player realization
//Player::Player() {
//	id = 0;
//}

Player::Player(SOCKET sc) {
	socket = sc;
	name = "";
}

Player::Player(SOCKET sc, std::string name) {
	socket = sc;
	this->name = name;
}

//Player::Player(long long n) {
//	id = n;
//}
//
//Player::Player(std::string n) {
//	name = n;
//
//}

SOCKET Player::getSOCKET() {
	return socket;
}

//Team realization
Team::Team() {
	id = 0;
	teamChar = 'x';
}

Team::Team(char c) {
	id = 0;
	teamChar = c;
}

bool Team::setId(long long n) {
	id = n;
	return 1;
}

bool Team::setChar(char c) {
	teamChar = c;
	return 1;
}

char Team::getChar() {
	return teamChar;
}

SOCKET Team::addPlayer(Player p) {
	players.push_back(p);
	return p.getSOCKET();
}

char Team::setPosition() {
	return teamChar;
}

//Room realization
Room::Room(int s) {
	currentQueue = 0;
	f = Field(s);
	teams = std::vector<Team>(2);
}

bool Room::addPlayer(Player p, int team_id) {
	teams[team_id].addPlayer(p);
	return 1;
}

char Room::setPosition(int x, int y) {
	char winer = f.setPosition(x, y, teams[currentQueue].setPosition());
	//char ans = teams[currentQueue].getChar();
	//currentQueue = (currentQueue+1)%teams.size();
	return winer;
}

void Room::print() {
	f.print();
}

char Room::getChar() {
	char ans = teams[currentQueue].getChar();
	currentQueue = (currentQueue+1)%teams.size();
	return ans;
}
