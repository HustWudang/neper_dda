/*
* Main procedure to make the transfer
* from Neper file "0.tess"
* to DDA program "0_block.json"
*/

// header file.
#include "structure.h"

// namespace std;
using namespace std;

// function to obtain string (file name path) from "filename.txt".
// the file name is used to define all file names associated with the analysis module.
std::string fGetFileNamePathStringFromFileInRootPath(std::string s_RootFileName)
{
	// [File-name] Load filename.txt in root directory ...
	string s_FilePath;
	ifstream iflname;
	iflname.open(s_RootFileName);
	if (iflname.is_open())
	{
		getline(iflname, s_FilePath);
		std::cout << "[Msg][File] open filename.txt ... \n";
		std::cout << "[Msg] Get filename for model & analyis ... \n";
		iflname.close();
	}
	else { std::cout << "[Error][File] open filename.txt !\n"; }
	return s_FilePath;
}

// main function.
int main()
{
	// [Screen Reminder].
	cout << "-----\n";
	cout << " Transfer Gmsh file (1.tess) to DDA block file (block.json) ...\n";
	cout << "-----\n";
	std::string sfin_base = fGetFileNamePathStringFromFileInRootPath("filename.txt");
	std::string sfin_tess = sfin_base + ".tess";
	std::string sfin_material_txt = sfin_base + "_material.txt";
	std::string sfot_blk_json = sfin_base + "_block_1.json";
	std::string sfot_blk_vtp = sfin_base + "_block_1.vtp";
	std::string sfot_blk_2_json = sfin_base + "_block_2.json";
	std::string sfot_blk_2_vtp = sfin_base + "_block_2.vtp";
	NeperDDA mNeperDDA_1;
	mNeperDDA_1.fReadNeper_tess(sfin_tess);
	mNeperDDA_1.fGenerateMaterialIndexFromInputFile(sfin_material_txt);
	mNeperDDA_1.fWriteDDABlock_json(sfot_blk_json);
	mNeperDDA_1.fWriteDDABlock_vtp(sfot_blk_vtp);
	mNeperDDA_1.fWriteDDABlock_json_2(sfot_blk_2_json);
	mNeperDDA_1.fWriteDDABlock_vtp_2(sfot_blk_2_vtp);
	// [Main function return].
	system("pause");
	return 0;
}
