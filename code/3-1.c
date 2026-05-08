#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 정보를 담을 노드 구조체 정의
typedef struct Node {
    char name[20];
    int score;
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 리스트의 시작점(head node)을 가리키는 포인터
Node* head = NULL;

// 1. 새로운 학생 정보를 리스트의 마지막에 추가하는 함수
void add (char* name, int score) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 새로운 노드 동적 할당
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);  // 이름 복사
    newNode->name[sizeof(newNode->name) - 1] = '\0';  // 문자열 종료 문자 추가
    newNode->score = score;  // 점수 설정
    newNode->next = NULL;  // 새 노드가 마지막 노드이므로 next는 NULL

    // 리스트가 비어있는 경우, 새 노드가 head가 됨
    if (head == NULL) { 
        head = newNode;
    } else {
        // 리스트의 끝을 찾아 새 노드를 추가
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;  // 다음 노드로 이동
        }
        current->next = newNode;  // 마지막 노드의 next를 새 노드로 설정
    }   
}

// 2. 학생 정보를 리스트에서 삭제하는 함수
void delete (char* name) {
    Node* current = head;
    Node* previous = NULL;

    // 리스트를 순회하며 삭제할 학생을 찾음
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {  // 이름이 일치하는 경우
            if (previous == NULL) {  // 삭제할 노드가 head인 경우
                head = current->next;  // head를 다음 노드로 설정
            } else {
                previous->next = current->next;  // 이전 노드의 next를 현재 노드의 next로 설정
            }
            free(current);  // 현재 노드 메모리 해제
            return;  // 함수 종료
        }
        previous = current;  // 이전 노드를 현재 노드로 업데이트
        current = current->next;  // 다음 노드로 이동
    }
}

// 3. 전체 리스트 출력 함수
void print() {
    Node* current = head;
    while (current != NULL) {
        printf("%s %d\n", current->name, current->score);  // 학생 정보 출력
        current = current->next;  // 다음 노드로 이동
    }
}

// 4. 프로그램 종료 전 전체 리스트 메모리 해제 함수
void freeList() {
    Node* current  = head;
    Node* next;
    // 리스트를 순회하며 모든 노드 메모리 해제
    while (current != NULL) {
        next = current->next;  // 다음 노드 저장
        free(current);  // 현재 노드 메모리 해제
        current = next;  // 다음 노드로 이동
    }
    head = NULL;  // head를 NULL로 설정하여 리스트 초기화
}

int main() {
    char command[10];
    char name[20]; 
    int score;

    while (1) {
        scanf("%s", command);  // 명령어 입력
        if (strcmp(command, "add") == 0) {  // add 명령어 처리
            scanf("%s %d", name, &score);  // 이름과 점수 입력
            add(name, score);  // 학생 정보 추가
        } else if (strcmp(command, "delete") == 0) {  // delete 명령어 처리
            scanf("%s", name);  // 이름 입력
            delete(name);  // 학생 정보 삭제
        } else if (strcmp(command, "print") == 0) {  // print 명령어 처리
            print();  // 전체 리스트 출력
        } else if (strcmp(command, "quit") == 0) {  // quit 명령어 처리
            freeList();  // 리스트 메모리 해제
            break;  // 프로그램 종료
        }
    }
    return 0;
}
