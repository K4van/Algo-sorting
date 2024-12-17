#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 200

typedef enum {
    NORMAL,
    FIGHTING,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    STEEL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCHIC,
    ICE,
    DRAGON,
    DARK,
    FAIRY
} pokemonType;

typedef struct {
    char name[51];
    int pokeID;
    char type[20];
    char weakness[20];
    char species[101];
    float height;
    float weight;
    char abilites[101];
} Pokemon;

const char* typeName(pokemonType type) {
    switch (type) {
        case NORMAL: return "Normal";
        case FIGHTING: return "Fighting";
        case FLYING: return "Flying";
        case POISON: return "Poison";
        case GROUND: return "Ground";
        case ROCK: return "Rock";
        case BUG: return "Bug";
        case GHOST: return "Ghost";
        case STEEL: return "Steel";
        case FIRE: return "Fire";
        case WATER: return "Water";
        case GRASS: return "Grass";
        case ELECTRIC: return "Electric";
        case PSYCHIC: return "Psychic";
        case ICE: return "Ice";
        case DRAGON: return "Dragon";
        case DARK: return "Dark";
        case FAIRY: return "Fairy";
    }
    return "Unknown";
}

Pokemon poke[MAX];
int size;

int equalID(int id){
    Pokemon p[MAX];
    FILE *fp = fopen("pokemon.txt", "r");
    int c = 0;
    while(fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n", p[c].name, &p[c].pokeID, p[c].type, p[c].weakness, p[c].species, &p[c].height, &p[c].weight, p[c].abilites) != EOF) {
        c++;
    }
    fclose(fp);
    for(int i = 0; i < c; i++){
        if(p[i].pokeID == id) return 0;
    }
    return 1;
}
void clearScreen() {
    printf("\e[1;1H\e[2J");
}

void removeID(int id) {
    FILE *fp = fopen("pokemon.txt", "r");
    FILE *fp2 = fopen("temp.txt", "a");
    Pokemon p[MAX];
    if (fp == NULL){
        printf("File not found"); getchar();
        return;
    } 
    else if(fp2 == NULL) {
        printf("File not found"); getchar();
        return;
    }
    int c = 0;
    while(fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n", p[c].name, &p[c].pokeID, p[c].type, p[c].weakness, p[c].species, &p[c].height, &p[c].weight, p[c].abilites) != EOF) {
        c++;
    }
    fclose(fp);
    for(int i = 0; i < c; i++){
    if(p[i].pokeID != id) {
        fprintf(fp2, "%s#%d#%s#%s#%s#%0.1f#%0.1f#%s\n", p[i].name, p[i].pokeID, p[i].type, p[i].weakness, p[i].species, p[i].height, p[i].weight, p[i].abilites);
    }
}
    fclose(fp2);
    remove("pokemon.txt");
    rename("temp.txt", "pokemon.txt");
    
}
void printPokemon(Pokemon *pokemons, int count) {
    printf("+-------+----------------------+----------+-----------------+-----------------------+--------+--------+----------------------------+\n");
    printf("| ID    |Name                  | Type     | Weakness        | Species               | Height | Weight | Abilities                  |\n");
    printf("+-------+----------------------+----------+-----------------+-----------------------+--------+--------+----------------------------+\n");
    for (int i = 0; i < count; i++) {
        printf("| #%04d | %-20s | %-8s | %-15s | %-21s | %-6.1f | %-6.1f | %-26s |\n",
               pokemons[i].pokeID,
               pokemons[i].name,
               pokemons[i].type,
               pokemons[i].weakness,
               pokemons[i].species,
               pokemons[i].height,
               pokemons[i].weight,
               pokemons[i].abilites);
    }
    printf("+-------+----------------------+----------+-----------------+-----------------------+--------+--------+----------------------------+\n");
}


