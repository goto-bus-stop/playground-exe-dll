#include <windows.h>
#include <stdio.h>

#define export __declspec(dllexport)

int shared = 0;

void runSubprocess() {
  STARTUPINFO info={sizeof(info)};
  PROCESS_INFORMATION processInfo;
  if (CreateProcess("b.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
  }
}

export void callDll() {
  HANDLE a = LoadLibrary("a.exe");
  int(*fn)() = GetProcAddress(a, "SPInit");
  printf("value: %d\n", fn());
  FreeLibrary(a);
}

int main() {
  printf("callDll:\n");
  callDll();
  callDll();
  printf("shared = %d\n\n", shared);
  printf("runSubprocess:\n");
  runSubprocess();
  runSubprocess();
  return 0;
}

BOOL WINAPI DllMain (HINSTANCE dll, DWORD reason, void* reserved) {
  printf("DllMain() with reason: %d\n", reason);
  shared += reason;
}

export int SPInit() {
  shared += 100;
  return shared;
}
