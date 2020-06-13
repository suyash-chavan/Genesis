/*---------------------------------------------------

	Authors:Sanmati Sattur
			Niraja Kulkarni
			Suyash Chavan

-----------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>
#include <dirent.h>
#include <time.h>
#include "headers/design.h"

/*-----------------------For Storing System Time-----------------------*/
time_t sys_time;
int hours, minutes, seconds, day, month, year;


/*------------------------Declaring Functions-----------------------*/
bool home();
bool login();
bool wrong_user();
bool verify_user(char *, char *);
bool student_data();
bool add_student();
bool my_schedule();
bool view_profile(int);
bool print_safe(char *);
bool attendance_record();
bool individual_profile(int );
bool print_note(char *);
bool clear_note();
bool note_not_found();
bool print_attendance(char *);
bool handle_attendance(char *, int *);
bool clear_attendance();
bool exam_record();
bool view_exams(int );
bool add_exam();
bool individual_exam(int );
bool clear_exam();
bool print_safe_exam(char *, char *);
bool empty_profiles();
bool empty_exams();

/*---------------------Mouse Pointer Coordinates----------------------*/
/*
POINT a;		Our approach was to capture mouse click events and choose the option
POINT *b;		but this failed as we were not able to capture the events.
*/
/*----------------------Main Function---------------------------------*/

/*
	Main function will control the call of all functions so that further
	there is no need to recursively call functions which can lead to stack overflow
	if there are many recursive calls by user. This consumes some amount of memory
	to store global variables but is necessary.
*/

/*------------------Global Variables to Control Flow of Program-------------*/
int view_profile_from = 0;
int home_option = 0;
int student_data_option = 0;
int exam_record_option = 0;
int view_exams_from = 0;

int main()
{
	/*-----------------------Getting and Saving System Time-----------------------*/

	time(&sys_time);
	struct tm *local = localtime(&sys_time);
	hours = local->tm_hour;
	minutes = local->tm_min;
	seconds = local->tm_sec;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	year = local->tm_year + 1900;

	/*-----------------------Time Saved in Global Variables-----------------------*/

	fullscreen();
	remove_scrollbar();


	/*------------------------Flow of Program------------------------------------*/

login_controller:
	if (!login())
	{
		wrong_user();
		Sleep(3000);
		goto login_controller;
	}


home_controller:
	if (!home())
		goto login_controller;
	else
	{
		if (home_option == 0)
			goto student_data_controller;
		else if (home_option == 1)
			goto exam_record_controller;
		else if (home_option == 2)
			goto attendance_record_controller;
		else if (home_option == 3)
			goto my_schedule_controller;
	}

student_data_controller:
	if (!student_data())
		goto home_controller;
	else
	{
		if (student_data_option == 0)
		{
			view_profile_from = 0;
			goto view_profile_controller;
		}
		else
			goto add_student_controller;
	}


view_profile_controller:
	if (!view_profile(view_profile_from))
	{
		goto student_data_controller;
	}
	else
	{
		goto view_profile_controller;
	}

add_student_controller:
	if (!add_student())
	{
		goto student_data_controller;
	}
	else
	{
		goto add_student_controller;
	}

exam_record_controller:
	if (!exam_record())
	{
		goto home_controller;
	}
	else
	{
		if (exam_record_option == 0)
			goto view_exams_controller;
		else if (exam_record_option == 1)
			goto add_exam_controller;
	}

view_exams_controller:
	if (!view_exams(view_exams_from))
	{
		goto exam_record_controller;
	}
	else
	{
		goto view_exams_controller;
	}

add_exam_controller:
	if (!add_exam())
	{
		goto exam_record_controller;
	}
	else
	{
		goto add_exam_controller;
	}

attendance_record_controller:
	if (!attendance_record())
		goto home_controller;
	else
		goto attendance_record_controller;

my_schedule_controller:
	if (!my_schedule())
		goto home_controller;
	else
		goto my_schedule_controller;

	return 0;
}


/*--------------------------------------Login Page-----------------------------------*/
/*
	This function take username and password from user and verify it, if found correct
	returns true else return false.
*/
bool login()
{
	system("cls");

	/*---------------------------------------Just Printing the Headings -------------------------------------------*/

	printf("\n\n");
	printf("\t\t\t        GGGGGGGGGGGGG     EEEEEEEEEEEEEEEEEEEEEE     NNNNNNNN        NNNNNNNN     EEEEEEEEEEEEEEEEEEEEEE        SSSSSSSSSSSSSSS      IIIIIIIIII        SSSSSSSSSSSSSSS \n");
	printf("\t\t\t     GGG::::::::::::G     E::::::::::::::::::::E     N:::::::N       N::::::N     E::::::::::::::::::::E      SS:::::::::::::::S     I::::::::I      SS:::::::::::::::S\n");
	printf("\t\t\t   GG:::::::::::::::G     E::::::::::::::::::::E     N::::::::N      N::::::N     E::::::::::::::::::::E     S:::::SSSSSS::::::S     I::::::::I     S:::::SSSSSS::::::S\n");
	printf("\t\t\t  G:::::GGGGGGGG::::G     EE::::::EEEEEEEEE::::E     N:::::::::N     N::::::N     EE::::::EEEEEEEEE::::E     S:::::S     SSSSSSS     II::::::II     S:::::S     SSSSSSS\n");
	printf("\t\t\t G:::::G       GGGGGG       E:::::E       EEEEEE     N::::::::::N    N::::::N       E:::::E       EEEEEE     S:::::S                   I::::I       S:::::S            \n");
	printf("\t\t\tG:::::G                     E:::::E                  N:::::::::::N   N::::::N       E:::::E                  S:::::S                   I::::I       S:::::S            \n");
	printf("\t\t\tG:::::G                     E::::::EEEEEEEEEE        N:::::::N::::N  N::::::N       E::::::EEEEEEEEEE         S::::SSSS                I::::I        S::::SSSS         \n");
	printf("\t\t\tG:::::G    GGGGGGGGGG       E:::::::::::::::E        N::::::N N::::N N::::::N       E:::::::::::::::E          SS::::::SSSSS           I::::I         SS::::::SSSSS    \n");
	printf("\t\t\tG:::::G    G::::::::G       E:::::::::::::::E        N::::::N  N::::N:::::::N       E:::::::::::::::E            SSS::::::::SS         I::::I           SSS::::::::SS  \n");
	printf("\t\t\tG:::::G    GGGGG::::G       E::::::EEEEEEEEEE        N::::::N   N:::::::::::N       E::::::EEEEEEEEEE               SSSSSS::::S        I::::I              SSSSSS::::S \n");
	printf("\t\t\tG:::::G        G::::G       E:::::E                  N::::::N    N::::::::::N       E:::::E                              S:::::S       I::::I                   S:::::S\n");
	printf("\t\t\t G:::::G       G::::G       E:::::E       EEEEEE     N::::::N     N:::::::::N       E:::::E       EEEEEE                 S:::::S       I::::I                   S:::::S\n");
	printf("\t\t\t  G:::::GGGGGGGG::::G     EE::::::EEEEEEEE:::::E     N::::::N      N::::::::N     EE::::::EEEEEEEE:::::E     SSSSSSS     S:::::S     II::::::II     SSSSSSS     S:::::S\n");
	printf("\t\t\t   GG:::::::::::::::G     E::::::::::::::::::::E     N::::::N       N:::::::N     E::::::::::::::::::::E     S::::::SSSSSS:::::S     I::::::::I     S::::::SSSSSS:::::S\n");
	printf("\t\t\t     GGG::::::GGG:::G     E::::::::::::::::::::E     N::::::N        N::::::N     E::::::::::::::::::::E     S:::::::::::::::SS      I::::::::I     S:::::::::::::::SS \n");
	printf("\t\t\t        GGGGGG   GGGG     EEEEEEEEEEEEEEEEEEEEEE     NNNNNNNN         NNNNNNN     EEEEEEEEEEEEEEEEEEEEEE      SSSSSSSSSSSSSSS        IIIIIIIIII      SSSSSSSSSSSSSSS   \n");

	printf("\n\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n\n");

	printf("\t\t\t\t\t\t\t\t\t+---------------------------------------------------------------+\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                     Enter Credientials                        |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|             Username:                                         |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|             Password:                                         |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t+---------------------------------------------------------------+\n");

	gotoxy(96, 37);

	char username[21] = {0};
	char password[21] = {0};
	char ch;
	int sze = 0;

	/*--------------------------------------------Getting input from user-------------------------------------------*/
	/*
		Note: We dont use scanf in any of the functions in this program because we need to get the character at the
			  instance itself when it is entered. By this we can control the flow of inputed data. So we used getch()
			  to get character by character input and and making decision. 
	*/
	while (ch = getch())
	{
		if (ch == 27)
		{
			exit(0);
		}

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			else
			{
				break;
			}
		}
		else if (ch == '\b' && sze == 0)
			continue;
		else if (ch == '\b')
		{
			printf("\b \b");
			username[sze] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) && sze < 20)
		{
			printf("%c", ch);
			username[sze] = ch;
			sze++;
		}
		else
			;
	}


	gotoxy(96, 41);

	int i = 0;

	while (ch = getch())
	{
		if (ch == 27)
			exit(0);

		if (ch == 13)
		{
			break;
		}
		else
		{
			if (ch == '\b' && i > 0)
			{
				printf("\b \b");
				password[i] = '\0';
				i--;
			}
			else if (ch != '\b' && i < 20)
			{
				printf("*");
				password[i] = ch;
				i++;
			}
		}
	}

