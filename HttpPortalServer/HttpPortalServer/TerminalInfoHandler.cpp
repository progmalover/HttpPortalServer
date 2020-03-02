#pragma once
#include "..\BaseHeader.h"
#include "..\BaseHttpTokenHandler.h"
#include <sstream>
#include <ostream>
#include <istream>
#include <string>
//#include "Router.cpp"
using namespace std;


class HelloRequestHandler : public BaseHttpHandler {
public:
	void doHandleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {

		Application& app = Application::instance();
		app.logger().information("Request from " + request.clientAddress().toString());


		bool _bEnc = request.getChunkedTransferEncoding();

		response.setChunkedTransferEncoding(_bEnc);
		response.setContentType("text/html");

		std::ostream& ostr = response.send();
	}
};

