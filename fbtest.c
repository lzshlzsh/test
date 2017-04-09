#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

int main()
{
        int fbfd = 0;
        struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
        long int screensize = 0;
        int * fbp = 0;
        int i;
        int x = 0, y = 0;
        long int location = 0;
	
        
        fbfd = open("/dev/fb0", O_RDWR);
        if (!fbfd) {
                printf("Error: cannot open framebuffer device.\n");
                exit(1);
        }


        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
                printf("Error reading fixed information.\n");
                exit(2);
        }
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
                printf("Error reading variable information.\n");
                exit(3);
        }
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
        //screensize = 1024*768 * vinfo.bits_per_pixel / 8;
        fbp = (int *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,fbfd, 0);
        if ((int)fbp == -1) {
                printf("Error: failed to map framebuffer device to memory.\n");
                exit(4);
        }
        printf("/dev/fb0:\n xres=%d,yres=%d,bpp=%d\n",vinfo.xres,vinfo.yres,vinfo.bits_per_pixel);
#if 0
        for(i=0;i<screensize/4;i++) //整个屏幕置为绿色
         *(fbp+i) = 255<<8 ;
#else 
       for(x=0;x<vinfo.xres;x++)
       		for(y=0;y<vinfo.yres;y++) 
                {
             	location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +(y+vinfo.yoffset) * finfo.line_length; 
             	*(fbp + location/4) = 0xff; /*  blue */
             	*(fbp + location/4 + 1) = 0x00;     
                }         
#endif	
        munmap(fbp, screensize);
        close(fbfd);
        return 0;
}