/*--------------------------Checking whether input is of genuine user-------------------------*/
	if (verify_user(username, password))
		return true;

	return false;
}


/*-----------------------------User Verification---------------------------*/
bool verify_user(char *username, char *password)
{
	char uname[21] = {0};
	char pass[21] = {0};
	FILE *fptr;

	fptr = fopen("C:/Student_Management_System/Database/General_Data.bat", "r");

	/*-----------------------Just checking if the username and password is matching--------------------------------*/
	/*
		We have not designed encryption system for the application whereas if we want to, then we can simply create
		function for encrypting and decrypting string and encrypting string before saving and retriving it after 
		decrypting.
	*/

	if (fptr != NULL)
	{

		char line[256];
		int i = 0;
		while (fgets(line, sizeof(line), fptr))
		{
			i++;

			if (i == 3 )
			{
				strcpy(uname, line);
			}
			else if (i == 4)
			{
				strcpy(pass, line);
			}
		}
	}

	uname[strlen(uname) - 1] = '\0';
	pass[strlen(pass) - 1] = '\0';

	if (!strcmp(uname, username) && !strcmp(pass, password))
		return true;

	return false;
}

/*-------------------------Warning if USername/Password entered is Wrong----------------------------*/
bool wrong_user()
{
	system("cls");

	/*---------------------------------------Just Printing the Headings -------------------------------------------*/

	printf("\n\n");
	printf("\t\t\t        GGGGGGGGGGGGG     EEEEEEEEEEEEEEEEEEEEEE     NNNNNNNN        NNNNNNNN     EEEEEEEEEEEEEEEEEEEEEE        SSSSSSSSSSSSSSS      IIIIIIIIII        SSSSSSSSSSSSSSS \n");
	printf("\t\t\t     GGG::::::::::::G     E::::::::::::::::::::E     N:::::::N       N::::::N     E::::::::::::::::::::E      SS:::::::::::::::S     I::::::::I      SS:::::::::::::::S\n");
	printf("\t\t\t   GG:::::::::::::::G     E::::::::::::::::::::E     N::::::::N      N::::::N     E::::::::::::::::::::E     S:::::SSSSSS::::::S     I::::::::I     S:::::SSSSSS::::::S\n");
	printf("\t\t\t  G:::::GGGGGGGG::::G     EE::::::EEEEEEEEE::::E     N:::::::::N     N::::::N     EE::::::EEEEEEEEE::::E     S:::::S     SSSSSSS     II::::::II     S:::::S     SSSSSSS\n");
	printf("\t\t\t G:::::G       GGGGGG       E:::::E       EEEEEE     N::::::::::N    N::::::N       E:::::E       EEEEEE     S:::::S                   I::::I       S:::::S            \n");
	printf("\t\t\tG:::::G                     E:::::E                  N:::::::::::N   N::::::N       E:::::E                  S:::::S                   I::::I       S:::::S            \n");
	printf("\t\t\tG:::::G                     E::::::EEEEEEEEEE        N:::::::N::::N  N::::::N       E::::::EEEEEEEEEE         S::::SSSS                I::::I        S::::SSSS         \n");
	printf("\t\t\tG:::::G    GGGGGGGGGG       E:::::::::::::::E        N::::::N N::::N N::::::N       E:::::::::::::::E          SS::::::SSSSS           I::::I         SS::::::SSSSS    \n");
	printf("\t\t\tG:::::G    G::::::::G       E:::::::::::::::E        N::::::N  N::::N:::::::N       E:::::::::::::::E            SSS::::::::SS         I::::I           SSS::::::::SS  \n");
	printf("\t\t\tG:::::G    GGGGG::::G       E::::::EEEEEEEEEE        N::::::N   N:::::::::::N       E::::::EEEEEEEEEE               SSSSSS::::S        I::::I              SSSSSS::::S \n");
	printf("\t\t\tG:::::G        G::::G       E:::::E                  N::::::N    N::::::::::N       E:::::E                              S:::::S       I::::I                   S:::::S\n");
	printf("\t\t\t G:::::G       G::::G       E:::::E       EEEEEE     N::::::N     N:::::::::N       E:::::E       EEEEEE                 S:::::S       I::::I                   S:::::S\n");
	printf("\t\t\t  G:::::GGGGGGGG::::G     EE::::::EEEEEEEE:::::E     N::::::N      N::::::::N     EE::::::EEEEEEEE:::::E     SSSSSSS     S:::::S     II::::::II     SSSSSSS     S:::::S\n");
	printf("\t\t\t   GG:::::::::::::::G     E::::::::::::::::::::E     N::::::N       N:::::::N     E::::::::::::::::::::E     S::::::SSSSSS:::::S     I::::::::I     S::::::SSSSSS:::::S\n");
	printf("\t\t\t     GGG::::::GGG:::G     E::::::::::::::::::::E     N::::::N        N::::::N     E::::::::::::::::::::E     S:::::::::::::::SS      I::::::::I     S:::::::::::::::SS \n");
	printf("\t\t\t        GGGGGG   GGGG     EEEEEEEEEEEEEEEEEEEEEE     NNNNNNNN         NNNNNNN     EEEEEEEEEEEEEEEEEEEEEE      SSSSSSSSSSSSSSS        IIIIIIIIII      SSSSSSSSSSSSSSS   \n");

	printf("\n\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n\n");

	printf("\t\t\t\t\t\t\t\t\t+---------------------------------------------------------------+\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!          |\n");
	printf("\t\t\t\t\t\t\t\t\t|         !!                                        !!          |\n");
	printf("\t\t\t\t\t\t\t\t\t|         !!   YOU HAVE ENTERED WORNG CREDENTIALS   !!          |\n");
	printf("\t\t\t\t\t\t\t\t\t|         !!                                        !!          |\n");
	printf("\t\t\t\t\t\t\t\t\t|         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!          |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t|                                                               |\n");
	printf("\t\t\t\t\t\t\t\t\t+---------------------------------------------------------------+\n");

	gotoxy(110,101);


}

/*-----------------------------------Homepage-----------------------------------*/
/*
	This Homepage shows the features provided to User.
*/
bool home()
{
	system("cls");

	/*--------------------------------------------------Printing required UI----------------------------------------------*/
	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n\n\n");

	printf("     (     \t  _____   _                 _                  _       _____            _            \n");
	printf("     \\    \t / ____| | |               | |                | |     |  __ \\          | |           \n");
	printf("      )    \t| (___   | |_   _   _    __| |   ___   _ __   | |_    | |  | |   __ _  | |_    __ _  \n");
	printf("##-------->\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |  | |  / _` | | __|  / _` | \n");
	printf("      )    \t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |__| | | (_| | | |_  | (_| | \n");
	printf("     /     \t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_____/   \\__,_|  \\__|  \\__,_| \n");
	printf("    (      \t\n");

	printf("\n\n");


	printf("     (     \t ______                              _                   _     _                     _____            _           \n");
	printf("     \\    \t|  ____|                            (_)                 | |   (_)                   |  __ \\          | |          \n");
	printf("      )    \t| |__    __  __   __ _   _ __ ___    _   _ __     __ _  | |_   _    ___    _ __     | |  | |   __ _  | |_    __ _ \n");
	printf("##-------->\t|  __|   \\ \\/ /  / _` | | '_ ` _ \\  | | | '_ \\   / _` | | __| | |  / _ \\  | '_ \\    | |  | |  / _` | | __|  / _` | \n");
	printf("      )    \t| |____   >  <  | (_| | | | | | | | | | | | | | | (_| | | |_  | | | (_) | | | | |   | |__| | | (_| | | |_  | (_| |\n");
	printf("     /     \t|______| /_/\\_\\  \\__,_| |_| |_| |_| |_| |_| |_|  \\__,_|  \\__| |_|  \\___/  |_| |_|   |_____/   \\__,_|  \\__|  \\__,_|\n");
	printf("    (     \n");

	printf("\n\n");


	printf("     (     \t            _     _                        _                                   _____                                     _  \n");
	printf("     \\    \t    /\\     | |   | |                      | |                                 |  __ \\                                   | | \n");
	printf("      )    \t   /  \\    | |_  | |_    ___   _ __     __| |   __ _   _ __     ___    ___    | |__) |   ___    ___    ___    _ __    __| | \n");
	printf("##-------->\t  / /\\ \\   | __| | __|  / _ \\ | '_ \\   / _` |  / _` | | '_ \\   / __|  / _ \\   |  _  /   / _ \\  / __|  / _ \\  | '__|  / _` | \n");
	printf("      )    \t / ____ \\  | |_  | |_  |  __/ | | | | | (_| | | (_| | | | | | | (__  |  __/   | | \\ \\  |  __/ | (__  | (_) | | |    | (_| | \n");
	printf("     /     \t/_/    \\_\\  \\__|  \\__|  \\___| |_| |_|  \\__,_|  \\__,_| |_| |_|  \\___|  \\___|   |_|  \\_\\  \\___|  \\___|  \\___/  |_|     \\__,_| \n");
	printf("    (     \n");

	printf("\n\n");


	printf("     (     \t __  __              _____          _                  _           _         \n");
	printf("     \\    \t|  \\/  |            / ____|        | |                | |         | |        \n");
	printf("      )    \t| \\  / |  _   _    | (___     ___  | |__     ___    __| |  _   _  | |   ___  \n");
	printf("##-------->\t| |\\/| | | | | |    \\___ \\   / __| | '_ \\   / _ \\  / _` | | | | | | |  / _ \\ \n");
	printf("      )    \t| |  | | | |_| |    ____) | | (__  | | | | |  __/ | (_| | | |_| | | | |  __/ \n");
	printf("     /     \t|_|  |_|  \\__, |   |_____/   \\___| |_| |_|  \\___|  \\__,_|  \\__,_| |_|  \\___| \n");
	printf("    (      \t           __/ |                                                             \n");
	printf("           \t          |___/                                                              \n");

	char ch;
	int option = 0;
	gotoxy(10, 19);

	/*-------------------------------------------Moving cursor according to wanted position----------------------------------------------*/ 
	while (ch = getch())
	{
		if (ch == '\t')
			option++;
		else if (ch == 13)
		{
			home_option = option;
			return true;
		}
		else if (ch == 27)
			return false;

		option %= 4;

		if (option == 0)
			gotoxy(10, 19);
		else if (option == 1)
			gotoxy(10, 28);
		else if (option == 2)
			gotoxy(10, 37);
		else if (option == 3)
			gotoxy(10, 46);
	}

	/*----------------------------Globally Options are stored for handeling the options that we are chosing-----------------------------*/

	return 0;

}

