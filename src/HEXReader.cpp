#include "HEXReader.h"


HEXDLLEXPORT HEX::HEXReader::HEXReader()
{
}


HEXDLLEXPORT HEX::HEXReader::~HEXReader()
{
	if (m_File.is_open())
		m_File.close();
}

//HEXDLLEXPORT std::ostream& HEX::HEXReader::operator<<(std::ostream& lhs)
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
HEXDLLEXPORT bool HEX::HEXReader::Open(std::wstring strFileName)
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
HEXDLLEXPORT bool HEX::HEXReader::IsValid(void)
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
HEXDLLEXPORT std::streampos HEX::HEXReader::GetFileSize(void)
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
HEXDLLEXPORT void HEX::HEXReader::Goto(const std::streamoff offset, bool bRelativeToCurrentPos /*= true*/)
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
HEXDLLEXPORT void* HEX::HEXReader::ReadByteArray(size_t size, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
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

template <typename Type>
HEXDLLEXPORT Type HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;

	buffer = ReadByteArray(sizeof(Type) * size, offset, bRelativeToCurrentPos);

	assert(buffer != NULL);

	Type ret = *reinterpret_cast<Type*>(buffer);

	delete[] buffer;
	buffer = NULL;

	return ret;
}
template HEXDLLEXPORT uint8_t		HEX::HEXReader::Read<uint8_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT uint16_t		HEX::HEXReader::Read<uint16_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT uint32_t		HEX::HEXReader::Read<uint32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT uint64_t		HEX::HEXReader::Read<uint64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT int8_t		HEX::HEXReader::Read<int8_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT int16_t		HEX::HEXReader::Read<int16_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT int32_t		HEX::HEXReader::Read<int32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT int64_t		HEX::HEXReader::Read<int64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT float32_t	HEX::HEXReader::Read<float32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);
template HEXDLLEXPORT double64_t	HEX::HEXReader::Read<double64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

template <>
HEXDLLEXPORT bool HEX::HEXReader::Read(size_t size /* = 1 */, const std::streamoff offset /* = 0x0 */, bool bRelativeToCurrentPos /* = true */)
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
HEXDLLEXPORT std::string HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
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
HEXDLLEXPORT std::wstring HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;

	buffer = ReadByteArray(sizeof(wchar_t) * size, offset, bRelativeToCurrentPos);

	assert(buffer != NULL);

	std::wstring ret(reinterpret_cast<wchar_t*>(buffer), size);

	delete[] buffer;
	buffer = NULL;

	return ret;
}