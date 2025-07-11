#pragma once

//�̱��� ������ �������� �������� ��� ����

template <typename T> //������ Ÿ������ ������ �� �ֵ��� ������
class Singleton
{
protected:
	Singleton() = default; 
	//�����Ϸ��� �ڵ����� �����ϴ� �⺻������ ���
	virtual ~Singleton() = default;

	//�̱���: �� Ŭ������ ��ü�� �� �Ѱ���
	//ex Ű���� ���� inputmgr, �������� �ʿ䰡 ����
	//���������, ������Կ����� ����
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:
	//���������� �ؼ� ���� ���ϰ� �׳� �� ��ü ��ü�� ������
	//�׷��� ��� ������ �� ��ü�� ����Ű�� ��
	static T& Instance()
	{
		static T instance;
		return instance;
	}
};
//��, �̱��� ���ø��� ����Ͽ� Ŭ������ �����ϹǷν�
//�ش� Ŭ������ ��ü�� 1���� ��