#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comando.h"

void adicionar_fila_de_comando(no_comando **fila, char ordem[200]){
    no_comando *aux = malloc(sizeof(no_comando));
    strcpy(aux->ordem, ordem);
    aux->prox = NULL;
    aux->ant = NULL;

    if(*fila == NULL){
        *fila = aux;
        return;
    }
    no_comando *aux2 = *fila;
    while(aux2->prox != NULL){
        aux2 = aux2->prox;
    }
    aux2->prox = aux;
    aux->ant = aux2;
}

void remover_fila_de_comando(no_comando **fila) {
    if(*fila == NULL) {
        printf("Fila vazia\n");
        return;
    }
    no_comando *aux = *fila;
    *fila = (*fila)->prox;
    free(aux);
    if(*fila != NULL) {
        (*fila)->ant = NULL;
    }
}

void esvaziar_fila_de_comando(no_comando **fila){
    no_comando *aux = *fila;

    while (aux != NULL) {
        *fila = aux->prox;
        free(aux);         
        aux = *fila;        
    }
    *fila = NULL; 
}

void ler_arquivo(FILE *f, no_comando **fila_comando) {

    int c;
    char comando_total[200] = {0};

    while ((c = fgetc(f)) != EOF) {

        char caractere = (char)c;

        // Separador de comandos
        if (caractere == ';') {

            if (strlen(comando_total) > 0) {   // evita comandos vazios
                strcat(comando_total,";");
                char ordem[200];
                strcpy(ordem, comando_total);
                adicionar_fila_de_comando(fila_comando, ordem);
            }

            memset(comando_total, 0, sizeof(comando_total)); // zera buffer
        }
        else {
            if(caractere != '\n'){
                char tmp[2] = { caractere, '\0' };
                strcat(comando_total, tmp);
            }
        }
    }

    // se o arquivo NÃO terminar com ; ou \n
    if (strlen(comando_total) > 0) {
        char ordem[200];
        strcpy(ordem, comando_total);
        adicionar_fila_de_comando(fila_comando, ordem);
    }
}

int validar_insert(char ordem[200]){
    char copia[200];
    strcpy(copia,ordem);
    
    char *token = strtok(copia," ");
    if(!token || strcmp(token,"insert")!=0)return 0;

    token = strtok(NULL, " ");
    if(!token || strcmp(token,"into")!=0)return 0;

    token = strtok(NULL, "(");
    if(token && strcmp(token,"tipo_pet")==0){
        token = strtok(NULL, ",");
        if(!token || strcmp(token,"codigo")!=0)return 0;

        token = strtok(NULL, " )");
        if(!token || strcmp(token,"descricao")!=0)return 0;

        token = strtok(NULL, " (");
        if(!token || strcmp(token,"values")!=0)return 0;

        token = strtok(NULL, ",");
        if(!token)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, "\0");
        if(!token || strcmp(token,");")!=0)return 0;

        return 1;

    }else if(token && strcmp(token,"pet")==0){
        
        token = strtok(NULL, ",");
        if(!token || strcmp(token,"codigo")!=0)return 0;

        token = strtok(NULL, " ,");
        if(!token || strcmp(token,"codigo_pes")!=0)return 0;

        token = strtok(NULL, " ,");
        if(!token || strcmp(token,"nome")!=0)return 0;

        token = strtok(NULL, " )");
        if(!token || strcmp(token,"codigo_tipo")!=0)return 0;

        token = strtok(NULL, " (");
        if(!token || strcmp(token,"values")!=0)return 0;

        token = strtok(NULL, ",");
        if(!token)return 0;

        token = strtok(NULL, " ,");
        if(!token)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, ", )");
        if(!token)return 0;

        token = strtok(NULL, "\0");
        if(!token || strcmp(token,";")!=0)return 0;

        return 1;
    }else if(token && strcmp(token,"pessoa")==0){

        token = strtok(NULL, ",");
        if(!token || strcmp(token,"codigo")!=0)return 0;

        token = strtok(NULL, " ,");
        if(!token || strcmp(token,"nome")!=0)return 0;

        token = strtok(NULL, " ,");
        if(!token || strcmp(token,"fone")!=0)return 0;

        token = strtok(NULL, " ,");
        if(!token || strcmp(token,"data_nascimento")!=0)return 0;

        token = strtok(NULL, " )");
        if(!token || strcmp(token,"endereco")!=0)return 0;

        token = strtok(NULL, " (");
        if(!token || strcmp(token,"values")!=0)return 0;

        token = strtok(NULL, ",");
        if(!token)return 0;

        token = strtok(NULL, ",'");
        if(!token)return 0;

        token = strtok(NULL, ",'");
        if(!token)return 0;

        token = strtok(NULL, ",'");
        if(!token)return 0;

        token = strtok(NULL, ",'");
        if(!token)return 0;

        token = strtok(NULL, "\0");
        if(!token || strcmp(token,");")!=0)return 0;

        return 1;
    }else{
        return 0;
    }
}

