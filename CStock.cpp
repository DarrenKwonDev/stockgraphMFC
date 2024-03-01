#include "pch.h"
#include "CStock.h"

CStock::CStock()
{
}

CStock::~CStock()
{
}

void CStock::Run()
{
	ReadDataFromFile();
	WriteDataToFile();
	AfxMessageBox(_T("success!"));
}

void CStock::ReadDataFromFile()
{
	int cn;
	FILE* fp;

	fp = fopen("../data.txt", "rt");
	if (fp == NULL)
	{
		AfxMessageBox(_T("data.txt file is not opened"));
		exit(1);
	}

	// fscanf 는 읽어들인 데이터의 수를 리턴한다 
	cn = fscanf(fp, "%d \n", &allCompanies.quantity);
	if (cn == 0)
	{
		AfxMessageBox(_T("Error: can't get allCompanies.quantity"));
		exit(1);
	}

	char jongmok[20];
	char name[50];

	for (int i = 0; i < allCompanies.quantity; i++)
	{
		// ex A000020 동화약품 250 
		cn = fscanf(fp, "%s %s %d \n", jongmok, name, &allCompanies.companies[i].quantity);
		if (cn == 0)
		{
			AfxMessageBox(_T("Error: fscanf error inside the first for loop"));
			exit(1);
		}

		// ensure null terminated
		jongmok[sizeof(jongmok) - 1] = '\0';
		name[sizeof(name) - 1] = '\0';

		allCompanies.companies[i].strJongMok = jongmok;
		allCompanies.companies[i].strName = name;

		// ex - 250
		for (int j = 0; j < allCompanies.companies[i].quantity; j++)
		{
			cn = fscanf(fp, "%ld %ld %ld %ld %ld %ld \n",
				&allCompanies.companies[i].data[j].date,
				&allCompanies.companies[i].data[j].startVal,
				&allCompanies.companies[i].data[j].highVal,
				&allCompanies.companies[i].data[j].lowVal,
				&allCompanies.companies[i].data[j].lastVal,
				&allCompanies.companies[i].data[j].vol);

			if (cn == 0)
			{
				AfxMessageBox(_T("Error: fscanf error inside the second for loop"));
				exit(1);
			}
		}
	}

	fclose(fp);
}

void CStock::WriteDataToFile()
{
	FILE* fp;
	fp = fopen("data2.txt", "wt");
	if (fp == NULL)
	{
		AfxMessageBox(_T("data2.txt file is not opened"));
		exit(1);
	}

	fprintf(fp, "%d \n", allCompanies.quantity);
	for (int i = 0; i < allCompanies.quantity; i++)
	{
		// CString -> const TCHAR* -> char*
		fprintf(fp, "%s %s %d \n",
			LPSTR(LPCTSTR(allCompanies.companies[i].strJongMok)), // CString to char*
			LPSTR(LPCTSTR(allCompanies.companies[i].strName)),
			allCompanies.companies[i].quantity
		);

		for (int j = 0; j < allCompanies.companies[i].quantity; j++)
		{
		
			fprintf(fp, "%ld %ld %ld %ld %ld %ld \n",
				allCompanies.companies[i].data[j].date,
				allCompanies.companies[i].data[j].startVal,
				allCompanies.companies[i].data[j].highVal,
				allCompanies.companies[i].data[j].lowVal,
				allCompanies.companies[i].data[j].lastVal,
				allCompanies.companies[i].data[j].vol
				);
		}
	}
	fclose(fp);
}
