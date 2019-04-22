/*67632 68260
*This program manages the accounts of the clients of the bank
*where you can log in/create account/transfer money/supply and withraw money/change personal info
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define size 10

int  Menu   (void);
int  Menu1  (void);
int  log_in (void);
int sign_up (void);
void  sort  (void);
void    transfer   (void);
void   print_file  (void);
int    forgot_pass (void);
void   fill_arrays (void);
void pop_up_recieve(void);
void check_account (void);
void     supply_withdraw_money  (void);
void     modify_personal_info   (void);
void     swap     (char *p1, char *p2);
void   protect_pass   (char *password);
int check_pass_safety (char *password);
void    swap_arr   (char arr1[30], char arr2[30]);
int check_password (char password[], char pass[]);

char usernames[size][20], fnames[size][20], lnames[size][20], passwords[size][13], temps[size][100], temps1[size][100], gars[size][10], line_info[size][200];
char *questions[100], *answers[20];
char username[20], password[13]; //entered by the user
int balances[size];
char fname_transfer_s[100][20], lname_transfer_s[100][20], fname_transfer_r[100][20], lname_transfer_r[100][20], str[100][20];//str status of the transfer
int amount_transfer[100], line_sender;// line sender to keep track of the index of the sender
int count_users, line, line_reciever, count_transfer_line = 0; // line defined by the user // count_transfer_line is the next name in the transfer list
FILE *database, *output, *input;//output for profiles updated, input for transactions records
int lent[10];
	

int main(void){
	
	int i, j, choice, res_menu, ok;	
	
	fill_arrays();
	
	system("COLOR F2");		
	
	choice = Menu1();	
	
	while(0==0){		
		do{	
			switch (choice){
				
				case 1:								
					ok = log_in();					
					break;
					
				case 2:
					ok = sign_up();
					break;					
			}		
		}while(ok != 1); 
			
				
			printf("\n////////////////////////////////////////////////////////////////");
			printf("\n////////////////////////////////////////////////////////////////");

			printf("\n\t\t ******** Welcome to our Bank ********");
			
			do{
				
				res_menu = Menu();
				
				if	   (res_menu == 1)
					check_account();
				else if(res_menu == 2)
					transfer();
				else if(res_menu == 3)
					pop_up_recieve();
				else if(res_menu == 4)	
					supply_withdraw_money();
			} while(res_menu != 5);
		choice = Menu1();
	if(choice == 3)
		break;
	
	}
	print_file();
	printf("\n\t\t ********\tThank you fo your visit ********\n");

	
	return 0;
}

void  fill_arrays (void){
	
	int i, j;
	
	//fill the arrays from the file "database.txt";
	two = fopen("database.txt","r");
	for(j=0; j<size; j++){
		if(feof(two))
			break;
			
		fscanf(two, "%s %s %s %s %d%s", &usernames[j], &fnames[j], &lnames[j], &passwords[j], &balances[j], &gars[j]);
		fgets(temps1[j], 150, two);
		
		questions[j] = strtok(temps1[j], "?");
		answers[j] = strtok(NULL, " ");
		}
	fclose(two);
	count_users = j;
}

int  Menu1  (void){
	int choice;
	
	do{
		
		printf("\n\t\t ********\tWelcome to our Bank \t********");
		printf("\n\t\t ********	\tMenu\t\t********");
		printf("\n1- Log into my account\n");
		printf("\n2- Create  new account\n");
		printf("\n3- Exit\n");
		printf("\n Enter the number of the action you want to proceed >> ");
		scanf ("%d", &choice);
		
	}while(choice<=0 && choice>=4);
	
return choice;
}

int Menu (void){
/*
* prints the menu of action to perform on the accont
*/
	system("COLOR F5");
	int choice, ok; 
	
	printf("\n\t\t ******** 		Menu 		********");
	printf("\n 1- Modify my personal info");
	printf("\n 2- Transfer Money");
	printf("\n 3- check incom");
	printf("\n 4- supply / withdraw money");
	printf("\n 5- Log out");
	printf("\n Enter the number of the action you want to proceed >> ");
	
	scanf("%d", &choice);
	getchar();

 return choice;
}