int validar_delete(char ordem[200]){
    char copia[200];
    strcpy(copia,ordem);
    
    char *token = strtok(copia," ");
    if(!token || strcmp(token,"delete")!=0)return 0;

    token = strtok(NULL, " ");
    if(!token || strcmp(token,"from")!=0)return 0;

    token = strtok(NULL, " ");
    if(token && strcmp(token, "pet")==0){

        token = strtok(NULL, " ");
        if(!token || strcmp(token,"where")!=0)return 0;

        token = strtok(NULL, " ");
        if(token && ((strcmp(token,"codigo")==0) || (strcmp(token,"codigo_pes")==0) || (strcmp(token,"codigo_tipo")==0))){
            token = strtok(NULL, " ");
            if(!token || strcmp(token,"=")!=0)return 0;

            token = strtok(NULL, ";");
            if(!token)return 0;

            return 1;
            }else if(token && strcmp(token,"nome")==0){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, "'");
                if(!token)return 0;

                token = strtok(NULL, "\0");
                if(!token || strcmp(token,";")!=0)return 0;

            return 1;
            }else{
                return 0;
            }   

    }else if(token && strcmp(token, "tipo_pet")==0){
        
        token = strtok(NULL, " ");
        if(!token || strcmp(token,"where")!=0)return 0;

        token = strtok(NULL, " ");
        if(token && strcmp(token,"codigo")==0){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, ";");
                if(!token)return 0;

                return 1;
            }else if(token && strcmp(token,"descricao")== 0){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, "'");
                if(!token)return 0;

                token = strtok(NULL, "\0");
                if(!token || strcmp(token,";")!=0)return 0;

                return 1;
            }else{
                return 0;
            }

    }else if(token && strcmp(token, "pessoa")==0){
        
        token = strtok(NULL, " ");
        if(!token || strcmp(token, "where")!=0);

        token = strtok(NULL, " ");
        if(token && ((strcmp(token,"fone")==0) || (strcmp(token,"nome")==0) || (strcmp(token,"data_nascimento")==0) || (strcmp(token,"endereco")==0))){
            token = strtok(NULL, " ");
            if(!token || strcmp(token,"=")!=0)return 0;

            token = strtok(NULL, "'");
            if(!token)return 0;

            token = strtok(NULL, "\0");
            if(!token || strcmp(token,";")!=0)return 0;

            return 1;
            }else if(token && strcmp(token, "codigo")==0){
            token = strtok(NULL, " ");
            if(!token || strcmp(token,"=")!=0)return 0;

            token = strtok(NULL, ";");
            if(!token)return 0;

            return 1;
            }else{
                return 0;
            }

        return 0;
    }else{
        return 0;
    }
} 

