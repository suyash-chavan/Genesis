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
int home();
bool login();
bool verify_user(char *, char *);
void student_data();
void add_student();
void my_schedule();
void view_profile(int);
void print_safe(char *);
void attendance_record();
void individual_profile();
void print_note(char *);
void clear_note();
void note_not_found();
void print_attendance(char *);
void handle_attendance(int , int , int , int *);
void clear_attendance();

/*---------------------Mouse Pointer Coordinates----------------------*/
POINT a;
POINT *b;


/*----------------------Main Function---------------------------------*/

/*
	Main function will control the call of all functions so that further
	there is no need to recursively call functions which avoids stack overflow
	if there are many recursive calls by user. This consumes some amount of memory
	to store global variables but is necessary.
*/

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

	my_schedule();

	/*
		fullscreen();
		remove_scrollbar();

		login_controller:
		if(!login())
			return 0;

		home_controller:
		home();
		// Add Navigation Functions here

		view_profile_controller:
		view_profile();

		attendance_record_controller:
		attendance_record();

		my_schedule_controller:
		//my_schedule();

		add_student_controller:
		add_student();
	*/


	return 0;
}


/*--------------------------------------Login Page-----------------------------------*/
/*
	This function take username and password from user and verify it, if found correct
	returns true else return false.
*/
bool login()
{
	ClearConsoleToColors(15, 0);
	//SetColor(28);

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

	printf("\t\t\t\t\t\t\t\t\t+---------------------------------------------------------------+ \n");
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

	while (ch = getch())
	{
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

/*-----------------------------------Homepage-----------------------------------*/
/*
	This Homepage shows the features provided by user
*/
int home()
{
	system("cls");
	hidecursor();

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
	printf("    (\n");

	printf("\n\n");


	printf("     (     \t ______                              _                   _     _                     _____            _           \n");
	printf("     \\    \t|  ____|                            (_)                 | |   (_)                   |  __ \\          | |          \n");
	printf("      )    \t| |__    __  __   __ _   _ __ ___    _   _ __     __ _  | |_   _    ___    _ __     | |  | |   __ _  | |_    __ _ \n");
	printf("##-------->\t|  __|   \\ \\/ /  / _` | | '_ ` _ \\  | | | '_ \\   / _` | | __| | |  / _ \\  | '_ \\    | |  | |  / _` | | __|  / _` |\n");
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



	getch();

	return 0;

}

void student_data()
{

	hidecursor();
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
	printf("    (      \t__      __  _                       _____                    __   _   _               \n");
	printf("     \\    \t\\ \\    / / (_)                     |  __ \\                  / _| (_) | |              \n");
	printf("      )    \t \\ \\  / /   _    ___  __      __   | |__) |  _ __    ___   | |_   _  | |   ___   ___  \n");
	printf("##-------->\t  \\ \\/ /   | |  / _ \\ \\ \\ /\\ / /   |  ___/  | '__|  / _ \\  |  _| | | | |  / _ \\ / __| \n");
	printf("      )    \t   \\  /    | | |  __/  \\ V  V /    | |      | |    | (_) | | |   | | | | |  __/ \\__ \\ \n");
	printf("     /     \t    \\/     |_|  \\___|   \\_/\\_/     |_|      |_|     \\___/  |_|   |_| |_|  \\___| |___/ \n");
	printf("    (      \t\n");

	printf("\n\n");


	printf("    (      \t                _       _      _____   _                 _                  _    \n");
	printf("     \\    \t    /\\         | |     | |    / ____| | |               | |                | |   \n");
	printf("      )    \t   /  \\      __| |   __| |   | (___   | |_   _   _    __| |   ___   _ __   | |_  \n");
	printf("##-------->\t  / /\\ \\    / _` |  / _` |    \\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __| \n");
	printf("      )    \t / ____ \\  | (_| | | (_| |    ____) | | |_  | |_| | | (_| | |  __/ | | | | | |_  \n");
	printf("     /     \t/_/    \\_\\  \\__,_|  \\__,_|   |_____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__| \n");
	printf("    (      \t\n");

	printf("\n\n");




	getch();
}

void add_student()
{

	//hidecursor();
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

	char self_explode[100] = "@echo off\ndel \"C:\\Student_Management_System\\Database\\Attendance\\";
	strcat(self_explode, current.roll);
	strcat(self_explode, ".bat\"\n");
	printf("%s\n", current.sfname);

	fptr = fopen(path, "w");


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

	getch();
}


/*------------------------------------------------Teachers Schedule ------------------------------------------------------*/
void my_schedule()
{

	//hidecursor();
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

	fptr = fopen(path, "");

	char self_explode[100] = "@echo off\ndel \"C:\\Student_Management_System\\Database\\Schedule\\";
	if (date.day < 10)
		strcat(self_explode, "0");
	strcat(self_explode, d);
	if (date.month < 10)
		strcat(self_explode, "0");
	strcat(self_explode, m);
	strcat(self_explode, y);
	strcat(self_explode, ".bat\"\n");

	if (fptr==NULL)
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

			int n=strlen(data);

			int now=22;

			for(int j=0;j<n;j++)
			{
				if(j!=0 && j%115==0)
				{
					gotoxy(20,now+1);
					now++;
				}
				printf("%c",data[j]);
			}

			while (ch = getch())
			{
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
				if (ch == 13)
					break;
				else if (ch == '\t')
				{
					gotoxy(179,32);
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
				if (ch == 13)
					break;
				else if (ch == '\t')
				{
					gotoxy(179,32);
					printf("\b\b  ");

					gotoxy(179,35);
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
				if (ch == 13)
				{
					gotoxy(179,32);
					printf("\b\b  ");

					gotoxy(179,35);
					printf("\b\b  ");

					gotoxy(181,38);
					printf("\b\b\b\b    ");
					break;
				}
				else if (ch == '\t')
				{
					gotoxy(179,32);
					printf("\b\b  ");

					gotoxy(179,35);
					printf("\b\b  ");

					gotoxy(181,38);
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
			strcat(path,".bat");

			FILE *fptr;
			fptr=fopen(path,"r+");

			if (fptr!=NULL)
			{
				clear_note();
				option=0;
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

	getch();

}

void print_note(char *path)
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

void clear_note()
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

void note_not_found()
{
	gotoxy(65, 33);
	printf("Schedule Not Found!!!");
	gotoxy(62, 34);
	printf("Going to Today's Schedule...");
	Sleep(3000);
	clear_note();
}

void view_profile(int from)
{

	system("cls");
	hidecursor();

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
			else if (from < -7)
				break;
		}
	}
	closedir(dir);

	getch();
}

void print_safe(char *path)
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

	printf("|         VIEW PROFILE        | \n");
	printf("\t\t\t\t\t\t|                |                                                                  |                             | \n");
	printf("\t\t\t\t\t\t+----------------+------------------------------------------------------------------+-----------------------------+ \n");

}

void attendance_record()
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

	/*-------------------------Creating bat file for storing today's attendance-----------------------------*/

	FILE *exist;

	char d[20], m[5], y[5];
	char path[50] = "C:/Student_Management_System/Database/Attendance/";

	itoa(day, d, 10);
	itoa(month, m, 10);
	itoa(year, y, 10);

	strcat(d, m);
	strcat(d, y);

	strcat(d, ".bat");

	strcat(path, d);

	exist = fopen(path, "r+");

	if (exist == NULL)
	{
		fclose(exist);

		FILE *fptr;
		fptr = fopen(path, "w");

		char self_explode[100] = "@echo off\ndel \"C:\\Student_Management_System\\Database\\Attendance\\";
		strcat(self_explode, d);
		strcat(self_explode, "\"\n");

		fputs(self_explode, fptr);

		fclose(fptr);
	}

	fclose(exist);

	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-------------------------------------------------+ \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                            Attendance List                                                               |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |         +---------------------------+           | \n");
	printf("\t|                                                                                                                                          |         |                           |           | \n");
	printf("\t|                                                                                                                                          |         |     Today's Attendance    |           | \n");
	printf("\t|                                                                                                                                          |         |                           |           | \n");
	printf("\t|                                                                                                                                          |         +---------------------------+           | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |     +------------------------------------+      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |          Goto Custom Date          |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |    Day      :                      |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |    Month    :                      |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |    Year     :                      |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |      SEARCH          CANCEL        |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     |                                    |      | \n");
	printf("\t|                                                                                                                                          |     +------------------------------------+      | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t|                                                                                                                                          |                                                 | \n");
	printf("\t+------------------------------------------------------------------------------------------------------------------------------------------+-------------------------------------------------+ \n");

	/*---------------------------------------File Handeling Here---------------------------------------*/

	struct _date {
		int day;
		int month;
		int year;
	} date;

	date.day = day;
	date.month = month;
	date.year = year;

	clear_attendance();
	/*
		int option=0;
		char ch;

		while(1)
		{
			gotoxy(71,17);
			printf("%02d/%02d/%04d",date.day,date.month,date.year);
			option%=3;

			switch(option)
			{
				case 0:
					gotoxy(20,19);
					getch();
					handle_attendance(date.day,date.month,date.year,&option);
					break;

				case 1:
					gotoxy(171,22);
					while(ch=getch())
					{
						if(ch==13)
						{
							date.day=day;
							date.month=month;
							date.year=year;
							option=0;
							break;
						}
						else if(ch=='\t')
						{
							option++;
							break;
						}
					}

					break;

				case 2:
					gotoxy(170,32);
					char d[3]={0};
					char m[3]={0};
					char y[5]={0};
					bool completed=true;

					int sze=0;
					while(ch=getch())
					{
						if(ch==13)
							break;
						else if(ch=='\t')
						{
							option++;
							completed=false;
							break;
						}
						else if(ch=='\b' && sze!=0)
						{
							printf("\b \b");
							d[sze-1]='\0';
							sze--;
						}
						else if(ch>=48 && ch<=57 && sze<2)
						{
							printf("%c",ch);
							d[sze]=ch;
							sze++;
						}

					}

					if(!completed)
					{
						break;
					}

					gotoxy(170,35);
					sze=0;
					while(ch=getch())
					{
						if(ch==13)
							break;
						else if(ch=='\t')
						{
							option++;
							completed=false;
							break;
						}
						else if(ch=='\b' && sze!=0)
						{
							printf("\b \b");
							d[sze-1]='\0';
							sze--;
						}
						else if(ch>=48 && ch<=57 && sze<2)
						{
							printf("%c",ch);
							d[sze]=ch;
							sze++;
						}

					}

					if(!completed)
					{
						break;
					}

					gotoxy(170,38);
					sze=0;
					while(ch=getch())
					{
						if(ch==13)
							break;
						else if(ch=='\t')
						{
							option++;
							completed=false;
							break;
						}
						else if(ch=='\b' && sze!=0)
						{
							printf("\b \b");
							d[sze-1]='\0';
							sze--;
						}
						else if(ch>=48 && ch<=57 && sze<4)
						{
							printf("%c",ch);
							d[sze]=ch;
							sze++;
						}
					}

					if(!completed)
						break;

					char path[100]="C:/Student_Management_System/Database/Schedule/";

					if(strlen(d)==1)
					{
						d[1]=d[0];
						d[0]=0;
					}

					if(strlen(m)==1)
					{
						m[1]=m[0];
						m[0]=0;
					}

					if(strlen(y)==2)
					{
						y[3]=y[1];
						y[2]=y[0];
						y[0]='2';
						y[1]='0';
					}

					strcat(path,d);
					strcat(path,m);
					strcat(path,y);

					if(access(path,F_OK)!=-1)
					{
						clear_attendance();
						print_attendance(path);
						date.day=atoi(d);
						date.month=atoi(m);
						date.year=atoi(y);
						option=0;
					}
					else
					{
						clear_note();
						note_not_found();
						option=1;
					}

					break;

			}

		}

	*/

	getch();
}

void handle_attendance(int d, int m, int y, int *option)
{
	*option = *option + 1;
}

void print_attendance(char *f_name)
{
	char path[100] = "C:/Student_Management_System/Database/Attendance/";

	struct dirent *dp;
	DIR *dir = opendir(path);
	int i = 0;
	/*
		while((dp=readdir(dir))!=NULL)
		{
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
	        {
				char f_path[100];
				strcpy(f_path,path);
				strcat(f_path,dp->d_name);
				if(from<0 && from>-31)
				{
					if(i%2==0)
						gotoxy(20,19+i);

					printf("%d.\t\tSuyash Chavan\t\tPresent\t\t\t\t",i+1);
					i++;
				}
				else if(from<-31)
					break;
			}
		}
		closedir(dir);


		for(int i=0;i<30;i++)
		{
			if(i%2==0)
				gotoxy(20,19+i);
			// First Arg - Horizontal , Second Arg- VErtical
			printf("%d.\t\tSuyash Chavan\t\tPresent\t\t\t\t",i+1);
		}
	*/
}

void clear_attendance()
{
	gotoxy(145, 19);
	int now = 19;

	for (int i = 0; i < 32; i++)
	{
		gotoxy(145, 19 + i);
		for (int j = 145; j >= 20; j--)
			printf("\b \b");
	}
}


void individual_profile()
{
	system("cls");
	hidecursor();

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
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|     Permanent Address:                                   |\t\t\t\t\t\t\t\t|   You can Make changes in this form by creating student  | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|     of this roll number and updating all the details.    | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t|                                                          |\t\t\t\t\t\t\t\t|                                                          | \n");
	printf("\t\t+----------------------------------------------------------+\t\t\t\t\t\t\t\t+----------------------------------------------------------+ \n");


	getch();
}