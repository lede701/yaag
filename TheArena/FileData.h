#ifndef H_FILEDATA
#define H_FILEDATA
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define MAXFDATASIZE 256

namespace Zaxis
{

	using std::ifstream;
	using std::ofstream;
	using std::string;

	template<class T>
	class FileData
	{
	private:
		T Data[MAXFDATASIZE];

		unsigned int front;
		unsigned int back;
		unsigned int pos;
		int _version;
		int _count;

	public:
		FileData();
		FileData(int version);
		~FileData();

		void Init();

		int GetVersion();

		bool Add(T);
		bool Add(T, unsigned int id);
		T Front();
		T Back();
		T Current();
		T GetAt(unsigned int p);
		bool Find(T item);

		unsigned int CurrentPos();
		unsigned int NextPos();
		unsigned int NextPos(unsigned int val);
		unsigned int PrevPos();
		unsigned int PrevPos(unsigned int val);
		unsigned int GetNextId();
		unsigned int Count();

		bool Load(string file);
		bool Save(string file);
	};


	// Template definitions
	template<class T>
	FileData<T>::FileData(int version)
	{
		_version = version;
		Init();
	}

	// Template definitions
	template<class T>
	FileData<T>::FileData()
	{
		_version = 1;
		Init();
	}

	template<class T>
	void FileData<T>::Init()
	{
		memset(&Data, 0, sizeof(Data));
		front = back = pos = 0;
	}

	template<class T>
	FileData<T>::~FileData()
	{

	}

	template<class T>
	int FileData<T>::GetVersion()
	{
		return _version;
	}

	template<class T>
	bool FileData<T>::Add(T item)
	{
		bool bRetVal = false;
		// Check if structure is not full and item is not already on the list
		if (front != NextPos(back))
		{
			Data[back] = item;
			bRetVal = true;
			back = NextPos(back);
		}

		return bRetVal;
	}

	template<class T>
	bool FileData<T>::Add(T item, unsigned int id)
	{
		bool bRetVal = false;
		if (id < MAXFDATASIZE)
		{
			Data[id] = item;
			if (front == back)
			{
				back = NextPos();
			}
			bRetVal = true;
			_count++;
		}

		return bRetVal;
	}

	template<class T>
	T FileData<T>::Front()
	{
		pos = front;
		return Data[pos];
	}

	template<class T>
	T FileData<T>::Back()
	{
		pos = PrevPos(back);
		return Data[pos];
	}

	template<class T>
	T FileData<T>::Current()
	{
		return Data[pos];
	}

	template<class T>
	T FileData<T>::GetAt(unsigned int p)
	{
		T item;
		memset(&item, 0, sizeof(T));
		if (p < MAXFDATASIZE)
		{
			return Data[p];
		}
		return item;
	}

	template<class T>
	unsigned int FileData<T>::CurrentPos()
	{
		return pos;
	}

	template<class T>
	unsigned int FileData<T>::NextPos(unsigned int val)
	{
		return (val + 1) % MAXFDATASIZE;
	}

	template<class T>
	unsigned int FileData<T>::NextPos()
	{
		pos = NextPos(pos);
		return pos;
	}

	template<class T>
	unsigned int FileData<T>::PrevPos(unsigned int val)
	{
		if (val == 0)
		{
			return MAXFDATASIZE;
		}
		return val - 1;
	}

	template<class T>
	unsigned int FileData<T>::PrevPos()
	{
		pos = PrevPos(pos);
		return pos;
	}

	template<class T>
	bool FileData<T>::Load(string file)
	{
		bool bRetVal = false;
		Init();

		ifstream fin;
		fin.open(file, std::ios::binary);
		if (fin.good())
		{
			int size = 0;
			fin.read((char*)&_version, sizeof(int));
			fin.read((char*)&size, sizeof(int));
			if (size > 0 && size < MAXFDATASIZE)
			{
				_count = size;
				for (int i = 0; i < size; i++)
				{
					T item;
					fin.read((char*)&item, sizeof(T));
					Add(item);
				}
			}
			bRetVal = true;
		}
		fin.close();

		return bRetVal;
	}

	template<class T>
	bool FileData<T>::Save(string file)
	{
		bool bRetVal = false;

		ofstream fout;
		fout.open(file, std::ios::binary | std::ios::trunc);
		int size = back - front;
		if (fout.good())
		{
			// Write file header
			fout.write((char*)&_version, sizeof(int));
			fout.write((char*)&size, sizeof(int));
			// Set position to front of list
			pos = front;
			while (pos != back)
			{
				// Write record to file
				fout.write((char*)&Data[pos], sizeof(T));
				pos = NextPos(pos);
			}
			bRetVal = fout.good();
		}

		fout.close();

		return bRetVal;
	}

	template<class T>
	unsigned int FileData<T>::GetNextId()
	{
		return NextPos(back);
	}

	template<class T>
	unsigned int FileData<T>::Count()
	{
		return _count;
	}

	template<class T>
	bool FileData<T>::Find(T item)
	{
		bool bRetVal = false;
		unsigned int p = front;
		// Check if the current position is pointing at the item
		/*
		if (Data[p] == item)
		{
			bRetVal = true;
		}
		else
		{
			do
			{
				if (Data[p] == item)
				{
					bRetVal = true;
					pos = p;
					break;
				}
				p = NextPos(p);
			} while (p != front);
		}*/

		return bRetVal;
	}

}// End namespace Zaxis


#endif