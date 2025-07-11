#pragma once

//싱글톤 디자인 패턴으로 전역에서 사용 예정

template <typename T> //임의의 타입으로 생성할 수 있도록 도와줌
class Singleton
{
protected:
	Singleton() = default; 
	//컴파일러가 자동으로 생성하는 기본생성자 사용
	virtual ~Singleton() = default;

	//싱글톤: 이 클래스의 객체는 딱 한개임
	//ex 키보드 같은 inputmgr, 여러개일 필요가 없음
	//복사생성자, 복사대입연산자 삭제
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:
	//참조형으로 해서 복사 안하고 그냥 그 객체 자체를 가져옴
	//그래서 모든 참조가 그 객체를 가리키게 됨
	static T& Instance()
	{
		static T instance;
		return instance;
	}
};
//즉, 싱글톤 템플릿을 사용하여 클래스를 선언하므로써
//해당 클래스의 객체는 1개가 됨