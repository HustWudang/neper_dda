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
	cout << " Transfer Gmsh file (1.msh) to DDA block file (block.json) ...\n";
	cout << "-----\n";
	std::string sfin_base = fGetFileNamePathStringFromFileInRootPath("filename.txt");
	std::string sfin_tess = sfin_base + ".tess";
	std::string sfot_blk_json = sfin_base + "_block.json";
	std::string sfot_blk_vtp = sfin_base + "_block.vtp";
	NeperDDA mNeperDDA_1;
	mNeperDDA_1.fReadNeper_tess(sfin_tess);
	mNeperDDA_1.fWriteDDABlock_json(sfot_blk_json);
	mNeperDDA_1.fWriteDDABlock_vtp(sfot_blk_vtp);
	// [Main function return].
	system("pause");
	return 0;
}