bool student_data()
{

	unhidecursor();
	system("cls");

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n\n\n");
	printf("    (      \t__      __  _                       _____                    __   _   _               \n");
	printf("     \\    \t\\ \\    / / (_)                     |  __ \\                  / _| (_) | |              \n");
	printf("      )    \t \\ \\  / /   _    ___  __      __   | |__) |  _ __    ___   | |_   _  | |   ___   ___  \n");
	printf("##-------->\t  \\ \\/ /   | |  / _ \\ \\ \\ /\\ / /   |  ___/  | '__|  / _ \\  |  _| | | | |  / _ \\ / __| \n");
	printf("      )    \t   \\  /    | | |  __/  \\ V  V /    | |      | |    | (_) | | |   | | | | |  __/ \\__ \\ \n");
	printf("     /     \t    \\/     |_|  \\___|   \\_/\\_/     |_|      |_|     \\___/  |_|   |_| |_|  \\___| |___/ \n");
	printf("    (      \t\n");

	printf("\n\n\n\n");


	printf("    (      \t                _       _      _____   _                 _                  _    \n");
	printf("     \\    \t    /\\         | |     | |    / ____| | |               | |                | |   \n");
	printf("      )    \t   /  \\      __| |   __| |   | (___   | |_   _   _    __| |   ___   _ __   | |_  \n");
	printf("##-------->\t  / /\\ \\    / _` |  / _` |    \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __| \n");
	printf("      )    \t / ____ \\  | (_| | | (_| |    ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_  \n");
	printf("     /     \t/_/    \\_\\  \\__,_|  \\__,_|   |_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__| \n");
	printf("    (      \t\n");

	printf("\n\n");

	student_data_option = 0;

	char ch;
	gotoxy(10, 19);

	while (ch = getch())
	{

		if (ch == 13)
			return true;
		else if (ch == 27)
			return false;
		else if (ch == '\t')
			student_data_option++;

		student_data_option %= 2;

		if (student_data_option == 0)
		{
			gotoxy(10, 19);
		}
		else if (student_data_option == 1)
		{
			gotoxy(10, 30);
		}

	}

}

bool add_student()
{

	system("cls");

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");

	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                     Student Details                      |\t\t\t\t\t\t\t\t|                     Gurdian Details                      | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     First Name  :                                        |\t\t\t\t\t\t\t\t|     First Name  :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Last Name   :                                        |\t\t\t\t\t\t\t\t|     Last Name   :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Roll No.    :                                        |\t\t\t\t\t\t\t\t|     Relation    :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Contact No. :                                        |\t\t\t\t\t\t\t\t|     Contact No. :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Temporary Address:                                   |\t\t\t\t\t\t\t\t|     Address:                                             | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Permanent Address:                                   |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                  Press Enter to Save                     | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");

	struct student {
		char sfname[21] = {0};
		char slname[21] = {0};
		char roll[21] = {0};
		char scontact[16] = {0};
		char stempadd[81] = {0};
		char spermadd[81] = {0};
		char gfname[21] = {0};
		char glname[21] = {0};
		char relation[31] = {0};
		char gcontact[16] = {0};
		char gadd[81] = {0};

	} current;

	char ch;

	gotoxy(36, 20);

	printf("%s", current.sfname);

	int sze = 0;
	/*---------------------------Getting FirstName of Student-----------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(36, 24);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.sfname[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) && sze < 20)
		{
			if (sze == 0)
			{
				if (ch >= 97 && ch <= 122)
					ch = ch - 32;
			}
			printf("%c", ch);
			current.sfname[sze] = ch;
			sze++;
		}
		else
			;
	}

	sze = 0;


	/*----------------------------------------Getting Last Name of Student----------------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(36, 28);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.slname[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) && sze < 20)
		{
			if (sze == 0)
			{
				if (ch >= 97 && ch <= 122)
					ch = ch - 32;
			}
			printf("%c", ch);
			current.slname[sze] = ch;
			sze++;
		}
		else
			;
	}

	sze = 0;

	/*------------------------------------------------Getting Roll Number of Student--------------------------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(36, 32);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.roll[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) && sze < 20)
		{
			printf("%c", ch);
			current.roll[sze] = ch;
			sze++;
		}
		else
			;
	}


	sze = 0;


	/*---------------------------------------------Getting Contact Number of Student---------------------------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(41, 37);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.scontact[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 48 && ch <= 57) || ch == 43 && sze < 15)
		{
			printf("%c", ch);
			current.scontact[sze] = ch;
			sze++;
		}
		else
			;
	}

	sze = 0;

	/*----------------------------------------------Getting Temporary Address of Student------------------------------------------*/
	int now_at = 37;
	bool once = true;
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (sze != 0 && sze % 30 == 0 && once)
		{
			gotoxy(22, now_at + 1);
			once = false;
		}

		if (ch == 10 || ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(41, 43);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.stempadd[sze - 1] = '\0';
			sze--;
		}
		else if (sze < 79 && ch != '\b')
		{
			printf("%c", ch);
			current.stempadd[sze] = ch;
			sze++;
		}
	}

	sze = 0;

	/*----------------------------------------------Getting Permanent Address of Student------------------------------------------*/
	now_at = 43;
	once = true;
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (sze != 0 && sze % 30 == 0 && once)
		{
			gotoxy(22, now_at + 1);
			once = false;
		}

		if (ch == 10 || ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(156, 20);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.spermadd[sze - 1] = '\0';
			sze--;
		}
		else if (sze < 79 && ch != '\b')
		{
			printf("%c", ch);
			current.spermadd[sze] = ch;
			sze++;
		}
	}

	sze = 0;

	/*--------------------------------------------Getting FirstName of Gurdian--------------------------------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 10 || ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(156, 24);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.gfname[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) && sze < 20)
		{
			if (sze == 0)
			{
				if (ch >= 97 && ch <= 122)
					ch = ch - 32;
			}
			printf("%c", ch);
			current.gfname[sze] = ch;
			sze++;
		}
		else
			;
	}

	sze = 0;

	/*---------------------------------------------Getting Last Name of Gurdian-------------------------------------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 10 || ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(156, 28);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.glname[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) && sze < 20)
		{
			if (sze == 0)
			{
				if (ch >= 97 && ch <= 122)
					ch = ch - 32;
			}
			printf("%c", ch);
			current.glname[sze] = ch;
			sze++;
		}
		else
			;
	}

	sze = 0;

	/*---------------------------------------------------Getting Relation----------------------------------------------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 10 || ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(156, 32);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.relation[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) && sze < 30)
		{
			if (sze == 0)
			{
				if (ch >= 97 && ch <= 122)
					ch = ch - 32;
			}
			printf("%c", ch);
			current.relation[sze] = ch;
			sze++;
		}
		else
			;
	}

	sze = 0;

	/*-------------------------------------------------Getting Contact Number of Gurdian---------------------------------------------------*/
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(151, 37);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.gcontact[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 48 && ch <= 57) && sze < 15)
		{
			printf("%c", ch);
			current.gcontact[sze] = ch;
			sze++;
		}
		else
			;
	}

	sze = 0;

	/*-----------------------------------------------Getting Address of Gurdian-------------------------------------------------------------*/
	now_at = 37;
	once = true;
	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (sze != 0 && sze % 41 == 0 && once)
		{
			gotoxy(142, now_at + 1);
			once = false;
		}

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			gotoxy(151, 39);
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			current.gadd[sze - 1] = '\0';
			sze--;
		}
		else if (ch != '\b' && sze < 79)
		{
			printf("%c", ch);
			current.gadd[sze] = ch;
			sze++;
		}
		else
			;
	}

	printf("%s\n", current.sfname);
	FILE *fptr;

	char path[100] = "C:/Student_Management_System/Database/Students/";
	strcat(path, current.roll);
	strcat(path, ".bat");

	printf("%s\n", current.sfname);

	char self_explode[100] = "@echo off\ndel \"C:\\Student_Management_System\\Database\\Students\\";
	strcat(self_explode, current.roll);
	strcat(self_explode, ".bat\"\n");
	printf("%s\n", current.sfname);

	fptr = fopen(path, "w");

	/*---------------------------------Saving in the file-------------------------------------------------*/

	fputs(self_explode, fptr);
	fputs(current.sfname, fptr);
	fputs("\n", fptr);
	fputs(current.slname, fptr);
	fputs("\n", fptr);
	fputs(current.roll, fptr);
	fputs("\n", fptr);
	fputs(current.scontact, fptr);
	fputs("\n", fptr);
	fputs(current.stempadd, fptr);
	fputs("\n", fptr);
	fputs(current.spermadd, fptr);
	fputs("\n", fptr);
	fputs(current.gfname, fptr);
	fputs("\n", fptr);
	fputs(current.glname, fptr);
	fputs("\n", fptr);
	fputs(current.relation, fptr);
	fputs("\n", fptr);
	fputs(current.gcontact, fptr);
	fputs("\n", fptr);
	fputs(current.gadd, fptr);

	fclose(fptr);

	return false;
}


