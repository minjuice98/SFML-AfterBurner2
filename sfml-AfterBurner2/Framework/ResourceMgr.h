#pragma once
#include "Singleton.h"

//문자열 ID로 저장 및 재사용 가능하도록 관리
//template <typename T>
//ResourceMgr<sf::Texture>::Instance()
//ResourceMgr<sf::Font>::Instance()
//ResourceMgr<sf::SoundBuffer>::Instance()

//싱글톤 클래스에게 자기 자신을 넘겨줌
//템플릿을 포함하여 어떤 클래스든 자기 자신을 Singleton<T>에 넘기기만 하면
//싱글톤화 가능
template <typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>> //싱글톤화
{
	friend Singleton<ResourceMgr<T>> ; //싱글톤에서 ResourceMgr 접근 허용

protected:
	ResourceMgr() = default;
	virtual ~ResourceMgr() //T*는 힙에 할당된 리소스, 직접 메모리 해제
	{	//unordered_map, std::pair<key,value>를 pair에 복사 해 사용
		for (auto pair : resources)
		{
			delete pair.second;
		}resources.clear(); //resources 맵 구조적 비우기
	}

	//싱글톤 안전장치
	//복사생성자, 대입연산자 삭제
	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr* operator=(const ResourceMgr&) = delete;

	//unordered_map으로 textureId 매핑
	//동적할당으로 동일한 리소스 공유 및 수명 제어
	//참조형은 복사 불가 & 재할당 불가 -> 컨테이너에서 사용 불가(map 저장 불가)
	//id->리소스 포인터(T*), ex) "player.png"->sf::Texture*
	std::unordered_map<std::string, T*> resources;

	static T Empty; //리소스 없는 상황에 대비한 빈 더미 객체

public:
	bool Load(const std::string& id)
	{
		auto it = resources.find(id); //유무 검사, 이터레이터
		if (it != resources.end()) //end()!=일 경우 존재
		{
			return false;
		}

		T* res = new T();  //새 텍스처 객체 동적 생성

		bool success = res->loadFromFile(id); //로드
		if (!success) //로드 실패 시 
		{
			delete res; //메모리 해제
			return false;
		}

		resources.insert({ id,res }); //성공 시 맵 등록
		return true;
	}

	bool Unload(const std::string& id)
	{
		auto it = resources.find(id);
		if (it == resources.end()) //end() 도달 한 경우 존재
		{
			return false;
		}
		delete it->second;
		resources.erase(it);
		return true;
	}
	//여러 개 로드 할 경우 활용
	void Load(const std::vector<std::string>& ids) //문자열로 이루어진 벡터, 원본 참조
	{
		for (auto id : ids)
		{
			Load(id);
		}
	}

	void Unload(const std::vector<std::string>& ids) //문자열로 이루어진 벡터, 원본 참조
	{
		for (auto id : ids)
		{
			Unload(id);
		}
	}

	//리소스 반환 get함수
	T& Get(const std::string& id)
	{
		auto it = resources.find(id);  //resouce key는 id, value는 포인터
		if (it == resources.end())
		{	//디버그 메세지 출력
			std::cerr << "Resource not found: " << id << std::endl;
			return Empty; //비어있는 객체 반환, 리턴 타입 참조
		}
		return *(it->second); // it가 가리키는 (id, 포인터) 쌍에서 포인터 객체를, 역참조 해서 참조 객체 (T&)로 반환!
	}
	//Exist 함수 필요 한 경우 생성
};

// 정적 멤버 변수는 클래스 밖에서 한 번 정의해야 메모리가 할당됨
template<typename T>
T ResourceMgr<T>::Empty;

//매크로
#define TEXTURE_MGR (ResourceMgr<sf::Texture>::Instance())
#define FONT_MGR (ResourceMgr<sf::Font>::Instance())
#define SOUNDBUFFER_MGR (ResourceMgr<sf::SoundBuffer>::Instance())