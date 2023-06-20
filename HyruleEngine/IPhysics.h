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
		virtual int Initialize() abstract;
		virtual void Finalize() abstract;
		virtual void Update() abstract;
	};
}