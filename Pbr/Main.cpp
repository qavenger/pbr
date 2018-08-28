#include "Vector.h"
#include "AABB.h"
int main()
{
	AABB3f aabb(float3(-7, -5, -3), float3(-3, -1, 1));
	float3 center;
	float radius;
	aabb.BoundingSphere(&center, &radius);
	
	std::cout << center << std::endl << radius << std::endl;
	system("pause");
	return 0;
}