#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <fstream>
#include <iostream>
#include "EngineOff.h"

#define CHARPERLINE 500
#define CHARPERWORD 100
#define FILEPATH "/etc/apache2/apache2.conf"
// ����� on ��� �߰��ϱ�
// - 1���� ������ 3�� �����
// - ������ ������ line�� �����

EngineOff::EngineOff()
{
}


EngineOff::~EngineOff()
{
}


int EngineOff::exec(char* _path)
{
	
	string str = "<Directory /var/www/html/"+ (string)_path + (string)">";
	string strend = "</Directory>\0";
	string stroff = "\tphp_admin_value engine off\0";

	//file read
	pFile = fopen(FILEPATH, ("rb"));
	if (pFile == NULL) {
		cout << "Not open" << endl;
		return 0;
	}
	long totnum = 0;
	long curnum = 0;
	int flag = 0;

	_fseeki64(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	cout << lSize << endl;
	_fseeki64(pFile, 0, SEEK_SET);

	char* buf = (char*)malloc(sizeof(char)*lSize);
	char* buf2 = (char*)malloc(sizeof(char) * CHARPERLINE);
	char* buf3 = (char*)malloc(sizeof(char) * CHARPERWORD);

	while (curnum = fread(&buf[totnum], sizeof(char), lSize - totnum, pFile) > 0) {
		totnum += curnum;
	}

	cout << buf << endl;

	getchar();

	buf2 = strtok(buf,"\n");

	cout << "buf2: " << buf2 << endl;

	getchar();
	//if already exists
	while (buf2) {
		
		cout << buf2 << endl;
		cout << str << endl;
		cout << stroff << endl;
		cout << strend << endl;

		if (strncmp(buf2,str.c_str(),strlen(str.c_str())) == 0) {
			flag = 1;
			cout << "flag = 1 " << endl;
		}
		if (flag == 1) {
			if (strncmp(buf2, stroff.c_str(), strlen(stroff.c_str())) == 0) {
				flag = 2;
				cout << "flag = 2 " << endl;
				break;
			}
			else if (strncmp(buf2, strend.c_str(), strlen(strend.c_str())) == 0) {
				flag = 0;
				cout << "flag = 0 " << endl;
			}
		}
		getchar();
		buf2 = strtok(NULL, "\n");
	}

	//there is already engine off
	if (flag == 2){
		return 0;

		free(buf);
		free(buf2);

	}
	else if (flag == 0) {

		fclose(pFile);

		pFile = fopen(_path, "a");
		if (pFile == NULL) {
			cout << "Not open" << endl;
			return 0;
		}
		printf("final output\n%s\n%s\n%s", str.c_str(), stroff.c_str(), strend.c_str());
		fprintf(pFile, "%s\n%s\n%s",str.c_str(),stroff.c_str(),strend.c_str());
		
		free(buf);
		free(buf2);
		
		return 1;
	}

	else {
		cout << "something wrong" << endl;

		free(buf);
		free(buf2);

		return 0;

	}
}