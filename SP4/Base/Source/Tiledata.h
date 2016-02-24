#include <string>

class CTiledata
{
public:
	//Tile mesh is rendered based on TILE_ID
	enum TILE_ID
	{
		TILE_NULL = 0,		//For error handling
		TILE_VOID,
		TILE_WALL_STONE_01,
		TILE_WALL_STONE_02,
		TILE_WALL_STONE_03,
		TILE_FLOOR_STONE_01,
		TILE_FLOOR_STONE_02,
		TILE_FLOOR_STONE_03,
		TILE_FLOOR_ICE_01,
		TILE_DOOR_RED,
		TILE_DOOR_BLUE,
		TILE_DOOR_GREEN,
		TILE_DOOR_YELLOW,		//Can only be opened with yellow key
		TILE_HOLE_STONE_01,
		TILE_HOLE_STONE_FILLED_01,
		TILE_WIND_UP,			//Pushes player up
		TILE_WIND_DOWN,			//Pushes player down
		TILE_WIND_LEFT,			//Pushes player to the left
		TILE_WIND_RIGHT,		//Pushes player to the right
		TILE_RUNE,				//Kills enemies on touch
		TILE_RUNE_USED,
		TILE_STAIRCASE,
		NUM_TILE
	};
	//Collision check based on COLLISION_TYPE
	enum COLLISION_TYPE
	{
		COL_NULL = 0,		//For error handling
		COL_VOID,			//No collision
		COL_BLOCK,			//Filled area - unpassable
		COL_HOLE,			//Unpassable until filled
		COL_HAZARD,			//Death on entry
		COL_ICE,		//Slide to next spot if possible
		COL_WIND_UP,
		COL_WIND_DOWN,
		COL_WIND_LEFT,
		COL_WIND_RIGHT,
		COL_RUNE,
		COL_LOCK_RED,
		COL_LOCK_BLUE,
		COL_LOCK_GREEN,
		COL_LOCK_YELLOW,
		COL_ENDLEVEL,
		NUM_COL
	};

	CTiledata(void);
	CTiledata(TILE_ID TileId, COLLISION_TYPE CollisionType);
	~CTiledata(void);

	void SetTileId(TILE_ID TileId);
	void SetCollisionType(COLLISION_TYPE CollisionType);
	void SetTint(bool b);

	TILE_ID GetTileId(void);
	COLLISION_TYPE GetCollisionType(void);
	bool IsTinted(void);

	void ChangeIdState(void);

private:
	TILE_ID m_iTileId;
	COLLISION_TYPE m_iCollisionType;
	bool m_bTint;			//Tint if any enemies are going to walk onto this tile
};
