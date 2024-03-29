#include "pch.h"
#include "GameMain.h"
//
#include "Level/Level.h"
#include "Level/World.h"
////#include "Level/Actor/SpriteActor/Sprite.h"
#include "Level/Actor/StaticMesh/StaticMesh.h"
#include <iostream>


//using namespace Engine;
//using namespace Level;

void GameMain::Initialize()
{
	//빌드 후 이벤트로 특정헤더파일에 포함시키기
	auto staticMesh = Engine::Level::SLevel::GetWorld()->CreateActor<Engine::Level::AStaticMesh>("MeshTest");

	/*
	0. 텍스트 파싱해서 소스 코드를 만들기. 또는 스크립트의 클래스 등록하기.... 어쩔수없다.
	0. 스크립트 런타임 객체에 스크립트 이름들을 등록해놓기. 스크립트용 클래스들은 인터페이스 상속받아서 구현하기.(자신이 상속받던지, 인터페이스를 구체화시키던지)
	1. 엔진에서 스크립트 이름을가져오기. 스크립트용 런타임 컨텍스트를 통해 해당 클래스 생성.
	2. 엔진의 스크립트 컴포넌트의 인터페이스에 생성한 인터페이스를 연결하기.
	*/

	//DirectX::Vertex
}


