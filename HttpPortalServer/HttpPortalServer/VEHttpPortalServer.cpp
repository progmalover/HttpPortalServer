#pragma once
#include "HttpRouteApplication.h"
#include "RoutingMap.h"
extern void  createRouter(RoutingMap &map);
using namespace std;

static HttpRouteApplication *_pApp = 0;

static int port = 7780;
static int mode = 0; // root
static string rootIp = "";
static int  rootPort = 7780;

void SetHttpAppServerParams(int _mode, int _port, char *_rootIp, int _rootPort)
{
	mode = _mode;
	port = _port;
	rootIp = _rootIp;
	rootPort = _rootPort;
}

int StartHttpAppServer()
{
	RoutingMap map;
	createRouter(map);
	if (!_pApp)
		_pApp= new HttpRouteApplication();
	else return -1;

	_pApp->setMainPort(port);
	_pApp->routingMap(map);

	char argv[255] = { 0 };
	::GetModuleFileNameA(0, argv, 255);
	return _pApp->run(1,(char**)&argv);
}

int IsHttpAppSvrRunninng()
{
	if (!_pApp) return false;
	return _pApp->isSvrRunning();
}

void StopHttpAppServer()
{
	if (_pApp)
		_pApp->stopSvr();
	else return;

	delete _pApp;
	_pApp = 0;
}

int main(int argc, char** argv) {
	//return StartHttpServer(7780);
	HttpRouteApplication app;
	RoutingMap map;
	createRouter(map);
	//server.setMainPort(port);
	app.routingMap(map);

	//char *argv[1] = { 0 };
	return app.run(argc,argv);
}
