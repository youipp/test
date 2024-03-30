//menu.c
#include "menu.h"
#include <stdlib.h>

#define SIZE 50
struct st_Book* clist[SIZE]; // book list

char LNAME[5][30]={"Graphite","Opal","Bronze","Silver","Gold"}; // labels by level



void displayMenu(){
    int no;	// amount of books
    int menu; // menu number 
    no = loadData(clist);
    while(1)
	{
		// Print menu
		printf("\n[1]List [2]Statistics [3]Random pick [4]Search [5]Add [6]Modify [7]Delete [8]Report [0]Exit\n> Enter a menu >> ");
		scanf("%d",&menu);	

		if(menu==1){
			printBooks(clist, no); // Print all list of Books
		}
		else if(menu==2){
			printStatistics(clist, no);	// Print statistics of each level
		}
		else if(menu==3){
			pickupRandomBooks(clist, no); // Pick up random Books
		}
		else if(menu==4){
			searchBook(clist, no);	// Search a Book
		}
		else if(menu==5){
			no = addBook(clist, no); // Add a Book
		}
		else if(menu==6){
			updateBook(clist, no); // Modify a Book
		}
		else if(menu==7){
			no = deleteBook(clist, no); // Delete a Book
		}
		else if(menu==8){
			makeReport(clist, no);	// Make a Report
		}
		else {
			break;
		}
	}
}

int loadData(struct st_Book* c[]){
	int no=0;
	FILE* file;

	file=fopen("Book.txt", "r"); // 파일을 연다.
	while(!feof(file)){ // 파일이 끝날 때 까지 무한 반복
		struct st_Book* t = (struct st_Book*)malloc(sizeof(struct st_Book)); // 구조체 포인터 메모리 할당
		int r=fscanf(file, "%s %d", t->name, &(t->count)); // 목록의 데이터 개수를 받기 위한 변수r, 파일을 스캔해서 구조체에 저장한다.
		if(r<2) break; // 목록의 데이터 개수가 2개 미만이면 반복문 종료
		t->level = findLevel(t->count); // 단어 수에 따라 레벨을 알려주는 함수를 호출해서 레벨을 받아서 구조체에 저장한다.
		c[no] = t; // 저장한 내용을 파라미터로 받은 구조체에 순서대로 넣는다.
		no++; // 1씩 추가. 다음배열로 넘어가야하므로, 목록 개수를 세야하므로.
	}
	fclose(file); // 파일을 닫는다.
	printf("> %d Books are loaded.\n", no);
	return no; // 몇개의 목록이 있는지 리턴한다.
}

int findLevel(int num){ // 단어 수에 따른 등급을 알려주는 함수
	int range[5]={1000,10000,100000,1000000,10000000}; // range for level
	for(int j=0;j<5;j++) // 5번 반복하면서 (등급이 5개 이므로.)
		if(num<range[j]) // 단어 수가 등급컷보다 낮으면
			return j; // 그 등급의 순서를 리턴한다.
	return 0;
}

