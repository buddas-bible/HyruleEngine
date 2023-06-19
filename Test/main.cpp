#include <iostream>
#include <windows.h>

/// 암시적 링킹
#include "../HyruleMath/HRVector.h"
// #pragma comment(lib, "../x64/Debug/KH_Math.lib")

// using VECTOR_SUM = Hyrule::Vector3D(*)(const Hyrule::Vector3D&);

int main()
{
	// // HMODULE vectorDLL = ::LoadLibraryW(L"..//x64/Debug//HyruleEngine.dll");
	// 
	// Hyrule::Vector3D vec{ 1.f,2.f,3.f };
	// Hyrule::Vector3D vec1{ 1.f,2.f,3.f };
	// Hyrule::Vector3D vec2{ 1.f,2.f,3.f };
	// 
	// int a = 0;
	// while (1)
	// {
	// 	if (a == 0)
	// 	{
	// 		VECTOR_SUM func = (VECTOR_SUM)::GetProcAddress(vectorDLL, "SumVector");
	// 
	// 		if (vectorDLL != NULL)
	// 		{
	// 			vec = SumVector(vec1, vec2);
	// 			std::cout << vec.x << ", "
	// 				<< vec.y << ", "
	// 				<< vec.z << std::endl;
	// 			a = 1;
	// 		}
	// 	}
	// }
	// 
	// FreeLibrary(vectorDLL);
	return 0;
}
