#pragma once

namespace Engine
{
	namespace PropertyGroup
	{
		struct PropertyActor
		{	
			//Property��� ���ø� value�� ĸ��ȭ �ؾ���. �� value���� ���� �����ͼ� ������ �гο�, �׸��� ���� ���ο� ���޽�Ű��.
			std::string ActorName;
			bool		Enable;
			bool		Visible;
			UINT		LayerMask;

			PropertyActor() : ActorName(""), Enable(false), Visible(false), LayerMask(0) {}
		};
	}
}
