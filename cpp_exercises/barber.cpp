#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>
using namespace std;

sem_t wait_cust_sem, wait_shav_sem;
pthread_mutex_t mymutex;
int customers = 0;

pthread_t cust_A;
pthread_t cust_B;
pthread_t cust_C;
pthread_t barber;

void* customer_thread(void* vptr)
{
        while(1)
        {
                sem_post(&wait_cust_sem);
                pthread_mutex_lock(&mymutex);
                        customers++; //critical section work
                        cout << "customers: " << customers << endl;
                pthread_mutex_unlock(&mymutex);

                sem_wait(&wait_shav_sem);

                sleep(500);
        }
}

void* barber_thread(void* vptr)
{
        while(1)
        {
                sem_wait(&wait_cust_sem);
                pthread_mutex_lock(&mymutex);
                        customers--; //critical section work
                        cout << "One customer shaved. Customers: " << customers << endl;
                pthread_mutex_unlock(&mymutex);
                sem_post(&wait_shav_sem);

                sleep(500);
        }
}

int main (void)
{
        pthread_create(&cust_A, NULL, &customer_thread, NULL);
        pthread_create(&cust_B, NULL, &customer_thread, NULL);
        pthread_create(&cust_C, NULL, &customer_thread, NULL);
        pthread_create(&barber, NULL, &barber_thread, NULL);

        pthread_join(cust_A, NULL);
        pthread_join(cust_B, NULL);
        pthread_join(cust_C, NULL);
        pthread_join(barber, NULL);

        return 0;
}
