#ifndef __KOALAEXCEPTION_H__
#define __KOALAEXCEPTION_H__

#include <iostream>
#include <string>

namespace koala
{
	class KoalaException
	{
		KoalaException() {}
		KoalaException(std::string str)
		{
			std::cout << str << std::endl;
		}
		~KoalaException() {}

	};
}

#endif