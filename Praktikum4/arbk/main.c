/*
 * main.c
 *
 * Created: 19.07.2024 12:01:19
 * Author : Fachbereich 5 - FH Aachen
 */
 #include "tasks.h"
 
 //! Enter the current task number (2 - 4)
 #define TASK 4

/*!
 * Selects task-function according to TASK define
 */
int main(void)
{
	#if (TASK == 2)
		task2();
	#endif
	#if (TASK == 3)
		task3();
	#endif
	#if (TASK == 4)
		task4();
	#endif
}
