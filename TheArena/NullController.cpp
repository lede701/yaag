#include "NullController.h"


namespace Zaxis{ namespace Controllers
{

	NullController::NullController()
	{
	}


	NullController::~NullController()
	{
	}

	bool NullController::ChkInput(int vk)
	{
		return false;
	}

	char NullController::GetInput()
	{
		return 0;
	}

	void NullController::Update()
	{
		return;
	}

} }// End namespace Zaxis::Controllers

