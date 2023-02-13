#include "symbolTable.h"
#include <stdbool.h>


int hash(unsigned char *str){
    unsigned int hash = 0;
    int c;

    while (c = *str++)
        hash += c;

    return hash;
}

//de sters naher
varEnv* lookupvar(varEnv* env, unsigned int hash){
    while (env != NULL){
        if (env->hash == hash) {
            return env;
        } else {
            env = env->nextEnv;
        }
    }
    return NULL; 
}
funcEnv* lookupfun(funcEnv* env, unsigned int hash){
    while (env != NULL){
        if (env->hash == hash) {
            return env;
        } else {
            env = env->nextEnv;
        }
    }
    return NULL; 
}

int countNonGlobal(varEnv *env){
    int count = 0; 
    varEnv *tmp = env;

    while (tmp != NULL){
        if(tmp->data->global == 0){
            count++;
        }

        tmp = tmp->nextEnv;
    }

    return count;
}

void deleteNonGlobal(varEnv **env){
    while (countNonGlobal(*env) != 0){
        deleteNonGlobal1El(env);
    }
}

void deleteNonGlobal1El(varEnv** head_ref){
    varEnv* temp = *head_ref;
    varEnv* prev = NULL;
    
    if (temp != NULL && temp->data->global == 0){
        *head_ref = temp->nextEnv;           
        return;
    } else {
        while (temp != NULL && temp->data->global != 0)
        {
            prev = temp;
            temp = temp->nextEnv;
        }

        if (temp == NULL)
            return;

        prev->nextEnv = temp->nextEnv;
    }
}

varEnv *addNewVar(varEnv *env, varData *data){  
    varEnv *tmpEnv = env;
    varEnv *newVar = malloc(sizeof(varEnv));

    newVar->hash = hash(data->id);
    newVar->data = data;
    newVar->nextEnv = NULL;

    while (tmpEnv != NULL && tmpEnv->nextEnv != NULL){
        tmpEnv = tmpEnv->nextEnv;
    }
    
    if (env == NULL){
        env = newVar;
    } else {
        tmpEnv->nextEnv = newVar; 
    }
    
    return env;
}

funcEnv *addNewFunc(funcEnv *env, funcData *data){  
    funcEnv *tmpEnv = env;
    funcEnv *newFunc = malloc(sizeof(funcEnv));

    newFunc->hash = hash(data->id);
    newFunc->data = data;
    newFunc->nextEnv = NULL;

    while (tmpEnv != NULL && tmpEnv->nextEnv != NULL){
        tmpEnv = tmpEnv->nextEnv;
    }
    
    if (env == NULL){
        env = newFunc;
    } else {
        tmpEnv->nextEnv = newFunc; 
    }
    
    return env;
}

structEnv *addNewStruct(structEnv *env, structData *data){  
    structEnv *tmpEnv = env;
    structEnv *newVar = malloc(sizeof(structEnv));

    newVar->hash = hash(data->id);
    newVar->data = data;
    newVar->nextEnv = NULL;

    while (tmpEnv != NULL && tmpEnv->nextEnv != NULL){
        tmpEnv = tmpEnv->nextEnv;
    }
    
    if (env == NULL){
        env = newVar;
    } else {
        tmpEnv->nextEnv = newVar; 
    }
    
    return env;
}

char *getStructNameByHash(structEnv *envStruct, int hash){
    int pointerFlag = 0;
    structEnv *tmp = envStruct;
    
    if (hash < 0){
        pointerFlag = 1;
        hash *= -1;
    }

    while (tmp != NULL){
        if (tmp->hash == hash) {

            if (pointerFlag) {
                char *tmpID = strdup(tmp->data->id);
                strcat(tmpID, "*");
                return tmpID;
            } else {
                return tmp->data->id;
            }

        }

        tmp = tmp->nextEnv;
    }

    return "-1";
}

char *getDataType(structEnv* envStruct, int i){
    switch (i)
    {
        case 0:
            return "VOID";
        case 1:
            return "INT";
        case -1:
            return "INT*";
        case -2:
            return "*FUNC";
        default:
            return getStructNameByHash(envStruct, i);
    }
}

char *getStringTypes(structEnv* envStruct,int *argsType, int argsLen){
    char *res = NULL;
    char tmpDest[255] = "";

    for(int i = 0; i < argsLen; i++){
        if ((argsType + i) != NULL){
            char *tmpChar = strdup(getDataType(envStruct, *(argsType + i))); 
            strcat(tmpDest, tmpChar);

            if (i != argsLen){
                strcat(tmpDest, " ");
            }

            res = strdup(tmpDest);
        }
    }

    return res;
}

