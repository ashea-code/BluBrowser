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

		if (!arguments[0]->IsString())
		{
			exception = "Parameter 1 must be a string!";
			return true;
		}

		// Get the first argument as a string, used for the event name
		CefString event_name = arguments[0]->GetStringValue();

		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("blu_event");

		// Event ID
		msg->GetArgumentList()->SetString(0, event_name);

		// Now we need to see what type of data they passed
		if (arguments[1]->IsBool())
		{
			msg->GetArgumentList()->SetBool(1, arguments[1]->GetBoolValue());
			msg->GetArgumentList()->SetString(3, "bool");
		}
		else if (arguments[1]->IsString())
		{
			msg->GetArgumentList()->SetString(1, arguments[1]->GetStringValue());
			msg->GetArgumentList()->SetString(3, "string");
		}
		else if (arguments[1]->IsDouble())
		{
			msg->GetArgumentList()->SetDouble(1, arguments[1]->GetDoubleValue());
			msg->GetArgumentList()->SetString(3, "double");
		}
		else if (arguments[1]->IsInt())
		{
			msg->GetArgumentList()->SetInt(1, arguments[1]->GetIntValue());
			msg->GetArgumentList()->SetString(3, "int");
		}
		else
		{
			exception = "Parameter 2 - unsupported type! (int, double, string and bool only)";
			return true;
		}


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
