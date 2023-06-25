#pragma once

/// <summary>
///	FlatBuffer ���̺귯���� ����ؼ� ������.
/// </summary>

namespace Hyrule
{
	class Serialize
	{
	public:
		Serialize() = default;
		~Serialize() = default;

		/// <summary>
		/// ������ �о����� ���⸦ ���� �ϱ� ���ؼ� ������ �����ε��� �غ���
		/// </summary>
		virtual void operator<<(Serialize*);
		virtual void operator>>(Serialize*);
	};
}


/*
�ʹ� ����߽����� �̰����� �ǵ�� �ִ°� ���Ƽ�
�ִ��� �����ؼ� �ϳ��� �ذ��غ����� ����.....
4���͵��� �������ص� �ð� �����Ұ� ������.
*/