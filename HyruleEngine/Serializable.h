#pragma once

/// <summary>
///	FlatBuffer ���̺귯���� ����ؼ� ������.
/// </summary>

namespace hyrule
{
	class Serializable
	{
	public:
		Serializable() = default;
		~Serializable() = default;

		/// <summary>
		/// ������ �о����� ���⸦ ���� �ϱ� ���ؼ� ������ �����ε��� �غ���
		/// </summary>
		virtual void operator<<(Serializable*);
		virtual void operator>>(Serializable*);
	};
}


/*
�ʹ� ����߽����� �̰����� �ǵ�� �ִ°� ���Ƽ�
�ִ��� �����ؼ� �ϳ��� �ذ��غ����� ����.....
4���͵��� �������ص� �ð� �����Ұ� ������.
*/