/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

#include "mbedtls/rsa.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

/*
 * Macros.
 */


/*
 * Variables.
 */

/* rsa public & private key data. */
const char rsa_key_n[]  = "A1D46FBA2318F8DCEF16C280948B1CF27966B9B47225ED2989F8D74B45BD36049C0AAB5AD0FF003553BA843C8E12782FC5873BB89A3DC84B883D25666CD22BF3"
                          "ACD5B675969F8BEBFBCAC93FDD927C7442B178B10D1DFF9398E52316AAE0AF74E594650BDC3C670241D418684593CDA1A7B9DC4F20D2FDC6F66344074003E211";
const char rsa_key_e[]  = "010001";
const char rsa_key_d[]  = "589552BB4F2F023ADDDD5586D0C8FD857512D82080436678D07F984A29D892D31F1F7000FC5A39A0F73E27D885E47249A4148C8A5653EF69F91F8F736BA9F848"
                          "41C2D99CD8C24DE8B72B5C9BE0EDBE23F93D731749FEA9CFB4A48DD2B7F35A2703E74AA2D4DB7DE9CEEA7D763AF0ADA7AC176C4E9A22C4CDA65CEC0C65964401";
const char rsa_key_p[]  = "CD083568D2D46C44C40C1FA0101AF2155E59C70B08423112AF0C1202514BBA5210765E29FF13036F56C7495894D80CF8C3BAEE2839BACBB0B86F6A2965F60DB1";
const char rsa_key_q[]  = "CA0EEEA5E710E8E9811A6B846399420E3AE4A4C16647E426DDF8BBBCB11CD3F35CE2E4B6BCAD07AE2C0EC2ECBFCC601B207CDD77B5673E16382B1130BF465261";

/* souce context. */
uint8_t source_ctx[128];
/* encrypt context. */
uint8_t encrypt_ctx[128];
/* decrypt context. */
uint8_t decrypt_ctx[128];

/*
 * Declerations.
 */

/* encrypt function, the source_ctx_len need to <= 117. */
void rsa_encrypt(uint8_t *source_ctx, uint32_t source_ctx_len, uint8_t * encrypt_ctx);
/* decrypt function, the source_ctx_len need to <= 117. */
void rsa_decrypt(uint8_t *source_ctx, uint8_t * decrypt_ctx, uint32_t * decrypt_ctx_len);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("mbedtls_rsa_encrypt_decrypt example.\r\n");

    while(1)
    {
        /* get source context. */
        printf("input source context: ");
        uint32_t source_len;
        for (source_len = 0; source_len < 116; source_len++)
        {
            source_ctx[source_len] = getchar();
            putchar(source_ctx[source_len]);

            if (source_ctx[source_len] == '\n')
            {
                break;
            }
        }
        source_ctx[source_len] = '\0'; /* the end of str is '\0'. */

        /* encrypt. */
        printf("prepare to encrypt.\r\n");
        rsa_encrypt(source_ctx, source_len, encrypt_ctx);
        printf("rsa encrypt raw:");
        for (uint32_t i = 0; i < sizeof(encrypt_ctx); i++)
        {
            if (i % 16 == 0)
            {
                printf("\r\n");
            }
            printf("%02X ", encrypt_ctx[i]);
        }
        printf("\r\n");

        /* decrypt. */
        printf("prepare to decrypt.\r\n");
        rsa_decrypt(encrypt_ctx, decrypt_ctx, &source_len);
        printf("rsa decrypt str: %s\r\n", source_ctx);
    }
}

