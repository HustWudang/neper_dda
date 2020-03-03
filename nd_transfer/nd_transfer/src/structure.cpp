#include "structure.h"

void NeperDDA::fFindPositionVertex(ifstream &infile_0)
{
	// find position vertex;
	while (infile_0.good())
	{
		char line[256];
		infile_0.getline(line, 256);
		if (line[1] != '*') { continue; }
		else if (line[2] != '*') { continue; }
		else if (line[3] != 'v') { continue; }
		else if (line[4] != 'e') { continue; }
		else if (line[5] != 'r') { continue; }
		else if (line[6] != 't') { continue; }
		else if (line[7] != 'e') { continue; }
		else if (line[8] != 'x') { continue; }
		else {
			return; 
		}
	}
}

void NeperDDA::fFindPositionFace(ifstream &infile_0)
{
	// find position face;
	while (infile_0.good())
	{
		char line[256];
		infile_0.getline(line, 256);
		if (line[1] != '*') { continue; }
		else if (line[2] != '*') { continue; }
		else if (line[3] != 'f') { continue; }
		else if (line[4] != 'a') { continue; }
		else if (line[5] != 'c') { continue; }
		else if (line[6] != 'e') { continue; }
		else { return; }
	}
}

void NeperDDA::fReadNeper_tess(string str_0)
{
	ifstream infile;
	infile.open(str_0);
	if (infile.is_open())
	{
		// find vertex position;
		fFindPositionVertex(infile);
		infile >> i_NumVertex;
		for (int i_vertex = 0; i_vertex < i_NumVertex; i_vertex++)
		{
			CNeperVertex nNeperVertex_t;
			infile >> nNeperVertex_t.i_No >> nNeperVertex_t.x >> nNeperVertex_t.y >> nNeperVertex_t.z >> nNeperVertex_t.i_state;
			lv_NeperVertex.push_back(nNeperVertex_t);
		}
		fFindPositionFace(infile);
		infile >> i_NumFace;
		for (int i_face = 0; i_face < i_NumFace; i_face++)
		{
			// face vertex.
			CNeperFace nNeperFace_t;
			infile >> nNeperFace_t.i_No;
			infile >> nNeperFace_t.i_NumVertex;
			for (int i_facevertex = 0; i_facevertex < nNeperFace_t.i_NumVertex; i_facevertex++)
			{
				int i_VertexNo_t;
				infile >> i_VertexNo_t;
				nNeperFace_t.lv_VertexNo.push_back(i_VertexNo_t);
			}
			// face edge.
			infile >> nNeperFace_t.i_NumEdge;
			for (int i_faceedge = 0; i_faceedge < nNeperFace_t.i_NumEdge; i_faceedge++)
			{
				int i_EdgeNo_t;
				infile >> i_EdgeNo_t;
				nNeperFace_t.lv_EdgeNo.push_back(i_EdgeNo_t);
			}
			// face equation.
			infile >> nNeperFace_t.d >> nNeperFace_t.a >> nNeperFace_t.b >> nNeperFace_t.c;
			// face point.
			infile >> nNeperFace_t.i_FaceState >> nNeperFace_t.i_FacePoint >> nNeperFace_t.fp_x >> nNeperFace_t.fp_y >> nNeperFace_t.fp_z;
			lv_NeperFace.push_back(nNeperFace_t);
		}
		cout << "read 0.msh successfully ...\n";
		infile.close();
	}
	else
	{
		cout << "[Error] in opening .msh file !\n";
	}
}


void NeperDDA::fWriteDDABlock_json(string str_0)
{
	ofstream of;
	of.open(str_0);
	if (of.is_open())
	{
		for (int i_face = 0; i_face < i_NumFace; i_face++)
		{
			/////////// ----- BEGIN -----
			of << "{";
			/////////// ----- id -----
			of << "\"no\":" << i_face << ",";
			/////////// ----- node number -----
			of << "\"node_num\":" << lv_NeperFace[i_face].i_NumVertex << ",";
			/// ----- edge number -----
			of << "\"edge_num\":" << lv_NeperFace[i_face].i_NumEdge << ",";
			/////////// ----- node coordinate list -----
			of << "\"node_list\":";
			of << "[";
			for (int i_facevertex = 0; i_facevertex < lv_NeperFace[i_face].i_NumVertex - 1; i_facevertex++)
			{
				of << "[" << lv_NeperVertex[lv_NeperFace[i_face].lv_VertexNo[i_facevertex]-1].x << "," << lv_NeperVertex[lv_NeperFace[i_face].lv_VertexNo[i_facevertex]-1].y << "],";
			}
			of << "[" << lv_NeperVertex[lv_NeperFace[i_face].lv_VertexNo[lv_NeperFace[i_face].i_NumVertex - 1]-1].x << "," << lv_NeperVertex[lv_NeperFace[i_face].lv_VertexNo[lv_NeperFace[i_face].i_NumVertex - 1]-1].y << "]";
			of << "]" << ",";
			////////// ----- physical parameter -----
			of << "\"density\":" << 2500 << ",";
			of << "\"elastic_modulus\":" << 1E10 << ",";
			of << "\"poisson_ratio\":" << 0.25 << ",";
			of << "\"cohesion\":" << 1E6 << ",";
			of << "\"friction_angle\":" << 45 << ",";
			////////// ----- other conditions -----
			of << "\"velo\":";
			of << "[";
			for (int ii = 0; ii < 5; ii++)
			{
				of << 0 << ",";
			}
			of << 0;
			of << "]" << ",";
			of << "\"stress\":";
			of << "[";
			for (int ii = 0; ii < 2; ii++)
			{
				of << 0 << ",";
			}
			of << 0;
			of << "]" << ",";
			of << "\"strain\":";
			of << "[";
			for (int ii = 0; ii < 2; ii++)
			{
				of << 0 << ",";
			}
			of << 0;
			of << "]";
			/////////// ----- END -----
			of << "}\n";
		}
		of.close();
		cout << "write otblock.json successfully ...\n";
	}
	else
	{
		cout << "[Error] cannot open otblock.json !\n";
	}
}


