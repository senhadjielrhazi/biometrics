/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWCrypto_AES.h	 											 //
//																			 //
//	Contents:																 //
//																			 //
//	Classes:																 //
//																			 //
//	Functions:																 //
//																			 //
//	History:	01-01-2003	 O. Senhadji El Rhazi   Created					 //
//				01-07-2003	 O. Senhadji El Rhazi   1 ere Release			     //
///////////////////////////////////////////////////////////////////////////////
//																			 //
//	Secure Workstation Suite Product										 //
//	SAGEM SA Cryptography Module											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/



#ifndef SWCRYPTO_AES_H
#define SWCRYPTO_AES_H


#ifdef SWCRYPTO_EXPORTS
#define SWCRYPTO_API __declspec(dllexport)
#else
#define SWCRYPTO_API __declspec(dllimport)
#endif

//Rijndael (pronounced Reindaal) is a block cipher, designed by Joan Daemen and Vincent Rijmen as a candidate algorithm for the AES.
//The cipher has a variable block length and key length. The authors currently specify how to use keys with a length
//of 128, 192, or 256 bits to encrypt blocks with al length of 128, 192 or 256 bits (all nine combinations of
//key length and block length are possible). Both block length and key length can be extended very easily to
// multiples of 32 bits.
class SWCRYPTO_API C_Crypto_AES
{
public:
	
	//Block Size
#define M_BLOCK_SIZE	16
	//Key Length
	typedef enum { Key16Bytes = 16 , Key24Bytes = 24 , Key32Bytes = 32} KeyLength;
	
private:
	enum { MAX_ROUNDS=14, MAX_KC=8, MAX_BC=8 };
	
public:
	//CONSTRUCTOR
	C_Crypto_AES();
	
	//DESTRUCTOR
	//virtual ~C_Crypto_AES();
	
private:
	//Auxiliary Function
	VOID C_Crypto_Xor
		(
		UCHAR* buff,
		UCHAR const* chain
		);
	
	//Convenience method to encrypt exactly one block of plaintext, assuming
	//Rijndael's default block size (128-bit).
	// in         - The plaintext
	// result     - The ciphertext generated from a plaintext using the key
	VOID C_Crypto_DefEncryptBlock
		(
		UCHAR const* in,
		UCHAR* result
		);
	
	//Convenience method to decrypt exactly one block of plaintext, assuming
	//Rijndael's default block size (128-bit).
	// in         - The ciphertext.
	// result     - The plaintext generated from a ciphertext using the session key.
	VOID C_Crypto_DefDecryptBlock
		(
		UCHAR const* in,
		UCHAR* result
		);
	
public:
	//Encrypt exactly one block of plaintext.
	// in           - The plaintext.
    // result       - The ciphertext generated from a plaintext using the key.
    VOID C_Crypto_Encrypt
		(
		VOID const* i_v_In,
		INT const i_i_Len,
		VOID* o_v_Out
		);
	
	//Decrypt exactly one block of ciphertext.
	// in         - The ciphertext.
	// result     - The plaintext generated from a ciphertext using the session key.
	VOID C_Crypto_Decrypt
		(
		VOID const* i_v_In,
		INT const i_i_Len,
		VOID* o_v_Out
		);
	
	//Expand a user-supplied key material into a session key.
	// key        - The 128/192/256-bit user-key to use.
	// keylength  - 16, 24 or 32 bytes
	// blockSize  - The block size in bytes of this Rijndael (16, 24 or 32 bytes).
	VOID C_Crypto_MakeKey
		(
		VOID const*o_pc_key, 
		KeyLength keylength
		);
	
	//Generate a user  key material.
	// keylength  - 16, 24 or 32 bytes
	VOID C_Crypto_GenerateKey
		(
		VOID *o_pc_key,
		KeyLength i_x_Key
		);
	
	//Get result of ciphertext or text length
	INT C_Crypto_Length
		(
		INT i_i_Length
		);
	
public:
	//Null chain
	static CHAR const* sm_chain0;
	
private:
	static const CHAR sm_S[256];
    static const CHAR sm_Si[256];
    static const INT sm_T1[256];
    static const INT sm_T2[256];
    static const INT sm_T3[256];
    static const INT sm_T4[256];
    static const INT sm_T5[256];
    static const INT sm_T6[256];
    static const INT sm_T7[256];
    static const INT sm_T8[256];
    static const INT sm_U1[256];
    static const INT sm_U2[256];
    static const INT sm_U3[256];
    static const INT sm_U4[256];
    static const CHAR sm_rcon[30];
	
	//Encryption (m_Ke) round key
	INT m_Ke[MAX_ROUNDS+1][MAX_BC];
	//Decryption (m_Kd) round key
    INT m_Kd[MAX_ROUNDS+1][MAX_BC];
	//Number of Rounds
	INT m_iROUNDS;
	//Chain Block
	UCHAR m_chain[M_BLOCK_SIZE + 1];
	//Auxiliary private use buffers
	INT tk[MAX_KC];
};

#endif//SWCCRYPTO_AES_H

