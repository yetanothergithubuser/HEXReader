#include "HEXReader.h"


HEXREADER_API HEX::HEXReader::HEXReader()
{
}


HEXREADER_API HEX::HEXReader::~HEXReader()
{
	if (m_File.is_open())
		m_File.close();
}

//HEXREADER_API std::ostream& HEX::HEXReader::operator<<(std::ostream& lhs)
//{
//
//}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens File with specified Filename/-path
///
/// 
///
/// @param strFileName Path-/Filename
/// @return A bool value showing successful opening of the File
/// @sa IsValid()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API bool HEX::HEXReader::Open(std::wstring strFileName)
{
	m_File.open(strFileName, std::ios::in | std::ios::binary);

	return IsValid();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Checks if file is opened successfully
///
///
///
/// @return A bool value representing the validity of the opened file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API bool HEX::HEXReader::IsValid(void)
{
	return m_File.is_open();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets the size of the opened file
///
///
///
/// @return A std::streampos value containing the file size
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API std::streampos HEX::HEXReader::GetFileSize(void)
{
	std::streampos begin = 0, end = 0, current = 0;

	current = m_File.tellg();

	m_File.seekg(0, std::ios::beg);
	begin = m_File.tellg();

	m_File.seekg(0, std::ios::end);
	end = m_File.tellg();

	m_File.seekg(current);

	return (end - begin);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the internal file pointer to the specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API void HEX::HEXReader::Goto(const std::streamoff offset, bool bRelativeToCurrentPos /*= true*/)
{
	if (bRelativeToCurrentPos)
		m_File.seekg(offset, std::ios::cur);
	else
		m_File.seekg(offset, std::ios::beg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads specified amount of bytes at specified position
///
///
///
/// @param size Amount of bytes to be read
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A void pointer to the allocated byte array
/// @warning this allocation needs to be freed after use!
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API void* HEX::HEXReader::ReadByteArray(size_t size, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	char* buffer = NULL;
	buffer = new char[size]();
	std::streampos current;

	if (bRelativeToCurrentPos)
	{
		m_File.seekg(offset, std::ios::cur);	// sets filepointer position +/- offset from current position. moves not if 0. in either case filepointer size will be moved by size. look below
	}
	else	// equals relative to beginning of file
	{		
		m_File.seekg(offset, std::ios::beg);
	}

	m_File.read(buffer, size);	// reads size amount at current filepointer position and also moves filepointer size amount forward.
	
	return reinterpret_cast<void *>(buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads integer from specified position and interprets it as boolean
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A bool value interpreted at the specified position
/// @sa ReadI8()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API bool HEX::HEXReader::ReadBool(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	return (ReadI8(offset, bRelativeToCurrentPos) != 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads unsigned 1-byte value at specified position
///
/// 
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint8_t value at the specified position or _UI8_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API uint8_t HEX::HEXReader::ReadU8(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(uint8_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _UI8_MAX;
	}
	uint8_t ret = *reinterpret_cast<uint8_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads unsigned 2-byte value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint16_t value at the specified position or _UI16_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API uint16_t HEX::HEXReader::ReadU16(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(uint16_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _UI16_MAX;
	}
	uint16_t ret = *reinterpret_cast<uint16_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads unsigned 4-byte value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint32_t value at the specified position or _UI32_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API uint32_t HEX::HEXReader::ReadU32(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(uint32_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _UI32_MAX;
	}
	uint32_t ret = *reinterpret_cast<uint32_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads unsigned 8-byte value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint64_t value at the specified position or _UI64_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API uint64_t HEX::HEXReader::ReadU64(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(uint64_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _UI64_MAX;
	}
	uint64_t ret = *reinterpret_cast<uint64_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads signed 1-byte value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int8_t value at the specified position or _I8_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API int8_t HEX::HEXReader::ReadI8(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(int8_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _I8_MAX;
	}
	int8_t ret = *reinterpret_cast<int8_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads signed 2-byte value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int16_t value at the specified position or _I16_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API int16_t HEX::HEXReader::ReadI16(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(int16_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _I16_MAX;
	}
	int16_t ret = *reinterpret_cast<int16_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads signed 4-byte value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int32_t value at the specified position or _I32_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API int32_t HEX::HEXReader::ReadI32(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(int32_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _I32_MAX;
	}
	int32_t ret = *reinterpret_cast<int32_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads signed 8-byte value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int64_t value at the specified position or _I64_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API int64_t HEX::HEXReader::ReadI64(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(int64_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		return _I64_MAX;
	}
	int64_t ret = *reinterpret_cast<int64_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads float value at specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A float value at the specified position or FLT_MAX if something went wrong
/// @sa ReadByteArray()
/// @attention Allocated buffer gets also freed here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXREADER_API float32_t HEX::HEXReader::ReadFloat(const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;
	buffer = ReadByteArray(sizeof(float32_t), offset, bRelativeToCurrentPos);
	if (buffer == NULL)
	{
		delete[] buffer;
		//return 2323.2323f;
		return FLT_MAX;
	}

	float32_t ret = *static_cast<float32_t*>(buffer);
	delete[] buffer;	// memory allocated inside ReadByteArray

	return ret;
}



template <typename Type>
HEXREADER_API Type HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;

	buffer = ReadByteArray(sizeof(Type) * size, offset, bRelativeToCurrentPos);

	assert(buffer != NULL);

	Type ret = *reinterpret_cast<Type*>(buffer);

	delete[] buffer;
	buffer = NULL;

	return ret;
}
template HEXREADER_API uint8_t		HEX::HEXReader::Read<uint8_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API uint16_t		HEX::HEXReader::Read<uint16_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API uint32_t		HEX::HEXReader::Read<uint32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API uint64_t		HEX::HEXReader::Read<uint64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API int8_t		HEX::HEXReader::Read<int8_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API int16_t		HEX::HEXReader::Read<int16_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API int32_t		HEX::HEXReader::Read<int32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API int64_t		HEX::HEXReader::Read<int64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API float32_t	HEX::HEXReader::Read<float32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXREADER_API double64_t	HEX::HEXReader::Read<double64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);


template <>
HEXREADER_API bool HEX::HEXReader::Read(size_t size /* = 1 */, const std::streamoff offset /* = 0x0 */, bool bRelativeToCurrentPos /* = true */)
{
	void* buffer = NULL;

	buffer = ReadByteArray(sizeof(uint8_t) * size, offset, bRelativeToCurrentPos);

	assert(buffer != NULL);

	uint8_t ret = *reinterpret_cast<uint8_t*>(buffer);

	delete[] buffer;
	buffer = NULL;

	return (ret != 0);
}

template <>
HEXREADER_API std::string HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
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
HEXREADER_API std::wstring HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;

	buffer = ReadByteArray(sizeof(wchar_t) * size, offset, bRelativeToCurrentPos);

	assert(buffer != NULL);

	std::wstring ret(reinterpret_cast<wchar_t*>(buffer), size);

	delete[] buffer;
	buffer = NULL;

	return ret;
}