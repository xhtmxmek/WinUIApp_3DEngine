#pragma once

namespace Engine
{
	namespace Renderer
	{
		class LevelRenderer
		{
		public:
			static LevelRenderer& GetInstance()
			{
				static LevelRenderer instance;
				return instance;
			}

			void Render();			
		private:
			LevelRenderer();
		};
	}
}