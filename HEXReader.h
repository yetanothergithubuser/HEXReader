#ifndef HEXReader_H__
#define HEXReader_H__

#ifdef HEXREADER_EXPORTS
#define HEXREADER_API __declspec(dllexport)
#else
#define HEXREADER_API __declspec(dllimport)
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
		HEXREADER_API	HEXReader();
		HEXREADER_API	~HEXReader();
	
	public:
		HEXREADER_API	bool			Open(std::wstring strFileName);
		HEXREADER_API	bool			IsValid(void);
		HEXREADER_API	std::streampos	GetFileSize(void);

	public:
		HEXREADER_API	void			Goto(const std::streamoff offset, bool bRelativeToCurrentPos = true);

	public:
		template <typename Type>
		HEXREADER_API	Type			Read(size_t size = 1, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		
		template <>
		HEXREADER_API	bool			Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);

		template <>
		HEXREADER_API	std::string		Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);

		template <>
		HEXREADER_API	std::wstring	Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);

		HEXREADER_API	void*			ReadByteArray(size_t size, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

		HEXREADER_API	bool			ReadBool(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

		HEXREADER_API	uint8_t			ReadU8(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	uint16_t		ReadU16(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	uint32_t		ReadU32(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	uint64_t		ReadU64(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	int8_t			ReadI8(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	int16_t			ReadI16(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	int32_t			ReadI32(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	int64_t			ReadI64(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

		HEXREADER_API	float32_t		ReadFloat(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		HEXREADER_API	double64_t		ReadDouble(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

	private:
		std::ifstream	m_File;
	};
}

#endif // HEXReader_H__