/*
	����� üũ �� ���� ���α׷�(��º� ���̺귯�� �׽�Ʈ�� ��)


  �����ؾ� �ϴ� ���

  v1. ����� ���� �� ExtEscape ��� �õ�
  2. �ػ� �����ϱ�

  http://www.codeproject.com/Articles/15072/Programmatically-change-display-resolution

  ��ġ�� ������ �� �����ɷ� ���δ�
  https://valelab.ucsf.edu/svn/micromanager2/branches/micromanager1.3/DeviceAdapters/GenericSLM/DisplayAdapters.cpp
	3. �������� ������ ���� Ȯ��

*/

#include "vx_driver.h"
#include <vector>

using namespace std;

int main(int argc, char *argv)
{
	vector<vx_mon_state*> mon_lst;
	
	vx_state *vx;
	int max,i;

	vx = vx_init();

	max = vx_get_devices(vx);
	for(i=0;i<max;i++)
	{
		vx_mon_state *vmon = vx_get_desc(vx,i);

		if(vmon)	//���� �������
			mon_lst.push_back(vmon);
	}
	
	printf("the number of detected virtual monitor %d\n",mon_lst.size());

	

	vx_release(vx);
	return 0;
}
