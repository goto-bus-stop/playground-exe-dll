# playground-exe-dll

Trying to load a running exe as a DLL.

## Goals

I want to use my application to tell a third party program to start, and to use a custom DLL for some behaviours. The third party program has a facility to tell it which DLL to use. I don't want to ship a separate DLL file, but instead embed it inside my application .exe.

Sharing state between the exe and DLL is not necessary, but interesting to see how Windows does that—if loading a .exe that has a running instance as a DLL maybe just uses the memory space of the already running exe. My understanding is that loading a DLL multiple times does share memory, after all…

## Findings

`test.c` → `a.exe` is the entry point.
`test2.c` → `b.exe` is started by `a.exe`, and calls into `a.exe`.

- You can in fact just export functions from a .exe using `__declspec(dllexport)`.
- Defining a `DllMain()` inside a .exe appears to work, although I cannot get it to output anything using `printf` … side effects of its execution are observable, though.
- Doing `LoadLibrary("a.exe")` from _within_ the running a.exe, will share memory space.
  Changing a variable `shared` from the DLL function is observable from the exe.
  Notably `DllMain()` is definitely not called in this situation.

## License

[Unlicense](./LICENSE)
