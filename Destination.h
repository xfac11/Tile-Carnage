#ifndef DESTINATION_H
#define DESTINATION_H
#include <string>
class Destination
{
private:
	std::string theDestination;
	int xID;
	int yID;
public:
	Destination();
	Destination(std::string dest, int x, int y);
	~Destination();

	void setDestination(std::string dest);
	void setXID(int x);
	void setYID(int y);

	std::string getDestination()const;
	int getXID()const;
	int getYID()const;

};
#endif