#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;//node구조체 선언


#define MAX_STACK_SIZE	20
Node* stack[MAX_STACK_SIZE];//노드형 포인터 변수 stack 배열 크기 20으로 선언
int top = -1;//int형 포인터 변수 top -1로 초기화

Node* pop();//Node형 포인터 변수 pop선언
void push(Node* aNode);

#define MAX_QUEUE_SIZE	20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;



int initializeBST(Node** h);//트리 초기화
void recursiveInorder(Node* ptr);//LVR순회로 방문하는 노드의 key값 출력
int insert(Node* head, int key);//key값을 가지는 노드 tree에 추가
int freeBST(Node* head);//트리에 있는 모든 노드들 free 시키기


void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key); //key값을 가지는 노드 삭제
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
        printf("[----- [윤혜준] [2022041021] -----]");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command 변수에 입력받을 명령어 저장

		switch(command) {
		case 'z': case 'Z'://command명령어로 z나 Z 입력받은 경우
			initializeBST(&head);//헤드 주소값 입력받아 트리 초기화
			break;
		case 'q': case 'Q'://command명령어로 q나 Q 입력받은 경우
			freeBST(head);//트리에 있는 모든 노드들 free 시키기
			break;
		case 'i': case 'I'://command명령어로 i나 I 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력받아 변수에 저장
			insert(head, key);//key값을 가지는 노드 tree에 추가
			break;
		case 'd': case 'D'://command명령어로 d나 D 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값 받아서 변수에 저장
			deleteNode(head, key);//key값을 가지는 노드 삭제
			break;

		case 'r': case 'R'://command명령어로 r이나 R 입력받은 경우
			recursiveInorder(head->left);//LVR순회로 방문하는 노드의 key값 출력
			break;
		case 't': case 'T'://command명령어로 t나 T 입력받은 경우
			iterativeInorder(head->left);
			break;

		case 'l': case 'L'://command명령어로 l이나 L 입력받은 경우
			levelOrder(head->left);
			break;

		case 'p': case 'P'://command명령어로 p나 P 입력받은 경우
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//command명령어로 q나 Q 입력받은 경우 loop 나가기

	return 1;
}



int initializeBST(Node** h) {//트리 초기화

	if(*h != NULL)
		freeBST(*h);//트리가 비어있지 않을 경우 트리 비우기

	*h = (Node*)malloc(sizeof(Node));//head노드 선언하고 초기화
	(*h)->left = NULL;
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)//LVR순회로 방문하는 노드의 key값 출력
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}



void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left)
			push(node);
		node = pop();

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}



void levelOrder(Node* ptr)
{

	if(!ptr) return;//트리가 비어있을 경우 함수 실행 종료

	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


int insert(Node* head, int key)//key값을 가지는 노드 tree에 추가
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {
		if(ptr->key == key) return 1;
		parentNode = ptr;
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)//key값을 가지는 노드 삭제
{
	if (head == NULL) {//tree가 비어있을 경우 함수 실행 종료
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//tree에 root만 존재할 경우 함수 실행 종료
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;

	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;

			if(ptr->key > key)//현재 노드의 key값이 삭제하고 싶은 노드의 key값보다 큰 경우 왼쪽 자식 노드로 이동
				ptr = ptr->left;
			else
				ptr = ptr->right;//현재 노드의 key값이 삭제하고 싶은 노드의 key값보다 작을 경우 오른쪽 자식 노드로 이동
		}
	}

	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}


	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { 
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {

			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {

			root = child;
		}

		free(ptr);
		return 1;
	}


	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;


	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)//ptr값 받아서 LRV순회로 돌면서 방문하는 노드들 free 시키기
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)//트리에 있는 모든 노드들 free 시키기
{

	if(head->left == head)//tree에 root노드만 존재할 경우 head만 free 시키고 함수 실행 종료
	{
		free(head);
		return 1;
	}

	Node* p = head->left;//트리에 있는 노드들 free 시킬 때 쓸 포인터 변수 p 선언하고 p 이용해서 tree 비우기

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];
}

void push(Node* aNode)
{
	stack[++top] = aNode;
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	if (front == rear) {
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		return;
	}

	queue[rear] = aNode;
}