int validar_select(char ordem[200]) {
    char copia[200];
    strcpy(copia, ordem);

    char *token = strtok(copia, " ");
    if (!token || strcmp(token, "select")!=0) return 0;

    token = strtok(NULL, " ");
    if (!token || strcmp(token, "*")!=0)return 0;

    token = strtok(NULL, " ");
    if (!token || strcmp(token, "from")!=0)return 0;

    token = strtok(NULL, " ");
    //Apartir dessa linha, verificações individuais para pet, tipo_pet e pessoa
    if(token && strcmp(token, "pet")==0){
        
        token = strtok(NULL, " ");
        if(token && strcmp(token, "order")==0){
            token = strtok(NULL, " ");
            if(!token || strcmp(token, "by")!=0)return 0;

            token = strtok(NULL, ";");
            if(!token || strcmp(token, "nome")!=0)return 0;

            return 1;
        }else if(token && strcmp(token,"where")==0){
            token = strtok(NULL, " ");
            if(token && ((strcmp(token,"codigo")==0) || (strcmp(token,"codigo_pes")==0) || (strcmp(token,"codigo_tipo")==0))){
                token = strtok(NULL, " ");
            if(!token || strcmp(token,"=")!=0)return 0;

            token = strtok(NULL, ";");
            if(!token)return 0;

            return 1;
            }else if(token && strcmp(token,"nome")==0){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, "'");
                if(!token)return 0;

                token = strtok(NULL, "\0");
                if(!token || strcmp(token,";")!=0)return 0;

            return 1;
            }else{
                return 0;
            } 
        }else{
            return 0;
        }
    }else if(token && strcmp(token, "pessoa")==0){
        
        token = strtok(NULL, " ");
        if(token && strcmp(token, "order")==0){
            token = strtok(NULL, " ");
            if(!token || strcmp(token, "by")!=0)return 0;

            token = strtok(NULL, ";");
            if(!token || strcmp(token, "nome")!=0)return 0;

            return 1;
        }else if(token && strcmp(token,"where")==0){
            token = strtok(NULL, " ");
            if(token && ((strcmp(token,"fone")==0) || (strcmp(token,"nome")==0) || (strcmp(token,"data_nascimento")==0) || (strcmp(token,"endereco")==0))){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, "'");
                if(!token)return 0;

                token = strtok(NULL, "\0");
                if(!token || strcmp(token,";")!=0)return 0;

                return 1;
            }else if(token && strcmp(token, "codigo")==0){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, ";");
                if(!token)return 0;

                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(token && strcmp(token, "tipo_pet")==0){
         token = strtok(NULL, " ");
        if(token && strcmp(token, "order")==0){
            token = strtok(NULL, " ");
            if(!token || strcmp(token, "by")!=0)return 0;

            token = strtok(NULL, ";");
            if(!token || strcmp(token, "nome")!=0)return 0;

            return 1;
        }else if(token && strcmp(token,"where")==0){
            token = strtok(NULL, " ");
            if(token && strcmp(token,"codigo")==0){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, ";");
                if(!token)return 0;

                return 1;
            }else if(token && strcmp(token,"descricao")== 0){
                token = strtok(NULL, " ");
                if(!token || strcmp(token,"=")!=0)return 0;

                token = strtok(NULL, "'");
                if(!token)return 0;

                token = strtok(NULL, "\0");
                if(!token || strcmp(token,";")!=0)return 0;

                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }

}

int validar_update(char ordem[200]){
    char copia[200];
    char descricao[200];
    strcpy(copia, ordem);
    
    char *token = strtok(copia, " ");
    if(!token || strcmp(token, "update")!=0)return 0;

    token = strtok(NULL, " ");
    if(token && strcmp(token,"tipo_pet")==0){
        
        token = strtok(NULL, " ");
        if(!token || strcmp(token, "set")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "descricao")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "where")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "codigo")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, ";");
        if(!token)return 0;

        return 1;

    }else if(token && strcmp(token,"pet")==0){
        
        token = strtok(NULL, " ");
        if(!token || strcmp(token, "set")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "codigo_pes")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, ",");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "nome")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "codigo_tipo")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "where")!=0)return 0;;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "codigo")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, ";");
        if(!token)return 0;

        return 1;
    }else if(token && strcmp(token,"pessoa")==0){
        token = strtok(NULL, " ");
        if(!token || strcmp(token, "set")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "nome")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "fone")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "data_nascimento")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "endereco")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, "'");
        if(!token)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "where")!=0)return 0;;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "codigo")!=0)return 0;

        token = strtok(NULL, " ");
        if(!token || strcmp(token, "=")!=0)return 0;

        token = strtok(NULL, ";");
        if(!token)return 0;

        return 1;
    }else{
        return 0;
    }

}

int validar_comando(no_comando *comando){
    no_comando *aux = comando;

    if(validar_insert(aux->ordem)==1)return 1;

    if(validar_delete(aux->ordem)==1)return 1;

    if(validar_select(aux->ordem)==1)return 1;

    if(validar_update(aux->ordem)==1)return 1;

    return 0;

}