/*------------------------------------------------Teachers Schedule ------------------------------------------------------*/
bool my_schedule()
{
	system("cls");

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");


	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------------------------+ \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t|                                                            Notepad                                                                       |                    Your Schedule                    | \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------------------------+ \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t|     +-----------------------------------------------------------------------------------------------------------------------------+      |             +----------------------------+          | \n");
	printf("\t|     |                                                                                                                             |      |             |                            |          | \n");
	printf("\t|     |                                                                                                                             |      |             |      Today's Schedule      |          | \n");
	printf("\t|     |                                                                                                                             |      |             |                            |          | \n");
	printf("\t|     |                                                                                                                             |      |             +----------------------------+          | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |         +------------------------------------+      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |          Goto Custom Date          |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |    Day      :                      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |    Month    :                      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |    Year     :                      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |      Press Enter to Goto Date      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         +------------------------------------+      | \n");
	printf("\t|     +-----------------------------------------------------------------------------------------------------------------------------+      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     |                                 Press Enter in Notepad to Save the Schedule for the Date                                    |      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     +-----------------------------------------------------------------------------------------------------------------------------+      |                                                     | \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------------------------+ \n");

	/*-------------------------------Configuration of Date--------------------------------*/
	struct _date {
		int day;
		int month;
		int year;
	} date;

	date.day = day;
	date.month = month;
	date.year = year;

	int option = 0;
	char ch;
	int sze = 0;
	char data[2501] = {0};

	/*--------------------------------Storing date in string-----------------------------*/
	FILE *fptr;
	char path[100] = "C:/Student_Management_System/Database/Schedule/";
	char d[3] = {0};
	char m[3] = {0};
	char y[5] = {0};
	itoa(date.day, d, 10);
	itoa(date.month, m, 10);
	itoa(date.year, y, 10);

	/*----------------------------Making date more neat---------------------------------*/
	if (date.day < 10)
		strcat(path, "0");
	strcat(path, d);
	if (date.month < 10)
		strcat(path, "0");
	strcat(path, m);
	strcat(path, y);
	strcat(path, ".bat");

	fptr = fopen(path, "");

	/*----------------------------------Creating self explode for bat file-------------------------------------*/
	/*
		Self explode for bat can be also created using del %0 but we used the path of the file instead if %0
		no problem both works.
	*/ 
	char self_explode[100] = "@echo off\ndel \"C:\\Student_Management_System\\Database\\Schedule\\";
	if (date.day < 10)
		strcat(self_explode, "0");
	strcat(self_explode, d);
	if (date.month < 10)
		strcat(self_explode, "0");
	strcat(self_explode, m);
	strcat(self_explode, y);
	strcat(self_explode, ".bat\"\n");

	if (fptr == NULL)
		fputs(self_explode, fptr);

	fclose(fptr);

	/*
		Capturing the data and saving it instantly as we click enter.
	*/

	while (1)
	{
		gotoxy(68, 19);
		printf("%02d/%02d/%04d", date.day, date.month, date.year);
		option %= 3;

		if (option == 0)
		{
			clear_note();
			gotoxy(20, 22);

			FILE *fptr;
			char path[100] = "C:/Student_Management_System/Database/Schedule/";
			char d[3] = {0};
			char m[3] = {0};
			char y[5] = {0};
			itoa(date.day, d, 10);
			itoa(date.month, m, 10);
			itoa(date.year, y, 10);

			if (date.day < 10)
				strcat(path, "0");
			strcat(path, d);
			if (date.month < 10)
				strcat(path, "0");
			strcat(path, m);
			strcat(path, y);
			strcat(path, ".bat");

			fptr = fopen(path, "r+");

			char line[2501] = {0};

			int i = 0;
			while (fgets(line, sizeof(line), fptr)) {
				i++;
				if (i == 3 )
				{
					break;
				}
			}

			strcpy(data, line);

			sze = strlen(line);

			fclose(fptr);

			int n = strlen(data);

			int now = 22;

			for (int j = 0; j < n; j++)
			{
				if (j != 0 && j % 115 == 0)
				{
					gotoxy(20, now + 1);
					now++;
				}
				printf("%c", data[j]);
			}

			while (ch = getch())
			{
				if (sze != 0 && sze % 115 == 0)
				{
					gotoxy(20, now + 1);
					now++;
				}

				if (ch == 27)
					return false;

				if (ch == 13)
				{
					fptr = fopen(path, "w");
					fputs(self_explode, fptr);
					fputs(data, fptr);
					fclose(fptr);
					break;
				}
				else if (ch == '\t')
				{
					option++;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					data[sze - 1] = '\0';
					sze--;
				}
				else if (ch != '\b')
				{
					printf("%c", ch);
					data[sze] = ch;
					sze++;
				}

			}

		}
		else if (option == 1)
		{
			gotoxy(177, 23);
			while (ch = getch())
			{
				if (ch == 27)
					return false;
				if (ch == 13)
				{
					date.day = day;
					date.month = month;
					date.year = year;
					option = 0;
					break;
				}
				else if (ch == '\t')
				{
					option++;
					break;
				}
			}
		}
		else if (option == 2)
		{
			gotoxy(177, 32);
			char d[3] = {0};
			char m[3] = {0};
			char y[5] = {0};
			bool completed = true;

			sze = 0;
			while (ch = getch())
			{
				if (ch == 27)
					return false;

				if (ch == 13)
					break;
				else if (ch == '\t')
				{
					gotoxy(179, 32);
					printf("\b\b  ");
					option++;
					completed = false;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					d[sze - 1] = '\0';
					sze--;
				}
				else if (ch >= 48 && ch <= 57 && sze < 2)
				{
					printf("%c", ch);
					d[sze] = ch;
					sze++;
				}

			}

			if (!completed)
			{
				continue;
			}

			gotoxy(177, 35);
			sze = 0;
			while (ch = getch())
			{
				if (ch == 27)
					return false;

				if (ch == 13)
					break;
				else if (ch == '\t')
				{
					gotoxy(179, 32);
					printf("\b\b  ");

					gotoxy(179, 35);
					printf("\b\b  ");
					option++;
					completed = false;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					m[sze - 1] = '\0';
					sze--;
				}
				else if (ch >= 48 && ch <= 57 && sze < 2)
				{
					printf("%c", ch);
					m[sze] = ch;
					sze++;
				}

			}

			if (!completed)
			{
				continue;
			}

			gotoxy(177, 38);
			sze = 0;
			while (ch = getch())
			{
				if (ch == 27)
					return false;
				if (ch == 13)
				{
					gotoxy(179, 32);
					printf("\b\b  ");

					gotoxy(179, 35);
					printf("\b\b  ");

					gotoxy(181, 38);
					printf("\b\b\b\b    ");
					break;
				}
				else if (ch == '\t')
				{
					gotoxy(179, 32);
					printf("\b\b  ");

					gotoxy(179, 35);
					printf("\b\b  ");

					gotoxy(181, 38);
					printf("\b\b\b\b    ");
					option++;
					completed = false;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					y[sze - 1] = '\0';
					sze--;
				}
				else if (ch >= 48 && ch <= 57 && sze < 4)
				{
					printf("%c", ch);
					y[sze] = ch;
					sze++;
				}
			}

			if (!completed)
				continue;

			char path[100] = "C:/Student_Management_System/Database/Schedule/";

			if (strlen(d) == 1)
			{
				d[1] = d[0];
				d[0] = '0';
			}

			if (strlen(m) == 1)
			{
				m[1] = m[0];
				m[0] = '0';
			}

			if (strlen(y) == 2)
			{
				y[3] = y[1];
				y[2] = y[0];
				y[0] = '2';
				y[1] = '0';
			}

			strcat(path, d);
			strcat(path, m);
			strcat(path, y);
			strcat(path, ".bat");

			FILE *fptr;
			fptr = fopen(path, "r+");

			if (fptr != NULL)
			{
				clear_note();
				option = 0;
				date.day = atoi(d);
				date.month = atoi(m);
				date.year = atoi(y);
			}
			else
			{
				clear_note();
				note_not_found();
				option = 1;
			}

		}

	}

}

