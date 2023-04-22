

// ЗАДАНИЕ
// enum
// двусвязный список
// удаление каждого k-того элемента












#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>



typedef enum 
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    THOUSEND = 1000
} eN;

typedef struct listDoublyConnected
{
    eN key;
    struct listDoublyConnected* before;
    struct listDoublyConnected* after;
} link;




link* NormalizeRoot(link* root){
    if ((root -> before) == NULL){
        return root;
    }
    while ((root -> before) != NULL)
    {
        root = root -> before;
    }
    return root;
}

link* Create(link* root, eN key)
{
    link* tmp = malloc(sizeof(link));
    tmp -> key = key;
    tmp -> before = NULL;
    tmp -> after = NULL;
    root = tmp;
    return root;
}

link* AddSimple(link* root, eN key)
{
    link* tmp = malloc(sizeof(link));
    tmp -> key = key;
    while ((root -> after) != NULL)
    {
        root = root -> after;
    }
    root -> after = tmp;
    tmp -> before = root;
    tmp -> after = NULL;
    return root;
}

link* AddAny(link* root, eN key, int whatPlace)
{
    link* tmp = malloc(sizeof(link));
    tmp -> key = key;
    root = NormalizeRoot(root);
    if (whatPlace == 0){
        tmp -> before = NULL;
        tmp -> after = root;
        root -> before = tmp;
    } else {
        while ((whatPlace - 1) > 0)
        {
            root = root -> after;
            whatPlace -= 1;
        }
        if ((root -> after) == NULL){
            root -> after = tmp;
            tmp -> before = root;
            tmp -> after = NULL;   
        } else {
            root -> after -> before = tmp;
            tmp -> after = root -> after;
            root -> after = tmp;
            tmp -> before = root;
        }
    }
    return root;
}

link* Delete(link* root, int position) {
    root = NormalizeRoot(root);
    link* tmp = malloc(sizeof(link));
    
    while ((position - 1) >= 0)
    {
        root = root -> after;
        position -= 1;
    }
    if (((root -> before) == NULL) &&  ((root -> after) == NULL)){
        link* tmp = malloc(sizeof(link));
        tmp -> before = NULL;
        tmp -> after = NULL;
        tmp -> key = 0;
        printf("LIST DESTROYED\n");
        free(root);
        return tmp;
    } else if ((root -> before) == NULL){
        root -> after -> before = NULL;
        tmp = root -> after;
        free(root);
        return tmp;
    } else if ((root -> after) == NULL){
        root -> before -> after = NULL;
        tmp = root -> before;
        free(root);
        return tmp;
    } else {
        root -> before -> after = root -> after;
        root -> after -> before = root -> before;
        tmp = root -> before;
        return tmp;
    }
    return NULL;
}

link* Display(link* root) {
    root = NormalizeRoot(root);
    while ((root -> after) != NULL)
    {
        printf("%d ", root -> key);
        root = root -> after;
    }
    printf("%d\n", root -> key);
}

int CountThis(link* root){
    root = NormalizeRoot(root);
    int counter = 0;
    while ((root -> after) != NULL)
    {
        counter += 1;
        root = root -> after;
    }
    counter += 1;
    return counter;
}

link* Shooting(link* root, int everyK){
    root = NormalizeRoot(root);
    if (everyK <= 1){
        int counter = CountThis(root);
        while (counter > 0){
            root = Delete(root, 0);
            root = NormalizeRoot(root);
            counter -= 1;
        }
    } else {
        int counter = 1;
        int shift = 1;
        while ((root -> after) != NULL)
        {
            if ((counter % everyK) == 0){
                root = Delete(root, counter - shift);
                shift += 1;
            }
            root = root -> after;
            counter += 1;
        }
        if ((counter % everyK) == 0){
            root = Delete(root, counter - shift);
        }
        return root;
    }
}


int main()
{
    link* root = NULL;
    root = Create(root, ZERO);
    root = AddSimple(root, ONE);
    root = AddSimple(root, TWO);
    root = AddSimple(root, THREE);
    Display(root);
    root = AddAny(root, THOUSEND, 0);
    root = AddAny(root, NINE, 5);
    Display(root);
    printf("there is %d elements\n", CountThis(root));
    root = Delete(root, 0);
    root = Delete(root, 4);
    Display(root);
    printf("there is %d elements\n", CountThis(root));
    
    root = Shooting(root, 1);
    Display(root);
    return 0;
}