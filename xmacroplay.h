#pragma once

#include <X11/Xlib.h>

extern "C"
{
  Display * remoteDisplay (const char * DisplayName);
  void xmacro_command(Display* RemoteDpy, int RemoteScreen, const char* ev);
}
