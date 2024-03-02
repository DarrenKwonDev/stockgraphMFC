#pragma once

#define MAX_DATA (250)
#define MAX_COMPANY (2500)

struct Data {
	long date; // 날짜
	long startVal;
	long highVal;
	long lowVal;
	long lastVal;
	long vol;// 거래량
};

// 특정 종목. 수량과 날짜별 데이터를 소유.
struct Company {
	CString strJongMok, strName;
	int quantity;
	Data data[MAX_DATA];
};

struct AllCompany {
	int quantity;
	Company companies[MAX_COMPANY];
};

struct SelectedCompany {
	int quantity;
	Company* companies[MAX_COMPANY];
};

class CStock
{
// 생성자와 소멸자
public:
	CStock();
	virtual ~CStock();

public:
	void Run();
	void ReadDataFromFile();
	void WriteDataToFile();
	void makeSelectedCompanyFromAllCompany();
	
// 멤버 변수
public:
	AllCompany allCompanies;
	SelectedCompany selectedCompanies;
};

