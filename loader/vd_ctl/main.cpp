#include <stdio.h>
#include "vx_disp.h"
#include "Common.h"

/* ini
http://www.codeguru.com/cpp/misc/misc/article.php/c233/CIniFile--Class-for-Reading-and-Writing-INI-Files.htm
*/

using namespace std;

#include "iniFile/iniFile.h"

#pragma comment(lib,"Setupapi.lib")

struct configure{
	string launcher_opt;
	string hardwareid;
	string drivername;
	POINT resol[3];
};

struct configure g_conf;

int load_configure(void)
{
	string res;
	CIniFile ini_p("setting.ini");
	if(ini_p.ReadFile())
	{

		g_conf.launcher_opt = ini_p.GetValue("Launcher","executeArgument");

		sscanf((char*)ini_p.GetValue("Monitor","1").c_str()," %d, %d",&g_conf.resol[0].x,&g_conf.resol[0].y);
		sscanf((char*)ini_p.GetValue("Monitor","2").c_str()," %d, %d",&g_conf.resol[1].x,&g_conf.resol[1].y);
		sscanf((char*)ini_p.GetValue("Monitor","3").c_str()," %d, %d",&g_conf.resol[2].x,&g_conf.resol[2].y);	

		g_conf.drivername = ini_p.GetValue("Driver","DRIVER_NAME");
		g_conf.hardwareid = ini_p.GetValue("Driver","HARDWAREID_NAME");
	}
	else
	{
		puts("setting.ini file not found!");
		return -1;
	}
	return 0;
}

int main(int argc,char **argv)
{
	int p,i,monCnt;
	CVxDispDrv vx;
	POINT sz;
	DWORD exitCode = 0;

	/*
		�ؾ��� ��
		1. ����� �� ������ �����ϵ��� ���� ���� �߰�.(ini ������ ���ؼ� �Ǵ� XML) - OK
		2. Oculus�� Monitor Adapter ��ȣ�� ������� Ȯ��(Ȯ�ο� ��Ʈ���� ���������� ���� �Է�) �� executeCommandLine���� adapter ��ȣ�� �Ѱ��ٰ�
		3. executeCommandLine�� ���� ���α׷� ���� ��, (vx.enable�ϸ鼭) primary monitor�� vx.enable�� ����� �� �ϳ��� ���� �� ���α׷� ���� ���� primary monitor�� ���� primary monitor�� �ǵ���
	*/
	if(load_configure())
		return -1;

	sz.x = 1600;
	sz.y = 1200;
	
	vx.SetDriverName(g_conf.drivername);
	vx.SetHardwareID(g_conf.hardwareid);
	vx.init();


	vx.mon_begin();
	monCnt = vx.GetMonitorCount();
	// �������� �� fail �߰� �� �� �ֵ���
	for(i=0;i<monCnt;i++)
	{
		sz = g_conf.resol[i];
		vx.enable(i,sz);
	}

	if(monCnt)
	{
		string argm;

		Sleep(1000);	//����Ͱ� ���������� Ȯ��ɶ����� ��ٸ�
		argm = "protype.exe ";
		argm += g_conf.launcher_opt;

		vx.changePrimaryMonitor();

		if(!executeCommandLine(argm.c_str(),exitCode))
			MessageBox(NULL,"Fail!","Error",MB_OK);
	}

	for(i=0;i<monCnt;i++)
		vx.disable(i);

	vx.mon_end();

	return 0;
}