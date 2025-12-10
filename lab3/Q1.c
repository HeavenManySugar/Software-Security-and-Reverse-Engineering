#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_serial(char* username, char* serial) {
    int user_len = strlen(username);
    int serial_len = strlen(serial); 
    // Serial must be exactly 8 digits
    if (serial_len != 8) {
        return 0;
    }

    int expected_serial_val = 0;

    // Simple algorithm:
    // Sum the ASCII values of all characters in the username
    for (int i = 0; i < user_len; i++) {
        expected_serial_val += username[i];
    }
    
    // Apply additional arithmetic obfuscation
    expected_serial_val = (expected_serial_val * 0xbeef) % 0x10000;

    // Convert the input serial (string) into an integer
    int input_serial_val = atoi(serial);
    // Check if the serial matches the expected value
    if (input_serial_val == expected_serial_val) {
        return 1; // Serial is correct
    } else {
        return 0; // Serial is incorrect
    }
}
int main() {
    char username[50];
    char serial[9]; // 8 digits + null terminator
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter serial (8 digits): ");
    scanf("%8s", serial);
    if (check_serial(username, serial)) {
        printf("Registration successful! Welcome.\n");
    } else {
        printf("Registration failed. Please check your username or serial.\n");
    }
    return 0;
}