int log_in (void){
	
	char ans, ansus;
	int i, j, tlag = 0, flag = 0, flagus = 0, forg;
	char secret_answer[20];
	
	printf("\n\t\t ********	\tLog in\t\t********\n");
	system("COLOR 70");

	do{				
		do{
			printf("Enter your username >> ");
			scanf("%s", &username);
			
			for(i=0; i<size; i++){
				if((strcmp(username, usernames[i])) == 0){
					flagus = 1;
					line = i;	//we take the line of the user's info
					break;	
				}
			}
			if(flagus == 1)
				printf("Username found\n");
			else
				printf("Not found!! try again (y/n) >> ");
				ansus = getchar();
				getchar();
		}while(flagus != 1 && ansus == 'y');
		
		if (flagus != 1)
			break;
		
		printf("Enter your password (press 'f'>> forgot password) >> ");
		scanf("%s", &password);
		getchar();
		
		if(strcmp(password, "f")==0){
			forg = forgot_pass();
			if(forg != 1){
				flag = 0;
				break;
			}	
		}
					
		if (strcmp(password, passwords[line]) == 0){
				flag = 1;	
		}

		else if (strcmp(password, passwords[line]) != 0){
			if (check_password(password, passwords[line]) == 1){
				do{
					printf("Please answer the secret question \n%s?", questions[line]);
					gets(secret_answer);
					if(strcmp(secret_answer, answers[line]) == 0){
						flag = 1;
						tlag = 1;
					}
					else if(strcmp(secret_answer, answers[line]) != 0){
						printf(" Error !! Invalid answer !! \n try again ? (y/n) >> ");
						scanf("%c", &ans);
						getchar();
					}
				}while(tlag != 1 && ans == 'y');		
			}
			else{
				flag = 0;
				printf(" Error !! Invalid username or password !! \n try again ? (y/n) >> ");
				scanf("%c", &ans);
				getchar();
			}
		}
	}while(flag != 1 && ans == 'y');
	
	if(flag == 1){
		printf("Access granted !!\n");
		return flag;;
	}
	else if (flag == 0)
		Menu1();
}

int  check_password (char password[], char pass[]){
/*checks if the password has only two characters that are swaped
*/
	int i, j, flag = 0;
	
	for(i=0;i<13;i++){

		if ( strlen(password) != strlen(pass) )
			break;
		swap(&password[i], &password[i+1]);
			
		if(strcmp(password, pass)==0){
			flag = 1;	
			break;
		}
				
		else if(strcmp(password, pass)!=0)
			swap(&password[i], &password[i+1]);
			
		if(i+1 == 13)
			break;
	}
	
	return flag;
}

