#pragma once
#include <QubitPCH.h>
#include "Layer.h"

namespace Qubit{
	layer::layer() {name = "Layer";}
	layer::layer(const char* n) {name = n;}

	void layer::OnAttatch() {

	}

	void layer::OnDetatch() {

	}

	void layer::OnUpdate() {

	}

	void layer::OnEvent(event& event) {

	}

	layer::~layer() {}

	bool layer::operator==(const layer& otherL) {
		return this->name == otherL.name;
	}
	
	bool layer::operator==(const char* i_name) {
		return this->name == i_name;
	}
}