
#include <stdint.h>
#include <stddef.h>

#ifndef __RISCV_CRYPTO_INTRINSICS__
#define __RISCV_CRYPTO_INTRINSICS__

typedef uint64_t uint_xlen_t;

//
// SHA256
//
static inline uint_xlen_t _sha256sig0 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha256sig0 %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint_xlen_t _sha256sig1 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha256sig1 %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint_xlen_t _sha256sum0 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha256sum0 %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint_xlen_t _sha256sum1 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha256sum1 %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}


//
// SHA512
//
static inline uint_xlen_t _sha512sig0 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha512sig0  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint_xlen_t _sha512sig1 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha512sig1  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint_xlen_t _sha512sum0 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha512sum0  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint_xlen_t _sha512sum1 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__ ("sha512sum1  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}


//
// AES
//
static inline uint_xlen_t _aes64ks1i  (uint_xlen_t rs1, int      rnum) {uint_xlen_t rd; __asm__("aes64ks1i %0, %1, %2" : "=r"(rd) : "r"(rs1), "i"(rnum)); return rd;}
static inline uint_xlen_t _aes64ks2   (uint_xlen_t rs1, uint_xlen_t rs2 ) {uint_xlen_t rd; __asm__("aes64ks2  %0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2 )); return rd;}
static inline uint_xlen_t _aes64im    (uint_xlen_t rs1               ) {uint_xlen_t rd; __asm__("aes64im   %0, %1    " : "=r"(rd) : "r"(rs1)           ); return rd;}
static inline uint_xlen_t _aes64esm   (uint_xlen_t rs1, uint_xlen_t rs2 ) {uint_xlen_t rd; __asm__("aes64esm  %0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2 )); return rd;}
static inline uint_xlen_t _aes64es    (uint_xlen_t rs1, uint_xlen_t rs2 ) {uint_xlen_t rd; __asm__("aes64es   %0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2 )); return rd;}
static inline uint_xlen_t _aes64dsm   (uint_xlen_t rs1, uint_xlen_t rs2 ) {uint_xlen_t rd; __asm__("aes64dsm  %0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2 )); return rd;}
static inline uint_xlen_t _aes64ds    (uint_xlen_t rs1, uint_xlen_t rs2 ) {uint_xlen_t rd; __asm__("aes64ds   %0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2 )); return rd;}


//
// SM4
//
static inline uint_xlen_t _sm4ks (uint_xlen_t rs1, uint_xlen_t rs2, int bs) {uint_xlen_t rd; __asm__("sm4ks %0, %1, %2, %3" : "=r"(rd) : "r"(rs1), "r"(rs2), "i"(bs)); return rd;}
static inline uint_xlen_t _sm4ed (uint_xlen_t rs1, uint_xlen_t rs2, int bs) {uint_xlen_t rd; __asm__("sm4ed %0, %1, %2, %3" : "=r"(rd) : "r"(rs1), "r"(rs2), "i"(bs)); return rd;}

//
// SM3
//
static inline uint_xlen_t _sm3p0 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__("sm3p0 %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint_xlen_t _sm3p1 (uint_xlen_t rs1) {uint_xlen_t rd; __asm__("sm3p1 %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}

#endif // __RISCV_CRYPTO_INTRINSICS__

