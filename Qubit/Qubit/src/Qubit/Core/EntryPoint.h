#pragma once
#include <QubitPCH.h>
#include "Qubit/Application/Application.h"

int main(int argc, char** argv) {
	Qubit::Application::Init();
	Qubit::Application* app = Qubit::Application::GetInstance();
	app->Run();

	std::cin.get();
}