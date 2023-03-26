// Pbuffer Bytes : 1-4 = call;
//                 5-14 = Nome para ser buscado;
//                 15-24 = Nome;
//                 25-28 = Idade;
//                 29-32 = Telefone;
//                 33-36 = Previous address // if sizeof(void *) = 4
//                 37-40 = Next address // if sizeof(void *) = 4


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERSON_SIZE (sizeof(char) * 10 + sizeof(int) * 2 + sizeof(void *) * 2)



int *AdicionarPessoa(void *p);
void ListarPessoas();
void BuscarPessoa(void *p);
char *RemoverPessoa(void *p);


char *pFirst; // Aponta para a primeira pessoa na ordem alfabética
char *pLast; // Aponta para a ultima pessoa na ordem alfabética
int *call; // call = quantidade de pessoas



int main(){

    void *pBuffer = NULL;
    int *esc = (int *)malloc(sizeof(int));

    while (1){
        do{
            printf("\n");
            printf("1- Adicionar\n");
            printf("2- Remover\n");
            printf("3- Buscar\n");
            printf("4- Listar\n");
            printf("5- Sair\n");
            printf("Digite sua escolha: ");
            scanf("%d", esc);
        }while (*esc < 1 || *esc > 5);
        switch (*esc){
        case 1:
            pBuffer = AdicionarPessoa(pBuffer);
            break;
        case 2:
            pBuffer = RemoverPessoa(pBuffer);
            break;
        case 3:
            BuscarPessoa(pBuffer);
            break;
        case 4:
            ListarPessoas();
            break;
        case 5:
            free(pBuffer);
            free(esc);
            return 0;
            break;
        }
    }

}


