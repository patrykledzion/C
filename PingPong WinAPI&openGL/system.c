#include "system.h"

int64_t readFile(file f, void* out, uint64_t size)
{
	DWORD os;
	if (ReadFile((HANDLE)f, out, (DWORD)size, &os, NULL) == TRUE)
	{
		return (int64_t)os;
	}
	return -1;
}

file openFile(const char* path)
{
	HANDLE h = (file)CreateFileA(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return h == INVALID_HANDLE_VALUE ? NULL : h;
}

void closeFile(file f)
{
	CloseHandle((HANDLE)f);
}

void seekFile(file f, uint64_t offset)
{
	LARGE_INTEGER li;
	LARGE_INTEGER out;
	li.QuadPart = offset;
	SetFilePointerEx((HANDLE)f, li, &out, FILE_BEGIN);
}