int validateType(const char* type){
    if (strcasecmp(type, "Normal") == 0) return 1;
    if (strcasecmp(type, "Fighting") == 0) return 1;
    if (strcasecmp(type, "Flying") == 0) return 1;
    if (strcasecmp(type, "Poison") == 0) return 1;
    if (strcasecmp(type, "Ground") == 0) return 1;
    if (strcasecmp(type, "Rock") == 0) return 1;
    if (strcasecmp(type, "Bug") == 0) return 1;
    if (strcasecmp(type, "Ghost") == 0) return 1;
    if (strcasecmp(type, "Steel") == 0) return 1;
    if (strcasecmp(type, "Fire") == 0) return 1;
    if (strcasecmp(type, "Water") == 0) return 1;
    if (strcasecmp(type, "Grass") == 0) return 1;
    if (strcasecmp(type, "Electric") == 0) return 1;
    if (strcasecmp(type, "Psychic") == 0) return 1;
    if (strcasecmp(type, "Ice") == 0) return 1;
    if (strcasecmp(type, "Dragon") == 0) return 1;
    if (strcasecmp(type, "Dark") == 0) return 1;
    if (strcasecmp(type, "Fairy") == 0) return 1;
    return 0;
}

int validateSpecies(const char* species){
    int idx = 0;
    char temp[51];
    for(int i = 0; i<=strlen(species); i++){
        if(species[i] == ' '||species[i] == '\0'){
            idx = 0;
        }
        else {
            temp[idx] = species[i];
            idx++;
        }
    }
    if (strcasecmp(temp, "Pokemon") == 0) return 1;
    return 0;
}
void writePokemon(){
    FILE *fp = fopen("pokemon.txt", "a");
    if(fp == NULL){
        printf("File not foung"); getchar();
        return;
    }
    char pokemonName[51];
    int pokemonID;
    char pokemonType[20];
    char pokemonWeakness[20];
    char pokemonSpecies[101];
    float pokemonHeight;
    float pokemonWeight;
    char pokemonAbility[101];
    int t = 0;
    int verified = 0;
 do {
        printf("Insert Pokemon's name (Pokemon name must be at least 3 characters, type \"exit\" to exit): ");
        scanf("%[^\n]", pokemonName); getchar();
        int hasNumber = 0;
        if(strcasecmp(pokemonName, "exit") == 0) return;
        for (int i = 0; i < strlen(pokemonName); i++) {
            if (pokemonName[i] >= '0' && pokemonName[i] <= '9') {
                hasNumber = 1;
                break;
            }
        }

        if (strlen(pokemonName) < 3 && hasNumber) {
            clearScreen();
            printf("Pokemon's name must not contain number and at least 3 characters\n");
            t=1;
        } else if (strlen(pokemonName) < 3) {
            clearScreen();
            printf("Pokemon's name must be at least 3 characters\n");
            t=1;
        } else if (hasNumber) {
            clearScreen();
            printf("Pokemon's name must not contain numbers\n");
            t=1;
        }
        else t=0;

    } while (t == 1);
    
    do{
        printf("Insert Pokemon's ID(ID must at least 1-9999): ");
        scanf("%d", &pokemonID); getchar();
        if((pokemonID < 1 || pokemonID > 9999) || pokemonID < 0){
            clearScreen();
            printf("Pokemon's ID must be around 1-9999\n");
            t=1;
        }
        else{
            if(!equalID(pokemonID)){
                clearScreen();
                printf("Pokemon's ID already exist\n"); 
                t=1;
            }
            else t =0;
        } 
    }while (t==1);
    
    do{
   printf("Insert Pokemon's type: ");
    scanf("%[^\n]", pokemonType); getchar();
    if(!validateType(pokemonType)){
        clearScreen();
        printf("Invalid pokemon's type\n");
        t = 1;
    }
    else{
    if (strcasecmp(pokemonType, "Normal") == 0) strcpy(pokemonType, "Normal");
    if (strcasecmp(pokemonType, "Fighting") == 0) strcpy(pokemonType, "Fighting");
    if (strcasecmp(pokemonType, "Flying") == 0) strcpy(pokemonType, "Flying");
    if (strcasecmp(pokemonType, "Poison") == 0) strcpy(pokemonType, "Poison");
    if (strcasecmp(pokemonType, "Ground") == 0) strcpy(pokemonType, "Ground");
    if (strcasecmp(pokemonType, "Rock") == 0) strcpy(pokemonType, "Rock");
    if (strcasecmp(pokemonType, "Bug") == 0) strcpy(pokemonType, "Bug");
    if (strcasecmp(pokemonType, "Ghost") == 0) strcpy(pokemonType, "Ghost");
    if (strcasecmp(pokemonType, "Steel") == 0) strcpy(pokemonType, "Steel");
    if (strcasecmp(pokemonType, "Fire") == 0) strcpy(pokemonType, "Fire");
    if (strcasecmp(pokemonType, "Water") == 0) strcpy(pokemonType, "Water");
    if (strcasecmp(pokemonType, "Grass") == 0) strcpy(pokemonType, "Grass");
    if (strcasecmp(pokemonType, "Electric") == 0) strcpy(pokemonType, "Electric");
    if (strcasecmp(pokemonType, "Psychic") == 0) strcpy(pokemonType, "Psychic");
    if (strcasecmp(pokemonType, "Ice") == 0) strcpy(pokemonType, "Ice");
    if (strcasecmp(pokemonType, "Dragon") == 0) strcpy(pokemonType, "Dragon");
    if (strcasecmp(pokemonType, "Dark") == 0) strcpy(pokemonType, "Dark");
    if (strcasecmp(pokemonType, "Fairy") == 0) strcpy(pokemonType, "Fairy");
    t=0;
    }
    }while(t==1);

    do{
    printf("Insert Pokemon's weakness: ");
    scanf("%[^\n]", pokemonWeakness); getchar();
    if(!validateType(pokemonWeakness)){
        clearScreen();
        printf("Invalid pokemon's weakness type\n");
        t = 1;
    }
    else{
    if (strcasecmp(pokemonWeakness, "Normal") == 0) strcpy(pokemonWeakness, "Normal");
    if (strcasecmp(pokemonWeakness, "Fighting") == 0) strcpy(pokemonWeakness, "Fighting");
    if (strcasecmp(pokemonWeakness, "Flying") == 0) strcpy(pokemonWeakness, "Flying");
    if (strcasecmp(pokemonWeakness, "Poison") == 0) strcpy(pokemonWeakness, "Poison");
    if (strcasecmp(pokemonWeakness, "Ground") == 0) strcpy(pokemonWeakness, "Ground");
    if (strcasecmp(pokemonWeakness, "Rock") == 0) strcpy(pokemonWeakness, "Rock");
    if (strcasecmp(pokemonWeakness, "Bug") == 0) strcpy(pokemonWeakness, "Bug");
    if (strcasecmp(pokemonWeakness, "Ghost") == 0) strcpy(pokemonWeakness, "Ghost");
    if (strcasecmp(pokemonWeakness, "Steel") == 0) strcpy(pokemonWeakness, "Steel");
    if (strcasecmp(pokemonWeakness, "Fire") == 0) strcpy(pokemonWeakness, "Fire");
    if (strcasecmp(pokemonWeakness, "Water") == 0) strcpy(pokemonWeakness, "Water");
    if (strcasecmp(pokemonWeakness, "Grass") == 0) strcpy(pokemonWeakness, "Grass");
    if (strcasecmp(pokemonWeakness, "Electric") == 0) strcpy(pokemonWeakness, "Electric");
    if (strcasecmp(pokemonWeakness, "Psychic") == 0) strcpy(pokemonWeakness, "Psychic");
    if (strcasecmp(pokemonWeakness, "Ice") == 0) strcpy(pokemonWeakness, "Ice");
    if (strcasecmp(pokemonWeakness, "Dragon") == 0) strcpy(pokemonWeakness, "Dragon");
    if (strcasecmp(pokemonWeakness, "Dark") == 0) strcpy(pokemonWeakness, "Dark");
    if (strcasecmp(pokemonWeakness, "Fairy") == 0) strcpy(pokemonWeakness, "Fairy");
    t=0;
    }
    }while(t==1);

    do{
    printf("Insert Pokemon's species: ");
    scanf("%[^\n]", pokemonSpecies); getchar();
    int len = strlen(pokemonSpecies);
    for(int i = 0; i < len; i++){
        if(pokemonSpecies[i] >= '0' && pokemonSpecies[i] <= '9'){
            clearScreen();
            printf("Pokemon's species can't contain numbers\n");
            t = 1;
        }
        else t =0;
     }
     if(!t)strcat(pokemonSpecies, " Pokemon");
    }while(t==1);   

    do{
    printf("Insert Pokemon's height: ");
    scanf("%f", &pokemonHeight); getchar();
    if(pokemonHeight <= 0){
        clearScreen();
        printf("Pokemon's height must above 0\n");
        t = 1;
    }
    else t = 0;
    }while(t==1);
    
    do{
        printf("Insert Pokemon's weight: ");
        scanf("%f", &pokemonWeight); getchar();
        if(pokemonWeight <= 0){
            clearScreen();
            printf("Pokemon's weight must above 0\n");
            t = 1;
        }
        else t = 0;
    }while(t==1);

    do{
    printf("Insert Pokemon's abilities: ");
    scanf("%[^\n]", pokemonAbility); getchar();
    int len = strlen(pokemonAbility);
    for(int i = 0; i < len; i++){
        if(pokemonAbility[i] >= '0' && pokemonAbility[i] <= '9'){
            clearScreen();
            printf("Pokemon's species can't contain numbers\n");
            t = 1;
        }
        else t =0;
    }

    }while(t==1);
    clearScreen();
    verified = 1;
    if(verified){
        fprintf(fp, "%s#%d#%s#%s#%s#%0.1f#%0.1f#%s\n", pokemonName, pokemonID, pokemonType, pokemonWeakness, pokemonSpecies, pokemonHeight, pokemonWeight, pokemonAbility);
        printf("Pokemon added!\n"); getchar();
    }
    else printf("Error while adding pokemon\n");verified = 0; 
    fclose(fp);
}

