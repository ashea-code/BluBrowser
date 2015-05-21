// Code Copyright (c) Aaron M. Shea 2014 for the BLUI project
#pragma once
#include "include/cef_app.h"

class BluScriptHandler : public CefV8Handler {

public:

//	BluScriptHandler::BluScriptHandler(CefRefPtr<CefBrowser> browser);
	BluScriptHandler(CefRefPtr<CefBrowser> browser);

	CefRefPtr<CefBrowser> browser;

	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception) override;

    ~BluScriptHandler() { };

	// Provide the reference counting implementation for this class.
	IMPLEMENT_REFCOUNTING(BluScriptHandler);
};
