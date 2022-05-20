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

			void PushDrawableComponent(std::shared_ptr<Component::DrawableComponent> const& component);
			void Update(float fElapsedTime);
			void Render();
		private:
			LevelRenderer();
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponents;	//�ִ� ������ ���͸� �����س��� ����?
		};
	}
}