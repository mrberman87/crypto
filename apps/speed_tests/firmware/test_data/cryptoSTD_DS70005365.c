/* cryptoSTD_DS70005365.c

   This package provides test data for the AES Electronic Code Book
   (i.e., Direct) operating mode.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_generate.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "DS70005365"

const CPU_CHAR appNoteReference[] = "SAML11 Security Guide AN5365 (DS70005365A)";

/*************************************************************
 * Raw (input) data definitions providing small-block constants.
 *************************************************************/
#if defined(HAVE_AES_ECB)
static CONST cryptoST_testVector_t ds_001122 =
{
    .name = DATA_PACKAGE_NAME "A_AES128", // DS70005365A rev.A
    .source = appNoteReference,
    .description = "DS70005365A example", // rev.A=fig.5-3, rev.B=fig.3-11
    .vector.data = (uint8_t[]){
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    },
    .vector.length = 16,
};
#endif // HAVE_AES_ECB

#if !defined(NO_SHA256)
static CONST cryptoST_testVector_t ds_sha256 =
{
    .name = DATA_PACKAGE_NAME "A_SHA256", // DS70005365A rev.A
    .source = appNoteReference,
    .description = "DS70005365A example", // rev.A=fig.5-3, rev.B=fig.3-11
    .vector.data = (uint8_t*)"hello world",
    .vector.length = 11,
};
#endif

/*************************************************************
 * Raw (input) data definitions for run-time defined
 * sequential and random data sets having large block sizes.
 *************************************************************/

/*************************************************************
 * Key inputs and golden data and tag result definitions.
 *************************************************************/
static CONST cryptoST_testDetail_t test_item[] =
{
#if defined(HAVE_AES_ECB)
    {
        .technique = ET_AES_128,
        .mode = EM_ECB, // does not require an IV
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = appNoteReference,
        .rawData = &ds_001122,
        .key = &(const cryptoST_testData_t){ 
            .length = 16,
            .data = (uint8_t[]){
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
            },
        },
        .goldenCipher = {
            .data = (uint8_t[]){
                0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
                0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a
            },
            .length = 16,
        },
    },
#endif // HAVE_AES_ECB
#if !defined(NO_SHA256)
    {
        .technique = ET_SHA_256,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = appNoteReference,
        .rawData = &ds_sha256,
        .goldenCipher = {
            .data = (uint8_t[]){
                0xb9, 0x4d, 0x27, 0xb9, 0x93, 0x4d, 0x3e, 0x08,
                0xa5, 0x2e, 0x52, 0xd7, 0xda, 0x7d, 0xab, 0xfa,
                0xc4, 0x84, 0xef, 0xe3, 0x7a, 0x53, 0x80, 0xee,
                0x90, 0x88, 0xf7, 0xac, 0xe2, 0xef, 0xcd, 0xe9
            },
            .length = 32,
        },
    },
#endif
#if 0 // CRYA GCM is not enabled at this time
    {
        .technique = ET_AES_GCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = appNoteReference,
        .rawData = &ds_001122,
        .key = { 
            .length = 16,
            .data = (uint8_t[]){
                0xcf, 0x06, 0x3a, 0x34, 0xd4, 0xa9, 0xa7, 0x6c,
                0x2c, 0x86, 0x78, 0x7d, 0x3f, 0x95, 0xdb, 0x71
            },
        },
        .ivNonce = {         // not required for CRYA GCM
            .length = 0,
            .data = (void*)0,
        },
        .additionalAuthData = { // not required for CRYA GCM
            .length = 0,
            .data = (void*)0,
        },
        .goldenCipher = { // from the application note
            .length = 16,
            .data = (uint8_t[]){
                0xc0, 0x8a, 0x14, 0x84, 0xd1, 0x3b, 0xe1, 0xe1, 
                0x93, 0x39, 0x67, 0x14, 0x93, 0xc3, 0xcb, 0xac
            }
        },
        .goldenTag = { 
            .length = 16,
            .data = (uint8_t[]){
                0x42, 0x3b, 0x3a, 0x05, 0x65, 0x0a, 0xdc, 0x94, 
                0x42, 0x15, 0x1d, 0x51, 0x54, 0x78, 0xba, 0x0a
            },
        },
    },
#endif
    {}
};
#define test_item_count (sizeof(test_item)/sizeof(cryptoST_testDetail_t))

/*************************************************************
 * Helper functions
 *************************************************************/

/*************************************************************
 * API handlers
 *************************************************************/
static cryptoST_testDetail_t * firstTest(void)
{
    // Assume that #1 is not dynamically built
    return (1 == test_item_count)? NULL : test_item;
}
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
{
    __NOP();
    
    // Assume that if the pointer is in range, that it is legitimate.
    if (old < test_item) 
        return NULL;
    old++; // repurpose: this is now "new"
    
    // We know that the final (illegitimate) entry has a null technique,
    // but we still need to check if "old" is _way_ out of bounds.
    if ((old >= &test_item[test_item_count])
            || (ET_NONE == old->technique))
        return NULL;
    else
        return old;
}

#if 0
static char * openData(void)
{ return null; }

static char * closeData(void)
{ return null; }
#endif

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const ds70005365 =
{
    .name = DATA_PACKAGE_NAME,
    .openData = (void*)0,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = (void*)0,
};

