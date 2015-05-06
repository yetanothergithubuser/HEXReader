#include "HEXReader.h"

//#include "vld.h"


HEXDLLEXPORT HEX::HEXReader::HEXReader()
{
	std::streampos begin = 0, end = 0, current = 0;

	m_File.clear();

	current = m_File.tellg();

	m_File.seekg(0, std::ios::beg);
	begin = m_File.tellg();

	m_File.seekg(0, std::ios::end);
	end = m_File.tellg();

	m_File.seekg(current);

	m_File.clear();

	m_fileSize =  (end - begin);
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

HEXDLLEXPORT bool HEX::HEXReader::Open(std::string strFileName)
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
	//std::streampos begin = 0, end = 0, current = 0;

	////m_File.clear();

	//current = m_File.tellg();

	//m_File.seekg(0, std::ios::beg);
	//begin = m_File.tellg();

	//m_File.seekg(0, std::ios::end);
	//end = m_File.tellg();

	//m_File.seekg(current);

	//return (end - begin);

	return m_fileSize;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the internal file pointer to the specified position
///
///
///
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return returns true if no stream error flags are set
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HEXDLLEXPORT bool HEX::HEXReader::Goto(const std::streamoff offset, bool bRelativeToCurrentPos /*= true*/)
{
	m_File.clear();

	if (bRelativeToCurrentPos)
		m_File.seekg(offset, std::ios::cur);
	else
		m_File.seekg(offset, std::ios::beg);

	return m_File.good();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads specified amount of bytes at specified position
///
///
///
/// @param size Amount of bytes to read
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

	m_File.clear();

	if (bRelativeToCurrentPos)
	{
		m_File.seekg(offset, std::ios::cur);	// sets filepointer position +/- offset from current position. moves not if 0. in either case filepointer size will be moved by size. look below
	}
	else	// equals relative to beginning of file
	{
		m_File.seekg(offset, std::ios::beg);
	}

	assert(m_File.good() == true);

	m_File.read(buffer, size);	// reads size amount at current filepointer position and also moves filepointer size amount forward.

	return reinterpret_cast<void *>(buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template function - Reads sizeof(T) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(T)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A value of template type T
/// @sa ReadByteArray()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
HEXDLLEXPORT T HEX::HEXReader::Read(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/)
{
	void* buffer = NULL;

	buffer = ReadByteArray(sizeof(T) * size, offset, bRelativeToCurrentPos);

	assert(buffer != NULL);

	T ret = *reinterpret_cast<T*>(buffer);

	delete[] buffer;
	buffer = NULL;

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(uint8_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(uint8_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint8_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT uint8_t		HEX::HEXReader::Read<uint8_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(uint16_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(uint16_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint16_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT uint16_t		HEX::HEXReader::Read<uint16_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(uint32_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(uint32_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint32_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT uint32_t		HEX::HEXReader::Read<uint32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(uint64_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(uint64_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A uint64_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT uint64_t		HEX::HEXReader::Read<uint64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(int8_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(int8_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int8_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT int8_t		HEX::HEXReader::Read<int8_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(int16_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(int16_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int16_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT int16_t		HEX::HEXReader::Read<int16_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(int32_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(int32_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int32_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT int32_t		HEX::HEXReader::Read<int32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(int64_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(int64_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A int64_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT int64_t		HEX::HEXReader::Read<int64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(float32_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(float32_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A float32_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT float32_t		HEX::HEXReader::Read<float32_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads sizeof(double64_t) amount of bytes at specified position
///
/// 
///
/// @param size Amount of bytes to read. default is 1, which leads to sizeof(double64_t)
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A double64_t value
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template HEXDLLEXPORT double64_t	HEX::HEXReader::Read<double64_t>(size_t size /*= 1*/, const std::streamoff offset /*= 0x0*/, bool bRelativeToCurrentPos /*= true*/);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads a byte at specified position and returns evaluates as bool
///
/// 
///
/// @param size default 1 should used (sizeof(int8_t))
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A bool value (true -> int8_t != 0)
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
HEXDLLEXPORT bool HEX::HEXReader::Read<bool>(size_t size /*= 1*/, const std::streamoff offset /* = 0x0 */, bool bRelativeToCurrentPos /* = true */)
{
	void* buffer = NULL;

	buffer = ReadByteArray(sizeof(int8_t), offset, bRelativeToCurrentPos);

	assert(buffer != NULL);

	int8_t ret = *reinterpret_cast<int8_t*>(buffer);

	delete[] buffer;
	buffer = NULL;

	return (ret != 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads specified amount of bytes at specified position as std::string
///
/// 
///
/// @param size Amount of bytes to read.
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A std::string
/// @wa the returned std::string will only contain useful data if the position points to an actual text.
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief template specialization - Reads specified amount of bytes at specified position as std::wstring
///
/// 
///
/// @param size Amount of bytes to read.
/// @param offset Offset from current Position (depends on bRelativeToCurrentPos)
/// @param bRelativeToCurrentPos Determines how Offset is interpreted (relative from current Position, or absolute from beginning of File)
/// @return A std::wstring
/// @wa the returned std::wstring will only contain useful data if the position points to an actual text.
/// @sa Read()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


template <typename T>
HEXDLLEXPORT	bool HEX::HEXReader::IsInsideBounds(void)
{
	//size_t sizeOfType;
	std::streampos current = 0;


	//problem here with bitstates since i added ifstream::clear() in GetFileSize (and GoTo)
	m_File.clear();

	current = m_File.tellg();

	if ((current + std::streampos(sizeof(T))) > GetFileSize())
	{
		return false;
	}

	return true;
}

template HEXDLLEXPORT	bool HEX::HEXReader::IsInsideBounds<uint32_t>(void);

HEXDLLEXPORT	std::streampos HEX::HEXReader::GetPos(void)
{
	return m_File.tellg();
}