/*--------------------------------Helper Function for printing note---------------------------------*/
bool print_note(char *path)
{
	FILE *fptr;

	fptr = fopen(path, "r");
	char ch;

	gotoxy(68, 19);
	int now = 19;

	int i = 0;

	while ((ch = getc(fptr)) != EOF)
	{
		if (i % 115 != 0 && i != 0)
		{
			gotoxy(68, now + 1);
			now++;
		}
		printf("%c", ch);
	}
}

/*-----------------------------------Helper Function for clearing note---------------------------------*/
bool clear_note()
{
	gotoxy(135, 22);
	int this_row = 22;

	for (int i = 0; i < 23; i++)
	{
		gotoxy(135, 22 + i);
		for (int j = 0; j < 115; j++)
		{
			printf("\b \b");
		}
	}
}

/*-----------------------------------Showing the user that file doesnt exist--------------------------*/
bool note_not_found()
{
	gotoxy(65, 33);
	printf("    Data Not Found!!!");
	gotoxy(62, 34);
	printf("   Going to Today's Data...");
	Sleep(3000);
	clear_note();
}

/*-------------------------------Viewig Profile of all users--------------------------------------*/

bool view_profile(int from)
{
	int f_no = from;

	
start_again:
	system("cls");
	unhidecursor();

	from = f_no;

	int total = 0;

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");

	printf("\n                                                                                                    Student List\n\n\n");

	char path[100] = "C:/Student_Management_System/Database/Students/";
	bool can_go_forward = false;

	struct dirent *dp;
	DIR *dir = opendir(path);

	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			from--;
			char f_path[100];
			strcpy(f_path, path);
			strcat(f_path, dp->d_name);
			if (from < 0 && from > -7)
			{
				print_safe(f_path);
			}
			else if (from <= -7)
			{
				can_go_forward = true;
			}
			total++;
		}
	}

	closedir(dir);

	if(total==0)
		return empty_profiles();

	char ch;
	int option = 0;

	int MOD = total < 6 ? total : 6;

	gotoxy(148, 20);

	while (ch = getch())
	{
		if (ch == '\t')
		{
			if (view_profile_from + (option % MOD) < total)
				option++;
		}
		else if (ch == 13)
		{
			if (!individual_profile(f_no + option + 1));
			goto start_again;
		}
		else if (ch == 27)
		{
			return false;
		}
		else if (ch == 72 || ch == 75)
		{
			view_profile_from -= 6;
			if (view_profile_from < 0)
				view_profile_from = 0;
			else
				return true;
		}
		else if (ch == 80 || ch == 77 && can_go_forward)
		{
			if(view_profile_from+6<total)
			{
				view_profile_from += 6;
				return true;
			}
		}

		option %= MOD;

		if (option == 0 && view_profile_from + option < total)
			gotoxy(148, 20);
		else if (option == 1 && view_profile_from + option < total)
			gotoxy(148, 25);
		else if (option == 2 && view_profile_from + option < total)
			gotoxy(148, 30);
		else if (option == 3 && view_profile_from + option < total)
			gotoxy(148, 35);
		else if (option == 4 && view_profile_from + option < total)
			gotoxy(148, 40);
		else if (option == 5 && view_profile_from + option < total)
			gotoxy(148, 45);
	}

}

/*--------------------------------Printing safely the Profiles of Students----------------------------------------*/

bool print_safe(char *path)
{
	char r_no[256] = {0};
	char name[256] = {0};

	FILE *fptr;
	fptr = fopen(path, "r");

	char line[256];
	int i = 0;
	while (fgets(line, sizeof(line), fptr)) {
		i++;
		if (i == 3)
		{
			strcpy(name, line);
			name[strlen(name) - 1] = ' ';
		}
		else if (i == 4)
		{
			strcat(name, line);
			name[strlen(name) - 1] = '\0';
		}
		else if (i == 5)
		{
			strcpy(r_no, line);
			r_no[strlen(r_no) - 1] = '\0';
		}
	}
	fclose(fptr);

	int roll = strlen(r_no);

	printf("\t\t\t\t\t\t+----------------+------------------------------------------------------------------+-----------------------------+ \n");
	printf("\t\t\t\t\t\t|                |                                                                  |                             | \n");
	printf("\t\t\t\t\t\t| ");
	roll -= 2;

	printf("%s", r_no);


	printf("              ");

	while (roll >= 0)
	{
		printf("\b");
		roll--;
	}

	printf("|                        ");

	printf("%s", name);

	printf("                                        ");

	int l = strlen(name);
	l -= 2;

	while (l > 0)
	{
		printf("\b");
		l--;
	}

	printf("|         VIEW RECORD         | \n");
	printf("\t\t\t\t\t\t|                |                                                                  |                             | \n");
	printf("\t\t\t\t\t\t+----------------+------------------------------------------------------------------+-----------------------------+ \n");

}


/*------------------------------------Printing Safely the Exam(Used in view_exams function)--------------------------------*/
bool print_safe_exam(char *path, char *name)
{
	char r_no[256] = {0};

	FILE *fptr;
	fptr = fopen(path, "r");

	char line[256];
	int i = 0;
	while (fgets(line, sizeof(line), fptr)) {
		i++;
		if (i == 5)
		{
			strcpy(r_no, line);
			r_no[strlen(r_no) - 1] = '\0';
			break;
		}
	}
	fclose(fptr);

	int roll = strlen(r_no);

	printf("\t\t\t\t\t\t+----------------+------------------------------------------------------------------+-----------------------------+ \n");
	printf("\t\t\t\t\t\t|                |                                                                  |                             | \n");
	printf("\t\t\t\t\t\t| ");
	roll -= 2;

	printf("%s", r_no);


	printf("              ");

	while (roll >= 0)
	{
		printf("\b");
		roll--;
	}

	printf("|                        ");

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '.' && name[i + 1] == 'b')
			break;
		printf("%c", name[i]);
		i++;
	}
	printf("    ");

	printf("                                        ");

	int l = strlen(name);
	l -= 2;

	while (l > 0)
	{
		printf("\b");
		l--;
	}

	printf("|         VIEW RECORD         | \n");
	printf("\t\t\t\t\t\t|                |                                                                  |                             | \n");
	printf("\t\t\t\t\t\t+----------------+------------------------------------------------------------------+-----------------------------+ \n");

}


