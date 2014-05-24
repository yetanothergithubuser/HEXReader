#include <windows.h>

#include <string>

#include "HEXReader.h"

int main(void)
{
	HEX::HEXReader* Testfile = new HEX::HEXReader();

	if (!Testfile->Open(L"HEXReaderx86.dll"))
	{
		fprintf(stderr, "Open failed\n");
		delete Testfile;
		return EXIT_FAILURE;
	}

	for (int i = 1; i <= (Testfile->GetFileSize() / sizeof(uint8_t)); ++i)
	{
		printf("%02X ", Testfile->Read<uint8_t>());

		if ((i * sizeof(uint8_t)) % 16 == 0x0)
			printf("\n");
	}

	delete Testfile;
	return EXIT_SUCCESS;
}