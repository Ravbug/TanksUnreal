#include "TanksUnreal_v2.h" //add your project name
#include "PlatformFunctions.h"


FString UPlatformFunctions::GetCPUBrandName()
{
	return FPlatformMisc::GetCPUBrand();
}

FString UPlatformFunctions::GetCPUVendorName()
{
	return FPlatformMisc::GetCPUVendor();
}

FString UPlatformFunctions::GetGPUBrandName()
{
	return FPlatformMisc::GetPrimaryGPUBrand();
}

int32 UPlatformFunctions::GetCPUCores()
{
	return FPlatformMisc::NumberOfCoresIncludingHyperthreads();
}

FString UPlatformFunctions::GetOSVersion()
{
	return FPlatformMisc::GetOSVersion();
}
