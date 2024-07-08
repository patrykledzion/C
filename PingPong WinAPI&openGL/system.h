#pragma once

#include <windows.h>
#include <stdint.h>

typedef void* file;

int64_t readFile(file f, void* out, uint64_t size);
file openFile(const char* path);
void closeFile(file f);

void seekFile(file f, uint64_t offset);