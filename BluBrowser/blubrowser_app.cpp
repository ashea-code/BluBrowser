// Some code in this file are Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
// Other code Copyright (c) Aaron M. Shea 2014 for the BLUI project

#include "blubrowser_app.h"

#include <string>

#include "blu_handler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
#include "cefsimple/script_handler.h"

BluBrowser::BluBrowser() {
}

void BluBrowser::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  // Information used when creating the native window.
  CefWindowInfo window_info;

#if defined(OS_WIN)
  // On Windows we need to specify certain flags that will be passed to
  // CreateWindowEx().
  window_info.SetAsPopup(NULL, "BLUI");
#endif

  // BluHandler implements browser-level callbacks.
  CefRefPtr<BluHandler> handler(new BluHandler());

  // Specify CEF browser settings here.
  CefBrowserSettings browser_settings;
  browser_settings.file_access_from_file_urls = STATE_ENABLED;
  browser_settings.universal_access_from_file_urls = STATE_ENABLED;

  std::string url;

  // Check if a "--url=" value was provided via the command-line. If so, use
  // that instead of the default URL.
  CefRefPtr<CefCommandLine> command_line =
      CefCommandLine::GetGlobalCommandLine();
  url = command_line->GetSwitchValue("url");
  if (url.empty())
    url = "chrome://flags";

  // Create the first browser window.
  CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
                                browser_settings, NULL);

}

void BluBrowser::OnContextCreated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context)
{

	// no handler yet, we need to create it first
	handler = new BluScriptHandler(browser);

	// Retrieve the context's window object.
	CefRefPtr<CefV8Value> object = context->GetGlobal();

	CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("blu_event", handler);

	// Add the string to the window object as "window.myval". See the "JS Objects" section below.
	object->SetValue("blu_event", func, V8_PROPERTY_ATTRIBUTE_NONE);
}

void BluBrowser::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{

}