void validar_fila_comando(no_comando **fila){
    no_comando *aux = *fila;
    no_comando *nova_fila = NULL;

    while(aux != NULL){
        if(validar_comando(aux) == 1){
            adicionar_fila_de_comando(&nova_fila,aux->ordem);
        }
        aux = aux->prox;
    }
    esvaziar_fila_de_comando(fila);
    *fila = nova_fila;
}

void despachar_fila_comando(no_comando **fila_comando, no_comando **fila_comando_pet, no_comando **fila_comando_tipo_pet, no_comando **fila_comando_pessoa){
    no_comando *aux = *fila_comando;
    while(aux != NULL){
        if(strstr(aux->ordem,"tipo_pet")!=NULL){
            adicionar_fila_de_comando(fila_comando_tipo_pet, aux->ordem);
        }else if(strstr(aux->ordem,"pet")!=NULL){
            adicionar_fila_de_comando(fila_comando_pet, aux->ordem);
        }else if(strstr(aux->ordem,"pessoa")!=NULL){
            adicionar_fila_de_comando(fila_comando_pessoa, aux->ordem);
        }
        aux = aux->prox;
    }
    esvaziar_fila_de_comando(fila_comando);
}

void extrair_valores(char ordem[200], Valores *valores){
    char copia[200];
    strcpy(copia,ordem);

    //armazeno tabela
    if(strstr(copia, "tipo_pet")){
        strcpy(valores->tabela,"tipo_pet");
        }
        else if(strstr(copia, "pet")){
        strcpy(valores->tabela,"pet");
        }
        else if(strstr(copia, "pessoa")){
        strcpy(valores->tabela,"pessoa");
        }

    if(strstr(copia,"insert") != NULL){
        if(strstr(copia,"tipo_pet")){
            //armazeno "insert"
            char *token = strtok(copia," ");
            strcpy(valores->tipo,token);

            // armazeno o código
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, "(");
            token = strtok(NULL, ",");
            valores->codigo = atoi(token);

            //armazeno descrição
            token = strtok(NULL,"'");
            strcpy(valores->descricao, token);

        }else if(strstr(copia,"pet")){
            //armazeno "insert"
            char *token = strtok(copia," ");
            strcpy(valores->tipo,token);

            //armazeno código
            token = strtok(NULL, ")");
            token = strtok(NULL, "(");
            token = strtok(NULL, ",");
            valores->codigo = atoi(token);

            //armazeno cófigo_pes
            token = strtok(NULL, " ,");
            valores->codigo_pes = atoi(token);

            //armazeno nome
            token = strtok(NULL,"'");
            strcpy(valores->nome,token);

            //armazeno codigo tipo
            token = strtok(NULL, ", )");
            valores->codigo_tipo = atoi(token);

        }else if(strstr(copia,"pessoa")){
            //armazeno "insert"
            char *token = strtok(copia," ");
            strcpy(valores->tipo,token);

            //armazeno codigo
            token = strtok(NULL,")");
            token = strtok(NULL," (");
            token = strtok(NULL,",");
            valores->codigo = atoi(token);

            //armazeno nome
            token = strtok(NULL,"'");
            strcpy(valores->nome,token);

            //armazeno fone
            token = strtok(NULL,",'");
            strcpy(valores->fone,token);

            //armazeno data
            token = strtok(NULL,",'");
            strcpy(valores->data_nascimento,token);

            //armazeno endereco
            token = strtok(NULL,",'");
            strcpy(valores->endereco,token);
        }

    }else if(strstr(copia,"delete")){
        //armazeno delete
        char copia2[200];
        strcpy(copia2,copia);
        char *token = strtok(copia2, " ");
        strcpy(valores->tipo,token);

        //armazeno tabela
        token = strtok(NULL," ");
        token = strtok(NULL," ");

        if(strcmp(token,"pessoa")==0){
            //armazeno campo
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            if(strcmp(token,"codigo")==0){token =strtok(NULL, " ");token =strtok(NULL," ;");valores->codigo = atoi(token);}
            if(strcmp(token,"nome")==0){token =strtok(NULL, " ");token =strtok(NULL,"'");strcpy(valores->nome,token);}
            if(strcmp(token,"fone")==0){token =strtok(NULL, " ");token =strtok(NULL,"'");strcpy(valores->fone,token);}
            if(strcmp(token,"data_nascimento")==0){token =strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->data_nascimento,token);}
            if(strcmp(token,"endereco")==0){token =strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->endereco,token);}

        }else if(strcmp(token,"pet")==0){
            //armazeno campo
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            if(strcmp(token,"codigo")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo = atoi(token);}
            if(strcmp(token,"codigo_pes")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo_pes = atoi(token);}
            if(strcmp(token,"codigo_tipo")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo_tipo = atoi(token);}
            if(strcmp(token,"nome")==0){token=strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->nome,token);}

        }else if(strcmp(token,"tipo_pet")==0){
            //armazeno campo
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            if(strcmp(token,"descricao")==0){token=strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->descricao,token);}
            if(strcmp(token,"codigo")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo = atoi(token);}

        }
    }else if(strstr(copia,"update")){
        //armazeno update
        char *token = strtok(copia," ");
        strcpy(valores->tipo, token);

        //verifico tabela
        token = strtok(NULL, " ");
        if(strcmp(token,"tipo_pet")==0){
            //armazeno descricao
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, "'");
            strcpy(valores->descricao,token);
            //armazeno codigo
            token = strtok(NULL, "=");
            token = strtok(NULL," ;");
            valores->codigo = atoi(token);


        }else if(strcmp(token,"pet")==0){
            //armazeno codigo_pes
            token = strtok(NULL, "=");
            token = strtok(NULL, " ,");
            valores->codigo_pes = atoi(token);

            //armazeno nome
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, "'");
            strcpy(valores->nome,token);

            //armazeno codigo_tipo
            token = strtok(NULL, ", ");
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            valores->codigo_tipo = atoi(token);

            //armazeno codigo
            token = strtok(NULL, "=");
            token = strtok(NULL," ;");
            valores->codigo = atoi(token);

        }else if(strcmp(token, "pessoa")==0){
            //armazeno nome
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, "'");
            strcpy(valores->nome, token);

            //armazeno fone
            token = strtok(NULL, ", ");
            token = strtok(NULL, " ");
            token = strtok(NULL, "'");
            strcpy(valores->fone, token);

            //armazeno data_nascimento
            token = strtok(NULL, ", ");
            token = strtok(NULL, " ");
            token = strtok(NULL, "'");
            strcpy(valores->data_nascimento, token);

            //armazeno endereco
            token = strtok(NULL, ", ");
            token = strtok(NULL, " ");
            token = strtok(NULL, "'");
            strcpy(valores->endereco, token);

            //armazeno codigo
            token = strtok(NULL, "=");
            token = strtok(NULL, " ;");
            valores->codigo = atoi(token); 
        }

    }else if(strstr(copia,"select")){
        if(strstr(copia,"order")!=NULL){
            valores->order = 1;
            char *token = strtok(copia," ");
            strcpy(valores->tipo,token);
        }else{
            
            //armazeno tipo
            char *token = strtok(copia, " ");
            strcpy(valores->tipo,token);

            //armazenar tabela
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");

            if(strcmp(token,"pessoa")==0){
            //armazeno campo
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            if(strcmp(token,"codigo")==0){token =strtok(NULL, " ");token =strtok(NULL," ;");valores->codigo = atoi(token);}
            if(strcmp(token,"nome")==0){token =strtok(NULL, " ");token =strtok(NULL,"'");strcpy(valores->nome,token);}
            if(strcmp(token,"fone")==0){token =strtok(NULL, " ");token =strtok(NULL,"'");strcpy(valores->fone,token);}
            if(strcmp(token,"data_nascimento")==0){token =strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->data_nascimento,token);}
            if(strcmp(token,"endereco")==0){token =strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->endereco,token);}

            }else if(strcmp(token,"pet")==0){
                //armazeno campo
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                if(strcmp(token,"codigo")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo = atoi(token);}
                if(strcmp(token,"codigo_pes")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo_pes = atoi(token);}
                if(strcmp(token,"codigo_tipo")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo_tipo = atoi(token);}
                if(strcmp(token,"nome")==0){token=strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->nome,token);}

            }else if(strcmp(token,"tipo_pet")==0){
                //armazeno campo
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                if(strcmp(token,"descricao")==0){token=strtok(NULL, " ");token=strtok(NULL,"'");strcpy(valores->descricao,token);}
                if(strcmp(token,"codigo")==0){token=strtok(NULL, " ");token=strtok(NULL," ;");valores->codigo = atoi(token);}

            }
        }
    }
}


            