void printBooks(struct st_Book* c[], int size){ // 책의 목록을 출력해주는 함수
	printf("> List of Books\n");
	for(int i=0; i<size; i++){ // 책의 개수만큼 반복하며
		printf("[%2d] %-20s %10d words [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]); // 채널 정보 출력
	}
}

int addBook(struct st_Book* c[], int size){ // 새로운 채널 추가 하는 함수
	struct st_Book* temp; // 구조체 포인터 생성
	printf("> Add a new Book\n");
	temp = (struct st_Book*)malloc(sizeof(struct st_Book)); // 구조체 메모리 할당
	printf("> Enter a name of Book > ");
	scanf("%s", temp->name);
	printf("> Enter an amount of words > ");
	scanf("%d", &(temp->count));
	temp->level = findLevel(temp->count); // 입력받은 후 레벨을 찾는 함수를 사용해서 레벨을 저장한다.
	c[size] = temp; // 목록 구조체 배열의 마지막 순서에 추가해준다.
	printf("> New Book is added.\n"); 
	printf("[%2d] %-20s %10d words [%s] \n",size+1, c[size]->name, c[size]->count,LNAME[c[size]->level]);
	return size+1; // 목록이 하나 추가되었으므로 사이즈에 1을 추가해서 리턴해준다.
}

void printStatistics(struct st_Book* c[], int size){ // 모든 책의 등급별 개수, 최대 채널정보를 출력한다.
// 파라미터는 채널정보를 저장된 구조체 포인터 배열 c, 채널정보 구조체의 개수 size
// 리턴값 : 없음
// 하는 일 : 모든 채널 정보에 대해 5개 등급별 채널개수와 평균 단어수, 최대 단어수를 가진 채널명, 단어수를 출력한다.
/*
목록 전체 개수 만큼 반복
	어떤 등급인지 확인하면서 등급별 채널 개수를 저장 + 단어수 합산 + 최대 단어 수인 채널 저장 
	만약 책의 등급이 0이면 
		0번째 num배열에 채널 수 1추가
		0번째 count단어 수 합산
		만약 최대단어 채널 0번째 배열의 단어 수보다 해당 책의 단어 수가 높으면 0번째 배열에 저장된 목록순서번호 바꾸기
	가장 단어 수가 적은 채널을 찾는 방법은?
		한 바퀴 돌리면서 비교한다.
*/
	int num[5] = {0}, topNum[5] = {0}; // num: 등급별 채널개수, countA: 단어수 합산, topNum: 최대 단어수를 가진 채널 번호
	float countA[5] = {0};
	for(int i=0;i<size;i++){ // 단어 수가 가장 적은 채널을 기본값으로 세팅한다. 
		for(int j=0;j<5;j++){
			if(c[topNum[j]]->count >= c[i]->count){
				topNum[j] = i;
			}
		}
	}
	printf("> Statistics of Books\n");
	for(int i=0;i<size;i++){	// 한바퀴 돌리면서 케이스마다 합산한다.
		if(c[i]->level == 0){
			num[0]++;
			countA[0] = countA[0] + c[i]->count;
			if(c[topNum[0]]->count <= c[i]->count){
			topNum[0] = i;
			}
		}
		else if(c[i]->level == 1){
			num[1]++;
			countA[1] = countA[1] + c[i]->count;
			if(c[topNum[1]]->count <= c[i]->count){
			topNum[1] = i;
			}
		}
		else if(c[i]->level == 2){
			num[2]++;
			countA[2] = countA[2] + c[i]->count;
			if(c[topNum[2]]->count <= c[i]->count){
			topNum[2] = i;
			}
		}
		else if(c[i]->level == 3){
			num[3]++;
			countA[3] = countA[3] + c[i]->count;
			if(c[topNum[3]]->count <= c[i]->count){
			topNum[3] = i;
			}
		}
		else if(c[i]->level == 4){
			num[4]++;
			countA[4] = countA[4] + c[i]->count;
			if(c[topNum[4]]->count <= c[i]->count){
			topNum[4] = i;
			}
		}
		else
			return;
	}
	for(int j=0;j<5;j++){
		printf("%s : %d Books, Average %.1f words, Top Book : %s (%d words)\n", LNAME[j], num[j], (countA[j]/num[j]),c[topNum[j]]->name, c[topNum[j]]->count);
	}
}

void pickupRandomBooks(struct st_Book* c[], int size){ 
/*
파라미터 채널정보를 저장된 : 구조체 포인터 배열 c, 채널정보 구조체의 개수 size
리턴값 : 없음
하는 일 : 모든 채널 중에서 사용자가 입력한 개수만큼의 임의의 채널을 선택해서 출력한다.

*/
	int pickUpNum = 0; // 몇개를 랜덤으로 뽑을지
	printf("> Pick up Books\n");
	printf("> How much Books you want to pick up? > ");
	scanf("%d", &pickUpNum);
	printf("Random Books\n");

	int random = 0; // 정수형 변수 선언
	for (int i = 0; i < pickUpNum; i++) { // 받은 숫자만큼 반복
		random = (rand()%size); // 난수 생성
		printf("[%d] %s (%s, %d words)\n", random+1, c[random]->name, LNAME[c[random]->level], c[random]->count);
	}
	return;
}
void searchBook(struct st_Book* c[], int size){
/*
파라미터 : 채널정보를 저장된 구조체 포인터 배열 c, 채널정보 구조체의 개수 size
리턴값 : 없음
하는 일 : 채널 정보 중에 다음 조건에 맞는 채널 정보를 찾아 출력한다.
1) 특정 범위 숫자(최소~최대)의 단어 수를 가진 채널 검색
2) 특정 문자열이 포함된 이름을 가진 채널 검색

만약 1을 입력받으면 단어 수 범위를 물어보고 그 안에 있는 채널을 출력해준다.
	그러려면 한바퀴를 돌리면서
		만약 입력받은 작은 수 < 이고 < 입력받은 큰 수 이면
			출력
			채널 수 합산
	합산한 채널 수 출력
아니고 만약 2를 입력 받으면 문자열을 입력받고
	한바퀴 돌려서 
		만약 입력받은 문자열이 채널명 속에 있으면
			출력
			합산
	합산 수 출력
*/
	int choose = 0;
	int num[2];
	int sum = 0;
	char name[50];
	char* re;
	printf("> Search Books\n");
	printf("> Choose one (1:by words 2:by names) > ");
	scanf("%d", &choose);
	if(choose == 1){
		printf("> Enter the range of words (from ~ to) > ");
		scanf("%d %d", &num[0], &num[1]);
		printf("> Result:\n");
		for(int i=0;i<size;i++){
			if(num[0]<= c[i]->count && c[i]->count <= num[1]){
				printf("[%2d] %-20s %10d words [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
				sum++;
			}
		}
		printf("> %d Books are found.\n", sum);
		return;
	}
	if(choose == 2){
		printf("> Enter a names > ");
		scanf("%s", &name);
		
		printf("> Result:\n");
		for(int i=0;i<size;i++){
			re = strstr(c[i]->name, name);
			if(re != NULL){
				printf("[%2d] %-20s %10d words [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
				sum++;
			}
		}
		printf("> %d Books are found.\n", sum);
		return;
	}
	else{
		printf("not\n");
		return;
	}
	return;
}

void updateBook(struct st_Book* c[], int size){
/*
파라미터 : 채널정보를 저장된 구조체 포인터 배열 c, 채널정보 구조체의 개수 size
리턴값 : 없음
하는 일 : 사용자가 입력한 번호에 해당하는 채널에 대해 새로운 정보(채널명, 단어수)를 입력받아 변경한다.
변경할 채널 번호를 입력받는다. 
사이즈만큼 반복
	만약 입력받은 번호가 존재하지 않는다면 메세지출력 후 함수 종료 
*/
	int Book;
	//printf("size: %d\n", size);
	printf("> Modify a new Book\n");
	printf("> Enter a number of Book > ");
	scanf("%d", &Book);
	for(int i=0;i<size;i++){
		if(Book<=0 || Book>size){
			printf("> Wrong number.\n");
			return;
		}
	}
	printf("> Book Info.\n");
	printf("[%2d] %-20s %10d words [%s] \n", Book, c[Book-1]->name, c[Book-1]->count,LNAME[c[Book-1]->level]);
	printf("> Enter a new name of Book > ");
	scanf("%s", &c[Book-1]->name);
	printf("> Enter a new amount of words > ");
	scanf("%d", &c[Book-1]->count);
	printf("> Book info. is modified.\n");
	return;
}

int deleteBook(struct st_Book* c[], int size){
/*
파라미터 : 채널정보를 저장된 구조체 포인터 배열 c, 채널정보 구조체의 개수 size
리턴값 : 채널 전체 개수(삭제된 경우 size-1, 삭제 취소된 경우 size)
하는 일 : 사용자가 입력한 번호의 구조체 포인터에 연결된 채널정보를 삭제하고, 대신 마지막 번호의 채널을
연결한다. 삭제 후에는 채널 개수가 1개 줄어들었으니 size-1을 리턴한다.

*/
	int yesno;
	int Book;
	printf("> Delete a new Book\n");
	printf("> Enter a number of Book > ");
	scanf("%d", &Book);
	for(int i=0;i<size;i++){
		if(Book<=0 || Book>size){
			printf("> Wrong number.\n");
			return size;
		}
	}
	printf("> Book Info.\n");
	printf("[%2d] %-20s %10d words [%s] \n", Book, c[Book-1]->name, c[Book-1]->count,LNAME[c[Book-1]->level]);
	printf("> Do you want to delete the Book? (1:Yes 0:No) > ");
	scanf("%d", &yesno);
	if(yesno == 0){
		printf("> Canceled.");
		return size;
	}
	else{
		c[Book-1] = c[size-1];
		size--;
		printf("> Book is deleted.");
		return size;
	}
	return size;
}


void makeReport(struct st_Book* c[], int size){
/*
파라미터 : 채널정보를 저장된 구조체 포인터 배열 c, 채널정보 구조체의 개수 size
리턴값 : 없음
하는 일 : report.txt 파일에 [1]과[2] 메뉴의 출력 내용을 저장하고, Books.txt에는 현재까지 변경된
모든 책의 이름과 단어수를 저장한다.

*/

	printf("> All information of Books are saved into Books.txt.\n");
	printf("> Book Statistics are saved into report.txt.");

	FILE* file; // 파일포인터
	file = fopen("Books.txt", "w"); // 쓰기모드로 파일 연다.
	
	for(int i=0; i<size; i++){ // size만큼 반복
		fprintf(file, "%s %d\n", c[i]->name, c[i]->count); 
	}
	fclose(file);

	FILE* file2; // 파일포인터
	file2 = fopen("report.txt", "w"); // 쓰기모드로 파일 연다.
	fprintf(file, "Book List\n");
	for(int i=0; i<size; i++){ // size만큼 반복
		fprintf(file, "[%2d] %-20s %10d words [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]); 
	}
	fprintf(file,"\n");
	fprintf(file,"Statistics of Books\n");
	int num[5] = {0}, topNum[5] = {0}; // num: 등급별 채널개수, countA: 단어수 합산, topNum: 최대 단어수를 가진 채널 번호
	float countA[5] = {0};
	for(int i=0;i<size;i++){ // 단어 수가 가장 적은 채널을 기본값으로 세팅한다. 
		for(int j=0;j<5;j++){
			if(c[topNum[j]]->count >= c[i]->count){
				topNum[j] = i;
			}
		}
	}
	printf("> Statistics of Books\n");
	for(int i=0;i<size;i++){	// 한바퀴 돌리면서 케이스마다 합산한다.
		if(c[i]->level == 0){
			num[0]++;
			countA[0] = countA[0] + c[i]->count;
			if(c[topNum[0]]->count <= c[i]->count){
			topNum[0] = i;
			}
		}
		else if(c[i]->level == 1){
			num[1]++;
			countA[1] = countA[1] + c[i]->count;
			if(c[topNum[1]]->count <= c[i]->count){
			topNum[1] = i;
			}
		}
		else if(c[i]->level == 2){
			num[2]++;
			countA[2] = countA[2] + c[i]->count;
			if(c[topNum[2]]->count <= c[i]->count){
			topNum[2] = i;
			}
		}
		else if(c[i]->level == 3){
			num[3]++;
			countA[3] = countA[3] + c[i]->count;
			if(c[topNum[3]]->count <= c[i]->count){
			topNum[3] = i;
			}
		}
		else if(c[i]->level == 4){
			num[4]++;
			countA[4] = countA[4] + c[i]->count;
			if(c[topNum[4]]->count <= c[i]->count){
			topNum[4] = i;
			}
		}
		else
			return;
	}
	for(int j=0;j<5;j++){
		fprintf(file2, "%s : %d Books, Average %.1f words, Top Book : %s (%d words)\n", LNAME[j], num[j], (countA[j]/num[j]),c[topNum[j]]->name, c[topNum[j]]->count);
	}
	fclose(file); // 파일닫는다.
}