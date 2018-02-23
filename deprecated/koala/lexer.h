#ifndef __LEXER_H__
#define __LEXER_H__

#include <regex>
#include <string>
#include <list>
#include "token.h"
#include "lineNumberReader.h"

namespace koala
{
	class Lexer
	{
	public:
		std::string regexPatern = "[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|&&|\|\||\p{Punct})?";
	private:
		const std::regex regexPat(regexPatern);
		std::list<Token> queue;
		bool hasMore;
		LineNumberReader reader;

	public:
		Lexer(Reader r)
		{
			hasMore = true;
			reader(LineNumberReader(r));
		}
	};
}

#endif