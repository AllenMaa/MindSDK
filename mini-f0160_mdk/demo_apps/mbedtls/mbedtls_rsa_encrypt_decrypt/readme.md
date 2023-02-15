# mbedtls_basic

## 实验过程

+ 读取用户输入的字符串。
+ 对用户输入的字符串进行 RSA 加密。
+ 打印加密后的内容。
+ 对加密后的内容进行解密。
+ 打印解密后的内容。

## 实验结果

mbedtls_rsa_encrypt_decrypt example.
input source context: hello, MindMotion.
prepare to encrypt.
rsa encrypt raw:
72 36 E4 41 57 99 3E C8 C1 11 01 75 58 66 E4 6B
32 78 E1 31 DC FD 67 DF 20 C9 D8 28 BE 70 B0 A2
FF A5 E8 BB 8F CA F9 57 EE E4 25 83 1D 9C DB 16
31 F2 82 E2 3A 8C 84 72 90 CB 82 38 A6 EF 7B 68
3A 14 86 66 43 1B E8 2D 9C 0E 22 49 B6 5B 89 E7
E8 95 54 18 2C D7 32 2E ED D5 45 A3 17 CC EE EB
5B 50 99 FD D8 17 A6 99 9A 22 10 34 AA 6A 6B EF
2B A3 3D 72 5C 76 63 12 93 B8 F8 80 AB 9F 9B 7F
prepare to decrypt.
rsa decrypt str: hello, MindMotion.
input source context: