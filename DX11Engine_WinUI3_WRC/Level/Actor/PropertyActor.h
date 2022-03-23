#pragma once

namespace Engine
{
	namespace PropertyGroup
	{
		struct PropertyActor
		{			
			string	ActorName;
			bool	Enable;
			bool	Visible;
			UINT	LayerMask;

			PropertyActor() : ActorName(""), Enable(false), Visible(false), LayerMask(0) {}
		};
	}
}