/* len <= 117. */
void rsa_encrypt(uint8_t *source_ctx, uint32_t source_ctx_len, uint8_t * encrypt_ctx)
{
    /* init rsa ctx. */
    mbedtls_rsa_context rsa_ctx;
    mbedtls_rsa_init(&rsa_ctx, MBEDTLS_RSA_PKCS_V15, 0);
    mbedtls_ctr_drbg_context ctr_drbg_ctx;
    mbedtls_ctr_drbg_init(&ctr_drbg_ctx);
    mbedtls_entropy_context entropy_ctx;
    mbedtls_entropy_init(&entropy_ctx);
    mbedtls_ctr_drbg_seed(&ctr_drbg_ctx, mbedtls_entropy_func, &entropy_ctx, NULL, 0);

    mbedtls_mpi N; /* N = P * Q */
    mbedtls_mpi E; /* a random number, normally, the number is 65537(0x10001). */

    /* (N, E) is public key. */
    mbedtls_mpi_init(&N);
    mbedtls_mpi_read_string(&N, 16, rsa_key_n);
    mbedtls_mpi_init(&E);
    mbedtls_mpi_read_string(&E, 16, rsa_key_e);
    mbedtls_rsa_import(&rsa_ctx, &N, NULL, NULL, NULL, &E);
    mbedtls_rsa_complete(&rsa_ctx);

    /* encrypt by public key. */
    mbedtls_rsa_pkcs1_encrypt(&rsa_ctx, mbedtls_ctr_drbg_random, &ctr_drbg_ctx, MBEDTLS_RSA_PUBLIC, source_ctx_len, source_ctx, encrypt_ctx);

    /* free memory. */
    mbedtls_mpi_free(&N);
    mbedtls_mpi_free(&E);
    mbedtls_rsa_free(&rsa_ctx);
    mbedtls_ctr_drbg_free(&ctr_drbg_ctx);
    mbedtls_entropy_free(&entropy_ctx);
}

/* len <= 117. */
void rsa_decrypt(uint8_t *source_ctx, uint8_t * decrypt_ctx, uint32_t * decrypt_ctx_len)
{
    /* init rsa ctx. */
    mbedtls_rsa_context rsa_ctx;
    mbedtls_rsa_init(&rsa_ctx, MBEDTLS_RSA_PKCS_V15, 0);
    mbedtls_ctr_drbg_context ctr_drbg_ctx;
    mbedtls_ctr_drbg_init(&ctr_drbg_ctx);
    mbedtls_entropy_context entropy_ctx;
    mbedtls_entropy_init(&entropy_ctx);
    mbedtls_ctr_drbg_seed(&ctr_drbg_ctx, mbedtls_entropy_func, &entropy_ctx, NULL, 0);

    mbedtls_mpi P; /* a big prime number. */
    mbedtls_mpi Q; /* a big prime number that not equal P. */
    mbedtls_mpi N; /* N = P * Q */
    mbedtls_mpi E; /* a random number, normally, the number is 65537(0x10001). */
    mbedtls_mpi D; /* a number that ((P - 1) * (Q - 1)) % (E * D) = 1. */

    /* (N, E, D, P, Q) is private key. */
    mbedtls_mpi_init(&N);
    mbedtls_mpi_read_string(&N, 16, rsa_key_n);
    mbedtls_mpi_init(&E);
    mbedtls_mpi_read_string(&E, 16, rsa_key_e);
    mbedtls_mpi_init(&D);
    mbedtls_mpi_read_string(&D, 16, rsa_key_d);
    mbedtls_mpi_init(&P);
    mbedtls_mpi_read_string(&P, 16, rsa_key_p);
    mbedtls_mpi_init(&Q);
    mbedtls_mpi_read_string(&E, 16, rsa_key_e);
    mbedtls_rsa_import(&rsa_ctx, &N, &P, &Q, &D, &E);
    mbedtls_rsa_complete(&rsa_ctx);

    /* encrypt by public key. */
    mbedtls_rsa_pkcs1_decrypt(&rsa_ctx, mbedtls_ctr_drbg_random, &ctr_drbg_ctx, MBEDTLS_RSA_PRIVATE, (size_t*)decrypt_ctx_len, source_ctx, decrypt_ctx, 1024);

    /* free memory. */
    mbedtls_mpi_free(&N);
    mbedtls_mpi_free(&E);
    mbedtls_rsa_free(&rsa_ctx);
    mbedtls_ctr_drbg_free(&ctr_drbg_ctx);
    mbedtls_entropy_free(&entropy_ctx);
}

/* EOF. */
