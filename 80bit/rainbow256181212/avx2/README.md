# rainbow

Rainbow GF(256) 18, 12, 12

This is a reference implementation.

This implementation aims for introducing the algorithm, instead of efficiency.


#usage:

0. (Optional) Edit rainbow_config.h for setting (V1,O1,O2).
   The default: (18,12,12).

1. Make for 3 executables: rainbow-genkey, rainbow-sign, and rainbow-verify .

2. (generate key pairs)
  rainbow-genkey  pk_file_name  sk_file_name

3. (sign a file)
  rainbow-sign  sk_file_name file_name_to_be_signed [seed]

4. (verify a signature)
  rainbow-verify  pk_file_name  signature_file_name  file_name_to_be_signed

