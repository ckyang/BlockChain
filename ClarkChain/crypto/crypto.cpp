//
//  crypto.cpp
//  ClarkChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <iostream>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include "crypto.h"

#define ECCTYPE "secp521r1"

crypto::crypto()
{
    generateKeyPair();
}

crypto::~crypto()
{
    EVP_PKEY_free(m_pkey);
    EC_KEY_free(m_myecc);
    BIO_free_all(m_pbio_key_file);
}

string crypto::HASH(const char *data)
{
    char outputBuffer[65];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, strlen(data));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);

    outputBuffer[64] = 0;
    return string(outputBuffer);
}

void crypto::generateKeyPair()
{
    cout << "Generate public/private key pairs..." << endl;

    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    m_pbio_key_file  = BIO_new(BIO_s_file());
    m_pbio_key_file = BIO_new_fp(stdout, BIO_NOCLOSE);
    m_myecc = EC_KEY_new_by_curve_name(OBJ_txt2nid(ECCTYPE));
    EC_KEY_set_asn1_flag(m_myecc, OPENSSL_EC_NAMED_CURVE);

    if (! (EC_KEY_generate_key(m_myecc)))
        BIO_printf(m_pbio_key_file, "Error generating the ECC key.");

    m_pkey = EVP_PKEY_new();

    if (!EVP_PKEY_assign_EC_KEY(m_pkey, m_myecc))
        BIO_printf(m_pbio_key_file, "Error assigning ECC key to EVP_PKEY structure.");

    m_myecc = EVP_PKEY_get1_EC_KEY(m_pkey);

//    BIO_printf(m_pbio_key_file, "ECC Key size: %d bit\n", EVP_PKEY_bits(m_pkey));
//    BIO_printf(m_pbio_key_file, "ECC Key type: %s\n", OBJ_nid2sn(EC_GROUP_get_curve_name(EC_KEY_get0_group(m_myecc))));
//    PEM_write_bio_PrivateKey(m_pbio_key_file, m_pkey, NULL, NULL, 0, 0, NULL);
//    PEM_write_bio_PUBKEY(m_pbio_key_file, m_pkey);

    cout << "Public/private key pairs generated." << endl;
}

ECDSA_SIG* crypto::sign(const string& message)
{
//    PEM_write_bio_PrivateKey(m_pbio_key_file, m_pkey, NULL, NULL, 0, 0, NULL);
//    PEM_write_bio_PUBKEY(m_pbio_key_file, m_pkey);

    EC_KEY* private_key = EC_KEY_new();
//    EC_KEY_set_group(private_key, EC_GROUP_new_by_curve_name(OBJ_txt2nid(ECCTYPE)));
    EC_KEY_generate_key(private_key);

//    private_key = PEM_read_bio_ECPrivateKey(m_pbio_key_file, &m_myecc, NULL, NULL);
//    EC_KEY* private_key = PEM_read_bio_ECPrivateKey(m_pbio_key_file, NULL, NULL, NULL);
//    private_key = m_myecc;

    if (!private_key)
    {
        cout << "Get key fail." << endl;
        return NULL;
    }

//    string digest = HASH(message.c_str());
    string digest = message;

    ECDSA_SIG *signature = ECDSA_do_sign((unsigned char*)digest.c_str(), (int)digest.size(), private_key);

    cout << "result " << ECDSA_do_verify((unsigned char*)digest.c_str(), (int)digest.size(), signature, private_key) << endl;

/*
    if (!ECDSA_sign(0, digest.c_str(), digest.size(), sig_buf, sig_len, ec_key))
    {
        printf("ECDSA_sign fail \n");
        return 0;
    }
*/
    if (private_key)
    {
        EC_KEY_free(private_key);
        private_key = NULL;
    }

    return signature;
}

bool crypto::verify(const string& message, ECDSA_SIG const * signature, EC_KEY* public_key)
{
    EC_KEY* local_public_key = PEM_read_bio_ECPrivateKey(m_pbio_key_file, NULL, NULL, NULL);
//    public_key = PEM_read_bio_EC_PUBKEY(m_pbio_key_file, NULL, NULL, NULL);

    if (!public_key)
    {
        cout << "get key fail " << endl;
        return NULL;
    }

//    string digest = HASH(message.c_str());
    string digest = message;

    return 1 == ECDSA_do_verify((unsigned char*)digest.c_str(), (int)digest.size(), signature, local_public_key);
}
