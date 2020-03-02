#pragma once
#include "HttpRouteApplication.h"

HTTPRequestHandler* HTTPRouteHandlerFactory::createRequestHandler(const HTTPServerRequest& request) {
	string _path = URI(request.getURI()).getPath();
	string _method = request.getMethod();

	try {
		Method method = map.at(_path +"_" + _method);
		if (method.first == _method)
			return method.second();
		else
			return 0;
	}
	catch (const out_of_range& oor) { return 0; }
}

void HttpRouteApplication::routingMap(RoutingMap& m) {
	_map = m;
}


void HttpRouteApplication::initialize(Application& self) {
	loadConfiguration();
	ServerApplication::initialize(self);
}

void HttpRouteApplication::uninitialize() {
	ServerApplication::uninitialize();
}


void HttpRouteApplication::defineOptions(OptionSet& options) {
	ServerApplication::defineOptions(options);

	options.addOption(
	Option("help", "h", "display argument help information")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<HttpRouteApplication>(
			this, &HttpRouteApplication::handleHelp)));
}


void HttpRouteApplication::handleHelp(const std::string& name, const std::string& value) {
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader(
		"A http routing server.");
	helpFormatter.format(std::cout);
	stopOptionsProcessing();
	_helpRequested = true;
}


int HttpRouteApplication::main(const vector<string>& args) {
	if (!_helpRequested) {
		unsigned short port = (unsigned short) config().getInt("HttpRouteApplication.port", _mainPort);

		ServerSocket svs(port);
		_httpSvr = new HTTPServer(new HTTPRouteHandlerFactory(_map), svs, new HTTPServerParams);
		_httpSvr->start();
		//waitForTerminationRequest();
		//srv.stop();
	
	}
	
	return Application::EXIT_OK;
}
