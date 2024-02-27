// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2022-2024 Thomas Basler and others
 */
#include "WebApi_productionhistory.h"
#include "Configuration.h"
#include "WebApi.h"
#include "WebApi_errors.h"
#include <AsyncJson.h>

void WebApiProductionHistory::init(AsyncWebServer& server, Scheduler& scheduler)
{
    using std::placeholders::_1;

    server.on("/api/production-history/url", HTTP_GET, std::bind(&WebApiProductionHistory::onGetUrl, this, _1));
    server.on("/api/production-history/url", HTTP_POST, std::bind(&WebApiProductionHistory::onSetUrl, this, _1));
}

void WebApiProductionHistory::onGetUrl(AsyncWebServerRequest* request)
{
    if (!WebApi.checkCredentialsReadonly(request)) {
        return;
    }

    AsyncJsonResponse* response = new AsyncJsonResponse();
    auto& root = response->getRoot();
    const CONFIG_T& config = Configuration.get();

    root["production_history_url"] = config.ProductionHistory.Url;

    response->setLength();
    request->send(response);
}

void WebApiProductionHistory::onSetUrl(AsyncWebServerRequest* request)
{
    if (!WebApi.checkCredentials(request)) {
        return;
    }

    AsyncJsonResponse* response = new AsyncJsonResponse();
    auto& retMsg = response->getRoot();
    retMsg["type"] = "warning";

    if (!request->hasParam("url", true)) {
        retMsg["message"] = "URL not provided!";
        retMsg["code"] = WebApiError::GenericNoValueFound;
        response->setLength();
        request->send(response);
        return;
    }

    const String url = request->getParam("url", true)->value();

    if (url.length() > 256) {
        retMsg["message"] = "URL is too long!";
        retMsg["code"] = WebApiError::GenericDataTooLarge;
        response->setLength();
        request->send(response);
        return;
    }

    CONFIG_T& config = Configuration.get();
    strlcpy(config.ProductionHistory.Url, url.c_str(), sizeof(config.ProductionHistory.Url));

    retMsg["type"] = "success";
    retMsg["message"] = "URL updated!";
    retMsg["code"] = WebApiError::GenericSuccess;

    response->setLength();
    request->send(response);
}
