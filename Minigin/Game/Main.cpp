#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"
#include "Game.h"

int main(int, char*[]) {
	King::Minigin engine;
	King::Game game{};
	engine.Run();
    return 0;
}