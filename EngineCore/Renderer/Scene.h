#pragma once

//Scene은 World의 렌더러 버전. World와 각종 DrawableComponent 정보로 렌더링.
namespace Engine
{
	namespace World
	{
		class WorldObject;
	}
	
	namespace Renderer	
	{
		class StaticPrimitiveInfo;
		class DynamicPrimitiveInfo;
		enum class MeshPass;

		struct MeshDrawCommand;

		namespace RHI
		{
			class RHICommand;
		}
		
		class Scene
		{
		public:			
			~Scene();
		private:
			std::shared_ptr<World::WorldObject> world_ptr;

			//생성되거나 visible 정보 바뀔떄 Scene의 DrawableComponentList에 추가됨. Visiblity 검사 통과한 Primitive에 대해서만.
			std::vector<shared_ptr<StaticPrimitiveInfo>> static_primitives;
			vector<shared_ptr<MeshDrawCommand>> cached_drawcommandlist;

			
			std::vector<DynamicPrimitiveInfo> dynamic_primitives;
			//-DynamicDrawCommandList : 매프레임 생성. Visiblity 검사 통과한 DynamicPrimitives에 대해서만. ex:모핑되는 스켈레탈,파티클 등. 
			vector<shared_ptr<MeshDrawCommand>> dynamic_drawcommandlist;

			//visible Flag나 visibility 검사를 통해 나온 Static과 Dynamic이 담김.
			vector<shared_ptr<MeshDrawCommand>> visible_drawcommandlist[MaxMeshPassNum];

			bool use_parallel_rendering;
			
		public:
			void AddToScene(const shared_ptr<StaticPrimitiveInfo>& primitive);
			void AddToScene(const shared_ptr<DynamicPrimitiveInfo>& primitive);			
			void DispatchVisibleDrawCommandList(MeshPass pass);
		};
	}
}
