#pragma once

#include "core.h"
#include "Model.h"


class CGPrincipleAxes : public Model {

private:


public:

	CGPrincipleAxes();
	~CGPrincipleAxes();

	void Load(ifstream& _file);

	void Render();
};
