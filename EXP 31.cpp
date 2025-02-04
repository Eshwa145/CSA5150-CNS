#include <stdio.h>
typedef unsigned char byte;
void print_hex(byte *data, int length) {
for (int i = 0; i < length; i++) {
printf("%02x", data[i]);
}
printf("\n");
}
void generate_subkeys(byte *initial_key, int block_size, byte *subkey1, byte *subkey2)
{ byte L[block_size / 8];
byte const_Rb[block_size / 8];
byte zero[block_size / 8] = {0};
// Calculate L
byte msb = (initial_key[0] & 0x80) ? 0x87 : 0x00;
for (int i = 0; i < block_size / 8; i++) {
L[i] = (initial_key[i] << 1) | ((i < block_size / 8 - 1) ? (initial_key[i + 1] >> 7) : 0);
subkey1[i] = L[i] ^ const_Rb[i];
}
// Left shift L
byte carry = (L[0] & 0x80) ? 1 : 0;
for (int i = 0; i < block_size / 8; i++) {
L[i] = (L[i] << 1) | carry;
carry = (L[i] & 0x80) ? 1 : 0;
}
// Calculate subkey2
for (int i = 0; i < block_size / 8; i++) {
subkey2[i] = L[i] ^ const_Rb[i];
}
}
int main() {
// Set block size (64 or 128 bits)
int block_size = 128;
byte initial_key[block_size / 8];
byte subkey1[block_size / 8];
byte subkey2[block_size / 8];
// Initialize initial_key with your key data here
// ...
// Calculate constants based on block size
byte const_Rb[block_size / 8];
if (block_size == 64) {
byte const_64 = 0x1B; // Rb for 64-bit block size
for (int i = 0; i < block_size / 8; i++) {
const_Rb[i] = const_64;
}
} else if (block_size == 128) {
byte const_128 = 0x87; // Rb for 128-bit block size
for (int i = 0; i < block_size / 8; i++) {
const_Rb[i] = const_128;
}
} else {
printf("Unsupported block size\n");
return 1;
}
generate_subkeys(initial_key, block_size, subkey1, subkey2);
printf("Subkey 1: ");
print_hex(subkey1, block_size / 8);
printf("Subkey 2: ");
print_hex(subkey2, block_size / 8);
return 0;
}
