#include "pch.h"
#include "GameMain.h"

#include "Level/Level.h"
#include "Level/World.h"
//#include "Level/Actor/SpriteActor/Sprite.h"
#include "Level/Actor/StaticMesh/StaticMesh.h"


//using namespace Engine;
//using namespace Level;

void GameMain::Initialize()
{
	//���� �� �̺�Ʈ�� Ư��������Ͽ� ���Խ�Ű��
	//auto sprite = Engine::Level::ActorManager::GetInstance().CreateActor<Engine::Level::ASprite>("hello");
	//Engine::Type::shared_ptr<int> test;
	//Engine::Type::TestClass test;	
	//Engine::Level::AStaticMesh test("test");
	auto staticMesh = Engine::Level::SLevel::GetWorld()->CreateActor<Engine::Level::AStaticMesh>("MeshTest");	
	//FVector2 test;
	//test.Test();

	/*
	0. �ؽ�Ʈ �Ľ��ؼ� �ҽ� �ڵ带 �����. �Ǵ� ��ũ��Ʈ�� Ŭ���� ����ϱ�.... ��¿������.
	0. ��ũ��Ʈ ��Ÿ�� ��ü�� ��ũ��Ʈ �̸����� ����س���. ��ũ��Ʈ�� Ŭ�������� �������̽� ��ӹ޾Ƽ� �����ϱ�.(�ڽ��� ��ӹ޴���, �������̽��� ��üȭ��Ű����)
	1. �������� ��ũ��Ʈ �̸�����������. ��ũ��Ʈ�� ��Ÿ�� ���ؽ�Ʈ�� ���� �ش� Ŭ���� ����.
	2. ������ ��ũ��Ʈ ������Ʈ�� �������̽��� ������ �������̽��� �����ϱ�.
	*/

	//DirectX::Vertex
}


