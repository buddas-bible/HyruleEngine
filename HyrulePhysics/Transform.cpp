// #include "Transform.h"
// #include "PHYSICALLYOBJECT_INFO.h"
// 
// namespace Hyrule
// {
// 	namespace Physics
// 	{
// 
// 		Transform::Transform(
// 			TRANSFORM_INFO* _info) noexcept :
// 			position(_info->pPosition), rotation(_info->pRotation), scale(_info->pScale), 
// 			worldTM()
// 		{
// 
// 		}
// 
// 		Hyrule::Matrix4x4& Transform::GetLocalTransform()
// 		{
// 			return *worldTM;
// 		}
// 	}
// }