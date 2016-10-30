#include "process_tests.h"

#include "greatest/greatest.h"

#include "teletype.h"

// runs multiple lines of commands and then asserts that the final answer is
// correct
TEST process_helper(size_t n, char* lines[], int16_t answer) {
    process_result_t result = {.has_value = false, .value = 0 };
    exec_state_t es;
    es_init(&es);
    for (size_t i = 0; i < n; i++) {
        tele_command_t cmd;
        char error_msg[ERROR_MSG_LENGTH];
        error_t error = parse(lines[i], &cmd, error_msg);
        if (error != E_OK) { FAIL(); }
        if (validate(&cmd, error_msg) != E_OK) { FAIL(); }
        result = process(&es, &cmd);
    }
    ASSERT_EQ(result.has_value, true);
    ASSERT_EQ(result.value, answer);

    PASS();
}

TEST test_numbers() {
    // beware of global state!!!
    char* test1[1] = { "1" };
    CHECK_CALL(process_helper(1, test1, 1));

    char* test2[1] = { "2" };
    CHECK_CALL(process_helper(1, test2, 2));

    char* test3[1] = { "0" };
    CHECK_CALL(process_helper(1, test3, 0));

    char* test4[1] = { "-1" };
    CHECK_CALL(process_helper(1, test4, -1));

    PASS();
}

TEST test_ADD() {
    // beware of global state!!!
    char* test1[1] = { "ADD 5 6" };
    CHECK_CALL(process_helper(1, test1, 11));

    char* test2[1] = { "ADD 2 -2" };
    CHECK_CALL(process_helper(1, test2, 0));

    PASS();
}

TEST test_IF() {
    // beware of global state!!!
    char* test1[3] = { "X 0", "IF 1 : X 1", "X" };
    CHECK_CALL(process_helper(3, test1, 1));

    char* test2[3] = { "X 0", "IF 0 : X 1", "X" };
    CHECK_CALL(process_helper(3, test2, 0));

    char* test3[3] = { "PN 0 0 0", "IF 1 : PN 0 0 1", "PN 0 0" };
    CHECK_CALL(process_helper(3, test3, 1));

    char* test4[3] = { "PN 0 0 0", "IF 0 : PN 0 0 1", "PN 0 0" };
    CHECK_CALL(process_helper(3, test4, 0));

    PASS();
}

TEST test_FLIP() {
    // beware of global state!!!
    char* test1[2] = { "FLIP 0", "FLIP" };
    CHECK_CALL(process_helper(2, test1, 0));

    char* test2[1] = { "FLIP" };
    CHECK_CALL(process_helper(1, test2, 1));

    char* test3[1] = { "FLIP" };
    CHECK_CALL(process_helper(1, test3, 0));

    char* test4[2] = { "FLIP 1", "FLIP" };
    CHECK_CALL(process_helper(2, test4, 1));

    char* test5[1] = { "FLIP" };
    CHECK_CALL(process_helper(1, test5, 0));

    char* test6[2] = { "FLIP 100", "FLIP" };
    CHECK_CALL(process_helper(2, test6, 1));

    char* test7[1] = { "FLIP" };
    CHECK_CALL(process_helper(1, test7, 0));

    PASS();
}

TEST test_L() {
    // beware of global state!!!
    char* test1[3] = { "X 0", "L 1 10 : X I", "X" };
    CHECK_CALL(process_helper(3, test1, 10));

    char* test2[3] = { "X 0", "L 1 -10 : X I", "X" };
    CHECK_CALL(process_helper(3, test2, -10));

    char* test3[3] = { "X 0", "L 1 10 : X ADD X I", "X" };
    CHECK_CALL(process_helper(3, test3, 55));

    PASS();
}

