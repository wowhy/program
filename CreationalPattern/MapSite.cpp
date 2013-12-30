#include "MapSite.h"
#include <iostream>

using namespace std;

Room::Room(int roomNo) :_roomNumber(roomNo)
{
}

void Room::Enter()
{
	cout << "Room::Enter()" << endl;
}

int Room::GetRoomNo() const
{
	return _roomNumber;
}


Wall::Wall(){}

void Wall::Enter()
{
	cout << "Wall::Enter()" << endl;
}


Door::Door(Room* room1 = nullptr, Room* room2 = nullptr) :
	_room1(room1),
	_room2(room2),
	_isOpen(false)
{
}

void Door::Enter()
{
	cout << "Door::Enter()" << endl;
}




Maze::Maze()
{
}

void Maze::AddRoom(Room* room)
{
	_rooms.push_back(room);
}

Room* Maze::RoomNo(int roomNo) const
{
	for (auto* room : _rooms)
	{
		if (room != nullptr && room->GetRoomNo() == roomNo)
			return room;
	}

	return nullptr;
}