void swap (char *p1, char *p2){
	char temp;
	
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void swap_arr (char arr1[30], char arr2[30]){
	char temp[30];
	
	strcpy(temp, arr1);
	strcpy(arr1, arr2);
	strcpy(arr2, temp);
}


int sign_up(void){
	
	int i, res_safe, balance, ok, flag = 0, ans;
	char password[13], question[200], answer[20], last_name[20], first_name[20];
	char username[20], passwordc[13], answer_bal;
	char passcopy[13];
	system("COLOR FC");
	printf("\n\t\t ********	\tsign up\t\t********\n");
	
	output = fopen("output.txt", "a");
	
	// ask for username and check availiability
	do{
		printf("\nPlease enter your username >> ");
		scanf("%s", username);
		getchar();

		for (i=0; i<count_users; ++i)
		{
			if(strcmp(username, usernames[i]) == 0)
				flag++;

		}
		if(flag >= 1)
			printf("\nUsername already exists !! Please enter another one !!"); 
	}while(flag == 1);


	// ask for last then first name
	printf("\nPlease enter you first name (in one word) >> ");
	gets(first_name);
	
	printf("\nPlease enter you last name (in one word)>> ");
	gets(last_name);
	
	// ask for password, check safety
	do
	{
		printf("\nPlease enter your password >> ");
		scanf("%s", password);
		
	}while((check_pass_safety(password)) != 1);

	// ask to confirm password, check matching
	do
	{
		printf("\nPlease confirm your password >> ");
		scanf("%s", passwordc);
		
	}while(strcmp(password, passwordc) != 0);
	
	getchar();
	
	// we keep the passwords uncrypted in the passcopy
	strcpy(passcopy, password);

	// ask for secrect question
	printf("\nPlease enter your secrect question >> ");
	gets(question);
		
	// ask for the answer
	printf("\nPlease enter your secrect answer >> ");
	scanf("%s", answer);
	getchar();
	// ask balance
	
	printf("\nDo you want to implement your account now?[y/n] >> ");
	scanf("%c", &answer_bal);
			
	if (answer_bal == 'y'){		
		printf("\nEnter the amount in DHs >> ");
		scanf("%d", &balance);
		printf("\nok ok!!");
	}
	else
		balance = 0;
		printf("\nok ok !!");
		
	count_users++;
	strcpy(usernames[count_users], username);
	strcpy(fnames[count_users], first_name);
	strcpy(lnames[count_users], last_name);
	strcpy(passwords[count_users], password);
	balances[count_users] = balance;
	questions[count_users] = question;
	answers[count_users] = answer;
	
	printf("\n Please log in to comfirm your registration\n");
	
	ok = log_in();
	
return ok;
}

int check_pass_safety (char *password){
/*
* checks if the password contain 3 lowercase letters, 3 uppercase letters
* 3 digits, and three other characters that are not digits and not letters.
* make sure the password does not contain the following special characters: '@', '\', ';'
* returns 1 if safe, 0 if not safe
*/

	int count_digits = 0, count_lowc = 0, count_upc = 0, count_char = 0;
	int i, flag = 0;

	for (i = 0; i < 13; ++i)

	{
		if ( isdigit(password[i]) != 0)
			count_digits++;
			
		else if ( isupper(password[i]) != 0)
			count_upc++;
		
		else if ( islower(password[i]) != 0)
			count_lowc++;
		
		else if ( password[i] == '@' || password[i] == '/' || password[i] == ';' )
			break;
		
		else 
			count_char++;	
	}
	
	if (count_char == 3 || count_digits == 3 || count_lowc == 3 || count_upc == 3)
		flag = 1;
	
 return flag;
}

void protect_pass (char *password){
/*
*
*takes the password as the first element of the arry(pointer)
*if the ASCII code of the character is odd, the character is replaced by the 
*character that is 150 ASCII code positions before it, 
*if it is even it must be replaced by the character that has half its ASCII code. 
*it does the opposite in the read_password function
*
*/

	int i;

	for (i = 0; i < 13; ++i){
		if (password[i] % 2 == 0)
		{
			password[i] /= 2;
		}
		else if (password[i] % 2 != 0)
		{
			password[i] -= 150; 
		}
	}
}

int forgot_pass (void){
	
	char user[20], answer1[20], npass[13], f_name[20], l_name[20], passcopy[13], gar[5];
	int i, line_pass, flag, ok, a;
	char ans, as;
	
	printf("\n\t\t********\tForgot password\t\t********\n");
	
	do{
		//ask for username
		printf("Enter  your username >> \n");
		gets(username);
		
		if((strcmp(username, usernames[line])) == 0){
			flag = 1;
			printf("valid !!\n");	
		}
		
			
		if(flag == 0){
			printf("Error !! ");
			break;
		}
		//ask for first and last name
		printf("\n Please enter your first then last name >> ");
		scanf("%s %s", &f_name, &l_name);
		
		if(strcmp(f_name, fnames[line]) == 0 && strcmp(l_name, lnames[line]) == 0){
			flag = 1;
			printf("valid !!\n");
		}
		
		if(flag == 0){
			printf("Error !! ");
			break;
		}
		//ask for answer to the secret answer
		printf("%s\n", questions[line]);
		printf("Your answer please >> ");
		scanf("%s", answer1);
		getchar();
		
		if(strcmp(answer1, answers[line]) == 0){
			flag = 1;
			printf("valid !!\n");
		}
		else{
			printf("Error !! try again (y/n)>> ");
			as = getchar();
			flag = 0;
		}
		
	}while(flag != 1 && as != 'y');
		
	if(flag == 1){	
		printf("\nPress 1- new password\nPress 2- recall password >> ");
		a = getchar();
		getchar();		
		
		if(a == 1){
			
			//renewing the password
				do{	
					printf("\nPlease enter your new password >> ");
					scanf("%s", &passwords[line]);
					getchar();
										
				}while(check_pass_safety(npass) == 1);			
			
		}
		else if (a == 2)
		//printing passwod
			printf("\n Your password is >> ", passwords[line]);
	}
	return flag;
}

void supply_withdraw_money (void){
	int i, flouss, ans;
	 
	
	printf("supply account\n");
	printf("\nPress 1- Supply account\nPress 2- Retriete money >> ");
	scanf("%d", &ans);
	
	
	switch(ans){
		case 1:
			printf("\nPlease enter th amount that you want to add >> ");
			scanf("%d", &flouss);
			balances[line] += flouss;
			break;
		case 2:
			printf("\nPlease enter the amount that you want to retriete >> ");
			scanf("%d", &flouss);
			balances[line] -= flouss;
			break;
	}
		
	printf("\nYour balance has been updated to >> %ddhs", balances[line]);
}

void check_account (void){
	
	char ans;
	
	printf("\n\t\t ********	\t check account \t********\n");
	printf("username >> %s\n", usernames[line]);
	printf("first name >> %s\n", fnames[line]);
	printf("last name >> %s\n", lnames[line]);
	printf("password >> ************\n");	
	printf("balance >> %d\n", balances[line]);
	printf("secret question >>%s\n", questions[line]);
	printf("secret answer >>%s\n", answers[line]);
	
	printf("Do you want to modify your personal informations? (y/n) >> ");
	ans = getchar();
	
	if(ans == 'y')
		modify_personal_info();
	
}

void transfer (void){
	int i, j, flag = 0, money_transfer;
	char lnamer[20], fnamer[20];
	
	printf("\n\t\t ********\ttransfer\t\t********\n");
	do{
		
		printf("please enter the first and last name of the reciever of the money >> ");
		scanf("%s %s", &fnamer, &lnamer);
		
		for(i=0;i<size;i++){
			if((strcmp(fnamer, fnames[i])) == 0 && (strcmp(lnamer, lnames[i])) == 0){
				flag = 1;
				line_reciever = i;
				break;
			}							
		}	
	}while(flag == 0);
	if(flag == 1)
		printf("\n The reciever is found !!\n");	
	
	printf("Please enter the amount that you want to transfer >> ");
	scanf("%d", &money_transfer);
	
	if (money_transfer > balances[line])
		printf("\nError !! You don't have enough credit ");
	else	
		balances[line] -=  money_transfer;
		
	
	strcpy(fname_transfer_s[count_transfer_line], fnames[line]);
	strcpy(lname_transfer_s[count_transfer_line], lnames[line]);
	strcpy(fname_transfer_r[count_transfer_line], fnamer);
	strcpy(lname_transfer_r[count_transfer_line], lnamer);
	strcpy(str[count_transfer_line], "hold");
	
	amount_transfer[count_transfer_line] = money_transfer;
	line_sender = line;
	
	count_transfer_line++;
}

void pop_up_recieve (void){
	
	int i, j, flag = 0, amount, index_tr, count_request = 0;
	char ans, ch;
	char lnamer[20], fnamer[20];
	printf("\n\t\t ********\tcheck incom\t\t********\n");
	
	for(i=0; i<count_users; i++){
		printf("***");
		if(strcmp(fnames[line], fname_transfer_r[i]) == 0 && strcmp(lnames[line], lname_transfer_r[i]) == 0){		
			printf("%s %s has sent you %d\n", fname_transfer_s[i], lname_transfer_s[i], amount_transfer[i]);
			printf("Do you accept this money (y/n) >> ");
			ans = getchar();
			getchar();
			
			if(ans == 'y'){
				balances[line] += amount_transfer[i];
				printf("Your balance has been updated !! >> %ddhs", balances[line]);
				strcpy(str[i], "accepted");
			}
			
			else{
				balances[line_sender] += amount_transfer[i];
				strcpy(str[i], "refused");
			}
		}
	}
	
}

void modify_personal_info (){
	int i, j, ans, r, flag = 0, a;
	char usernamem[20], passwordm[20], questionm[100], answerm[20];

	do{
		printf("\n\t\t ********\t\tmodify personal info\t\t********\n");
		printf("\n1- username >> ");
		printf("\n2- password >> ");
		printf("\n3- secret question and secret answer >> ");
		printf("choice >> ");
		scanf("%d", &ans);
		getchar();
		
		//for security we ask for the previous info before chaging it
		switch(ans){
		case 1:
			do{
				printf("Please enter your previous username >> ");
				gets(usernamem);
				if (strcmp(usernamem, usernames[line]) == 0){
					flag = 1;
					printf("Enter the new username >> ");
					scanf("%s", &usernames[line]);
					getchar();
				} 
				else{
					printf("Error !! try again (y/n) >> ");
					r = getchar();
					getchar();
				}
			}while(r == 'y' && flag == 0);
			break;
		case 2:
			do{
				printf("Please enter your previous password >> ");
				scanf("%s", &passwordm);
				
				if (strcmp(passwordm, passwords[line]) == 0){
					flag = 1;
					printf("Enter the new password >> ");
					scanf("%s", &passwords[line]);
					getchar();
				} 
				else{
					printf("Error !! try again (y/n) >> ");
					r = getchar();
					getchar();
				}
			}while(r == 'y' && flag == 0);
			break;		
		case 3:		
			do{
				printf("Please enter your previous secret answer >> ");
				gets(answerm);
				if (strcmp(answerm, answers	[line]) == 0){
					flag = 1;
					
					printf("Enter the new question (don't forget (?) )>> ");
					gets(questions[line]);
					getchar();
					
					printf("Enter the new answer >> ");
					gets(answers[line]);
					getchar();
				} 
				else{
					printf("Error !! try again (y/n) >> ");
					r = getchar();
					getchar();
				}
			}while(r == 'y' && flag == 0);
			
			break;
	}
	getchar();
	printf("Do you want to modify another thing (y/n) >> ");
	a = getchar();
	}while(a == 'y');	
}

void sort (void){
		int i;
		
	 for (i=0;i<count_users-1;++i){
	    if (strcmp(lnames[i], lnames[i+1]) > 0){
	          //We swap the elements if the condition is satisfied
	 		swap_arr(lnames[i], lnames[i+1]);
    	}    
	}
}

void print_file (void){
	int j, i;
	
	sort();
	
	printf("\nSaving datas ...\n");
	output = fopen("output.txt","w");
	for(i=0;i<count_users-1;i++){
		protect_pass(passwords[i]);
		fprintf(output, "%s %s %s %s %ddhs %s? %s\n", usernames[i], fnames[i], lnames[i], passwords[i], balances[i], questions[i], answers[i]);
	}
	fclose(output);
	
	input = fopen("transactions.txt","w");
	for(j=0;j<count_transfer_line;j++){
			fprintf(input, "%s %s sent to %s %s ", fname_transfer_s[j], lname_transfer_s[j], fname_transfer_r[j], lname_transfer_r[j]);
			fprintf(input, "%d ", amount_transfer[j]);
			fprintf(input, "%s\n", str[j]);
	}
	fclose(input);
	
	
}
