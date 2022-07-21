#pragma once
#include "../ComponentBase.h"

namespace Engine
{
	namespace Component
	{
		class StaticMeshComponentImpl;

		class StaticMeshComponent : public DrawableComponent
		{
		public:
			RUNTIME_SUBCLASS(StaticMeshComponent)
			StaticMeshComponent(const std::string& name = "StaticMeshComponent");
			~StaticMeshComponent();
			void Init() final;
			void Tick(float elapsedTime) final;
			void Draw() final;
		private:
			StaticMeshComponentImpl* pImpl;
		};


	}
}