void pokemonList() {
    FILE *fp = fopen("pokemon.txt", "r");
    if (fp == NULL) {
        printf("File not found");
        return;
    }
    int c = 0;
    while (fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n", poke[c].name, &poke[c].pokeID, poke[c].type, poke[c].weakness, poke[c].species, &poke[c].height, &poke[c].weight, poke[c].abilites) != EOF) {
        c++;
    }
    fclose(fp);
    size = c;
}

void sortedPokemon(){
    FILE *fp = fopen("sortedPokemon.txt", "w");
    for(int i = 0; i < size; i++){
        fprintf(fp, "%s#%d#%s#%s#%s#%0.1f#%0.1f#%s\n", poke[i].name, poke[i].pokeID, poke[i].type, poke[i].weakness, poke[i].species, poke[i].height, poke[i].weight, poke[i].abilites);
    }
    fclose(fp);
}

void linearSearch(int mode){
    Pokemon temp;
    int id;
    int c=0;
    int found = 0;
    FILE *fp;
    clearScreen();
    puts("Insert a Pokemon ID: ");
    scanf("%d", &id);getchar();
    if(mode == 1) fp = fopen("sortedPokemon.txt", "r");
    else if(mode == 2) fp = fopen("pokemon.txt", "r");
    else {
        printf("Invalid"); getchar();
    }

    while(fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n", temp.name, &temp.pokeID, temp.type, temp.weakness, temp.species, &temp.height, &temp.weight, temp.abilites) != EOF){
        if(temp.pokeID == id){
            printf("Pokemon with ID %d and called %s found on index %d", id, temp.name, c+1); getchar();
            found = 1;
            break;
        }
        c++;
    }

    if(!found){
        printf("Pokemon with ID %d not found", id); getchar();
    }

    fclose(fp);
}

