#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void Mmenu(void);
void Send(void);
void Edit(void);
void View(void);
void pass(void);
void log(void);

void sign(void) {
	puts("----------------------------------------------------------------------------");
	printf("SIGN UP\n1.sign up\n2.already have an account?\nenter number of menu:\n");

}

void Mmenu(void) {
	puts("----------------------------------------------------------------------------");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n","MENU" ,"1.send message", "2.edit message", "3.view all messages", "4.change password", "5.exit", "enter number of menu:");
}

void Send(void) {
	puts("----------------------------------------------------------------------------");
	printf("%s\n%s\n%s\n%s\n", "SEND MESSAGE", "1.send message", "2.exit", "enter number of menu:");
}

void Edit(void) {
	puts("----------------------------------------------------------------------------");
	printf("%s\n%s\n%s\n%s\n", "EDIT MESSAGE", "1.edit message", "2.exit", "enter number of menu:");

	}

void View(void) {
	puts("----------------------------------------------------------------------------");
	printf("%s\n%s\n%s\n%s\n", "VIEW ALL MESSAGES ", "1.view all messages", "2.exit", "enter number of menu:");
}

void pass(void) {
	puts("----------------------------------------------------------------------------");
	printf("%s\n%s\n%s\n%s\n", "CHANGE PASSWORD ", "1.change password", "2.exit", "enter number of menu:");
	}

void log(void) {
	puts("----------------------------------------------------------------------------");
	printf("LOG IN\n1.log in\n2.creat new account?\nenter number of menu:");

}


typedef struct {
	char username[51]; //username contains maximum 100 char
	char password[51]; //username contains maximum 100 char
	int user_messages[21];//each user can send maximum 20 messages
	int user_ID;

}USER;


