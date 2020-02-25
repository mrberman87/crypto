/*******************************************************************************
  Crypto Speed Test Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cyrptoSTE_loadTests.c

  Summary:
    This file loads the available test data sets.

  Description:
    Identify all test datasets that are to be included. If a test
    is not available (per Harmony configuration) the corresponding
    dataset is omitted.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2013-2020 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/

//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "cryptoSTE_init.h"
#include "configuration.h"
#include <wolfssl/wolfcrypt/settings.h>
#include "../../test_data/cryptoSpeedTestData.h"

// Datasets are screened based on the Harmony configuration.
#if !defined(NO_SHA) // SHA1
#include "../test_data/cryptoSTD_sha1.h"
#endif
#if !defined(NO_SHA224)
#include "../test_data/cryptoSTD_sha224.h"
#endif
#if !defined(NO_SHA256)
#include "../test_data/cryptoSTD_sha256.h"
#endif
#if defined(HAVE_AES_ECB)
#include "../test_data/cryptoSTD_aesavs.h"
#include "../test_data/cryptoSTD_aes_ecb.H"
#endif
#if defined(HAVE_AES_CBC)
#include "../test_data/cryptoSTD_wolfSSL_aes_cbc.h"
#endif
#if defined(HAVE_AESGCM)
#include "../test_data/cryptoSTD_wolfSSL_aes_gcm.h"
#endif
#if defined(HAVE_AESCCM)
#include "../test_data/cryptoSTD_aes_ccm.h"
#endif
#if defined(WOLFSSL_AES_COUNTER)
#include "../test_data/cryptoSTD_wolfSSL_aes_ctr.h"
#endif
#if defined(HAVE_AESCCM)
#include "../test_data/cryptoSTD_wolfSSL_aes_ctr.h"
#endif
#if defined(WOLFSSL_AES_CFB)
#include "../test_data/cryptoSTD_wolfSSL_aes_cfb.h"
#endif
#include "../test_data/cryptoSTD_DS70005365.h"

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

/* Formulate the list of available tests.
 * Note: this is not a list of pointers, and the literal API structures
 * are _copied_ here. The instantiated size of the list is arbitrary,
 * as long as there are enough to cover the given API's, and that
 * will be verified by assertion when the list is loaded.
 *  */
static cryptoST_testAPI_t ST_list[11];
#define API_MAX (sizeof(ST_list)/sizeof(ST_list[0]))

void cryptoSTE_init(cryptoSTE_localData_t * testInformation)
{
    int numberOfLoadedAPI = 0;
    
    // Set up a fresh execution -- copy the included API's.
    // Each line here is representative of a #include above,
    // and this list determines test order.
#ifdef CRYPTOSTV_WOLFSSL_AES_CFB
    ST_list[numberOfLoadedAPI++] = wolfSSL_aes_cfb;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#ifdef CRYPTOSTV_WOLFSSL_AES_CBC
    ST_list[numberOfLoadedAPI++] = wolfSSL_aes_cbc;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#ifdef CRYPTOSTV_WOLFSSL_AES_CTR
    ST_list[numberOfLoadedAPI++] = wolfSSL_aes_ctr;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#ifdef CRYPTOSTV_WOLFSSL_AES_GCM
    ST_list[numberOfLoadedAPI++] = wolfSSL_aes_gcm;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#ifdef CRYPTOSTV_WOLFSSL_AES_CCM
    ST_list[numberOfLoadedAPI++] = microchip_aes_ccm;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#if defined(CRYPTOSTV_DS70005365)
    ST_list[numberOfLoadedAPI++] = ds70005365;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#if defined(CRYPTOSTV_SHA1)
    ST_list[numberOfLoadedAPI++] = microchip_sha1;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#if defined(CRYPTOSTV_SHA224)
    ST_list[numberOfLoadedAPI++] = microchip_sha224;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#if defined(CRYPTOSTV_SHA256)
    ST_list[numberOfLoadedAPI++] = microchip_sha256;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#ifdef CRYPTOSTD_AESAVS_H
    ST_list[numberOfLoadedAPI++] = aesavs_aes128;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
#ifdef CRYPTOSTV_AES_ECB_H
    ST_list[numberOfLoadedAPI++] = microchip_aes_ecb;
    __conditional_software_breakpoint(numberOfLoadedAPI <= API_MAX);
#endif
    
    __conditional_software_breakpoint(numberOfLoadedAPI > 0);

    // Zero-out the array to eliminate bus noise.
    *testInformation = (cryptoSTE_localData_t){0};
    testInformation->vectorAPI = ST_list;
    testInformation->numberOfVectorAPI = numberOfLoadedAPI;
}