bool attendance_record()
{
	system("cls");
	/*--------------------------Headings---------------------------*/
	/*
		This function is same as My Schedule for more customised use for user.
	*/
	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");


	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------------------------+ \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t|                                                            Attendance Record                                                             |                    Jump to Date                     | \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------------------------+ \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t|     +-----------------------------------------------------------------------------------------------------------------------------+      |             +----------------------------+          | \n");
	printf("\t|     |                                                                                                                             |      |             |                            |          | \n");
	printf("\t|     |                                                                                                                             |      |             |     Today's Attendance     |          | \n");
	printf("\t|     |                                                                                                                             |      |             |                            |          | \n");
	printf("\t|     |                                                                                                                             |      |             +----------------------------+          | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |         +------------------------------------+      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |          Goto Custom Date          |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |    Day      :                      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |    Month    :                      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |    Year     :                      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |      Press Enter to Goto Date      |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         |                                    |      | \n");
	printf("\t|     |                                                                                                                             |      |         +------------------------------------+      | \n");
	printf("\t|     +-----------------------------------------------------------------------------------------------------------------------------+      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     |                                 Press Enter in Notepad to Save the Attendance for the Date                                  |      |                                                     | \n");
	printf("\t|     |                                                                                                                             |      |                                                     | \n");
	printf("\t|     +-----------------------------------------------------------------------------------------------------------------------------+      |                                                     | \n");
	printf("\t|                                                                                                                                          |                                                     | \n");
	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------------------------+ \n");

	/*-------------------------------Configuration of Date--------------------------------*/
	struct _date {
		int day;
		int month;
		int year;
	} date;

	date.day = day;
	date.month = month;
	date.year = year;

	int option = 0;
	char ch;
	int sze = 0;
	char data[2501] = {0};

	FILE *fptr;
	char path[100] = "C:/Student_Management_System/Database/Attendance/";
	char d[3] = {0};
	char m[3] = {0};
	char y[5] = {0};
	itoa(date.day, d, 10);
	itoa(date.month, m, 10);
	itoa(date.year, y, 10);

	if (date.day < 10)
		strcat(path, "0");
	strcat(path, d);
	if (date.month < 10)
		strcat(path, "0");
	strcat(path, m);
	strcat(path, y);
	strcat(path, ".bat");

	fptr = fopen(path, "");

	char self_explode[100] = "@echo off\ndel \"C:\\Student_Management_System\\Database\\Attendance\\";
	if (date.day < 10)
		strcat(self_explode, "0");
	strcat(self_explode, d);
	if (date.month < 10)
		strcat(self_explode, "0");
	strcat(self_explode, m);
	strcat(self_explode, y);
	strcat(self_explode, ".bat\"\n");

	if (fptr == NULL)
		fputs(self_explode, fptr);

	fclose(fptr);

	while (1)
	{
		gotoxy(68, 19);
		printf("%02d/%02d/%04d", date.day, date.month, date.year);
		option %= 3;

		if (option == 0)
		{
			clear_note();
			gotoxy(20, 22);

			FILE *fptr;
			char path[100] = "C:/Student_Management_System/Database/Attendance/";
			char d[3] = {0};
			char m[3] = {0};
			char y[5] = {0};
			itoa(date.day, d, 10);
			itoa(date.month, m, 10);
			itoa(date.year, y, 10);

			if (date.day < 10)
				strcat(path, "0");
			strcat(path, d);
			if (date.month < 10)
				strcat(path, "0");
			strcat(path, m);
			strcat(path, y);
			strcat(path, ".bat");

			fptr = fopen(path, "r+");

			char line[2501] = {0};

			int i = 0;
			while (fgets(line, sizeof(line), fptr)) {
				i++;
				if (i == 3 )
				{
					break;
				}
			}

			strcpy(data, line);

			sze = strlen(line);

			fclose(fptr);

			int n = strlen(data);

			int now = 22;

			for (int j = 0; j < n; j++)
			{
				if (j != 0 && j % 115 == 0)
				{
					gotoxy(20, now + 1);
					now++;
				}
				printf("%c", data[j]);
			}

			while (ch = getch())
			{
				if (sze != 0 && sze % 115 == 0)
				{
					gotoxy(20, now + 1);
					now++;
				}

				if (ch == 27)
					return false;

				if (ch == 13)
				{
					fptr = fopen(path, "w");
					fputs(self_explode, fptr);
					fputs(data, fptr);
					fclose(fptr);
					break;
				}
				else if (ch == '\t')
				{
					option++;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					data[sze - 1] = '\0';
					sze--;
				}
				else if (ch != '\b')
				{
					printf("%c", ch);
					data[sze] = ch;
					sze++;
				}

			}

		}
		else if (option == 1)
		{
			gotoxy(177, 23);
			while (ch = getch())
			{
				if (ch == 27)
					return false;
				if (ch == 13)
				{
					date.day = day;
					date.month = month;
					date.year = year;
					option = 0;
					break;
				}
				else if (ch == '\t')
				{
					option++;
					break;
				}
			}
		}
		else if (option == 2)
		{
			gotoxy(177, 32);
			char d[3] = {0};
			char m[3] = {0};
			char y[5] = {0};
			bool completed = true;

			sze = 0;
			while (ch = getch())
			{
				if (ch == 27)
					return false;

				if (ch == 13)
					break;
				else if (ch == '\t')
				{
					gotoxy(179, 32);
					printf("\b\b  ");
					option++;
					completed = false;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					d[sze - 1] = '\0';
					sze--;
				}
				else if (ch >= 48 && ch <= 57 && sze < 2)
				{
					printf("%c", ch);
					d[sze] = ch;
					sze++;
				}

			}

			if (!completed)
			{
				continue;
			}

			gotoxy(177, 35);
			sze = 0;
			while (ch = getch())
			{
				if (ch == 27)
					return false;

				if (ch == 13)
					break;
				else if (ch == '\t')
				{
					gotoxy(179, 32);
					printf("\b\b  ");

					gotoxy(179, 35);
					printf("\b\b  ");
					option++;
					completed = false;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					m[sze - 1] = '\0';
					sze--;
				}
				else if (ch >= 48 && ch <= 57 && sze < 2)
				{
					printf("%c", ch);
					m[sze] = ch;
					sze++;
				}

			}

			if (!completed)
			{
				continue;
			}

			gotoxy(177, 38);
			sze = 0;
			while (ch = getch())
			{
				if (ch == 27)
					return false;
				if (ch == 13)
				{
					gotoxy(179, 32);
					printf("\b\b  ");

					gotoxy(179, 35);
					printf("\b\b  ");

					gotoxy(181, 38);
					printf("\b\b\b\b    ");
					break;
				}
				else if (ch == '\t')
				{
					gotoxy(179, 32);
					printf("\b\b  ");

					gotoxy(179, 35);
					printf("\b\b  ");

					gotoxy(181, 38);
					printf("\b\b\b\b    ");
					option++;
					completed = false;
					break;
				}
				else if (ch == '\b' && sze != 0)
				{
					printf("\b \b");
					y[sze - 1] = '\0';
					sze--;
				}
				else if (ch >= 48 && ch <= 57 && sze < 4)
				{
					printf("%c", ch);
					y[sze] = ch;
					sze++;
				}
			}

			if (!completed)
				continue;

			char path[100] = "C:/Student_Management_System/Database/Attendance/";

			if (strlen(d) == 1)
			{
				d[1] = d[0];
				d[0] = '0';
			}

			if (strlen(m) == 1)
			{
				m[1] = m[0];
				m[0] = '0';
			}

			if (strlen(y) == 2)
			{
				y[3] = y[1];
				y[2] = y[0];
				y[0] = '2';
				y[1] = '0';
			}

			strcat(path, d);
			strcat(path, m);
			strcat(path, y);
			strcat(path, ".bat");

			FILE *fptr;
			fptr = fopen(path, "r+");

			if (fptr != NULL)
			{
				clear_note();
				option = 0;
				date.day = atoi(d);
				date.month = atoi(m);
				date.year = atoi(y);
			}
			else
			{
				clear_note();
				note_not_found();
				option = 1;
			}

		}

	}

}

bool individual_profile(int f_no)
{
	system("cls");
	hidecursor();

	/*---------------------------------------------------------------Viewing the Student's Details------------------------------------------------------------*/
	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");

	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                     Student Details                      |\t\t\t\t\t\t\t\t|                     Gurdian Details                      | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     First Name  :                                        |\t\t\t\t\t\t\t\t|     First Name  :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Last Name   :                                        |\t\t\t\t\t\t\t\t|     Last Name   :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Roll No.    :                                        |\t\t\t\t\t\t\t\t|     Relation    :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Contact No. :                                        |\t\t\t\t\t\t\t\t|     Contact No. :                                        | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Temporary Address:                                   |\t\t\t\t\t\t\t\t|     Address:                                             | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Permanent Address:                                   |\t\t\t\t\t\t\t\t|   You can Make changes in this form by creating student  | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|     of this roll number and updating all the details.    | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");

	/*------------------------------------Displaying in the fields----------------------------------------*/

	char path[100] = "C:/Student_Management_System/Database/Students/";
	char name[21] = {0};


	struct dirent *dp;
	DIR *dir = opendir(path);

	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			f_no--;

			if (f_no <= 0)
			{
				strcpy(name, dp->d_name);
				break;
			}
		}
	}
	closedir(dir);

	strcat(path, name);

	FILE *fptr;

	fptr = fopen(path, "r");

	if (fptr != NULL)
	{

		char line[256];
		int i = 0;
		while (fgets(line, sizeof(line), fptr))
		{
			i++;

			if (i == 3 )
			{
				gotoxy(36, 20);
				printf("%s", line);
			}
			else if (i == 4)
			{
				gotoxy(36, 24);
				printf("%s", line);
			}
			else if (i == 5)
			{
				gotoxy(36, 28);
				printf("%s", line);
			}
			else if (i == 6)
			{
				gotoxy(36, 32);
				printf("%s", line);
			}
			else if (i == 7)
			{
				gotoxy(41, 37);
				int now_at = 37;
				int sze = 0;
				bool once = true;

				while (line[sze] != '\0')
				{
					if (sze != 0 && sze % 30 == 0 && once)
					{
						gotoxy(22, now_at + 1);
						once = false;
					}

					printf("%c", line[sze]);
					sze++;
				}
			}
			else if (i == 8)
			{
				gotoxy(41, 43);
				int now_at = 43;
				int sze = 0;
				bool once = true;

				while (line[sze] != '\0')
				{
					if (sze != 0 && sze % 30 == 0 && once)
					{
						gotoxy(22, now_at + 1);
						once = false;
					}

					printf("%c", line[sze]);
					sze++;
				}
			}
			else if (i == 9)
			{
				gotoxy(156, 20);
				printf("%s", line);
			}
			else if (i == 10)
			{
				gotoxy(156, 24);
				printf("%s", line);
			}
			else if (i == 11)
			{
				gotoxy(156, 28);
				printf("%s", line);
			}
			else if (i == 12)
			{
				gotoxy(156, 32);
				printf("%s", line);
			}
			else if (i == 13)
			{
				gotoxy(151, 37);

				int now_at = 37;
				int sze = 0;
				bool once = true;

				while (line[sze] != '\0')
				{
					if (sze != 0 && sze % 41 == 0 && once)
					{
						gotoxy(142, now_at + 1);
						once = false;
					}
					printf("%c", line[sze]);
					sze++;
				}
			}
			else if (i == 14)
				break;
		}
	}

	fclose(fptr);

	char ch;

	while (ch = getch())
	{
		if (ch == 27)
			return false;
	}
}

