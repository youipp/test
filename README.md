# 21900300 박의성


## 책이름과 단어수에 따른 등급 프로그램


---- 

### 제작 의도와 메뉴별 기능을 설명하는 내용

목록에 담긴 책이름과 단어 수를 등급을 나눠서 출력해주는 프로그램 제작

책의 제목과 그 안의 단어 수 목록이 텍스트 파일로 존재한다. 그것을 불러와서 여러가지 기능을 사용할 수 있는 프로그램이다. 기능은 데이터 파일인 Book.txt 에서 책제목과 단어수를 읽어 책정보를 구축하는 기능, 어떤 책의 단어수에 해당하는 등급을 찾아내는 기능, c 배열에 size 만큼 저장된 모든 책 정보를 읽어서 책번호, 책제목, 단어수, 등급을 출력하는 기능, 책정보 배열 c에 1개의 책을 추가하고 1개 늘어난 전체 책 개수를 리턴하는 기능이다.

![1번 실행(makeutility로 빌드 후 실행).png](https://github.com/youipp/test/blob/b1/1%EB%B2%88%20%EC%8B%A4%ED%96%89(makeutility%EB%A1%9C%20%EB%B9%8C%EB%93%9C%20%ED%9B%84%20%EC%8B%A4%ED%96%89).png)

1번을 누르면 텍스트파일에 담긴 책의 정보를 사용해 등급을 알려주는 함수를 통해 정리한 목록을 출력해준다.

![2번실행.png](https://github.com/youipp/test/blob/b1/2%EB%B2%88%EC%8B%A4%ED%96%89.png)

2번을 누르면 통계가 나온다. Top Book은 이 책이 등급안에서 가장 많은 단어 수를 보유했으므로 출력해준다. 등급별로 몇 개의 책이 있는지, 평균 단어 수는 몇 개인지, 가장 단어 수가 많은 채널은 무엇인지 알려준다.

![3번실행.png](https://github.com/youipp/test/blob/b1/3%EB%B2%88%EC%8B%A4%ED%96%89.png)

3번을 누르면 몇 개의 랜덤한 책을 출력할 것인지 입력받고 그 수 만큼 랜덤한 책을 출력해준다. 

![4번실행.png](https://github.com/youipp/test/blob/b1/4%EB%B2%88%EC%8B%A4%ED%96%89.png)

4번을 누르면 단어 수 범위로 채널을 검색할 것인지, 이름으로 검색할 것인지 물어보고 단어 수 범위로 찾겠다고 답하면 그 수 안의 책을 출력해준다. 이름이면 이름이 포함된 책을 알려준다.

![5번실행.png](https://github.com/youipp/test/blob/b1/5%EB%B2%88%EC%8B%A4%ED%96%89.png)


![5번실행1.png](https://github.com/youipp/test/blob/b1/5%EB%B2%88%EC%8B%A4%ED%96%891.png)


5번을 누르면 유튜브 채널을 새로 추가할 수 있다. 이름과 구독자 수를 입력해서 추가한다.
1번을 누르면 추가한 유튜브 채널을 포함한 정보가 목록으로 출력된다.

![6번실행.png](https://github.com/youipp/test/blob/b1/6%EB%B2%88%EC%8B%A4%ED%96%89.png)

![6번실행1.png](https://github.com/youipp/test/blob/b1/6%EB%B2%88%EC%8B%A4%ED%96%891.png)

6번을 누르면 원하는 채널의 정보를 수정할 수 있다. 

![7번실행.png](https://github.com/youipp/test/blob/b1/7%EB%B2%88%EC%8B%A4%ED%96%89.png)

![7번실행1.png](https://github.com/youipp/test/blob/b1/7%EB%B2%88%EC%8B%A4%ED%96%891.png)

7번을 누르면 원하는 책을 삭제할 수 있다. 원하는 책에 마지막 책 정보를 덮어씌우고 마지막 순서인 책을 삭제한다.

![8번실행.png](https://github.com/youipp/test/blob/b1/8%EB%B2%88%EC%8B%A4%ED%96%89.png)

![8번실행1.png](https://github.com/youipp/test/blob/b1/8%EB%B2%88%EC%8B%A4%ED%96%891.png)

![8번실행2.png](https://github.com/youipp/test/blob/b1/8%EB%B2%88%EC%8B%A4%ED%96%892.png)

![8번실행3.png](https://github.com/youipp/test/blob/b1/8%EB%B2%88%EC%8B%A4%ED%96%893.png)

![8번실행4.png](https://github.com/youipp/test/blob/b1/8%EB%B2%88%EC%8B%A4%ED%96%894.png)

8번을 누르면 Books.txt 파일에 수정된 내용을 저장한다.