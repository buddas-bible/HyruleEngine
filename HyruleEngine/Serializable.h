#pragma once

/// <summary>
///	FlatBuffer 라이브러리를 사용해서 만들어보자.
/// </summary>

namespace hyrule
{
	class Serializable
	{
	public:
		Serializable() = default;
		~Serializable() = default;

		/// <summary>
		/// 파일을 읽어오기와 쓰기를 쉽게 하기 위해서 연산자 오버로딩을 해보자
		/// </summary>
		virtual void operator<<(Serializable*);
		virtual void operator>>(Serializable*);
	};
}


/*
너무 문어발식으로 이것저것 건들고 있는거 같아서
최대한 집중해서 하나씩 해결해보도록 하자.....
4쿼터동안 물리만해도 시간 부족할거 같으니.
*/