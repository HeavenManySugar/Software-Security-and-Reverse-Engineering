#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void get_serial(const char* username, char* serial) {
    int expected_serial_val = 0;
    size_t user_len = strlen(username);
    for (size_t i = 0; i < user_len; ++i) {
        expected_serial_val += (unsigned char)username[i];
    }
    int expected = (expected_serial_val * 0xBEEF) % 0x10000;
    /* serial buffer provided by caller is 9 bytes (8 digits + null) */
    snprintf(serial, 9, "%08d", expected);
}
int main() {
    char username[50];
    char serial[9]; // 8 digits + null terminator
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Generated serial: ");
    get_serial(username, serial);
    printf("%s\n", serial);
    return 0;
}
