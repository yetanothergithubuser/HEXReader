#ifndef HEXReader_H__
#define HEXReader_H__

#ifdef HEXSTATICLIB
	#define HEXDLLEXPORT
#else
	#ifdef HEXREADER_EXPORTS
		#define HEXDLLEXPORT __declspec(dllexport)
	#else
		#define HEXDLLEXPORT __declspec(dllimport)
	#endif
#endif


#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <assert.h>

typedef float float32_t;
typedef double double64_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace HEX
///
/// @brief Contains routines to mimic hex-editor functionality.
/// @todo add class with write and file-resize support
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace HEX
{
	enum DATATYPES
	{
		BYTE = 1,
		WORD = 2,
		DWORD = 4,
		QWORD = 8,
		FLOAT = 4,
		DOUBLE = 8
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class HEXReader
	///
	/// @brief Open and read a file byte-wise. mimic hex-editor functionality.
	/// @todo support for endianess
	/// @todo add bounding-check (offset/reads are not outside file-size)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class HEXReader
	{
	public:
		HEXDLLEXPORT	HEXReader();
		HEXDLLEXPORT	~HEXReader();

	public:
		HEXDLLEXPORT	bool			Open(std::wstring strFileName);
		HEXDLLEXPORT	bool			IsValid(void);
		HEXDLLEXPORT	std::streampos	GetFileSize(void);
		HEXDLLEXPORT	void			Goto(const std::streamoff offset, bool bRelativeToCurrentPos = true);

	public:
		template <typename Type>
		HEXDLLEXPORT	Type			Read(size_t size = 1, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

		template <>
		HEXDLLEXPORT	bool			Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);

		template <>
		HEXDLLEXPORT	std::string		Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);

		template <>
		HEXDLLEXPORT	std::wstring	Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);

		HEXDLLEXPORT	void*			ReadByteArray(size_t size, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

	private:
		std::ifstream	m_File;
	};
}

#endif // HEXReader_H__