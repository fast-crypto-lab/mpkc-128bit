
#include "tbl_gf256v_polymul.h"
#include "gfext_sse.h"

void tbl_gf256v_polymul_32( __m128i * bs_p1_xmm , const __m128i * p1_xmm , const __m128i * p2_xmm ) {
	__m128i bs_p2_xmm[32*2];
	__m128i temp;

//p1_xmm[0]:0x0
//p1_xmm[1]:0x1
//p1_xmm[2]:0x2
//p1_xmm[3]:0x3
//p1_xmm[4]:0x4
//p1_xmm[5]:0x5
//p1_xmm[6]:0x6
//p1_xmm[7]:0x7
//p1_xmm[8]:0x8
//p1_xmm[9]:0x9
//p1_xmm[10]:0xa
//p1_xmm[11]:0xb
//p1_xmm[12]:0xc
//p1_xmm[13]:0xd
//p1_xmm[14]:0xe
//p1_xmm[15]:0xf
//p1_xmm[16]:0x10
//p1_xmm[17]:0x11
//p1_xmm[18]:0x12
//p1_xmm[19]:0x13
//p1_xmm[20]:0x14
//p1_xmm[21]:0x15
//p1_xmm[22]:0x16
//p1_xmm[23]:0x17
//p1_xmm[24]:0x18
//p1_xmm[25]:0x19
//p1_xmm[26]:0x1a
//p1_xmm[27]:0x1b
//p1_xmm[28]:0x1c
//p1_xmm[29]:0x1d
//p1_xmm[30]:0x1e
//p1_xmm[31]:0x1f
//p2_xmm[0]:0x0
//p2_xmm[1]:0x1
//p2_xmm[2]:0x2
//p2_xmm[3]:0x3
//p2_xmm[4]:0x4
//p2_xmm[5]:0x5
//p2_xmm[6]:0x6
//p2_xmm[7]:0x7
//p2_xmm[8]:0x8
//p2_xmm[9]:0x9
//p2_xmm[10]:0xa
//p2_xmm[11]:0xb
//p2_xmm[12]:0xc
//p2_xmm[13]:0xd
//p2_xmm[14]:0xe
//p2_xmm[15]:0xf
//p2_xmm[16]:0x10
//p2_xmm[17]:0x11
//p2_xmm[18]:0x12
//p2_xmm[19]:0x13
//p2_xmm[20]:0x14
//p2_xmm[21]:0x15
//p2_xmm[22]:0x16
//p2_xmm[23]:0x17
//p2_xmm[24]:0x18
//p2_xmm[25]:0x19
//p2_xmm[26]:0x1a
//p2_xmm[27]:0x1b
//p2_xmm[28]:0x1c
//p2_xmm[29]:0x1d
//p2_xmm[30]:0x1e
//p2_xmm[31]:0x1f
//bs_p1_xmm[0]:0x0
//bs_p1_xmm[1]:0x0
//bs_p1_xmm[2]:0x1
//bs_p1_xmm[3]:0x0
//bs_p1_xmm[4]:0x3
//bs_p1_xmm[5]:0x0
//bs_p1_xmm[6]:0x2
//bs_p1_xmm[7]:0x0
//bs_p1_xmm[8]:0x6
//bs_p1_xmm[9]:0x0
//bs_p1_xmm[10]:0x7
//bs_p1_xmm[11]:0x0
//bs_p1_xmm[12]:0x5
//bs_p1_xmm[13]:0x0
//bs_p1_xmm[14]:0x4
//bs_p1_xmm[15]:0x0
//bs_p1_xmm[16]:0xd
//bs_p1_xmm[17]:0x0
//bs_p1_xmm[18]:0xc
//bs_p1_xmm[19]:0x0
//bs_p1_xmm[20]:0xe
//bs_p1_xmm[21]:0x0
//bs_p1_xmm[22]:0xf
//bs_p1_xmm[23]:0x0
//bs_p1_xmm[24]:0xb
//bs_p1_xmm[25]:0x0
//bs_p1_xmm[26]:0xa
//bs_p1_xmm[27]:0x0
//bs_p1_xmm[28]:0x8
//bs_p1_xmm[29]:0x0
//bs_p1_xmm[30]:0x9
//bs_p1_xmm[31]:0x0
//bs_p1_xmm[32]:0x18
//bs_p1_xmm[33]:0x0
//bs_p1_xmm[34]:0x19
//bs_p1_xmm[35]:0x0
//bs_p1_xmm[36]:0x1b
//bs_p1_xmm[37]:0x0
//bs_p1_xmm[38]:0x1a
//bs_p1_xmm[39]:0x0
//bs_p1_xmm[40]:0x1e
//bs_p1_xmm[41]:0x0
//bs_p1_xmm[42]:0x1f
//bs_p1_xmm[43]:0x0
//bs_p1_xmm[44]:0x1d
//bs_p1_xmm[45]:0x0
//bs_p1_xmm[46]:0x1c
//bs_p1_xmm[47]:0x0
//bs_p1_xmm[48]:0x15
//bs_p1_xmm[49]:0x0
//bs_p1_xmm[50]:0x14
//bs_p1_xmm[51]:0x0
//bs_p1_xmm[52]:0x16
//bs_p1_xmm[53]:0x0
//bs_p1_xmm[54]:0x17
//bs_p1_xmm[55]:0x0
//bs_p1_xmm[56]:0x13
//bs_p1_xmm[57]:0x0
//bs_p1_xmm[58]:0x12
//bs_p1_xmm[59]:0x0
//bs_p1_xmm[60]:0x10
//bs_p1_xmm[61]:0x0
//bs_p1_xmm[62]:0x11
//bs_p1_xmm[63]:0x0
//[add,mul_const,mul_var] =  [1283, 387, 64]
//code:
//code:
bs_p1_xmm[0] = p1_xmm[0];
bs_p1_xmm[1] = p1_xmm[1];
bs_p1_xmm[2] = p1_xmm[2];
bs_p1_xmm[3] = p1_xmm[3];
bs_p1_xmm[4] = p1_xmm[4];
bs_p1_xmm[5] = p1_xmm[5];
bs_p1_xmm[6] = p1_xmm[6];
bs_p1_xmm[7] = p1_xmm[7];
bs_p1_xmm[8] = p1_xmm[8];
bs_p1_xmm[9] = p1_xmm[9];
bs_p1_xmm[10] = p1_xmm[10];
bs_p1_xmm[11] = p1_xmm[11];
bs_p1_xmm[12] = p1_xmm[12];
bs_p1_xmm[13] = p1_xmm[13];
bs_p1_xmm[14] = p1_xmm[14];
bs_p1_xmm[15] = p1_xmm[15];
bs_p1_xmm[16] = p1_xmm[16];
bs_p1_xmm[17] = p1_xmm[17];
bs_p1_xmm[18] = p1_xmm[18];
bs_p1_xmm[19] = p1_xmm[19];
bs_p1_xmm[20] = p1_xmm[20];
bs_p1_xmm[21] = p1_xmm[21];
bs_p1_xmm[22] = p1_xmm[22];
bs_p1_xmm[23] = p1_xmm[23];
bs_p1_xmm[24] = p1_xmm[24];
bs_p1_xmm[25] = p1_xmm[25];
bs_p1_xmm[26] = p1_xmm[26];
bs_p1_xmm[27] = p1_xmm[27];
bs_p1_xmm[28] = p1_xmm[28];
bs_p1_xmm[29] = p1_xmm[29];
bs_p1_xmm[30] = p1_xmm[30];
bs_p1_xmm[31] = p1_xmm[31];
bs_p1_xmm[16] = bs_p1_xmm[16] ^ bs_p1_xmm[31];
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[30];
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[29];
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[28];
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[27];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[26];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[25];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[24];
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[23];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[22];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[21];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[20];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[19];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[18];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[17];
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[16];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[15];
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[14];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[13];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[12];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[11];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[10];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[9];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[8];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[7];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[6];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[5];
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[4];
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[15];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[14];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[13];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[12];
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[12];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[13];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[14];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[15];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[8];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[9];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[10];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[11];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[3];
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[2];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[7];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[6];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[11];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[10];
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[15];
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[14];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[31];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[30];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[29];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[28];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[27];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[26];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[25];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[24];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[23];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[22];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[21];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[20];
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[31];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[30];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[29];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[28];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[28];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[29];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[30];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[31];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[24];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[25];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[26];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[27];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[19];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[18];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[23];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[22];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[27];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[26];
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[31];
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[30];
bs_p1_xmm[32] = bs_p1_xmm[0];
bs_p1_xmm[33] = bs_p1_xmm[1];
bs_p1_xmm[34] = bs_p1_xmm[2];
bs_p1_xmm[35] = bs_p1_xmm[3];
bs_p1_xmm[36] = bs_p1_xmm[4];
bs_p1_xmm[37] = bs_p1_xmm[5];
bs_p1_xmm[38] = bs_p1_xmm[6];
bs_p1_xmm[39] = bs_p1_xmm[7];
bs_p1_xmm[40] = bs_p1_xmm[8];
bs_p1_xmm[41] = bs_p1_xmm[9];
bs_p1_xmm[42] = bs_p1_xmm[10];
bs_p1_xmm[43] = bs_p1_xmm[11];
bs_p1_xmm[44] = bs_p1_xmm[12];
bs_p1_xmm[45] = bs_p1_xmm[13];
bs_p1_xmm[46] = bs_p1_xmm[14];
bs_p1_xmm[47] = bs_p1_xmm[15];
bs_p1_xmm[48] = bs_p1_xmm[16];
bs_p1_xmm[49] = bs_p1_xmm[17];
bs_p1_xmm[50] = bs_p1_xmm[18];
bs_p1_xmm[51] = bs_p1_xmm[19];
bs_p1_xmm[52] = bs_p1_xmm[20];
bs_p1_xmm[53] = bs_p1_xmm[21];
bs_p1_xmm[54] = bs_p1_xmm[22];
bs_p1_xmm[55] = bs_p1_xmm[23];
bs_p1_xmm[56] = bs_p1_xmm[24];
bs_p1_xmm[57] = bs_p1_xmm[25];
bs_p1_xmm[58] = bs_p1_xmm[26];
bs_p1_xmm[59] = bs_p1_xmm[27];
bs_p1_xmm[60] = bs_p1_xmm[28];
bs_p1_xmm[61] = bs_p1_xmm[29];
bs_p1_xmm[62] = bs_p1_xmm[30];
bs_p1_xmm[63] = bs_p1_xmm[31];
bs_p2_xmm[0] = p2_xmm[0];
bs_p2_xmm[1] = p2_xmm[1];
bs_p2_xmm[2] = p2_xmm[2];
bs_p2_xmm[3] = p2_xmm[3];
bs_p2_xmm[4] = p2_xmm[4];
bs_p2_xmm[5] = p2_xmm[5];
bs_p2_xmm[6] = p2_xmm[6];
bs_p2_xmm[7] = p2_xmm[7];
bs_p2_xmm[8] = p2_xmm[8];
bs_p2_xmm[9] = p2_xmm[9];
bs_p2_xmm[10] = p2_xmm[10];
bs_p2_xmm[11] = p2_xmm[11];
bs_p2_xmm[12] = p2_xmm[12];
bs_p2_xmm[13] = p2_xmm[13];
bs_p2_xmm[14] = p2_xmm[14];
bs_p2_xmm[15] = p2_xmm[15];
bs_p2_xmm[16] = p2_xmm[16];
bs_p2_xmm[17] = p2_xmm[17];
bs_p2_xmm[18] = p2_xmm[18];
bs_p2_xmm[19] = p2_xmm[19];
bs_p2_xmm[20] = p2_xmm[20];
bs_p2_xmm[21] = p2_xmm[21];
bs_p2_xmm[22] = p2_xmm[22];
bs_p2_xmm[23] = p2_xmm[23];
bs_p2_xmm[24] = p2_xmm[24];
bs_p2_xmm[25] = p2_xmm[25];
bs_p2_xmm[26] = p2_xmm[26];
bs_p2_xmm[27] = p2_xmm[27];
bs_p2_xmm[28] = p2_xmm[28];
bs_p2_xmm[29] = p2_xmm[29];
bs_p2_xmm[30] = p2_xmm[30];
bs_p2_xmm[31] = p2_xmm[31];
bs_p2_xmm[16] = bs_p2_xmm[16] ^ bs_p2_xmm[31];
bs_p2_xmm[15] = bs_p2_xmm[15] ^ bs_p2_xmm[30];
bs_p2_xmm[14] = bs_p2_xmm[14] ^ bs_p2_xmm[29];
bs_p2_xmm[13] = bs_p2_xmm[13] ^ bs_p2_xmm[28];
bs_p2_xmm[12] = bs_p2_xmm[12] ^ bs_p2_xmm[27];
bs_p2_xmm[11] = bs_p2_xmm[11] ^ bs_p2_xmm[26];
bs_p2_xmm[10] = bs_p2_xmm[10] ^ bs_p2_xmm[25];
bs_p2_xmm[9] = bs_p2_xmm[9] ^ bs_p2_xmm[24];
bs_p2_xmm[8] = bs_p2_xmm[8] ^ bs_p2_xmm[23];
bs_p2_xmm[7] = bs_p2_xmm[7] ^ bs_p2_xmm[22];
bs_p2_xmm[6] = bs_p2_xmm[6] ^ bs_p2_xmm[21];
bs_p2_xmm[5] = bs_p2_xmm[5] ^ bs_p2_xmm[20];
bs_p2_xmm[4] = bs_p2_xmm[4] ^ bs_p2_xmm[19];
bs_p2_xmm[3] = bs_p2_xmm[3] ^ bs_p2_xmm[18];
bs_p2_xmm[2] = bs_p2_xmm[2] ^ bs_p2_xmm[17];
bs_p2_xmm[1] = bs_p2_xmm[1] ^ bs_p2_xmm[16];
bs_p2_xmm[9] = bs_p2_xmm[9] ^ bs_p2_xmm[15];
bs_p2_xmm[8] = bs_p2_xmm[8] ^ bs_p2_xmm[14];
bs_p2_xmm[7] = bs_p2_xmm[7] ^ bs_p2_xmm[13];
bs_p2_xmm[6] = bs_p2_xmm[6] ^ bs_p2_xmm[12];
bs_p2_xmm[5] = bs_p2_xmm[5] ^ bs_p2_xmm[11];
bs_p2_xmm[4] = bs_p2_xmm[4] ^ bs_p2_xmm[10];
bs_p2_xmm[3] = bs_p2_xmm[3] ^ bs_p2_xmm[9];
bs_p2_xmm[2] = bs_p2_xmm[2] ^ bs_p2_xmm[8];
bs_p2_xmm[4] = bs_p2_xmm[4] ^ bs_p2_xmm[7];
bs_p2_xmm[3] = bs_p2_xmm[3] ^ bs_p2_xmm[6];
bs_p2_xmm[2] = bs_p2_xmm[2] ^ bs_p2_xmm[5];
bs_p2_xmm[1] = bs_p2_xmm[1] ^ bs_p2_xmm[4];
bs_p2_xmm[12] = bs_p2_xmm[12] ^ bs_p2_xmm[15];
bs_p2_xmm[11] = bs_p2_xmm[11] ^ bs_p2_xmm[14];
bs_p2_xmm[10] = bs_p2_xmm[10] ^ bs_p2_xmm[13];
bs_p2_xmm[9] = bs_p2_xmm[9] ^ bs_p2_xmm[12];
bs_p2_xmm[8] = bs_p2_xmm[8] ^ bs_p2_xmm[12];
bs_p2_xmm[9] = bs_p2_xmm[9] ^ bs_p2_xmm[13];
bs_p2_xmm[10] = bs_p2_xmm[10] ^ bs_p2_xmm[14];
bs_p2_xmm[11] = bs_p2_xmm[11] ^ bs_p2_xmm[15];
bs_p2_xmm[4] = bs_p2_xmm[4] ^ bs_p2_xmm[8];
bs_p2_xmm[5] = bs_p2_xmm[5] ^ bs_p2_xmm[9];
bs_p2_xmm[6] = bs_p2_xmm[6] ^ bs_p2_xmm[10];
bs_p2_xmm[7] = bs_p2_xmm[7] ^ bs_p2_xmm[11];
bs_p2_xmm[2] = bs_p2_xmm[2] ^ bs_p2_xmm[3];
bs_p2_xmm[1] = bs_p2_xmm[1] ^ bs_p2_xmm[2];
bs_p2_xmm[6] = bs_p2_xmm[6] ^ bs_p2_xmm[7];
bs_p2_xmm[5] = bs_p2_xmm[5] ^ bs_p2_xmm[6];
bs_p2_xmm[10] = bs_p2_xmm[10] ^ bs_p2_xmm[11];
bs_p2_xmm[9] = bs_p2_xmm[9] ^ bs_p2_xmm[10];
bs_p2_xmm[14] = bs_p2_xmm[14] ^ bs_p2_xmm[15];
bs_p2_xmm[13] = bs_p2_xmm[13] ^ bs_p2_xmm[14];
bs_p2_xmm[25] = bs_p2_xmm[25] ^ bs_p2_xmm[31];
bs_p2_xmm[24] = bs_p2_xmm[24] ^ bs_p2_xmm[30];
bs_p2_xmm[23] = bs_p2_xmm[23] ^ bs_p2_xmm[29];
bs_p2_xmm[22] = bs_p2_xmm[22] ^ bs_p2_xmm[28];
bs_p2_xmm[21] = bs_p2_xmm[21] ^ bs_p2_xmm[27];
bs_p2_xmm[20] = bs_p2_xmm[20] ^ bs_p2_xmm[26];
bs_p2_xmm[19] = bs_p2_xmm[19] ^ bs_p2_xmm[25];
bs_p2_xmm[18] = bs_p2_xmm[18] ^ bs_p2_xmm[24];
bs_p2_xmm[20] = bs_p2_xmm[20] ^ bs_p2_xmm[23];
bs_p2_xmm[19] = bs_p2_xmm[19] ^ bs_p2_xmm[22];
bs_p2_xmm[18] = bs_p2_xmm[18] ^ bs_p2_xmm[21];
bs_p2_xmm[17] = bs_p2_xmm[17] ^ bs_p2_xmm[20];
bs_p2_xmm[28] = bs_p2_xmm[28] ^ bs_p2_xmm[31];
bs_p2_xmm[27] = bs_p2_xmm[27] ^ bs_p2_xmm[30];
bs_p2_xmm[26] = bs_p2_xmm[26] ^ bs_p2_xmm[29];
bs_p2_xmm[25] = bs_p2_xmm[25] ^ bs_p2_xmm[28];
bs_p2_xmm[24] = bs_p2_xmm[24] ^ bs_p2_xmm[28];
bs_p2_xmm[25] = bs_p2_xmm[25] ^ bs_p2_xmm[29];
bs_p2_xmm[26] = bs_p2_xmm[26] ^ bs_p2_xmm[30];
bs_p2_xmm[27] = bs_p2_xmm[27] ^ bs_p2_xmm[31];
bs_p2_xmm[20] = bs_p2_xmm[20] ^ bs_p2_xmm[24];
bs_p2_xmm[21] = bs_p2_xmm[21] ^ bs_p2_xmm[25];
bs_p2_xmm[22] = bs_p2_xmm[22] ^ bs_p2_xmm[26];
bs_p2_xmm[23] = bs_p2_xmm[23] ^ bs_p2_xmm[27];
bs_p2_xmm[18] = bs_p2_xmm[18] ^ bs_p2_xmm[19];
bs_p2_xmm[17] = bs_p2_xmm[17] ^ bs_p2_xmm[18];
bs_p2_xmm[22] = bs_p2_xmm[22] ^ bs_p2_xmm[23];
bs_p2_xmm[21] = bs_p2_xmm[21] ^ bs_p2_xmm[22];
bs_p2_xmm[26] = bs_p2_xmm[26] ^ bs_p2_xmm[27];
bs_p2_xmm[25] = bs_p2_xmm[25] ^ bs_p2_xmm[26];
bs_p2_xmm[30] = bs_p2_xmm[30] ^ bs_p2_xmm[31];
bs_p2_xmm[29] = bs_p2_xmm[29] ^ bs_p2_xmm[30];
bs_p2_xmm[32] = bs_p2_xmm[0];
bs_p2_xmm[33] = bs_p2_xmm[1];
bs_p2_xmm[34] = bs_p2_xmm[2];
bs_p2_xmm[35] = bs_p2_xmm[3];
bs_p2_xmm[36] = bs_p2_xmm[4];
bs_p2_xmm[37] = bs_p2_xmm[5];
bs_p2_xmm[38] = bs_p2_xmm[6];
bs_p2_xmm[39] = bs_p2_xmm[7];
bs_p2_xmm[40] = bs_p2_xmm[8];
bs_p2_xmm[41] = bs_p2_xmm[9];
bs_p2_xmm[42] = bs_p2_xmm[10];
bs_p2_xmm[43] = bs_p2_xmm[11];
bs_p2_xmm[44] = bs_p2_xmm[12];
bs_p2_xmm[45] = bs_p2_xmm[13];
bs_p2_xmm[46] = bs_p2_xmm[14];
bs_p2_xmm[47] = bs_p2_xmm[15];
bs_p2_xmm[48] = bs_p2_xmm[16];
bs_p2_xmm[49] = bs_p2_xmm[17];
bs_p2_xmm[50] = bs_p2_xmm[18];
bs_p2_xmm[51] = bs_p2_xmm[19];
bs_p2_xmm[52] = bs_p2_xmm[20];
bs_p2_xmm[53] = bs_p2_xmm[21];
bs_p2_xmm[54] = bs_p2_xmm[22];
bs_p2_xmm[55] = bs_p2_xmm[23];
bs_p2_xmm[56] = bs_p2_xmm[24];
bs_p2_xmm[57] = bs_p2_xmm[25];
bs_p2_xmm[58] = bs_p2_xmm[26];
bs_p2_xmm[59] = bs_p2_xmm[27];
bs_p2_xmm[60] = bs_p2_xmm[28];
bs_p2_xmm[61] = bs_p2_xmm[29];
bs_p2_xmm[62] = bs_p2_xmm[30];
bs_p2_xmm[63] = bs_p2_xmm[31];
//butterfly_0x20( vec[32], 0x0 )
bs_p1_xmm[16] = bs_p1_xmm[16] ^ bs_p1_xmm[0];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[1];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[2];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[3];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[4];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[5];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[6];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[7];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[8];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[9];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[10];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[11];
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[12];
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[13];
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[14];
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[15];
//butterfly_0x10( vec[16], 0x0 )
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[0];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[1];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[2];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[3];
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[4];
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[5];
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[6];
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[7];
//butterfly_0x8( vec[8], 0x0 )
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[0];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[1];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[2];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[3];
//butterfly_0x4( vec[4], 0x0 )
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[0];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[1];
//butterfly_0x2( vec[2], 0x0 )
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[0];
//butterfly_0x2( vec[2], 0x2 )
temp = bs_p1_xmm[3];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[2] = bs_p1_xmm[2] ^ temp;
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[2];
//butterfly_0x4( vec[4], 0x4 )
temp = bs_p1_xmm[6];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[4] = bs_p1_xmm[4] ^ temp;
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[4];
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[5] = bs_p1_xmm[5] ^ temp;
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[5];
//butterfly_0x2( vec[2], 0x4 )
temp = bs_p1_xmm[5];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[4] = bs_p1_xmm[4] ^ temp;
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[4];
//butterfly_0x2( vec[2], 0x6 )
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[6] = bs_p1_xmm[6] ^ temp;
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[6];
//butterfly_0x8( vec[8], 0x8 )
temp = bs_p1_xmm[12];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[8] = bs_p1_xmm[8] ^ temp;
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[8];
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[9] = bs_p1_xmm[9] ^ temp;
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[9];
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[10] = bs_p1_xmm[10] ^ temp;
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[10];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[11] = bs_p1_xmm[11] ^ temp;
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[11];
//butterfly_0x4( vec[4], 0x8 )
temp = bs_p1_xmm[10];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[8] = bs_p1_xmm[8] ^ temp;
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[8];
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[9] = bs_p1_xmm[9] ^ temp;
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[9];
//butterfly_0x2( vec[2], 0x8 )
temp = bs_p1_xmm[9];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[8] = bs_p1_xmm[8] ^ temp;
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[8];
//butterfly_0x2( vec[2], 0xa )
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[10] = bs_p1_xmm[10] ^ temp;
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[10];
//butterfly_0x4( vec[4], 0xc )
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[12] = bs_p1_xmm[12] ^ temp;
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[12];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[13] = bs_p1_xmm[13] ^ temp;
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[13];
//butterfly_0x2( vec[2], 0xc )
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0xc,temp);
bs_p1_xmm[12] = bs_p1_xmm[12] ^ temp;
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[12];
//butterfly_0x2( vec[2], 0xe )
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0xe,temp);
bs_p1_xmm[14] = bs_p1_xmm[14] ^ temp;
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[14];
//butterfly_0x10( vec[16], 0x10 )
temp = bs_p1_xmm[24];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[16];
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[17] = bs_p1_xmm[17] ^ temp;
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[17];
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[18] = bs_p1_xmm[18] ^ temp;
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[18];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[19] = bs_p1_xmm[19] ^ temp;
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[19];
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[20] = bs_p1_xmm[20] ^ temp;
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[20];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[21] = bs_p1_xmm[21] ^ temp;
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[21];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[22] = bs_p1_xmm[22] ^ temp;
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[22];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[23] = bs_p1_xmm[23] ^ temp;
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[23];
//butterfly_0x8( vec[8], 0x10 )
temp = bs_p1_xmm[20];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[16];
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[17] = bs_p1_xmm[17] ^ temp;
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[17];
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[18] = bs_p1_xmm[18] ^ temp;
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[18];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[19] = bs_p1_xmm[19] ^ temp;
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[19];
//butterfly_0x4( vec[4], 0x10 )
temp = bs_p1_xmm[18];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[16];
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[17] = bs_p1_xmm[17] ^ temp;
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[17];
//butterfly_0x2( vec[2], 0x10 )
temp = bs_p1_xmm[17];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[16];
//butterfly_0x2( vec[2], 0x12 )
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[18] = bs_p1_xmm[18] ^ temp;
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[18];
//butterfly_0x4( vec[4], 0x14 )
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[20] = bs_p1_xmm[20] ^ temp;
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[20];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[21] = bs_p1_xmm[21] ^ temp;
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[21];
//butterfly_0x2( vec[2], 0x14 )
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[20] = bs_p1_xmm[20] ^ temp;
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[20];
//butterfly_0x2( vec[2], 0x16 )
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[22] = bs_p1_xmm[22] ^ temp;
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[22];
//butterfly_0x8( vec[8], 0x18 )
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[24] = bs_p1_xmm[24] ^ temp;
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[24];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[25] = bs_p1_xmm[25] ^ temp;
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[25];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[26] = bs_p1_xmm[26] ^ temp;
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[26];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[27] = bs_p1_xmm[27] ^ temp;
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[27];
//butterfly_0x4( vec[4], 0x18 )
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[24] = bs_p1_xmm[24] ^ temp;
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[24];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[25] = bs_p1_xmm[25] ^ temp;
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[25];
//butterfly_0x2( vec[2], 0x18 )
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x18,temp);
bs_p1_xmm[24] = bs_p1_xmm[24] ^ temp;
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[24];
//butterfly_0x2( vec[2], 0x1a )
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x1a,temp);
bs_p1_xmm[26] = bs_p1_xmm[26] ^ temp;
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[26];
//butterfly_0x4( vec[4], 0x1c )
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[28] = bs_p1_xmm[28] ^ temp;
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[28];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[29] = bs_p1_xmm[29] ^ temp;
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[29];
//butterfly_0x2( vec[2], 0x1c )
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[28] = bs_p1_xmm[28] ^ temp;
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[28];
//butterfly_0x2( vec[2], 0x1e )
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[30] = bs_p1_xmm[30] ^ temp;
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[30];
//butterfly_0x20( vec[32], 0x20 )
temp = bs_p1_xmm[48];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[48] = bs_p1_xmm[48] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
bs_p1_xmm[49] = bs_p1_xmm[49] ^ bs_p1_xmm[33];
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[34];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[35] = bs_p1_xmm[35] ^ temp;
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[35];
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[36];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[37] = bs_p1_xmm[37] ^ temp;
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[37];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[38] = bs_p1_xmm[38] ^ temp;
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[38];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[39] = bs_p1_xmm[39] ^ temp;
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[39];
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
bs_p1_xmm[56] = bs_p1_xmm[56] ^ bs_p1_xmm[40];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[41] = bs_p1_xmm[41] ^ temp;
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[41];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[42] = bs_p1_xmm[42] ^ temp;
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[42];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[43] = bs_p1_xmm[43] ^ temp;
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[43];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[44] = bs_p1_xmm[44] ^ temp;
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[44];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[45] = bs_p1_xmm[45] ^ temp;
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[45];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[46] = bs_p1_xmm[46] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[46];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[47] = bs_p1_xmm[47] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[47];
//butterfly_0x10( vec[16], 0x20 )
temp = bs_p1_xmm[40];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[40] = bs_p1_xmm[40] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[33];
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[34];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[35] = bs_p1_xmm[35] ^ temp;
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[35];
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[36];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[37] = bs_p1_xmm[37] ^ temp;
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[37];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[38] = bs_p1_xmm[38] ^ temp;
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[38];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[39] = bs_p1_xmm[39] ^ temp;
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[39];
//butterfly_0x8( vec[8], 0x20 )
temp = bs_p1_xmm[36];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[33];
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[34];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[35] = bs_p1_xmm[35] ^ temp;
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[35];
//butterfly_0x4( vec[4], 0x20 )
temp = bs_p1_xmm[34];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[33];
//butterfly_0x2( vec[2], 0x20 )
temp = bs_p1_xmm[33];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[32];
//butterfly_0x2( vec[2], 0x22 )
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[34];
//butterfly_0x4( vec[4], 0x24 )
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[36];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[37] = bs_p1_xmm[37] ^ temp;
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[37];
//butterfly_0x2( vec[2], 0x24 )
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0x24,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[36];
//butterfly_0x2( vec[2], 0x26 )
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x26,temp);
bs_p1_xmm[38] = bs_p1_xmm[38] ^ temp;
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[38];
//butterfly_0x8( vec[8], 0x28 )
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[40];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[41] = bs_p1_xmm[41] ^ temp;
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[41];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[42] = bs_p1_xmm[42] ^ temp;
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[42];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[43] = bs_p1_xmm[43] ^ temp;
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[43];
//butterfly_0x4( vec[4], 0x28 )
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[40];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[41] = bs_p1_xmm[41] ^ temp;
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[41];
//butterfly_0x2( vec[2], 0x28 )
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[40];
//butterfly_0x2( vec[2], 0x2a )
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[42] = bs_p1_xmm[42] ^ temp;
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[42];
//butterfly_0x4( vec[4], 0x2c )
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[44] = bs_p1_xmm[44] ^ temp;
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[44];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[45] = bs_p1_xmm[45] ^ temp;
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[45];
//butterfly_0x2( vec[2], 0x2c )
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x2c,temp);
bs_p1_xmm[44] = bs_p1_xmm[44] ^ temp;
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[44];
//butterfly_0x2( vec[2], 0x2e )
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x2e,temp);
bs_p1_xmm[46] = bs_p1_xmm[46] ^ temp;
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[46];
//butterfly_0x10( vec[16], 0x30 )
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
bs_p1_xmm[56] = bs_p1_xmm[56] ^ bs_p1_xmm[48];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[49] = bs_p1_xmm[49] ^ temp;
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[49];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[50] = bs_p1_xmm[50] ^ temp;
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[50];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[51] = bs_p1_xmm[51] ^ temp;
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[51];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[52] = bs_p1_xmm[52] ^ temp;
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[52];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[53] = bs_p1_xmm[53] ^ temp;
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[53];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[54] = bs_p1_xmm[54] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[54];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[55] = bs_p1_xmm[55] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[55];
//butterfly_0x8( vec[8], 0x30 )
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[48];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[49] = bs_p1_xmm[49] ^ temp;
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[49];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[50] = bs_p1_xmm[50] ^ temp;
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[50];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[51] = bs_p1_xmm[51] ^ temp;
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[51];
//butterfly_0x4( vec[4], 0x30 )
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[48];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[49] = bs_p1_xmm[49] ^ temp;
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[49];
//butterfly_0x2( vec[2], 0x30 )
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x30,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
bs_p1_xmm[49] = bs_p1_xmm[49] ^ bs_p1_xmm[48];
//butterfly_0x2( vec[2], 0x32 )
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x32,temp);
bs_p1_xmm[50] = bs_p1_xmm[50] ^ temp;
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[50];
//butterfly_0x4( vec[4], 0x34 )
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[52] = bs_p1_xmm[52] ^ temp;
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[52];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[53] = bs_p1_xmm[53] ^ temp;
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[53];
//butterfly_0x2( vec[2], 0x34 )
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x34,temp);
bs_p1_xmm[52] = bs_p1_xmm[52] ^ temp;
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[52];
//butterfly_0x2( vec[2], 0x36 )
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x36,temp);
bs_p1_xmm[54] = bs_p1_xmm[54] ^ temp;
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[54];
//butterfly_0x8( vec[8], 0x38 )
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[56] = bs_p1_xmm[56] ^ temp;
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[56];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[57] = bs_p1_xmm[57] ^ temp;
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[57];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[58] = bs_p1_xmm[58] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[58];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[59] = bs_p1_xmm[59] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[59];
//butterfly_0x4( vec[4], 0x38 )
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[56] = bs_p1_xmm[56] ^ temp;
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[56];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[57] = bs_p1_xmm[57] ^ temp;
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[57];
//butterfly_0x2( vec[2], 0x38 )
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x38,temp);
bs_p1_xmm[56] = bs_p1_xmm[56] ^ temp;
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[56];
//butterfly_0x2( vec[2], 0x3a )
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x3a,temp);
bs_p1_xmm[58] = bs_p1_xmm[58] ^ temp;
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[58];
//butterfly_0x4( vec[4], 0x3c )
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[60] = bs_p1_xmm[60] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[60];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[61] = bs_p1_xmm[61] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[61];
//butterfly_0x2( vec[2], 0x3c )
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x3c,temp);
bs_p1_xmm[60] = bs_p1_xmm[60] ^ temp;
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[60];
//butterfly_0x2( vec[2], 0x3e )
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x3e,temp);
bs_p1_xmm[62] = bs_p1_xmm[62] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[62];
//butterfly_0x20( vec[32], 0x0 )
bs_p2_xmm[16] = bs_p2_xmm[16] ^ bs_p2_xmm[0];
bs_p2_xmm[17] = bs_p2_xmm[17] ^ bs_p2_xmm[1];
bs_p2_xmm[18] = bs_p2_xmm[18] ^ bs_p2_xmm[2];
bs_p2_xmm[19] = bs_p2_xmm[19] ^ bs_p2_xmm[3];
bs_p2_xmm[20] = bs_p2_xmm[20] ^ bs_p2_xmm[4];
bs_p2_xmm[21] = bs_p2_xmm[21] ^ bs_p2_xmm[5];
bs_p2_xmm[22] = bs_p2_xmm[22] ^ bs_p2_xmm[6];
bs_p2_xmm[23] = bs_p2_xmm[23] ^ bs_p2_xmm[7];
bs_p2_xmm[24] = bs_p2_xmm[24] ^ bs_p2_xmm[8];
bs_p2_xmm[25] = bs_p2_xmm[25] ^ bs_p2_xmm[9];
bs_p2_xmm[26] = bs_p2_xmm[26] ^ bs_p2_xmm[10];
bs_p2_xmm[27] = bs_p2_xmm[27] ^ bs_p2_xmm[11];
bs_p2_xmm[28] = bs_p2_xmm[28] ^ bs_p2_xmm[12];
bs_p2_xmm[29] = bs_p2_xmm[29] ^ bs_p2_xmm[13];
bs_p2_xmm[30] = bs_p2_xmm[30] ^ bs_p2_xmm[14];
bs_p2_xmm[31] = bs_p2_xmm[31] ^ bs_p2_xmm[15];
//butterfly_0x10( vec[16], 0x0 )
bs_p2_xmm[8] = bs_p2_xmm[8] ^ bs_p2_xmm[0];
bs_p2_xmm[9] = bs_p2_xmm[9] ^ bs_p2_xmm[1];
bs_p2_xmm[10] = bs_p2_xmm[10] ^ bs_p2_xmm[2];
bs_p2_xmm[11] = bs_p2_xmm[11] ^ bs_p2_xmm[3];
bs_p2_xmm[12] = bs_p2_xmm[12] ^ bs_p2_xmm[4];
bs_p2_xmm[13] = bs_p2_xmm[13] ^ bs_p2_xmm[5];
bs_p2_xmm[14] = bs_p2_xmm[14] ^ bs_p2_xmm[6];
bs_p2_xmm[15] = bs_p2_xmm[15] ^ bs_p2_xmm[7];
//butterfly_0x8( vec[8], 0x0 )
bs_p2_xmm[4] = bs_p2_xmm[4] ^ bs_p2_xmm[0];
bs_p2_xmm[5] = bs_p2_xmm[5] ^ bs_p2_xmm[1];
bs_p2_xmm[6] = bs_p2_xmm[6] ^ bs_p2_xmm[2];
bs_p2_xmm[7] = bs_p2_xmm[7] ^ bs_p2_xmm[3];
//butterfly_0x4( vec[4], 0x0 )
bs_p2_xmm[2] = bs_p2_xmm[2] ^ bs_p2_xmm[0];
bs_p2_xmm[3] = bs_p2_xmm[3] ^ bs_p2_xmm[1];
//butterfly_0x2( vec[2], 0x0 )
bs_p2_xmm[1] = bs_p2_xmm[1] ^ bs_p2_xmm[0];
//butterfly_0x2( vec[2], 0x2 )
temp = bs_p2_xmm[3];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[2] = bs_p2_xmm[2] ^ temp;
bs_p2_xmm[3] = bs_p2_xmm[3] ^ bs_p2_xmm[2];
//butterfly_0x4( vec[4], 0x4 )
temp = bs_p2_xmm[6];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[4] = bs_p2_xmm[4] ^ temp;
bs_p2_xmm[6] = bs_p2_xmm[6] ^ bs_p2_xmm[4];
temp = bs_p2_xmm[7];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[5] = bs_p2_xmm[5] ^ temp;
bs_p2_xmm[7] = bs_p2_xmm[7] ^ bs_p2_xmm[5];
//butterfly_0x2( vec[2], 0x4 )
temp = bs_p2_xmm[5];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[4] = bs_p2_xmm[4] ^ temp;
bs_p2_xmm[5] = bs_p2_xmm[5] ^ bs_p2_xmm[4];
//butterfly_0x2( vec[2], 0x6 )
temp = bs_p2_xmm[7];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[6] = bs_p2_xmm[6] ^ temp;
bs_p2_xmm[7] = bs_p2_xmm[7] ^ bs_p2_xmm[6];
//butterfly_0x8( vec[8], 0x8 )
temp = bs_p2_xmm[12];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[8] = bs_p2_xmm[8] ^ temp;
bs_p2_xmm[12] = bs_p2_xmm[12] ^ bs_p2_xmm[8];
temp = bs_p2_xmm[13];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[9] = bs_p2_xmm[9] ^ temp;
bs_p2_xmm[13] = bs_p2_xmm[13] ^ bs_p2_xmm[9];
temp = bs_p2_xmm[14];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[10] = bs_p2_xmm[10] ^ temp;
bs_p2_xmm[14] = bs_p2_xmm[14] ^ bs_p2_xmm[10];
temp = bs_p2_xmm[15];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[11] = bs_p2_xmm[11] ^ temp;
bs_p2_xmm[15] = bs_p2_xmm[15] ^ bs_p2_xmm[11];
//butterfly_0x4( vec[4], 0x8 )
temp = bs_p2_xmm[10];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[8] = bs_p2_xmm[8] ^ temp;
bs_p2_xmm[10] = bs_p2_xmm[10] ^ bs_p2_xmm[8];
temp = bs_p2_xmm[11];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[9] = bs_p2_xmm[9] ^ temp;
bs_p2_xmm[11] = bs_p2_xmm[11] ^ bs_p2_xmm[9];
//butterfly_0x2( vec[2], 0x8 )
temp = bs_p2_xmm[9];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[8] = bs_p2_xmm[8] ^ temp;
bs_p2_xmm[9] = bs_p2_xmm[9] ^ bs_p2_xmm[8];
//butterfly_0x2( vec[2], 0xa )
temp = bs_p2_xmm[11];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[10] = bs_p2_xmm[10] ^ temp;
bs_p2_xmm[11] = bs_p2_xmm[11] ^ bs_p2_xmm[10];
//butterfly_0x4( vec[4], 0xc )
temp = bs_p2_xmm[14];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[12] = bs_p2_xmm[12] ^ temp;
bs_p2_xmm[14] = bs_p2_xmm[14] ^ bs_p2_xmm[12];
temp = bs_p2_xmm[15];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[13] = bs_p2_xmm[13] ^ temp;
bs_p2_xmm[15] = bs_p2_xmm[15] ^ bs_p2_xmm[13];
//butterfly_0x2( vec[2], 0xc )
temp = bs_p2_xmm[13];
temp = tbl_gf256_mul_const(0xc,temp);
bs_p2_xmm[12] = bs_p2_xmm[12] ^ temp;
bs_p2_xmm[13] = bs_p2_xmm[13] ^ bs_p2_xmm[12];
//butterfly_0x2( vec[2], 0xe )
temp = bs_p2_xmm[15];
temp = tbl_gf256_mul_const(0xe,temp);
bs_p2_xmm[14] = bs_p2_xmm[14] ^ temp;
bs_p2_xmm[15] = bs_p2_xmm[15] ^ bs_p2_xmm[14];
//butterfly_0x10( vec[16], 0x10 )
temp = bs_p2_xmm[24];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[16] = bs_p2_xmm[16] ^ temp;
bs_p2_xmm[24] = bs_p2_xmm[24] ^ bs_p2_xmm[16];
temp = bs_p2_xmm[25];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[17] = bs_p2_xmm[17] ^ temp;
bs_p2_xmm[25] = bs_p2_xmm[25] ^ bs_p2_xmm[17];
temp = bs_p2_xmm[26];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[18] = bs_p2_xmm[18] ^ temp;
bs_p2_xmm[26] = bs_p2_xmm[26] ^ bs_p2_xmm[18];
temp = bs_p2_xmm[27];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[19] = bs_p2_xmm[19] ^ temp;
bs_p2_xmm[27] = bs_p2_xmm[27] ^ bs_p2_xmm[19];
temp = bs_p2_xmm[28];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[20] = bs_p2_xmm[20] ^ temp;
bs_p2_xmm[28] = bs_p2_xmm[28] ^ bs_p2_xmm[20];
temp = bs_p2_xmm[29];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[21] = bs_p2_xmm[21] ^ temp;
bs_p2_xmm[29] = bs_p2_xmm[29] ^ bs_p2_xmm[21];
temp = bs_p2_xmm[30];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[22] = bs_p2_xmm[22] ^ temp;
bs_p2_xmm[30] = bs_p2_xmm[30] ^ bs_p2_xmm[22];
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[23] = bs_p2_xmm[23] ^ temp;
bs_p2_xmm[31] = bs_p2_xmm[31] ^ bs_p2_xmm[23];
//butterfly_0x8( vec[8], 0x10 )
temp = bs_p2_xmm[20];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[16] = bs_p2_xmm[16] ^ temp;
bs_p2_xmm[20] = bs_p2_xmm[20] ^ bs_p2_xmm[16];
temp = bs_p2_xmm[21];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[17] = bs_p2_xmm[17] ^ temp;
bs_p2_xmm[21] = bs_p2_xmm[21] ^ bs_p2_xmm[17];
temp = bs_p2_xmm[22];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[18] = bs_p2_xmm[18] ^ temp;
bs_p2_xmm[22] = bs_p2_xmm[22] ^ bs_p2_xmm[18];
temp = bs_p2_xmm[23];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[19] = bs_p2_xmm[19] ^ temp;
bs_p2_xmm[23] = bs_p2_xmm[23] ^ bs_p2_xmm[19];
//butterfly_0x4( vec[4], 0x10 )
temp = bs_p2_xmm[18];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[16] = bs_p2_xmm[16] ^ temp;
bs_p2_xmm[18] = bs_p2_xmm[18] ^ bs_p2_xmm[16];
temp = bs_p2_xmm[19];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[17] = bs_p2_xmm[17] ^ temp;
bs_p2_xmm[19] = bs_p2_xmm[19] ^ bs_p2_xmm[17];
//butterfly_0x2( vec[2], 0x10 )
temp = bs_p2_xmm[17];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p2_xmm[16] = bs_p2_xmm[16] ^ temp;
bs_p2_xmm[17] = bs_p2_xmm[17] ^ bs_p2_xmm[16];
//butterfly_0x2( vec[2], 0x12 )
temp = bs_p2_xmm[19];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p2_xmm[18] = bs_p2_xmm[18] ^ temp;
bs_p2_xmm[19] = bs_p2_xmm[19] ^ bs_p2_xmm[18];
//butterfly_0x4( vec[4], 0x14 )
temp = bs_p2_xmm[22];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[20] = bs_p2_xmm[20] ^ temp;
bs_p2_xmm[22] = bs_p2_xmm[22] ^ bs_p2_xmm[20];
temp = bs_p2_xmm[23];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[21] = bs_p2_xmm[21] ^ temp;
bs_p2_xmm[23] = bs_p2_xmm[23] ^ bs_p2_xmm[21];
//butterfly_0x2( vec[2], 0x14 )
temp = bs_p2_xmm[21];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p2_xmm[20] = bs_p2_xmm[20] ^ temp;
bs_p2_xmm[21] = bs_p2_xmm[21] ^ bs_p2_xmm[20];
//butterfly_0x2( vec[2], 0x16 )
temp = bs_p2_xmm[23];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p2_xmm[22] = bs_p2_xmm[22] ^ temp;
bs_p2_xmm[23] = bs_p2_xmm[23] ^ bs_p2_xmm[22];
//butterfly_0x8( vec[8], 0x18 )
temp = bs_p2_xmm[28];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[24] = bs_p2_xmm[24] ^ temp;
bs_p2_xmm[28] = bs_p2_xmm[28] ^ bs_p2_xmm[24];
temp = bs_p2_xmm[29];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[25] = bs_p2_xmm[25] ^ temp;
bs_p2_xmm[29] = bs_p2_xmm[29] ^ bs_p2_xmm[25];
temp = bs_p2_xmm[30];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[26] = bs_p2_xmm[26] ^ temp;
bs_p2_xmm[30] = bs_p2_xmm[30] ^ bs_p2_xmm[26];
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[27] = bs_p2_xmm[27] ^ temp;
bs_p2_xmm[31] = bs_p2_xmm[31] ^ bs_p2_xmm[27];
//butterfly_0x4( vec[4], 0x18 )
temp = bs_p2_xmm[26];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[24] = bs_p2_xmm[24] ^ temp;
bs_p2_xmm[26] = bs_p2_xmm[26] ^ bs_p2_xmm[24];
temp = bs_p2_xmm[27];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[25] = bs_p2_xmm[25] ^ temp;
bs_p2_xmm[27] = bs_p2_xmm[27] ^ bs_p2_xmm[25];
//butterfly_0x2( vec[2], 0x18 )
temp = bs_p2_xmm[25];
temp = tbl_gf256_mul_const(0x18,temp);
bs_p2_xmm[24] = bs_p2_xmm[24] ^ temp;
bs_p2_xmm[25] = bs_p2_xmm[25] ^ bs_p2_xmm[24];
//butterfly_0x2( vec[2], 0x1a )
temp = bs_p2_xmm[27];
temp = tbl_gf256_mul_const(0x1a,temp);
bs_p2_xmm[26] = bs_p2_xmm[26] ^ temp;
bs_p2_xmm[27] = bs_p2_xmm[27] ^ bs_p2_xmm[26];
//butterfly_0x4( vec[4], 0x1c )
temp = bs_p2_xmm[30];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[28] = bs_p2_xmm[28] ^ temp;
bs_p2_xmm[30] = bs_p2_xmm[30] ^ bs_p2_xmm[28];
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[29] = bs_p2_xmm[29] ^ temp;
bs_p2_xmm[31] = bs_p2_xmm[31] ^ bs_p2_xmm[29];
//butterfly_0x2( vec[2], 0x1c )
temp = bs_p2_xmm[29];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p2_xmm[28] = bs_p2_xmm[28] ^ temp;
bs_p2_xmm[29] = bs_p2_xmm[29] ^ bs_p2_xmm[28];
//butterfly_0x2( vec[2], 0x1e )
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p2_xmm[30] = bs_p2_xmm[30] ^ temp;
bs_p2_xmm[31] = bs_p2_xmm[31] ^ bs_p2_xmm[30];
//butterfly_0x20( vec[32], 0x20 )
temp = bs_p2_xmm[48];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[32] = bs_p2_xmm[32] ^ temp;
bs_p2_xmm[48] = bs_p2_xmm[48] ^ bs_p2_xmm[32];
temp = bs_p2_xmm[49];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[33] = bs_p2_xmm[33] ^ temp;
bs_p2_xmm[49] = bs_p2_xmm[49] ^ bs_p2_xmm[33];
temp = bs_p2_xmm[50];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[34] = bs_p2_xmm[34] ^ temp;
bs_p2_xmm[50] = bs_p2_xmm[50] ^ bs_p2_xmm[34];
temp = bs_p2_xmm[51];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[35] = bs_p2_xmm[35] ^ temp;
bs_p2_xmm[51] = bs_p2_xmm[51] ^ bs_p2_xmm[35];
temp = bs_p2_xmm[52];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[36] = bs_p2_xmm[36] ^ temp;
bs_p2_xmm[52] = bs_p2_xmm[52] ^ bs_p2_xmm[36];
temp = bs_p2_xmm[53];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[37] = bs_p2_xmm[37] ^ temp;
bs_p2_xmm[53] = bs_p2_xmm[53] ^ bs_p2_xmm[37];
temp = bs_p2_xmm[54];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[38] = bs_p2_xmm[38] ^ temp;
bs_p2_xmm[54] = bs_p2_xmm[54] ^ bs_p2_xmm[38];
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[39] = bs_p2_xmm[39] ^ temp;
bs_p2_xmm[55] = bs_p2_xmm[55] ^ bs_p2_xmm[39];
temp = bs_p2_xmm[56];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[40] = bs_p2_xmm[40] ^ temp;
bs_p2_xmm[56] = bs_p2_xmm[56] ^ bs_p2_xmm[40];
temp = bs_p2_xmm[57];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[41] = bs_p2_xmm[41] ^ temp;
bs_p2_xmm[57] = bs_p2_xmm[57] ^ bs_p2_xmm[41];
temp = bs_p2_xmm[58];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[42] = bs_p2_xmm[42] ^ temp;
bs_p2_xmm[58] = bs_p2_xmm[58] ^ bs_p2_xmm[42];
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[43] = bs_p2_xmm[43] ^ temp;
bs_p2_xmm[59] = bs_p2_xmm[59] ^ bs_p2_xmm[43];
temp = bs_p2_xmm[60];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[44] = bs_p2_xmm[44] ^ temp;
bs_p2_xmm[60] = bs_p2_xmm[60] ^ bs_p2_xmm[44];
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[45] = bs_p2_xmm[45] ^ temp;
bs_p2_xmm[61] = bs_p2_xmm[61] ^ bs_p2_xmm[45];
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[46] = bs_p2_xmm[46] ^ temp;
bs_p2_xmm[62] = bs_p2_xmm[62] ^ bs_p2_xmm[46];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[47] = bs_p2_xmm[47] ^ temp;
bs_p2_xmm[63] = bs_p2_xmm[63] ^ bs_p2_xmm[47];
//butterfly_0x10( vec[16], 0x20 )
temp = bs_p2_xmm[40];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[32] = bs_p2_xmm[32] ^ temp;
bs_p2_xmm[40] = bs_p2_xmm[40] ^ bs_p2_xmm[32];
temp = bs_p2_xmm[41];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[33] = bs_p2_xmm[33] ^ temp;
bs_p2_xmm[41] = bs_p2_xmm[41] ^ bs_p2_xmm[33];
temp = bs_p2_xmm[42];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[34] = bs_p2_xmm[34] ^ temp;
bs_p2_xmm[42] = bs_p2_xmm[42] ^ bs_p2_xmm[34];
temp = bs_p2_xmm[43];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[35] = bs_p2_xmm[35] ^ temp;
bs_p2_xmm[43] = bs_p2_xmm[43] ^ bs_p2_xmm[35];
temp = bs_p2_xmm[44];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[36] = bs_p2_xmm[36] ^ temp;
bs_p2_xmm[44] = bs_p2_xmm[44] ^ bs_p2_xmm[36];
temp = bs_p2_xmm[45];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[37] = bs_p2_xmm[37] ^ temp;
bs_p2_xmm[45] = bs_p2_xmm[45] ^ bs_p2_xmm[37];
temp = bs_p2_xmm[46];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[38] = bs_p2_xmm[38] ^ temp;
bs_p2_xmm[46] = bs_p2_xmm[46] ^ bs_p2_xmm[38];
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[39] = bs_p2_xmm[39] ^ temp;
bs_p2_xmm[47] = bs_p2_xmm[47] ^ bs_p2_xmm[39];
//butterfly_0x8( vec[8], 0x20 )
temp = bs_p2_xmm[36];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[32] = bs_p2_xmm[32] ^ temp;
bs_p2_xmm[36] = bs_p2_xmm[36] ^ bs_p2_xmm[32];
temp = bs_p2_xmm[37];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[33] = bs_p2_xmm[33] ^ temp;
bs_p2_xmm[37] = bs_p2_xmm[37] ^ bs_p2_xmm[33];
temp = bs_p2_xmm[38];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[34] = bs_p2_xmm[34] ^ temp;
bs_p2_xmm[38] = bs_p2_xmm[38] ^ bs_p2_xmm[34];
temp = bs_p2_xmm[39];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[35] = bs_p2_xmm[35] ^ temp;
bs_p2_xmm[39] = bs_p2_xmm[39] ^ bs_p2_xmm[35];
//butterfly_0x4( vec[4], 0x20 )
temp = bs_p2_xmm[34];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p2_xmm[32] = bs_p2_xmm[32] ^ temp;
bs_p2_xmm[34] = bs_p2_xmm[34] ^ bs_p2_xmm[32];
temp = bs_p2_xmm[35];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p2_xmm[33] = bs_p2_xmm[33] ^ temp;
bs_p2_xmm[35] = bs_p2_xmm[35] ^ bs_p2_xmm[33];
//butterfly_0x2( vec[2], 0x20 )
temp = bs_p2_xmm[33];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p2_xmm[32] = bs_p2_xmm[32] ^ temp;
bs_p2_xmm[33] = bs_p2_xmm[33] ^ bs_p2_xmm[32];
//butterfly_0x2( vec[2], 0x22 )
temp = bs_p2_xmm[35];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p2_xmm[34] = bs_p2_xmm[34] ^ temp;
bs_p2_xmm[35] = bs_p2_xmm[35] ^ bs_p2_xmm[34];
//butterfly_0x4( vec[4], 0x24 )
temp = bs_p2_xmm[38];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p2_xmm[36] = bs_p2_xmm[36] ^ temp;
bs_p2_xmm[38] = bs_p2_xmm[38] ^ bs_p2_xmm[36];
temp = bs_p2_xmm[39];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p2_xmm[37] = bs_p2_xmm[37] ^ temp;
bs_p2_xmm[39] = bs_p2_xmm[39] ^ bs_p2_xmm[37];
//butterfly_0x2( vec[2], 0x24 )
temp = bs_p2_xmm[37];
temp = tbl_gf256_mul_const(0x24,temp);
bs_p2_xmm[36] = bs_p2_xmm[36] ^ temp;
bs_p2_xmm[37] = bs_p2_xmm[37] ^ bs_p2_xmm[36];
//butterfly_0x2( vec[2], 0x26 )
temp = bs_p2_xmm[39];
temp = tbl_gf256_mul_const(0x26,temp);
bs_p2_xmm[38] = bs_p2_xmm[38] ^ temp;
bs_p2_xmm[39] = bs_p2_xmm[39] ^ bs_p2_xmm[38];
//butterfly_0x8( vec[8], 0x28 )
temp = bs_p2_xmm[44];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[40] = bs_p2_xmm[40] ^ temp;
bs_p2_xmm[44] = bs_p2_xmm[44] ^ bs_p2_xmm[40];
temp = bs_p2_xmm[45];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[41] = bs_p2_xmm[41] ^ temp;
bs_p2_xmm[45] = bs_p2_xmm[45] ^ bs_p2_xmm[41];
temp = bs_p2_xmm[46];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[42] = bs_p2_xmm[42] ^ temp;
bs_p2_xmm[46] = bs_p2_xmm[46] ^ bs_p2_xmm[42];
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[43] = bs_p2_xmm[43] ^ temp;
bs_p2_xmm[47] = bs_p2_xmm[47] ^ bs_p2_xmm[43];
//butterfly_0x4( vec[4], 0x28 )
temp = bs_p2_xmm[42];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p2_xmm[40] = bs_p2_xmm[40] ^ temp;
bs_p2_xmm[42] = bs_p2_xmm[42] ^ bs_p2_xmm[40];
temp = bs_p2_xmm[43];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p2_xmm[41] = bs_p2_xmm[41] ^ temp;
bs_p2_xmm[43] = bs_p2_xmm[43] ^ bs_p2_xmm[41];
//butterfly_0x2( vec[2], 0x28 )
temp = bs_p2_xmm[41];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p2_xmm[40] = bs_p2_xmm[40] ^ temp;
bs_p2_xmm[41] = bs_p2_xmm[41] ^ bs_p2_xmm[40];
//butterfly_0x2( vec[2], 0x2a )
temp = bs_p2_xmm[43];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p2_xmm[42] = bs_p2_xmm[42] ^ temp;
bs_p2_xmm[43] = bs_p2_xmm[43] ^ bs_p2_xmm[42];
//butterfly_0x4( vec[4], 0x2c )
temp = bs_p2_xmm[46];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p2_xmm[44] = bs_p2_xmm[44] ^ temp;
bs_p2_xmm[46] = bs_p2_xmm[46] ^ bs_p2_xmm[44];
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p2_xmm[45] = bs_p2_xmm[45] ^ temp;
bs_p2_xmm[47] = bs_p2_xmm[47] ^ bs_p2_xmm[45];
//butterfly_0x2( vec[2], 0x2c )
temp = bs_p2_xmm[45];
temp = tbl_gf256_mul_const(0x2c,temp);
bs_p2_xmm[44] = bs_p2_xmm[44] ^ temp;
bs_p2_xmm[45] = bs_p2_xmm[45] ^ bs_p2_xmm[44];
//butterfly_0x2( vec[2], 0x2e )
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x2e,temp);
bs_p2_xmm[46] = bs_p2_xmm[46] ^ temp;
bs_p2_xmm[47] = bs_p2_xmm[47] ^ bs_p2_xmm[46];
//butterfly_0x10( vec[16], 0x30 )
temp = bs_p2_xmm[56];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[48] = bs_p2_xmm[48] ^ temp;
bs_p2_xmm[56] = bs_p2_xmm[56] ^ bs_p2_xmm[48];
temp = bs_p2_xmm[57];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[49] = bs_p2_xmm[49] ^ temp;
bs_p2_xmm[57] = bs_p2_xmm[57] ^ bs_p2_xmm[49];
temp = bs_p2_xmm[58];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[50] = bs_p2_xmm[50] ^ temp;
bs_p2_xmm[58] = bs_p2_xmm[58] ^ bs_p2_xmm[50];
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[51] = bs_p2_xmm[51] ^ temp;
bs_p2_xmm[59] = bs_p2_xmm[59] ^ bs_p2_xmm[51];
temp = bs_p2_xmm[60];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[52] = bs_p2_xmm[52] ^ temp;
bs_p2_xmm[60] = bs_p2_xmm[60] ^ bs_p2_xmm[52];
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[53] = bs_p2_xmm[53] ^ temp;
bs_p2_xmm[61] = bs_p2_xmm[61] ^ bs_p2_xmm[53];
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[54] = bs_p2_xmm[54] ^ temp;
bs_p2_xmm[62] = bs_p2_xmm[62] ^ bs_p2_xmm[54];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[55] = bs_p2_xmm[55] ^ temp;
bs_p2_xmm[63] = bs_p2_xmm[63] ^ bs_p2_xmm[55];
//butterfly_0x8( vec[8], 0x30 )
temp = bs_p2_xmm[52];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[48] = bs_p2_xmm[48] ^ temp;
bs_p2_xmm[52] = bs_p2_xmm[52] ^ bs_p2_xmm[48];
temp = bs_p2_xmm[53];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[49] = bs_p2_xmm[49] ^ temp;
bs_p2_xmm[53] = bs_p2_xmm[53] ^ bs_p2_xmm[49];
temp = bs_p2_xmm[54];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[50] = bs_p2_xmm[50] ^ temp;
bs_p2_xmm[54] = bs_p2_xmm[54] ^ bs_p2_xmm[50];
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[51] = bs_p2_xmm[51] ^ temp;
bs_p2_xmm[55] = bs_p2_xmm[55] ^ bs_p2_xmm[51];
//butterfly_0x4( vec[4], 0x30 )
temp = bs_p2_xmm[50];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p2_xmm[48] = bs_p2_xmm[48] ^ temp;
bs_p2_xmm[50] = bs_p2_xmm[50] ^ bs_p2_xmm[48];
temp = bs_p2_xmm[51];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p2_xmm[49] = bs_p2_xmm[49] ^ temp;
bs_p2_xmm[51] = bs_p2_xmm[51] ^ bs_p2_xmm[49];
//butterfly_0x2( vec[2], 0x30 )
temp = bs_p2_xmm[49];
temp = tbl_gf256_mul_const(0x30,temp);
bs_p2_xmm[48] = bs_p2_xmm[48] ^ temp;
bs_p2_xmm[49] = bs_p2_xmm[49] ^ bs_p2_xmm[48];
//butterfly_0x2( vec[2], 0x32 )
temp = bs_p2_xmm[51];
temp = tbl_gf256_mul_const(0x32,temp);
bs_p2_xmm[50] = bs_p2_xmm[50] ^ temp;
bs_p2_xmm[51] = bs_p2_xmm[51] ^ bs_p2_xmm[50];
//butterfly_0x4( vec[4], 0x34 )
temp = bs_p2_xmm[54];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p2_xmm[52] = bs_p2_xmm[52] ^ temp;
bs_p2_xmm[54] = bs_p2_xmm[54] ^ bs_p2_xmm[52];
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p2_xmm[53] = bs_p2_xmm[53] ^ temp;
bs_p2_xmm[55] = bs_p2_xmm[55] ^ bs_p2_xmm[53];
//butterfly_0x2( vec[2], 0x34 )
temp = bs_p2_xmm[53];
temp = tbl_gf256_mul_const(0x34,temp);
bs_p2_xmm[52] = bs_p2_xmm[52] ^ temp;
bs_p2_xmm[53] = bs_p2_xmm[53] ^ bs_p2_xmm[52];
//butterfly_0x2( vec[2], 0x36 )
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0x36,temp);
bs_p2_xmm[54] = bs_p2_xmm[54] ^ temp;
bs_p2_xmm[55] = bs_p2_xmm[55] ^ bs_p2_xmm[54];
//butterfly_0x8( vec[8], 0x38 )
temp = bs_p2_xmm[60];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[56] = bs_p2_xmm[56] ^ temp;
bs_p2_xmm[60] = bs_p2_xmm[60] ^ bs_p2_xmm[56];
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[57] = bs_p2_xmm[57] ^ temp;
bs_p2_xmm[61] = bs_p2_xmm[61] ^ bs_p2_xmm[57];
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[58] = bs_p2_xmm[58] ^ temp;
bs_p2_xmm[62] = bs_p2_xmm[62] ^ bs_p2_xmm[58];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[59] = bs_p2_xmm[59] ^ temp;
bs_p2_xmm[63] = bs_p2_xmm[63] ^ bs_p2_xmm[59];
//butterfly_0x4( vec[4], 0x38 )
temp = bs_p2_xmm[58];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p2_xmm[56] = bs_p2_xmm[56] ^ temp;
bs_p2_xmm[58] = bs_p2_xmm[58] ^ bs_p2_xmm[56];
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p2_xmm[57] = bs_p2_xmm[57] ^ temp;
bs_p2_xmm[59] = bs_p2_xmm[59] ^ bs_p2_xmm[57];
//butterfly_0x2( vec[2], 0x38 )
temp = bs_p2_xmm[57];
temp = tbl_gf256_mul_const(0x38,temp);
bs_p2_xmm[56] = bs_p2_xmm[56] ^ temp;
bs_p2_xmm[57] = bs_p2_xmm[57] ^ bs_p2_xmm[56];
//butterfly_0x2( vec[2], 0x3a )
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x3a,temp);
bs_p2_xmm[58] = bs_p2_xmm[58] ^ temp;
bs_p2_xmm[59] = bs_p2_xmm[59] ^ bs_p2_xmm[58];
//butterfly_0x4( vec[4], 0x3c )
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p2_xmm[60] = bs_p2_xmm[60] ^ temp;
bs_p2_xmm[62] = bs_p2_xmm[62] ^ bs_p2_xmm[60];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p2_xmm[61] = bs_p2_xmm[61] ^ temp;
bs_p2_xmm[63] = bs_p2_xmm[63] ^ bs_p2_xmm[61];
//butterfly_0x2( vec[2], 0x3c )
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0x3c,temp);
bs_p2_xmm[60] = bs_p2_xmm[60] ^ temp;
bs_p2_xmm[61] = bs_p2_xmm[61] ^ bs_p2_xmm[60];
//butterfly_0x2( vec[2], 0x3e )
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x3e,temp);
bs_p2_xmm[62] = bs_p2_xmm[62] ^ temp;
bs_p2_xmm[63] = bs_p2_xmm[63] ^ bs_p2_xmm[62];
bs_p1_xmm[0] = tbl_gf256_mul(bs_p2_xmm[0],bs_p1_xmm[0]);
bs_p1_xmm[1] = tbl_gf256_mul(bs_p2_xmm[1],bs_p1_xmm[1]);
bs_p1_xmm[2] = tbl_gf256_mul(bs_p2_xmm[2],bs_p1_xmm[2]);
bs_p1_xmm[3] = tbl_gf256_mul(bs_p2_xmm[3],bs_p1_xmm[3]);
bs_p1_xmm[4] = tbl_gf256_mul(bs_p2_xmm[4],bs_p1_xmm[4]);
bs_p1_xmm[5] = tbl_gf256_mul(bs_p2_xmm[5],bs_p1_xmm[5]);
bs_p1_xmm[6] = tbl_gf256_mul(bs_p2_xmm[6],bs_p1_xmm[6]);
bs_p1_xmm[7] = tbl_gf256_mul(bs_p2_xmm[7],bs_p1_xmm[7]);
bs_p1_xmm[8] = tbl_gf256_mul(bs_p2_xmm[8],bs_p1_xmm[8]);
bs_p1_xmm[9] = tbl_gf256_mul(bs_p2_xmm[9],bs_p1_xmm[9]);
bs_p1_xmm[10] = tbl_gf256_mul(bs_p2_xmm[10],bs_p1_xmm[10]);
bs_p1_xmm[11] = tbl_gf256_mul(bs_p2_xmm[11],bs_p1_xmm[11]);
bs_p1_xmm[12] = tbl_gf256_mul(bs_p2_xmm[12],bs_p1_xmm[12]);
bs_p1_xmm[13] = tbl_gf256_mul(bs_p2_xmm[13],bs_p1_xmm[13]);
bs_p1_xmm[14] = tbl_gf256_mul(bs_p2_xmm[14],bs_p1_xmm[14]);
bs_p1_xmm[15] = tbl_gf256_mul(bs_p2_xmm[15],bs_p1_xmm[15]);
bs_p1_xmm[16] = tbl_gf256_mul(bs_p2_xmm[16],bs_p1_xmm[16]);
bs_p1_xmm[17] = tbl_gf256_mul(bs_p2_xmm[17],bs_p1_xmm[17]);
bs_p1_xmm[18] = tbl_gf256_mul(bs_p2_xmm[18],bs_p1_xmm[18]);
bs_p1_xmm[19] = tbl_gf256_mul(bs_p2_xmm[19],bs_p1_xmm[19]);
bs_p1_xmm[20] = tbl_gf256_mul(bs_p2_xmm[20],bs_p1_xmm[20]);
bs_p1_xmm[21] = tbl_gf256_mul(bs_p2_xmm[21],bs_p1_xmm[21]);
bs_p1_xmm[22] = tbl_gf256_mul(bs_p2_xmm[22],bs_p1_xmm[22]);
bs_p1_xmm[23] = tbl_gf256_mul(bs_p2_xmm[23],bs_p1_xmm[23]);
bs_p1_xmm[24] = tbl_gf256_mul(bs_p2_xmm[24],bs_p1_xmm[24]);
bs_p1_xmm[25] = tbl_gf256_mul(bs_p2_xmm[25],bs_p1_xmm[25]);
bs_p1_xmm[26] = tbl_gf256_mul(bs_p2_xmm[26],bs_p1_xmm[26]);
bs_p1_xmm[27] = tbl_gf256_mul(bs_p2_xmm[27],bs_p1_xmm[27]);
bs_p1_xmm[28] = tbl_gf256_mul(bs_p2_xmm[28],bs_p1_xmm[28]);
bs_p1_xmm[29] = tbl_gf256_mul(bs_p2_xmm[29],bs_p1_xmm[29]);
bs_p1_xmm[30] = tbl_gf256_mul(bs_p2_xmm[30],bs_p1_xmm[30]);
bs_p1_xmm[31] = tbl_gf256_mul(bs_p2_xmm[31],bs_p1_xmm[31]);
bs_p1_xmm[32] = tbl_gf256_mul(bs_p2_xmm[32],bs_p1_xmm[32]);
bs_p1_xmm[33] = tbl_gf256_mul(bs_p2_xmm[33],bs_p1_xmm[33]);
bs_p1_xmm[34] = tbl_gf256_mul(bs_p2_xmm[34],bs_p1_xmm[34]);
bs_p1_xmm[35] = tbl_gf256_mul(bs_p2_xmm[35],bs_p1_xmm[35]);
bs_p1_xmm[36] = tbl_gf256_mul(bs_p2_xmm[36],bs_p1_xmm[36]);
bs_p1_xmm[37] = tbl_gf256_mul(bs_p2_xmm[37],bs_p1_xmm[37]);
bs_p1_xmm[38] = tbl_gf256_mul(bs_p2_xmm[38],bs_p1_xmm[38]);
bs_p1_xmm[39] = tbl_gf256_mul(bs_p2_xmm[39],bs_p1_xmm[39]);
bs_p1_xmm[40] = tbl_gf256_mul(bs_p2_xmm[40],bs_p1_xmm[40]);
bs_p1_xmm[41] = tbl_gf256_mul(bs_p2_xmm[41],bs_p1_xmm[41]);
bs_p1_xmm[42] = tbl_gf256_mul(bs_p2_xmm[42],bs_p1_xmm[42]);
bs_p1_xmm[43] = tbl_gf256_mul(bs_p2_xmm[43],bs_p1_xmm[43]);
bs_p1_xmm[44] = tbl_gf256_mul(bs_p2_xmm[44],bs_p1_xmm[44]);
bs_p1_xmm[45] = tbl_gf256_mul(bs_p2_xmm[45],bs_p1_xmm[45]);
bs_p1_xmm[46] = tbl_gf256_mul(bs_p2_xmm[46],bs_p1_xmm[46]);
bs_p1_xmm[47] = tbl_gf256_mul(bs_p2_xmm[47],bs_p1_xmm[47]);
bs_p1_xmm[48] = tbl_gf256_mul(bs_p2_xmm[48],bs_p1_xmm[48]);
bs_p1_xmm[49] = tbl_gf256_mul(bs_p2_xmm[49],bs_p1_xmm[49]);
bs_p1_xmm[50] = tbl_gf256_mul(bs_p2_xmm[50],bs_p1_xmm[50]);
bs_p1_xmm[51] = tbl_gf256_mul(bs_p2_xmm[51],bs_p1_xmm[51]);
bs_p1_xmm[52] = tbl_gf256_mul(bs_p2_xmm[52],bs_p1_xmm[52]);
bs_p1_xmm[53] = tbl_gf256_mul(bs_p2_xmm[53],bs_p1_xmm[53]);
bs_p1_xmm[54] = tbl_gf256_mul(bs_p2_xmm[54],bs_p1_xmm[54]);
bs_p1_xmm[55] = tbl_gf256_mul(bs_p2_xmm[55],bs_p1_xmm[55]);
bs_p1_xmm[56] = tbl_gf256_mul(bs_p2_xmm[56],bs_p1_xmm[56]);
bs_p1_xmm[57] = tbl_gf256_mul(bs_p2_xmm[57],bs_p1_xmm[57]);
bs_p1_xmm[58] = tbl_gf256_mul(bs_p2_xmm[58],bs_p1_xmm[58]);
bs_p1_xmm[59] = tbl_gf256_mul(bs_p2_xmm[59],bs_p1_xmm[59]);
bs_p1_xmm[60] = tbl_gf256_mul(bs_p2_xmm[60],bs_p1_xmm[60]);
bs_p1_xmm[61] = tbl_gf256_mul(bs_p2_xmm[61],bs_p1_xmm[61]);
bs_p1_xmm[62] = tbl_gf256_mul(bs_p2_xmm[62],bs_p1_xmm[62]);
bs_p1_xmm[63] = tbl_gf256_mul(bs_p2_xmm[63],bs_p1_xmm[63]);
//ibutterfly_0x40( vec[64], 0x0 )
//ibutterfly_0x20( vec[32], 0x0 )
//ibutterfly_0x10( vec[16], 0x0 )
//ibutterfly_0x8( vec[8], 0x0 )
//ibutterfly_0x4( vec[4], 0x0 )
//ibutterfly_0x2( vec[2], 0x0 )
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[0];
//ibutterfly_0x2( vec[2], 0x2 )
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[2];
temp = bs_p1_xmm[3];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[2] = bs_p1_xmm[2] ^ temp;
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[0];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[1];
//ibutterfly_0x4( vec[4], 0x4 )
//ibutterfly_0x2( vec[2], 0x4 )
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[4];
temp = bs_p1_xmm[5];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[4] = bs_p1_xmm[4] ^ temp;
//ibutterfly_0x2( vec[2], 0x6 )
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[6];
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[6] = bs_p1_xmm[6] ^ temp;
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[4];
temp = bs_p1_xmm[6];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[4] = bs_p1_xmm[4] ^ temp;
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[5];
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[5] = bs_p1_xmm[5] ^ temp;
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[0];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[1];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[2];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[3];
//ibutterfly_0x8( vec[8], 0x8 )
//ibutterfly_0x4( vec[4], 0x8 )
//ibutterfly_0x2( vec[2], 0x8 )
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[8];
temp = bs_p1_xmm[9];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[8] = bs_p1_xmm[8] ^ temp;
//ibutterfly_0x2( vec[2], 0xa )
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[10];
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[10] = bs_p1_xmm[10] ^ temp;
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[8];
temp = bs_p1_xmm[10];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[8] = bs_p1_xmm[8] ^ temp;
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[9];
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[9] = bs_p1_xmm[9] ^ temp;
//ibutterfly_0x4( vec[4], 0xc )
//ibutterfly_0x2( vec[2], 0xc )
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[12];
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0xc,temp);
bs_p1_xmm[12] = bs_p1_xmm[12] ^ temp;
//ibutterfly_0x2( vec[2], 0xe )
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[14];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0xe,temp);
bs_p1_xmm[14] = bs_p1_xmm[14] ^ temp;
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[12];
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[12] = bs_p1_xmm[12] ^ temp;
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[13];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[13] = bs_p1_xmm[13] ^ temp;
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[8];
temp = bs_p1_xmm[12];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[8] = bs_p1_xmm[8] ^ temp;
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[9];
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[9] = bs_p1_xmm[9] ^ temp;
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[10];
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[10] = bs_p1_xmm[10] ^ temp;
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[11];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[11] = bs_p1_xmm[11] ^ temp;
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[0];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[1];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[2];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[3];
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[4];
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[5];
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[6];
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[7];
//ibutterfly_0x10( vec[16], 0x10 )
//ibutterfly_0x8( vec[8], 0x10 )
//ibutterfly_0x4( vec[4], 0x10 )
//ibutterfly_0x2( vec[2], 0x10 )
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[16];
temp = bs_p1_xmm[17];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
//ibutterfly_0x2( vec[2], 0x12 )
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[18];
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[18] = bs_p1_xmm[18] ^ temp;
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[16];
temp = bs_p1_xmm[18];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[17];
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[17] = bs_p1_xmm[17] ^ temp;
//ibutterfly_0x4( vec[4], 0x14 )
//ibutterfly_0x2( vec[2], 0x14 )
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[20];
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[20] = bs_p1_xmm[20] ^ temp;
//ibutterfly_0x2( vec[2], 0x16 )
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[22];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[22] = bs_p1_xmm[22] ^ temp;
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[20];
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[20] = bs_p1_xmm[20] ^ temp;
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[21];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[21] = bs_p1_xmm[21] ^ temp;
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[16];
temp = bs_p1_xmm[20];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[17];
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[17] = bs_p1_xmm[17] ^ temp;
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[18];
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[18] = bs_p1_xmm[18] ^ temp;
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[19];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[19] = bs_p1_xmm[19] ^ temp;
//ibutterfly_0x8( vec[8], 0x18 )
//ibutterfly_0x4( vec[4], 0x18 )
//ibutterfly_0x2( vec[2], 0x18 )
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[24];
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x18,temp);
bs_p1_xmm[24] = bs_p1_xmm[24] ^ temp;
//ibutterfly_0x2( vec[2], 0x1a )
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[26];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x1a,temp);
bs_p1_xmm[26] = bs_p1_xmm[26] ^ temp;
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[24];
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[24] = bs_p1_xmm[24] ^ temp;
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[25];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[25] = bs_p1_xmm[25] ^ temp;
//ibutterfly_0x4( vec[4], 0x1c )
//ibutterfly_0x2( vec[2], 0x1c )
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[28];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[28] = bs_p1_xmm[28] ^ temp;
//ibutterfly_0x2( vec[2], 0x1e )
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[30];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[30] = bs_p1_xmm[30] ^ temp;
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[28];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[28] = bs_p1_xmm[28] ^ temp;
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[29];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[29] = bs_p1_xmm[29] ^ temp;
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[24];
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[24] = bs_p1_xmm[24] ^ temp;
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[25];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[25] = bs_p1_xmm[25] ^ temp;
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[26];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[26] = bs_p1_xmm[26] ^ temp;
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[27];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[27] = bs_p1_xmm[27] ^ temp;
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[16];
temp = bs_p1_xmm[24];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[16] = bs_p1_xmm[16] ^ temp;
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[17];
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[17] = bs_p1_xmm[17] ^ temp;
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[18];
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[18] = bs_p1_xmm[18] ^ temp;
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[19];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[19] = bs_p1_xmm[19] ^ temp;
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[20];
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[20] = bs_p1_xmm[20] ^ temp;
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[21];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[21] = bs_p1_xmm[21] ^ temp;
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[22];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[22] = bs_p1_xmm[22] ^ temp;
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[23];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[23] = bs_p1_xmm[23] ^ temp;
bs_p1_xmm[16] = bs_p1_xmm[16] ^ bs_p1_xmm[0];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[1];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[2];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[3];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[4];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[5];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[6];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[7];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[8];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[9];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[10];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[11];
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[12];
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[13];
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[14];
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[15];
//ibutterfly_0x20( vec[32], 0x20 )
//ibutterfly_0x10( vec[16], 0x20 )
//ibutterfly_0x8( vec[8], 0x20 )
//ibutterfly_0x4( vec[4], 0x20 )
//ibutterfly_0x2( vec[2], 0x20 )
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[33];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
//ibutterfly_0x2( vec[2], 0x22 )
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[34];
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[34];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[33];
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
//ibutterfly_0x4( vec[4], 0x24 )
//ibutterfly_0x2( vec[2], 0x24 )
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[36];
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0x24,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
//ibutterfly_0x2( vec[2], 0x26 )
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[38];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x26,temp);
bs_p1_xmm[38] = bs_p1_xmm[38] ^ temp;
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[36];
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[37];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[37] = bs_p1_xmm[37] ^ temp;
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[36];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[33];
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[34];
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[35];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[35] = bs_p1_xmm[35] ^ temp;
//ibutterfly_0x8( vec[8], 0x28 )
//ibutterfly_0x4( vec[4], 0x28 )
//ibutterfly_0x2( vec[2], 0x28 )
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[40];
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
//ibutterfly_0x2( vec[2], 0x2a )
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[42];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[42] = bs_p1_xmm[42] ^ temp;
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[40];
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[41];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[41] = bs_p1_xmm[41] ^ temp;
//ibutterfly_0x4( vec[4], 0x2c )
//ibutterfly_0x2( vec[2], 0x2c )
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[44];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x2c,temp);
bs_p1_xmm[44] = bs_p1_xmm[44] ^ temp;
//ibutterfly_0x2( vec[2], 0x2e )
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[46];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x2e,temp);
bs_p1_xmm[46] = bs_p1_xmm[46] ^ temp;
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[44];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[44] = bs_p1_xmm[44] ^ temp;
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[45];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[45] = bs_p1_xmm[45] ^ temp;
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[40];
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[41];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[41] = bs_p1_xmm[41] ^ temp;
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[42];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[42] = bs_p1_xmm[42] ^ temp;
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[43];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[43] = bs_p1_xmm[43] ^ temp;
bs_p1_xmm[40] = bs_p1_xmm[40] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[40];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[33];
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[34];
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[35];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[35] = bs_p1_xmm[35] ^ temp;
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[36];
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[37];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[37] = bs_p1_xmm[37] ^ temp;
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[38];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[38] = bs_p1_xmm[38] ^ temp;
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[39];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[39] = bs_p1_xmm[39] ^ temp;
//ibutterfly_0x10( vec[16], 0x30 )
//ibutterfly_0x8( vec[8], 0x30 )
//ibutterfly_0x4( vec[4], 0x30 )
//ibutterfly_0x2( vec[2], 0x30 )
bs_p1_xmm[49] = bs_p1_xmm[49] ^ bs_p1_xmm[48];
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x30,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
//ibutterfly_0x2( vec[2], 0x32 )
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[50];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x32,temp);
bs_p1_xmm[50] = bs_p1_xmm[50] ^ temp;
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[48];
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[49];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[49] = bs_p1_xmm[49] ^ temp;
//ibutterfly_0x4( vec[4], 0x34 )
//ibutterfly_0x2( vec[2], 0x34 )
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[52];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x34,temp);
bs_p1_xmm[52] = bs_p1_xmm[52] ^ temp;
//ibutterfly_0x2( vec[2], 0x36 )
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[54];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x36,temp);
bs_p1_xmm[54] = bs_p1_xmm[54] ^ temp;
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[52];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[52] = bs_p1_xmm[52] ^ temp;
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[53];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[53] = bs_p1_xmm[53] ^ temp;
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[48];
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[49];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[49] = bs_p1_xmm[49] ^ temp;
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[50];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[50] = bs_p1_xmm[50] ^ temp;
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[51];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[51] = bs_p1_xmm[51] ^ temp;
//ibutterfly_0x8( vec[8], 0x38 )
//ibutterfly_0x4( vec[4], 0x38 )
//ibutterfly_0x2( vec[2], 0x38 )
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[56];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x38,temp);
bs_p1_xmm[56] = bs_p1_xmm[56] ^ temp;
//ibutterfly_0x2( vec[2], 0x3a )
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[58];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x3a,temp);
bs_p1_xmm[58] = bs_p1_xmm[58] ^ temp;
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[56];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[56] = bs_p1_xmm[56] ^ temp;
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[57];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[57] = bs_p1_xmm[57] ^ temp;
//ibutterfly_0x4( vec[4], 0x3c )
//ibutterfly_0x2( vec[2], 0x3c )
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[60];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x3c,temp);
bs_p1_xmm[60] = bs_p1_xmm[60] ^ temp;
//ibutterfly_0x2( vec[2], 0x3e )
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[62];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x3e,temp);
bs_p1_xmm[62] = bs_p1_xmm[62] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[60];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[60] = bs_p1_xmm[60] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[61];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[61] = bs_p1_xmm[61] ^ temp;
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[56];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[56] = bs_p1_xmm[56] ^ temp;
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[57];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[57] = bs_p1_xmm[57] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[58];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[58] = bs_p1_xmm[58] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[59];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[59] = bs_p1_xmm[59] ^ temp;
bs_p1_xmm[56] = bs_p1_xmm[56] ^ bs_p1_xmm[48];
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[48] = bs_p1_xmm[48] ^ temp;
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[49];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[49] = bs_p1_xmm[49] ^ temp;
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[50];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[50] = bs_p1_xmm[50] ^ temp;
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[51];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[51] = bs_p1_xmm[51] ^ temp;
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[52];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[52] = bs_p1_xmm[52] ^ temp;
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[53];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[53] = bs_p1_xmm[53] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[54];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[54] = bs_p1_xmm[54] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[55];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[55] = bs_p1_xmm[55] ^ temp;
bs_p1_xmm[48] = bs_p1_xmm[48] ^ bs_p1_xmm[32];
temp = bs_p1_xmm[48];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[32] = bs_p1_xmm[32] ^ temp;
bs_p1_xmm[49] = bs_p1_xmm[49] ^ bs_p1_xmm[33];
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[33] = bs_p1_xmm[33] ^ temp;
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[34];
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[34] = bs_p1_xmm[34] ^ temp;
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[35];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[35] = bs_p1_xmm[35] ^ temp;
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[36];
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[36] = bs_p1_xmm[36] ^ temp;
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[37];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[37] = bs_p1_xmm[37] ^ temp;
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[38];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[38] = bs_p1_xmm[38] ^ temp;
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[39];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[39] = bs_p1_xmm[39] ^ temp;
bs_p1_xmm[56] = bs_p1_xmm[56] ^ bs_p1_xmm[40];
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[40] = bs_p1_xmm[40] ^ temp;
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[41];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[41] = bs_p1_xmm[41] ^ temp;
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[42];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[42] = bs_p1_xmm[42] ^ temp;
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[43];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[43] = bs_p1_xmm[43] ^ temp;
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[44];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[44] = bs_p1_xmm[44] ^ temp;
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[45];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[45] = bs_p1_xmm[45] ^ temp;
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[46];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[46] = bs_p1_xmm[46] ^ temp;
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[47];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[47] = bs_p1_xmm[47] ^ temp;
bs_p1_xmm[32] = bs_p1_xmm[32] ^ bs_p1_xmm[0];
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[1];
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[2];
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[3];
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[4];
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[5];
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[6];
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[7];
bs_p1_xmm[40] = bs_p1_xmm[40] ^ bs_p1_xmm[8];
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[9];
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[10];
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[11];
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[12];
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[13];
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[14];
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[15];
bs_p1_xmm[48] = bs_p1_xmm[48] ^ bs_p1_xmm[16];
bs_p1_xmm[49] = bs_p1_xmm[49] ^ bs_p1_xmm[17];
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[18];
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[19];
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[20];
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[21];
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[22];
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[23];
bs_p1_xmm[56] = bs_p1_xmm[56] ^ bs_p1_xmm[24];
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[25];
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[26];
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[27];
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[28];
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[29];
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[30];
bs_p1_xmm[63] = bs_p1_xmm[63] ^ bs_p1_xmm[31];
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[2];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[3];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[6];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[7];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[10];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[11];
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[14];
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[15];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[8];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[9];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[10];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[11];
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[12];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[13];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[14];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[15];
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[4];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[5];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[6];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[7];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[12];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[13];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[14];
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[15];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[8];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[9];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[10];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[11];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[12];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[13];
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[14];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[15];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[18];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[19];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[22];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[23];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[26];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[27];
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[30];
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[31];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[24];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[25];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[26];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[27];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[28];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[29];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[30];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[31];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[20];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[21];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[22];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[23];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[28];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[29];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[30];
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[31];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[24];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[25];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[26];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[27];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[28];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[29];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[30];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[31];
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[34];
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[35];
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[38];
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[39];
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[42];
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[43];
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[46];
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[47];
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[40];
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[41];
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[42];
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[43];
bs_p1_xmm[40] = bs_p1_xmm[40] ^ bs_p1_xmm[44];
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[45];
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[46];
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[47];
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[36];
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[37];
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[38];
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[39];
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[44];
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[45];
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[46];
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[47];
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[40];
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[41];
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[42];
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[43];
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[44];
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[45];
bs_p1_xmm[40] = bs_p1_xmm[40] ^ bs_p1_xmm[46];
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[47];
bs_p1_xmm[49] = bs_p1_xmm[49] ^ bs_p1_xmm[50];
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[51];
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[54];
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[55];
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[58];
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[59];
bs_p1_xmm[61] = bs_p1_xmm[61] ^ bs_p1_xmm[62];
bs_p1_xmm[62] = bs_p1_xmm[62] ^ bs_p1_xmm[63];
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[56];
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[57];
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[58];
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[59];
bs_p1_xmm[56] = bs_p1_xmm[56] ^ bs_p1_xmm[60];
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[61];
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[62];
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[63];
bs_p1_xmm[49] = bs_p1_xmm[49] ^ bs_p1_xmm[52];
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[53];
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[54];
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[55];
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[60];
bs_p1_xmm[58] = bs_p1_xmm[58] ^ bs_p1_xmm[61];
bs_p1_xmm[59] = bs_p1_xmm[59] ^ bs_p1_xmm[62];
bs_p1_xmm[60] = bs_p1_xmm[60] ^ bs_p1_xmm[63];
bs_p1_xmm[50] = bs_p1_xmm[50] ^ bs_p1_xmm[56];
bs_p1_xmm[51] = bs_p1_xmm[51] ^ bs_p1_xmm[57];
bs_p1_xmm[52] = bs_p1_xmm[52] ^ bs_p1_xmm[58];
bs_p1_xmm[53] = bs_p1_xmm[53] ^ bs_p1_xmm[59];
bs_p1_xmm[54] = bs_p1_xmm[54] ^ bs_p1_xmm[60];
bs_p1_xmm[55] = bs_p1_xmm[55] ^ bs_p1_xmm[61];
bs_p1_xmm[56] = bs_p1_xmm[56] ^ bs_p1_xmm[62];
bs_p1_xmm[57] = bs_p1_xmm[57] ^ bs_p1_xmm[63];
bs_p1_xmm[16] = bs_p1_xmm[16] ^ bs_p1_xmm[32];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[33];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[34];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[35];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[36];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[37];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[38];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[39];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[40];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[41];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[42];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[43];
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[44];
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[45];
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[46];
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[47];
bs_p1_xmm[32] = bs_p1_xmm[32] ^ bs_p1_xmm[48];
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[49];
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[50];
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[51];
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[52];
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[53];
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[54];
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[55];
bs_p1_xmm[40] = bs_p1_xmm[40] ^ bs_p1_xmm[56];
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[57];
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[58];
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[59];
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[60];
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[61];
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[62];
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[63];
bs_p1_xmm[1] = bs_p1_xmm[1] ^ bs_p1_xmm[16];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[17];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[18];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[19];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[20];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[21];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[22];
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[23];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[24];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[25];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[26];
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[27];
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[28];
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[29];
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[30];
bs_p1_xmm[16] = bs_p1_xmm[16] ^ bs_p1_xmm[31];
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[48];
bs_p1_xmm[34] = bs_p1_xmm[34] ^ bs_p1_xmm[49];
bs_p1_xmm[35] = bs_p1_xmm[35] ^ bs_p1_xmm[50];
bs_p1_xmm[36] = bs_p1_xmm[36] ^ bs_p1_xmm[51];
bs_p1_xmm[37] = bs_p1_xmm[37] ^ bs_p1_xmm[52];
bs_p1_xmm[38] = bs_p1_xmm[38] ^ bs_p1_xmm[53];
bs_p1_xmm[39] = bs_p1_xmm[39] ^ bs_p1_xmm[54];
bs_p1_xmm[40] = bs_p1_xmm[40] ^ bs_p1_xmm[55];
bs_p1_xmm[41] = bs_p1_xmm[41] ^ bs_p1_xmm[56];
bs_p1_xmm[42] = bs_p1_xmm[42] ^ bs_p1_xmm[57];
bs_p1_xmm[43] = bs_p1_xmm[43] ^ bs_p1_xmm[58];
bs_p1_xmm[44] = bs_p1_xmm[44] ^ bs_p1_xmm[59];
bs_p1_xmm[45] = bs_p1_xmm[45] ^ bs_p1_xmm[60];
bs_p1_xmm[46] = bs_p1_xmm[46] ^ bs_p1_xmm[61];
bs_p1_xmm[47] = bs_p1_xmm[47] ^ bs_p1_xmm[62];
bs_p1_xmm[48] = bs_p1_xmm[48] ^ bs_p1_xmm[63];
bs_p1_xmm[2] = bs_p1_xmm[2] ^ bs_p1_xmm[32];
bs_p1_xmm[3] = bs_p1_xmm[3] ^ bs_p1_xmm[33];
bs_p1_xmm[4] = bs_p1_xmm[4] ^ bs_p1_xmm[34];
bs_p1_xmm[5] = bs_p1_xmm[5] ^ bs_p1_xmm[35];
bs_p1_xmm[6] = bs_p1_xmm[6] ^ bs_p1_xmm[36];
bs_p1_xmm[7] = bs_p1_xmm[7] ^ bs_p1_xmm[37];
bs_p1_xmm[8] = bs_p1_xmm[8] ^ bs_p1_xmm[38];
bs_p1_xmm[9] = bs_p1_xmm[9] ^ bs_p1_xmm[39];
bs_p1_xmm[10] = bs_p1_xmm[10] ^ bs_p1_xmm[40];
bs_p1_xmm[11] = bs_p1_xmm[11] ^ bs_p1_xmm[41];
bs_p1_xmm[12] = bs_p1_xmm[12] ^ bs_p1_xmm[42];
bs_p1_xmm[13] = bs_p1_xmm[13] ^ bs_p1_xmm[43];
bs_p1_xmm[14] = bs_p1_xmm[14] ^ bs_p1_xmm[44];
bs_p1_xmm[15] = bs_p1_xmm[15] ^ bs_p1_xmm[45];
bs_p1_xmm[16] = bs_p1_xmm[16] ^ bs_p1_xmm[46];
bs_p1_xmm[17] = bs_p1_xmm[17] ^ bs_p1_xmm[47];
bs_p1_xmm[18] = bs_p1_xmm[18] ^ bs_p1_xmm[48];
bs_p1_xmm[19] = bs_p1_xmm[19] ^ bs_p1_xmm[49];
bs_p1_xmm[20] = bs_p1_xmm[20] ^ bs_p1_xmm[50];
bs_p1_xmm[21] = bs_p1_xmm[21] ^ bs_p1_xmm[51];
bs_p1_xmm[22] = bs_p1_xmm[22] ^ bs_p1_xmm[52];
bs_p1_xmm[23] = bs_p1_xmm[23] ^ bs_p1_xmm[53];
bs_p1_xmm[24] = bs_p1_xmm[24] ^ bs_p1_xmm[54];
bs_p1_xmm[25] = bs_p1_xmm[25] ^ bs_p1_xmm[55];
bs_p1_xmm[26] = bs_p1_xmm[26] ^ bs_p1_xmm[56];
bs_p1_xmm[27] = bs_p1_xmm[27] ^ bs_p1_xmm[57];
bs_p1_xmm[28] = bs_p1_xmm[28] ^ bs_p1_xmm[58];
bs_p1_xmm[29] = bs_p1_xmm[29] ^ bs_p1_xmm[59];
bs_p1_xmm[30] = bs_p1_xmm[30] ^ bs_p1_xmm[60];
bs_p1_xmm[31] = bs_p1_xmm[31] ^ bs_p1_xmm[61];
bs_p1_xmm[32] = bs_p1_xmm[32] ^ bs_p1_xmm[62];
bs_p1_xmm[33] = bs_p1_xmm[33] ^ bs_p1_xmm[63];

}
