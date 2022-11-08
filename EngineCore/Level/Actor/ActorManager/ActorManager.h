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

		//���Ͱ� ����Ǹ� ActorManager�� �����ؾ� �ϰ� ActorManager�����ϸ� �� ģ���� �����ϴ� ��� �ҽ����ϵ� �ٽ� �����ؾ���. ActorManager���� ��û�ϴ� ���� ���ϵ��� �������ε�...
		//�ٵ� Actor�Ŵ������� Actor�� ��û�ؼ� ���� �༮���� cpp������ ������ Actor�� ���Խ��Ѿ���.
		//Actor�� ����, Actor�Ŵ����� ����, Actor�Ŵ����� ��� �ִ� ������ ����.
		//Actor�� �������̽� �����Ǹ� ��������� ���� ����. �ڽĵ��� ����Ǵ� ������.
		//SingleTon���� ����������, ���������� singleTon�� �ƴϾ �Ǹ� �̱������� ������ ����.
		class ActorManager : public Uncopyable
		{
		public:
			ENGINE_API static ActorManager& GetInstance()
			{
				static ActorManager actor;
				return actor;
			}

			void ReleaseInstance();
			void Init();

			template<typename T>
			std::shared_ptr<T> CreateActor(const std::string& name)
			{
				CheckActorListCapacity();
				//�����Ҷ� �̸��� ������� ó���ϴ� ����(ex-�ڿ�_#�� ���δٴ���)�� �����غ���								
				auto newActor = CreateActor(T::ClassName(), name);
				std::shared_ptr<T> newActorPtr(std::static_pointer_cast<T>(newActor));
				return newActorPtr;
			}

			std::shared_ptr<Actor> GetActorByName(const std::string& actorName);

			ENGINE_API size_t GetNumActorList();
		private:			
			//func
			ActorManager() : CurrentActorSizeFactor(1), ActorListResized(false){}			
			ENGINE_API void CheckActorListCapacity();
			ENGINE_API std::shared_ptr<Actor> CreateActor(const std::string& className, const std::string& instanceName);
			//Actor* CreateActor(const std::string& className, const std::string& instanceName);			

			//��� ����
			std::unordered_map<const char*, std::shared_ptr<Actor>> Actors;
			//public���� �����ؼ� �ܺο��� ��������� �����Ͱ����� �׶� ����
			const size_t	ActorsSizeUnit = 1000;
			const size_t	ActorSizeBias = 5;
			unsigned int	CurrentActorSizeFactor;
			bool			ActorListResized;
		};
	}
}