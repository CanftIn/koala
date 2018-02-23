#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include "koalaException.h"

namespace koala
{
	class Token
	{
	public:
#ifndef EOF
		const int EOF = -1;
#endif // EOF

		const std::string EOL = "\\n";
	private:
		int lineNumber;

	public:
		Token(int line) : lineNumber(line) {}

		~Token() {}

		int getLineNumber()
		{
			return lineNumber;
		}

		bool isIdentifier()
		{
			return false;
		}

		bool isNumber()
		{
			return false;
		}
		
		bool isString()
		{
			return false;
		}

		int getNumber()
		{
			//TODO
			//throw new KoalaException("not number token");
			std::cout << "not number token" << std::endl;
		}

		std::string getText()
		{
			return "";
		}

	};
}

#endif // !__TOKEN_H__
