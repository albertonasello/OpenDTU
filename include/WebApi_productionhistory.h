// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <ESPAsyncWebServer.h>
#include <TaskSchedulerDeclarations.h>

class WebApiProductionHistory {
public:
    void init(AsyncWebServer& server, Scheduler& scheduler);

private:
    void onGetUrl(AsyncWebServerRequest* request);
    void onSetUrl(AsyncWebServerRequest* request);
};
