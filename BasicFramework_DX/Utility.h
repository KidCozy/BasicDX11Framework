#pragma once
#include"GraphicHeader.h"
#include<iostream>
#include<string>
#include<DbgHelp.h>

#pragma comment(lib, "dbghelp.lib")

#define MAX_STACKDEPTH 16 
#define SUCCESS(Result) if(Result != S_OK) {DISPLAY_STACKONPOINT(); return false;}

class CallStack
{
private:
	void* Address[MAX_STACKDEPTH];
	ULONG Hash;
	size_t Count;
public:
	explicit CallStack()
	{
		Count = CaptureStackBackTrace(0, MAX_STACKDEPTH, Address, &Hash);
	}

	void* operator[] (const size_t index) const { return Address[index]; }

	ULONG GetHash() const { return Hash; }
	size_t GetCount() const { return Count; }

};

struct SymbolBuffer : public SYMBOL_INFO
{
	static const size_t BufferSize = 256;
	char Buffer[BufferSize];

	SymbolBuffer()
	{
		MaxNameLen = static_cast<ULONG>(BufferSize);
		SizeOfStruct = sizeof(SYMBOL_INFO);
	}
};

class SymbolLookup
{
private:
	const static size_t StrBufferSize = 1024;
	HANDLE Handle;
public:
	SymbolLookup() : Handle(GetCurrentProcess())
	{
		SymInitialize(Handle, nullptr, TRUE);
		SymSetOptions(SYMOPT_LOAD_LINES);
	}

	std::string GetSymbolString(void* Address) const;
};

void DISPLAY_STACKTRACE();
void DISPLAY_STACKONPOINT();

