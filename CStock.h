#pragma once

#define MAX_DATA (250)
#define MAX_COMPANY (2500)

struct Data {
	long date; // ��¥
	long startVal;
	long highVal;
	long lowVal;
	long lastVal;
	long vol;// �ŷ���
};

struct MovementAverage {
	long avg5;
	long avg20;
	long avg60;
	long avg120;
};

// Ư�� ����. ������ ��¥�� �����͸� ����.
struct Company {
	CString strJongMok, strName;
	int quantity;
	Data data[MAX_DATA];
	MovementAverage moveAverage[MAX_DATA];
};

struct AllCompany {
	int quantity;
	Company companies[MAX_COMPANY];
};

// Ư�� ���ǿ� ���� �ɷ��� �����
struct SelectedCompany {
	int quantity;
	Company* companies[MAX_COMPANY];
};




class CStock
{
// �����ڿ� �Ҹ���
public:
	CStock();
	virtual ~CStock();

public:
	void Run();
	void ReadDataFromFile();
	void WriteDataToFile();
	void makeSelectedCompanyFromAllCompany();
	void makeMovementAverage();
	
// ��� ����
public:
	AllCompany allCompanies;
	SelectedCompany selectedCompanies;
	Company* ptrCompany;
};

