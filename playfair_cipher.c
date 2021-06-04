#include <stdio.h>
#include <string.h>
#include <ctype.h>


void LowerCase(char plain[]);//convert uppercase texts to lowercase texts
int removeSpz(char* plain, int plainl);//remove all spaces in thr plaintext/cipher text
void CREATEKEYTABLE(char key[], int keyl, char keyg[5][5]);//create key table
void Find_char(char keyg[5][5], char a, char b, int arr[]);//find the position of the character
int mod5(int a);//find modulus of 5
int search_for_odd(char str[], int ptrs);// search whether the text length is odd if it is odd add a 'z' to the end
void encrypt(char str[], char keyg[5][5], int plainl);//algorithm for encrypt
void decrypt(char str[], char keyg[5][5], int plainl);//algorithm for decrypt
void encryption(char str[], char key[]);//basic processes before encrypting
void decryption(char str[], char key[]);//basic processes before decrypting

// Function to convert the PLAINTEXT/CIPHERTEXT to lowercase
void LowerCase(char plain[])
{
    strlwr(plain);
}

// Function to remove all spaces in a plaintext/ciphertext
int removeSpz(char* plain, int plainl)
{
	int i, count = 0;
	for (i = 0; i < plainl; i++)
		if (plain[i] != ' ')
			plain[count++] = plain[i];
	plain[count] = '\0';
	return count;
}

// Function to generate the 5x5 key table/grid
void CREATEKEYTABLE(char key[], int keyl, char keyg[5][5])//keyg mean keygrid
{
	int i, j, index, *dt;


	// to store count of the alphabet
	dt = (int*)calloc(26, sizeof(int));
	for (i = 0; i < keyl; i++) {
		if (key[i] != 'j')
			dt[key[i] - 97] = 2;
	}

	dt['j' - 97] = 1;

	i = 0;
	j = 0;

	for (index = 0; index < keyl; index++) {
		if (dt[key[index] - 97] == 2) {
			dt[key[index] - 97] -= 1;
			keyg[i][j] = key[index];
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}

	for (index = 0; index < 26; index++) {
		if (dt[index] == 0) {
			keyg[i][j] = (char)(index + 97);
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
}

// Function to search for the characters in the key square and return their position
void Find_char(char keyg[5][5], char a, char b, int arr[])
{
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';

	for (i = 0; i < 5; i++) {

		for (j = 0; j < 5; j++) {

			if (keyg[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyg[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}

// Function to find the modulus with 5
int mod5(int a)
{
	return (a % 5);
}

// Function to make the plain text length to be even
int search_for_odd(char str[], int ptrs)
{
	if (ptrs % 2 != 0) {
		str[ptrs++] = 'z';
		str[ptrs] = '\0';
	}
	return ptrs;
}

// Function for performing the encryption
void encrypt(char str[], char keyg[5][5], int plainl)
{
	int i, a[4];

	for (i = 0; i < plainl; i += 2) {

		Find_char(keyg, str[i], str[i + 1], a);

		if (a[0] == a[2]) {
			str[i] = keyg[a[0]][mod5(a[1] + 1)];
			str[i + 1] = keyg[a[0]][mod5(a[3] + 1)];
		}
		else if (a[1] == a[3]) {
			str[i] = keyg[mod5(a[0] + 1)][a[1]];
			str[i + 1] = keyg[mod5(a[2] + 1)][a[1]];
		}
		else {
			str[i] = keyg[a[0]][a[3]];
			str[i + 1] = keyg[a[2]][a[1]];
		}
	}
}

void decrypt(char str[], char keyg[5][5], int plainl)
{
    int i, a[4];
    for (i = 0; i < plainl; i += 2) {
        Find_char(keyg, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyg[a[0]][mod5(a[1] - 1)];
            str[i + 1] = keyg[a[0]][mod5(a[3] - 1)];
        }
        else if (a[1] == a[3]) {
            str[i] = keyg[mod5(a[0] - 1)][a[1]];
            str[i + 1] = keyg[mod5(a[2] - 1)][a[1]];
        }
        else {
            str[i] = keyg[a[0]][a[3]];
            str[i + 1] = keyg[a[2]][a[1]];
        }
    }
}


// Function to encrypt using Playfair Cipher
void encryption(char str[], char key[])
{
	char plainl, keyl, keyg[5][5];

	// Key
	keyl = strlen(key);
	keyl = removeSpz(key, keyl);
	LowerCase(key);

	// Plaintext
	plainl = strlen(str);
	LowerCase(str);
	plainl = removeSpz(str, plainl);

	plainl = search_for_odd(str, plainl);

	CREATEKEYTABLE(key, keyl, keyg);

	encrypt(str, keyg, plainl);
}

// Function to call decrypt
void decryption(char str[], char key[])
{
    char plainl, keyl, keyg[5][5];

    // Key
    keyl = strlen(key);
    keyl = removeSpz(key, keyl);
    LowerCase(key);

    // ciphertext
    plainl = strlen(str);
    LowerCase(str);
    plainl = removeSpz(str, plainl);

    CREATEKEYTABLE(key, keyl, keyg);

    decrypt(str, keyg, plainl);
}

int main()
{   char ar[5][5]={"MONAR","CHYBD","EFGIK","LPQST","UVWXZ"};
	char str[50], key[10];
	int i,j,n,p,exit=0;

	// Key
	strcpy(key, "Monarchy");

    while(exit==0){

	printf("Welcome To The PlaYfair Encyption & Decryption Programme!!! \n");
    printf("\n");
	printf("______INSTRUCTIONS FOR USING THE SERVICE_________ \n");
    printf("\n");
    printf("1] Simply select your preference according to decryption or encryption. \n");
    printf("2] Insert your plaintext.... \n");
    printf("3] Check the cyphertext.... \n");
    printf("\n");
    printf(">>>>>>>>Here the system is not allowed you to insert a key.<<<<<<<<<<< \n");
    printf("\n");
	printf("Key text that we are using is >> %s\n", key);
	printf("\n");



        for(i=0; i<5; i++)
        {
            for(j=0; j<5; j++)
            printf("%c ", ar[i][j]);
            printf("\n");
        }
        printf("\n");

    printf("Choose one of the following to continue\n");
	printf("	1)Encryption\n");
	printf("	2)Decryption\n");
	printf("Enter your choice : ");
	scanf("%d",&n);

	printf("Enter the Plaintext to be encrypted or decrypted:\n");
	scanf(" %[^\n]",&str);
	printf("Plain text/Cipher text entered: %s\n", str);


	if(n==1){
	encryption(str, key);
	printf("Cipher text: %s\n", str);

	}
	else{
	decryption(str, key);
	printf("Plain text: %s\n", str);

	}


	printf("Do you want to continue the programme? \n");
    printf("1]yes\n");
    printf("2]no \n");
    scanf("%d",&p);
    if(p==2){
        printf("Thank you for using our service!!! \n");
        exit=1;
    }
    }
	return 0;
}
