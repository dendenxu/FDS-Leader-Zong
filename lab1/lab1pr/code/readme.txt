For better reading experience, please open the file with a markdown reader.

# How to run
## Compile and run lab1test.c.(make sure the file lab1algoimplementation.c is in your complier's search dir. Or you just put it in the same folder with lab1test.c)
The executable in the folder is complied with clang with args: -Ofast -Wall
Complier output:
```bash
lab1test.c:36:10: warning: 'fopen' is deprecated: This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for
      details. [-Wdeprecated-declarations]
    fp = fopen("testResult.md", "w"); //set the relative path and the file mode in "w" so that the old data can be deleted
         ^
C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h:207:20: note: 'fopen' has been explicitly marked deprecated here
    _Check_return_ _CRT_INSECURE_DEPRECATE(fopen_s)
                   ^
C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.22.27905\include\vcruntime.h:297:55: note: expanded from macro '_CRT_INSECURE_DEPRECATE'
        #define _CRT_INSECURE_DEPRECATE(_Replacement) _CRT_DEPRECATE_TEXT(    \
                                                      ^
C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.22.27905\include\vcruntime.h:287:47: note: expanded from macro '_CRT_DEPRECATE_TEXT'
#define _CRT_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))
                                              ^
1 warning generated.
```
Executable output
```
1.10517
1.64868
2.71815
7.38832
54.5872
403.308
2979.77
22015.5
1.10517
1.64868
2.71815
7.38832
54.5872
403.308
2979.77
22015.5
1.10517
1.64868
2.71815
7.38832
54.5872
403.308
2979.77
22015.5
```