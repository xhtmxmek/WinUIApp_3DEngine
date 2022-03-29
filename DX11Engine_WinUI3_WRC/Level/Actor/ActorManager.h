#pragma once
#include "Actor.h"
#include "Common/Uncopyable.h"
/*
���� ����/������ Ŭ����. ���� ������û�� �������� ������ ������� �����ϵ��� �ٲٴ°� ������
�ڷᰡ ����� �������� �ؽ� ���̺��� ����. �ؽ� ������ �����Ǳ⿡ �ؽ� �浹�� ������ ����. ����/������ ������� �ʰ� ���ĵ� �ʿ䰡 �ִ� �ڷᱸ������ map�� ����
key���� string����.
*/

/*enumClass�� ��Ƽ� ����� ����� ����� �� ������� ���Խ�Ű�� �������� ���������� �߻��ϰԵ�(��� ������ ��������, ������ Ÿ���� �ǵ�ġ ���� ������ �Ͼ�� ����)
enum�� �ɰ��� �������� �ִ��� �ٿ����ų�.. �׳� Ŭ���� ���ο� �����ϰų�,(�ۿ��� ������ ������. �ɼ������� ���ʿ��� ���ٰ�, �ۿ� ������ ������ �׶� ��Ƽ� ������)
*/

/*1000���� ���͸� �����س���, 1000���� �Ѿ�� 2000���� �����ϴ� ������.
*/

namespace Engine
{
	namespace Level
	{
		class Actor;
		
		//���Ͱ� ����Ǹ� ActorManager�� �����ؾ� �ϰ� ActorManager�����ϸ� �� ģ���� �����ϴ� ��� �ҽ����ϵ� �ٽ� �����ؾ���. ActorManager���� ��û�ϴ� ���� ���ϵ��� �������ε�...
		//�ٵ� Actor�Ŵ������� Actor�� ��û�ؼ� ���� �༮���� cpp������ ������ Actor�� ���Խ��Ѿ���. �� ActorManager�� ���� �ڷ������� ��� �ִ� �ֻ��� ���� Ŭ������ �ٽ� �����.
		//Actor�� ����, Actor �Ŵ����� ����, Actor�Ŵ����� ��� �ִ� ������ ����.
		//Actor�� �������̽� �����Ǹ� ��������� ���� ����. �ڽĵ��� ����Ǵ� ������.
		//SingleTon���� ����������, ���������� singleTon�� �ƴϾ �Ǹ� �̱������� ������ ����.
		class ActorManager : public Uncopyable
		{			
		public:
			static ActorManager& GetInstance()
			{
				static ActorManager actor;
				return actor;
			}

			void Init();			

			template<typename T>
			std::shared_ptr<Actor> CreateActor(const std::string& name)
			{				
				CheckActorListCapacity();
				//�����Ҷ� �̸��� ������� ó���ϴ� ����(ex-�ڿ�_#�� ���δٴ���)�� �����غ���
				std::shared_ptr<T>(new T(name)) newActor;
				Actors.insert(make_pair(name, newActor));
				return newActor;
			}
		private:
			//func
			ActorManager();
			void CheckActorListCapacity();
						
			std::unordered_map<std::string, std::shared_ptr<Actor>> Actors;
			//public���� �����ؼ� �ܺο��� ��������� �����Ͱ����� �׶� ����
			const size_t	ActorsSizeUnit = 1000;
			const size_t	ActorSizeBias = 5;
			unsigned int	CurrentActorSizeFactor;
			bool			ActorListResized;
		};
	}
}