#include <stdio.h>
#include <alsa/asoundlib.h>
#include <stdlib.h>

int main()
{
	long loops;
	int  rc;
	int  size;
	snd_pcm_t *handle;
	snd_pcm_hw_params_t *params;
	unsigned int val;
	int dir;
	snd_pcm_uframes_t  frames;
	char *buffer;

	if ( (rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0){
		printf("unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(handle, params);
	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_channels(handle, params, 2);

	val = 44100;

	snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

	frames = 32;
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

	if ( (rc = snd_pcm_hw_params(handle, params)) < 0){
		printf("unable to set hw paramseters: %s\n", snd_strerror(rc));
		exit(1);
	}
	snd_pcm_hw_params_get_period_size(params, &frames, &dir);

	size = frames * 4;
	buffer = (char *)malloc(size);
	snd_pcm_hw_params_get_period_time(params, &val, &dir);

       loops = 50;//5000000 / val;
       while (loops > 0) {
              loops--;
/*              if ( (rc = read(0, buffer, size)) == 0){
                     std::cerr << "end of file on input" << std::endl;
                     break;
              }
              else if (rc != size)
                     std::cerr << "short read: read " << rc << " bytes" << std::endl;
*/
			  printf("before snd_pcm_writei\n");
              if ( (rc = snd_pcm_writei(handle, buffer, frames)) == -EPIPE){
                     printf("underrun occurred\n");
                     snd_pcm_prepare(handle);
              }
              else if (rc < 0)
                     printf("error from writei: %s\n", snd_strerror(rc));
/*
              else if (rc != (int)frames)
                     std::cerr << "short write, write " << rc << " frames" << std::endl;
*/					 
			  printf("after snd_pcm_writei\n");
       }
       snd_pcm_drain(handle);
       snd_pcm_close(handle);
       free(buffer);
       return 0;
}
