#include "graph.h"
#include <stdio.h>

int main(void) {

    // 같은 폴더에 있다고 가정
    const char* input1 = "input1.txt";
    const char* input2 = "input2.txt";

    // 파일 존재 여부 확인 (선택사항)
    FILE* f1 = fopen(input1, "r");
    if (!f1) {
        printf("오류: %s 파일을 찾을 수 없습니다.\n", input1);
        return 1;
    }
    fclose(f1);

    FILE* f2 = fopen(input2, "r");
    if (!f2) {
        printf("오류: %s 파일을 찾을 수 없습니다.\n", input2);
        return 1;
    }
    fclose(f2);

    // 실행
    if (!processInput1(input1))
    {
        printf("오류 발생: input1 처리 중 문제 발생.\n");
        return 1;
    }
    
    int result2 = processInput2(input2);
    if (result2 == 0)
    {
        printf("오류 발생: input2 처리 중 문제 발생.\n");
        return 1;
    }
    if (result2 == -1)
    {
        printf("오류 발생: 음수 거리값 문제.\n");
        return 1;
    }

    return 0;
}
