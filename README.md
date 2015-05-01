# BluBrowser for [BLUI](https://github.com/AaronShea/BLUI)

## What?
This is the CEF code of the child process for BLUI. **It's not recommended to mess with this at the moment.** It's a modified CefSimple example to include the blu_event function which notifies BLUI of Javascript events in the UE4 game engine.

## How do I compile this? (Windows only right now)
* Well, first you need to nab a zip from the [CEF Builds Site](http://cefbuilds.com/) (I used branch 2272).
* Replace the code in CefSimple with the code in this repository, the original project has some configuration that needs to be kept for output to work correctly.
* (If you want to build the wrapper lib for use in UE4) Open the solution in Visual Studio and change the project options in "libcef\_dll\_wrapper" to output a "multi-threaded DLL", and build.
* (If you want to build the blu_browser.exe process) Switch "libcef\_dll\_wrapper" to output "Multi-threaded (/MT)"
* Build the solution, and it will produce the proper dlls, lib files, or the child process exe.

(Again, I don't recommend this, I will be distributing the correct binaries in BLUI releases on [It's repo page!](https://github.com/AaronShea/BLUI))
