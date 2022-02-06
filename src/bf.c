#include "../inc/bf.h"

static int insertNode(list_t* list, char op);
static void listWalk(list_t* list, const char* desc);
static void memset(void* arr, unsigned char val, size_t len);

list_t* buildQueue(const char* fname) {
    list_t* list = malloc(sizeof(list_t));
    FILE* fptr = fopen(fname, "r");
    int ret = 0;

    list->head = NULL;

    if (list == NULL) {
        throwError("could not alloc (root)", "bf.c", 12, -1);
        
        return NULL;
    }

    if (fptr == NULL) {
        throwError("could not open", fname, -1, -1);

        return NULL;
    }

    do {
        ret = fgetc(fptr);
        if (ret != EOF) {
            fseek(fptr, 1, SEEK_CUR);
            if (!insertNode(list, ret)) {
                throwError("could not alloc (node)", "bf.c", 28, -1);
                fclose(fptr);

                return NULL;
            }
        }
    } while (ret != EOF);

    return list;
}

int queueInterpret(list_t* list) {
    int* bins = malloc(sizeof(int) * 30000);

    if (bins == NULL) {
        throwError("could not alloc (bins)", "bf.c", 46, -1);

        return 0;
    }

    return 1;
}

static int insertNode(list_t* list, char op) {
    instruction_t* inst;

    inst = malloc(sizeof(inst));

    if (inst == NULL) {
        throwError("could not alloc (node)", "bf.c", 56, -1);

        return 0;
    }

    inst->op = op;
    if (list->head == NULL) {
        list->head = inst;
        list->tail = inst;
    } else {
        inst->last_ptr = list->tail;
        inst->next_ptr = NULL;
        list->tail->next_ptr = inst;
        list->tail = inst;
    }
    
    return 1;
}

static void listWalk(list_t* list, const char* desc) {
    int i = 0;
    instruction_t* inst = list->head;

    printf("Debug: %s\n", desc);

    while (inst != NULL) {
        printf("Node %d: %c\n", i++, inst->op);
        inst = inst->next_ptr;
    }
}

static void memset(void* arr, unsigned char val, size_t len) {
    size_t i;
    unsigned char* dest = arr;

    for (i = 0; i < len; i++) {
        dest[i] = val;
    }
}
