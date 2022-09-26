// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
//#include "EngineMinimal.h"
#include <string>
#include <memory>
#include <map>
#include <unordered_map>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include "SimpleMath.h"
//#include "SpriteBatch.h"

#include "Level/Actor/ActorManager/ActorManager.h"
#include "Level/Actor/SpriteActor/Sprite.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Level/Component/StaticMeshComponent/StaticMeshComponent.h"
#include "Common/Math/TransformGroup.h"
#include "Level/World.h"


using namespace DirectX::SimpleMath;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    std::shared_ptr<Engine::Level::ASprite> sprite;
    switch (ul_reason_for_call)
    {        
    case DLL_PROCESS_ATTACH:
    {        
        //TestActor test;        
        sprite = Engine::Level::ActorManager::GetInstance().CreateActor<Engine::Level::ASprite>("hello");
        size_t actorCount = Engine::Level::ActorManager::GetInstance().GetNumActorList();
        int k = 5;
        //Engine::Component::SpriteComponent* spriteComponent;
        //spriteComponent = nullptr;
        //spriteComponent->SetRotation(Vector3(1, 1, 1));        
    }
    break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }    

    return TRUE;
}

