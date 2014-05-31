//#include <windows.h>

//#include <string>

#include "HEXReader.h"

#include "vld.h"

int main(void)
{
	HEX::HEXReader* Testfile = new HEX::HEXReader();

	if (!Testfile->Open(L"TestFile.bin"))
	{
		fprintf(stderr, "Open failed\n");

		delete Testfile;

		return EXIT_FAILURE;
	}
	
	printf("%lu\n", Testfile->Read<uint8_t>(1, 0x0, false));
	printf("%lu\n", Testfile->Read<uint16_t>(1, 0x0, false));
	printf("%lu\n", Testfile->Read<uint32_t>(1, 0x0, false));
	printf("%llu\n", Testfile->Read<uint64_t>(1, 0x0, false));
	printf("%ld\n", Testfile->Read<int8_t>(1, 0x0, false));
	printf("%ld\n", Testfile->Read<int16_t>(1, 0x0, false));
	printf("%ld\n", Testfile->Read<int32_t>(1, 0x0, false));
	printf("%lld\n", Testfile->Read<int64_t>(1, 0x0, false));
	printf("%e\n", Testfile->Read<float32_t>(1, 0x0, false));
	printf("%e\n", Testfile->Read<double64_t>(1, 0x0, false));
	printf("%d\n", Testfile->Read<bool>(1, 0x0, false));
	printf("%s\n", Testfile->Read<std::string>(0x1B, 0x0, false).c_str());
	printf("%ls\n", Testfile->Read<std::wstring>(0x32, 0x1C, false).c_str());
	
	
	delete Testfile;
	
	return EXIT_SUCCESS;
}