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

void gen_serial(const char *username, char *serial) {
  uint32_t serial_val = compute_serial_value(username);
  snprintf(serial, 9, "%08u", serial_val);
}

int main(void) {
  char username[64];
  char serial[16]; // 8 digits + room for newline / null, just in case
  printf("Enter username: ");
  if (scanf("%63s", username) != 1) {
    fprintf(stderr, "Input error.\n");
    return 1;
  }
  printf("Generated serial: ");
  gen_serial(username, serial);
  printf("%s\n", serial);
  return 0;
}
