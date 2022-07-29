#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Message
{
	int ID;
	char * msg;
	struct Message * next;
};
void add_Message (struct Message ** first, struct Message ** last, const char * m, int id)
{
	if (*first == NULL)
	{
		(*first) = (struct Message *) malloc (sizeof (struct Message));
		(*first) -> msg = (char *) malloc (strlen(m) + 1);
		strcpy ((*first) -> msg, m);
		(*first) -> ID = id;
		(*first) -> next = NULL;
		(*last) = (*first);
	}
	else
	{
		struct Message * temp = (struct Message *) malloc (sizeof (struct Message));
		temp -> msg = (char *) malloc (strlen(m) + 1);
		strcpy (temp -> msg, m);
		temp -> ID = id;
		temp -> next = NULL;
		(*last) -> next = temp;
		(*last) = temp;
	}
	
}
void print_Messages (struct Message * temp)
{
	while (temp != NULL)
	{
		printf ("\n   %s", temp -> msg);
		printf ("\n   ID: %d", temp -> ID);
		printf ("\n   -------------------------------------------------");
		temp = temp -> next;
	}
}

struct Message * search_and_edit_ID (struct Message * temp, int id)
{
	while (temp != NULL)
	{
		if (temp -> ID == id)
			return temp;
		temp = temp -> next;
	}
	return NULL;
}

struct User
{
	char * user_name;
	int password;
	struct Message * first, * last;
	struct User * next;
};

static struct User * user = NULL;
static int ID_counter = 0;
struct User * first = NULL, * last = NULL;

void add_User (const char * ptr, int * p)
{
	if (first == NULL)
	{
		first = (struct User *) malloc (sizeof (struct User));
		first -> user_name = (char *) malloc (strlen(ptr) + 1);
		strcpy (first -> user_name, ptr);
		first -> password = *p;
		first -> next = NULL;
		first -> first = first -> last = NULL;
		last = first;
		user = first;
	}
	else
	{
		struct User * temp = (struct User *) malloc (sizeof (struct User));
		temp -> user_name = (char *) malloc (strlen(ptr) + 1);
		strcpy (temp -> user_name, ptr);
		temp -> password = *p;
		temp -> next = NULL;
		temp -> first = temp -> last = NULL;
		last -> next = temp;
		last = temp;
		user = last;
	}
}

int find_User (const char * ptr, int * p)
{
	struct User * temp = first;
	while (temp != NULL)
	{
		if ((strcmp (temp -> user_name, ptr) == 0))
		{
			if ((temp -> password == *p))
			{
				user = temp;
				return 1;
			}
			else
				return 2;
		}	
		temp = temp -> next;
	}
	return 3;
}


void Login_signup_menu();
void Main_menu();
void Send_message();
void Edit_message();
void View_all_messages();
void Change_password();

int main ()
{
	while (1)
	{
		Login_signup_menu();
		Main_menu();
	}
	return 0;
}

