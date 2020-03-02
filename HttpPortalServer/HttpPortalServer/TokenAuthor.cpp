#include "BaseHeader.h"
#include "TokenAuthor.h"

const string TokenAuthor::XAUTHOR = "ve_x_au";

 TokenAuthor * TokenAuthor::Inst() {
	static TokenAuthor *pInst = new TokenAuthor();
	return pInst;
}

bool  TokenAuthor::tokenIsAvalaible(string & token,int &cause) {
	 cause = TokenAuthor::OK;

	 try {
		 t_map.at(token);
	 }
	 catch (const out_of_range& oor) { cause = TokenAuthor::NOTEXIST; }

	 return true;
 }

 bool TokenAuthor::updateToken(string &token)
 {
	 t_map[token] = tockenSample();
	 return true;
 }

 void TokenAuthor::removeToken(string &token)
 {
	 try {
		 t_map.at(token);
	 }
	 catch (const out_of_range& oor) { return; }
	 t_map.erase(token);
 }

 //Build simply UUID-MD5 token here,i think maybe merge ip, user, and creation time 
 //to token and change MD5 to DES,this should downgrade the risk.
 string createToken()
 {
	 UUIDGenerator& gen = Poco::UUIDGenerator::defaultGenerator();
	 string strUUID = gen.createRandom().toString();

	 MD5Engine md5;
	 md5.update(strUUID.c_str(), strUUID.length());
	 return MD5Engine::digestToHex(md5.digest());

 }