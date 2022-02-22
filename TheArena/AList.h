#ifndef H_ALIST
#define H_ALIST

#define MAXLISTSIZE 16

namespace Zaxis{ namespace Engine{ namespace Data
{
	template<class T>
	class AList
	{
	private:
		T* list[MAXLISTSIZE];
		int front;
		int back;

		int _size;

	public:
		AList();
		virtual ~AList();

		int NextIndex(int val);
		int PrevIndex(int val);

		T* push_back(T item);
		T* push_front(T item);
		T pop_back();
		T pop_front();
		T RmItem(int idx);


		T GetPos(int idx);
		int Front();
		int Back();

		int size();
	};

} } }// End namespace Zaxis::Engine::Data

#endif