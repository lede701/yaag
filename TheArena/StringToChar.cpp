#include "StringToChar.h"

void StringToChar(int maxsize, char *c_str, const std::string& str)
{
	int size = str.size();

	if (size > maxsize - 1)
	{
		size = maxsize - 1;
	}

	for (int i = 0; i < size; i++)
	{
		c_str[i] = str[i];
	}
	if (maxsize > size)
	{
		for (int i = size; i < maxsize; i++)
		{
			c_str[i] = '\0';
		}
	}
}