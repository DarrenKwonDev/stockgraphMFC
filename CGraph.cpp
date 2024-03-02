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
	// 정적 지역 변수 (일종의 전역 변수며 수거되지 않음)
	// 함수 호출 사이에서도 값이 유지되며, stack frame을 벗어나도 값이 유지됨.
	static PointData ptData; 
	GetDataForChart(company, &ptData);
	return &ptData;
}

void CGraph::GetDataForChart(Company* company, PointData* ptData)
{
	int i, maxVal, minVal, maxVol, interval;

	


	// 종목이 가진 값 중 가장 높은 값을 찾습니다.
	// 왜냐하면 그래프 최대 높이 기준이 필요하거든요.
	maxVal = 0;
	int quantity = company->quantity;
	for ( i = 0; i < quantity; i++)
	{
		if (company->data[i].highVal > maxVal)
		{
			maxVal = company->data[i].highVal;
		}
	}


	// 종목이 가진 값 중 가장 낮은 값을 찾습니다. 
	// 왜냐하면 그래프 최하선 기준이 필요하거든요.
	minVal = maxVal;
	for (i = 0; i < quantity; i++)
	{
		if (company->data[i].lowVal < minVal)
		{
			minVal = company->data[i].lowVal;
		}
	}

	
	// 최대 볼륨을 찾습니다.
	// 볼륨 그래프의 높이 기준이 필요하기 때문에.
	// 참고로 최소 볼륨은 찾을 필요 없습니다. 어차피 볼륨 그래프는 바닥에서부터 시작이라.
	maxVol = 0;
	for (i = 0; i < quantity; i++)
	{
		if (company->data[i].vol > maxVol)
		{
			maxVol = company->data[i].vol;
		}
	}

	interval = (int)(WIDTH_GRAPH / quantity); // 종목 갯수 만큼 나눠 캔들 간격 설정

	// 증권사로부터는 '최근 데이터' 부터 받는다.
	// 따라서 가장 오른쪽부터 그려야 한다.
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
