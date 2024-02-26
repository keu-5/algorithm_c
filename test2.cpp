#include <iostream>
#include <cassert>

// テスト対象の関数
int add(int a, int b) {
    return a + b;
}

// テストケース1
void test_add_case1() {
    int result = add(3, 5);
    assert(result == 8);
    std::cout << "Test Case 1 Passed" << std::endl;
}

// テストケース2
void test_add_case2() {
    int result = add(-2, 7);
    assert(result == 5);
    std::cout << "Test Case 2 Passed" << std::endl;
}

// メイン関数
int main() {
    // テストケースの実行
    test_add_case1();
    test_add_case2();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

