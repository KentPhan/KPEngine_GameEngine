GameObject = 
{
	name = "Player",
	position = { 140.0, 100.0, 3.0},
	layer = 1,
	tag = 1,
	components =
	{
		KPRender2DComponent = 
		{
			texture = "Assets\\Sprites\\Characters\\Stein.dds"
		},
		KPPhysics2DComponent = 
		{
			isStatic = false
		},
		BoxCollisionComponent = 
		{
			center = { 0.0, 0.0, 0.0},
			extents = { 15.0, 15.0, 0.0}
		}
	}
}