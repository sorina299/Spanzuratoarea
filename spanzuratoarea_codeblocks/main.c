#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char* get_random_word (){

	srand(time(0));
	char* word = (char*)malloc( 20 * sizeof(char) );

	FILE *file;
	FILE *copy;
	file = fopen("cuvinte.txt", "r");
	copy = file;

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
	//rewind( file );
	file = fopen("cuvinte.txt", "r");
    if ( file == EOF ){
        printf("Nu s a resetat fisierul");
    }

	for( c = getc(file); c != EOF; c = getc(file) ){

        //printf("%c", c );

		if ( a == count ){
			// extragem cuvantul
			int i;
			word[0] = c;
			for( c = getc(file), i = 1 ; c != '\n'; c = getc(file), i++ ){
				word[i] = c;
                //printf("%c", c );
			}
			word[i+1] = '\0';
			fclose(file);
			//printf("%s", word);
//			for( int i = 0; word[i] != '\0'; i++ ){
//                printf("%d %c\t", word[i], word[i]);
//			}
//			printf("%d", word[i+1]);
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

char* generate_mask_string( char* word ){
    int length = strlen(word);
    int i;
    char* mask = malloc( ( length+1 ) * sizeof( char ) );
    for ( i = 0; i< length; i++ ){
        mask[i] = '*';
    }
    mask[i+1] = '\0';
    return mask;
}

char* reveal_mask_begging ( char* word, char* mask ){
    int length = strlen(word);
    mask[0] = word[0];
    mask[length] = word[length];
    return mask;
}

bool word_is_found( char* word, char* mask ){
    if ( strcmp ( word, mask) == 0){
        return true;
    }else{
        return false;
    }
}

bool check_letter ( char* word ){

}


int main(){

//	//printf("%s",get_random_word());
//	int i;
//	char* word = get_random_word();
//	for(  i = 0; word[i] != '\0'; i++ ){
//        printf("%d %c\t", word[i], word[i]);
//    }
//    printf("%d", word[i+1]);

	return 0;
}
