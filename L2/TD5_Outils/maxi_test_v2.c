#include <stdio.h>
#include "/usr/local/include/CUnit/CUnit.h"
#include "/usr/local/include/CUnit/Basic.h"
#include "maxi.h"

int main(){

    CU_ASSERT_EQUAL( max(1,2), 2);
    CU_ASSERT_EQUAL( max(2,1), 2);

    CU_ASSERT_EQUAL( max(2,2), 2);
    CU_ASSERT_EQUAL( max(0,0), 0);
    CU_ASSERT_EQUAL( max(-1,-1), -1);

    CU_ASSERT_EQUAL( max(-1,-2), -1);
}
