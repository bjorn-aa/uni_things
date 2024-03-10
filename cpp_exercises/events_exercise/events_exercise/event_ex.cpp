using namespace std;

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#define EVER ;; 


HANDLE calc_threads[5];
HANDLE calc_events[4];
HANDLE ready_event;

int mul_number_1 = 0, mul_number_2 = 0, mul_result = 0;
int div_number_1 = 0, div_number_2 = 0, div_result = 0;
int add_number_1 = 0, add_number_2 = 0, add_result = 0;
int sub_number_1 = 0, sub_number_2 = 0, sub_result = 0;

void mul_thread(void)
{
	for (EVER)
	{
		WaitForSingleObject(ready_event, INFINITE);
		mul_result = mul_number_1 * mul_number_2;
		//cout << "Multiplication successful!\n";
		SetEvent(calc_events[0]);
	}
}
void div_thread(void)
{
	for (EVER)
	{
		WaitForSingleObject(ready_event, INFINITE);
		if(div_number_2 > 0)
		div_result = div_number_1 / div_number_2;
		//cout << "Division successful!\n";
		SetEvent(calc_events[1]);
	}
}
void add_thread(void)
{
	for (EVER)
	{
		WaitForSingleObject(calc_events[0], INFINITE);
		WaitForSingleObject(calc_events[1], INFINITE);
		add_result = add_number_1 + add_number_2;
		//cout << "Addition successful!\n";
		SetEvent(calc_events[3]);
	}
}
void sub_thread(void)
{
	for (EVER)
	{
		WaitForSingleObject(calc_events[3], INFINITE);
		sub_result = sub_number_1 - sub_number_2;
		//cout << "Subtraction successful!\n";
		ResetEvent(calc_events[0]);
		ResetEvent(calc_events[1]);
		ResetEvent(calc_events[2]);
		ResetEvent(calc_events[3]);
		SetEvent(ready_event);
	}
}
void calc_thread(void)
{
	mul_number_1 = 4;
	mul_number_2 = 3;
	div_number_1 = 8;
	div_number_2 = 2;
	add_number_1 = sub_result;
	add_number_2 = div_result;
	sub_number_1 = mul_result;
	sub_number_2 = 2;

	cout << (int)add_result << "\n";
}


int main(void)
{
	while (1)
	{
		calc_threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mul_thread, NULL, 0, NULL);
		calc_threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)div_thread, NULL, 0, NULL);
		calc_threads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)add_thread, NULL, 0, NULL);
		calc_threads[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sub_thread, NULL, 0, NULL);
		calc_threads[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)calc_thread, NULL, 0, NULL);

		calc_events[0] = CreateEvent(NULL, TRUE, FALSE, "mul_event");
		calc_events[1] = CreateEvent(NULL, TRUE, FALSE, "div_event");
		calc_events[2] = CreateEvent(NULL, TRUE, FALSE, "add_event");
		calc_events[3] = CreateEvent(NULL, TRUE, FALSE, "sub_event");
		ready_event = CreateEvent(NULL, TRUE, TRUE, "ready_event");

		
	}
	return 0;
}
