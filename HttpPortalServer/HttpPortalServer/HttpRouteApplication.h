#include "BaseHeader.h"
#include "RoutingMap.h"

using namespace std;

class HTTPRouteHandlerFactory : public HTTPRequestHandlerFactory {
public:
	HTTPRouteHandlerFactory(RoutingMap& m) :
		map(m) {
	}

	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);
private:
	RoutingMap map;
};

class HttpRouteApplication: public ServerApplication {
public:
	HttpRouteApplication(): _helpRequested(false), _mainPort(7789),_httpSvr(0){ }
    ~HttpRouteApplication() { }
	
	void routingMap(RoutingMap& m);
	void setMainPort(int port) { _mainPort = port; }
	void stopSvr() {
		if (_httpSvr != 0)
			_httpSvr->stopAll(true);
		this->terminate();
		delete _httpSvr;
		_httpSvr = 0;
	}
	bool isSvrRunning()
	{
		if (!_httpSvr)
			return false;
		return true;
	}
protected:
	
    void initialize(Application& self);
    void uninitialize();
    void defineOptions(OptionSet& options);
    void handleHelp(const string& name, const string& value);
	int main(const vector<string>& args);

private:
    bool _helpRequested;
	RoutingMap _map;
	int _mainPort;
	HTTPServer * _httpSvr;
};
