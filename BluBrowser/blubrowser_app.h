// Some code in this file are Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
// Other code Copyright (c) Aaron M. Shea 2014 for the BLUI project

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "script_handler.h"
#include "include/cef_app.h"

class BluBrowser : public CefApp,
                  public CefBrowserProcessHandler,
				  public CefRenderProcessHandler {
 public:
  BluBrowser();

  // CefApp methods:
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
      OVERRIDE { return this; }

  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()
	  OVERRIDE { return this; }

  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() OVERRIDE;

 private:
  // Include the default reference counting implementation.

  virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		 CefRefPtr<CefFrame> frame,
		 CefRefPtr<CefV8Context> context) OVERRIDE;

  virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
												CefRefPtr< CefCommandLine > command_line) OVERRIDE;

  BluScriptHandler* handler;

  IMPLEMENT_REFCOUNTING(BluBrowser);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
