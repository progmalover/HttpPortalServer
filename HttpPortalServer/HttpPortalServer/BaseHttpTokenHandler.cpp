#pragma once
#include "BaseHttpTokenHandler.h"
#include "TokenAuthor.h"

using namespace std;
void BaseHttpTokenHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	string _token;
	bool _hasToken = request.hasToken(TokenAuthor::XAUTHOR, _token);
	//Support tocken authorization
	int status = (int)HTTPServerResponse::HTTPStatus::HTTP_NETWORK_AUTHENTICATION_REQUIRED;
	if (_hasToken ){
		int cause = 0;
		if (!TokenAuthor::Inst()->tokenIsAvalaible(_token, cause)) {
			switch (cause)
			{
			case TokenAuthor::EXPIRED:
				status += 1; //512
				break;
			case TokenAuthor::MISMATCH:
				status += 2; //513
				break;
			case TokenAuthor::NOTEXIST:
				status += 3; //514
				break;
			}
		}
		else {
			parseParameters(request);
			doHandleRequest(request, response);
			return;
		}
	}
	response.setStatus(HTTPServerResponse::HTTPStatus(status));
	response.setContentType("text/html");
	ostream &os = response.send();
	os << "Request failed on token authorization!";
	os.flush();
}

string BaseHttpHandler::readContent(HTTPServerRequest & request) {
	Application &app = Application::instance();
	istream &istr = request.stream();
	ostringstream os;

	while (!istr.eof()) {
		string line;
		std::getline(istr, line);
		//app.logger().information(line.c_str());
		os << line;
	}

	app.logger().information(("Request content:" + os.str()).c_str());

	return os.str();
}

void BaseHttpHandler::parseParameters(HTTPServerRequest & request)
{
	string _uri = request.getURI();
	string _method = request.getMethod();
	string _contentType = request.getContentType();

	/*
	Only support json body and parameters with uri.  --maxwell.z
	*/

	URI uri(_uri);
	uri_params = uri.getQueryParameters();

	if (_method == "POST"){
		if (_contentType == "application/json")
		{
			Parser parser;
			string content = readContent(request);
			Var var_json = parser.parse(content);
			//if(var_json)
			try {
				bool bArray = var_json.isArray();
				if(bArray)
					json_arr_params = var_json.extract<Array::Ptr >();
				else
					json_obj_params = var_json.extract<Object::Ptr>();
			}
			catch(BadCastException &) {}
			catch (InvalidAccessException &) {}

		}
	}
 }