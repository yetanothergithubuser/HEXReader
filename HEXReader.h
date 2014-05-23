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
		//HEXREADER_API	operator+(size_t )
		//HEXREADER_API	std::ostream& operator<<(std::ostream& lhs);
		/*std::ostream& X::outputToStream(std::ostream&) const;
		std::ostream& operator<<(std::ostream& lhs, X const& rhs)
		{
		return rhs.outputToStream(lhs);
		}*/



	public:
		HEXREADER_API	bool			Open(std::wstring strFileName);
		HEXREADER_API	bool			IsValid(void);
		HEXREADER_API	std::streampos	GetFileSize(void);

	public:
		HEXREADER_API	void			Goto(const std::streamoff offset, bool bRelativeToCurrentPos = true);

	public:
		template <typename Type>
						Type			Read(size_t size = 1, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		template <>
						std::string		Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);
		template <>
						std::wstring	Read(size_t size, const std::streamoff offset, bool bRelativeToCurrentPos);

		/*template <typename Type>
						Type			ReadString(size_t size = 32, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);*/
		//template <typename Type>
		//				//Type			
		//				Type ReadString(size_t size = 32, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		//template <>
		//std::string		ReadString(size_t size /* = 32 */, const std::streamoff offset /* = 0x0 */, bool bRelativeToCurrentPos /* = true */);

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

		//HEXREADER_API	std::string		ReadString(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		//HEXREADER_API	std::string		ReadString(size_t size, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		//HEXREADER_API	std::wstring	ReadWString(const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);
		//HEXREADER_API	std::wstring	ReadWString(size_t size, const std::streamoff offset = 0x0, bool bRelativeToCurrentPos = true);

	private:
		std::ifstream	m_File;
	};

	//template <typename Type>
	//	Type HEX::HEXReader::Read(size_t size /*= 32*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
	//{
	//		//if (typeid(Type) == typeid(bool))
	//		//	return (Type)ReadBool(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(uint8_t))
	//		//	return ReadU8(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(uint16_t))
	//		//	return (Type)ReadU16(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(uint32_t))
	//		//	return ReadU32(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(uint64_t))
	//		//	return (Type)ReadU64(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(int8_t))
	//		//	return ReadI8(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(int16_t))
	//		//	return (Type)ReadI16(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(int32_t))
	//		//	return ReadI32(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(int64_t))
	//		//	return (Type)ReadI64(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(float32_t))
	//		//	return (Type)ReadFloat(offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(double64_t))
	//		//	return (Type)ReadDouble(offset, bRelativeToCurrentPos);
	//		///*else if (typeid(Type) == typeid(std::string))
	//		//	return (Type)ReadString(size, offset, bRelativeToCurrentPos);
	//		//else if (typeid(Type) == typeid(std::wstring))
	//		//	return (Type)ReadWString(size, offset, bRelativeToCurrentPos);*/

	//		//return (Type)ReadByteArray(size, offset, bRelativeToCurrentPos);

	//		char* buffer = NULL;

	//		if (typeid(Type) == typeid(std::string))
	//		{
	//			buffer = new char[size];
	//		}
	//		else
	//		{
	//			buffer = new char[sizeof(Type) * size];
	//		}
	//		
	//		std::streampos current;

	//		if (bRelativeToCurrentPos)
	//		{
	//			m_File.seekg(offset, std::ios::cur);	// sets filepointer position +/- offset from current position. moves not if 0. in either case filepointer size will be moved by size. look below
	//		}
	//		else	// equals relative to beginning of file
	//		{
	//			m_File.seekg(offset, std::ios::beg);
	//		}

	//		if (typeid(Type) == typeid(std::string))
	//		{
	//			m_File.read(buffer, size);
	//		}
	//		else
	//		{
	//			m_File.read(buffer, sizeof(Type) * size);	// reads size amount at current filepointer position and also moves filepointer size amount forward.
	//		}

	//		Type ret;

	//		if (typeid(Type) == typeid(std::string))
	//		{
	//			ret = reinterpret_cast<Type>(buffer);
	//		}
	//		else
	//		{
	//			//return reinterpret_cast<void *>(buffer);
	//			ret = *reinterpret_cast<Type*>(buffer);
	//		}

	//		

	//		delete[] buffer;

	//		return ret;
	//}


	//template <typename Type>
	//Type * HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
	//{
	//	/*Type ret = 0;
	//	if (typeid(Type) == typeid(uint8_t))
	//	{
	//		printf("uint8_t\n");
	//		return ret;
	//	}
	//	else if (typeid(Type) == typeid(int64_t))
	//	{
	//		printf("int64_t\n");
	//		return ret;
	//	}
	//	else
	//	{
	//		printf("lolk unknown\n");
	//	}

	//	return ret;*/

	//	void* buffer = NULL;

	//	if (typeid(Type) == typeid(std::string))
	//	{
	//		buffer = ReadByteArray(sizeof(char) * 8, offset, bRelativeToCurrentPos);
	//	}
	//	else
	//	{
	//		buffer = ReadByteArray(sizeof(Type) * size, offset, bRelativeToCurrentPos);
	//	}
	//	/*if (buffer == NULL)
	//	{
	//		delete[] buffer;

	//		assert(buffer != NULL);
	//	}*/
	//	assert(buffer != NULL);

	//	Type ret;
	//	//auto ret = NULL;
	//	std::string ret2 = NULL;

	//	if (typeid(Type) == typeid(std::string))
	//	{
	//		ret2 = reinterpret_cast<char*>(buffer);
	//		//ret = ret2;
	//		//ret = reinterpret_cast<char*>(buffer);
	//	}
	//	else
	//	{
	//		ret = *reinterpret_cast<Type*>(buffer);
	//	}
	//	


	//	delete[] buffer;

	//	if (typeid(Type) == typeid(std::string))
	//	{
	//		return reinterpret_cast<Type*>(ret2);
	//	}
	//	else
	//	{
	//		return ret;
	//	}
	//}

	template <typename Type>
	Type HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
	{	
		void* buffer = NULL;
		
		buffer = ReadByteArray(sizeof(Type) * size, offset, bRelativeToCurrentPos);
		
		assert(buffer != NULL);
	
		Type ret = *reinterpret_cast<Type*>(buffer);
			
		delete[] buffer;
		buffer = NULL;
	
		return ret;
	}

	template <>
	std::string HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
	{
		void* buffer = NULL;

		buffer = ReadByteArray(sizeof(char) * size, offset, bRelativeToCurrentPos);

		assert(buffer != NULL);

		std::string ret(reinterpret_cast<char*>(buffer), size);

		delete[] buffer;
		buffer = NULL;

		return ret;
	}

	template <>
	std::wstring HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
	{
		void* buffer = NULL;

		buffer = ReadByteArray(sizeof(wchar_t) * size, offset, bRelativeToCurrentPos);

		assert(buffer != NULL);

		std::wstring ret(reinterpret_cast<wchar_t*>(buffer), size);

		delete[] buffer;
		buffer = NULL;

		return ret;
	}
}

#endif // HEXReader_H__