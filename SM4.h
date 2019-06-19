/**
 * \file sm4.h
 */
#ifndef _SM4_H
#define _SM4_H

#define SM4_ENCRYPT     1
#define SM4_DECRYPT     0

#define SM4_ECB         1
#define SM4_CBC         0

#define SMS4_KEY_LENGTH		16
#define SMS4_BLOCK_SIZE		16
#define SMS4_NUM_ROUNDS		32

#include <sys/types.h>
#include <stdint.h>
#include <string.h>
/**
 * \brief          SM4 context structure
 */
typedef struct
{
    int mode;                   /*!<  encrypt/decrypt   */
    unsigned long sk[32];       /*!<  SM4 subkeys       */
}
sm4_context;

typedef struct
{
    int buf_len;
    unsigned char buf[32];/* saved partial block */
    unsigned char iv[16];
    int block_size;
    int final_used;
    int block_mask;
    unsigned char final[32]; /* possible final block */
    int mode;
    sm4_context key;
}sm4_cipher_ctx;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          SM4 key schedule (128-bit, encryption)
 *
 * \param ctx      SM4 context to be initialized
 * \param key      16-byte secret key
 */
void sm4_setkey_enc( sm4_context *ctx, const unsigned char key[16] );

/**
 * \brief          SM4 key schedule (128-bit, decryption)
 *
 * \param ctx      SM4 context to be initialized
 * \param key      16-byte secret key
 */
void sm4_setkey_dec( sm4_context *ctx, const unsigned char key[16] );

/**
 * \brief          SM4-ECB block encryption/decryption
 * \param ctx      SM4 context
 * \param mode     SM4_ENCRYPT or SM4_DECRYPT
 * \param length   length of the input data
 * \param input    input block
 * \param output   output block
 */
void sm4_crypt_ecb(const sm4_context *ctx,
		    int mode,
		    size_t length,
                    const unsigned char *input,
                     unsigned char *output);

/**
 * \brief          SM4-CBC buffer encryption/decryption
 * \param ctx      SM4 context
 * \param mode     SM4_ENCRYPT or SM4_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
void sm4_crypt_cbc(const sm4_context *ctx,
                     int mode,
                     size_t length,
                     unsigned char iv[16],
                     const unsigned char *input,
                     unsigned char *output );

int sms4_init_key(sm4_cipher_ctx *ctx, const unsigned char *key, int enc);

int sms4_ecb_cipher(sm4_cipher_ctx *ctx, unsigned char *out, const unsigned char *in, size_t inl);

int sms4_cbc_cipher(sm4_cipher_ctx *ctx, unsigned char *out, const unsigned char *in, size_t inl);

int SM4_encrypt_init(sm4_cipher_ctx *ctx, const unsigned char *key,
                      const unsigned char *iv, int mode);

int SM4_encrypt_update(sm4_cipher_ctx *ctx, unsigned char *out, unsigned int *outl,
                     const unsigned char *in, unsigned int inl);

int SM4_encrypt_final(sm4_cipher_ctx *ctx, unsigned char *out, unsigned int *outl);

int SM4_decrypt_init(sm4_cipher_ctx *ctx, const unsigned char *key,
                      const unsigned char *iv, int mode);

int SM4_decrypt_update(sm4_cipher_ctx *ctx, unsigned char *out, unsigned int *outl,
                      const unsigned char *in, unsigned int inl);

int SM4_decrypt_final(sm4_cipher_ctx *ctx, unsigned char *out, unsigned int *outl);

#ifdef __cplusplus
}
#endif

#endif /* sm4.h */
