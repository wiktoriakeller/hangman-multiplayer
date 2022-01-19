#pragma once

#include "Handler.h"

class Player : public Handler {
public:
	Player(int socket, int id, int epollFd);
	void Close() override;
	HandleResult Handle(uint events) override;
	void SetId(int id);
	int GetId();
	void SetName(std::string name);
	std::string GetName();
	void SetRoomId(int id);
	int GetRoomId();
	void CloseSocket();
	void PrepereToSend(std::string message);

private:
	const size_t BUFFER_SIZE = 24;
	int _socket;
	int _id;
	int _roomId;
	int _epollFd;
	std::string _name;
	std::vector<char> currentMessagesToRead;
	std::vector<std::string> currentMessagesToSend;

	void WaitForWrite(bool epollout);
	void HandleOperation(std::vector<std::string>& splitted);
	void ParseMessage(std::string message);	

	//operation codes handlers
	std::string SendNewRoomId(std::vector<std::string>& splitted);
	std::string JoinRoom(std::vector<std::string>& splitted);
	std::string SendPlayerName(std::vector<std::string>& splitted);
	std::string SendAllPlayerNames(std::vector<std::string>& splitted);
};