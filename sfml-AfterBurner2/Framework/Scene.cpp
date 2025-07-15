#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id) 
	:Id(id)
{
}

void Scene::Init() //시작, 리소스 초기화
{
	//해당 게임 오브젝트의 Init 함수 호출
	for (auto obj : gameObjects)
	{
		obj->Init();
	}
	for (auto obj : objectsToAdd)
	{
		obj->Init();
	}
}

void Scene::Release() //끝, 리소스 해제 
{
	ApplyPendingChanges();
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter() //씬 입장, 리소스 로딩, 리셋
{
	TEXTURE_MGR.Load(texIds);

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Reset();
	}
}

void Scene::Exit() //씬 퇴장, 리소스 언로드
{
	ApplyPendingChanges();

	TEXTURE_MGR.Unload(texIds);
}

void Scene::Update(float dt) //프레임마다 업데이트 할 내용
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::list<GameObject*> sortedObjects(gameObjects);
	sortedObjects.sort(DrawOrderComparer());

	for (auto obj : sortedObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
	ApplyPendingChanges();
}

GameObject* Scene::AddGameObject(GameObject* go) //추가하기 전 objectsToAdd(임시거처)에 등록하는 함수 
{
	objectsToAdd.push_back(go);
	return go; //to chaning
}

void Scene::RemoveGameObject(GameObject* go) //다음 프레임에 제거될 객체
{
	go->SetActive(false); //active false, removeList로
	objectsToRemove.push_back(go);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

void Scene::ApplyPendingChanges()
{
	for (GameObject* go : objectsToAdd)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go); 
		}
	}
	objectsToAdd.clear(); 

	for (GameObject* go : objectsToRemove)
	{
		gameObjects.remove(go);
		if (go != nullptr) //안전한 동적 할당 해제
		{
			go->Release();
			delete go;
		}
	}
	objectsToRemove.clear();
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}
sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return sf::Vector2f();
}