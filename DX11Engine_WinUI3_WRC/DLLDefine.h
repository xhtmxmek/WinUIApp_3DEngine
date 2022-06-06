#pragma once
#ifdef ENGINE_LIBRARY_EXPORT
#define ENGINE_API __declspec(dllexport)
#define DLLEXPORT_TEMPLATE
#else
#define ENGINE_API __declspec(dllimport)
# define DLLEXPORT_TEMPLATE extern
#endif