char *getFieldsName(char **fieldsName, int len){
    char *res = NULL;
    char tmpDest[255] = "";

    for(int i = 0; i < len; i++){
        if ((fieldsName + i) != NULL){
            char *tmpChar = strdup(*(fieldsName + i)); 
            strcat(tmpDest, tmpChar);

            if (i != len){
                strcat(tmpDest, " ");
            }

            res = strdup(tmpDest);
        }
    }

    return res;
}

varData *createVarData(char *id, int type, int value, int globalFlag, int line){
    varData *tmpVarData = malloc(sizeof(varData));
    tmpVarData->id = strdup(id);
    tmpVarData->type = type;
    tmpVarData->value = hash("extern");
    tmpVarData->global = globalFlag;
    tmpVarData->line = line;

    return tmpVarData;
}

structData *createStructData(char *id, int *fieldsType, int fieldsLen, char *fieldsName[100], int line){
    structData *tmpStructData = malloc(sizeof(structData));
    tmpStructData->id = strdup(id);
    tmpStructData->fieldsType = fieldsType;
    tmpStructData->fieldsLen = fieldsLen;

    for (int i = 0; i < fieldsLen; i++){
        tmpStructData->fieldsName[i] = strdup(fieldsName[i]);
    }

    tmpStructData->line = line;
    return tmpStructData;
}

funcData *createFuncData(char *id, int returnType, int *argsType, int argsLen, char *paramsName[100], int line){
    funcData *tmpFuncData = malloc(sizeof(funcData));
    tmpFuncData->id = strdup(id);
    tmpFuncData->returnType = returnType;
    tmpFuncData->argsType = argsType;
    tmpFuncData->argsLen = argsLen;

    for (int i = 0; i < argsLen; i++){
        tmpFuncData->paramsName[i] = strdup(paramsName[i]);
    }
    
    tmpFuncData->line = line;
    return tmpFuncData;
}

void printDashes(int n){
    printf("\n");
	for(int i = 0; i < n; i++) {
	    printf("=");
    }
	printf("\n");
}

void printVarST(structEnv* envStruct, varEnv *env){
    varEnv *tmpEnv = env;

    printDashes(100);
    printf("VARIABLE SYMBOL TABLE");
    printDashes(100);
    printf("%-20s %-20s %-20s %-20s %-20s\n", "ID", "HASH", "TYPE", "GLOBAL_FLAG", "LINE");

    while(tmpEnv != NULL) {
        varData *data = tmpEnv->data;
        
        printf("%-20s %-20d %-20s %-20d %-20d", data->id, tmpEnv->hash, getDataType(envStruct,data->type), data->global, data->line);

        if (tmpEnv->nextEnv != NULL){
            printf("\n");
        }

        tmpEnv = tmpEnv->nextEnv;
    }
    printDashes(100);   
}

void printFuncST(structEnv* envStruct, funcEnv *env){
    funcEnv *tmpEnv = env;

    printDashes(190);
    printf("FUNCTION SYMBOL TABLE");
    printDashes(190);
    printf("%-20s %-20s %-20s %-40s %-70s %-20s\n", "ID", "HASH", "RETURN_TYPE", "ARGS_TYPE", "ARGS_NAME", "LINE");

    while(tmpEnv != NULL) {
        funcData *data = tmpEnv->data;
        
        printf("%-20s %-20d %-20s %-40s %-70s %-20d", data->id, tmpEnv->hash, getDataType(envStruct, data->returnType), getStringTypes(envStruct,data->argsType, data->argsLen), getFieldsName(data->paramsName, data->argsLen), data->line);

        if (tmpEnv->nextEnv != NULL){
            printf("\n");
        }

        tmpEnv = tmpEnv->nextEnv;
    }
    printDashes(190);   
}

void printStructST(structEnv *env){
    structEnv *tmpEnv = env;

    printDashes(200);
    printf("STRUCT SYMBOL TABLE");
    printDashes(200);
    printf("%-20s %-20s %-70s %-70s %-20s\n", "ID", "HASH", "FIELDS_TYPE", "FIELDS_NAME", "LINE");

    while(tmpEnv != NULL) {
        structData *data = tmpEnv->data;
        printf("%-20s %-20d %-70s %-70s %-20d", data->id, tmpEnv->hash, getStringTypes(env,data->fieldsType, data->fieldsLen), getFieldsName(data->fieldsName, data->fieldsLen), data->line);

        if (tmpEnv->nextEnv != NULL){
            printf("\n");
        }

        tmpEnv = tmpEnv->nextEnv;
    }
    printDashes(200);   
}

//SEMANTICS PARTS -> need to add in a new FILE after


// BOOL : 
//     0 -> false
//     1 -> true

int checkVarExists(varEnv *env, int hash){
    varEnv *tmp = env;

    while(tmp != NULL){
        if (tmp->hash == hash){
            return 1;
        }
        
        tmp = tmp->nextEnv;
    }   

    return 0;
}