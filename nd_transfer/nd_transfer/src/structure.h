#pragma once

// lib header.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>

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

class NeperDDA
{
public:
	int i_NumVertex;
	int i_NumFace;
	vector<CNeperVertex> lv_NeperVertex;
	vector<CNeperFace> lv_NeperFace;
	void fFindPositionVertex(ifstream &infile_0);
	void fFindPositionFace(ifstream &infile_0);
	void fReadNeper_tess(string str_0);
	void fWriteDDABlock_json(string str_0);
	void fWriteDDABlock_vtp(string str_0);
};




