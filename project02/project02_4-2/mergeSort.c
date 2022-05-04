#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>

int a[30], b[15], c[15], d[30];
int size_sub1, size_sub2;

void sublist1(int a[])
{
  sleep(1);
  int i, j, temp;
  for (i = 0; i < size_sub1; i++)
  {
    for (j = 0; j < size_sub1 - i - 1; j++)
    {
      if (a[j + 1] < a[j])
      {
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }

  for (i = 0; i < size_sub1; i++)
    b[i] = a[i];

  //First Sorted array
  for (i = 0; i < size_sub1; i++)
    printf("%d \t", b[i]);
}

void sublist2(int a[])
{
  sleep(2);
  int i, j, temp;
  for (i = 0; i < size_sub2; i++)
  {
    for (j = 0; j < size_sub2 - i - 1; j++)
    {
      if (a[j + 1] < a[j])
      {
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
  for (i = 0; i < size_sub2; i++)
    c[i] = a[i];

  //Second Sorted array
  for (i = 0; i < size_sub2; i++)
    printf("%d \t", c[i]);
}

void mergelist(int a[])
{
  sleep(3);
  int i, j, k, temp;
  int size_total = size_sub1 + size_sub2;
  for (i = 0; i < size_sub1; i++)
    a[i] = b[i];

  k = size_sub1;
  for (i = 0; i < size_sub2; i++)
  {
    a[k] = c[i];
    k++;
  }
  
  //Merged Array
  for (i = 0; i < size_total; i++)
  {
    d[i] = a[i];
    printf("%d \t", d[i]);
  }

  for (i = 0; i < size_total; i++)
  {
    for (j = 0; j < size_total - i - 1; j++)
    {
      if (d[j + 1] < d[j])
      {
        temp = d[j];
        d[j] = d[j + 1];
        d[j + 1] = temp;
      }
    }
  }
  
  //Merge Sort
  for (i = 0; i < size_total; i++)
    printf("%d \t", d[i]);
}

void main()
{
  int n, i, j, k;
  pthread_t th1, th2, th3;
  
  scanf("%d", &n);

  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  for (i = 0, j = 0; i < n / 2; i++)
  {
    b[j] = a[i];
    j++;
  }
  size_sub1 = j;
  for (i = n / 2, k = 0; i < n; i++)
  {
    c[k] = a[i];
    k++;
  }
  size_sub2 = k;

  printf("First array:\n");
  for (i = 0; i < n / 2; i++)
    printf("%d \n", b[i]);

  printf("Second array:\n");
  for (i = 0; i < n / 2; i++)
    printf("%d\n", c[i]);

  pthread_create(&th1, NULL, sublist1, &b);
  pthread_create(&th2, NULL, sublist2, &c);
  pthread_create(&th3, NULL, mergelist, &d);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);
}
