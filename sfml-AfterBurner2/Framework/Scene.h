#pragma once
class Scene
{
protected:
	std::list<GameObject*> gameObjects;
	std::list<GameObject*> objectsToAdd;
	std::list<GameObject*> objectsToRemove;
	//게임 루프 중 오브젝트를 바로 삭제하지 않고, remove 리스트에 넣어두고 프레임 끝에서 한번에 처리

	std::vector<std::string> texIds;
	std::vector<std::string> fontIds;
	std::vector<std::string> soundIds;

	sf::View worldView;
	sf::View uiView;

	void ApplyPendingChanges(); //CRUD 일괄적용

public:
	//씬아이디, 씬아이디를 이용한 생성자
	const SceneIds Id;
	Scene(SceneIds id);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	//포인터는 null 가능성을 허용한다.
	//참조형은 무조건 유효한 객체를 가치켜야 한다.
	//객체의 생명주기와 소유권이 명확해야 하기 때문에
	//포인터를 이용하여 해제 시점도 직접 컨트롤한다.

	GameObject* AddGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go);

	GameObject* FindGameObject(const std::string& name);
	std::vector<GameObject*> FindGameObjects(const std::string& name);
	void FindGameObjects(const std::string& name, std::vector<GameObject*>& results);

	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos); //스크린좌표계를 월드좌표계로
	sf::Vector2i WorldToScreen(sf::Vector2f worldPos); //월드좌표계를 스크린좌표계로
	sf::Vector2f ScreenToUi(sf::Vector2i screenPos); //스크린좌표계를 UI좌표계로
	sf::Vector2i UiToScreen(sf::Vector2f worldPos); //UI좌표계를 스크린좌표계로 

	//스크린 좌표계 : 실제 화면 상의 위치
	//월드 좌표계 : 카메라가 이동할 수 있는 자유로운 좌표계, 게임 월드 내의 가상 좌표
	//UI 좌표계 : 점수, 체력 등 화면에 고정된 요소 위치
};

struct DrawOrderComparer
{
	bool operator()(const GameObject* a, const GameObject* b)
	{
		if (a->sortingLayer != b->sortingLayer)
		{
			return a->sortingLayer < b->sortingLayer;
		}
		return a->sortingOrder < b->sortingOrder;
	}
};