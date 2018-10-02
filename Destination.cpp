#include "Destination.h"

Destination::Destination()
{
	this->theDestination = "NULL";
	this->xID = -1;
	this->yID = -1;
}

Destination::Destination(std::string dest, int x, int y)
{
	this->theDestination = dest;
	this->xID = x;
	this->yID = y;
}

Destination::~Destination()
{
}

void Destination::setDestination(std::string dest)
{
	this->theDestination = dest;
}

void Destination::setXID(int x)
{
	this->xID = x;
}

void Destination::setYID(int y)
{
	this->yID = y;
}

std::string Destination::getDestination() const
{
	return this->theDestination;
}

int Destination::getXID() const
{
	return this->xID;
}

int Destination::getYID() const
{
	return this->yID;
}
