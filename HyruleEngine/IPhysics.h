#pragma once


namespace Hyrule
{
	class IPhysics
	{
	public:
		IPhysics() = default;
		virtual ~IPhysics() = default;

	private:


	public:
		virtual void Initialize() abstract;
		virtual void Finalize() abstract;
	};
}