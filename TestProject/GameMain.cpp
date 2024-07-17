#include "pch.h"
#include "GameMain.h"
//
#include "Level/Level.h"
#include "Level/World.h"
////#include "Level/Actor/SpriteActor/Sprite.h"
#include "Level/Actor/StaticMesh/StaticMesh.h"
#include <iostream>


//using namespace Engine;
//using namespace World;

void GameMain::Initialize()
{
	//��� �� �̺�Ʈ�� Ư��������Ͽ� ���Խ�Ű��
	auto staticMesh = Engine::Level::SLevel::GetWorld()->CreateActor<Engine::Level::AStaticMesh>("MeshTest");

	/*
	0. �ؽ�Ʈ �Ľ��ؼ� �ҽ� �ڵ带 �����. �Ǵ� ��ũ��Ʈ�� Ŭ���� ����ϱ�.... ��¿������.
	0. ��ũ��Ʈ ��Ÿ�� ��ü�� ��ũ��Ʈ �̸����� ����س���. ��ũ��Ʈ�� Ŭ�������� �������̽� ��ӹ޾Ƽ� �����ϱ�.(�ڽ��� ��ӹ޴���, �������̽��� ��üȭ��Ű����)
	1. �������� ��ũ��Ʈ �̸�����������. ��ũ��Ʈ�� ��Ÿ�� ���ؽ�Ʈ�� ���� �ش� Ŭ���� ����.
	2. ������ ��ũ��Ʈ ������Ʈ�� �������̽��� ������ �������̽��� �����ϱ�.
	*/

	//DirectX::Vertex
}


