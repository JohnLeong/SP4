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
		NUM_TILE
	};
	//Collision check based on COLLISION_TYPE
	enum COLLISION_TYPE
	{
		COL_NULL = 0,		//For error handling
		COL_VOID,			//No collision
		COL_BLOCK,			//Filled area - unpassable
		COL_HAZARD,			//Death on entry
		COL_SLIPPERY,		//Slide to next spot if possible
		NUM_COL
	};

	CTiledata(void);
	CTiledata(TILE_ID TileId, COLLISION_TYPE CollisionType);
	~CTiledata(void);

	void SetTileId(TILE_ID TileId);
	void SetCollisionType(COLLISION_TYPE CollisionType);

	TILE_ID GetTileId(void);
	COLLISION_TYPE GetCollisionType(void);

private:
	TILE_ID m_iTileId;
	COLLISION_TYPE m_iCollisionType;

};
