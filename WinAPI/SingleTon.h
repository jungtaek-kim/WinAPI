#pragma once

//========================================
//##		디자인 패턴 SingleTon		##
//========================================
/*
	싱글톤 패턴 :
	오직 한 개의 클래스 인스턴스만을 갖도록 보장
	이에 대한 전역적인 접근점을 제공

	구현 :
	1. 전역에서 접근 가능한 인스턴스의 주소를 갖기 위해
	데이터 영역 메모리 공간을 활용 (전역변수, 정적변수)
	2. 정적 변수를 활용하여 캡슐화를 진행
	3. 생성자의 접근권한을 외부에서 생성할 수 없도록 제한
	3. GetInstance 함수를 통해 인스턴스에 접근할 수 있도록 함
	4. instance 변수는 단 하나만 있도록 유지

	장점 :
	1. 전역에서 접근가능한 하나뿐인 존재로 주요 클래스, 관리자의 역할을 함
	2. 다른 클래스의 인스턴스들이 데이터를 공유하기 쉬워짐
	
	단점 : 
	1. 싱글톤 인스턴스가 너무 많은 책임을 짊어지는 경우를 방지해야함
		-> 단일 책임의 원칙 위배
	2. 싱글톤의 남발은 코드 결합도가 높아짐
		-> 개방-폐쇄 원칙 위배

*/

// 싱글톤 클래스 정의
template <typename T>
class SingleTon
{
protected:
	static T* instance;

	SingleTon() {};
	virtual ~SingleTon() { ReleaseInstance(); };

public:
	static T* GetInstance()
	{
		// 싱글톤 인스턴스가 없으면 새로 만들어 전달.
		if (nullptr == instance)
			instance = new T;

		return instance;
	}

	void ReleaseInstance()
	{
		// 싱글톤 인스턴스가 있으면 해제
		if (nullptr != instance)
			delete instance;

		instance = nullptr;
	}
};

// 싱글톤 인스턴스 선언
template <typename T>
T* SingleTon<T>::instance = nullptr;