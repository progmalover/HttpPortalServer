#pragma once
#include "..\BaseHeader.h"
#include "..\BaseHttpTokenHandler.h"
#include <sstream>
#include <ostream>
#include <istream>
#include <string>
//#include "Router.cpp"
using namespace std;


class TerminalInfoHandler : public BaseHttpHandler {
public:
	void doHandleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {

		Application& app = Application::instance();
		app.logger().information("Request from " + request.clientAddress().toString());


		bool _bEnc = request.getChunkedTransferEncoding();

		response.setChunkedTransferEncoding(_bEnc);
		response.setContentType("application/json");

		std::ostream& ostr = response.send();
		ostr << "[{ \"terminal_name\": \"termial_1\", \"ip\" : \"192.168.1.1\" ,\"mac\":\"xx:xx:xx:xx:xx:xx\"},{ \"terminal_name\": \"termial_2\",\"ip\" : \"192.168.1.1\" ,\"mac\":\"xx:xx:xx:xx:xx:xx\"},{ \"terminal_name\": \"termial_3\", \"ip\" : \"192.168.1.1\" ,\"mac\":\"xx:xx:xx:xx:xx:xx\"}]";
		ostr.flush();
	}
};

