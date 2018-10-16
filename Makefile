a.exe: test.c
	i686-w64-mingw32-gcc -g test.c -o a.exe
b.exe: test2.c
	i686-w64-mingw32-gcc -g test2.c -o b.exe

run: a.exe b.exe
	wine a.exe
