#include <stdio.h>

struct S { int i; char c; };

int main(void) {
    struct S s = {65, 'A'};
    printf("before: s.c = %c\n", s.c);

    int *p = &s.i;      // i를 가리키는 포인터
    p = p + 1;          // 포인터 + 1: 다음 "슬롯"으로 이동 (실제로는 c의 위치)
    *(char *)p = 'Z';   // c의 메모리를 강제로 덮어씀

    printf("after:  s.c = %c\n", s.c);
    return 0;
}
