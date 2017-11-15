
#include <iostream>
#include "header.h"

using namespace std;

int main(int argc, char ** argv)
{
	if (argc > 1)
	{
		for (int i = 1; i<argc; i++)
		{
			if (string(argv[i]) == "-h")
				cout << "Usage: [-h] [-file file_path -type [Statistics of all page: 1 ,Scan all pages: 0,default 0]] " << endl;
			else if (string(argv[i]) == "-file")
			{
				if (argc < 3)
				{
					cout << "Usage: [-h] [-file file_path -type [Statistics of all page: 1 ,Scan all pages: 0,default 0]] " << endl;
					break;
				}
				else
				{
					char *file_name = argv[i + 1];
					ulint scan_type = atoi(argv[i + 3]);
					Enter(file_name,&scan_type);
					return 1;
				}
			}
			else cout << "Usage: [-h] [-file file_path -type [Statistics of all page: 1 ,Scan all pages: 0, default 0]] " << endl;
		}
	}
	else
	{
		cout << "Usage: [-h] [-file file_path -type [Statistics of all page: 1 ,Scan all pages: 0,default 0]] " << endl;

	}
	return 0;
}
