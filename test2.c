#include <windows.h>
#include <stdio.h>

void callDll() {
  HANDLE a = LoadLibrary("a.exe");
  int(*fn)() = GetProcAddress(a, "SPInit");
  printf("value: %d\n", fn());
  FreeLibrary(a);
}

int main() {
  callDll();
  return 0;
}
