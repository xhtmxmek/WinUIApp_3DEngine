#pragma once

namespace Engine
{
	namespace PropertyGroup
	{
		struct PropertyActor
		{	
			//Property라는 템플릿 value로 캡슐화 해야함. 이 value에서 값을 가져와서 디테일 패널에, 그리고 엔진 내부에 전달시키기.
			std::string ActorName;
			bool		Enable;
			bool		Visible;
			UINT		LayerMask;

			PropertyActor() : ActorName(""), Enable(false), Visible(false), LayerMask(0) {}
		};
	}
}
