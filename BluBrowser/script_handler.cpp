// Code Copyright (c) Aaron M. Shea 2014 for the BLUI project

#include "script_handler.h"
#include "include/wrapper/cef_helpers.h"

BluScriptHandler::BluScriptHandler(CefRefPtr<CefBrowser> browser)
{
	this->browser = browser;
}

bool BluScriptHandler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{

	// CEF_REQUIRE_RENDERER_THREAD();

	// Our event function
	if (name == "blu_event") {

		if (arguments.size() < 2)
		{
			exception = "Invalid number of arguments! (two required)";
			return true;
		}

		if (!arguments[0]->IsString() || !arguments[1]->IsString())
		{
			exception = "Both parameters must be strings. If you would like to pass a JSON object, please convert it to a string!";
			return true;
		}

		// Get the first argument as a string, used for the event name
		CefString event_name = arguments[0]->GetStringValue();

		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("blu_event");

		// Event ID
		msg->GetArgumentList()->SetString(0, event_name);

		// Event Data
		msg->GetArgumentList()->SetString(1, arguments[1]->GetStringValue());

		// Set the type of the event for UE4 to parse
		msg->GetArgumentList()->SetString(2, "js_event");

		if (browser == nullptr)
		{
			exception = "Browser pointer at NULL";
			return true;
		}

		// Send the message to the browser process
		browser->SendProcessMessage(PID_BROWSER, msg);

		// return a true value in js context
		retval = CefV8Value::CreateBool(true);

		// We're done
		return true;
	}

	// Function does not exist.
	return false;
}