#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_serial_format(const char *serial) {
  // Serial must be exactly 8 digits, all numeric characters
  if (strlen(serial) != 8) {
    return 0;
  }
  for (int i = 0; i < 8; i++) {
    if (!isdigit((unsigned char)serial[i])) {
      return 0;
    }
  }
  return 1;
}

static uint32_t compute_serial_value(const char *username) {
  size_t len = strlen(username);

  // First accumulator: variant of djb2-style hash
  uint32_t acc1 = 5381u;
  // Second accumulator: variant of FNV-like mixing
  uint32_t acc2 = 2166136261u;

  for (size_t i = 0; i < len; i++) {
    unsigned char c = (unsigned char)username[i];

    // Mix character with position into the first accumulator
    acc1 = ((acc1 << 5) + acc1) ^ (c + (unsigned char)i);

    // Mix into the second accumulator with a different pattern
    acc2 ^= (uint32_t)(c + (unsigned char)(i * 17));
    acc2 *= 16777619u;
  }

  // Combine the two accumulators with additional mixing
  uint32_t combined = acc1 ^ (acc2 >> 1);
  combined ^= (combined << 13);
  combined ^= (combined >> 7);
  combined ^= (combined << 17);

  // Final reduction to an 8-digit decimal number (0 ~ 99,999,999)
  uint32_t serial_val = combined % 100000000u;
  return serial_val;
}

int check_serial(const char *username, const char *serial) {
  if (!is_valid_serial_format(serial)) {
    return 0;
  }

  // Compute expected serial value from username
  uint32_t expected_val = compute_serial_value(username);

  // Convert serial string (8 digits) to integer
  char *endptr = NULL;
  unsigned long input_val = strtoul(serial, &endptr, 10);
  if (*serial == '\0' || *endptr != '\0') {
    // Not a pure numeric string
    return 0;
  }

  // Compare with expected value
  return (input_val == expected_val) ? 1 : 0;
}

int main(void) {
  char username[64];
  char serial[16]; // 8 digits + room for newline / null, just in case
  printf("Enter username: ");
  if (scanf("%63s", username) != 1) {
    fprintf(stderr, "Input error.\n");
    return 1;
  }
  printf("Enter serial (8 digits): ");
  if (scanf("%15s", serial) != 1) {
    fprintf(stderr, "Input error.\n");
    return 1;
  }
  if (check_serial(username, serial)) {
    printf("Registration successful! Welcome.\n");
  } else {
    printf("Registration failed. Please check your username or serial.\n");
  }
  return 0;
}
