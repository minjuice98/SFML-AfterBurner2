#pragma once
class GameObject
{
protected:
	//na
	std::string name;
	bool active = true;
	
	//prso
	//�ʱ�ȭ {}, ���� ���� ()
	sf::Vector2f position = {0.f,0.f}; //������ǥ(ȭ�� ����)
	//���� ��ǥ��(��ü ����)
	float rotation = 0.f;
	sf::Vector2f scale = { 1.f, 1.f }; //����
	sf::Vector2f origin = {0.f,0.f}; //�»��

public:
	//���̾�,bound ���� �߰�

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

	//������ ����
	virtual void Init() = 0; 
	virtual void Release() = 0;
	virtual void Reset() = 0;

	//behavior
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

};

