#include "Room.h"

Room::Room(int id) {
	_roomId = id;
}

int Room::GetRoomId() {
	return _roomId;
}

void Room::AddPlayer(std::shared_ptr<Player> player, std::string name) {
	_playersInRoom[name] = player;
}

std::shared_ptr<Player> Room::GetPlayer(const std::string& name){
	if (_playersInRoom.find(name) != _playersInRoom.end())
		return _playersInRoom[name];

	return nullptr;
}

void Room::DeletePlayer(std::string name) {
	_playersInRoom.erase(name);
}

void Room::DeleteAllPlayersInRoom() {
	_playersInRoom.clear();
}

void Room::SendToAllBut(std::string message, std::string name) {
	for (auto it = _playersInRoom.begin(); it != _playersInRoom.end(); it++) {
		if(it->first != name)
			it->second->PrepereToSend(message);
	}
}

bool Room::IsNameUnique(std::string name) {
	if (_playersInRoom.find(name) != _playersInRoom.end())
		return false;

	return true;
}

bool Room::IsRoomFull() {
	if (_playersInRoom.size() == ROOM_MAX_SIZE)
		return true;
	return false;
}

std::string Room::GetAllPlayerNamesBut(const std::string& name) {
	std::string all = "";

	for (auto it = _playersInRoom.begin(); it != _playersInRoom.end(); it++) {
		if (it->first != name) {
			all += it->second->GetName();
			all += " ";
		}
	}

	return all;
}
