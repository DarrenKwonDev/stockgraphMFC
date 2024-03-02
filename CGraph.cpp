#include "pch.h"
#include "CGraph.h"

CGraph::CGraph()
{
}

CGraph::~CGraph()
{
}

PointData* CGraph::GetPointData(Company* company)
{
	// ���� ���� ���� (������ ���� ������ ���ŵ��� ����)
	// �Լ� ȣ�� ���̿����� ���� �����Ǹ�, stack frame�� ����� ���� ������.
	static PointData ptData; 
	GetDataForChart(company, &ptData);
	return &ptData;
}

void CGraph::GetDataForChart(Company* company, PointData* ptData)
{
	int i, maxVal, minVal, maxVol, interval;

	


	// ������ ���� �� �� ���� ���� ���� ã���ϴ�.
	// �ֳ��ϸ� �׷��� �ִ� ���� ������ �ʿ��ϰŵ��.
	maxVal = 0;
	int quantity = company->quantity;
	for ( i = 0; i < quantity; i++)
	{
		if (company->data[i].highVal > maxVal)
		{
			maxVal = company->data[i].highVal;
		}
	}


	// ������ ���� �� �� ���� ���� ���� ã���ϴ�. 
	// �ֳ��ϸ� �׷��� ���ϼ� ������ �ʿ��ϰŵ��.
	minVal = maxVal;
	for (i = 0; i < quantity; i++)
	{
		if (company->data[i].lowVal < minVal)
		{
			minVal = company->data[i].lowVal;
		}
	}

	
	// �ִ� ������ ã���ϴ�.
	// ���� �׷����� ���� ������ �ʿ��ϱ� ������.
	// ����� �ּ� ������ ã�� �ʿ� �����ϴ�. ������ ���� �׷����� �ٴڿ������� �����̶�.
	maxVol = 0;
	for (i = 0; i < quantity; i++)
	{
		if (company->data[i].vol > maxVol)
		{
			maxVol = company->data[i].vol;
		}
	}

	interval = (int)(WIDTH_GRAPH / quantity); // ���� ���� ��ŭ ���� ĵ�� ���� ����

	// ���ǻ�κ��ʹ� '�ֱ� ������' ���� �޴´�.
	// ���� ���� �����ʺ��� �׷��� �Ѵ�.
	int x_end, y_end;
	x_end = X_START_GRAPH + WIDTH_GRAPH;
	y_end = Y_START_GRAPH + HEIGHT_GRAPH;

	ptData->startVal.quantity = company->quantity;
	for (int i = 0; i < ptData->startVal.quantity; i++)
	{
		ptData->startVal.point[i].X = x_end - (i * interval);
		ptData->startVal.point[i].Y = y_end - (HEIGHT_GRAPH * (company->data[i].startVal - minVal)) / (maxVal - minVal);
	}
	
	ptData->highVal.quantity = company->quantity;
	for (i = 0; i < ptData->highVal.quantity; i++)
	{
		ptData->highVal.point[i].X = x_end - (i * interval);
		ptData->highVal.point[i].Y = y_end - (HEIGHT_GRAPH * (company->data[i].highVal - minVal)) / (maxVal - minVal);
	}

	ptData->lowVal.quantity = company->quantity;
	for (i = 0; i < ptData->lowVal.quantity; i++)
	{
		ptData->lowVal.point[i].X = x_end - (i * interval);
		ptData->lowVal.point[i].Y = y_end - (HEIGHT_GRAPH * (company->data[i].lowVal - minVal)) / (maxVal - minVal);
	}

	ptData->lastVal.quantity = company->quantity;
	for (i = 0; i < ptData->lastVal.quantity; i++)
	{
		ptData->lastVal.point[i].X = x_end - (i * interval);
		ptData->lastVal.point[i].Y = y_end - (HEIGHT_GRAPH * (company->data[i].lastVal - minVal)) / (maxVal - minVal);
	}

	//--- volume chart
	y_end = Y_START_GRAPH + HEIGHT_GRAPH + GAP_GRAPH_VOLUME + HEIGHT_VOLUME;

	ptData->volume.quantity = company->quantity;
	for (i = 0; i < ptData->volume.quantity; i++)
	{
		ptData->volume.point[i].X = x_end - (i * interval);
		ptData->volume.point[i].Y = y_end - (HEIGHT_VOLUME * company->data[i].vol) / maxVol;
	}
}