void NeperDDA::fWriteDDABlock_vtp(string str_0)
{
	ofstream of;
	of.open(str_0);
	if (of.is_open())
	{
		////////// Output file head [little endian]
		of << "<?xml version=\"1.0\"?>";
		of << "<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">";
		of << "<PolyData>\n";
		////////// cycle the block list
		for (int i_face = 0; i_face < i_NumFace; i_face++)
		{
			////////// general
			int iNumBlockNode = lv_NeperFace[i_face].i_NumVertex;
			of << "<Piece NumberOfPoints=\"" << iNumBlockNode << "\" NumberOfVerts=\"" << 0 << "\"";
			of << " NumberOfLines=\"" << 0 << "\" NumberOfStrips=\"" << 0 << "\" NumberOfPolys=\"" << 1 << "\">";

			////////// Points - geometry
			of << "<Points>";
			of << "<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">";
			for (int i_facevertex = 0; i_facevertex < lv_NeperFace[i_face].i_NumVertex; i_facevertex++)
			{
				of << float(lv_NeperVertex[lv_NeperFace[i_face].lv_VertexNo[i_facevertex]-1].x) << " " << float(lv_NeperVertex[lv_NeperFace[i_face].lv_VertexNo[i_facevertex]-1].y) << " " << 0 << " ";
			}
			of << "</DataArray>";
			of << "</Points>";

			//////////// Point data - block attributes
			of << "<PointData>";
			of << "<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"2\" format=\"ascii\">";
			for (int i_facevertex = 0; i_facevertex < lv_NeperFace[i_face].i_NumVertex; i_facevertex++)
			{
				float ux = 0;
				float uy = 0;
				of << ux << " " << uy << " ";
			}
			of << "</DataArray>";
			of << "</PointData>";

			////////// Cell data - block attribtutes
			of << "<CellData>";
			of << "<DataArray type=\"Int32\" Name=\"ID\" format=\"ascii\">";
			int id = i_face;
			of << id << " ";
			of << "</DataArray>";
			of << "<DataArray type=\"Float32\" Name=\"Density\" format=\"ascii\">";
			float dens = 2500;
			of << dens << " ";
			of << "</DataArray>";
			of << "<DataArray type=\"Float32\" Name=\"Elastic_Modulus\" format=\"ascii\">";
			float e_m = 1E10;
			of << e_m << " ";
			of << "</DataArray>";
			of << "<DataArray type=\"Float32\" Name=\"Poisson_Ratio\" format=\"ascii\">";
			float p_r = 0.25;
			of << p_r << " ";
			of << "</DataArray>";
			of << "<DataArray type=\"Float32\" Name=\"Cohesion\" format=\"ascii\">";
			float coh = 1E6;
			of << coh << " ";
			of << "</DataArray>";
			of << "<DataArray type=\"Float32\" Name=\"Friction_Angle\" format=\"ascii\">";
			float f_a = 45;
			of << f_a << " ";
			of << "</DataArray>";
			of << "<DataArray type=\"Float32\" Name=\"Stress\" NumberOfComponents=\"3\" format=\"ascii\">";
			float stress_xx = 0;
			float stress_yy = 0;
			float stress_xy = 0;
			of << stress_xx << " " << stress_yy << " " << stress_xy << " ";
			of << "</DataArray>";
			of << "<DataArray type=\"Float32\" Name=\"Strain\" NumberOfComponents=\"3\" format=\"ascii\">";
			float strain_xx = 0;
			float strain_yy = 0;
			float strain_xy = 0;
			of << strain_xx << " " << strain_yy << " " << strain_xy << " ";
			of << "</DataArray>";
			of << "</CellData>";

			////////// Polys - connectivity
			of << "<Polys>";
			of << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">";
			for (int i_facevertex = 0; i_facevertex < lv_NeperFace[i_face].i_NumVertex; i_facevertex++)
			{
				of << i_facevertex << " ";
			}
			of << "</DataArray>";

			////////// Polys - offset
			of << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">";
			of << lv_NeperFace[i_face].i_NumVertex;
			of << "</DataArray>";

			////////// Polys - end
			of << "</Polys>";

			////////// Piece - end
			of << "</Piece>\n";
		}
		////////// write file ender
		of << "</PolyData>";
		of << "</VTKFile>";
		of.close();
		cout << "write otblock.vtp successfully ...\n";
	}
	else
	{
		cout << "[Error-File] cannot open file otblock.vtp !\n";
	}
}