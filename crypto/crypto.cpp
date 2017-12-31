//
//  crypto.cpp
//  BlockChain
//
//  Created by Chung-kaiYang on 12/16/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include "crypto.h"
#include "factory.h"
#include "dialog.h"

#define ECCTYPE "secp521r1"

crypto::crypto()
{
    generateKeyPair();
}

crypto::~crypto()
{
    EC_KEY_free(m_pECCKeyPair);
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
    dialog* dialog = factory::GetDialog();
    dialog->AppendLog("Generating public/private key pairs...");

    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    BIO* pbio_key_file  = BIO_new(BIO_s_file());
    pbio_key_file = BIO_new_fp(stdout, BIO_NOCLOSE);
    m_pECCKeyPair = EC_KEY_new_by_curve_name(OBJ_txt2nid(ECCTYPE));
    EC_KEY_set_asn1_flag(m_pECCKeyPair, OPENSSL_EC_NAMED_CURVE);

    if (! (EC_KEY_generate_key(m_pECCKeyPair)))
        BIO_printf(pbio_key_file, "Failed to generate the ECC key.");

    EVP_PKEY* pkey = EVP_PKEY_new();

    if (!EVP_PKEY_assign_EC_KEY(pkey, m_pECCKeyPair))
        BIO_printf(pbio_key_file, "Failed to assign ECC key to EVP_PKEY structure.");

    m_pECCKeyPair = EVP_PKEY_get1_EC_KEY(pkey);

    EVP_PKEY_free(pkey);
    BIO_free_all(pbio_key_file);
    dialog->AppendLog("Public/private key pairs generated.");
}

ECDSA_SIG* crypto::sign(const string& message)
{
    string digest = HASH(message.c_str());
    return ECDSA_do_sign((unsigned char*)digest.c_str(), (int)digest.size(), m_pECCKeyPair);
}

bool crypto::verify(const string& message, ECDSA_SIG const * signature, EC_KEY* public_key)
{
    if(!public_key)
    {
        factory::GetDialog()->AppendLog("Public key is invalid, please enter valid public key to verify message!");
        return false;
    }

    string digest = HASH(message.c_str());

    return 1 == ECDSA_do_verify((unsigned char*)digest.c_str(), (int)digest.size(), signature, public_key);
}
