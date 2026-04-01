// Copyright (c) 2018 by HHD Software Ltd.
// This file is part of the HHD Software Device Monitoring Studio
// For usage and distribution policies, consult the license distributed with a product installation program

// Modification options:
// Trial mode: Modified file is loaded, compiled and used on startup
// Lite and Standard Editions: Protocol-related features are not available
// Professional Edition: Pre-configured version is used, changes in this file will be ignored
// Ultimate Edition: Modified file is loaded, compiled and used on startup

// This file contains common declarations used by all protocol definition files

#pragma once

// Constants and macros

// MAX and MIN macros
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

// Common constants TRUE, FALSE and NULL
#define TRUE true
#define FALSE false
#define NULL 0

// Type aliases

// Standard Windows types
typedef char CHAR;
typedef wchar_t WCHAR;
typedef short SHORT;
typedef int INT;
typedef long LONG;
typedef __int64 LONGLONG;

typedef unsigned char BYTE,UCHAR;
typedef unsigned short WORD,USHORT;
typedef unsigned int UINT;
typedef unsigned long DWORD,ULONG;
typedef unsigned __int64 ULONGLONG,FILETIME,QWORD;
typedef unsigned char  BOOLEAN;

// Sized integer types
typedef char int8,__int8;
typedef short int16,__int16;
typedef int int32,__int32;
typedef __int64 int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned __int64 uint64;

// Expression type, as returned by built-in type() function
enum
{
	BooleanType,
	IntegerType,
	FloatingPointType,
	StringType,
	ReferenceType,
	ByteArrayType,
};

typedef DWORD COLORREF;
typedef float	FLOAT;
typedef double	DOUBLE;

[display(format("{{{0b16Xw8arf0}-{1b16Xw4arf0}-{2b16Xw4arf0}-{3b16Xw2arf0}{4b16Xw2arf0}-{5b16Xw2arf0}{6b16Xw2arf0}{7b16Xw2arf0}{8b16Xw2arf0}{9b16Xw2arf0}{10b16Xw2arf0}}",
	Data1,
	Data2,
	Data3,
	Data4[0],
	Data4[1],
	Data4[2],
	Data4[3],
	Data4[4],
	Data4[5],
	Data4[6],
	Data4[7]))]
struct GUID 
{
	unsigned long  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[8];
};

#define LONG_MAX 0xFFFFFFFF

// Pascal string with ASCII chars
struct pstring_a
{
	BYTE nLength;
	char data[nLength];
};

// Pascal string with UNICODE chars
struct pstring_w
{
	WORD nLength;
	wchar_t data[nLength/2];
};
