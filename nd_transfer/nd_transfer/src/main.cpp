/*
* Main procedure to make the transfer
* from Neper file "0.tess"
* to DDA program "0_block.json"
*/

// header file.
#include "structure.h"

// namespace std;
using namespace std;

// main function.
int main()
{
	// [Screen Reminder].
	cout << "-----\n";
	cout << " Transfer Gmsh file (1.msh) to DDA block file (block.json) ...\n";
	cout << "-----\n";

	NeperDDA mNeperDDA_1;
	mNeperDDA_1.fReadNeper_tess("1.tess");
	mNeperDDA_1.fWriteDDABlock_json("1_block.json");
	mNeperDDA_1.fWriteDDABlock_vtp("1_block.vtp");
	// [Main function return].
	system("pause");
	return 0;
}
