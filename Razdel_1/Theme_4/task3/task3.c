#include "task3.h"

void init() {
    List = malloc(sizeof(MainList));
    List -> next = NULL;
    List -> first = NULL;
    List -> value = 0;
}

bool isEmptyMain(){
    return List -> next == NULL;
}

bool isEmptySub(MainList *Current) {
    return Current -> first -> next == NULL;
}


void showList() {
    printf("Состояние списка:\n");
    if(!isEmptyMain()) {
        MainList *mainCurrent = List -> next;
        while (mainCurrent != NULL) {
            printf("\nСписок %d: ", mainCurrent->value);
        if (!isEmptySub(mainCurrent)) {
            SubList *subCurrent = mainCurrent->first->next;
            while (subCurrent != NULL) {
                printf("%d  ", subCurrent -> value);
                subCurrent = subCurrent -> next;
            }
        }
        mainCurrent = mainCurrent -> next;
        }
    }
    else printf("Главный список пуст\n");
}

void addSubListToMain() {
    int value, key, choice;
    MainList *current = NULL;
    MainList *tmp = malloc(sizeof(MainList));
    tmp -> first = malloc(sizeof(SubList));

    printf("\nКуда добавить элемент?\n");
    printf("0. До указанного элемента\n");
    printf("1. После указанного элемента\n");
    scanf("%d", &choice);

    if (choice == 0) {
        if (!isEmptyMain()) {
            MainList *prev = List;
            current = List->next;
            printf("\nВведите заголовок, перед которым хотите добавить новый саблист: ");
            scanf("%d", &key);
            while (current != NULL) {
                if (current->value == key) break;
                current = current->next;
                prev = prev->next;
            }
            if (current == NULL) {
                printf("Значение %d не найдено\n", key);
                return;
            }
            tmp->next = current;
            tmp->first->next = NULL;
            prev->next = tmp;
        } else {
            tmp -> next = NULL;
            tmp -> first -> next = NULL;
            List -> next = tmp;
        }
    } else if (choice == 1) {
        if (!isEmptyMain()) {
            current = List->next;
            printf("\nВведите заголовок, после которого хотите добавить новый саблист: ");
            scanf("%d", &key);
            while ((current != NULL) && (current->value != key)) {
                current = current->next;
            }
            if (current == NULL) {
                printf("Значение %d не найдено\n", key);
                return;
            }
            tmp->next = current->next;
            tmp->first->next = NULL;
            current->next = tmp;
        } else {
            tmp -> next = NULL;
            tmp -> first -> next = NULL;
            List -> next = tmp;
        }
    } else {
        printf("Неизвестная операция\n");
        return;
    }

    printf("Введите значение элемента главного списка: ");
    scanf("%d", &value);
    tmp -> first -> value = value;
    tmp -> value = value;

    printf("Саблист с заголовком %d добавлен в главный список\n", value);
}


void addToSub() {
    if (!isEmptyMain()) {
        int mainValue, newValue, subValue;
        MainList *mainCurrent = List->next;
        printf("Введите значение главного списка, в который хотите добавить элемент: ");
        scanf("%d", &mainValue);
        while (mainCurrent != NULL && mainCurrent->value != mainValue) {
            mainCurrent = mainCurrent->next;
        }
        if (mainCurrent == NULL) {
            printf("Значение %d не найдено.\n", mainValue);
            return;
        }
        SubList *head = mainCurrent -> first;
        SubList *current = NULL;
        SubList *tmp = malloc(sizeof(SubList));
        int choice;
        printf("Куда добавить элемент?\n");
        printf("0. До указанного элемента\n");
        printf("1. После указанного элемента\n");
        scanf("%d", &choice);
        if (choice == 0) {
            if (!isEmptySub(mainCurrent)) {
                SubList *prev = head;
                current = head -> next;
                printf("\nВведите значение, перед которым хотите добавить новый элемент: ");
                scanf("%d", &subValue);
                while (current != NULL) {
                    if (current -> value == subValue) break;
                    current = current -> next;
                    prev = prev -> next;  
                }
                if (current == NULL) {
                    printf("Значение %d не найдено", subValue);
                    return;
                }
                tmp -> next = current;
                prev -> next = tmp;
            } else {
                tmp -> next = NULL;
                head -> next = tmp;
            }
        } else if (choice == 1) {
            if (!isEmptySub(mainCurrent)) {
                printf("\nВведите значение, после которого хотите добавить новый элемент: ");
                scanf("%d", &subValue);
                current = head -> next;
                while (current != NULL && current->value != subValue) {
                    current = current->next;
                }
                if (current == NULL) {
                    printf("Значение %d не найдено\n", subValue);
                    return;
                }
                tmp->next = current->next;
                current->next = tmp;
            } else {
                tmp -> next = NULL;
                head -> next = tmp;
            }
        } else {
            printf("Некорректный выбор.\n");
            return;
        }

        printf("\nВведите значение, нового элемента: ");
        scanf("%d", &newValue);
        tmp -> value = newValue;
        printf("Элемент %d успешно добавлен.\n", newValue);

    } else {
        printf("Главный список пуст. Добавьте хотя бы один саблист.\n");
    }
}



