#ifndef H_ICONTROLLER
#define H_ICONTROLLER

#define LPCONTROLLER Zaxis::Controllers::IController*

namespace Zaxis{ namespace Controllers
{

	class IController
	{
	public:
		IController();
		virtual ~IController();

		virtual bool ChkInput(int vk) = 0;
		virtual char GetInput() = 0;
		virtual void Update() = 0;
	};

} }// End namespace Zaxis::Controllers


#endif