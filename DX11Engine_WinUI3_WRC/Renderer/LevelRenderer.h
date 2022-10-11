#pragma once
//�������� ���忡 ���� ������Ʈ�� �������� ����ϴ� Ŭ�����̴�. 
//������ ������������ ����ϰ� �ִ�.
//���尡 �������� �����ϴ°�? �������� ���带 �����ϴ°�?

namespace Engine
{
	namespace Component
	{
		class DrawableComponent;
	}

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
			
			LevelRenderer(const LevelRenderer& ) = delete;
			LevelRenderer& operator=(const LevelRenderer& ) = delete;

			void Render(const vector<shared_ptr<Component::DrawableComponent>>& drawList );
		private:
			LevelRenderer();			
		};
	}
}