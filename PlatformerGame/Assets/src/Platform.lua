GameObject = 
{
	name = "Platform",
	position = { -380.0, -300.0, 0.0},
	layer = 2,
	tag = 2,
	components =
	{
		KPRender2DComponent = 
		{
			texture = "Assets\\Sprites\\Tiles\\Tile_1_C.dds"
		},
		BoxCollisionComponent = 
		{
			center = { 0.0, 0.0, 0.0},
			extents = { 15.0, 15.0, 0.0}
		}
	}
}