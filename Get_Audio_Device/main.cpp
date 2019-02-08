#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>

#include <iostream>
#include <string>

using namespace std;

wstring getActiveAudioDeviceName(ERole role)
{
	IMMDeviceEnumerator* enumerator;
	CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,
		CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
		(void**)&enumerator);

	IMMDevice* device;
	enumerator->GetDefaultAudioEndpoint(eRender, role, &device);

	IPropertyStore* props;
	device->OpenPropertyStore(STGM_READ, &props);

	PROPVARIANT nameProp;
	PropVariantInit(&nameProp);
	props->GetValue(PKEY_Device_FriendlyName, &nameProp);
	wstring name = wstring(nameProp.pwszVal);

	props->Release();
	device->Release();
	enumerator->Release();
	PropVariantClear(&nameProp);

	return name;
}

int main(int argc, char** argv)
{
	ERole role = eMultimedia;
	if (argc > 1)
	{
		int value = atoi(argv[1]);
		if (value == 2)
		{
			role = eCommunications;
		}
	}

	CoInitialize(NULL);
	wcout << getActiveAudioDeviceName(role) << endl;
}