void removeSubFromMain() {
    if (isEmptyMain()) {
        printf("Главный список пуст\n");
        return;
    }

    int value;
    printf("Введите заголовок саблиста для удаления: ");
    scanf("%d", &value);

    MainList *prev = NULL;
    MainList *current = List;
    while (current != NULL && current->value != value) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Саблист с заголовком %d не найден в главном списке\n", value);
        return;
    }

    SubList *subCurrent = current->first;
    while (subCurrent != NULL) {
        SubList *temp = subCurrent;
        subCurrent = subCurrent->next;
        free(temp);
    }

    if (prev == NULL) {
        List = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);

    printf("Саблист с заголовком %d успешно удален из главного списка\n", value);
}



void removeFromSub() {
    if(!isEmptyMain()){
        int value;
        MainList *currentMain = NULL;
        currentMain = List -> next;
        printf("Введите заголовок саблиста, из которого хотите удалить элемент: ");
        scanf("%d", &value);        
        while((currentMain!=NULL) && (currentMain->first->value != value)) {
            currentMain = currentMain ->next;
        }
        if(currentMain == NULL) {
            printf("Значние %d не найдено\n", value);
            return;            
        }
        if (!isEmptySub(currentMain)){
            SubList *head = currentMain -> first;
            SubList *currentSub = NULL;
            SubList *prevSub = NULL;
            currentSub = head -> next;
            prevSub = head;
            printf("Введите значение для удаления: ");
            scanf("%d", &value);          
            while (currentSub != NULL)
            {
                if(currentSub -> value == value) break;
                currentSub = currentSub -> next;
                prevSub = prevSub -> next;
            }
            if (currentSub == NULL)
            {
                printf("Значние %d не найдено\n", value);
                return;  
            }
            prevSub ->next = currentSub -> next;
            free(currentSub);
            printf("Значние %d удалено\n", value);
        }
        else printf("Саблист пуст.\n");
    }
    else printf("Главный список пуст.\n");
}

void searchElement(){
    if (!isEmptyMain()) {
        int value;
        printf("Введите значение для поиска: ");
        scanf("%d", &value);
        MainList *currentMain = List -> next;
        while (currentMain != NULL) {
            if(!isEmptySub(currentMain)) {
                int pos = 1;
                SubList *currentSub = currentMain -> first -> next;
                while ((currentSub != NULL) && (currentSub -> value != value) ){
                    currentSub = currentSub -> next;
                    ++pos;
                }
                if (currentSub != NULL){
                    printf("Элемент %d найден в саблисте с заголовком %d на позиции %d\n",value, currentMain -> first ->value, pos);
                }
            }
            else printf("Саблист %d пуст, либо элемент не найден\n",currentMain -> first ->value );
            currentMain = currentMain -> next;  
        }
    }
    else printf("Главный список пуст.\n");
}

void clearList() {
    MainList *currentMain;
    SubList *currentSub;
    currentMain = List;
    while (List != NULL) {
        currentMain = List;
        while (currentMain -> first != NULL) {
            currentSub = currentMain -> first;
            currentMain -> first = currentMain -> first -> next;
            free(currentSub);
        }
        List = currentMain -> next;
        free(currentMain);
    }
}

void mainMenu() {
    int result = -1;
    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Проверить пустоту списка\n");
        printf("2 - Вывести состояние списка\n");
        printf("3 - Добавить саблист в главный список\n"); 
        printf("4 - Добавить элемент в саблист\n");    
        printf("5 - Удалить саблист из главного списка\n");
        printf("6 - Удалить элемент из саблиста\n");
        printf("7 - Найти элемент по значению\n");
        printf("0 - Выход\n");
        printf("Введите номер операции - ");
        scanf("%d", &result);

        switch (result) {
            case 0:
                clearList();
                return;
            case 1:
                if (!isEmptyMain()) {
                    printf("Cписок не пуст\n");
                } else {
                    printf("Cписок пуст\n");
                }
                break;
            case 2:
                showList();
                break;
            case 3:
                addSubListToMain();                
                break;
            case 4:
                addToSub();
                break;
            case 5:
                removeSubFromMain();
                break;                
            case 6:
                removeFromSub();
                break;
            case 7:
                searchElement();
                break;
            default:
                printf("Неизвестная операция! Повторите ввод...\n");
                break;
        }
        getchar();
        getchar();
    }
}

int main(){
    init();
    mainMenu();
    return EXIT_SUCCESS;
}