void Login_signup_menu ()
{
	struct User * temp;
	char user_name[30];
	int password, choice;
	do
	{
		system("cls");
		printf ("\n   -> User name can be a combination of\n      letters and numbers. (with no space)");
		printf ("\n   -> Your password must be integer");
		printf ("\n\n   User name: ");
		scanf ("%s", user_name);
		printf ("\n   Passwrod: ");
		scanf ("%d", &password);
		choice = find_User(user_name, &password);
		if (choice == 2)
		{
			printf("\n   This username has already been taken");
			printf("\n   Choose a different username\n   ");
			system("pause");
		}
		else if (choice == 3)
		{
			add_User (user_name, &password);
			printf("\n   Your registration was successful\n   ");
			system("pause");
		}
	} while (choice == 2);
}
void Display_menu (int * choice)
{
	system("cls");
	printf ("\n\t\t\tWelcome");
	printf ("\n\n   1. Send message");
	printf ("\n   2. Edit message");
	printf ("\n   3. View all messages");
	printf ("\n   4. Change password");
	printf ("\n   5. Exit");
	printf ("\n\n   Enter number of menu: ");
	scanf ("%d", &*choice);
}
void Main_menu ()
{
	int choice;
	do
	{
		Display_menu (&choice);
		switch (choice)
		{
			case 1:  {  Send_message();       break;  }
			case 2:  {  Edit_message();       break;  }
			case 3:  {  View_all_messages();  break;  }
			case 4:  {  Change_password();    break;  }
			case 5:  {						  break;  }
			default: {
				printf ("\n\n   Wrong choice");
				printf ("\n   It has to be between 1 to 5\n   ");
				system("pause");
				system("cls");
				break;
			}
		}
	} while (choice != 5);
}
void print (const char * str)
{
	system("cls");
	printf ("\n\n   1. %s", str);
	printf ("\n   2. Exit");
	printf ("\n\n   Enter number of menu: ");
}
void Send_message()
{
	const int size = 200;
	int choice;
	char str[size];
	do
	{
		print("Send message");
		scanf ("%d", &choice);
		switch (choice)
		{
			case 1:
			{
				system("cls");
				printf ("\n\n   Enter a message: ");
				fseek(stdin,0,SEEK_END);
				scanf ("%[^\n]", str);
				ID_counter++;
				add_Message (&user -> first, &user -> last, str, ID_counter);
				break;
			}
			case 2: break;
			default:
			{
				printf ("\n\n   Wrong choice");
				printf ("\n   It has to be 1 or 2\n   ");
				system("pause");
				break;
			}
		}
	} while (choice != 2);
}
void Edit_message()
{
	const int size = 200;
	char str[size];
	int choice, ID;
	do
	{
		print("Edit message");
		scanf ("%d", &choice);
		switch (choice)
		{
			case 1:
			{
				system("cls");
				printf ("\n\n   Enter ID: ");
				scanf("%d", &ID);
				fseek(stdin,0,SEEK_END);
				struct Message * temp = search_and_edit_ID (user -> first, ID);
				if (temp != NULL) {
					printf ("   Enter new message: ");
					scanf ("%[^\n]", str);
					free (temp -> msg);
					temp -> msg = (char *) malloc (strlen(str) + 1);
					strcpy (temp -> msg, str);
					printf ("\n   Message edited successfully\n   ");
				}
				else
					printf ("\n   The message you want to edit does not belong to you\n   ");
				system("pause");
				break;
			}
			case 2: break;
			default:
			{
				printf ("\n\n   Wrong choice");
				printf ("\n   It has to be 1 or 2\n   ");
				system("pause");
				break;
			}
		}
	} while (choice != 2);
}
void View_all_messages()
{
	int choice;
	do
	{
		print("view all messages");
		scanf ("%d", &choice);
		switch (choice)
		{
			case 1:
			{
				struct User * temp = first;
				while (temp != NULL)
				{
					print_Messages (temp -> first);
					temp = temp -> next;
				}
				printf ("\n\n   ");
				system("pause");
				break;
			}
			case 2: break;
			default:
			{
				printf ("\n\n   Wrong choice");
				printf ("\n   It has to be 1 or 2\n   ");
				system("pause");
				break;
			}
		}
	} while (choice != 2);
}
void Change_password()
{
	int choice, password;
	do
	{
		print("change password");
		scanf ("%d", &choice);
		switch (choice)
		{
			case 1:
			{
				printf ("\n   Your password must be integer");
				printf ("\n   Enter new password: ");
				scanf ("%d", &password);
				user -> password = password;
				printf ("\n   Password changed successfully ");
				break;
			}
			case 2: break;
			default:
			{
				printf ("\n\n   Wrong choice");
				printf ("\n   It has to be 1 or 2\n   ");
				system("pause");
				break;
			}
		}
	} while (choice != 2);
}