void binarySearch(int mode) {
    FILE *fp;
    Pokemon poke[MAX];
    int id, found = 0;

    clearScreen();
    puts("Insert a Pokemon ID: ");
    scanf("%d", &id); getchar();

    if (mode == 1) fp = fopen("sortedPokemon.txt", "r");
    else if (mode == 2) fp = fopen("pokemon.txt", "r");
    else {
        printf("Invalid"); getchar();
        return;
    }

    int n = 0;
    while (fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n",
                  poke[n].name, &poke[n].pokeID, poke[n].type, poke[n].weakness,
                  poke[n].species, &poke[n].height, &poke[n].weight, poke[n].abilites) != EOF) {
        n++;
    }
    fclose(fp);

    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (poke[mid].pokeID == id) {
            printf("Pokemon with ID %d and called %s found at index %d\n", id, poke[mid].name, mid + 1);
            found = 1;
            break;
        }
        if (poke[mid].pokeID < id) left = mid + 1;
        else right = mid - 1;
    }

    if (!found) printf("Pokemon with ID %d not found(maybe try to sort the data by ID first)\n", id);
    getchar();
}

void interpolationSearch(int mode) {
    FILE *fp;
    Pokemon poke[MAX];
    int id, found = 0;

    clearScreen();
    puts("Insert a Pokemon ID: ");
    scanf("%d", &id); getchar();

    if (mode == 1) fp = fopen("sortedPokemon.txt", "r");
    else if (mode == 2) fp = fopen("pokemon.txt", "r");
    else {
        printf("Invalid"); getchar();
        return;
    }

    int n = 0;
    while (fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n",
                  poke[n].name, &poke[n].pokeID, poke[n].type, poke[n].weakness,
                  poke[n].species, &poke[n].height, &poke[n].weight, poke[n].abilites) != EOF) {
        n++;
    }
    fclose(fp);

    int left = 0, right = n - 1, pos;
    while (left <= right && id >= poke[left].pokeID && id <= poke[right].pokeID) {
        pos = left + ((id - poke[left].pokeID) * (right - left)) / 
                     (poke[right].pokeID - poke[left].pokeID);

        if (poke[pos].pokeID == id) {
            printf("Pokemon with ID %d and called %s found at index %d\n", id, poke[pos].name, pos + 1);
            found = 1;
            break;
        }

        if (poke[pos].pokeID < id) left = pos + 1;
        else right = pos - 1;
    }

    if (!found) printf("Pokemon with ID %d not found(maybe try to sort the data by ID first)\n", id);
    getchar();
}