TEST test_O() {
    // beware of global state!!!
    char* test1[6] = {
        "O.MIN 0", "O.MAX 63", "O.INC 1", "O.WRAP 1", "O 0", "O"
    };
    CHECK_CALL(process_helper(6, test1, 0));

    char* test2[1] = { "O" };
    CHECK_CALL(process_helper(1, test2, 1));

    char* test3[2] = { "O 0", "O" };
    CHECK_CALL(process_helper(2, test3, 0));

    char* test4[2] = { "O 63", "O" };
    CHECK_CALL(process_helper(2, test4, 63));

    char* test5[1] = { "O" };
    CHECK_CALL(process_helper(1, test5, 0));

    char* test6[4] = { "O 0", "O.INC -1", "O", "O" };
    CHECK_CALL(process_helper(4, test6, 63));

    char* test7[4] = { "O 0", "O.WRAP 0", "O", "O" };
    CHECK_CALL(process_helper(4, test7, 0));

    PASS();
}

TEST test_P() {
    // beware of global state!!!
    char* test1[2] = { "P 0 1", "P 0" };
    CHECK_CALL(process_helper(2, test1, 1));

    char* test2[2] = { "P 0 2", "P 0" };
    CHECK_CALL(process_helper(2, test2, 2));

    PASS();
}

TEST test_PN() {
    // beware of global state!!!
    char* test1[2] = { "PN 0 0 1", "PN 0 0" };
    CHECK_CALL(process_helper(2, test1, 1));

    char* test2[2] = { "PN 0 0 2", "PN 0 0" };
    CHECK_CALL(process_helper(2, test2, 2));

    char* test3[3] = { "P.N 0", "P 0 3", "PN 0 0" };
    CHECK_CALL(process_helper(3, test3, 3));

    char* test4[3] = { "P.N 0", "PN 0 0 4", "P 0" };
    CHECK_CALL(process_helper(3, test4, 4));

    PASS();
}

TEST test_Q() {
    // beware of global state!!!
    char* test1[2] = { "Q.N 16", "Q.N" };
    CHECK_CALL(process_helper(2, test1, 16));

    for (int i = 1; i <= 16; i++) {
        char buf1[20];
        char buf2[20];
        sprintf(buf1, "Q.N %d", i);
        sprintf(buf2, "Q %d", i);
        char* test2[3] = { buf1, buf2, "Q" };
        CHECK_CALL(process_helper(3, test2, 1));
    }

    for (int i = 1; i <= 16; i++) {
        char buf1[20];
        sprintf(buf1, "Q.N %d", i);
        char* test3[2] = { buf1, "Q" };
        CHECK_CALL(process_helper(2, test3, 17 - i));
    }

    // 1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16 = 136
    // 136 / 16 = 8.5
    // TODO fix Q.AVG to return 9 in this circumstance
    char* test4[1] = { "Q.AVG" };
    CHECK_CALL(process_helper(1, test4, 8));

    char* test5[2] = { "Q.AVG 5", "Q.AVG" };
    CHECK_CALL(process_helper(2, test5, 5));

    for (int i = 1; i <= 16; i++) {
        char* test6[1] = { "Q" };
        CHECK_CALL(process_helper(1, test6, 5));
    }

    PASS();
}

TEST test_X() {
    // beware of global state!!!
    char* test1[2] = { "X 0", "X" };
    CHECK_CALL(process_helper(2, test1, 0));

    char* test2[2] = { "X 10", "X" };
    CHECK_CALL(process_helper(2, test2, 10));

    char* test3[2] = { "X 10", "ADD 5 X" };
    CHECK_CALL(process_helper(2, test3, 15));

    PASS();
}

SUITE(process_suite) {
    RUN_TEST(test_numbers);
    RUN_TEST(test_ADD);
    RUN_TEST(test_IF);
    RUN_TEST(test_FLIP);
    RUN_TEST(test_L);
    RUN_TEST(test_O);
    RUN_TEST(test_P);
    RUN_TEST(test_Q);
    RUN_TEST(test_PN);
    RUN_TEST(test_X);
}
