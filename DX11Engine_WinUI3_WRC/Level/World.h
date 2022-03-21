#pragma once
#include <vector>
#include <unordered_map>

namespace Level
{
	class Actor;
	class World
	{
	public:
		World();		
		void Update(float fTime);
		void Render(float fTime);

	private:
		void BuildDrawActors();
		std::unordered_map<std::wstring, Actor> m_Actors;
		std::vector<Actor> m_DrawActors;
	};
}