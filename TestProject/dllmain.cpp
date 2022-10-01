// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
//#include "GameMain.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{    
    switch (ul_reason_for_call)
    {        
    case DLL_PROCESS_ATTACH:
    {        
        //DLL을 로드하면, DLL 자체적으로 돌도록해야함?
        /*
        스크립트를 로드.
        스크립트에 파일을 구현후, 오브젝트에 연결이 필요.
        스크립트 객체에서 게임 오브젝트의 UID를 찾아서, 게임 오브젝트가 들고 있는 스크립트 인터페이스에 스크립트를 연결.
        엔진쪽에서는 인터페이스를 통해 스크립트 조작...
        혹은 상속구조로 만들기...
        */
    }
    break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }    

    return TRUE;
}