bool exam_record()
{
	system("cls");
	/*------------------------------Heading-----------------------------------------*/
	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n\n\n");

	printf("     (     \t__      __  _                       ______                                   \n");
	printf("     \\    \t\\ \\    / / (_)                     |  ____|                                  \n");
	printf("      )    \t \\ \\  / /   _    ___  __      __   | |__    __  __   __ _   _ __ ___    ___  \n");
	printf("##-------->\t  \\ \\/ /   | |  / _ \\ \\ \\ /\\ / /   |  __|   \\ \\/ /  / _` | | '_ ` _ \\  / __| \n");
	printf("      )    \t   \\  /    | | |  __/  \\ V  V /    | |____   >  <  | (_| | | | | | | | \\__ \\ \n");
	printf("     /     \t    \\/     |_|  \\___|   \\_/\\_/     |______| /_/\\_\\  \\__,_| |_| |_| |_| |___/ \n");
	printf("    (      \t");

	printf("\n\n\n\n");

	printf("     (     \t                _       _     ______                             \n");
	printf("     \\    \t    /\\         | |     | |   |  ____|                            \n");
	printf("      )    \t   /  \\      __| |   __| |   | |__    __  __   __ _   _ __ ___   \n");
	printf("##-------->\t  / /\\ \\    / _` |  / _` |   |  __|   \\ \\/ /  / _` | | '_ ` _ \\  \n");
	printf("      )    \t / ____ \\  | (_| | | (_| |   | |____   >  <  | (_| | | | | | | | \n");
	printf("     /     \t/_/    \\_\\  \\__,_|  \\__,_|   |______| /_/\\_\\  \\__,_| |_| |_| |_| \n");
	printf("    (      \t");


	exam_record_option = 0;
	gotoxy(10, 19);

	/*----------------------------------For handeling option to choose-------------------------------------*/

	char ch;

	while (ch = getch())
	{
		if (ch == '\t')
			exam_record_option++;
		else if (ch == 13)
			return true;
		else if (ch == 27)
			return false;

		exam_record_option %= 2;

		if (exam_record_option == 0)
			gotoxy(10, 19);
		else if (exam_record_option == 1)
			gotoxy(10, 29);
	}

}

bool view_exams(int from)
{
	int f_no = from;
	
	/*
		Viewing the Exams Occured.
	*/

start_again:
	system("cls");
	unhidecursor();

	from = f_no;

	int total = 0;

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");

	printf("\n                                                                                                    Exam List\n\n\n");

	char path[100] = "C:/Student_Management_System/Database/Exams/";
	bool can_go_forward = false;

	struct dirent *dp;
	DIR *dir = opendir(path);

	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			from--;
			char f_path[100];
			strcpy(f_path, path);
			strcat(f_path, dp->d_name);
			if (from < 0 && from > -7)
			{
				print_safe_exam(f_path, dp->d_name);
			}
			else if (from <= -7)
			{
				can_go_forward = true;
			}
			total++;
		}
	}


	closedir(dir);

	if(total==0)
		return empty_exams();

	char ch;
	int option = 0;

	int MOD = total < 6 ? total : 6;

	gotoxy(148, 20);

	while (ch = getch())
	{
		if (ch == '\t')
		{
			if (view_exams_from + (option % MOD) < total)
				option++;
		}
		else if (ch == 13)
		{
			if (!individual_exam(f_no + option + 1));
			goto start_again;
		}
		else if (ch == 27)
		{
			return false;
		}
		else if (ch == 72 || ch == 75)
		{
			view_exams_from -= 6;
			if (view_exams_from < 0)
				view_exams_from = 0;
			else
				return true;
		}
		else if (ch == 80 || ch == 77 && can_go_forward)
		{
			view_exams_from += 6;
			return true;
		}

		option %= MOD;

		if (option == 0 && view_exams_from + option < total)
			gotoxy(148, 20);
		else if (option == 1 && view_exams_from + option < total)
			gotoxy(148, 25);
		else if (option == 2 && view_exams_from + option < total)
			gotoxy(148, 30);
		else if (option == 3 && view_exams_from + option < total)
			gotoxy(148, 35);
		else if (option == 4 && view_exams_from + option < total)
			gotoxy(148, 40);
		else if (option == 5 && view_exams_from + option < total)
			gotoxy(148, 45);
	}

}

bool add_exam()
{
	system("cls");

	/*
		For adding exams

	*/

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");

	printf("\t+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------------------------------+ \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|                              Examination Details                                   |                                               Individual Marks                                            | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t+------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------+ \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Name of Exam   :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Time (in mins) :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Supervisor     :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Mode           :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Total Marks    :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------------------------------+ \n");

	int sze = 0;
	char ch;

	struct _exam {
		char name[31] = {0};
		char time[5] = {0};
		char sup[31] = {0};
		char mode[31] = {0};
		char total[5] = {0};
	} exam;

	/*----------------------------------------------Getting Name of Exam------------------------------------------*/
	gotoxy(37, 22);
	sze = 0;

	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			exam.name[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || ch == 32 || ch == 46 || (ch >= 97 && ch <= 122) && sze < 30)
		{
			printf("%c", ch);
			exam.name[sze] = ch;
			sze++;
		}
		else
			;
	}

	/*------------------------------------------Getting Time of Exam----------------------------------------------*/
	gotoxy(37, 28);
	sze = 0;

	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			exam.time[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 48 && ch <= 57) || ch == 45 && sze < 5)
		{
			printf("%c", ch);
			exam.time[sze] = ch;
			sze++;
		}
		else
			;
	}

	/*----------------------------------------Getting Supervisor-------------------------------------*/
	gotoxy(37, 34);
	sze = 0;

	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			exam.sup[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || ch == 32 || ch == 46 && sze < 30)
		{
			printf("%c", ch);
			exam.sup[sze] = ch;
			sze++;
		}
		else
			;
	}

	/*-----------------------------------Getting Mode of Exam--------------------------------------------*/
	gotoxy(37, 40);
	sze = 0;

	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			exam.mode[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) && sze < 30)
		{
			printf("%c", ch);
			exam.mode[sze] = ch;
			sze++;
		}
		else
			;
	}

	/*-----------------------------------Getting Total Marks----------------------------------------*/
	gotoxy(37, 46);
	sze = 0;

	while (ch = getch())
	{
		if (ch == 27)
			return false;

		if (ch == 13 || ch == '\t')
		{
			if (sze == 0)
				continue;
			break;
		}
		else if (ch == '\b' && sze != 0)
		{
			printf("\b \b");
			exam.total[sze - 1] = '\0';
			sze--;
		}
		else if ((ch >= 48 && ch <= 57) && sze < 5)
		{
			printf("%c", ch);
			exam.total[sze] = ch;
			sze++;
		}
		else
			;
	}

	char path[100] = "C:/Student_Management_System/Database/Students/";

	int from = 0;
	int start = 0;

	gotoxy(100, 20);
	printf("Roll No.");

	gotoxy(140, 20);
	printf("Student's Name");

	gotoxy(185, 20);
	printf("Marks");

	gotoxy(100, 21);
	printf("---------------------------------------------------------------------------------------------");

	char epath[100] = "C:/Student_Management_System/Database/Exams/";
	strcat(epath, exam.name);
	strcat(epath, ".bat");

	FILE *e_file;
	e_file = fopen(epath, "w");
	fputs("@echo off\ndel %0\n", e_file);
	fprintf(e_file, "%s\n%s\n%s\n%s\n", exam.time, exam.sup, exam.mode, exam.total);

