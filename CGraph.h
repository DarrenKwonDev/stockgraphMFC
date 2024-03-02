#pragma once
#include "CStock.h"

#define X_START_GRAPH (10)
#define Y_START_GRAPH (10)

#define WIDTH_GRAPH (1000)
#define HEIGHT_GRAPH (400)

#define HEIGHT_VOLUME (150)

#define GAP_GRAPH_VOLUME (40)

#define WIDTH_LINE (1)
#define WIDTH_THICK_LINE (3)

// 화면내 좌표
struct Point {
	int X;
	int Y;
};

struct PointArray {
	int quantity;
	Point point[MAX_DATA]; // 한 company의 가격 데이터. {{x, y}, {x, y}, ...}
};

struct PointData {
	PointArray startVal;
	PointArray highVal;
	PointArray lowVal;
	PointArray lastVal;
	PointArray volume;
};

class CGraph
{
public:
	CGraph();
	virtual ~CGraph();

public:
	static PointData* GetPointData(Company* company);
	static void GetDataForChart(Company* company, PointData* ptData);
};