int *AdicionarPessoa(void *p){

    char *currentName;
    char *lowestName;
    void *begin;
    void *end;
    void *slowBegin;
    void *tmpBegin;
    void *constantBegin;
    void *tmpConstantBegin;
    void *checkIfUsed;
    void *pointersToNull;
    void *nextpFirst;


    if (p == NULL){
        p = (int *)malloc( sizeof(int) + (sizeof(char) * 10) + PERSON_SIZE);
        call = p;
        *call = 1;
        p += sizeof(int);
        p += sizeof(char) * 10;
        printf("Nome: ");
        scanf("%s", (char *)p);
        p += sizeof(char) * 10;
        printf("Idade: "); 
        scanf("%d", (int *)p);
        p += sizeof(int);
        printf("Telefone: ");
        scanf("%d", (int *)p);
        p += sizeof(void *);
        *(int *)p = 0; // Previous address = NULL
        p += sizeof(void *);
        *(int *)p = 0; // Next address = NULL
        p -= (sizeof(char) * 10) + PERSON_SIZE;
        pFirst = p;
        pFirst += sizeof(int) + sizeof(char) * 10;
        pLast = p;
        pLast += sizeof(int) + sizeof(char) * 10;
        return p;
    }
    else{
        p = (int *)realloc(p, ( sizeof(int) + (sizeof(char) * 10) + ( PERSON_SIZE * (*call + 1) ) ));
        call = p;
        *call += 1;
        p += sizeof(int);
        p += sizeof(char) * 10;
        begin = p;
        constantBegin = p;
        tmpConstantBegin = p;
        pointersToNull = p;
        begin += PERSON_SIZE;
        slowBegin = begin;
        slowBegin += PERSON_SIZE; // Points to the 3rd person to finish the loop later, if theres no 3rd person, just point to trash values, no problem cause its not gonna be used in call = 2 case
        tmpBegin = begin;
        lowestName = p;
        currentName = p;
        currentName += PERSON_SIZE; // Points to the second name
        p += ( PERSON_SIZE ) * (*call - 1);
        printf("Nome: ");
        scanf("%s", (char *)p);
        p += sizeof(char) * 10;
        printf("Idade: "); 
        scanf("%d", (int *)p);
        p += sizeof(int);
        printf("Telefone: ");
        scanf("%d", (int *)p);
        p += sizeof(void *);
        *(int *)p = 0; // Previous address = NULL
        p += sizeof(void *);
        *(int *)p = 0; // Next address = NULL
        end = p;
        end += sizeof(int);

        while (pointersToNull != end){ // Setting every pointer to null
            pointersToNull += sizeof(char) * 10 + sizeof(int) + sizeof(int);
            *(int *)pointersToNull = 0;
            pointersToNull += sizeof(void *);
            *(int *)pointersToNull = 0;
            pointersToNull += sizeof(void *);
        }

        while (begin != end){ // Loop to find the lowest name
            if (strcmp(lowestName, currentName) == 1){
                lowestName = currentName;
            }
            begin += PERSON_SIZE;
            currentName += PERSON_SIZE;
        }
        pFirst = lowestName;

        if (*call == 2){
            if (constantBegin == pFirst){ // Two names were added in the right order
                pFirst += sizeof(char) * 10 + sizeof(int) + sizeof(int);
                *(int *)pFirst = 0; // Prev address = NULL
                pFirst += sizeof(void *);
                constantBegin += PERSON_SIZE;
                *(int *)pFirst = (int)constantBegin; // Next address = next person address
                pFirst -= sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
                constantBegin += sizeof(char) * 10 + sizeof(int) + sizeof(int);
                *(int *)constantBegin = (int)pFirst;
                constantBegin -= sizeof(char) * 10 + sizeof(int) + sizeof(int);
                pLast = constantBegin;

            }
            else{
                pFirst += sizeof(char) * 10 + sizeof(int) + sizeof(int);
                *(int *)pFirst = 0; // Prev address = NULL
                pFirst += sizeof(void *);
                *(int *)pFirst = (int)constantBegin; // Next address = next person address
                pFirst -= sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
                constantBegin += sizeof(char) * 10 + sizeof(int) + sizeof(int);
                *(int *)constantBegin = (int)pFirst; // Prev address = previous person address
                constantBegin -= sizeof(char) * 10 + sizeof(int) + sizeof(int);    
                pLast = constantBegin;         
            }
        }
        else{
            if (constantBegin == pFirst){ // if first name added is the lowest name, new lowest name is the second one
                lowestName = constantBegin;
                lowestName += PERSON_SIZE;
                begin = slowBegin;
            }
            else{
                lowestName = constantBegin;
                begin = slowBegin;
                begin -= PERSON_SIZE;
                tmpBegin -= PERSON_SIZE;
            }
            currentName = lowestName;
            currentName += PERSON_SIZE;
            checkIfUsed = lowestName;
            checkIfUsed += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
            nextpFirst = pFirst;

            while (slowBegin != end){ // Fixing everyone's pointers
                while (begin != end){
                    if (*(int *)checkIfUsed == 0 && pFirst != currentName){ // Skip if name has been seen already
                        if (strcmp(lowestName, currentName) == 1){
                            lowestName = currentName;
                        }
                        begin += PERSON_SIZE;
                        currentName += PERSON_SIZE;
                        checkIfUsed += PERSON_SIZE;
                    }
                    else{
                        begin += PERSON_SIZE;
                        currentName += PERSON_SIZE;
                        checkIfUsed += PERSON_SIZE;
                    }
                }
                slowBegin += PERSON_SIZE;

                nextpFirst += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
                *(int *)nextpFirst = (int)lowestName; // next address gets next person's address
                nextpFirst -= sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
                lowestName += sizeof(char) * 10 + sizeof(int) + sizeof(int);
                *(int *)lowestName = (int)nextpFirst; // prev address of the next person gets prev person's address
                lowestName += sizeof(void *);
                *(int *)lowestName = 999; // Placeholder so it doenst equal null, so we can later find where it should point to;
                lowestName -= sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
                nextpFirst = lowestName;

                while (tmpConstantBegin != end){ // Loop to find the first lowest name that hasn't been seen
                    tmpConstantBegin += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
                    if (*(int *)tmpConstantBegin == 0){
                        lowestName = tmpConstantBegin;
                        lowestName -= sizeof(void *) + sizeof(int) + sizeof(int) + sizeof(char) * 10;
                        break;
                    }
                    tmpConstantBegin += sizeof(void *);
                }

                tmpConstantBegin = constantBegin;
                currentName = constantBegin;
                begin = currentName;
                checkIfUsed = currentName;
                checkIfUsed += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
            }

            // Here fix the last person pointer, loop to find it if next = null, thats the last person
            while (constantBegin != end){
                constantBegin += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
                if (*(int *)constantBegin == 0){
                    lowestName = constantBegin;
                    lowestName -= sizeof(void *) + sizeof(int) + sizeof(int) + sizeof(char) * 10;
                    break;
                }
                constantBegin += sizeof(void *);
            }

            nextpFirst += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
            *(int *)nextpFirst = (int)lowestName; // next address gets next person's address
            nextpFirst -= sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
            lowestName += sizeof(char) * 10 + sizeof(int) + sizeof(int);
            *(int *)lowestName = (int)nextpFirst; // prev address of the next person gets prev person's address
            lowestName -= sizeof(char) * 10 + sizeof(int) + sizeof(int);
            nextpFirst = lowestName;
            pLast = nextpFirst;

        }

        p -= ( (sizeof(char) * 10) + PERSON_SIZE );
        p -= ( PERSON_SIZE) * (*call - 1);
        return p;
    }
}


