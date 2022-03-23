#pragma once
/*
���� ����/������ Ŭ����. ���� ������û�� �������� ������ ������� �����ϵ��� �ٲٴ°� ������
�ڷᰡ ����� �������� �ؽ� ���̺��� ����. �ؽ� ������ �����Ǳ⿡ �ؽ� �浹�� ������ ����. ����/������ ������� �ʰ� ���ĵ� �ʿ䰡 �ִ� �ڷᱸ������ map�� ����
key���� string����.
*/

//enumClass�� ��Ƽ� ����� ����� ����� �� ������� ���Խ�Ű�� �������� ���������� �߻��ϰԵ�(��� ������ ��������, ������ Ÿ���� �ǵ�ġ ���� ������ �Ͼ�� ����)
//enum�� �ɰ��� �������� �ִ��� �ٿ����ų�.. �׳� Ŭ���� ���ο� �����ϰų�,(�ۿ��� ������ ������)

namespace Engine
{
	namespace Level
	{
		class Actor;
		
		class ActorManager
		{			
		public:
			void Init();

			template<typename T>
			std::shared_ptr<Actor> CreateActor(const std::string& name)
			{				
				std::shared_ptr<T(name)>(new T(name)) newActor;
				Actors.insert(make_pair(name, newActor));
			}
		private:
			std::unordered_map<std::string, std::shared_ptr<Actor>> Actors;
			//public���� �����ؼ� �ܺο��� ��������� �����Ͱ����� �׶� ����
			const unsigned int ActorsSize = 1000;
		};
	}
}