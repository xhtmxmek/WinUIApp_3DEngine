#pragma once
namespace Engine
{
	namespace Level
	{
		class World;

		class SLevel
		{
		public:
			SLevel(const SLevel&) = delete;
			SLevel& operator=(const SLevel&) = delete;

			static SLevel& GetInstance()
			{
				static SLevel level;
				return level;
			}

			//World& GetWorld()
			//{
			//	return 
			//}
			std::shared_ptr<World> GetWorld()
			{
				return OwningWorld;
			}
		private:
			SLevel();
			std::shared_ptr<World> OwningWorld;
		};
	}
}