#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t chair_sem[3];
sem_t std;
sem_t ta_sleep; 

pthread_t *Students; 
pthread_t TA; 

int chair_count = 0;
int index_chair = 0;
int count_TA = 0;
int count_Std = 0;
pthread_mutex_t ChairAccess;


void * TA_check()
{	
	while(2)

	{
		count_TA++;
		sem_wait(&ta_sleep);	
		printf("std comes\n");
		printf("TA awakes\n");
		while(1)
		{
			
			pthread_mutex_lock(&ChairAccess);
			if(chair_count == 0) 
			{
				
				pthread_mutex_unlock(&ChairAccess);
				break;

			}

			

			sem_post(&chair_sem[index_chair]); 
			chair_count--;  
			printf("Std left the chair in waiting room. Remaining Chairs %d\n",3 - chair_count);
			index_chair = (index_chair + 1) % 3;
			pthread_mutex_unlock(&ChairAccess);
		
			printf("\t TA is helping the student now.\n");
			sleep(5);
			sem_post(&std);
			usleep(1000);

		}

	}

}


void *Student_Check(void *threadID) 
{
	int Time_with_ta;
	while(2)

	{
		count_Std++;
		printf("Std %ld doing HW .\n", (long)threadID);

		Time_with_ta = rand() % 10 + 1;; 
		sleep(Time_with_ta);		
		printf("Std %ld needs help from the TA\n", (long)threadID);
		pthread_mutex_lock(&ChairAccess); 
		int count = chair_count;

		pthread_mutex_unlock(&ChairAccess);
		if(count < 3)		
		{
			if(count == 0)		
				sem_post(&ta_sleep); 
			else
			printf("Std %ld sat on a chair waiting for the TA to finish. \n", (long)threadID);

			pthread_mutex_lock(&ChairAccess); 

			int index = (index_chair + chair_count) % 3;
			chair_count++;
			printf("Std sat on chair.Chairs Remaining: %d\n", 3 - chair_count);
			pthread_mutex_unlock(&ChairAccess);
			// unlock
			sem_wait(&chair_sem[index]);	
			printf("\t Std %ld is done the Hw with TA. \n", (long)threadID);
			sem_wait(&std);
			printf("Std %ld left TA room.\n",(long)threadID);

		}

		else 
			printf("Student %ld will return in the future. \n", (long)threadID);

		

	}

}

int main()

{

	int num_of_students = 3;		

	int id;
	srand(time(NULL));

	sem_init(&ta_sleep, 0, 0);

	sem_init(&std, 0, 0);

	for(id = 0; id < 3; ++id)	
		sem_init(&chair_sem[id], 0, 0);
	pthread_mutex_init(&ChairAccess, NULL);
	Students = (pthread_t*) malloc(sizeof(pthread_t)*num_of_students);

	pthread_create(&TA, NULL, TA_check, (void*) (long)id);	
	for(id = 0; id < num_of_students; id++)
		pthread_create(&Students[id], NULL, Student_Check,(void*) (long)id);
        pthread_join(TA, NULL);
	for(id = 0; id < num_of_students; id++)
pthread_join(Students[id], NULL);
free(Students);
	return 0;

}

