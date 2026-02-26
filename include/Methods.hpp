#pragma once

#include "../include/Request.hpp"
#include "../include/Response.hpp"

void handleGET(const Request& req, Response& res);
void handlePOST(const Request& req, Response& res);
void handleDELETE(const Request& req, Response& res);
