#pragma once

// lib header.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

// namespace std;
using namespace std;

// Gmsh basic elements.
class CNeperVertex
{
public:
	int i_No;
	int i_state;
	double x, y, z;
};

class CNeperFace
{
public:
	int i_No;
	int i_NumVertex;
	int i_NumEdge;
	vector<int> lv_VertexNo;
	vector<int> lv_EdgeNo;
	double d, a, b, c;
	int i_FaceState;
	int i_FacePoint;
	double fp_x, fp_y, fp_z;
};

class CMaterialType
{
public:
	int Index;
	double E;
	double U;
	double D;
	double Ratio;
	int i_Num;
};

class NeperDDA
{
public:
	int i_NumVertex;
	int i_NumFace;
	vector<CNeperVertex> lv_NeperVertex;
	vector<CNeperFace> lv_NeperFace;
	vector<int> lv_MaterialIndex;
	vector<CMaterialType> lv_MaterialType;
	void fFindPositionVertex(ifstream &infile_0);
	void fFindPositionFace(ifstream &infile_0);
	void fReadNeper_tess(string str_0);
	void fGenerateMaterialIndexFromInputFile(string str_0);
	void fWriteDDABlock_json(string str_0);
	void fWriteDDABlock_json_2(string str_0);
	void fWriteDDABlock_vtp(string str_0);
	void fWriteDDABlock_vtp_2(string str_0);
};




