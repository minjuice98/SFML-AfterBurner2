#pragma once
class GameObject
{
protected:
	//na
	std::string name;
	bool active = true;
	
	//prso
	//초기화 {}, 인자 전달 ()
	sf::Vector2f position = {0.f,0.f}; //월드좌표(화면 기준)
	//로컬 좌표계(객체 기준)
	float rotation = 0.f;
	sf::Vector2f scale = { 1.f, 1.f }; //원본
	sf::Vector2f origin = {0.f,0.f}; //좌상단

public:
	//레이어,bound 추후 추가

	GameObject(const std::string& name="");
	virtual ~GameObject();

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	const sf::Vector2f GetPosition() const { return position; }
	void SetPosition(const sf::Vector2f pos) { position = pos; }

	const float GetRotation() const { return rotation; }
	void SetRotation(const float r) { rotation = r; }

	const sf::Vector2f GetScale() const { return scale; }
	void SetScale(const sf::Vector2f o) { origin = o; }

	//데이터 관리
	virtual void Init() = 0; 
	virtual void Release() = 0;
	virtual void Reset() = 0;

	//behavior
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

};

