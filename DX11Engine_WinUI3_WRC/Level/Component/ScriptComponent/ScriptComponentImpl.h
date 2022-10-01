#pragma once

namespace Engine
{
	namespace Component
	{
		class ScriptComponentImpl
		{
		public:
			ScriptComponentImpl(const std::string& name);
			void Init() { InitFunc(); }
			void Tick(float elasedTime) { UpdateFunc(elasedTime); }

			void SetInitFunc(const std::function<void()>& initFunc) { InitFunc = initFunc; }
			void SetUpdateFunc(const std::function<void(float)>& updateFunc) { UpdateFunc = updateFunc; }
		private:
			std::function<void()> InitFunc;
			std::function<void(float)> UpdateFunc;
		};
	}
}