void searching(){
    int mode;
    int t = 0;
    int select;
    do{
    clearScreen();
    puts("Are the data sorted?\n1. Yes\n2. No\n3. Exit\n>> ");
    scanf("%d", &mode); getchar();
    if(mode <1 || mode > 3) {
        printf("Invalid"); 
        t =1;
        getchar();

    }
    else if(mode == 3) return;
    else t = 0;
    }while (t==1);
    clearScreen();
    puts("Choose searching method.\n1. Linear Search\n2. Binary Search\n3. Interpolation Search\n>> ");
    scanf("%d", &select);getchar();
    if(select == 1) linearSearch(mode);
    else if(select == 2) binarySearch(mode);
    else if(select == 3) interpolationSearch(mode);
}
char select[21];
void bubbleSort(Pokemon p[], int size){
    Pokemon temp;
    if(strcasecmp(select, "ID") == 0){
        for(int i = 0; i < size-1; i++){
            for(int j = 0; j < size-i-1; j++){
                if(poke[j].pokeID > poke[j+1].pokeID){
                    temp = poke[j];
                    poke[j] = poke[j+1];
                    poke[j+1] = temp;
                }
            }
        }
    }
    else if(strcasecmp(select, "name") == 0){
        for(int i = 0; i < size-1; i++){
            for(int j = 0; j < size-i-1; j++){
                if(strcmp(poke[j].name, poke[j+1].name) > 0){
                    temp = poke[j];
                    poke[j] = poke[j+1];
                    poke[j+1] = temp;
                }
            }
        }
    }
    else return;
    sortedPokemon();
    printf("Pokemon list sorted!\n"); getchar();
}

