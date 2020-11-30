#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)
pthread_mutex_t mutex;
int count = 0;

struct mystruct
{
	int begin, end, id;
};

int check_circuit (int z, int pid) {
  int v[16];        /* Each element is a bit of z */
  int i;

  for (i = 0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);

  // second least significant bit is 1?
  if(v[1] != 1) return 0;

  if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
      && (!v[3] || !v[4]) && (v[4] || !v[5])
      && (v[5] || !v[6]) && (v[5] || v[6])
      && (v[6] || !v[15]) && (v[7] || !v[8])
      && (!v[7] || !v[13]) && (v[8] || v[9])
      && (v[8] || !v[9]) && (!v[9] || !v[10])
      && (v[9] || v[11]) && (v[10] || v[11])
      && (v[12] || v[13]) && (v[13] || !v[14])
      && (v[14] || v[15])) {
    printf ("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",
	    v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],
	    v[10],v[11],v[12],v[13],v[14],v[15]);
    return 1;
  } else return 0;
}

void* child_thread(void* arg)
{
	struct mystruct* s = (struct mystruct*)arg;
	for (int i = s->begin; i < s->end; i++)
	{
		if(check_circuit(i, s->id))
		{
			pthread_mutex_lock(&mutex);
			count++;
			pthread_mutex_unlock(&mutex);
		}
	}
    return 0;
}

int main (int argc, char *argv[]) 
{

  // p (# of threads)
  int p;
  if(argc != 2)
  {
  	printf("Needs 1 argument\n");
  	return 0;
  }
  else
  {
  	p = atoi(argv[1]);
  	if(p<1 || p>128)
  	{
  		printf("Between 1, 128 threads\n");
  		return 0;
  	}
  }

  struct timeval t1, t2;
  pthread_t t_arr[p];
  int sum = 0;

  pthread_mutex_init(&mutex, NULL);
  gettimeofday(&t1, 0);
  
  for(int i=0; i<p; i++)
  {
  	struct mystruct* s = malloc(sizeof(struct mystruct));
  	
  	s->begin = sum;
  	sum += 65536/p;
  	if(i<65536%p)
  		sum++;

  	s->end = sum;
  	s->id = i;

  	pthread_t ti;
  	pthread_create(&ti, NULL, child_thread, (void*)s);
  	t_arr[i] = ti;
  }
  for(int i=0; i<p; i++)
  	pthread_join(t_arr[i], NULL);
  
  gettimeofday(&t2, 0);
  pthread_mutex_destroy(&mutex);

  printf ("Execution time %fs\n", (t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec)*1e-6);
  printf ("There are %d solutions\n", count);
  return 0;
}
