#pragma once
#include ".\BaseHeader.h"
#include <string>
class BaseHttpHandler :
	public HTTPRequestHandler
{
protected:
	void parseParameters(HTTPServerRequest & request);
	std::string readContent(HTTPServerRequest & request);

public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		parseParameters(request);
		doHandleRequest(request, response);
	};

	virtual void doHandleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {}
protected:
	URI::QueryParameters  uri_params;
	Array::Ptr json_arr_params;
	Object::Ptr json_obj_params;
};

class BaseHttpTokenHandler :
	public BaseHttpHandler
{
public:
	 void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
	 virtual void doHandleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {}
protected:

};