void selectionSort(Pokemon p[], int size) {
    Pokemon temp;
    if (strcasecmp(select, "ID") == 0) {
        for (int i = 0; i < size - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < size; j++) {
                if (p[j].pokeID < p[minIdx].pokeID) {
                    minIdx = j;
                }
            }
            temp = p[minIdx];
            p[minIdx] = p[i];
            p[i] = temp;
        }
    } else if (strcasecmp(select, "name") == 0) {
        for (int i = 0; i < size - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < size; j++) {
                if (strcmp(p[j].name, p[minIdx].name) < 0) {
                    minIdx = j;
                }
            }
            temp = p[minIdx];
            p[minIdx] = p[i];
            p[i] = temp;
        }
    }
    sortedPokemon();
    printf("Pokemon list sorted!\n");
    getchar();
}

void insertionSort(Pokemon p[], int size) {
    Pokemon key;
    int j;

    if (strcasecmp(select, "ID") == 0) {
        for (int i = 1; i < size; i++) {
            key = p[i];
            j = i - 1;

            while (j >= 0 && p[j].pokeID > key.pokeID) {
                p[j + 1] = p[j];
                j--;
            }
            p[j + 1] = key;
        }
    } else if (strcasecmp(select, "name") == 0) {
        for (int i = 1; i < size; i++) {
            key = p[i];
            j = i - 1;

            while (j >= 0 && strcmp(p[j].name, key.name) > 0) {
                p[j + 1] = p[j];
                j--;
            }
            p[j + 1] = key;
        }
    }
    sortedPokemon();
    printf("Pokemon list sorted!\n");
    getchar();
}

