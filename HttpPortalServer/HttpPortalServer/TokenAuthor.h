#pragma once
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <time.h>
using namespace std;
class TokenAuthor
{
public:
	enum {
		OK = 0,
		EXPIRED = -1,
		MISMATCH = -2,
		NOTEXIST = -3
	};
		
	TokenAuthor() {}
	bool tokenIsAvalaible(string &token ,int &cause);
	bool updateToken(string &token);
	void removeToken(string &token);
	string& createToken();
	
	static TokenAuthor *Inst();
	static const string XAUTHOR;
protected:
	struct tockenSample {
		tockenSample() {
			time = ::time(NULL);
		}
		time_t time;
	};
	typedef map<string, tockenSample>  token_map;
	token_map  t_map;
};

