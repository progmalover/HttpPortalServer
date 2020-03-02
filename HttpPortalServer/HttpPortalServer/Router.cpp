#pragma once

#include "RoutingMap.h"
#include "Portal\HelloRequestHandler.cpp"
#include "Portal\PortalRequestHandler.cpp"
#include "Portal\TerminalInfoHandler.cpp"
#include "Portal\PushMessageHandler.cpp"
#include "Portal\HelloRootHandler.cpp"

/*
It has two ways to use router:
1.For each interface to build divided requesthandler.
2.For each interface to reuse one requesthandler but need to append more info about method invoking.
*/
void  createRouter(RoutingMap &map) {
	addRouteMapItem<HelloRequestHandler>(map, "POST", "/");
	addRouteMapItem<PortalRequestHandler>(map, "GET", "/portal");
	addRouteMapItem<TerminalInfoHandler>(map, "GET", "/portal/terminal_info");
	addRouteMapItem<PushMessageHandler>(map, "POST", "/portal/PushMessage");
	addRouteMapItem<HelloRootHandler>(map, "POST", "/portal/HelloRoot");

}