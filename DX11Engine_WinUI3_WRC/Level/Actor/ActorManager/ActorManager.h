#pragma once
#include "DLLDefine.h"
#include "Common/Uncopyable.h"
#include "Common/RuntimeContext.h"

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
		class ActorManagerImpl;

		//���Ͱ� ����Ǹ� ActorManager�� �����ؾ� �ϰ� ActorManager�����ϸ� �� ģ���� �����ϴ� ��� �ҽ����ϵ� �ٽ� �����ؾ���. ActorManager���� ��û�ϴ� ���� ���ϵ��� �������ε�...
		//�ٵ� Actor�Ŵ������� Actor�� ��û�ؼ� ���� �༮���� cpp������ ������ Actor�� ���Խ��Ѿ���.
		//Actor�� ����, Actor�Ŵ����� ����, Actor�Ŵ����� ��� �ִ� ������ ����.
		//Actor�� �������̽� �����Ǹ� ��������� ���� ����. �ڽĵ��� ����Ǵ� ������.
		//SingleTon���� ����������, ���������� singleTon�� �ƴϾ �Ǹ� �̱������� ������ ����.
		class ENGINE_API ActorManager : public Uncopyable
		{
		public:
			static ActorManager& GetInstance()
			{
				static ActorManager actor;
				return actor;
			}

			void ReleaseInstance();

			void Init();

			template<typename T>
			SharedPointer<T> CreateActor(const std::string& name)
			{
				CheckActorListCapacity();
				//�����Ҷ� �̸��� ������� ó���ϴ� ����(ex-�ڿ�_#�� ���δٴ���)�� �����غ���				
				//SharedPointer<T> newActorPtr;
				//auto newActor = CreateActor(T::ClassName(), name);
				//SharedPointer<T> newActorPtr(std::static_pointer_cast<T>(newActor()));								
				return nullptr;
			}

			size_t GetNumActorList();
		private:			
			//func
			ActorManager() : CurrentActorSizeFactor(1), ActorListResized(false){}			
			void CheckActorListCapacity();
			SharedPointer<Actor> CreateActor(const std::string& className, const std::string& instanceName);
			//Actor* CreateActor(const std::string& className, const std::string& instanceName);
			SharedPointer<Actor> GetActorByName(const std::string& actorName);

			//��� ����
			HashMap<const char*, SharedPointer<Actor>> Actors;
			//public���� �����ؼ� �ܺο��� ��������� �����Ͱ����� �׶� ����
			const size_t	ActorsSizeUnit = 1000;
			const size_t	ActorSizeBias = 5;
			unsigned int	CurrentActorSizeFactor;
			bool			ActorListResized;
		};
	}
}