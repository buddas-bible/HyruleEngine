#pragma once

namespace GRX
{
	template<typename T>
	class IDisposable {
	public:
		virtual void Dispose() = 0;
	};
}