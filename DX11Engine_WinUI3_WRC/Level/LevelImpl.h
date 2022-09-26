#pragma once
namespace Engine
{
	namespace Level
	{
		class World;

		class SLevelImpl
		{
		public:
			SLevelImpl();
			SLevelImpl(const SLevelImpl&) = delete;
			SLevelImpl& operator=(const SLevelImpl&) = delete;

			std::shared_ptr<World> GetWorld()
			{
				return OwningWorld;
			}
		private:
			std::shared_ptr<World> OwningWorld;
		};
	}
}