int main(void) {
	char mes[1000] = "";
	int ID = 0;
	USER User[51] = { "","",{ 0 },0 };        //maximum 50 users
	int user = 0;                             //number of all the users



	FILE* q;
	q = fopen("users.txt", "rb+");//////////////////////////////////////////////////

	if(q==0){
            USER blank = { "","",{0},0 };////////////making users.txt
            ID=0;
	        q = fopen("users.txt", "w+");

	        for (int i = 1; i <= 50; i++) {
		    fwrite(&blank, sizeof(USER), 1, q);
	}


	fseek(q, 60 * sizeof(USER), SEEK_SET);
	fwrite(&ID, sizeof(int), 1, q);
	fclose(q);

	}
	else{
	fseek(q, 60 * sizeof(USER), SEEK_SET);
	fread(&ID,sizeof(int),1,q);
	fclose(q);////////////////////////
	}

    FILE* me = fopen("messages.txt", "r+");
	if(me==0){
        me=fopen("messages.txt", "w+");
	for (int i = 1; i <= 1000; i++) {
		fwrite(&mes, sizeof(mes), 1, me);
	}
	fclose(me);}
	else{
     	fclose(me);

	}





	FILE* m;
	m = fopen("users.txt", "rb+");
	for (int i = 1; i <= 100; i++) {
		fseek(m, i * sizeof(USER), SEEK_SET);
		USER t;
		fread(&t, sizeof(USER), 1, m);
		if (t.user_ID == 0) {
			user = i - 1;
			break;
		}
	}


	int userinp = 0;                            //ID of the user in progress



SIGN:

	sign();
	int si;
	scanf("%d", &si);
	if (si == 1) {              //sign in
		puts("username:");
		user++;
		scanf("\n");
		char* usern = (char*)malloc(51 * sizeof(char));
		gets(usern);

		FILE* p;
		p = fopen("users.txt", "rb+");//////////////////////////////////////////////////

		for (int i = 1; i < user; i++) {          //repeticious username
			USER now;
			fseek(p, i * sizeof(USER), SEEK_SET);
			fread(&now, sizeof(USER), 1, p);
			if (strcmp(now.username, usern) == 0) {
				puts("username has been taken already!");
				user--;
				goto SIGN;
			}
		}

        userinp = user;
		User[userinp].user_ID = user;
		strcpy(User[userinp].username, usern);
		puts("password:");
		scanf("\n");
		gets(User[userinp].password);

		fseek(p, userinp * sizeof(USER), SEEK_SET);
		fwrite(&User[userinp], sizeof(USER), 1, p);

		fclose(p);////////////////////////////////////////

		puts("----------------------------------------------------------------------------");

		system("cls");
        printf("welcome %s!\n", User[user].username);
		goto MENU;

	}
	if (si == 2) {        //already have an account
		system("cls");
		goto LOG;
	}
	else {
		system("cls");
		puts("your number must be 1 or 2!");
		goto SIGN;
	}




LOG:



	log();
	int lo;
	puts("");
	scanf("%d", &lo);
	if (lo == 1) {             //log in
		char* us = (char*)malloc(51 * sizeof(char));
		puts("username:");
		scanf("\n");
		gets(us);
		int y = 0;

		FILE* p;
		p = fopen("users.txt", "rb+");//////////////////////////////////////////////////
		USER b;

		for (int i = 1; i <= user; i++) {
			fseek(p, i * sizeof(USER), SEEK_SET);
			fread(&b, sizeof(USER), 1, p);

			if (strcmp(b.username, us) == 0) {
				y = i;
				break;
			}


		}

		fclose(p);///////////////////////////////////////

		if (y == 0) {     //invalid username
			puts("no account found with this username");
			goto LOG;
		}


		puts("password:");          //valid username
		char* pa = (char*)malloc(50 * sizeof(char));
		scanf("\n");
		gets(pa);



		if (strcmp(b.password, pa) == 0) {
			userinp = y;
			system("cls");
			puts("----------------------------------------------------------------------------");
			puts("welcome!");

			goto MENU;
		}
		else {
			system("cls");
			puts("wrong password!");
			goto LOG;
		}
	}

	if (lo == 2) {          //creat new account
		system("cls");
		goto SIGN;
	}
	else {
		system("cls");
		puts("your number must be 1 or 2!");
		goto LOG;
	}


	MENU:

		Mmenu();
	    int n;
		scanf("%d", &n);


		switch (n) {
		case 1:

            system("cls");

		SEND:

			Send();
			int s;
			scanf("%d", &s);
			if (s == 1) {         //send
				ID++;

				FILE* se;
				se = fopen("users.txt", "rb+");//////////////////////////////////////////////////
				fseek(se, userinp * sizeof(USER), SEEK_SET);
				fread(&User[userinp], sizeof(USER), 1, se);

				for (int i = 1; i <= 20; i++) {

					if (User[userinp].user_messages[i] == 0) {
						User[userinp].user_messages[i] = ID;
						break;
					}

				}


				char mes1[1000];     /////getting message
				printf("Message(press enter to send):\nID:%d\t", ID);
				scanf("\n");
				gets(mes1);

				fseek(se, userinp * sizeof(USER), SEEK_SET);
				fwrite(&User[userinp], sizeof(USER), 1, se);//writing the user's last message ID

				fseek(se, 60 * sizeof(USER), SEEK_SET);
				fwrite(&ID, sizeof(int), 1, se);   //writing the last message ID in doc

				fclose(se);////////////////////////

				FILE* M = fopen("messages.txt", "rb+");///////////////////////////////writing the message in messages doc
				fseek(M, ID * sizeof(mes), SEEK_SET);
				fwrite(&mes1, sizeof(mes), 1, M);
				fclose(M);///////////////////////////

				goto SEND;
			}
			if(s == 2) {
                system("cls");
				goto MENU;
			}
			else {
                system("cls");
				puts("your number must be 1 or 2!");
				goto SEND;
			}



		case 2:

		system("cls");

		EDIT:


			Edit();
			int e;
			scanf("%d",&e);
			if (e == 1) {       //edit
				int x;
				puts("enter your message ID");
				scanf("%d", &x);
				if (x>ID||x<1) {
					puts("no message has been sent with this ID");
				}
				else {
					FILE* ed;
					ed = fopen("users.txt", "rb+");//////////////////////////////////////////////////
					fseek(ed, userinp * sizeof(USER), SEEK_SET);
					fread(&User[userinp], sizeof(USER), 1, ed);

					int validity=0;

					for (int i = 1; i <= 20; i++) {
						if (User[userinp].user_messages[i] == x) {      ///valid message ID
							printf("your message is:\n");

							char mes2[1000];

							FILE* M2 = fopen("messages.txt", "rb+");/////////////////writing the message in messages doc
							fseek(M2, x * sizeof(mes), SEEK_SET);
							fread(&mes2, sizeof(mes), 1, M2);

							printf("%s\n", mes2);


							puts("enter your new message:");
							scanf("\n");
							gets(mes2);

							fseek(M2, x * sizeof(mes), SEEK_SET);
							fwrite(&mes2, sizeof(mes), 1, M2);

							fclose(M2);///////////////////////////

							validity = 1;
							break;
						}

					}

					if (validity == 0) {                 //invalid message ID
                        puts("this message is not yours!");
					}
					fclose(ed);
				}
				goto EDIT;
			}
			if (e == 2) {
                system("cls");
				goto MENU;
			}
			else {
			    system("cls");
				puts("your number must be 1 or 2!");
				goto EDIT;
			}



		case 3:

		    system("cls");

		VIEW:

			View();
			int v;
			scanf("%d", &v);
			if (v == 1) {
				int lastid;
				FILE* vi = fopen("users.txt", "rb+");//////////////////////////////////////////////////
				fseek(vi, 60 * sizeof(USER), SEEK_SET);
				fread(&lastid, sizeof(USER), 1, vi);
				fclose(vi);///////




				if (lastid == 0) {
					puts("no messages has been sent!");
					goto MENU;
				}
				else {
					FILE* ME = fopen("messages.txt", "rb+");///////////

					for (int i = 1; i <= ID; i++) {
						char mes4[1000];
						fseek(ME, i * sizeof(mes), SEEK_SET);
						fread(&mes4, sizeof(mes), 1, ME);
						printf("(ID:%d)\t%s\n", i, mes4);
					}

					fclose(ME);
					goto VIEW;
				}
			}
			if (v == 2) {
                system("cls");
				goto MENU;
			}
			else {
			    system("cls");
				puts("your number must be 1 or 2!");
				goto VIEW;
			}

		case 4:

		    system("cls");

		PASS:

			pass();
			int p;
			scanf("%d",&p);
			if(p == 1){    //change password
            puts("enter your new password:");

			FILE* PA = fopen("users.txt", "rb+");
			fseek(PA, userinp * sizeof(USER), SEEK_SET);
			fread(&User[userinp], sizeof(USER), 1, PA);

            scanf("\n");
            gets(User[userinp].password);

			fseek(PA, userinp * sizeof(USER), SEEK_SET);
			fwrite(&User[userinp], sizeof(USER), 1, PA);

			fclose(PA);


            puts("password changed");
            goto PASS;

			}
			if(p == 2){
                system("cls");
                goto MENU;
			}
			else{
			    system("cls");
                puts("your number must be 1 or 2!");
                goto PASS;
			}

		case 5:
		    system("cls");
		    goto LOG;

		default:
		    system("cls");
			puts("invalid number!");
			goto MENU;
		}

	}

