/**
 *	Created Time: 2009-11-20 14:38:55
 *	Last Modified: 2009-11-20 14:38:55
 *	File Name: ioctl.c
 *	Description: 
 */
#include <linux/usbdevice_fs.h>
#include <sys/ioctl.h>
#include <stdio.h>

static void test_iox()
{
	printf("0x%x\n", _IOR('U', 0x00, int));
}
int main()
{
	int cmd[100] = {0x80045500, 0x81785501, 0x40045532, 0x5401};
	int i;
	printf("USBDEVFS_CONTROL: 0x%x\n", USBDEVFS_CONTROL);


	for (i = 0; i < 100 && cmd[i]; i++){
		printf("cmd: 0x%x: (dir, size, type, nr) = (%d, %d, %d, %d)\n", cmd[i], _IOC_DIR(cmd[i]), _IOC_SIZE(cmd[i]), 
					_IOC_TYPE(cmd[i]), _IOC_NR(cmd[i]));
	}

	test_iox();
	return 0;
}
