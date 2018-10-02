#ifndef TILETYPE_H
#define TILETYPE_H
enum TileType
{
	Normal,  //normalTile
	Collidable,  //blocks players and characters path
	Gate,  //teleport to another map
	Teleport //teleport to another location on the sameMap
};
inline const char* ToString(TileType v)
{
	switch (v)
	{
	case Normal:   return "Normal";
	case Collidable:   return "Collidable";
	case Gate: return "Gate";
	case Teleport: return "Teleport";
	default:      return "[Unknown TileType]";
	}
}
#endif // !TILETYPE_H