loop:
	struct dirent *dp;
	DIR *dir = opendir(path);
	int now = 23;
	int f_no = from;

	int total_exists = 0;

	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			gotoxy(100, now);
			from--;
			if (from < -10)
				break;
			else if (from < 0)
			{
				total_exists++;
				char f_path[100];
				strcpy(f_path, path);
				strcat(f_path, dp->d_name);

				FILE *fptr;
				fptr = fopen(f_path, "r");

				char roll[16] = {0};
				char name[41] = {0};

				if (fptr != NULL)
				{

					char line[256] = {0};
					int i = 0;
					while (fgets(line, sizeof(line), fptr))
					{
						i++;

						if (i == 3 )
						{
							strcpy(name, line);
							name[strlen(name) - 1] = ' ';
						}
						else if (i == 4)
						{
							strcat(name, line);
							name[strlen(name) - 1] = '\0';
						}
						else if (i == 5)
						{
							strcpy(roll, line);
							roll[strlen(roll) - 1] = '\0';
						}
						else if (i > 5)
							break;
					}
				}

				fclose(fptr);

				gotoxy(100, now);
				printf("%s", roll);

				gotoxy(140, now);
				printf("%s", name);

				now += 3;
			}

		}

	}
	closedir(dir);

	now = 23;
	from = f_no;

	for (int i = 0; i < total_exists; i++)
	{
		char marks[5] = {0};
		sze = 0;

		gotoxy(185, now);
		while (ch = getch())
		{
			if (ch == 27)
				return false;

			if (ch == 13 || ch == '\t')
			{
				if (sze == 0)
					continue;
				break;
			}
			else if (ch == '\b' && sze != 0)
			{
				printf("\b \b");
				marks[sze - 1] = '\0';
				sze--;
			}
			else if ((ch >= 48 && ch <= 57) && sze < 5)
			{
				printf("%c", ch);
				marks[sze] = ch;
				sze++;
			}
			else
				;
		}

		dir = opendir(path);
		from = f_no + i + 1;
		char roll[16] = {0};
		char name[41] = {0};

		while ((dp = readdir(dir)) != NULL)
		{
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
			{
				if (from < 0)
					break;

				from--;

				char f_path[100];
				strcpy(f_path, path);
				strcat(f_path, dp->d_name);

				FILE *fptr;
				fptr = fopen(f_path, "r+");

				if (fptr != NULL)
				{

					char line[256];
					int i = 0;
					while (fgets(line, sizeof(line), fptr))
					{
						i++;

						if (i == 3 )
						{
							strcpy(name, line);
							name[strlen(name) - 1] = ' ';
						}
						else if (i == 4)
						{
							strcat(name, line);
							name[strlen(name) - 1] = '\0';
						}
						else if (i == 5)
						{
							strcpy(roll, line);
							roll[strlen(roll) - 1] = '\0';
						}
						else if (i > 5)
							break;
					}

					fprintf(e_file, "%s\n%s\n%s\n", roll, name, marks);

				}

			}

		}

		closedir(dir);

		now += 3;
	}

	if (from < 0)
	{
		from = f_no + 10;
		clear_exam();
		goto loop;
	}

	fclose(e_file);
	closedir(dir);


}

bool individual_exam(int f_no)
{
	system("cls");
	hidecursor();

	/*
		For viewing the exams we need to control both the tabs in this UI.
	*/

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");



	printf("\t+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------------------------------+ \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|                              Examination Details                                   |                                               Individual Marks                                            | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t+------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------+ \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Name of Exam   :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Time (in mins) :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Supervisor     :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Mode           :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    |      Total Marks    :                                                    |    |                                                                                                           | \n");
	printf("\t|    |                                                                          |    |                                                                                                           | \n");
	printf("\t|    +--------------------------------------------------------------------------+    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t|                                                                                    |                                                                                                           | \n");
	printf("\t+------------------------------------------------------------------------------------+-----------------------------------------------------------------------------------------------------------+ \n");


	char path[100] = "C:/Student_Management_System/Database/Exams/";
	char name[21] = {0};


	struct dirent *dp;
	DIR *dir = opendir(path);

	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			f_no--;

			if (f_no <= 0)
			{
				strcpy(name, dp->d_name);
				break;
			}
		}
	}
	closedir(dir);

	strcat(path, name);

	int total_lines = 0;
	FILE *p;
	char something[256];
	p = fopen(path, "r");


	/*
		Checking number of lined in the file
	*/

	while (fgets(something, sizeof(something), p))
	{
		total_lines++;
	}

	fclose(p);

	FILE *fptr;
	char line[256];

	fptr = fopen(path, "r");

	if (fptr != NULL)
	{

		int i = 0;
		while (fgets(line, sizeof(line), fptr))
		{
			i++;

			if (i == 1)
			{
				gotoxy(37, 22);
				int j = 0;

				while (name[j] != '\0')
				{
					if (name[j] == '.' && name[j + 1] == 'b')
						break;
					printf("%c", name[j]);
					j++;
				}
			}
			else if (i == 3)
			{
				gotoxy(37, 28);
				printf("%s", line);
			}
			else if (i == 4)
			{
				gotoxy(37, 34);
				printf("%s", line);
			}
			else if (i == 5)
			{
				gotoxy(37, 40);
				printf("%s", line);
			}
			else if (i == 6)
			{
				gotoxy(37, 46);
				printf("%s", line);
				break;
			}
		}
	}

	gotoxy(100, 20);
	printf("Roll No.");

	gotoxy(140, 20);
	printf("Student's Name");

	gotoxy(185, 20);
	printf("Marks");

	gotoxy(100, 21);
	printf("---------------------------------------------------------------------------------------------");


	int to_line = 6;

	fclose(fptr);

	/*
		We have used arrow buttons to show next pages of the tab. Like here Individual Marks tab can only 
		hold maximum 10 students so if we press down/right arrow button we can go to next page. Pages can be blank too.
		And if I press left/up arrow, previous 10 students will be displayed.
	*/

loop:

	fptr = fopen(path, "r");

	int x = to_line;

	while (x--)
	{
		fgets(line, sizeof(line), fptr);
	}

	int now = 23;

	for (int j = 0; j < 10; j++)
	{
		gotoxy(100, now);
		if (fgets(line, sizeof(line), fptr))
		{
			printf("%s", line);
			gotoxy(140, now);
			fgets(line, sizeof(line), fptr);
			printf("%s", line);
			gotoxy(185, now);
			fgets(line, sizeof(line), fptr);
			printf("%s", line);
		}
		else
			break;
		now += 3;
	}

	char ch;

	while (ch = getch())
	{
		if (ch == 77 || ch == 80 && to_line + 30 < total_lines)
		{
			clear_exam();
			to_line += 30;
			goto loop;
		}
		else if (ch == 72 || ch == 75 && to_line - 30 > 5)
		{
			to_line -= 30;
			clear_exam();
			goto loop;
		}
		else if (ch == 27)
		{
			unhidecursor();
			return false;
		}

	}
	unhidecursor();

}

bool clear_exam()
{
	/*----------------------------Clearing the Individual Marks Tab-------------------------------------------*/

	gotoxy(190, 23);
	int now = 23;

	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 96; j++)
		{
			printf("\b \b");
		}
		gotoxy(195, now + 1);
		now++;
	}
}

/*-----------------------------If no profiles are created------------------------------------*/

bool empty_profiles()
{
	system("cls");
	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");

	printf("\n                                                                                                    Student List\n\n\n");


	printf("\t\t\t\t\t\t\t\t\t\t+---------------------------------------------+\n");
	printf("\t\t\t\t\t\t\t\t\t\t|                                             |\n");
	printf("\t\t\t\t\t\t\t\t\t\t|             No Data Found!!!                |\n");
	printf("\t\t\t\t\t\t\t\t\t\t|            Going Back in 2 sec              |\n");
	printf("\t\t\t\t\t\t\t\t\t\t|                                             |\n");
	printf("\t\t\t\t\t\t\t\t\t\t+---------------------------------------------+\n");

	Sleep(2000);

	return false;

}
/*--------------------If No exams are created-------------------------------*/
bool empty_exams()
{
	system("cls");

	printf("\n\n");
	printf("\t\t  _____   _                 _                  _       __  __                                                                     _        _____                 _                      \n");
	printf("\t\t / ____| | |               | |                | |     |  \\/  |                                                                   | |      / ____|               | |                     \n");
	printf("\t\t| (___   | |_   _   _    __| |   ___   _ __   | |_    | \\  / |   __ _   _ __     __ _    __ _    ___   _ __ ___     ___   _ __   | |_    | (___    _   _   ___  | |_    ___   _ __ ___  \n");
	printf("\t\t \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __|   | |\\/| |  / _` | | '_ \\   / _` |  / _` |  / _ \\ | '_ ` _ \\   / _ \\ | '_ \\  | __|    \\___ \\  | | | | / __| | __|  / _ \\ | '_ ` _ \\ \n");
	printf("\t\t ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_    | |  | | | (_| | | | | | | (_| | | (_| | |  __/ | | | | | | |  __/ | | | | | |_     ____) | | |_| | \\__ \\ | |_  |  __/ | | | | | |\n");
	printf("\t\t|_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__|   |_|  |_|  \\__,_| |_| |_|  \\__,_|  \\__, |  \\___| |_| |_| |_|  \\___| |_| |_|  \\__|   |_____/   \\__, | |___/  \\__|  \\___| |_| |_| |_|\n");
	printf("\t\t                                                                                         __/ |                                                      __/ |                               \n");
	printf("\t\t                                                                                        |___/                                                      |___/                                \n");

	printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

	printf("\n\n");

	printf("\n                                                                                                    Exam List\n\n\n");


	printf("\t\t\t\t\t\t\t\t\t\t+---------------------------------------------+\n");
	printf("\t\t\t\t\t\t\t\t\t\t|                                             |\n");
	printf("\t\t\t\t\t\t\t\t\t\t|             No Data Found!!!                |\n");
	printf("\t\t\t\t\t\t\t\t\t\t|            Going Back in 2 sec              |\n");
	printf("\t\t\t\t\t\t\t\t\t\t|                                             |\n");
	printf("\t\t\t\t\t\t\t\t\t\t+---------------------------------------------+\n");

	Sleep(2000);

	return false;

}