void ListarPessoas(){

    if (pFirst == NULL){
        printf("\nNao ha ninguem para ser listado\n");
        return;
    }

    void **tracer;
    void *start;
    start = pFirst;
    void *check = start;

    while (start != NULL){
        check += sizeof(char) * 10;
        if (*(int *)check != 9999){ // Skip flagged names
            printf("--------------------------\n");
            printf("Nome: %s\n", (char *)start);
            start += sizeof(char) * 10;
            printf("Idade: %d\n", *(int *)start);
            start += sizeof(int);
            printf("Telefone: %d\n", *(int *)start);
            start += sizeof(int);
            start += sizeof(void *);
            tracer = start;
            start = (char *)*tracer;
            check = start;
            printf("--------------------------\n");
        }
        else{
            start += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
            tracer = start;
            start = (char *)*tracer;
            check = start;
        }
    }
    return;
}


void BuscarPessoa(void *p){

    if (p == NULL){
         printf("Nao e possivel encontrar um nome\n");
         return;
    }
    
    void **tracer;
    void *check = pFirst;
    
    void *start;
    start = pFirst;
    void *name = p;
    name += sizeof(int);
    printf("Nome a ser procurado: ");
    scanf("%s", (char *)name);
    
    while (start != NULL){
        check += sizeof(char) * 10;
        if (*(int *)check != 9999){ // Skip flagged names
            if (strcmp(name, start) == 0){
                printf("--------------------------\n");
                printf("Nome: %s\n", (char *)start);
                start += sizeof(char) * 10;
                printf("Idade: %d\n", *(int *)start);
                start += sizeof(int);
                printf("Telefone: %d\n", *(int *)start);
                start += sizeof(int);
                start += sizeof(void *);
                printf("--------------------------\n");
                printf("\n");
                return;
            }
        }
        start += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
        tracer = start;
        start = (char *)*tracer;
        check = start;
    }
    printf("Nome nao encontrado.\n");
    return;
}


char *RemoverPessoa(void *p){

    if (p == NULL || pFirst == NULL){
        printf("Nao e possivel remover uma pessoa\n");
        return p;
    }

    void *check = pFirst;
    void **tmpTracer;
    void *tmpOffset = pFirst;
    check += sizeof(char) * 10;
    
    while (*(int *)check == 9999){ // loop so we dont delete a person that has been deleted already
        tmpOffset += sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void *);
        tmpTracer = tmpOffset;
        tmpOffset = (char *)*tmpTracer;
        pFirst = tmpOffset;
        check = pFirst;
        check += sizeof(char) * 10;
        if (pFirst == NULL){ // if pFirst == null every name has been deleted
            printf("Nao e possivel remover uma pessoa\n");
            return p;
        }
    }

    void *offset = pFirst;
    offset += sizeof(char) * 10;
    *(int *)offset = 9999; // Flag so it doenst get printed
    void **tracer;
    offset += sizeof(int) + sizeof(int) + sizeof(void *);
    tracer = offset;
    pFirst = (char *)*tracer;

    return p;
}
