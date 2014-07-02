#include <windows.h>

typedef struct vx_state vx_state;
typedef struct vx_mon_state vx_mon_state;

vx_state *vx_init();			//����̹� �ʱ�ȭ
void vx_release(vx_state *vx);		//����̹� ����
int vx_get_devices(vx_state *vx);	//����� ���� ����
void vx_set_devices_position();	//����͵��� ��ġ �� �ػ󵵸� ������
vx_mon_state *vx_get_desc(vx_state *vs,int idx);		//�ش� ����̹��� ��ũ���͸� ����
BOOL vx_mon_isUpdate(vx_mon_state *mon);	//�ش� ����Ͱ� ������Ʈ �Ǿ��� ?
void vx_mon_tokenUpdate(vx_mon_state *mon);
PCHAR vx_mon_getFramebuffer(vx_mon_state *mon);	//framebuffer�� �����͸� ����
POINT vx_mon_getResolution(vx_mon_state *mon);	//�ػ� ������ ����
void vx_mon_changeResolution(vx_mon_state *mon,POINT res);	//�ش� ������� �ػ󵵸� ����