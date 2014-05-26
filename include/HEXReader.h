#ifndef HEXReader_H__
#define HEXReader_H__


#pragma once

#ifdef HEXSTATICLIB
	#define HEXDLLEXPORT
#else
	#ifdef HEXREADER_EXPORTS
		#define HEXDLLEXPORT __declspec(dllexport)
	#else
		#define HEXDLLEXPORT __declspec(dllimport)
	#endif
#endif


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

		HEXDLLEXPORT	bool			Open(std::wstring strFileName);
		HEXDLLEXPORT	bool			IsValid(void);
		HEXDLLEXPORT	std::streampos	GetFileSize(void);
		HEXDLLEXPORT	void			Goto(const std::streamoff offset, bool bRelativeToCurrentPos = true);

		template <typename T>
		HEXDLLEXPORT	T				Read(size_t size = 1, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

		HEXDLLEXPORT	void*			ReadByteArray(size_t size, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

	private:
		std::ifstream	m_File;
	};
}

#endif // HEXReader_H__