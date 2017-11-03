//例子1：以二进制模式打开并写入文件
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
				cout << "Usage: [-h] [-file file_path] " << endl;
			else if (string(argv[i]) == "-file")
			{
				if (argc < 3)
				{
					cout << "Usage: [-h] [-file file_path] " << endl;
					break;
				}
				else
				{
					char *file_name = argv[i + 1];
					Enter(file_name);
					return 1;
				}
			}
			else cout << "Usage: [-h] [-file file_path] " << endl;
		}
	}
	else
	{
		cout << "Usage: [-h] [-file file_path] " << endl;

	}
	return 0;
}