void merge(Pokemon p[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pokemon L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = p[left + i];
    for (int i = 0; i < n2; i++) R[i] = p[mid + 1 + i];

    int i = 0, j = 0, k = left;

    if (strcasecmp(select, "ID") == 0) {
        while (i < n1 && j < n2) {
            if (L[i].pokeID <= R[j].pokeID) p[k++] = L[i++];
            else p[k++] = R[j++];
        }
    } else if (strcasecmp(select, "name") == 0) {
        while (i < n1 && j < n2) {
            if (strcmp(L[i].name, R[j].name) <= 0) p[k++] = L[i++];
            else p[k++] = R[j++];
        }
    }

    while (i < n1) p[k++] = L[i++];
    while (j < n2) p[k++] = R[j++];
}

void mergeSort(Pokemon p[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(p, left, mid);
        mergeSort(p, mid + 1, right);
        merge(p, left, mid, right);
    }
    sortedPokemon();
}

int partition(Pokemon p[], int low, int high) {
    Pokemon pivot = p[high];
    int i = low - 1;

    if (strcasecmp(select, "ID") == 0) {
        for (int j = low; j < high; j++) {
            if (p[j].pokeID <= pivot.pokeID) {
                i++;
                Pokemon temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    } else if (strcasecmp(select, "name") == 0) {
        for (int j = low; j < high; j++) {
            if (strcmp(p[j].name, pivot.name) <= 0) {
                i++;
                Pokemon temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    Pokemon temp = p[i + 1];
    p[i + 1] = p[high];
    p[high] = temp;

    return i + 1;
}

void quickSort(Pokemon p[], int low, int high) {
    if (low < high) {
        int pi = partition(p, low, high);

        quickSort(p, low, pi - 1);
        quickSort(p, pi + 1, high);
    }
    sortedPokemon();
}

void sorting(){
    int t=0;
    pokemonList();
   do {
        clearScreen();
        puts("Which category do you want to sort(By ID or by name? Type \"exit\" to exit)");
        printf(">> ");
        scanf("%[^\n]", select);
        getchar();
        if(strcasecmp(select,"exit")==0){
            return;
        }
        else if (strcasecmp(select, "ID") != 0 && strcasecmp(select, "name") != 0) {
            printf("Invalid");getchar();
            t = 1;
        }
        else t = 0;
    } while (t == 1);
   
   do{
    int c;
    clearScreen();
    puts("Choose a sorting method: ");
    puts("1. Bubble Sort");
    puts("2. Selection Sort");
    puts("3. Insertion Sort");
    puts("4. Merge Sort");
    puts("5. Quick Sort");
    puts("6. Exit");
    printf(">> ");
    scanf("%d", &c);getchar();
    switch(c){
        case 1:
            bubbleSort(poke, size);
            break;
        case 2:
            selectionSort(poke, size);
            break;
        case 3:
            insertionSort(poke, size);
            break;
        case 4:
            mergeSort(poke, 0, size - 1);
            printf("Pokemon list sorted!\n"); getchar();
            break;
        case 5:
            quickSort(poke, 0, size - 1);
            printf("Pokemon list sorted!\n"); getchar();
            break;
        case 6:
            return;
        default:
            printf("Invalid");getchar();
            t = 1;
    }
   }while (t == 1);
    
}

int main() {
    int choice;
    do {
        clearScreen();
        printf("Welcome to pokeLite123\n");
        printf("1. Show pokemon list\n");
        printf("2. Edit pokemon list\n");
        printf("3. Sort pokemon\n");
        printf("4. Search pokemon\n");
        printf("5. Quit\n");
        printf(">> ");
        int t;
        do{
            scanf("%d", &choice); getchar();
            if (choice >= '0' || choice <= '9') {
                continue;
            }
            else t = 1;   
        }while(t == 1);
        switch (choice) {
            case 1:
            pokemonList();
            int select;
            do {
                clearScreen();
                puts("1. Show all");
                puts("2. Show type specific");
                puts("3. Exit");
                printf(">>");
                 do{
                     scanf("%d", &select); getchar();
                      if (select >= '0' || select <= '9') {
                     continue;
                      }
                    else t = 1;
                }while(t == 1);
                switch(select){
                    case 1: 
                        clearScreen();
                        printPokemon(poke, size);
                        getchar();
                     break;
                    case 2: {
                        char element[20];
                        Pokemon filteredPokemons[MAX];
                        int found = 0; 
                        int size2 = 0; 

                        printf("Insert what element type of Pokémon(type \"exit\" for exit): ");
                        scanf("%s", element);
                        getchar();
                        if(strcasecmp(element, "exit") == 0) break;
                        clearScreen();

                        for (int i = 0; i < size; i++) {
                            if (strcasecmp(element, poke[i].type) == 0) {
                                filteredPokemons[size2++] = poke[i];
                                found = 1;
                            }
                        }

                        if (found) {
                            printPokemon(filteredPokemons, size2); 
                        } else {
                            printf("No Pokémon found with type %s.\n", element);
                        }

                        getchar();
                        break;
                    }
                    break;
                    case 3:
                    break;
                    default:
                    printf("Invalid"); getchar();
                    break;
                     }
            }while (select !=3);
            break;
            case 2:
                int select2;
                do{
                    clearScreen();
                    puts("1. Add Pokemon");
                    puts("2. Remove Pokemon");
                    puts("3. Exit");
                    printf(">>");
                    do{
                     scanf("%d", &select2); getchar();
                      if (select2 >= '0' || select2 <= '9') {
                     continue;
                      }
                    else t = 1;
                }while(t == 1);
                    switch(select2){
                        case 1:
                        clearScreen();
                        writePokemon();
                        break;
                        case 2:
                        char select3[5];
                        int t = 0;
                        do{
                            clearScreen();
                            puts("Insert an ID(type \"exit\" for exit): ");
                            printf(">>");
                            scanf("%s", select3); getchar();
                            if (strcasecmp(select3, "exit") == 0) break;
                            int id = atoi(select3);
                            if(id<1 || id>9999) {
                                printf("Invalid ID"); getchar();
                                t = 1;
                            }
                            else{
                                if(equalID(id) == 0) {
                                removeID(id);
                                printf("Pokemon removed"); getchar();
                                }
                                else{
                                    printf("ID not found"); getchar();
                                    t = 1;
                                } 
                            }
                        }while(t == 1);
                        break;
                        case 3:
                        break;
                        default:
                        printf("Invalid"); getchar();
                        break;
                 }
                }while(select2 != 3);
            break;
            case 3:
            clearScreen();
            sorting();
            break;
            case 4:
            clearScreen();
            searching();
            break;
            case 5:
            break;
            default:
            printf("Invalid"); getchar();
            break;
            }
    }while (choice != 5);
    return 0;
}
