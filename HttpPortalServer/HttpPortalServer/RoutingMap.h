#pragma once

#include "BaseHeader.h"

using namespace std;


template<typename T>
HTTPRequestHandler* createInstance() { return new T; }

typedef std::pair<string, HTTPRequestHandler* (*)()> Method;
typedef map<string, Method> RoutingMap;

template<typename T>
void addRouteMapItem(RoutingMap &map, string _method, string _uri) {
	map[_uri+"_" +  _method] = Method(_method, &createInstance<T>);
}
