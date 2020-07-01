#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

#define LIVES 10

char* get_random_word (){

	srand(time(0));
	char* word; //= (char*)malloc( 20 * sizeof(char) );
    int length = 1;

	FILE *file;
	file = fopen("cuvinte.txt", "r");

	int count=0;
	char c;

	if (file == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    for (c = getc(file); c != EOF; c = getc(file)){
        if (c == '\n'){
            count = count + 1;
        }
    }

    fclose(file);

	int a = rand() % count;
	printf(" a=%d\t count=%d\n", a, count);

	count = 0;
	file = fopen("cuvinte.txt", "r");
    if ( file == EOF ){
        printf("Nu s a resetat fisierul");
    }

	for( c = getc(file); c != EOF; c = getc(file) ){

		if ( a == count ){
			int i;
			word = (char*)malloc( length * sizeof( char ));
			word[0] = c;
			for( c = getc(file), i = 1 ; c != '\n'; c = getc(file), i++ ){
                realloc ( word, ++length * sizeof ( char ) );
				word[i] = c;
			}
            realloc ( word, ++length * sizeof ( char ) );
			word[i+1] = '\0';
			fclose(file);
			return word;


		}

		if ( c == '\n' ){
			count++;
		}


	}

	fclose(file);
	printf("Exceptie: nu a gasit cuvantul pe care trebuia sa l returneze");
	return NULL;


}

char* mask_new( char* word ){
    int length = strlen(word);
    int i;
    char* mask = malloc( ( length+1 ) * sizeof( char ) );
    for ( i = 0; i< length; i++ ){
        mask[i] = '*';
    }
    mask[i+1] = '\0';
    return mask;
}

void mask_beggining_reveal ( char* word, char* mask ){
    int length = strlen(word);
    mask[0] = word[0];
    mask[length-1] = word[length-1];

}

bool word_is_found( char* word, char* mask ){
    if ( strcmp ( word, mask) == 0){
        return true;
    }else{
        return false;
    }
}

bool letter_check ( char* word, char* mask, char c ){
    for ( int i = 0; i < strlen(word); i++ ){
        if ( word[i] == c && mask[i] == '*' ){
            return true;
        }
    }
    return false;
}
//sorina
//s****a

void letter_reveal ( char* word, char* mask, char c  ){
    for ( int i = 0; i < strlen(word); i++ ){
        if ( word[i] == c && mask[i] == '*' ){
            mask[i] = c;
        }
    }
}

void game_print ( char* mask, int no_lives ){
    system(CLEAR_SCREEN);
    printf("\n");
    printf("word:");
    printf("\033[1;35m %s \033[0m", mask);
    printf("\t\t\tLIVES LEFT:%d", no_lives);
    printf("\n\nIntroduceti o litera:");
}

void game_play ( char* word, char* mask, int no_lives ){
    while ( true ){
        game_print( mask, no_lives );
        char c = getc(stdin); // reads the inserted letter
        getc(stdin); // reads new line character ( daca nu am folosi getc ar citi \n in loc de tasta introdusa de la tastatura la urmatorul ciclu )
        if ( letter_check( word, mask, c ) ){
            letter_reveal( word, mask, c );
        }else{
            no_lives--;
        }

        if ( no_lives == 0 ){
            system(CLEAR_SCREEN);
            printf("\033[1;31mAti pierdut:( \033[0m");

            return;
        }
        if ( word_is_found( word, mask ) ){
            system(CLEAR_SCREEN);
            printf("\033[1;32mAti castigat! \033[0m");
            return;
        }
    }
}

void game_initialize (){
    char* word = get_random_word();
    char* mask = mask_new( word );
    mask_beggining_reveal( word, mask );
    int no_lives = LIVES;

    game_play( word, mask, no_lives );
    printf("\nCuvantul este:%s", word);

    free( mask );
    free ( word );
}

int main(){

    game_initialize();

	return 0;
}
