// IsoMounter: Mount an ISO file as a new drive (Windows PE)

#define INITGUID
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <virtdisk.h>

int _tmain(int argc, _TCHAR *argv[])
{
	VIRTUAL_STORAGE_TYPE vst;
	HANDLE h;
	vst.DeviceId = 1;
	vst.VendorId = VIRTUAL_STORAGE_TYPE_VENDOR_MICROSOFT;
	if (argc < 2) {
		printf("Not enough arguments!\n");
		return 0;
	}
	if (OpenVirtualDisk(&vst, argv[1], VIRTUAL_DISK_ACCESS_ATTACH_RO | VIRTUAL_DISK_ACCESS_DETACH, OPEN_VIRTUAL_DISK_FLAG_NONE, NULL, &h) == ERROR_SUCCESS) {
		if (AttachVirtualDisk(h, NULL, ATTACH_VIRTUAL_DISK_FLAG_READ_ONLY, 0, NULL, NULL) == ERROR_SUCCESS) {
			printf("Done! Keep this cmd window open!\n");
			system("cmd");
		}
		else {
			printf("AttachVirtualDisk failed!\n");
		}
	}
	else {
		printf("OpenVirtualDisk failed: *%ls*\n", argv[1]);
	}
	return 0;
}

