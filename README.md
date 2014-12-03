# BluBrowser for [BLUI](https://github.com/aaron524/BLUI)

## What?
This is the CEF code of the child process for BLUI. **It's not recommended to mess with this at the moment.** It's a modified CefSimple example to include the blu_event function which notifies BLUI of Javascript events in the UE4 game engine.

## How do I compile this? (Windows only right now)
* Well, first you need to nab a zip from the [CEF Builds Site](http://cefbuilds.com/) (I used branch 2171).
* Open the solution in Visual Studio and change the project options in "libcef\_dll\_wrapper" and "CefSimple" to output a multi-threaded DLL. (IMPORTANT)
* Replace the code in CefSimple with the code in this repository, the original project has some configuration that needs to be kept for output to work correctly.
* Build the solution, and it will produce the proper dlls, lib files, and the child process exe in the folder called "out".

(Again, I don't recommend this, I will be distributing the correct binaries in BLUI released on [It's repo page!](https://github.com/aaron524/BLUI)