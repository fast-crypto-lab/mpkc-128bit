
#include "tbl_gf256v_polymul.h"
#include "gfext_sse.h"

void tbl_gf256v_polymul_48( __m128i * rp_xmm , const __m128i * p1_xmm , const __m128i * p2_xmm ) {
	__m128i bs_p1_xmm[64*2];
	__m128i bs_p2_xmm[64*2];
	__m128i temp;

//p1_xmm[0]:0x0 ,0? False, omit? False
//p1_xmm[1]:0x1 ,0? False, omit? False
//p1_xmm[2]:0x2 ,0? False, omit? False
//p1_xmm[3]:0x3 ,0? False, omit? False
//p1_xmm[4]:0x4 ,0? False, omit? False
//p1_xmm[5]:0x5 ,0? False, omit? False
//p1_xmm[6]:0x6 ,0? False, omit? False
//p1_xmm[7]:0x7 ,0? False, omit? False
//p1_xmm[8]:0x8 ,0? False, omit? False
//p1_xmm[9]:0x9 ,0? False, omit? False
//p1_xmm[10]:0xa ,0? False, omit? False
//p1_xmm[11]:0xb ,0? False, omit? False
//p1_xmm[12]:0xc ,0? False, omit? False
//p1_xmm[13]:0xd ,0? False, omit? False
//p1_xmm[14]:0xe ,0? False, omit? False
//p1_xmm[15]:0xf ,0? False, omit? False
//p1_xmm[16]:0x10 ,0? False, omit? False
//p1_xmm[17]:0x11 ,0? False, omit? False
//p1_xmm[18]:0x12 ,0? False, omit? False
//p1_xmm[19]:0x13 ,0? False, omit? False
//p1_xmm[20]:0x14 ,0? False, omit? False
//p1_xmm[21]:0x15 ,0? False, omit? False
//p1_xmm[22]:0x16 ,0? False, omit? False
//p1_xmm[23]:0x17 ,0? False, omit? False
//p1_xmm[24]:0x18 ,0? False, omit? False
//p1_xmm[25]:0x19 ,0? False, omit? False
//p1_xmm[26]:0x1a ,0? False, omit? False
//p1_xmm[27]:0x1b ,0? False, omit? False
//p1_xmm[28]:0x1c ,0? False, omit? False
//p1_xmm[29]:0x1d ,0? False, omit? False
//p1_xmm[30]:0x1e ,0? False, omit? False
//p1_xmm[31]:0x1f ,0? False, omit? False
//p1_xmm[32]:0x20 ,0? False, omit? False
//p1_xmm[33]:0x21 ,0? False, omit? False
//p1_xmm[34]:0x22 ,0? False, omit? False
//p1_xmm[35]:0x23 ,0? False, omit? False
//p1_xmm[36]:0x24 ,0? False, omit? False
//p1_xmm[37]:0x25 ,0? False, omit? False
//p1_xmm[38]:0x26 ,0? False, omit? False
//p1_xmm[39]:0x27 ,0? False, omit? False
//p1_xmm[40]:0x28 ,0? False, omit? False
//p1_xmm[41]:0x29 ,0? False, omit? False
//p1_xmm[42]:0x2a ,0? False, omit? False
//p1_xmm[43]:0x2b ,0? False, omit? False
//p1_xmm[44]:0x2c ,0? False, omit? False
//p1_xmm[45]:0x2d ,0? False, omit? False
//p1_xmm[46]:0x2e ,0? False, omit? False
//p1_xmm[47]:0x2f ,0? False, omit? False
//p2_xmm[0]:0x0 ,0? False, omit? False
//p2_xmm[1]:0x1 ,0? False, omit? False
//p2_xmm[2]:0x2 ,0? False, omit? False
//p2_xmm[3]:0x3 ,0? False, omit? False
//p2_xmm[4]:0x4 ,0? False, omit? False
//p2_xmm[5]:0x5 ,0? False, omit? False
//p2_xmm[6]:0x6 ,0? False, omit? False
//p2_xmm[7]:0x7 ,0? False, omit? False
//p2_xmm[8]:0x8 ,0? False, omit? False
//p2_xmm[9]:0x9 ,0? False, omit? False
//p2_xmm[10]:0xa ,0? False, omit? False
//p2_xmm[11]:0xb ,0? False, omit? False
//p2_xmm[12]:0xc ,0? False, omit? False
//p2_xmm[13]:0xd ,0? False, omit? False
//p2_xmm[14]:0xe ,0? False, omit? False
//p2_xmm[15]:0xf ,0? False, omit? False
//p2_xmm[16]:0x10 ,0? False, omit? False
//p2_xmm[17]:0x11 ,0? False, omit? False
//p2_xmm[18]:0x12 ,0? False, omit? False
//p2_xmm[19]:0x13 ,0? False, omit? False
//p2_xmm[20]:0x14 ,0? False, omit? False
//p2_xmm[21]:0x15 ,0? False, omit? False
//p2_xmm[22]:0x16 ,0? False, omit? False
//p2_xmm[23]:0x17 ,0? False, omit? False
//p2_xmm[24]:0x18 ,0? False, omit? False
//p2_xmm[25]:0x19 ,0? False, omit? False
//p2_xmm[26]:0x1a ,0? False, omit? False
//p2_xmm[27]:0x1b ,0? False, omit? False
//p2_xmm[28]:0x1c ,0? False, omit? False
//p2_xmm[29]:0x1d ,0? False, omit? False
//p2_xmm[30]:0x1e ,0? False, omit? False
//p2_xmm[31]:0x1f ,0? False, omit? False
//p2_xmm[32]:0x20 ,0? False, omit? False
//p2_xmm[33]:0x21 ,0? False, omit? False
//p2_xmm[34]:0x22 ,0? False, omit? False
//p2_xmm[35]:0x23 ,0? False, omit? False
//p2_xmm[36]:0x24 ,0? False, omit? False
//p2_xmm[37]:0x25 ,0? False, omit? False
//p2_xmm[38]:0x26 ,0? False, omit? False
//p2_xmm[39]:0x27 ,0? False, omit? False
//p2_xmm[40]:0x28 ,0? False, omit? False
//p2_xmm[41]:0x29 ,0? False, omit? False
//p2_xmm[42]:0x2a ,0? False, omit? False
//p2_xmm[43]:0x2b ,0? False, omit? False
//p2_xmm[44]:0x2c ,0? False, omit? False
//p2_xmm[45]:0x2d ,0? False, omit? False
//p2_xmm[46]:0x2e ,0? False, omit? False
//p2_xmm[47]:0x2f ,0? False, omit? False
//bs_p1_xmm[0]:0x0 ,0? False, omit? False
//bs_p1_xmm[1]:0x0 ,0? False, omit? False
//bs_p1_xmm[2]:0x1 ,0? False, omit? False
//bs_p1_xmm[3]:0x0 ,0? False, omit? False
//bs_p1_xmm[4]:0x3 ,0? False, omit? False
//bs_p1_xmm[5]:0x0 ,0? False, omit? False
//bs_p1_xmm[6]:0x2 ,0? False, omit? False
//bs_p1_xmm[7]:0x0 ,0? False, omit? False
//bs_p1_xmm[8]:0x6 ,0? False, omit? False
//bs_p1_xmm[9]:0x0 ,0? False, omit? False
//bs_p1_xmm[10]:0x7 ,0? False, omit? False
//bs_p1_xmm[11]:0x0 ,0? False, omit? False
//bs_p1_xmm[12]:0x5 ,0? False, omit? False
//bs_p1_xmm[13]:0x0 ,0? False, omit? False
//bs_p1_xmm[14]:0x4 ,0? False, omit? False
//bs_p1_xmm[15]:0x0 ,0? False, omit? False
//bs_p1_xmm[16]:0xd ,0? False, omit? False
//bs_p1_xmm[17]:0x0 ,0? False, omit? False
//bs_p1_xmm[18]:0xc ,0? False, omit? False
//bs_p1_xmm[19]:0x0 ,0? False, omit? False
//bs_p1_xmm[20]:0xe ,0? False, omit? False
//bs_p1_xmm[21]:0x0 ,0? False, omit? False
//bs_p1_xmm[22]:0xf ,0? False, omit? False
//bs_p1_xmm[23]:0x0 ,0? False, omit? False
//bs_p1_xmm[24]:0xb ,0? False, omit? False
//bs_p1_xmm[25]:0x0 ,0? False, omit? False
//bs_p1_xmm[26]:0xa ,0? False, omit? False
//bs_p1_xmm[27]:0x0 ,0? False, omit? False
//bs_p1_xmm[28]:0x8 ,0? False, omit? False
//bs_p1_xmm[29]:0x0 ,0? False, omit? False
//bs_p1_xmm[30]:0x9 ,0? False, omit? False
//bs_p1_xmm[31]:0x0 ,0? False, omit? False
//bs_p1_xmm[32]:0x18 ,0? False, omit? False
//bs_p1_xmm[33]:0x0 ,0? False, omit? False
//bs_p1_xmm[34]:0x19 ,0? False, omit? False
//bs_p1_xmm[35]:0x0 ,0? False, omit? False
//bs_p1_xmm[36]:0x1b ,0? False, omit? False
//bs_p1_xmm[37]:0x0 ,0? False, omit? False
//bs_p1_xmm[38]:0x1a ,0? False, omit? False
//bs_p1_xmm[39]:0x0 ,0? False, omit? False
//bs_p1_xmm[40]:0x1e ,0? False, omit? False
//bs_p1_xmm[41]:0x0 ,0? False, omit? False
//bs_p1_xmm[42]:0x1f ,0? False, omit? False
//bs_p1_xmm[43]:0x0 ,0? False, omit? False
//bs_p1_xmm[44]:0x1d ,0? False, omit? False
//bs_p1_xmm[45]:0x0 ,0? False, omit? False
//bs_p1_xmm[46]:0x1c ,0? False, omit? False
//bs_p1_xmm[47]:0x0 ,0? False, omit? False
//bs_p1_xmm[48]:0x15 ,0? False, omit? False
//bs_p1_xmm[49]:0x0 ,0? False, omit? False
//bs_p1_xmm[50]:0x14 ,0? False, omit? False
//bs_p1_xmm[51]:0x0 ,0? False, omit? False
//bs_p1_xmm[52]:0x16 ,0? False, omit? False
//bs_p1_xmm[53]:0x0 ,0? False, omit? False
//bs_p1_xmm[54]:0x17 ,0? False, omit? False
//bs_p1_xmm[55]:0x0 ,0? False, omit? False
//bs_p1_xmm[56]:0x13 ,0? False, omit? False
//bs_p1_xmm[57]:0x0 ,0? False, omit? False
//bs_p1_xmm[58]:0x12 ,0? False, omit? False
//bs_p1_xmm[59]:0x0 ,0? False, omit? False
//bs_p1_xmm[60]:0x10 ,0? False, omit? False
//bs_p1_xmm[61]:0x0 ,0? False, omit? False
//bs_p1_xmm[62]:0x11 ,0? False, omit? False
//bs_p1_xmm[63]:0x0 ,0? False, omit? False
//bs_p1_xmm[64]:0x34 ,0? False, omit? False
//bs_p1_xmm[65]:0x0 ,0? False, omit? False
//bs_p1_xmm[66]:0x35 ,0? False, omit? False
//bs_p1_xmm[67]:0x0 ,0? False, omit? False
//bs_p1_xmm[68]:0x37 ,0? False, omit? False
//bs_p1_xmm[69]:0x0 ,0? False, omit? False
//bs_p1_xmm[70]:0x36 ,0? False, omit? False
//bs_p1_xmm[71]:0x0 ,0? False, omit? False
//bs_p1_xmm[72]:0x32 ,0? False, omit? False
//bs_p1_xmm[73]:0x0 ,0? False, omit? False
//bs_p1_xmm[74]:0x33 ,0? False, omit? False
//bs_p1_xmm[75]:0x0 ,0? False, omit? False
//bs_p1_xmm[76]:0x31 ,0? False, omit? False
//bs_p1_xmm[77]:0x0 ,0? False, omit? False
//bs_p1_xmm[78]:0x30 ,0? False, omit? False
//bs_p1_xmm[79]:0x0 ,0? False, omit? False
//bs_p1_xmm[80]:0x39 ,0? False, omit? False
//bs_p1_xmm[81]:0x0 ,0? False, omit? False
//bs_p1_xmm[82]:0x38 ,0? False, omit? False
//bs_p1_xmm[83]:0x0 ,0? False, omit? False
//bs_p1_xmm[84]:0x3a ,0? False, omit? False
//bs_p1_xmm[85]:0x0 ,0? False, omit? False
//bs_p1_xmm[86]:0x3b ,0? False, omit? False
//bs_p1_xmm[87]:0x0 ,0? False, omit? False
//bs_p1_xmm[88]:0x3f ,0? False, omit? False
//bs_p1_xmm[89]:0x0 ,0? False, omit? False
//bs_p1_xmm[90]:0x3e ,0? False, omit? False
//bs_p1_xmm[91]:0x0 ,0? False, omit? False
//bs_p1_xmm[92]:0x3c ,0? False, omit? False
//bs_p1_xmm[93]:0x0 ,0? False, omit? False
//bs_p1_xmm[94]:0x3d ,0? False, omit? False
//bs_p1_xmm[95]:0x0 ,0? False, omit? False
//bs_p1_xmm[96]:0x0 ,0? True, omit? True
//bs_p1_xmm[97]:0x0 ,0? True, omit? True
//bs_p1_xmm[98]:0x0 ,0? True, omit? True
//bs_p1_xmm[99]:0x0 ,0? True, omit? True
//bs_p1_xmm[100]:0x0 ,0? True, omit? True
//bs_p1_xmm[101]:0x0 ,0? True, omit? True
//bs_p1_xmm[102]:0x0 ,0? True, omit? True
//bs_p1_xmm[103]:0x0 ,0? True, omit? True
//bs_p1_xmm[104]:0x0 ,0? True, omit? True
//bs_p1_xmm[105]:0x0 ,0? True, omit? True
//bs_p1_xmm[106]:0x0 ,0? True, omit? True
//bs_p1_xmm[107]:0x0 ,0? True, omit? True
//bs_p1_xmm[108]:0x0 ,0? True, omit? True
//bs_p1_xmm[109]:0x0 ,0? True, omit? True
//bs_p1_xmm[110]:0x0 ,0? True, omit? True
//bs_p1_xmm[111]:0x0 ,0? True, omit? True
//bs_p1_xmm[112]:0x0 ,0? True, omit? True
//bs_p1_xmm[113]:0x0 ,0? True, omit? True
//bs_p1_xmm[114]:0x0 ,0? True, omit? True
//bs_p1_xmm[115]:0x0 ,0? True, omit? True
//bs_p1_xmm[116]:0x0 ,0? True, omit? True
//bs_p1_xmm[117]:0x0 ,0? True, omit? True
//bs_p1_xmm[118]:0x0 ,0? True, omit? True
//bs_p1_xmm[119]:0x0 ,0? True, omit? True
//bs_p1_xmm[120]:0x0 ,0? True, omit? True
//bs_p1_xmm[121]:0x0 ,0? True, omit? True
//bs_p1_xmm[122]:0x0 ,0? True, omit? True
//bs_p1_xmm[123]:0x0 ,0? True, omit? True
//bs_p1_xmm[124]:0x0 ,0? True, omit? True
//bs_p1_xmm[125]:0x0 ,0? True, omit? True
//bs_p1_xmm[126]:0x0 ,0? True, omit? True
//bs_p1_xmm[127]:0x0 ,0? True, omit? True
//[add,mul_const,mul_var] =  [3331, 963, 128]
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
bs_p1_xmm[32] = p1_xmm[32];
bs_p1_xmm[33] = p1_xmm[33];
bs_p1_xmm[34] = p1_xmm[34];
bs_p1_xmm[35] = p1_xmm[35];
bs_p1_xmm[36] = p1_xmm[36];
bs_p1_xmm[37] = p1_xmm[37];
bs_p1_xmm[38] = p1_xmm[38];
bs_p1_xmm[39] = p1_xmm[39];
bs_p1_xmm[40] = p1_xmm[40];
bs_p1_xmm[41] = p1_xmm[41];
bs_p1_xmm[42] = p1_xmm[42];
bs_p1_xmm[43] = p1_xmm[43];
bs_p1_xmm[44] = p1_xmm[44];
bs_p1_xmm[45] = p1_xmm[45];
bs_p1_xmm[46] = p1_xmm[46];
bs_p1_xmm[47] = p1_xmm[47];
/// + 0: bs_p1_xmm[33] ^= bs_p1_xmm[63];
/// + 0: bs_p1_xmm[32] ^= bs_p1_xmm[62];
/// + 0: bs_p1_xmm[31] ^= bs_p1_xmm[61];
/// + 0: bs_p1_xmm[30] ^= bs_p1_xmm[60];
/// + 0: bs_p1_xmm[29] ^= bs_p1_xmm[59];
/// + 0: bs_p1_xmm[28] ^= bs_p1_xmm[58];
/// + 0: bs_p1_xmm[27] ^= bs_p1_xmm[57];
/// + 0: bs_p1_xmm[26] ^= bs_p1_xmm[56];
/// + 0: bs_p1_xmm[25] ^= bs_p1_xmm[55];
/// + 0: bs_p1_xmm[24] ^= bs_p1_xmm[54];
/// + 0: bs_p1_xmm[23] ^= bs_p1_xmm[53];
/// + 0: bs_p1_xmm[22] ^= bs_p1_xmm[52];
/// + 0: bs_p1_xmm[21] ^= bs_p1_xmm[51];
/// + 0: bs_p1_xmm[20] ^= bs_p1_xmm[50];
/// + 0: bs_p1_xmm[19] ^= bs_p1_xmm[49];
/// + 0: bs_p1_xmm[18] ^= bs_p1_xmm[48];
bs_p1_xmm[17] ^= bs_p1_xmm[47];
bs_p1_xmm[16] ^= bs_p1_xmm[46];
bs_p1_xmm[15] ^= bs_p1_xmm[45];
bs_p1_xmm[14] ^= bs_p1_xmm[44];
bs_p1_xmm[13] ^= bs_p1_xmm[43];
bs_p1_xmm[12] ^= bs_p1_xmm[42];
bs_p1_xmm[11] ^= bs_p1_xmm[41];
bs_p1_xmm[10] ^= bs_p1_xmm[40];
bs_p1_xmm[9] ^= bs_p1_xmm[39];
bs_p1_xmm[8] ^= bs_p1_xmm[38];
bs_p1_xmm[7] ^= bs_p1_xmm[37];
bs_p1_xmm[6] ^= bs_p1_xmm[36];
bs_p1_xmm[5] ^= bs_p1_xmm[35];
bs_p1_xmm[4] ^= bs_p1_xmm[34];
bs_p1_xmm[3] ^= bs_p1_xmm[33];
bs_p1_xmm[2] ^= bs_p1_xmm[32];
bs_p1_xmm[16] ^= bs_p1_xmm[31];
bs_p1_xmm[15] ^= bs_p1_xmm[30];
bs_p1_xmm[14] ^= bs_p1_xmm[29];
bs_p1_xmm[13] ^= bs_p1_xmm[28];
bs_p1_xmm[12] ^= bs_p1_xmm[27];
bs_p1_xmm[11] ^= bs_p1_xmm[26];
bs_p1_xmm[10] ^= bs_p1_xmm[25];
bs_p1_xmm[9] ^= bs_p1_xmm[24];
bs_p1_xmm[8] ^= bs_p1_xmm[23];
bs_p1_xmm[7] ^= bs_p1_xmm[22];
bs_p1_xmm[6] ^= bs_p1_xmm[21];
bs_p1_xmm[5] ^= bs_p1_xmm[20];
bs_p1_xmm[4] ^= bs_p1_xmm[19];
bs_p1_xmm[3] ^= bs_p1_xmm[18];
bs_p1_xmm[2] ^= bs_p1_xmm[17];
bs_p1_xmm[1] ^= bs_p1_xmm[16];
/// + 0: bs_p1_xmm[48] = bs_p1_xmm[63];
/// + 0: bs_p1_xmm[47] ^= bs_p1_xmm[62];
/// + 0: bs_p1_xmm[46] ^= bs_p1_xmm[61];
/// + 0: bs_p1_xmm[45] ^= bs_p1_xmm[60];
/// + 0: bs_p1_xmm[44] ^= bs_p1_xmm[59];
/// + 0: bs_p1_xmm[43] ^= bs_p1_xmm[58];
/// + 0: bs_p1_xmm[42] ^= bs_p1_xmm[57];
/// + 0: bs_p1_xmm[41] ^= bs_p1_xmm[56];
/// + 0: bs_p1_xmm[40] ^= bs_p1_xmm[55];
/// + 0: bs_p1_xmm[39] ^= bs_p1_xmm[54];
/// + 0: bs_p1_xmm[38] ^= bs_p1_xmm[53];
/// + 0: bs_p1_xmm[37] ^= bs_p1_xmm[52];
/// + 0: bs_p1_xmm[36] ^= bs_p1_xmm[51];
/// + 0: bs_p1_xmm[35] ^= bs_p1_xmm[50];
/// + 0: bs_p1_xmm[34] ^= bs_p1_xmm[49];
/// + 0: bs_p1_xmm[33] ^= bs_p1_xmm[48];
/// + 0: bs_p1_xmm[32] ^= bs_p1_xmm[48];
/// + 0: bs_p1_xmm[33] ^= bs_p1_xmm[49];
/// + 0: bs_p1_xmm[34] ^= bs_p1_xmm[50];
/// + 0: bs_p1_xmm[35] ^= bs_p1_xmm[51];
/// + 0: bs_p1_xmm[36] ^= bs_p1_xmm[52];
/// + 0: bs_p1_xmm[37] ^= bs_p1_xmm[53];
/// + 0: bs_p1_xmm[38] ^= bs_p1_xmm[54];
/// + 0: bs_p1_xmm[39] ^= bs_p1_xmm[55];
/// + 0: bs_p1_xmm[40] ^= bs_p1_xmm[56];
/// + 0: bs_p1_xmm[41] ^= bs_p1_xmm[57];
/// + 0: bs_p1_xmm[42] ^= bs_p1_xmm[58];
/// + 0: bs_p1_xmm[43] ^= bs_p1_xmm[59];
/// + 0: bs_p1_xmm[44] ^= bs_p1_xmm[60];
/// + 0: bs_p1_xmm[45] ^= bs_p1_xmm[61];
/// + 0: bs_p1_xmm[46] ^= bs_p1_xmm[62];
/// + 0: bs_p1_xmm[47] ^= bs_p1_xmm[63];
bs_p1_xmm[16] ^= bs_p1_xmm[32];
bs_p1_xmm[17] ^= bs_p1_xmm[33];
bs_p1_xmm[18] ^= bs_p1_xmm[34];
bs_p1_xmm[19] ^= bs_p1_xmm[35];
bs_p1_xmm[20] ^= bs_p1_xmm[36];
bs_p1_xmm[21] ^= bs_p1_xmm[37];
bs_p1_xmm[22] ^= bs_p1_xmm[38];
bs_p1_xmm[23] ^= bs_p1_xmm[39];
bs_p1_xmm[24] ^= bs_p1_xmm[40];
bs_p1_xmm[25] ^= bs_p1_xmm[41];
bs_p1_xmm[26] ^= bs_p1_xmm[42];
bs_p1_xmm[27] ^= bs_p1_xmm[43];
bs_p1_xmm[28] ^= bs_p1_xmm[44];
bs_p1_xmm[29] ^= bs_p1_xmm[45];
bs_p1_xmm[30] ^= bs_p1_xmm[46];
bs_p1_xmm[31] ^= bs_p1_xmm[47];
bs_p1_xmm[9] ^= bs_p1_xmm[15];
bs_p1_xmm[8] ^= bs_p1_xmm[14];
bs_p1_xmm[7] ^= bs_p1_xmm[13];
bs_p1_xmm[6] ^= bs_p1_xmm[12];
bs_p1_xmm[5] ^= bs_p1_xmm[11];
bs_p1_xmm[4] ^= bs_p1_xmm[10];
bs_p1_xmm[3] ^= bs_p1_xmm[9];
bs_p1_xmm[2] ^= bs_p1_xmm[8];
bs_p1_xmm[4] ^= bs_p1_xmm[7];
bs_p1_xmm[3] ^= bs_p1_xmm[6];
bs_p1_xmm[2] ^= bs_p1_xmm[5];
bs_p1_xmm[1] ^= bs_p1_xmm[4];
bs_p1_xmm[12] ^= bs_p1_xmm[15];
bs_p1_xmm[11] ^= bs_p1_xmm[14];
bs_p1_xmm[10] ^= bs_p1_xmm[13];
bs_p1_xmm[9] ^= bs_p1_xmm[12];
bs_p1_xmm[8] ^= bs_p1_xmm[12];
bs_p1_xmm[9] ^= bs_p1_xmm[13];
bs_p1_xmm[10] ^= bs_p1_xmm[14];
bs_p1_xmm[11] ^= bs_p1_xmm[15];
bs_p1_xmm[4] ^= bs_p1_xmm[8];
bs_p1_xmm[5] ^= bs_p1_xmm[9];
bs_p1_xmm[6] ^= bs_p1_xmm[10];
bs_p1_xmm[7] ^= bs_p1_xmm[11];
bs_p1_xmm[2] ^= bs_p1_xmm[3];
bs_p1_xmm[1] ^= bs_p1_xmm[2];
bs_p1_xmm[6] ^= bs_p1_xmm[7];
bs_p1_xmm[5] ^= bs_p1_xmm[6];
bs_p1_xmm[10] ^= bs_p1_xmm[11];
bs_p1_xmm[9] ^= bs_p1_xmm[10];
bs_p1_xmm[14] ^= bs_p1_xmm[15];
bs_p1_xmm[13] ^= bs_p1_xmm[14];
bs_p1_xmm[25] ^= bs_p1_xmm[31];
bs_p1_xmm[24] ^= bs_p1_xmm[30];
bs_p1_xmm[23] ^= bs_p1_xmm[29];
bs_p1_xmm[22] ^= bs_p1_xmm[28];
bs_p1_xmm[21] ^= bs_p1_xmm[27];
bs_p1_xmm[20] ^= bs_p1_xmm[26];
bs_p1_xmm[19] ^= bs_p1_xmm[25];
bs_p1_xmm[18] ^= bs_p1_xmm[24];
bs_p1_xmm[20] ^= bs_p1_xmm[23];
bs_p1_xmm[19] ^= bs_p1_xmm[22];
bs_p1_xmm[18] ^= bs_p1_xmm[21];
bs_p1_xmm[17] ^= bs_p1_xmm[20];
bs_p1_xmm[28] ^= bs_p1_xmm[31];
bs_p1_xmm[27] ^= bs_p1_xmm[30];
bs_p1_xmm[26] ^= bs_p1_xmm[29];
bs_p1_xmm[25] ^= bs_p1_xmm[28];
bs_p1_xmm[24] ^= bs_p1_xmm[28];
bs_p1_xmm[25] ^= bs_p1_xmm[29];
bs_p1_xmm[26] ^= bs_p1_xmm[30];
bs_p1_xmm[27] ^= bs_p1_xmm[31];
bs_p1_xmm[20] ^= bs_p1_xmm[24];
bs_p1_xmm[21] ^= bs_p1_xmm[25];
bs_p1_xmm[22] ^= bs_p1_xmm[26];
bs_p1_xmm[23] ^= bs_p1_xmm[27];
bs_p1_xmm[18] ^= bs_p1_xmm[19];
bs_p1_xmm[17] ^= bs_p1_xmm[18];
bs_p1_xmm[22] ^= bs_p1_xmm[23];
bs_p1_xmm[21] ^= bs_p1_xmm[22];
bs_p1_xmm[26] ^= bs_p1_xmm[27];
bs_p1_xmm[25] ^= bs_p1_xmm[26];
bs_p1_xmm[30] ^= bs_p1_xmm[31];
bs_p1_xmm[29] ^= bs_p1_xmm[30];
bs_p1_xmm[41] ^= bs_p1_xmm[47];
bs_p1_xmm[40] ^= bs_p1_xmm[46];
bs_p1_xmm[39] ^= bs_p1_xmm[45];
bs_p1_xmm[38] ^= bs_p1_xmm[44];
bs_p1_xmm[37] ^= bs_p1_xmm[43];
bs_p1_xmm[36] ^= bs_p1_xmm[42];
bs_p1_xmm[35] ^= bs_p1_xmm[41];
bs_p1_xmm[34] ^= bs_p1_xmm[40];
bs_p1_xmm[36] ^= bs_p1_xmm[39];
bs_p1_xmm[35] ^= bs_p1_xmm[38];
bs_p1_xmm[34] ^= bs_p1_xmm[37];
bs_p1_xmm[33] ^= bs_p1_xmm[36];
bs_p1_xmm[44] ^= bs_p1_xmm[47];
bs_p1_xmm[43] ^= bs_p1_xmm[46];
bs_p1_xmm[42] ^= bs_p1_xmm[45];
bs_p1_xmm[41] ^= bs_p1_xmm[44];
bs_p1_xmm[40] ^= bs_p1_xmm[44];
bs_p1_xmm[41] ^= bs_p1_xmm[45];
bs_p1_xmm[42] ^= bs_p1_xmm[46];
bs_p1_xmm[43] ^= bs_p1_xmm[47];
bs_p1_xmm[36] ^= bs_p1_xmm[40];
bs_p1_xmm[37] ^= bs_p1_xmm[41];
bs_p1_xmm[38] ^= bs_p1_xmm[42];
bs_p1_xmm[39] ^= bs_p1_xmm[43];
bs_p1_xmm[34] ^= bs_p1_xmm[35];
bs_p1_xmm[33] ^= bs_p1_xmm[34];
bs_p1_xmm[38] ^= bs_p1_xmm[39];
bs_p1_xmm[37] ^= bs_p1_xmm[38];
bs_p1_xmm[42] ^= bs_p1_xmm[43];
bs_p1_xmm[41] ^= bs_p1_xmm[42];
bs_p1_xmm[46] ^= bs_p1_xmm[47];
bs_p1_xmm[45] ^= bs_p1_xmm[46];
/// + 0: bs_p1_xmm[57] = bs_p1_xmm[63];
/// + 0: bs_p1_xmm[56] = bs_p1_xmm[62];
/// + 0: bs_p1_xmm[55] = bs_p1_xmm[61];
/// + 0: bs_p1_xmm[54] = bs_p1_xmm[60];
/// + 0: bs_p1_xmm[53] = bs_p1_xmm[59];
/// + 0: bs_p1_xmm[52] = bs_p1_xmm[58];
/// + 0: bs_p1_xmm[51] = bs_p1_xmm[57];
/// + 0: bs_p1_xmm[50] = bs_p1_xmm[56];
/// + 0: bs_p1_xmm[52] = bs_p1_xmm[55];
/// + 0: bs_p1_xmm[51] = bs_p1_xmm[54];
/// + 0: bs_p1_xmm[50] = bs_p1_xmm[53];
/// + 0: bs_p1_xmm[49] = bs_p1_xmm[52];
/// + 0: bs_p1_xmm[60] = bs_p1_xmm[63];
/// + 0: bs_p1_xmm[59] = bs_p1_xmm[62];
/// + 0: bs_p1_xmm[58] = bs_p1_xmm[61];
/// + 0: bs_p1_xmm[57] = bs_p1_xmm[60];
/// + 0: bs_p1_xmm[56] = bs_p1_xmm[60];
/// + 0: bs_p1_xmm[57] = bs_p1_xmm[61];
/// + 0: bs_p1_xmm[58] = bs_p1_xmm[62];
/// + 0: bs_p1_xmm[59] = bs_p1_xmm[63];
/// + 0: bs_p1_xmm[52] = bs_p1_xmm[56];
/// + 0: bs_p1_xmm[53] = bs_p1_xmm[57];
/// + 0: bs_p1_xmm[54] = bs_p1_xmm[58];
/// + 0: bs_p1_xmm[55] = bs_p1_xmm[59];
/// + 0: bs_p1_xmm[50] = bs_p1_xmm[51];
/// + 0: bs_p1_xmm[49] = bs_p1_xmm[50];
/// + 0: bs_p1_xmm[54] = bs_p1_xmm[55];
/// + 0: bs_p1_xmm[53] = bs_p1_xmm[54];
/// + 0: bs_p1_xmm[58] = bs_p1_xmm[59];
/// + 0: bs_p1_xmm[57] = bs_p1_xmm[58];
/// + 0: bs_p1_xmm[62] = bs_p1_xmm[63];
/// + 0: bs_p1_xmm[61] = bs_p1_xmm[62];
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
bs_p2_xmm[32] = p2_xmm[32];
bs_p2_xmm[33] = p2_xmm[33];
bs_p2_xmm[34] = p2_xmm[34];
bs_p2_xmm[35] = p2_xmm[35];
bs_p2_xmm[36] = p2_xmm[36];
bs_p2_xmm[37] = p2_xmm[37];
bs_p2_xmm[38] = p2_xmm[38];
bs_p2_xmm[39] = p2_xmm[39];
bs_p2_xmm[40] = p2_xmm[40];
bs_p2_xmm[41] = p2_xmm[41];
bs_p2_xmm[42] = p2_xmm[42];
bs_p2_xmm[43] = p2_xmm[43];
bs_p2_xmm[44] = p2_xmm[44];
bs_p2_xmm[45] = p2_xmm[45];
bs_p2_xmm[46] = p2_xmm[46];
bs_p2_xmm[47] = p2_xmm[47];
/// + 0: bs_p2_xmm[33] ^= bs_p2_xmm[63];
/// + 0: bs_p2_xmm[32] ^= bs_p2_xmm[62];
/// + 0: bs_p2_xmm[31] ^= bs_p2_xmm[61];
/// + 0: bs_p2_xmm[30] ^= bs_p2_xmm[60];
/// + 0: bs_p2_xmm[29] ^= bs_p2_xmm[59];
/// + 0: bs_p2_xmm[28] ^= bs_p2_xmm[58];
/// + 0: bs_p2_xmm[27] ^= bs_p2_xmm[57];
/// + 0: bs_p2_xmm[26] ^= bs_p2_xmm[56];
/// + 0: bs_p2_xmm[25] ^= bs_p2_xmm[55];
/// + 0: bs_p2_xmm[24] ^= bs_p2_xmm[54];
/// + 0: bs_p2_xmm[23] ^= bs_p2_xmm[53];
/// + 0: bs_p2_xmm[22] ^= bs_p2_xmm[52];
/// + 0: bs_p2_xmm[21] ^= bs_p2_xmm[51];
/// + 0: bs_p2_xmm[20] ^= bs_p2_xmm[50];
/// + 0: bs_p2_xmm[19] ^= bs_p2_xmm[49];
/// + 0: bs_p2_xmm[18] ^= bs_p2_xmm[48];
bs_p2_xmm[17] ^= bs_p2_xmm[47];
bs_p2_xmm[16] ^= bs_p2_xmm[46];
bs_p2_xmm[15] ^= bs_p2_xmm[45];
bs_p2_xmm[14] ^= bs_p2_xmm[44];
bs_p2_xmm[13] ^= bs_p2_xmm[43];
bs_p2_xmm[12] ^= bs_p2_xmm[42];
bs_p2_xmm[11] ^= bs_p2_xmm[41];
bs_p2_xmm[10] ^= bs_p2_xmm[40];
bs_p2_xmm[9] ^= bs_p2_xmm[39];
bs_p2_xmm[8] ^= bs_p2_xmm[38];
bs_p2_xmm[7] ^= bs_p2_xmm[37];
bs_p2_xmm[6] ^= bs_p2_xmm[36];
bs_p2_xmm[5] ^= bs_p2_xmm[35];
bs_p2_xmm[4] ^= bs_p2_xmm[34];
bs_p2_xmm[3] ^= bs_p2_xmm[33];
bs_p2_xmm[2] ^= bs_p2_xmm[32];
bs_p2_xmm[16] ^= bs_p2_xmm[31];
bs_p2_xmm[15] ^= bs_p2_xmm[30];
bs_p2_xmm[14] ^= bs_p2_xmm[29];
bs_p2_xmm[13] ^= bs_p2_xmm[28];
bs_p2_xmm[12] ^= bs_p2_xmm[27];
bs_p2_xmm[11] ^= bs_p2_xmm[26];
bs_p2_xmm[10] ^= bs_p2_xmm[25];
bs_p2_xmm[9] ^= bs_p2_xmm[24];
bs_p2_xmm[8] ^= bs_p2_xmm[23];
bs_p2_xmm[7] ^= bs_p2_xmm[22];
bs_p2_xmm[6] ^= bs_p2_xmm[21];
bs_p2_xmm[5] ^= bs_p2_xmm[20];
bs_p2_xmm[4] ^= bs_p2_xmm[19];
bs_p2_xmm[3] ^= bs_p2_xmm[18];
bs_p2_xmm[2] ^= bs_p2_xmm[17];
bs_p2_xmm[1] ^= bs_p2_xmm[16];
/// + 0: bs_p2_xmm[48] = bs_p2_xmm[63];
/// + 0: bs_p2_xmm[47] ^= bs_p2_xmm[62];
/// + 0: bs_p2_xmm[46] ^= bs_p2_xmm[61];
/// + 0: bs_p2_xmm[45] ^= bs_p2_xmm[60];
/// + 0: bs_p2_xmm[44] ^= bs_p2_xmm[59];
/// + 0: bs_p2_xmm[43] ^= bs_p2_xmm[58];
/// + 0: bs_p2_xmm[42] ^= bs_p2_xmm[57];
/// + 0: bs_p2_xmm[41] ^= bs_p2_xmm[56];
/// + 0: bs_p2_xmm[40] ^= bs_p2_xmm[55];
/// + 0: bs_p2_xmm[39] ^= bs_p2_xmm[54];
/// + 0: bs_p2_xmm[38] ^= bs_p2_xmm[53];
/// + 0: bs_p2_xmm[37] ^= bs_p2_xmm[52];
/// + 0: bs_p2_xmm[36] ^= bs_p2_xmm[51];
/// + 0: bs_p2_xmm[35] ^= bs_p2_xmm[50];
/// + 0: bs_p2_xmm[34] ^= bs_p2_xmm[49];
/// + 0: bs_p2_xmm[33] ^= bs_p2_xmm[48];
/// + 0: bs_p2_xmm[32] ^= bs_p2_xmm[48];
/// + 0: bs_p2_xmm[33] ^= bs_p2_xmm[49];
/// + 0: bs_p2_xmm[34] ^= bs_p2_xmm[50];
/// + 0: bs_p2_xmm[35] ^= bs_p2_xmm[51];
/// + 0: bs_p2_xmm[36] ^= bs_p2_xmm[52];
/// + 0: bs_p2_xmm[37] ^= bs_p2_xmm[53];
/// + 0: bs_p2_xmm[38] ^= bs_p2_xmm[54];
/// + 0: bs_p2_xmm[39] ^= bs_p2_xmm[55];
/// + 0: bs_p2_xmm[40] ^= bs_p2_xmm[56];
/// + 0: bs_p2_xmm[41] ^= bs_p2_xmm[57];
/// + 0: bs_p2_xmm[42] ^= bs_p2_xmm[58];
/// + 0: bs_p2_xmm[43] ^= bs_p2_xmm[59];
/// + 0: bs_p2_xmm[44] ^= bs_p2_xmm[60];
/// + 0: bs_p2_xmm[45] ^= bs_p2_xmm[61];
/// + 0: bs_p2_xmm[46] ^= bs_p2_xmm[62];
/// + 0: bs_p2_xmm[47] ^= bs_p2_xmm[63];
bs_p2_xmm[16] ^= bs_p2_xmm[32];
bs_p2_xmm[17] ^= bs_p2_xmm[33];
bs_p2_xmm[18] ^= bs_p2_xmm[34];
bs_p2_xmm[19] ^= bs_p2_xmm[35];
bs_p2_xmm[20] ^= bs_p2_xmm[36];
bs_p2_xmm[21] ^= bs_p2_xmm[37];
bs_p2_xmm[22] ^= bs_p2_xmm[38];
bs_p2_xmm[23] ^= bs_p2_xmm[39];
bs_p2_xmm[24] ^= bs_p2_xmm[40];
bs_p2_xmm[25] ^= bs_p2_xmm[41];
bs_p2_xmm[26] ^= bs_p2_xmm[42];
bs_p2_xmm[27] ^= bs_p2_xmm[43];
bs_p2_xmm[28] ^= bs_p2_xmm[44];
bs_p2_xmm[29] ^= bs_p2_xmm[45];
bs_p2_xmm[30] ^= bs_p2_xmm[46];
bs_p2_xmm[31] ^= bs_p2_xmm[47];
bs_p2_xmm[9] ^= bs_p2_xmm[15];
bs_p2_xmm[8] ^= bs_p2_xmm[14];
bs_p2_xmm[7] ^= bs_p2_xmm[13];
bs_p2_xmm[6] ^= bs_p2_xmm[12];
bs_p2_xmm[5] ^= bs_p2_xmm[11];
bs_p2_xmm[4] ^= bs_p2_xmm[10];
bs_p2_xmm[3] ^= bs_p2_xmm[9];
bs_p2_xmm[2] ^= bs_p2_xmm[8];
bs_p2_xmm[4] ^= bs_p2_xmm[7];
bs_p2_xmm[3] ^= bs_p2_xmm[6];
bs_p2_xmm[2] ^= bs_p2_xmm[5];
bs_p2_xmm[1] ^= bs_p2_xmm[4];
bs_p2_xmm[12] ^= bs_p2_xmm[15];
bs_p2_xmm[11] ^= bs_p2_xmm[14];
bs_p2_xmm[10] ^= bs_p2_xmm[13];
bs_p2_xmm[9] ^= bs_p2_xmm[12];
bs_p2_xmm[8] ^= bs_p2_xmm[12];
bs_p2_xmm[9] ^= bs_p2_xmm[13];
bs_p2_xmm[10] ^= bs_p2_xmm[14];
bs_p2_xmm[11] ^= bs_p2_xmm[15];
bs_p2_xmm[4] ^= bs_p2_xmm[8];
bs_p2_xmm[5] ^= bs_p2_xmm[9];
bs_p2_xmm[6] ^= bs_p2_xmm[10];
bs_p2_xmm[7] ^= bs_p2_xmm[11];
bs_p2_xmm[2] ^= bs_p2_xmm[3];
bs_p2_xmm[1] ^= bs_p2_xmm[2];
bs_p2_xmm[6] ^= bs_p2_xmm[7];
bs_p2_xmm[5] ^= bs_p2_xmm[6];
bs_p2_xmm[10] ^= bs_p2_xmm[11];
bs_p2_xmm[9] ^= bs_p2_xmm[10];
bs_p2_xmm[14] ^= bs_p2_xmm[15];
bs_p2_xmm[13] ^= bs_p2_xmm[14];
bs_p2_xmm[25] ^= bs_p2_xmm[31];
bs_p2_xmm[24] ^= bs_p2_xmm[30];
bs_p2_xmm[23] ^= bs_p2_xmm[29];
bs_p2_xmm[22] ^= bs_p2_xmm[28];
bs_p2_xmm[21] ^= bs_p2_xmm[27];
bs_p2_xmm[20] ^= bs_p2_xmm[26];
bs_p2_xmm[19] ^= bs_p2_xmm[25];
bs_p2_xmm[18] ^= bs_p2_xmm[24];
bs_p2_xmm[20] ^= bs_p2_xmm[23];
bs_p2_xmm[19] ^= bs_p2_xmm[22];
bs_p2_xmm[18] ^= bs_p2_xmm[21];
bs_p2_xmm[17] ^= bs_p2_xmm[20];
bs_p2_xmm[28] ^= bs_p2_xmm[31];
bs_p2_xmm[27] ^= bs_p2_xmm[30];
bs_p2_xmm[26] ^= bs_p2_xmm[29];
bs_p2_xmm[25] ^= bs_p2_xmm[28];
bs_p2_xmm[24] ^= bs_p2_xmm[28];
bs_p2_xmm[25] ^= bs_p2_xmm[29];
bs_p2_xmm[26] ^= bs_p2_xmm[30];
bs_p2_xmm[27] ^= bs_p2_xmm[31];
bs_p2_xmm[20] ^= bs_p2_xmm[24];
bs_p2_xmm[21] ^= bs_p2_xmm[25];
bs_p2_xmm[22] ^= bs_p2_xmm[26];
bs_p2_xmm[23] ^= bs_p2_xmm[27];
bs_p2_xmm[18] ^= bs_p2_xmm[19];
bs_p2_xmm[17] ^= bs_p2_xmm[18];
bs_p2_xmm[22] ^= bs_p2_xmm[23];
bs_p2_xmm[21] ^= bs_p2_xmm[22];
bs_p2_xmm[26] ^= bs_p2_xmm[27];
bs_p2_xmm[25] ^= bs_p2_xmm[26];
bs_p2_xmm[30] ^= bs_p2_xmm[31];
bs_p2_xmm[29] ^= bs_p2_xmm[30];
bs_p2_xmm[41] ^= bs_p2_xmm[47];
bs_p2_xmm[40] ^= bs_p2_xmm[46];
bs_p2_xmm[39] ^= bs_p2_xmm[45];
bs_p2_xmm[38] ^= bs_p2_xmm[44];
bs_p2_xmm[37] ^= bs_p2_xmm[43];
bs_p2_xmm[36] ^= bs_p2_xmm[42];
bs_p2_xmm[35] ^= bs_p2_xmm[41];
bs_p2_xmm[34] ^= bs_p2_xmm[40];
bs_p2_xmm[36] ^= bs_p2_xmm[39];
bs_p2_xmm[35] ^= bs_p2_xmm[38];
bs_p2_xmm[34] ^= bs_p2_xmm[37];
bs_p2_xmm[33] ^= bs_p2_xmm[36];
bs_p2_xmm[44] ^= bs_p2_xmm[47];
bs_p2_xmm[43] ^= bs_p2_xmm[46];
bs_p2_xmm[42] ^= bs_p2_xmm[45];
bs_p2_xmm[41] ^= bs_p2_xmm[44];
bs_p2_xmm[40] ^= bs_p2_xmm[44];
bs_p2_xmm[41] ^= bs_p2_xmm[45];
bs_p2_xmm[42] ^= bs_p2_xmm[46];
bs_p2_xmm[43] ^= bs_p2_xmm[47];
bs_p2_xmm[36] ^= bs_p2_xmm[40];
bs_p2_xmm[37] ^= bs_p2_xmm[41];
bs_p2_xmm[38] ^= bs_p2_xmm[42];
bs_p2_xmm[39] ^= bs_p2_xmm[43];
bs_p2_xmm[34] ^= bs_p2_xmm[35];
bs_p2_xmm[33] ^= bs_p2_xmm[34];
bs_p2_xmm[38] ^= bs_p2_xmm[39];
bs_p2_xmm[37] ^= bs_p2_xmm[38];
bs_p2_xmm[42] ^= bs_p2_xmm[43];
bs_p2_xmm[41] ^= bs_p2_xmm[42];
bs_p2_xmm[46] ^= bs_p2_xmm[47];
bs_p2_xmm[45] ^= bs_p2_xmm[46];
/// + 0: bs_p2_xmm[57] = bs_p2_xmm[63];
/// + 0: bs_p2_xmm[56] = bs_p2_xmm[62];
/// + 0: bs_p2_xmm[55] = bs_p2_xmm[61];
/// + 0: bs_p2_xmm[54] = bs_p2_xmm[60];
/// + 0: bs_p2_xmm[53] = bs_p2_xmm[59];
/// + 0: bs_p2_xmm[52] = bs_p2_xmm[58];
/// + 0: bs_p2_xmm[51] = bs_p2_xmm[57];
/// + 0: bs_p2_xmm[50] = bs_p2_xmm[56];
/// + 0: bs_p2_xmm[52] = bs_p2_xmm[55];
/// + 0: bs_p2_xmm[51] = bs_p2_xmm[54];
/// + 0: bs_p2_xmm[50] = bs_p2_xmm[53];
/// + 0: bs_p2_xmm[49] = bs_p2_xmm[52];
/// + 0: bs_p2_xmm[60] = bs_p2_xmm[63];
/// + 0: bs_p2_xmm[59] = bs_p2_xmm[62];
/// + 0: bs_p2_xmm[58] = bs_p2_xmm[61];
/// + 0: bs_p2_xmm[57] = bs_p2_xmm[60];
/// + 0: bs_p2_xmm[56] = bs_p2_xmm[60];
/// + 0: bs_p2_xmm[57] = bs_p2_xmm[61];
/// + 0: bs_p2_xmm[58] = bs_p2_xmm[62];
/// + 0: bs_p2_xmm[59] = bs_p2_xmm[63];
/// + 0: bs_p2_xmm[52] = bs_p2_xmm[56];
/// + 0: bs_p2_xmm[53] = bs_p2_xmm[57];
/// + 0: bs_p2_xmm[54] = bs_p2_xmm[58];
/// + 0: bs_p2_xmm[55] = bs_p2_xmm[59];
/// + 0: bs_p2_xmm[50] = bs_p2_xmm[51];
/// + 0: bs_p2_xmm[49] = bs_p2_xmm[50];
/// + 0: bs_p2_xmm[54] = bs_p2_xmm[55];
/// + 0: bs_p2_xmm[53] = bs_p2_xmm[54];
/// + 0: bs_p2_xmm[58] = bs_p2_xmm[59];
/// + 0: bs_p2_xmm[57] = bs_p2_xmm[58];
/// + 0: bs_p2_xmm[62] = bs_p2_xmm[63];
/// + 0: bs_p2_xmm[61] = bs_p2_xmm[62];
//butterfly_w0x80( vec[128:0-127], 0x0 )
bs_p1_xmm[64] = bs_p1_xmm[0];
bs_p1_xmm[65] = bs_p1_xmm[1];
bs_p1_xmm[66] = bs_p1_xmm[2];
bs_p1_xmm[67] = bs_p1_xmm[3];
bs_p1_xmm[68] = bs_p1_xmm[4];
bs_p1_xmm[69] = bs_p1_xmm[5];
bs_p1_xmm[70] = bs_p1_xmm[6];
bs_p1_xmm[71] = bs_p1_xmm[7];
bs_p1_xmm[72] = bs_p1_xmm[8];
bs_p1_xmm[73] = bs_p1_xmm[9];
bs_p1_xmm[74] = bs_p1_xmm[10];
bs_p1_xmm[75] = bs_p1_xmm[11];
bs_p1_xmm[76] = bs_p1_xmm[12];
bs_p1_xmm[77] = bs_p1_xmm[13];
bs_p1_xmm[78] = bs_p1_xmm[14];
bs_p1_xmm[79] = bs_p1_xmm[15];
bs_p1_xmm[80] = bs_p1_xmm[16];
bs_p1_xmm[81] = bs_p1_xmm[17];
bs_p1_xmm[82] = bs_p1_xmm[18];
bs_p1_xmm[83] = bs_p1_xmm[19];
bs_p1_xmm[84] = bs_p1_xmm[20];
bs_p1_xmm[85] = bs_p1_xmm[21];
bs_p1_xmm[86] = bs_p1_xmm[22];
bs_p1_xmm[87] = bs_p1_xmm[23];
bs_p1_xmm[88] = bs_p1_xmm[24];
bs_p1_xmm[89] = bs_p1_xmm[25];
bs_p1_xmm[90] = bs_p1_xmm[26];
bs_p1_xmm[91] = bs_p1_xmm[27];
bs_p1_xmm[92] = bs_p1_xmm[28];
bs_p1_xmm[93] = bs_p1_xmm[29];
bs_p1_xmm[94] = bs_p1_xmm[30];
bs_p1_xmm[95] = bs_p1_xmm[31];
/// interaction with truncated: //bs_p1_xmm[96]:0x20 ,0? True, omit? True
bs_p1_xmm[96] = bs_p1_xmm[32];
/// interaction with truncated: //bs_p1_xmm[97]:0x20 ,0? True, omit? True
bs_p1_xmm[97] = bs_p1_xmm[33];
/// interaction with truncated: //bs_p1_xmm[98]:0x5 ,0? True, omit? True
bs_p1_xmm[98] = bs_p1_xmm[34];
/// interaction with truncated: //bs_p1_xmm[99]:0x2f ,0? True, omit? True
bs_p1_xmm[99] = bs_p1_xmm[35];
/// interaction with truncated: //bs_p1_xmm[100]:0x1 ,0? True, omit? True
bs_p1_xmm[100] = bs_p1_xmm[36];
/// interaction with truncated: //bs_p1_xmm[101]:0x25 ,0? True, omit? True
bs_p1_xmm[101] = bs_p1_xmm[37];
/// interaction with truncated: //bs_p1_xmm[102]:0x3 ,0? True, omit? True
bs_p1_xmm[102] = bs_p1_xmm[38];
/// interaction with truncated: //bs_p1_xmm[103]:0x20 ,0? True, omit? True
bs_p1_xmm[103] = bs_p1_xmm[39];
/// interaction with truncated: //bs_p1_xmm[104]:0x5 ,0? True, omit? True
bs_p1_xmm[104] = bs_p1_xmm[40];
/// interaction with truncated: //bs_p1_xmm[105]:0x2b ,0? True, omit? True
bs_p1_xmm[105] = bs_p1_xmm[41];
/// interaction with truncated: //bs_p1_xmm[106]:0x3 ,0? True, omit? True
bs_p1_xmm[106] = bs_p1_xmm[42];
/// interaction with truncated: //bs_p1_xmm[107]:0x2a ,0? True, omit? True
bs_p1_xmm[107] = bs_p1_xmm[43];
/// interaction with truncated: //bs_p1_xmm[108]:0x3 ,0? True, omit? True
bs_p1_xmm[108] = bs_p1_xmm[44];
/// interaction with truncated: //bs_p1_xmm[109]:0x2c ,0? True, omit? True
bs_p1_xmm[109] = bs_p1_xmm[45];
/// interaction with truncated: //bs_p1_xmm[110]:0x1 ,0? True, omit? True
bs_p1_xmm[110] = bs_p1_xmm[46];
/// interaction with truncated: //bs_p1_xmm[111]:0x2f ,0? True, omit? True
bs_p1_xmm[111] = bs_p1_xmm[47];
/// interaction with truncated: //bs_p1_xmm[112]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[112] = bs_p1_xmm[48];
/// interaction with truncated: //bs_p1_xmm[113]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[113] = bs_p1_xmm[49];
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[114] = bs_p1_xmm[50];
/// interaction with truncated: //bs_p1_xmm[115]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[115] = bs_p1_xmm[51];
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[116] = bs_p1_xmm[52];
/// interaction with truncated: //bs_p1_xmm[117]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[117] = bs_p1_xmm[53];
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[118] = bs_p1_xmm[54];
/// interaction with truncated: //bs_p1_xmm[119]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[119] = bs_p1_xmm[55];
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[120] = bs_p1_xmm[56];
/// interaction with truncated: //bs_p1_xmm[121]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[121] = bs_p1_xmm[57];
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[122] = bs_p1_xmm[58];
/// interaction with truncated: //bs_p1_xmm[123]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[123] = bs_p1_xmm[59];
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[124] = bs_p1_xmm[60];
/// interaction with truncated: //bs_p1_xmm[125]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[125] = bs_p1_xmm[61];
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[126] = bs_p1_xmm[62];
/// interaction with truncated: //bs_p1_xmm[127]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[127] = bs_p1_xmm[63];
//butterfly_w0x40( vec[64:0-63], 0x0 )
bs_p1_xmm[32] ^= bs_p1_xmm[0];
bs_p1_xmm[33] ^= bs_p1_xmm[1];
bs_p1_xmm[34] ^= bs_p1_xmm[2];
bs_p1_xmm[35] ^= bs_p1_xmm[3];
bs_p1_xmm[36] ^= bs_p1_xmm[4];
bs_p1_xmm[37] ^= bs_p1_xmm[5];
bs_p1_xmm[38] ^= bs_p1_xmm[6];
bs_p1_xmm[39] ^= bs_p1_xmm[7];
bs_p1_xmm[40] ^= bs_p1_xmm[8];
bs_p1_xmm[41] ^= bs_p1_xmm[9];
bs_p1_xmm[42] ^= bs_p1_xmm[10];
bs_p1_xmm[43] ^= bs_p1_xmm[11];
bs_p1_xmm[44] ^= bs_p1_xmm[12];
bs_p1_xmm[45] ^= bs_p1_xmm[13];
bs_p1_xmm[46] ^= bs_p1_xmm[14];
bs_p1_xmm[47] ^= bs_p1_xmm[15];
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
//butterfly_w0x20( vec[32:0-31], 0x0 )
bs_p1_xmm[16] ^= bs_p1_xmm[0];
bs_p1_xmm[17] ^= bs_p1_xmm[1];
bs_p1_xmm[18] ^= bs_p1_xmm[2];
bs_p1_xmm[19] ^= bs_p1_xmm[3];
bs_p1_xmm[20] ^= bs_p1_xmm[4];
bs_p1_xmm[21] ^= bs_p1_xmm[5];
bs_p1_xmm[22] ^= bs_p1_xmm[6];
bs_p1_xmm[23] ^= bs_p1_xmm[7];
bs_p1_xmm[24] ^= bs_p1_xmm[8];
bs_p1_xmm[25] ^= bs_p1_xmm[9];
bs_p1_xmm[26] ^= bs_p1_xmm[10];
bs_p1_xmm[27] ^= bs_p1_xmm[11];
bs_p1_xmm[28] ^= bs_p1_xmm[12];
bs_p1_xmm[29] ^= bs_p1_xmm[13];
bs_p1_xmm[30] ^= bs_p1_xmm[14];
bs_p1_xmm[31] ^= bs_p1_xmm[15];
//butterfly_w0x10( vec[16:0-15], 0x0 )
bs_p1_xmm[8] ^= bs_p1_xmm[0];
bs_p1_xmm[9] ^= bs_p1_xmm[1];
bs_p1_xmm[10] ^= bs_p1_xmm[2];
bs_p1_xmm[11] ^= bs_p1_xmm[3];
bs_p1_xmm[12] ^= bs_p1_xmm[4];
bs_p1_xmm[13] ^= bs_p1_xmm[5];
bs_p1_xmm[14] ^= bs_p1_xmm[6];
bs_p1_xmm[15] ^= bs_p1_xmm[7];
//butterfly_w0x8( vec[8:0-7], 0x0 )
bs_p1_xmm[4] ^= bs_p1_xmm[0];
bs_p1_xmm[5] ^= bs_p1_xmm[1];
bs_p1_xmm[6] ^= bs_p1_xmm[2];
bs_p1_xmm[7] ^= bs_p1_xmm[3];
//butterfly_w0x4( vec[4:0-3], 0x0 )
bs_p1_xmm[2] ^= bs_p1_xmm[0];
bs_p1_xmm[3] ^= bs_p1_xmm[1];
//butterfly_w0x2( vec[2:0-1], 0x0 )
bs_p1_xmm[1] ^= bs_p1_xmm[0];
//butterfly_w0x2( vec[2:2-3], 0x2 )
temp = bs_p1_xmm[3];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[2] ^= temp;
bs_p1_xmm[3] ^= bs_p1_xmm[2];
//butterfly_w0x4( vec[4:4-7], 0x4 )
temp = bs_p1_xmm[6];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[4] ^= temp;
bs_p1_xmm[6] ^= bs_p1_xmm[4];
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[5] ^= temp;
bs_p1_xmm[7] ^= bs_p1_xmm[5];
//butterfly_w0x2( vec[2:4-5], 0x4 )
temp = bs_p1_xmm[5];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[4] ^= temp;
bs_p1_xmm[5] ^= bs_p1_xmm[4];
//butterfly_w0x2( vec[2:6-7], 0x6 )
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[6] ^= temp;
bs_p1_xmm[7] ^= bs_p1_xmm[6];
//butterfly_w0x8( vec[8:8-15], 0x8 )
temp = bs_p1_xmm[12];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[8] ^= temp;
bs_p1_xmm[12] ^= bs_p1_xmm[8];
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[9] ^= temp;
bs_p1_xmm[13] ^= bs_p1_xmm[9];
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[10] ^= temp;
bs_p1_xmm[14] ^= bs_p1_xmm[10];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[11] ^= temp;
bs_p1_xmm[15] ^= bs_p1_xmm[11];
//butterfly_w0x4( vec[4:8-11], 0x8 )
temp = bs_p1_xmm[10];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[8] ^= temp;
bs_p1_xmm[10] ^= bs_p1_xmm[8];
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[9] ^= temp;
bs_p1_xmm[11] ^= bs_p1_xmm[9];
//butterfly_w0x2( vec[2:8-9], 0x8 )
temp = bs_p1_xmm[9];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[8] ^= temp;
bs_p1_xmm[9] ^= bs_p1_xmm[8];
//butterfly_w0x2( vec[2:10-11], 0xa )
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[10] ^= temp;
bs_p1_xmm[11] ^= bs_p1_xmm[10];
//butterfly_w0x4( vec[4:12-15], 0xc )
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[12] ^= temp;
bs_p1_xmm[14] ^= bs_p1_xmm[12];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[13] ^= temp;
bs_p1_xmm[15] ^= bs_p1_xmm[13];
//butterfly_w0x2( vec[2:12-13], 0xc )
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0xc,temp);
bs_p1_xmm[12] ^= temp;
bs_p1_xmm[13] ^= bs_p1_xmm[12];
//butterfly_w0x2( vec[2:14-15], 0xe )
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0xe,temp);
bs_p1_xmm[14] ^= temp;
bs_p1_xmm[15] ^= bs_p1_xmm[14];
//butterfly_w0x10( vec[16:16-31], 0x10 )
temp = bs_p1_xmm[24];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[16] ^= temp;
bs_p1_xmm[24] ^= bs_p1_xmm[16];
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[17] ^= temp;
bs_p1_xmm[25] ^= bs_p1_xmm[17];
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[18] ^= temp;
bs_p1_xmm[26] ^= bs_p1_xmm[18];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[19] ^= temp;
bs_p1_xmm[27] ^= bs_p1_xmm[19];
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[20] ^= temp;
bs_p1_xmm[28] ^= bs_p1_xmm[20];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[21] ^= temp;
bs_p1_xmm[29] ^= bs_p1_xmm[21];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[22] ^= temp;
bs_p1_xmm[30] ^= bs_p1_xmm[22];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[23] ^= temp;
bs_p1_xmm[31] ^= bs_p1_xmm[23];
//butterfly_w0x8( vec[8:16-23], 0x10 )
temp = bs_p1_xmm[20];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[16] ^= temp;
bs_p1_xmm[20] ^= bs_p1_xmm[16];
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[17] ^= temp;
bs_p1_xmm[21] ^= bs_p1_xmm[17];
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[18] ^= temp;
bs_p1_xmm[22] ^= bs_p1_xmm[18];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[19] ^= temp;
bs_p1_xmm[23] ^= bs_p1_xmm[19];
//butterfly_w0x4( vec[4:16-19], 0x10 )
temp = bs_p1_xmm[18];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[16] ^= temp;
bs_p1_xmm[18] ^= bs_p1_xmm[16];
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[17] ^= temp;
bs_p1_xmm[19] ^= bs_p1_xmm[17];
//butterfly_w0x2( vec[2:16-17], 0x10 )
temp = bs_p1_xmm[17];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[16] ^= temp;
bs_p1_xmm[17] ^= bs_p1_xmm[16];
//butterfly_w0x2( vec[2:18-19], 0x12 )
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[18] ^= temp;
bs_p1_xmm[19] ^= bs_p1_xmm[18];
//butterfly_w0x4( vec[4:20-23], 0x14 )
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[20] ^= temp;
bs_p1_xmm[22] ^= bs_p1_xmm[20];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[21] ^= temp;
bs_p1_xmm[23] ^= bs_p1_xmm[21];
//butterfly_w0x2( vec[2:20-21], 0x14 )
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[20] ^= temp;
bs_p1_xmm[21] ^= bs_p1_xmm[20];
//butterfly_w0x2( vec[2:22-23], 0x16 )
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[22] ^= temp;
bs_p1_xmm[23] ^= bs_p1_xmm[22];
//butterfly_w0x8( vec[8:24-31], 0x18 )
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[24] ^= temp;
bs_p1_xmm[28] ^= bs_p1_xmm[24];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[25] ^= temp;
bs_p1_xmm[29] ^= bs_p1_xmm[25];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[26] ^= temp;
bs_p1_xmm[30] ^= bs_p1_xmm[26];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[27] ^= temp;
bs_p1_xmm[31] ^= bs_p1_xmm[27];
//butterfly_w0x4( vec[4:24-27], 0x18 )
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[24] ^= temp;
bs_p1_xmm[26] ^= bs_p1_xmm[24];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[25] ^= temp;
bs_p1_xmm[27] ^= bs_p1_xmm[25];
//butterfly_w0x2( vec[2:24-25], 0x18 )
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x18,temp);
bs_p1_xmm[24] ^= temp;
bs_p1_xmm[25] ^= bs_p1_xmm[24];
//butterfly_w0x2( vec[2:26-27], 0x1a )
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x1a,temp);
bs_p1_xmm[26] ^= temp;
bs_p1_xmm[27] ^= bs_p1_xmm[26];
//butterfly_w0x4( vec[4:28-31], 0x1c )
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[28] ^= temp;
bs_p1_xmm[30] ^= bs_p1_xmm[28];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[29] ^= temp;
bs_p1_xmm[31] ^= bs_p1_xmm[29];
//butterfly_w0x2( vec[2:28-29], 0x1c )
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[28] ^= temp;
bs_p1_xmm[29] ^= bs_p1_xmm[28];
//butterfly_w0x2( vec[2:30-31], 0x1e )
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[30] ^= temp;
bs_p1_xmm[31] ^= bs_p1_xmm[30];
//butterfly_w0x20( vec[32:32-63], 0x20 )
temp = bs_p1_xmm[48];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[48] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[33] ^= temp;
bs_p1_xmm[49] ^= bs_p1_xmm[33];
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[34] ^= temp;
bs_p1_xmm[50] ^= bs_p1_xmm[34];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[35] ^= temp;
bs_p1_xmm[51] ^= bs_p1_xmm[35];
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[36] ^= temp;
bs_p1_xmm[52] ^= bs_p1_xmm[36];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[37] ^= temp;
bs_p1_xmm[53] ^= bs_p1_xmm[37];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[38] ^= temp;
bs_p1_xmm[54] ^= bs_p1_xmm[38];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[39] ^= temp;
bs_p1_xmm[55] ^= bs_p1_xmm[39];
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[40] ^= temp;
bs_p1_xmm[56] ^= bs_p1_xmm[40];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[41] ^= temp;
bs_p1_xmm[57] ^= bs_p1_xmm[41];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[42] ^= temp;
bs_p1_xmm[58] ^= bs_p1_xmm[42];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[43] ^= temp;
bs_p1_xmm[59] ^= bs_p1_xmm[43];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[44] ^= temp;
bs_p1_xmm[60] ^= bs_p1_xmm[44];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[45] ^= temp;
bs_p1_xmm[61] ^= bs_p1_xmm[45];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[46] ^= temp;
bs_p1_xmm[62] ^= bs_p1_xmm[46];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[47] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[47];
//butterfly_w0x10( vec[16:32-47], 0x20 )
temp = bs_p1_xmm[40];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[40] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[33] ^= temp;
bs_p1_xmm[41] ^= bs_p1_xmm[33];
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[34] ^= temp;
bs_p1_xmm[42] ^= bs_p1_xmm[34];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[35] ^= temp;
bs_p1_xmm[43] ^= bs_p1_xmm[35];
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[36] ^= temp;
bs_p1_xmm[44] ^= bs_p1_xmm[36];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[37] ^= temp;
bs_p1_xmm[45] ^= bs_p1_xmm[37];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[38] ^= temp;
bs_p1_xmm[46] ^= bs_p1_xmm[38];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[39] ^= temp;
bs_p1_xmm[47] ^= bs_p1_xmm[39];
//butterfly_w0x8( vec[8:32-39], 0x20 )
temp = bs_p1_xmm[36];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[36] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[33] ^= temp;
bs_p1_xmm[37] ^= bs_p1_xmm[33];
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[34] ^= temp;
bs_p1_xmm[38] ^= bs_p1_xmm[34];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[35] ^= temp;
bs_p1_xmm[39] ^= bs_p1_xmm[35];
//butterfly_w0x4( vec[4:32-35], 0x20 )
temp = bs_p1_xmm[34];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[34] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[33] ^= temp;
bs_p1_xmm[35] ^= bs_p1_xmm[33];
//butterfly_w0x2( vec[2:32-33], 0x20 )
temp = bs_p1_xmm[33];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[33] ^= bs_p1_xmm[32];
//butterfly_w0x2( vec[2:34-35], 0x22 )
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[34] ^= temp;
bs_p1_xmm[35] ^= bs_p1_xmm[34];
//butterfly_w0x4( vec[4:36-39], 0x24 )
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[36] ^= temp;
bs_p1_xmm[38] ^= bs_p1_xmm[36];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[37] ^= temp;
bs_p1_xmm[39] ^= bs_p1_xmm[37];
//butterfly_w0x2( vec[2:36-37], 0x24 )
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0x24,temp);
bs_p1_xmm[36] ^= temp;
bs_p1_xmm[37] ^= bs_p1_xmm[36];
//butterfly_w0x2( vec[2:38-39], 0x26 )
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x26,temp);
bs_p1_xmm[38] ^= temp;
bs_p1_xmm[39] ^= bs_p1_xmm[38];
//butterfly_w0x8( vec[8:40-47], 0x28 )
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[40] ^= temp;
bs_p1_xmm[44] ^= bs_p1_xmm[40];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[41] ^= temp;
bs_p1_xmm[45] ^= bs_p1_xmm[41];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[42] ^= temp;
bs_p1_xmm[46] ^= bs_p1_xmm[42];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[43] ^= temp;
bs_p1_xmm[47] ^= bs_p1_xmm[43];
//butterfly_w0x4( vec[4:40-43], 0x28 )
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[40] ^= temp;
bs_p1_xmm[42] ^= bs_p1_xmm[40];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[41] ^= temp;
bs_p1_xmm[43] ^= bs_p1_xmm[41];
//butterfly_w0x2( vec[2:40-41], 0x28 )
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[40] ^= temp;
bs_p1_xmm[41] ^= bs_p1_xmm[40];
//butterfly_w0x2( vec[2:42-43], 0x2a )
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[42] ^= temp;
bs_p1_xmm[43] ^= bs_p1_xmm[42];
//butterfly_w0x4( vec[4:44-47], 0x2c )
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[44] ^= temp;
bs_p1_xmm[46] ^= bs_p1_xmm[44];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[45] ^= temp;
bs_p1_xmm[47] ^= bs_p1_xmm[45];
//butterfly_w0x2( vec[2:44-45], 0x2c )
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x2c,temp);
bs_p1_xmm[44] ^= temp;
bs_p1_xmm[45] ^= bs_p1_xmm[44];
//butterfly_w0x2( vec[2:46-47], 0x2e )
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x2e,temp);
bs_p1_xmm[46] ^= temp;
bs_p1_xmm[47] ^= bs_p1_xmm[46];
//butterfly_w0x10( vec[16:48-63], 0x30 )
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[48] ^= temp;
bs_p1_xmm[56] ^= bs_p1_xmm[48];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[49] ^= temp;
bs_p1_xmm[57] ^= bs_p1_xmm[49];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[50] ^= temp;
bs_p1_xmm[58] ^= bs_p1_xmm[50];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[51] ^= temp;
bs_p1_xmm[59] ^= bs_p1_xmm[51];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[52] ^= temp;
bs_p1_xmm[60] ^= bs_p1_xmm[52];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[53] ^= temp;
bs_p1_xmm[61] ^= bs_p1_xmm[53];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[54] ^= temp;
bs_p1_xmm[62] ^= bs_p1_xmm[54];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[55] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[55];
//butterfly_w0x8( vec[8:48-55], 0x30 )
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[48] ^= temp;
bs_p1_xmm[52] ^= bs_p1_xmm[48];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[49] ^= temp;
bs_p1_xmm[53] ^= bs_p1_xmm[49];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[50] ^= temp;
bs_p1_xmm[54] ^= bs_p1_xmm[50];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[51] ^= temp;
bs_p1_xmm[55] ^= bs_p1_xmm[51];
//butterfly_w0x4( vec[4:48-51], 0x30 )
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[48] ^= temp;
bs_p1_xmm[50] ^= bs_p1_xmm[48];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[49] ^= temp;
bs_p1_xmm[51] ^= bs_p1_xmm[49];
//butterfly_w0x2( vec[2:48-49], 0x30 )
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x30,temp);
bs_p1_xmm[48] ^= temp;
bs_p1_xmm[49] ^= bs_p1_xmm[48];
//butterfly_w0x2( vec[2:50-51], 0x32 )
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x32,temp);
bs_p1_xmm[50] ^= temp;
bs_p1_xmm[51] ^= bs_p1_xmm[50];
//butterfly_w0x4( vec[4:52-55], 0x34 )
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[52] ^= temp;
bs_p1_xmm[54] ^= bs_p1_xmm[52];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[53] ^= temp;
bs_p1_xmm[55] ^= bs_p1_xmm[53];
//butterfly_w0x2( vec[2:52-53], 0x34 )
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x34,temp);
bs_p1_xmm[52] ^= temp;
bs_p1_xmm[53] ^= bs_p1_xmm[52];
//butterfly_w0x2( vec[2:54-55], 0x36 )
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x36,temp);
bs_p1_xmm[54] ^= temp;
bs_p1_xmm[55] ^= bs_p1_xmm[54];
//butterfly_w0x8( vec[8:56-63], 0x38 )
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[56] ^= temp;
bs_p1_xmm[60] ^= bs_p1_xmm[56];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[57] ^= temp;
bs_p1_xmm[61] ^= bs_p1_xmm[57];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[58] ^= temp;
bs_p1_xmm[62] ^= bs_p1_xmm[58];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[59] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[59];
//butterfly_w0x4( vec[4:56-59], 0x38 )
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[56] ^= temp;
bs_p1_xmm[58] ^= bs_p1_xmm[56];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[57] ^= temp;
bs_p1_xmm[59] ^= bs_p1_xmm[57];
//butterfly_w0x2( vec[2:56-57], 0x38 )
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x38,temp);
bs_p1_xmm[56] ^= temp;
bs_p1_xmm[57] ^= bs_p1_xmm[56];
//butterfly_w0x2( vec[2:58-59], 0x3a )
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x3a,temp);
bs_p1_xmm[58] ^= temp;
bs_p1_xmm[59] ^= bs_p1_xmm[58];
//butterfly_w0x4( vec[4:60-63], 0x3c )
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[60] ^= temp;
bs_p1_xmm[62] ^= bs_p1_xmm[60];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[61] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[61];
//butterfly_w0x2( vec[2:60-61], 0x3c )
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x3c,temp);
bs_p1_xmm[60] ^= temp;
bs_p1_xmm[61] ^= bs_p1_xmm[60];
//butterfly_w0x2( vec[2:62-63], 0x3e )
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x3e,temp);
bs_p1_xmm[62] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[62];
//butterfly_w0x40( vec[64:64-127], 0x40 )
/// interaction with truncated: //bs_p1_xmm[96]:0x20 ,0? False, omit? True
temp = bs_p1_xmm[96];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p1_xmm[64] ^= temp;
/// interaction with truncated: //bs_p1_xmm[96]:0x10 ,0? False, omit? True
bs_p1_xmm[96] ^= bs_p1_xmm[64];
/// interaction with truncated: //bs_p1_xmm[97]:0x20 ,0? False, omit? True
temp = bs_p1_xmm[97];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p1_xmm[65] ^= temp;
/// interaction with truncated: //bs_p1_xmm[97]:0x10 ,0? False, omit? True
bs_p1_xmm[97] ^= bs_p1_xmm[65];
/// interaction with truncated: //bs_p1_xmm[98]:0x5 ,0? False, omit? True
temp = bs_p1_xmm[98];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0xa ,0? False, omit? True
bs_p1_xmm[66] ^= temp;
/// interaction with truncated: //bs_p1_xmm[98]:0x2f ,0? False, omit? True
bs_p1_xmm[98] ^= bs_p1_xmm[66];
/// interaction with truncated: //bs_p1_xmm[99]:0x2f ,0? False, omit? True
temp = bs_p1_xmm[99];
/// omit x const: //temp:0x35 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x35 ,0? False, omit? True
bs_p1_xmm[67] ^= temp;
/// interaction with truncated: //bs_p1_xmm[99]:0x2a ,0? False, omit? True
bs_p1_xmm[99] ^= bs_p1_xmm[67];
/// interaction with truncated: //bs_p1_xmm[100]:0x1 ,0? False, omit? True
temp = bs_p1_xmm[100];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2 ,0? False, omit? True
bs_p1_xmm[68] ^= temp;
/// interaction with truncated: //bs_p1_xmm[100]:0x4 ,0? False, omit? True
bs_p1_xmm[100] ^= bs_p1_xmm[68];
/// interaction with truncated: //bs_p1_xmm[101]:0x25 ,0? False, omit? True
temp = bs_p1_xmm[101];
/// omit x const: //temp:0x3a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x3a ,0? False, omit? True
bs_p1_xmm[69] ^= temp;
/// interaction with truncated: //bs_p1_xmm[101]:0x25 ,0? False, omit? True
bs_p1_xmm[101] ^= bs_p1_xmm[69];
/// interaction with truncated: //bs_p1_xmm[102]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[102];
/// omit x const: //temp:0x1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x1 ,0? False, omit? True
bs_p1_xmm[70] ^= temp;
/// interaction with truncated: //bs_p1_xmm[102]:0x3 ,0? False, omit? True
bs_p1_xmm[102] ^= bs_p1_xmm[70];
/// interaction with truncated: //bs_p1_xmm[103]:0x20 ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p1_xmm[71] ^= temp;
/// interaction with truncated: //bs_p1_xmm[103]:0x25 ,0? False, omit? True
bs_p1_xmm[103] ^= bs_p1_xmm[71];
/// interaction with truncated: //bs_p1_xmm[104]:0x5 ,0? False, omit? True
temp = bs_p1_xmm[104];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0xa ,0? False, omit? True
bs_p1_xmm[72] ^= temp;
/// interaction with truncated: //bs_p1_xmm[104]:0x8 ,0? False, omit? True
bs_p1_xmm[104] ^= bs_p1_xmm[72];
/// interaction with truncated: //bs_p1_xmm[105]:0x2b ,0? False, omit? True
temp = bs_p1_xmm[105];
/// omit x const: //temp:0x3d ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x3d ,0? False, omit? True
bs_p1_xmm[73] ^= temp;
/// interaction with truncated: //bs_p1_xmm[105]:0x22 ,0? False, omit? True
bs_p1_xmm[105] ^= bs_p1_xmm[73];
/// interaction with truncated: //bs_p1_xmm[106]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[106];
/// omit x const: //temp:0x1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x1 ,0? False, omit? True
bs_p1_xmm[74] ^= temp;
/// interaction with truncated: //bs_p1_xmm[106]:0x7 ,0? False, omit? True
bs_p1_xmm[106] ^= bs_p1_xmm[74];
/// interaction with truncated: //bs_p1_xmm[107]:0x2a ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0x3f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x3f ,0? False, omit? True
bs_p1_xmm[75] ^= temp;
/// interaction with truncated: //bs_p1_xmm[107]:0x2e ,0? False, omit? True
bs_p1_xmm[107] ^= bs_p1_xmm[75];
/// interaction with truncated: //bs_p1_xmm[108]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[108];
/// omit x const: //temp:0x1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x1 ,0? False, omit? True
bs_p1_xmm[76] ^= temp;
/// interaction with truncated: //bs_p1_xmm[108]:0x3 ,0? False, omit? True
bs_p1_xmm[108] ^= bs_p1_xmm[76];
/// interaction with truncated: //bs_p1_xmm[109]:0x2c ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0x34 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x34 ,0? False, omit? True
bs_p1_xmm[77] ^= temp;
/// interaction with truncated: //bs_p1_xmm[109]:0x21 ,0? False, omit? True
bs_p1_xmm[109] ^= bs_p1_xmm[77];
/// interaction with truncated: //bs_p1_xmm[110]:0x1 ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2 ,0? False, omit? True
bs_p1_xmm[78] ^= temp;
/// interaction with truncated: //bs_p1_xmm[110]:0x0 ,0? False, omit? True
bs_p1_xmm[110] ^= bs_p1_xmm[78];
/// interaction with truncated: //bs_p1_xmm[111]:0x2f ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0x35 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x35 ,0? False, omit? True
bs_p1_xmm[79] ^= temp;
/// interaction with truncated: //bs_p1_xmm[111]:0x26 ,0? False, omit? True
bs_p1_xmm[111] ^= bs_p1_xmm[79];
/// interaction with truncated: //bs_p1_xmm[112]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[112];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[80] ^= temp;
/// interaction with truncated: //bs_p1_xmm[112]:0x1 ,0? True, omit? True
bs_p1_xmm[112] = bs_p1_xmm[80];
/// interaction with truncated: //bs_p1_xmm[113]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[113];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[81] ^= temp;
/// interaction with truncated: //bs_p1_xmm[113]:0x1f ,0? True, omit? True
bs_p1_xmm[113] = bs_p1_xmm[81];
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[114];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[82] ^= temp;
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? True, omit? True
bs_p1_xmm[114] = bs_p1_xmm[82];
/// interaction with truncated: //bs_p1_xmm[115]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[83] ^= temp;
/// interaction with truncated: //bs_p1_xmm[115]:0x30 ,0? True, omit? True
bs_p1_xmm[115] = bs_p1_xmm[83];
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[116];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[84] ^= temp;
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? True, omit? True
bs_p1_xmm[116] = bs_p1_xmm[84];
/// interaction with truncated: //bs_p1_xmm[117]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[85] ^= temp;
/// interaction with truncated: //bs_p1_xmm[117]:0x30 ,0? True, omit? True
bs_p1_xmm[117] = bs_p1_xmm[85];
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[86] ^= temp;
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? True, omit? True
bs_p1_xmm[118] = bs_p1_xmm[86];
/// interaction with truncated: //bs_p1_xmm[119]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[87] ^= temp;
/// interaction with truncated: //bs_p1_xmm[119]:0x30 ,0? True, omit? True
bs_p1_xmm[119] = bs_p1_xmm[87];
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[120];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[88] ^= temp;
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? True, omit? True
bs_p1_xmm[120] = bs_p1_xmm[88];
/// interaction with truncated: //bs_p1_xmm[121]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[89] ^= temp;
/// interaction with truncated: //bs_p1_xmm[121]:0x30 ,0? True, omit? True
bs_p1_xmm[121] = bs_p1_xmm[89];
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[90] ^= temp;
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? True, omit? True
bs_p1_xmm[122] = bs_p1_xmm[90];
/// interaction with truncated: //bs_p1_xmm[123]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[91] ^= temp;
/// interaction with truncated: //bs_p1_xmm[123]:0x30 ,0? True, omit? True
bs_p1_xmm[123] = bs_p1_xmm[91];
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[92] ^= temp;
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? True, omit? True
bs_p1_xmm[124] = bs_p1_xmm[92];
/// interaction with truncated: //bs_p1_xmm[125]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[93] ^= temp;
/// interaction with truncated: //bs_p1_xmm[125]:0x30 ,0? True, omit? True
bs_p1_xmm[125] = bs_p1_xmm[93];
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[94] ^= temp;
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? True, omit? True
bs_p1_xmm[126] = bs_p1_xmm[94];
/// interaction with truncated: //bs_p1_xmm[127]:0x0 ,0? True, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[95] ^= temp;
/// interaction with truncated: //bs_p1_xmm[127]:0x30 ,0? True, omit? True
bs_p1_xmm[127] = bs_p1_xmm[95];
//butterfly_w0x20( vec[32:64-95], 0x40 )
temp = bs_p1_xmm[80];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[80] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[81];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[65] ^= temp;
bs_p1_xmm[81] ^= bs_p1_xmm[65];
temp = bs_p1_xmm[82];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[66] ^= temp;
bs_p1_xmm[82] ^= bs_p1_xmm[66];
temp = bs_p1_xmm[83];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[67] ^= temp;
bs_p1_xmm[83] ^= bs_p1_xmm[67];
temp = bs_p1_xmm[84];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[68] ^= temp;
bs_p1_xmm[84] ^= bs_p1_xmm[68];
temp = bs_p1_xmm[85];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[69] ^= temp;
bs_p1_xmm[85] ^= bs_p1_xmm[69];
temp = bs_p1_xmm[86];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[70] ^= temp;
bs_p1_xmm[86] ^= bs_p1_xmm[70];
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[71] ^= temp;
bs_p1_xmm[87] ^= bs_p1_xmm[71];
temp = bs_p1_xmm[88];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[72] ^= temp;
bs_p1_xmm[88] ^= bs_p1_xmm[72];
temp = bs_p1_xmm[89];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[73] ^= temp;
bs_p1_xmm[89] ^= bs_p1_xmm[73];
temp = bs_p1_xmm[90];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[74] ^= temp;
bs_p1_xmm[90] ^= bs_p1_xmm[74];
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[75] ^= temp;
bs_p1_xmm[91] ^= bs_p1_xmm[75];
temp = bs_p1_xmm[92];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[76] ^= temp;
bs_p1_xmm[92] ^= bs_p1_xmm[76];
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[77] ^= temp;
bs_p1_xmm[93] ^= bs_p1_xmm[77];
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[78] ^= temp;
bs_p1_xmm[94] ^= bs_p1_xmm[78];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[79] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[79];
//butterfly_w0x10( vec[16:64-79], 0x40 )
temp = bs_p1_xmm[72];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[72] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[73];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[65] ^= temp;
bs_p1_xmm[73] ^= bs_p1_xmm[65];
temp = bs_p1_xmm[74];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[66] ^= temp;
bs_p1_xmm[74] ^= bs_p1_xmm[66];
temp = bs_p1_xmm[75];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[67] ^= temp;
bs_p1_xmm[75] ^= bs_p1_xmm[67];
temp = bs_p1_xmm[76];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[68] ^= temp;
bs_p1_xmm[76] ^= bs_p1_xmm[68];
temp = bs_p1_xmm[77];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[69] ^= temp;
bs_p1_xmm[77] ^= bs_p1_xmm[69];
temp = bs_p1_xmm[78];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[70] ^= temp;
bs_p1_xmm[78] ^= bs_p1_xmm[70];
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[71] ^= temp;
bs_p1_xmm[79] ^= bs_p1_xmm[71];
//butterfly_w0x8( vec[8:64-71], 0x40 )
temp = bs_p1_xmm[68];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[68] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[69];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[65] ^= temp;
bs_p1_xmm[69] ^= bs_p1_xmm[65];
temp = bs_p1_xmm[70];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[66] ^= temp;
bs_p1_xmm[70] ^= bs_p1_xmm[66];
temp = bs_p1_xmm[71];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[67] ^= temp;
bs_p1_xmm[71] ^= bs_p1_xmm[67];
//butterfly_w0x4( vec[4:64-67], 0x40 )
temp = bs_p1_xmm[66];
temp = tbl_gf256_mul_const(0x27,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[66] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[67];
temp = tbl_gf256_mul_const(0x27,temp);
bs_p1_xmm[65] ^= temp;
bs_p1_xmm[67] ^= bs_p1_xmm[65];
//butterfly_w0x2( vec[2:64-65], 0x40 )
temp = bs_p1_xmm[65];
temp = tbl_gf256_mul_const(0x40,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[65] ^= bs_p1_xmm[64];
//butterfly_w0x2( vec[2:66-67], 0x42 )
temp = bs_p1_xmm[67];
temp = tbl_gf256_mul_const(0x42,temp);
bs_p1_xmm[66] ^= temp;
bs_p1_xmm[67] ^= bs_p1_xmm[66];
//butterfly_w0x4( vec[4:68-71], 0x44 )
temp = bs_p1_xmm[70];
temp = tbl_gf256_mul_const(0x25,temp);
bs_p1_xmm[68] ^= temp;
bs_p1_xmm[70] ^= bs_p1_xmm[68];
temp = bs_p1_xmm[71];
temp = tbl_gf256_mul_const(0x25,temp);
bs_p1_xmm[69] ^= temp;
bs_p1_xmm[71] ^= bs_p1_xmm[69];
//butterfly_w0x2( vec[2:68-69], 0x44 )
temp = bs_p1_xmm[69];
temp = tbl_gf256_mul_const(0x44,temp);
bs_p1_xmm[68] ^= temp;
bs_p1_xmm[69] ^= bs_p1_xmm[68];
//butterfly_w0x2( vec[2:70-71], 0x46 )
temp = bs_p1_xmm[71];
temp = tbl_gf256_mul_const(0x46,temp);
bs_p1_xmm[70] ^= temp;
bs_p1_xmm[71] ^= bs_p1_xmm[70];
//butterfly_w0x8( vec[8:72-79], 0x48 )
temp = bs_p1_xmm[76];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[72] ^= temp;
bs_p1_xmm[76] ^= bs_p1_xmm[72];
temp = bs_p1_xmm[77];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[73] ^= temp;
bs_p1_xmm[77] ^= bs_p1_xmm[73];
temp = bs_p1_xmm[78];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[74] ^= temp;
bs_p1_xmm[78] ^= bs_p1_xmm[74];
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[75] ^= temp;
bs_p1_xmm[79] ^= bs_p1_xmm[75];
//butterfly_w0x4( vec[4:72-75], 0x48 )
temp = bs_p1_xmm[74];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[72] ^= temp;
bs_p1_xmm[74] ^= bs_p1_xmm[72];
temp = bs_p1_xmm[75];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[73] ^= temp;
bs_p1_xmm[75] ^= bs_p1_xmm[73];
//butterfly_w0x2( vec[2:72-73], 0x48 )
temp = bs_p1_xmm[73];
temp = tbl_gf256_mul_const(0x48,temp);
bs_p1_xmm[72] ^= temp;
bs_p1_xmm[73] ^= bs_p1_xmm[72];
//butterfly_w0x2( vec[2:74-75], 0x4a )
temp = bs_p1_xmm[75];
temp = tbl_gf256_mul_const(0x4a,temp);
bs_p1_xmm[74] ^= temp;
bs_p1_xmm[75] ^= bs_p1_xmm[74];
//butterfly_w0x4( vec[4:76-79], 0x4c )
temp = bs_p1_xmm[78];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[76] ^= temp;
bs_p1_xmm[78] ^= bs_p1_xmm[76];
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[77] ^= temp;
bs_p1_xmm[79] ^= bs_p1_xmm[77];
//butterfly_w0x2( vec[2:76-77], 0x4c )
temp = bs_p1_xmm[77];
temp = tbl_gf256_mul_const(0x4c,temp);
bs_p1_xmm[76] ^= temp;
bs_p1_xmm[77] ^= bs_p1_xmm[76];
//butterfly_w0x2( vec[2:78-79], 0x4e )
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0x4e,temp);
bs_p1_xmm[78] ^= temp;
bs_p1_xmm[79] ^= bs_p1_xmm[78];
//butterfly_w0x10( vec[16:80-95], 0x50 )
temp = bs_p1_xmm[88];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[80] ^= temp;
bs_p1_xmm[88] ^= bs_p1_xmm[80];
temp = bs_p1_xmm[89];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[81] ^= temp;
bs_p1_xmm[89] ^= bs_p1_xmm[81];
temp = bs_p1_xmm[90];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[82] ^= temp;
bs_p1_xmm[90] ^= bs_p1_xmm[82];
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[83] ^= temp;
bs_p1_xmm[91] ^= bs_p1_xmm[83];
temp = bs_p1_xmm[92];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[84] ^= temp;
bs_p1_xmm[92] ^= bs_p1_xmm[84];
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[85] ^= temp;
bs_p1_xmm[93] ^= bs_p1_xmm[85];
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[86] ^= temp;
bs_p1_xmm[94] ^= bs_p1_xmm[86];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[87] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[87];
//butterfly_w0x8( vec[8:80-87], 0x50 )
temp = bs_p1_xmm[84];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[80] ^= temp;
bs_p1_xmm[84] ^= bs_p1_xmm[80];
temp = bs_p1_xmm[85];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[81] ^= temp;
bs_p1_xmm[85] ^= bs_p1_xmm[81];
temp = bs_p1_xmm[86];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[82] ^= temp;
bs_p1_xmm[86] ^= bs_p1_xmm[82];
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[83] ^= temp;
bs_p1_xmm[87] ^= bs_p1_xmm[83];
//butterfly_w0x4( vec[4:80-83], 0x50 )
temp = bs_p1_xmm[82];
temp = tbl_gf256_mul_const(0x2f,temp);
bs_p1_xmm[80] ^= temp;
bs_p1_xmm[82] ^= bs_p1_xmm[80];
temp = bs_p1_xmm[83];
temp = tbl_gf256_mul_const(0x2f,temp);
bs_p1_xmm[81] ^= temp;
bs_p1_xmm[83] ^= bs_p1_xmm[81];
//butterfly_w0x2( vec[2:80-81], 0x50 )
temp = bs_p1_xmm[81];
temp = tbl_gf256_mul_const(0x50,temp);
bs_p1_xmm[80] ^= temp;
bs_p1_xmm[81] ^= bs_p1_xmm[80];
//butterfly_w0x2( vec[2:82-83], 0x52 )
temp = bs_p1_xmm[83];
temp = tbl_gf256_mul_const(0x52,temp);
bs_p1_xmm[82] ^= temp;
bs_p1_xmm[83] ^= bs_p1_xmm[82];
//butterfly_w0x4( vec[4:84-87], 0x54 )
temp = bs_p1_xmm[86];
temp = tbl_gf256_mul_const(0x2d,temp);
bs_p1_xmm[84] ^= temp;
bs_p1_xmm[86] ^= bs_p1_xmm[84];
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x2d,temp);
bs_p1_xmm[85] ^= temp;
bs_p1_xmm[87] ^= bs_p1_xmm[85];
//butterfly_w0x2( vec[2:84-85], 0x54 )
temp = bs_p1_xmm[85];
temp = tbl_gf256_mul_const(0x54,temp);
bs_p1_xmm[84] ^= temp;
bs_p1_xmm[85] ^= bs_p1_xmm[84];
//butterfly_w0x2( vec[2:86-87], 0x56 )
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x56,temp);
bs_p1_xmm[86] ^= temp;
bs_p1_xmm[87] ^= bs_p1_xmm[86];
//butterfly_w0x8( vec[8:88-95], 0x58 )
temp = bs_p1_xmm[92];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[88] ^= temp;
bs_p1_xmm[92] ^= bs_p1_xmm[88];
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[89] ^= temp;
bs_p1_xmm[93] ^= bs_p1_xmm[89];
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[90] ^= temp;
bs_p1_xmm[94] ^= bs_p1_xmm[90];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[91] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[91];
//butterfly_w0x4( vec[4:88-91], 0x58 )
temp = bs_p1_xmm[90];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[88] ^= temp;
bs_p1_xmm[90] ^= bs_p1_xmm[88];
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[89] ^= temp;
bs_p1_xmm[91] ^= bs_p1_xmm[89];
//butterfly_w0x2( vec[2:88-89], 0x58 )
temp = bs_p1_xmm[89];
temp = tbl_gf256_mul_const(0x58,temp);
bs_p1_xmm[88] ^= temp;
bs_p1_xmm[89] ^= bs_p1_xmm[88];
//butterfly_w0x2( vec[2:90-91], 0x5a )
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x5a,temp);
bs_p1_xmm[90] ^= temp;
bs_p1_xmm[91] ^= bs_p1_xmm[90];
//butterfly_w0x4( vec[4:92-95], 0x5c )
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[92] ^= temp;
bs_p1_xmm[94] ^= bs_p1_xmm[92];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[93] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[93];
//butterfly_w0x2( vec[2:92-93], 0x5c )
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x5c,temp);
bs_p1_xmm[92] ^= temp;
bs_p1_xmm[93] ^= bs_p1_xmm[92];
//butterfly_w0x2( vec[2:94-95], 0x5e )
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x5e,temp);
bs_p1_xmm[94] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[94];
//butterfly_w0x20( vec[32:96-127], 0x60 )
/// interaction with truncated: //bs_p1_xmm[112]:0x1 ,0? False, omit? True
temp = bs_p1_xmm[112];
/// omit x const: //temp:0x6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[112] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[113]:0x1f ,0? False, omit? True
temp = bs_p1_xmm[113];
/// omit x const: //temp:0x64 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
/// truncated: bs_p1_xmm[113] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[114];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
/// truncated: bs_p1_xmm[114] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[115]:0x30 ,0? False, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[99] ^= temp;
/// truncated: bs_p1_xmm[115] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[116];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
/// truncated: bs_p1_xmm[116] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[117]:0x30 ,0? False, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[101] ^= temp;
/// truncated: bs_p1_xmm[117] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[102] ^= temp;
/// truncated: bs_p1_xmm[118] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[119]:0x30 ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[103] ^= temp;
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[103];
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[120];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
/// truncated: bs_p1_xmm[120] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[121]:0x30 ,0? False, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[105] ^= temp;
/// truncated: bs_p1_xmm[121] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[106] ^= temp;
/// truncated: bs_p1_xmm[122] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[123]:0x30 ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[107] ^= temp;
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[107];
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[108] ^= temp;
/// truncated: bs_p1_xmm[124] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[125]:0x30 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[109] ^= temp;
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[109];
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[110] ^= temp;
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[110];
/// interaction with truncated: //bs_p1_xmm[127]:0x30 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[111] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[111];
//butterfly_w0x10( vec[16:96-111], 0x60 )
/// interaction with truncated: //bs_p1_xmm[104]:0x8 ,0? False, omit? True
temp = bs_p1_xmm[104];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[104] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[105]:0xf2 ,0? False, omit? True
temp = bs_p1_xmm[105];
/// omit x const: //temp:0x95 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
/// truncated: bs_p1_xmm[105] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[106]:0x7 ,0? False, omit? True
temp = bs_p1_xmm[106];
/// omit x const: //temp:0xb ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
/// truncated: bs_p1_xmm[106] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[107]:0xfe ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0x96 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[99] ^= temp;
/// truncated: bs_p1_xmm[107] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[108]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[108];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
/// truncated: bs_p1_xmm[108] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[109]:0xf1 ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0x9f ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[101] ^= temp;
/// truncated: bs_p1_xmm[109] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[110]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[102] ^= temp;
/// truncated: bs_p1_xmm[110] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[111]:0xf6 ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0x94 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[103] ^= temp;
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[103];
//butterfly_w0x8( vec[8:96-103], 0x60 )
/// interaction with truncated: //bs_p1_xmm[100]:0xe ,0? False, omit? True
temp = bs_p1_xmm[100];
/// omit x const: //temp:0xe1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[100] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[101]:0x6a ,0? False, omit? True
temp = bs_p1_xmm[101];
/// omit x const: //temp:0x3f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
/// truncated: bs_p1_xmm[101] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[102]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[102];
/// omit x const: //temp:0x3b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
/// truncated: bs_p1_xmm[102] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[103]:0x61 ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x8a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[99] ^= temp;
/// truncated: bs_p1_xmm[103] ^= bs_p1_xmm[99];
//butterfly_w0x4( vec[4:96-99], 0x60 )
/// interaction with truncated: //bs_p1_xmm[98]:0x1f ,0? False, omit? True
temp = bs_p1_xmm[98];
/// omit x const: //temp:0xae ,0? False, omit? True
temp = tbl_gf256_mul_const(0x33,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[98] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[99]:0xe6 ,0? False, omit? True
temp = bs_p1_xmm[99];
/// omit x const: //temp:0xd8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x33,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
/// truncated: bs_p1_xmm[99] ^= bs_p1_xmm[97];
//butterfly_w0x2( vec[2:96-97], 0x60 )
/// interaction with truncated: //bs_p1_xmm[97]:0x6 ,0? False, omit? True
temp = bs_p1_xmm[97];
/// omit x const: //temp:0x50 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x60,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[97] ^= bs_p1_xmm[96];
//butterfly_w0x2( vec[2:98-99], 0x62 )
/// interaction with truncated: //bs_p1_xmm[99]:0xe0 ,0? False, omit? True
temp = bs_p1_xmm[99];
/// omit x const: //temp:0x5c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x62,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
/// truncated: bs_p1_xmm[99] ^= bs_p1_xmm[98];
//butterfly_w0x4( vec[4:100-103], 0x64 )
/// interaction with truncated: //bs_p1_xmm[102]:0x1c ,0? False, omit? True
temp = bs_p1_xmm[102];
/// omit x const: //temp:0xa8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x31,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
/// truncated: bs_p1_xmm[102] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[103]:0x87 ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x2c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x31,temp);
/// truncated: bs_p1_xmm[101] ^= temp;
/// truncated: bs_p1_xmm[103] ^= bs_p1_xmm[101];
//butterfly_w0x2( vec[2:100-101], 0x64 )
/// interaction with truncated: //bs_p1_xmm[101]:0x98 ,0? False, omit? True
temp = bs_p1_xmm[101];
/// omit x const: //temp:0x93 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x64,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
/// truncated: bs_p1_xmm[101] ^= bs_p1_xmm[100];
//butterfly_w0x2( vec[2:102-103], 0x66 )
/// interaction with truncated: //bs_p1_xmm[103]:0x1f ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x43 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x66,temp);
/// truncated: bs_p1_xmm[102] ^= temp;
/// truncated: bs_p1_xmm[103] ^= bs_p1_xmm[102];
//butterfly_w0x8( vec[8:104-111], 0x68 )
/// interaction with truncated: //bs_p1_xmm[108]:0xd ,0? False, omit? True
temp = bs_p1_xmm[108];
/// omit x const: //temp:0xdc ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
/// truncated: bs_p1_xmm[108] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[109]:0x9b ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0xfd ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[105] ^= temp;
/// truncated: bs_p1_xmm[109] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[110]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0x3a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[106] ^= temp;
/// truncated: bs_p1_xmm[110] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[111]:0x97 ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0x3e ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[107] ^= temp;
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[107];
//butterfly_w0x4( vec[4:104-107], 0x68 )
/// interaction with truncated: //bs_p1_xmm[106]:0x19 ,0? False, omit? True
temp = bs_p1_xmm[106];
/// omit x const: //temp:0x25 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x36,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
/// truncated: bs_p1_xmm[106] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[107]:0xac ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0x1a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x36,temp);
/// truncated: bs_p1_xmm[105] ^= temp;
/// truncated: bs_p1_xmm[107] ^= bs_p1_xmm[105];
//butterfly_w0x2( vec[2:104-105], 0x68 )
/// interaction with truncated: //bs_p1_xmm[105]:0xf4 ,0? False, omit? True
temp = bs_p1_xmm[105];
/// omit x const: //temp:0x80 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x68,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
/// truncated: bs_p1_xmm[105] ^= bs_p1_xmm[104];
//butterfly_w0x2( vec[2:106-107], 0x6a )
/// interaction with truncated: //bs_p1_xmm[107]:0x58 ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0x6c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6a,temp);
/// truncated: bs_p1_xmm[106] ^= temp;
/// truncated: bs_p1_xmm[107] ^= bs_p1_xmm[106];
//butterfly_w0x4( vec[4:108-111], 0x6c )
/// interaction with truncated: //bs_p1_xmm[110]:0x1a ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0x27 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x34,temp);
/// truncated: bs_p1_xmm[108] ^= temp;
/// truncated: bs_p1_xmm[110] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[111]:0x3b ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0x8b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x34,temp);
/// truncated: bs_p1_xmm[109] ^= temp;
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[109];
//butterfly_w0x2( vec[2:108-109], 0x6c )
/// interaction with truncated: //bs_p1_xmm[109]:0xfe ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0x54 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6c,temp);
/// truncated: bs_p1_xmm[108] ^= temp;
/// truncated: bs_p1_xmm[109] ^= bs_p1_xmm[108];
//butterfly_w0x2( vec[2:110-111], 0x6e )
/// interaction with truncated: //bs_p1_xmm[111]:0xc5 ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0xee ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6e,temp);
/// truncated: bs_p1_xmm[110] ^= temp;
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[110];
//butterfly_w0x10( vec[16:112-127], 0x70 )
/// interaction with truncated: //bs_p1_xmm[120]:0x8 ,0? False, omit? True
temp = bs_p1_xmm[120];
/// omit x const: //temp:0xe ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
/// truncated: bs_p1_xmm[120] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[121]:0xc2 ,0? False, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0x76 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[113] ^= temp;
/// truncated: bs_p1_xmm[121] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[122]:0x7 ,0? False, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[114] ^= temp;
/// truncated: bs_p1_xmm[122] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[123]:0xce ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0x71 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[115] ^= temp;
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[115];
/// interaction with truncated: //bs_p1_xmm[124]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0xb ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[116] ^= temp;
/// truncated: bs_p1_xmm[124] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[125]:0xc1 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0x7d ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[117] ^= temp;
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[117];
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[118] ^= temp;
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[118];
/// interaction with truncated: //bs_p1_xmm[127]:0xc6 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x7f ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[119] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[119];
//butterfly_w0x8( vec[8:112-119], 0x70 )
/// interaction with truncated: //bs_p1_xmm[116]:0xf ,0? False, omit? True
temp = bs_p1_xmm[116];
/// omit x const: //temp:0xf2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
/// truncated: bs_p1_xmm[116] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[117]:0xb8 ,0? False, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0xa4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[113] ^= temp;
/// truncated: bs_p1_xmm[117] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[118]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0x34 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[114] ^= temp;
/// truncated: bs_p1_xmm[118] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[119]:0xba ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x88 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[115] ^= temp;
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[115];
//butterfly_w0x4( vec[4:112-115], 0x70 )
/// interaction with truncated: //bs_p1_xmm[114]:0x19 ,0? False, omit? True
temp = bs_p1_xmm[114];
/// omit x const: //temp:0xf6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3b,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
/// truncated: bs_p1_xmm[114] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[115]:0x33 ,0? False, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0x6a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3b,temp);
/// truncated: bs_p1_xmm[113] ^= temp;
/// truncated: bs_p1_xmm[115] ^= bs_p1_xmm[113];
//butterfly_w0x2( vec[2:112-113], 0x70 )
/// interaction with truncated: //bs_p1_xmm[113]:0xd3 ,0? False, omit? True
temp = bs_p1_xmm[113];
/// omit x const: //temp:0xcc ,0? False, omit? True
temp = tbl_gf256_mul_const(0x70,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
/// truncated: bs_p1_xmm[113] ^= bs_p1_xmm[112];
//butterfly_w0x2( vec[2:114-115], 0x72 )
/// interaction with truncated: //bs_p1_xmm[115]:0xe0 ,0? False, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0xb6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x72,temp);
/// truncated: bs_p1_xmm[114] ^= temp;
/// truncated: bs_p1_xmm[115] ^= bs_p1_xmm[114];
//butterfly_w0x4( vec[4:116-119], 0x74 )
/// interaction with truncated: //bs_p1_xmm[118]:0x1a ,0? False, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0xff ,0? False, omit? True
temp = tbl_gf256_mul_const(0x39,temp);
/// truncated: bs_p1_xmm[116] ^= temp;
/// truncated: bs_p1_xmm[118] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[119]:0x89 ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x67 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x39,temp);
/// truncated: bs_p1_xmm[117] ^= temp;
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[117];
//butterfly_w0x2( vec[2:116-117], 0x74 )
/// interaction with truncated: //bs_p1_xmm[117]:0x66 ,0? False, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0xea ,0? False, omit? True
temp = tbl_gf256_mul_const(0x74,temp);
/// truncated: bs_p1_xmm[116] ^= temp;
/// truncated: bs_p1_xmm[117] ^= bs_p1_xmm[116];
//butterfly_w0x2( vec[2:118-119], 0x76 )
/// interaction with truncated: //bs_p1_xmm[119]:0xef ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x52 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x76,temp);
/// truncated: bs_p1_xmm[118] ^= temp;
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[118];
//butterfly_w0x8( vec[8:120-127], 0x78 )
/// interaction with truncated: //bs_p1_xmm[124]:0xc ,0? False, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0xc2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[120] ^= temp;
/// truncated: bs_p1_xmm[124] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[125]:0x79 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0x84 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[121] ^= temp;
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[121];
/// interaction with truncated: //bs_p1_xmm[126]:0x3 ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0x35 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[122] ^= temp;
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[122];
/// interaction with truncated: //bs_p1_xmm[127]:0x7c ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0xdd ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[123] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[123];
//butterfly_w0x4( vec[4:120-123], 0x78 )
/// interaction with truncated: //bs_p1_xmm[122]:0x1f ,0? False, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0x72 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3e,temp);
/// truncated: bs_p1_xmm[120] ^= temp;
/// truncated: bs_p1_xmm[122] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[123]:0xa8 ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0xc9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3e,temp);
/// truncated: bs_p1_xmm[121] ^= temp;
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[121];
//butterfly_w0x2( vec[2:120-121], 0x78 )
/// interaction with truncated: //bs_p1_xmm[121]:0x92 ,0? False, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0x41 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x78,temp);
/// truncated: bs_p1_xmm[120] ^= temp;
/// truncated: bs_p1_xmm[121] ^= bs_p1_xmm[120];
//butterfly_w0x2( vec[2:122-123], 0x7a )
/// interaction with truncated: //bs_p1_xmm[123]:0x3a ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0xd4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7a,temp);
/// truncated: bs_p1_xmm[122] ^= temp;
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[122];
//butterfly_w0x4( vec[4:124-127], 0x7c )
/// interaction with truncated: //bs_p1_xmm[126]:0x1c ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0x7f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3c,temp);
/// truncated: bs_p1_xmm[124] ^= temp;
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[124];
/// interaction with truncated: //bs_p1_xmm[127]:0xd4 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3c,temp);
/// truncated: bs_p1_xmm[125] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[125];
//butterfly_w0x2( vec[2:124-125], 0x7c )
/// interaction with truncated: //bs_p1_xmm[125]:0x26 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0xec ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7c,temp);
/// truncated: bs_p1_xmm[124] ^= temp;
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[124];
//butterfly_w0x2( vec[2:126-127], 0x7e )
/// interaction with truncated: //bs_p1_xmm[127]:0xf2 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x4e ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7e,temp);
/// truncated: bs_p1_xmm[126] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[126];
//butterfly_w0x80( vec[128:0-127], 0x0 )
bs_p2_xmm[64] = bs_p2_xmm[0];
bs_p2_xmm[65] = bs_p2_xmm[1];
bs_p2_xmm[66] = bs_p2_xmm[2];
bs_p2_xmm[67] = bs_p2_xmm[3];
bs_p2_xmm[68] = bs_p2_xmm[4];
bs_p2_xmm[69] = bs_p2_xmm[5];
bs_p2_xmm[70] = bs_p2_xmm[6];
bs_p2_xmm[71] = bs_p2_xmm[7];
bs_p2_xmm[72] = bs_p2_xmm[8];
bs_p2_xmm[73] = bs_p2_xmm[9];
bs_p2_xmm[74] = bs_p2_xmm[10];
bs_p2_xmm[75] = bs_p2_xmm[11];
bs_p2_xmm[76] = bs_p2_xmm[12];
bs_p2_xmm[77] = bs_p2_xmm[13];
bs_p2_xmm[78] = bs_p2_xmm[14];
bs_p2_xmm[79] = bs_p2_xmm[15];
bs_p2_xmm[80] = bs_p2_xmm[16];
bs_p2_xmm[81] = bs_p2_xmm[17];
bs_p2_xmm[82] = bs_p2_xmm[18];
bs_p2_xmm[83] = bs_p2_xmm[19];
bs_p2_xmm[84] = bs_p2_xmm[20];
bs_p2_xmm[85] = bs_p2_xmm[21];
bs_p2_xmm[86] = bs_p2_xmm[22];
bs_p2_xmm[87] = bs_p2_xmm[23];
bs_p2_xmm[88] = bs_p2_xmm[24];
bs_p2_xmm[89] = bs_p2_xmm[25];
bs_p2_xmm[90] = bs_p2_xmm[26];
bs_p2_xmm[91] = bs_p2_xmm[27];
bs_p2_xmm[92] = bs_p2_xmm[28];
bs_p2_xmm[93] = bs_p2_xmm[29];
bs_p2_xmm[94] = bs_p2_xmm[30];
bs_p2_xmm[95] = bs_p2_xmm[31];
/// interaction with truncated: //bs_p2_xmm[96]:0x20 ,0? True, omit? True
bs_p2_xmm[96] = bs_p2_xmm[32];
/// interaction with truncated: //bs_p2_xmm[97]:0x20 ,0? True, omit? True
bs_p2_xmm[97] = bs_p2_xmm[33];
/// interaction with truncated: //bs_p2_xmm[98]:0x5 ,0? True, omit? True
bs_p2_xmm[98] = bs_p2_xmm[34];
/// interaction with truncated: //bs_p2_xmm[99]:0x2f ,0? True, omit? True
bs_p2_xmm[99] = bs_p2_xmm[35];
/// interaction with truncated: //bs_p2_xmm[100]:0x1 ,0? True, omit? True
bs_p2_xmm[100] = bs_p2_xmm[36];
/// interaction with truncated: //bs_p2_xmm[101]:0x25 ,0? True, omit? True
bs_p2_xmm[101] = bs_p2_xmm[37];
/// interaction with truncated: //bs_p2_xmm[102]:0x3 ,0? True, omit? True
bs_p2_xmm[102] = bs_p2_xmm[38];
/// interaction with truncated: //bs_p2_xmm[103]:0x20 ,0? True, omit? True
bs_p2_xmm[103] = bs_p2_xmm[39];
/// interaction with truncated: //bs_p2_xmm[104]:0x5 ,0? True, omit? True
bs_p2_xmm[104] = bs_p2_xmm[40];
/// interaction with truncated: //bs_p2_xmm[105]:0x2b ,0? True, omit? True
bs_p2_xmm[105] = bs_p2_xmm[41];
/// interaction with truncated: //bs_p2_xmm[106]:0x3 ,0? True, omit? True
bs_p2_xmm[106] = bs_p2_xmm[42];
/// interaction with truncated: //bs_p2_xmm[107]:0x2a ,0? True, omit? True
bs_p2_xmm[107] = bs_p2_xmm[43];
/// interaction with truncated: //bs_p2_xmm[108]:0x3 ,0? True, omit? True
bs_p2_xmm[108] = bs_p2_xmm[44];
/// interaction with truncated: //bs_p2_xmm[109]:0x2c ,0? True, omit? True
bs_p2_xmm[109] = bs_p2_xmm[45];
/// interaction with truncated: //bs_p2_xmm[110]:0x1 ,0? True, omit? True
bs_p2_xmm[110] = bs_p2_xmm[46];
/// interaction with truncated: //bs_p2_xmm[111]:0x2f ,0? True, omit? True
bs_p2_xmm[111] = bs_p2_xmm[47];
/// interaction with truncated: //bs_p2_xmm[112]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[112] = bs_p2_xmm[48];
/// interaction with truncated: //bs_p2_xmm[113]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[113] = bs_p2_xmm[49];
/// interaction with truncated: //bs_p2_xmm[114]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[114] = bs_p2_xmm[50];
/// interaction with truncated: //bs_p2_xmm[115]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[115] = bs_p2_xmm[51];
/// interaction with truncated: //bs_p2_xmm[116]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[116] = bs_p2_xmm[52];
/// interaction with truncated: //bs_p2_xmm[117]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[117] = bs_p2_xmm[53];
/// interaction with truncated: //bs_p2_xmm[118]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[118] = bs_p2_xmm[54];
/// interaction with truncated: //bs_p2_xmm[119]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[119] = bs_p2_xmm[55];
/// interaction with truncated: //bs_p2_xmm[120]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[120] = bs_p2_xmm[56];
/// interaction with truncated: //bs_p2_xmm[121]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[121] = bs_p2_xmm[57];
/// interaction with truncated: //bs_p2_xmm[122]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[122] = bs_p2_xmm[58];
/// interaction with truncated: //bs_p2_xmm[123]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[123] = bs_p2_xmm[59];
/// interaction with truncated: //bs_p2_xmm[124]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[124] = bs_p2_xmm[60];
/// interaction with truncated: //bs_p2_xmm[125]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[125] = bs_p2_xmm[61];
/// interaction with truncated: //bs_p2_xmm[126]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[126] = bs_p2_xmm[62];
/// interaction with truncated: //bs_p2_xmm[127]:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[127] = bs_p2_xmm[63];
//butterfly_w0x40( vec[64:0-63], 0x0 )
bs_p2_xmm[32] ^= bs_p2_xmm[0];
bs_p2_xmm[33] ^= bs_p2_xmm[1];
bs_p2_xmm[34] ^= bs_p2_xmm[2];
bs_p2_xmm[35] ^= bs_p2_xmm[3];
bs_p2_xmm[36] ^= bs_p2_xmm[4];
bs_p2_xmm[37] ^= bs_p2_xmm[5];
bs_p2_xmm[38] ^= bs_p2_xmm[6];
bs_p2_xmm[39] ^= bs_p2_xmm[7];
bs_p2_xmm[40] ^= bs_p2_xmm[8];
bs_p2_xmm[41] ^= bs_p2_xmm[9];
bs_p2_xmm[42] ^= bs_p2_xmm[10];
bs_p2_xmm[43] ^= bs_p2_xmm[11];
bs_p2_xmm[44] ^= bs_p2_xmm[12];
bs_p2_xmm[45] ^= bs_p2_xmm[13];
bs_p2_xmm[46] ^= bs_p2_xmm[14];
bs_p2_xmm[47] ^= bs_p2_xmm[15];
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
//butterfly_w0x20( vec[32:0-31], 0x0 )
bs_p2_xmm[16] ^= bs_p2_xmm[0];
bs_p2_xmm[17] ^= bs_p2_xmm[1];
bs_p2_xmm[18] ^= bs_p2_xmm[2];
bs_p2_xmm[19] ^= bs_p2_xmm[3];
bs_p2_xmm[20] ^= bs_p2_xmm[4];
bs_p2_xmm[21] ^= bs_p2_xmm[5];
bs_p2_xmm[22] ^= bs_p2_xmm[6];
bs_p2_xmm[23] ^= bs_p2_xmm[7];
bs_p2_xmm[24] ^= bs_p2_xmm[8];
bs_p2_xmm[25] ^= bs_p2_xmm[9];
bs_p2_xmm[26] ^= bs_p2_xmm[10];
bs_p2_xmm[27] ^= bs_p2_xmm[11];
bs_p2_xmm[28] ^= bs_p2_xmm[12];
bs_p2_xmm[29] ^= bs_p2_xmm[13];
bs_p2_xmm[30] ^= bs_p2_xmm[14];
bs_p2_xmm[31] ^= bs_p2_xmm[15];
//butterfly_w0x10( vec[16:0-15], 0x0 )
bs_p2_xmm[8] ^= bs_p2_xmm[0];
bs_p2_xmm[9] ^= bs_p2_xmm[1];
bs_p2_xmm[10] ^= bs_p2_xmm[2];
bs_p2_xmm[11] ^= bs_p2_xmm[3];
bs_p2_xmm[12] ^= bs_p2_xmm[4];
bs_p2_xmm[13] ^= bs_p2_xmm[5];
bs_p2_xmm[14] ^= bs_p2_xmm[6];
bs_p2_xmm[15] ^= bs_p2_xmm[7];
//butterfly_w0x8( vec[8:0-7], 0x0 )
bs_p2_xmm[4] ^= bs_p2_xmm[0];
bs_p2_xmm[5] ^= bs_p2_xmm[1];
bs_p2_xmm[6] ^= bs_p2_xmm[2];
bs_p2_xmm[7] ^= bs_p2_xmm[3];
//butterfly_w0x4( vec[4:0-3], 0x0 )
bs_p2_xmm[2] ^= bs_p2_xmm[0];
bs_p2_xmm[3] ^= bs_p2_xmm[1];
//butterfly_w0x2( vec[2:0-1], 0x0 )
bs_p2_xmm[1] ^= bs_p2_xmm[0];
//butterfly_w0x2( vec[2:2-3], 0x2 )
temp = bs_p2_xmm[3];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[2] ^= temp;
bs_p2_xmm[3] ^= bs_p2_xmm[2];
//butterfly_w0x4( vec[4:4-7], 0x4 )
temp = bs_p2_xmm[6];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[4] ^= temp;
bs_p2_xmm[6] ^= bs_p2_xmm[4];
temp = bs_p2_xmm[7];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[5] ^= temp;
bs_p2_xmm[7] ^= bs_p2_xmm[5];
//butterfly_w0x2( vec[2:4-5], 0x4 )
temp = bs_p2_xmm[5];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[4] ^= temp;
bs_p2_xmm[5] ^= bs_p2_xmm[4];
//butterfly_w0x2( vec[2:6-7], 0x6 )
temp = bs_p2_xmm[7];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[6] ^= temp;
bs_p2_xmm[7] ^= bs_p2_xmm[6];
//butterfly_w0x8( vec[8:8-15], 0x8 )
temp = bs_p2_xmm[12];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[8] ^= temp;
bs_p2_xmm[12] ^= bs_p2_xmm[8];
temp = bs_p2_xmm[13];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[9] ^= temp;
bs_p2_xmm[13] ^= bs_p2_xmm[9];
temp = bs_p2_xmm[14];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[10] ^= temp;
bs_p2_xmm[14] ^= bs_p2_xmm[10];
temp = bs_p2_xmm[15];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[11] ^= temp;
bs_p2_xmm[15] ^= bs_p2_xmm[11];
//butterfly_w0x4( vec[4:8-11], 0x8 )
temp = bs_p2_xmm[10];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[8] ^= temp;
bs_p2_xmm[10] ^= bs_p2_xmm[8];
temp = bs_p2_xmm[11];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[9] ^= temp;
bs_p2_xmm[11] ^= bs_p2_xmm[9];
//butterfly_w0x2( vec[2:8-9], 0x8 )
temp = bs_p2_xmm[9];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[8] ^= temp;
bs_p2_xmm[9] ^= bs_p2_xmm[8];
//butterfly_w0x2( vec[2:10-11], 0xa )
temp = bs_p2_xmm[11];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[10] ^= temp;
bs_p2_xmm[11] ^= bs_p2_xmm[10];
//butterfly_w0x4( vec[4:12-15], 0xc )
temp = bs_p2_xmm[14];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[12] ^= temp;
bs_p2_xmm[14] ^= bs_p2_xmm[12];
temp = bs_p2_xmm[15];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[13] ^= temp;
bs_p2_xmm[15] ^= bs_p2_xmm[13];
//butterfly_w0x2( vec[2:12-13], 0xc )
temp = bs_p2_xmm[13];
temp = tbl_gf256_mul_const(0xc,temp);
bs_p2_xmm[12] ^= temp;
bs_p2_xmm[13] ^= bs_p2_xmm[12];
//butterfly_w0x2( vec[2:14-15], 0xe )
temp = bs_p2_xmm[15];
temp = tbl_gf256_mul_const(0xe,temp);
bs_p2_xmm[14] ^= temp;
bs_p2_xmm[15] ^= bs_p2_xmm[14];
//butterfly_w0x10( vec[16:16-31], 0x10 )
temp = bs_p2_xmm[24];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[16] ^= temp;
bs_p2_xmm[24] ^= bs_p2_xmm[16];
temp = bs_p2_xmm[25];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[17] ^= temp;
bs_p2_xmm[25] ^= bs_p2_xmm[17];
temp = bs_p2_xmm[26];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[18] ^= temp;
bs_p2_xmm[26] ^= bs_p2_xmm[18];
temp = bs_p2_xmm[27];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[19] ^= temp;
bs_p2_xmm[27] ^= bs_p2_xmm[19];
temp = bs_p2_xmm[28];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[20] ^= temp;
bs_p2_xmm[28] ^= bs_p2_xmm[20];
temp = bs_p2_xmm[29];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[21] ^= temp;
bs_p2_xmm[29] ^= bs_p2_xmm[21];
temp = bs_p2_xmm[30];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[22] ^= temp;
bs_p2_xmm[30] ^= bs_p2_xmm[22];
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[23] ^= temp;
bs_p2_xmm[31] ^= bs_p2_xmm[23];
//butterfly_w0x8( vec[8:16-23], 0x10 )
temp = bs_p2_xmm[20];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[16] ^= temp;
bs_p2_xmm[20] ^= bs_p2_xmm[16];
temp = bs_p2_xmm[21];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[17] ^= temp;
bs_p2_xmm[21] ^= bs_p2_xmm[17];
temp = bs_p2_xmm[22];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[18] ^= temp;
bs_p2_xmm[22] ^= bs_p2_xmm[18];
temp = bs_p2_xmm[23];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p2_xmm[19] ^= temp;
bs_p2_xmm[23] ^= bs_p2_xmm[19];
//butterfly_w0x4( vec[4:16-19], 0x10 )
temp = bs_p2_xmm[18];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[16] ^= temp;
bs_p2_xmm[18] ^= bs_p2_xmm[16];
temp = bs_p2_xmm[19];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[17] ^= temp;
bs_p2_xmm[19] ^= bs_p2_xmm[17];
//butterfly_w0x2( vec[2:16-17], 0x10 )
temp = bs_p2_xmm[17];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p2_xmm[16] ^= temp;
bs_p2_xmm[17] ^= bs_p2_xmm[16];
//butterfly_w0x2( vec[2:18-19], 0x12 )
temp = bs_p2_xmm[19];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p2_xmm[18] ^= temp;
bs_p2_xmm[19] ^= bs_p2_xmm[18];
//butterfly_w0x4( vec[4:20-23], 0x14 )
temp = bs_p2_xmm[22];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[20] ^= temp;
bs_p2_xmm[22] ^= bs_p2_xmm[20];
temp = bs_p2_xmm[23];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[21] ^= temp;
bs_p2_xmm[23] ^= bs_p2_xmm[21];
//butterfly_w0x2( vec[2:20-21], 0x14 )
temp = bs_p2_xmm[21];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p2_xmm[20] ^= temp;
bs_p2_xmm[21] ^= bs_p2_xmm[20];
//butterfly_w0x2( vec[2:22-23], 0x16 )
temp = bs_p2_xmm[23];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p2_xmm[22] ^= temp;
bs_p2_xmm[23] ^= bs_p2_xmm[22];
//butterfly_w0x8( vec[8:24-31], 0x18 )
temp = bs_p2_xmm[28];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[24] ^= temp;
bs_p2_xmm[28] ^= bs_p2_xmm[24];
temp = bs_p2_xmm[29];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[25] ^= temp;
bs_p2_xmm[29] ^= bs_p2_xmm[25];
temp = bs_p2_xmm[30];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[26] ^= temp;
bs_p2_xmm[30] ^= bs_p2_xmm[26];
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p2_xmm[27] ^= temp;
bs_p2_xmm[31] ^= bs_p2_xmm[27];
//butterfly_w0x4( vec[4:24-27], 0x18 )
temp = bs_p2_xmm[26];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[24] ^= temp;
bs_p2_xmm[26] ^= bs_p2_xmm[24];
temp = bs_p2_xmm[27];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[25] ^= temp;
bs_p2_xmm[27] ^= bs_p2_xmm[25];
//butterfly_w0x2( vec[2:24-25], 0x18 )
temp = bs_p2_xmm[25];
temp = tbl_gf256_mul_const(0x18,temp);
bs_p2_xmm[24] ^= temp;
bs_p2_xmm[25] ^= bs_p2_xmm[24];
//butterfly_w0x2( vec[2:26-27], 0x1a )
temp = bs_p2_xmm[27];
temp = tbl_gf256_mul_const(0x1a,temp);
bs_p2_xmm[26] ^= temp;
bs_p2_xmm[27] ^= bs_p2_xmm[26];
//butterfly_w0x4( vec[4:28-31], 0x1c )
temp = bs_p2_xmm[30];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[28] ^= temp;
bs_p2_xmm[30] ^= bs_p2_xmm[28];
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[29] ^= temp;
bs_p2_xmm[31] ^= bs_p2_xmm[29];
//butterfly_w0x2( vec[2:28-29], 0x1c )
temp = bs_p2_xmm[29];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p2_xmm[28] ^= temp;
bs_p2_xmm[29] ^= bs_p2_xmm[28];
//butterfly_w0x2( vec[2:30-31], 0x1e )
temp = bs_p2_xmm[31];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p2_xmm[30] ^= temp;
bs_p2_xmm[31] ^= bs_p2_xmm[30];
//butterfly_w0x20( vec[32:32-63], 0x20 )
temp = bs_p2_xmm[48];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[32] ^= temp;
bs_p2_xmm[48] ^= bs_p2_xmm[32];
temp = bs_p2_xmm[49];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[33] ^= temp;
bs_p2_xmm[49] ^= bs_p2_xmm[33];
temp = bs_p2_xmm[50];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[34] ^= temp;
bs_p2_xmm[50] ^= bs_p2_xmm[34];
temp = bs_p2_xmm[51];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[35] ^= temp;
bs_p2_xmm[51] ^= bs_p2_xmm[35];
temp = bs_p2_xmm[52];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[36] ^= temp;
bs_p2_xmm[52] ^= bs_p2_xmm[36];
temp = bs_p2_xmm[53];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[37] ^= temp;
bs_p2_xmm[53] ^= bs_p2_xmm[37];
temp = bs_p2_xmm[54];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[38] ^= temp;
bs_p2_xmm[54] ^= bs_p2_xmm[38];
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[39] ^= temp;
bs_p2_xmm[55] ^= bs_p2_xmm[39];
temp = bs_p2_xmm[56];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[40] ^= temp;
bs_p2_xmm[56] ^= bs_p2_xmm[40];
temp = bs_p2_xmm[57];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[41] ^= temp;
bs_p2_xmm[57] ^= bs_p2_xmm[41];
temp = bs_p2_xmm[58];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[42] ^= temp;
bs_p2_xmm[58] ^= bs_p2_xmm[42];
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[43] ^= temp;
bs_p2_xmm[59] ^= bs_p2_xmm[43];
temp = bs_p2_xmm[60];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[44] ^= temp;
bs_p2_xmm[60] ^= bs_p2_xmm[44];
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[45] ^= temp;
bs_p2_xmm[61] ^= bs_p2_xmm[45];
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[46] ^= temp;
bs_p2_xmm[62] ^= bs_p2_xmm[46];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p2_xmm[47] ^= temp;
bs_p2_xmm[63] ^= bs_p2_xmm[47];
//butterfly_w0x10( vec[16:32-47], 0x20 )
temp = bs_p2_xmm[40];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[32] ^= temp;
bs_p2_xmm[40] ^= bs_p2_xmm[32];
temp = bs_p2_xmm[41];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[33] ^= temp;
bs_p2_xmm[41] ^= bs_p2_xmm[33];
temp = bs_p2_xmm[42];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[34] ^= temp;
bs_p2_xmm[42] ^= bs_p2_xmm[34];
temp = bs_p2_xmm[43];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[35] ^= temp;
bs_p2_xmm[43] ^= bs_p2_xmm[35];
temp = bs_p2_xmm[44];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[36] ^= temp;
bs_p2_xmm[44] ^= bs_p2_xmm[36];
temp = bs_p2_xmm[45];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[37] ^= temp;
bs_p2_xmm[45] ^= bs_p2_xmm[37];
temp = bs_p2_xmm[46];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[38] ^= temp;
bs_p2_xmm[46] ^= bs_p2_xmm[38];
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[39] ^= temp;
bs_p2_xmm[47] ^= bs_p2_xmm[39];
//butterfly_w0x8( vec[8:32-39], 0x20 )
temp = bs_p2_xmm[36];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[32] ^= temp;
bs_p2_xmm[36] ^= bs_p2_xmm[32];
temp = bs_p2_xmm[37];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[33] ^= temp;
bs_p2_xmm[37] ^= bs_p2_xmm[33];
temp = bs_p2_xmm[38];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[34] ^= temp;
bs_p2_xmm[38] ^= bs_p2_xmm[34];
temp = bs_p2_xmm[39];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p2_xmm[35] ^= temp;
bs_p2_xmm[39] ^= bs_p2_xmm[35];
//butterfly_w0x4( vec[4:32-35], 0x20 )
temp = bs_p2_xmm[34];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p2_xmm[32] ^= temp;
bs_p2_xmm[34] ^= bs_p2_xmm[32];
temp = bs_p2_xmm[35];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p2_xmm[33] ^= temp;
bs_p2_xmm[35] ^= bs_p2_xmm[33];
//butterfly_w0x2( vec[2:32-33], 0x20 )
temp = bs_p2_xmm[33];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p2_xmm[32] ^= temp;
bs_p2_xmm[33] ^= bs_p2_xmm[32];
//butterfly_w0x2( vec[2:34-35], 0x22 )
temp = bs_p2_xmm[35];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p2_xmm[34] ^= temp;
bs_p2_xmm[35] ^= bs_p2_xmm[34];
//butterfly_w0x4( vec[4:36-39], 0x24 )
temp = bs_p2_xmm[38];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p2_xmm[36] ^= temp;
bs_p2_xmm[38] ^= bs_p2_xmm[36];
temp = bs_p2_xmm[39];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p2_xmm[37] ^= temp;
bs_p2_xmm[39] ^= bs_p2_xmm[37];
//butterfly_w0x2( vec[2:36-37], 0x24 )
temp = bs_p2_xmm[37];
temp = tbl_gf256_mul_const(0x24,temp);
bs_p2_xmm[36] ^= temp;
bs_p2_xmm[37] ^= bs_p2_xmm[36];
//butterfly_w0x2( vec[2:38-39], 0x26 )
temp = bs_p2_xmm[39];
temp = tbl_gf256_mul_const(0x26,temp);
bs_p2_xmm[38] ^= temp;
bs_p2_xmm[39] ^= bs_p2_xmm[38];
//butterfly_w0x8( vec[8:40-47], 0x28 )
temp = bs_p2_xmm[44];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[40] ^= temp;
bs_p2_xmm[44] ^= bs_p2_xmm[40];
temp = bs_p2_xmm[45];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[41] ^= temp;
bs_p2_xmm[45] ^= bs_p2_xmm[41];
temp = bs_p2_xmm[46];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[42] ^= temp;
bs_p2_xmm[46] ^= bs_p2_xmm[42];
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p2_xmm[43] ^= temp;
bs_p2_xmm[47] ^= bs_p2_xmm[43];
//butterfly_w0x4( vec[4:40-43], 0x28 )
temp = bs_p2_xmm[42];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p2_xmm[40] ^= temp;
bs_p2_xmm[42] ^= bs_p2_xmm[40];
temp = bs_p2_xmm[43];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p2_xmm[41] ^= temp;
bs_p2_xmm[43] ^= bs_p2_xmm[41];
//butterfly_w0x2( vec[2:40-41], 0x28 )
temp = bs_p2_xmm[41];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p2_xmm[40] ^= temp;
bs_p2_xmm[41] ^= bs_p2_xmm[40];
//butterfly_w0x2( vec[2:42-43], 0x2a )
temp = bs_p2_xmm[43];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p2_xmm[42] ^= temp;
bs_p2_xmm[43] ^= bs_p2_xmm[42];
//butterfly_w0x4( vec[4:44-47], 0x2c )
temp = bs_p2_xmm[46];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p2_xmm[44] ^= temp;
bs_p2_xmm[46] ^= bs_p2_xmm[44];
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p2_xmm[45] ^= temp;
bs_p2_xmm[47] ^= bs_p2_xmm[45];
//butterfly_w0x2( vec[2:44-45], 0x2c )
temp = bs_p2_xmm[45];
temp = tbl_gf256_mul_const(0x2c,temp);
bs_p2_xmm[44] ^= temp;
bs_p2_xmm[45] ^= bs_p2_xmm[44];
//butterfly_w0x2( vec[2:46-47], 0x2e )
temp = bs_p2_xmm[47];
temp = tbl_gf256_mul_const(0x2e,temp);
bs_p2_xmm[46] ^= temp;
bs_p2_xmm[47] ^= bs_p2_xmm[46];
//butterfly_w0x10( vec[16:48-63], 0x30 )
temp = bs_p2_xmm[56];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[48] ^= temp;
bs_p2_xmm[56] ^= bs_p2_xmm[48];
temp = bs_p2_xmm[57];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[49] ^= temp;
bs_p2_xmm[57] ^= bs_p2_xmm[49];
temp = bs_p2_xmm[58];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[50] ^= temp;
bs_p2_xmm[58] ^= bs_p2_xmm[50];
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[51] ^= temp;
bs_p2_xmm[59] ^= bs_p2_xmm[51];
temp = bs_p2_xmm[60];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[52] ^= temp;
bs_p2_xmm[60] ^= bs_p2_xmm[52];
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[53] ^= temp;
bs_p2_xmm[61] ^= bs_p2_xmm[53];
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[54] ^= temp;
bs_p2_xmm[62] ^= bs_p2_xmm[54];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p2_xmm[55] ^= temp;
bs_p2_xmm[63] ^= bs_p2_xmm[55];
//butterfly_w0x8( vec[8:48-55], 0x30 )
temp = bs_p2_xmm[52];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[48] ^= temp;
bs_p2_xmm[52] ^= bs_p2_xmm[48];
temp = bs_p2_xmm[53];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[49] ^= temp;
bs_p2_xmm[53] ^= bs_p2_xmm[49];
temp = bs_p2_xmm[54];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[50] ^= temp;
bs_p2_xmm[54] ^= bs_p2_xmm[50];
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p2_xmm[51] ^= temp;
bs_p2_xmm[55] ^= bs_p2_xmm[51];
//butterfly_w0x4( vec[4:48-51], 0x30 )
temp = bs_p2_xmm[50];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p2_xmm[48] ^= temp;
bs_p2_xmm[50] ^= bs_p2_xmm[48];
temp = bs_p2_xmm[51];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p2_xmm[49] ^= temp;
bs_p2_xmm[51] ^= bs_p2_xmm[49];
//butterfly_w0x2( vec[2:48-49], 0x30 )
temp = bs_p2_xmm[49];
temp = tbl_gf256_mul_const(0x30,temp);
bs_p2_xmm[48] ^= temp;
bs_p2_xmm[49] ^= bs_p2_xmm[48];
//butterfly_w0x2( vec[2:50-51], 0x32 )
temp = bs_p2_xmm[51];
temp = tbl_gf256_mul_const(0x32,temp);
bs_p2_xmm[50] ^= temp;
bs_p2_xmm[51] ^= bs_p2_xmm[50];
//butterfly_w0x4( vec[4:52-55], 0x34 )
temp = bs_p2_xmm[54];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p2_xmm[52] ^= temp;
bs_p2_xmm[54] ^= bs_p2_xmm[52];
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p2_xmm[53] ^= temp;
bs_p2_xmm[55] ^= bs_p2_xmm[53];
//butterfly_w0x2( vec[2:52-53], 0x34 )
temp = bs_p2_xmm[53];
temp = tbl_gf256_mul_const(0x34,temp);
bs_p2_xmm[52] ^= temp;
bs_p2_xmm[53] ^= bs_p2_xmm[52];
//butterfly_w0x2( vec[2:54-55], 0x36 )
temp = bs_p2_xmm[55];
temp = tbl_gf256_mul_const(0x36,temp);
bs_p2_xmm[54] ^= temp;
bs_p2_xmm[55] ^= bs_p2_xmm[54];
//butterfly_w0x8( vec[8:56-63], 0x38 )
temp = bs_p2_xmm[60];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[56] ^= temp;
bs_p2_xmm[60] ^= bs_p2_xmm[56];
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[57] ^= temp;
bs_p2_xmm[61] ^= bs_p2_xmm[57];
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[58] ^= temp;
bs_p2_xmm[62] ^= bs_p2_xmm[58];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p2_xmm[59] ^= temp;
bs_p2_xmm[63] ^= bs_p2_xmm[59];
//butterfly_w0x4( vec[4:56-59], 0x38 )
temp = bs_p2_xmm[58];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p2_xmm[56] ^= temp;
bs_p2_xmm[58] ^= bs_p2_xmm[56];
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p2_xmm[57] ^= temp;
bs_p2_xmm[59] ^= bs_p2_xmm[57];
//butterfly_w0x2( vec[2:56-57], 0x38 )
temp = bs_p2_xmm[57];
temp = tbl_gf256_mul_const(0x38,temp);
bs_p2_xmm[56] ^= temp;
bs_p2_xmm[57] ^= bs_p2_xmm[56];
//butterfly_w0x2( vec[2:58-59], 0x3a )
temp = bs_p2_xmm[59];
temp = tbl_gf256_mul_const(0x3a,temp);
bs_p2_xmm[58] ^= temp;
bs_p2_xmm[59] ^= bs_p2_xmm[58];
//butterfly_w0x4( vec[4:60-63], 0x3c )
temp = bs_p2_xmm[62];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p2_xmm[60] ^= temp;
bs_p2_xmm[62] ^= bs_p2_xmm[60];
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p2_xmm[61] ^= temp;
bs_p2_xmm[63] ^= bs_p2_xmm[61];
//butterfly_w0x2( vec[2:60-61], 0x3c )
temp = bs_p2_xmm[61];
temp = tbl_gf256_mul_const(0x3c,temp);
bs_p2_xmm[60] ^= temp;
bs_p2_xmm[61] ^= bs_p2_xmm[60];
//butterfly_w0x2( vec[2:62-63], 0x3e )
temp = bs_p2_xmm[63];
temp = tbl_gf256_mul_const(0x3e,temp);
bs_p2_xmm[62] ^= temp;
bs_p2_xmm[63] ^= bs_p2_xmm[62];
//butterfly_w0x40( vec[64:64-127], 0x40 )
/// interaction with truncated: //bs_p2_xmm[96]:0x20 ,0? False, omit? True
temp = bs_p2_xmm[96];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p2_xmm[64] ^= temp;
/// interaction with truncated: //bs_p2_xmm[96]:0x10 ,0? False, omit? True
bs_p2_xmm[96] ^= bs_p2_xmm[64];
/// interaction with truncated: //bs_p2_xmm[97]:0x20 ,0? False, omit? True
temp = bs_p2_xmm[97];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p2_xmm[65] ^= temp;
/// interaction with truncated: //bs_p2_xmm[97]:0x10 ,0? False, omit? True
bs_p2_xmm[97] ^= bs_p2_xmm[65];
/// interaction with truncated: //bs_p2_xmm[98]:0x5 ,0? False, omit? True
temp = bs_p2_xmm[98];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0xa ,0? False, omit? True
bs_p2_xmm[66] ^= temp;
/// interaction with truncated: //bs_p2_xmm[98]:0x2f ,0? False, omit? True
bs_p2_xmm[98] ^= bs_p2_xmm[66];
/// interaction with truncated: //bs_p2_xmm[99]:0x2f ,0? False, omit? True
temp = bs_p2_xmm[99];
/// omit x const: //temp:0x35 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x35 ,0? False, omit? True
bs_p2_xmm[67] ^= temp;
/// interaction with truncated: //bs_p2_xmm[99]:0x2a ,0? False, omit? True
bs_p2_xmm[99] ^= bs_p2_xmm[67];
/// interaction with truncated: //bs_p2_xmm[100]:0x1 ,0? False, omit? True
temp = bs_p2_xmm[100];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2 ,0? False, omit? True
bs_p2_xmm[68] ^= temp;
/// interaction with truncated: //bs_p2_xmm[100]:0x4 ,0? False, omit? True
bs_p2_xmm[100] ^= bs_p2_xmm[68];
/// interaction with truncated: //bs_p2_xmm[101]:0x25 ,0? False, omit? True
temp = bs_p2_xmm[101];
/// omit x const: //temp:0x3a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x3a ,0? False, omit? True
bs_p2_xmm[69] ^= temp;
/// interaction with truncated: //bs_p2_xmm[101]:0x25 ,0? False, omit? True
bs_p2_xmm[101] ^= bs_p2_xmm[69];
/// interaction with truncated: //bs_p2_xmm[102]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[102];
/// omit x const: //temp:0x1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x1 ,0? False, omit? True
bs_p2_xmm[70] ^= temp;
/// interaction with truncated: //bs_p2_xmm[102]:0x3 ,0? False, omit? True
bs_p2_xmm[102] ^= bs_p2_xmm[70];
/// interaction with truncated: //bs_p2_xmm[103]:0x20 ,0? False, omit? True
temp = bs_p2_xmm[103];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p2_xmm[71] ^= temp;
/// interaction with truncated: //bs_p2_xmm[103]:0x25 ,0? False, omit? True
bs_p2_xmm[103] ^= bs_p2_xmm[71];
/// interaction with truncated: //bs_p2_xmm[104]:0x5 ,0? False, omit? True
temp = bs_p2_xmm[104];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0xa ,0? False, omit? True
bs_p2_xmm[72] ^= temp;
/// interaction with truncated: //bs_p2_xmm[104]:0x8 ,0? False, omit? True
bs_p2_xmm[104] ^= bs_p2_xmm[72];
/// interaction with truncated: //bs_p2_xmm[105]:0x2b ,0? False, omit? True
temp = bs_p2_xmm[105];
/// omit x const: //temp:0x3d ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x3d ,0? False, omit? True
bs_p2_xmm[73] ^= temp;
/// interaction with truncated: //bs_p2_xmm[105]:0x22 ,0? False, omit? True
bs_p2_xmm[105] ^= bs_p2_xmm[73];
/// interaction with truncated: //bs_p2_xmm[106]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[106];
/// omit x const: //temp:0x1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x1 ,0? False, omit? True
bs_p2_xmm[74] ^= temp;
/// interaction with truncated: //bs_p2_xmm[106]:0x7 ,0? False, omit? True
bs_p2_xmm[106] ^= bs_p2_xmm[74];
/// interaction with truncated: //bs_p2_xmm[107]:0x2a ,0? False, omit? True
temp = bs_p2_xmm[107];
/// omit x const: //temp:0x3f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x3f ,0? False, omit? True
bs_p2_xmm[75] ^= temp;
/// interaction with truncated: //bs_p2_xmm[107]:0x2e ,0? False, omit? True
bs_p2_xmm[107] ^= bs_p2_xmm[75];
/// interaction with truncated: //bs_p2_xmm[108]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[108];
/// omit x const: //temp:0x1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x1 ,0? False, omit? True
bs_p2_xmm[76] ^= temp;
/// interaction with truncated: //bs_p2_xmm[108]:0x3 ,0? False, omit? True
bs_p2_xmm[108] ^= bs_p2_xmm[76];
/// interaction with truncated: //bs_p2_xmm[109]:0x2c ,0? False, omit? True
temp = bs_p2_xmm[109];
/// omit x const: //temp:0x34 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x34 ,0? False, omit? True
bs_p2_xmm[77] ^= temp;
/// interaction with truncated: //bs_p2_xmm[109]:0x21 ,0? False, omit? True
bs_p2_xmm[109] ^= bs_p2_xmm[77];
/// interaction with truncated: //bs_p2_xmm[110]:0x1 ,0? False, omit? True
temp = bs_p2_xmm[110];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2 ,0? False, omit? True
bs_p2_xmm[78] ^= temp;
/// interaction with truncated: //bs_p2_xmm[110]:0x0 ,0? False, omit? True
bs_p2_xmm[110] ^= bs_p2_xmm[78];
/// interaction with truncated: //bs_p2_xmm[111]:0x2f ,0? False, omit? True
temp = bs_p2_xmm[111];
/// omit x const: //temp:0x35 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x35 ,0? False, omit? True
bs_p2_xmm[79] ^= temp;
/// interaction with truncated: //bs_p2_xmm[111]:0x26 ,0? False, omit? True
bs_p2_xmm[111] ^= bs_p2_xmm[79];
/// interaction with truncated: //bs_p2_xmm[112]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[112];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[80] ^= temp;
/// interaction with truncated: //bs_p2_xmm[112]:0x1 ,0? True, omit? True
bs_p2_xmm[112] = bs_p2_xmm[80];
/// interaction with truncated: //bs_p2_xmm[113]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[113];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[81] ^= temp;
/// interaction with truncated: //bs_p2_xmm[113]:0x1f ,0? True, omit? True
bs_p2_xmm[113] = bs_p2_xmm[81];
/// interaction with truncated: //bs_p2_xmm[114]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[114];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[82] ^= temp;
/// interaction with truncated: //bs_p2_xmm[114]:0x0 ,0? True, omit? True
bs_p2_xmm[114] = bs_p2_xmm[82];
/// interaction with truncated: //bs_p2_xmm[115]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[115];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[83] ^= temp;
/// interaction with truncated: //bs_p2_xmm[115]:0x30 ,0? True, omit? True
bs_p2_xmm[115] = bs_p2_xmm[83];
/// interaction with truncated: //bs_p2_xmm[116]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[116];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[84] ^= temp;
/// interaction with truncated: //bs_p2_xmm[116]:0x0 ,0? True, omit? True
bs_p2_xmm[116] = bs_p2_xmm[84];
/// interaction with truncated: //bs_p2_xmm[117]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[117];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[85] ^= temp;
/// interaction with truncated: //bs_p2_xmm[117]:0x30 ,0? True, omit? True
bs_p2_xmm[117] = bs_p2_xmm[85];
/// interaction with truncated: //bs_p2_xmm[118]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[118];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[86] ^= temp;
/// interaction with truncated: //bs_p2_xmm[118]:0x0 ,0? True, omit? True
bs_p2_xmm[118] = bs_p2_xmm[86];
/// interaction with truncated: //bs_p2_xmm[119]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[119];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[87] ^= temp;
/// interaction with truncated: //bs_p2_xmm[119]:0x30 ,0? True, omit? True
bs_p2_xmm[119] = bs_p2_xmm[87];
/// interaction with truncated: //bs_p2_xmm[120]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[120];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[88] ^= temp;
/// interaction with truncated: //bs_p2_xmm[120]:0x0 ,0? True, omit? True
bs_p2_xmm[120] = bs_p2_xmm[88];
/// interaction with truncated: //bs_p2_xmm[121]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[121];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[89] ^= temp;
/// interaction with truncated: //bs_p2_xmm[121]:0x30 ,0? True, omit? True
bs_p2_xmm[121] = bs_p2_xmm[89];
/// interaction with truncated: //bs_p2_xmm[122]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[122];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[90] ^= temp;
/// interaction with truncated: //bs_p2_xmm[122]:0x0 ,0? True, omit? True
bs_p2_xmm[122] = bs_p2_xmm[90];
/// interaction with truncated: //bs_p2_xmm[123]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[123];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[91] ^= temp;
/// interaction with truncated: //bs_p2_xmm[123]:0x30 ,0? True, omit? True
bs_p2_xmm[123] = bs_p2_xmm[91];
/// interaction with truncated: //bs_p2_xmm[124]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[124];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[92] ^= temp;
/// interaction with truncated: //bs_p2_xmm[124]:0x0 ,0? True, omit? True
bs_p2_xmm[124] = bs_p2_xmm[92];
/// interaction with truncated: //bs_p2_xmm[125]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[125];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[93] ^= temp;
/// interaction with truncated: //bs_p2_xmm[125]:0x30 ,0? True, omit? True
bs_p2_xmm[125] = bs_p2_xmm[93];
/// interaction with truncated: //bs_p2_xmm[126]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[126];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[94] ^= temp;
/// interaction with truncated: //bs_p2_xmm[126]:0x0 ,0? True, omit? True
bs_p2_xmm[126] = bs_p2_xmm[94];
/// interaction with truncated: //bs_p2_xmm[127]:0x0 ,0? True, omit? True
temp = bs_p2_xmm[127];
/// omit x const: //temp:0x0 ,0? True, omit? True
/// 0x?: temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? True, omit? True
/// + 0: bs_p2_xmm[95] ^= temp;
/// interaction with truncated: //bs_p2_xmm[127]:0x30 ,0? True, omit? True
bs_p2_xmm[127] = bs_p2_xmm[95];
//butterfly_w0x20( vec[32:64-95], 0x40 )
temp = bs_p2_xmm[80];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[64] ^= temp;
bs_p2_xmm[80] ^= bs_p2_xmm[64];
temp = bs_p2_xmm[81];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[65] ^= temp;
bs_p2_xmm[81] ^= bs_p2_xmm[65];
temp = bs_p2_xmm[82];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[66] ^= temp;
bs_p2_xmm[82] ^= bs_p2_xmm[66];
temp = bs_p2_xmm[83];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[67] ^= temp;
bs_p2_xmm[83] ^= bs_p2_xmm[67];
temp = bs_p2_xmm[84];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[68] ^= temp;
bs_p2_xmm[84] ^= bs_p2_xmm[68];
temp = bs_p2_xmm[85];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[69] ^= temp;
bs_p2_xmm[85] ^= bs_p2_xmm[69];
temp = bs_p2_xmm[86];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[70] ^= temp;
bs_p2_xmm[86] ^= bs_p2_xmm[70];
temp = bs_p2_xmm[87];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[71] ^= temp;
bs_p2_xmm[87] ^= bs_p2_xmm[71];
temp = bs_p2_xmm[88];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[72] ^= temp;
bs_p2_xmm[88] ^= bs_p2_xmm[72];
temp = bs_p2_xmm[89];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[73] ^= temp;
bs_p2_xmm[89] ^= bs_p2_xmm[73];
temp = bs_p2_xmm[90];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[74] ^= temp;
bs_p2_xmm[90] ^= bs_p2_xmm[74];
temp = bs_p2_xmm[91];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[75] ^= temp;
bs_p2_xmm[91] ^= bs_p2_xmm[75];
temp = bs_p2_xmm[92];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[76] ^= temp;
bs_p2_xmm[92] ^= bs_p2_xmm[76];
temp = bs_p2_xmm[93];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[77] ^= temp;
bs_p2_xmm[93] ^= bs_p2_xmm[77];
temp = bs_p2_xmm[94];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[78] ^= temp;
bs_p2_xmm[94] ^= bs_p2_xmm[78];
temp = bs_p2_xmm[95];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p2_xmm[79] ^= temp;
bs_p2_xmm[95] ^= bs_p2_xmm[79];
//butterfly_w0x10( vec[16:64-79], 0x40 )
temp = bs_p2_xmm[72];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[64] ^= temp;
bs_p2_xmm[72] ^= bs_p2_xmm[64];
temp = bs_p2_xmm[73];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[65] ^= temp;
bs_p2_xmm[73] ^= bs_p2_xmm[65];
temp = bs_p2_xmm[74];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[66] ^= temp;
bs_p2_xmm[74] ^= bs_p2_xmm[66];
temp = bs_p2_xmm[75];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[67] ^= temp;
bs_p2_xmm[75] ^= bs_p2_xmm[67];
temp = bs_p2_xmm[76];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[68] ^= temp;
bs_p2_xmm[76] ^= bs_p2_xmm[68];
temp = bs_p2_xmm[77];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[69] ^= temp;
bs_p2_xmm[77] ^= bs_p2_xmm[69];
temp = bs_p2_xmm[78];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[70] ^= temp;
bs_p2_xmm[78] ^= bs_p2_xmm[70];
temp = bs_p2_xmm[79];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p2_xmm[71] ^= temp;
bs_p2_xmm[79] ^= bs_p2_xmm[71];
//butterfly_w0x8( vec[8:64-71], 0x40 )
temp = bs_p2_xmm[68];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p2_xmm[64] ^= temp;
bs_p2_xmm[68] ^= bs_p2_xmm[64];
temp = bs_p2_xmm[69];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p2_xmm[65] ^= temp;
bs_p2_xmm[69] ^= bs_p2_xmm[65];
temp = bs_p2_xmm[70];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p2_xmm[66] ^= temp;
bs_p2_xmm[70] ^= bs_p2_xmm[66];
temp = bs_p2_xmm[71];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p2_xmm[67] ^= temp;
bs_p2_xmm[71] ^= bs_p2_xmm[67];
//butterfly_w0x4( vec[4:64-67], 0x40 )
temp = bs_p2_xmm[66];
temp = tbl_gf256_mul_const(0x27,temp);
bs_p2_xmm[64] ^= temp;
bs_p2_xmm[66] ^= bs_p2_xmm[64];
temp = bs_p2_xmm[67];
temp = tbl_gf256_mul_const(0x27,temp);
bs_p2_xmm[65] ^= temp;
bs_p2_xmm[67] ^= bs_p2_xmm[65];
//butterfly_w0x2( vec[2:64-65], 0x40 )
temp = bs_p2_xmm[65];
temp = tbl_gf256_mul_const(0x40,temp);
bs_p2_xmm[64] ^= temp;
bs_p2_xmm[65] ^= bs_p2_xmm[64];
//butterfly_w0x2( vec[2:66-67], 0x42 )
temp = bs_p2_xmm[67];
temp = tbl_gf256_mul_const(0x42,temp);
bs_p2_xmm[66] ^= temp;
bs_p2_xmm[67] ^= bs_p2_xmm[66];
//butterfly_w0x4( vec[4:68-71], 0x44 )
temp = bs_p2_xmm[70];
temp = tbl_gf256_mul_const(0x25,temp);
bs_p2_xmm[68] ^= temp;
bs_p2_xmm[70] ^= bs_p2_xmm[68];
temp = bs_p2_xmm[71];
temp = tbl_gf256_mul_const(0x25,temp);
bs_p2_xmm[69] ^= temp;
bs_p2_xmm[71] ^= bs_p2_xmm[69];
//butterfly_w0x2( vec[2:68-69], 0x44 )
temp = bs_p2_xmm[69];
temp = tbl_gf256_mul_const(0x44,temp);
bs_p2_xmm[68] ^= temp;
bs_p2_xmm[69] ^= bs_p2_xmm[68];
//butterfly_w0x2( vec[2:70-71], 0x46 )
temp = bs_p2_xmm[71];
temp = tbl_gf256_mul_const(0x46,temp);
bs_p2_xmm[70] ^= temp;
bs_p2_xmm[71] ^= bs_p2_xmm[70];
//butterfly_w0x8( vec[8:72-79], 0x48 )
temp = bs_p2_xmm[76];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p2_xmm[72] ^= temp;
bs_p2_xmm[76] ^= bs_p2_xmm[72];
temp = bs_p2_xmm[77];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p2_xmm[73] ^= temp;
bs_p2_xmm[77] ^= bs_p2_xmm[73];
temp = bs_p2_xmm[78];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p2_xmm[74] ^= temp;
bs_p2_xmm[78] ^= bs_p2_xmm[74];
temp = bs_p2_xmm[79];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p2_xmm[75] ^= temp;
bs_p2_xmm[79] ^= bs_p2_xmm[75];
//butterfly_w0x4( vec[4:72-75], 0x48 )
temp = bs_p2_xmm[74];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p2_xmm[72] ^= temp;
bs_p2_xmm[74] ^= bs_p2_xmm[72];
temp = bs_p2_xmm[75];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p2_xmm[73] ^= temp;
bs_p2_xmm[75] ^= bs_p2_xmm[73];
//butterfly_w0x2( vec[2:72-73], 0x48 )
temp = bs_p2_xmm[73];
temp = tbl_gf256_mul_const(0x48,temp);
bs_p2_xmm[72] ^= temp;
bs_p2_xmm[73] ^= bs_p2_xmm[72];
//butterfly_w0x2( vec[2:74-75], 0x4a )
temp = bs_p2_xmm[75];
temp = tbl_gf256_mul_const(0x4a,temp);
bs_p2_xmm[74] ^= temp;
bs_p2_xmm[75] ^= bs_p2_xmm[74];
//butterfly_w0x4( vec[4:76-79], 0x4c )
temp = bs_p2_xmm[78];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p2_xmm[76] ^= temp;
bs_p2_xmm[78] ^= bs_p2_xmm[76];
temp = bs_p2_xmm[79];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p2_xmm[77] ^= temp;
bs_p2_xmm[79] ^= bs_p2_xmm[77];
//butterfly_w0x2( vec[2:76-77], 0x4c )
temp = bs_p2_xmm[77];
temp = tbl_gf256_mul_const(0x4c,temp);
bs_p2_xmm[76] ^= temp;
bs_p2_xmm[77] ^= bs_p2_xmm[76];
//butterfly_w0x2( vec[2:78-79], 0x4e )
temp = bs_p2_xmm[79];
temp = tbl_gf256_mul_const(0x4e,temp);
bs_p2_xmm[78] ^= temp;
bs_p2_xmm[79] ^= bs_p2_xmm[78];
//butterfly_w0x10( vec[16:80-95], 0x50 )
temp = bs_p2_xmm[88];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[80] ^= temp;
bs_p2_xmm[88] ^= bs_p2_xmm[80];
temp = bs_p2_xmm[89];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[81] ^= temp;
bs_p2_xmm[89] ^= bs_p2_xmm[81];
temp = bs_p2_xmm[90];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[82] ^= temp;
bs_p2_xmm[90] ^= bs_p2_xmm[82];
temp = bs_p2_xmm[91];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[83] ^= temp;
bs_p2_xmm[91] ^= bs_p2_xmm[83];
temp = bs_p2_xmm[92];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[84] ^= temp;
bs_p2_xmm[92] ^= bs_p2_xmm[84];
temp = bs_p2_xmm[93];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[85] ^= temp;
bs_p2_xmm[93] ^= bs_p2_xmm[85];
temp = bs_p2_xmm[94];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[86] ^= temp;
bs_p2_xmm[94] ^= bs_p2_xmm[86];
temp = bs_p2_xmm[95];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p2_xmm[87] ^= temp;
bs_p2_xmm[95] ^= bs_p2_xmm[87];
//butterfly_w0x8( vec[8:80-87], 0x50 )
temp = bs_p2_xmm[84];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p2_xmm[80] ^= temp;
bs_p2_xmm[84] ^= bs_p2_xmm[80];
temp = bs_p2_xmm[85];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p2_xmm[81] ^= temp;
bs_p2_xmm[85] ^= bs_p2_xmm[81];
temp = bs_p2_xmm[86];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p2_xmm[82] ^= temp;
bs_p2_xmm[86] ^= bs_p2_xmm[82];
temp = bs_p2_xmm[87];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p2_xmm[83] ^= temp;
bs_p2_xmm[87] ^= bs_p2_xmm[83];
//butterfly_w0x4( vec[4:80-83], 0x50 )
temp = bs_p2_xmm[82];
temp = tbl_gf256_mul_const(0x2f,temp);
bs_p2_xmm[80] ^= temp;
bs_p2_xmm[82] ^= bs_p2_xmm[80];
temp = bs_p2_xmm[83];
temp = tbl_gf256_mul_const(0x2f,temp);
bs_p2_xmm[81] ^= temp;
bs_p2_xmm[83] ^= bs_p2_xmm[81];
//butterfly_w0x2( vec[2:80-81], 0x50 )
temp = bs_p2_xmm[81];
temp = tbl_gf256_mul_const(0x50,temp);
bs_p2_xmm[80] ^= temp;
bs_p2_xmm[81] ^= bs_p2_xmm[80];
//butterfly_w0x2( vec[2:82-83], 0x52 )
temp = bs_p2_xmm[83];
temp = tbl_gf256_mul_const(0x52,temp);
bs_p2_xmm[82] ^= temp;
bs_p2_xmm[83] ^= bs_p2_xmm[82];
//butterfly_w0x4( vec[4:84-87], 0x54 )
temp = bs_p2_xmm[86];
temp = tbl_gf256_mul_const(0x2d,temp);
bs_p2_xmm[84] ^= temp;
bs_p2_xmm[86] ^= bs_p2_xmm[84];
temp = bs_p2_xmm[87];
temp = tbl_gf256_mul_const(0x2d,temp);
bs_p2_xmm[85] ^= temp;
bs_p2_xmm[87] ^= bs_p2_xmm[85];
//butterfly_w0x2( vec[2:84-85], 0x54 )
temp = bs_p2_xmm[85];
temp = tbl_gf256_mul_const(0x54,temp);
bs_p2_xmm[84] ^= temp;
bs_p2_xmm[85] ^= bs_p2_xmm[84];
//butterfly_w0x2( vec[2:86-87], 0x56 )
temp = bs_p2_xmm[87];
temp = tbl_gf256_mul_const(0x56,temp);
bs_p2_xmm[86] ^= temp;
bs_p2_xmm[87] ^= bs_p2_xmm[86];
//butterfly_w0x8( vec[8:88-95], 0x58 )
temp = bs_p2_xmm[92];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p2_xmm[88] ^= temp;
bs_p2_xmm[92] ^= bs_p2_xmm[88];
temp = bs_p2_xmm[93];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p2_xmm[89] ^= temp;
bs_p2_xmm[93] ^= bs_p2_xmm[89];
temp = bs_p2_xmm[94];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p2_xmm[90] ^= temp;
bs_p2_xmm[94] ^= bs_p2_xmm[90];
temp = bs_p2_xmm[95];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p2_xmm[91] ^= temp;
bs_p2_xmm[95] ^= bs_p2_xmm[91];
//butterfly_w0x4( vec[4:88-91], 0x58 )
temp = bs_p2_xmm[90];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p2_xmm[88] ^= temp;
bs_p2_xmm[90] ^= bs_p2_xmm[88];
temp = bs_p2_xmm[91];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p2_xmm[89] ^= temp;
bs_p2_xmm[91] ^= bs_p2_xmm[89];
//butterfly_w0x2( vec[2:88-89], 0x58 )
temp = bs_p2_xmm[89];
temp = tbl_gf256_mul_const(0x58,temp);
bs_p2_xmm[88] ^= temp;
bs_p2_xmm[89] ^= bs_p2_xmm[88];
//butterfly_w0x2( vec[2:90-91], 0x5a )
temp = bs_p2_xmm[91];
temp = tbl_gf256_mul_const(0x5a,temp);
bs_p2_xmm[90] ^= temp;
bs_p2_xmm[91] ^= bs_p2_xmm[90];
//butterfly_w0x4( vec[4:92-95], 0x5c )
temp = bs_p2_xmm[94];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p2_xmm[92] ^= temp;
bs_p2_xmm[94] ^= bs_p2_xmm[92];
temp = bs_p2_xmm[95];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p2_xmm[93] ^= temp;
bs_p2_xmm[95] ^= bs_p2_xmm[93];
//butterfly_w0x2( vec[2:92-93], 0x5c )
temp = bs_p2_xmm[93];
temp = tbl_gf256_mul_const(0x5c,temp);
bs_p2_xmm[92] ^= temp;
bs_p2_xmm[93] ^= bs_p2_xmm[92];
//butterfly_w0x2( vec[2:94-95], 0x5e )
temp = bs_p2_xmm[95];
temp = tbl_gf256_mul_const(0x5e,temp);
bs_p2_xmm[94] ^= temp;
bs_p2_xmm[95] ^= bs_p2_xmm[94];
//butterfly_w0x20( vec[32:96-127], 0x60 )
/// interaction with truncated: //bs_p2_xmm[112]:0x1 ,0? False, omit? True
temp = bs_p2_xmm[112];
/// omit x const: //temp:0x6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[96] ^= temp;
/// truncated: bs_p2_xmm[112] ^= bs_p2_xmm[96];
/// interaction with truncated: //bs_p2_xmm[113]:0x1f ,0? False, omit? True
temp = bs_p2_xmm[113];
/// omit x const: //temp:0x64 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[97] ^= temp;
/// truncated: bs_p2_xmm[113] ^= bs_p2_xmm[97];
/// interaction with truncated: //bs_p2_xmm[114]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[114];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[98] ^= temp;
/// truncated: bs_p2_xmm[114] ^= bs_p2_xmm[98];
/// interaction with truncated: //bs_p2_xmm[115]:0x30 ,0? False, omit? True
temp = bs_p2_xmm[115];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[99] ^= temp;
/// truncated: bs_p2_xmm[115] ^= bs_p2_xmm[99];
/// interaction with truncated: //bs_p2_xmm[116]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[116];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[100] ^= temp;
/// truncated: bs_p2_xmm[116] ^= bs_p2_xmm[100];
/// interaction with truncated: //bs_p2_xmm[117]:0x30 ,0? False, omit? True
temp = bs_p2_xmm[117];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[101] ^= temp;
/// truncated: bs_p2_xmm[117] ^= bs_p2_xmm[101];
/// interaction with truncated: //bs_p2_xmm[118]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[118];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[102] ^= temp;
/// truncated: bs_p2_xmm[118] ^= bs_p2_xmm[102];
/// interaction with truncated: //bs_p2_xmm[119]:0x30 ,0? False, omit? True
temp = bs_p2_xmm[119];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[103] ^= temp;
/// truncated: bs_p2_xmm[119] ^= bs_p2_xmm[103];
/// interaction with truncated: //bs_p2_xmm[120]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[120];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[104] ^= temp;
/// truncated: bs_p2_xmm[120] ^= bs_p2_xmm[104];
/// interaction with truncated: //bs_p2_xmm[121]:0x30 ,0? False, omit? True
temp = bs_p2_xmm[121];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[105] ^= temp;
/// truncated: bs_p2_xmm[121] ^= bs_p2_xmm[105];
/// interaction with truncated: //bs_p2_xmm[122]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[122];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[106] ^= temp;
/// truncated: bs_p2_xmm[122] ^= bs_p2_xmm[106];
/// interaction with truncated: //bs_p2_xmm[123]:0x30 ,0? False, omit? True
temp = bs_p2_xmm[123];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[107] ^= temp;
/// truncated: bs_p2_xmm[123] ^= bs_p2_xmm[107];
/// interaction with truncated: //bs_p2_xmm[124]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[124];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[108] ^= temp;
/// truncated: bs_p2_xmm[124] ^= bs_p2_xmm[108];
/// interaction with truncated: //bs_p2_xmm[125]:0x30 ,0? False, omit? True
temp = bs_p2_xmm[125];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[109] ^= temp;
/// truncated: bs_p2_xmm[125] ^= bs_p2_xmm[109];
/// interaction with truncated: //bs_p2_xmm[126]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[126];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[110] ^= temp;
/// truncated: bs_p2_xmm[126] ^= bs_p2_xmm[110];
/// interaction with truncated: //bs_p2_xmm[127]:0x30 ,0? False, omit? True
temp = bs_p2_xmm[127];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p2_xmm[111] ^= temp;
/// truncated: bs_p2_xmm[127] ^= bs_p2_xmm[111];
//butterfly_w0x10( vec[16:96-111], 0x60 )
/// interaction with truncated: //bs_p2_xmm[104]:0x8 ,0? False, omit? True
temp = bs_p2_xmm[104];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[96] ^= temp;
/// truncated: bs_p2_xmm[104] ^= bs_p2_xmm[96];
/// interaction with truncated: //bs_p2_xmm[105]:0xf2 ,0? False, omit? True
temp = bs_p2_xmm[105];
/// omit x const: //temp:0x95 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[97] ^= temp;
/// truncated: bs_p2_xmm[105] ^= bs_p2_xmm[97];
/// interaction with truncated: //bs_p2_xmm[106]:0x7 ,0? False, omit? True
temp = bs_p2_xmm[106];
/// omit x const: //temp:0xb ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[98] ^= temp;
/// truncated: bs_p2_xmm[106] ^= bs_p2_xmm[98];
/// interaction with truncated: //bs_p2_xmm[107]:0xfe ,0? False, omit? True
temp = bs_p2_xmm[107];
/// omit x const: //temp:0x96 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[99] ^= temp;
/// truncated: bs_p2_xmm[107] ^= bs_p2_xmm[99];
/// interaction with truncated: //bs_p2_xmm[108]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[108];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[100] ^= temp;
/// truncated: bs_p2_xmm[108] ^= bs_p2_xmm[100];
/// interaction with truncated: //bs_p2_xmm[109]:0xf1 ,0? False, omit? True
temp = bs_p2_xmm[109];
/// omit x const: //temp:0x9f ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[101] ^= temp;
/// truncated: bs_p2_xmm[109] ^= bs_p2_xmm[101];
/// interaction with truncated: //bs_p2_xmm[110]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[110];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[102] ^= temp;
/// truncated: bs_p2_xmm[110] ^= bs_p2_xmm[102];
/// interaction with truncated: //bs_p2_xmm[111]:0xf6 ,0? False, omit? True
temp = bs_p2_xmm[111];
/// omit x const: //temp:0x94 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p2_xmm[103] ^= temp;
/// truncated: bs_p2_xmm[111] ^= bs_p2_xmm[103];
//butterfly_w0x8( vec[8:96-103], 0x60 )
/// interaction with truncated: //bs_p2_xmm[100]:0xe ,0? False, omit? True
temp = bs_p2_xmm[100];
/// omit x const: //temp:0xe1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p2_xmm[96] ^= temp;
/// truncated: bs_p2_xmm[100] ^= bs_p2_xmm[96];
/// interaction with truncated: //bs_p2_xmm[101]:0x6a ,0? False, omit? True
temp = bs_p2_xmm[101];
/// omit x const: //temp:0x3f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p2_xmm[97] ^= temp;
/// truncated: bs_p2_xmm[101] ^= bs_p2_xmm[97];
/// interaction with truncated: //bs_p2_xmm[102]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[102];
/// omit x const: //temp:0x3b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p2_xmm[98] ^= temp;
/// truncated: bs_p2_xmm[102] ^= bs_p2_xmm[98];
/// interaction with truncated: //bs_p2_xmm[103]:0x61 ,0? False, omit? True
temp = bs_p2_xmm[103];
/// omit x const: //temp:0x8a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p2_xmm[99] ^= temp;
/// truncated: bs_p2_xmm[103] ^= bs_p2_xmm[99];
//butterfly_w0x4( vec[4:96-99], 0x60 )
/// interaction with truncated: //bs_p2_xmm[98]:0x1f ,0? False, omit? True
temp = bs_p2_xmm[98];
/// omit x const: //temp:0xae ,0? False, omit? True
temp = tbl_gf256_mul_const(0x33,temp);
/// truncated: bs_p2_xmm[96] ^= temp;
/// truncated: bs_p2_xmm[98] ^= bs_p2_xmm[96];
/// interaction with truncated: //bs_p2_xmm[99]:0xe6 ,0? False, omit? True
temp = bs_p2_xmm[99];
/// omit x const: //temp:0xd8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x33,temp);
/// truncated: bs_p2_xmm[97] ^= temp;
/// truncated: bs_p2_xmm[99] ^= bs_p2_xmm[97];
//butterfly_w0x2( vec[2:96-97], 0x60 )
/// interaction with truncated: //bs_p2_xmm[97]:0x6 ,0? False, omit? True
temp = bs_p2_xmm[97];
/// omit x const: //temp:0x50 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x60,temp);
/// truncated: bs_p2_xmm[96] ^= temp;
/// truncated: bs_p2_xmm[97] ^= bs_p2_xmm[96];
//butterfly_w0x2( vec[2:98-99], 0x62 )
/// interaction with truncated: //bs_p2_xmm[99]:0xe0 ,0? False, omit? True
temp = bs_p2_xmm[99];
/// omit x const: //temp:0x5c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x62,temp);
/// truncated: bs_p2_xmm[98] ^= temp;
/// truncated: bs_p2_xmm[99] ^= bs_p2_xmm[98];
//butterfly_w0x4( vec[4:100-103], 0x64 )
/// interaction with truncated: //bs_p2_xmm[102]:0x1c ,0? False, omit? True
temp = bs_p2_xmm[102];
/// omit x const: //temp:0xa8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x31,temp);
/// truncated: bs_p2_xmm[100] ^= temp;
/// truncated: bs_p2_xmm[102] ^= bs_p2_xmm[100];
/// interaction with truncated: //bs_p2_xmm[103]:0x87 ,0? False, omit? True
temp = bs_p2_xmm[103];
/// omit x const: //temp:0x2c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x31,temp);
/// truncated: bs_p2_xmm[101] ^= temp;
/// truncated: bs_p2_xmm[103] ^= bs_p2_xmm[101];
//butterfly_w0x2( vec[2:100-101], 0x64 )
/// interaction with truncated: //bs_p2_xmm[101]:0x98 ,0? False, omit? True
temp = bs_p2_xmm[101];
/// omit x const: //temp:0x93 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x64,temp);
/// truncated: bs_p2_xmm[100] ^= temp;
/// truncated: bs_p2_xmm[101] ^= bs_p2_xmm[100];
//butterfly_w0x2( vec[2:102-103], 0x66 )
/// interaction with truncated: //bs_p2_xmm[103]:0x1f ,0? False, omit? True
temp = bs_p2_xmm[103];
/// omit x const: //temp:0x43 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x66,temp);
/// truncated: bs_p2_xmm[102] ^= temp;
/// truncated: bs_p2_xmm[103] ^= bs_p2_xmm[102];
//butterfly_w0x8( vec[8:104-111], 0x68 )
/// interaction with truncated: //bs_p2_xmm[108]:0xd ,0? False, omit? True
temp = bs_p2_xmm[108];
/// omit x const: //temp:0xdc ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p2_xmm[104] ^= temp;
/// truncated: bs_p2_xmm[108] ^= bs_p2_xmm[104];
/// interaction with truncated: //bs_p2_xmm[109]:0x9b ,0? False, omit? True
temp = bs_p2_xmm[109];
/// omit x const: //temp:0xfd ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p2_xmm[105] ^= temp;
/// truncated: bs_p2_xmm[109] ^= bs_p2_xmm[105];
/// interaction with truncated: //bs_p2_xmm[110]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[110];
/// omit x const: //temp:0x3a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p2_xmm[106] ^= temp;
/// truncated: bs_p2_xmm[110] ^= bs_p2_xmm[106];
/// interaction with truncated: //bs_p2_xmm[111]:0x97 ,0? False, omit? True
temp = bs_p2_xmm[111];
/// omit x const: //temp:0x3e ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p2_xmm[107] ^= temp;
/// truncated: bs_p2_xmm[111] ^= bs_p2_xmm[107];
//butterfly_w0x4( vec[4:104-107], 0x68 )
/// interaction with truncated: //bs_p2_xmm[106]:0x19 ,0? False, omit? True
temp = bs_p2_xmm[106];
/// omit x const: //temp:0x25 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x36,temp);
/// truncated: bs_p2_xmm[104] ^= temp;
/// truncated: bs_p2_xmm[106] ^= bs_p2_xmm[104];
/// interaction with truncated: //bs_p2_xmm[107]:0xac ,0? False, omit? True
temp = bs_p2_xmm[107];
/// omit x const: //temp:0x1a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x36,temp);
/// truncated: bs_p2_xmm[105] ^= temp;
/// truncated: bs_p2_xmm[107] ^= bs_p2_xmm[105];
//butterfly_w0x2( vec[2:104-105], 0x68 )
/// interaction with truncated: //bs_p2_xmm[105]:0xf4 ,0? False, omit? True
temp = bs_p2_xmm[105];
/// omit x const: //temp:0x80 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x68,temp);
/// truncated: bs_p2_xmm[104] ^= temp;
/// truncated: bs_p2_xmm[105] ^= bs_p2_xmm[104];
//butterfly_w0x2( vec[2:106-107], 0x6a )
/// interaction with truncated: //bs_p2_xmm[107]:0x58 ,0? False, omit? True
temp = bs_p2_xmm[107];
/// omit x const: //temp:0x6c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6a,temp);
/// truncated: bs_p2_xmm[106] ^= temp;
/// truncated: bs_p2_xmm[107] ^= bs_p2_xmm[106];
//butterfly_w0x4( vec[4:108-111], 0x6c )
/// interaction with truncated: //bs_p2_xmm[110]:0x1a ,0? False, omit? True
temp = bs_p2_xmm[110];
/// omit x const: //temp:0x27 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x34,temp);
/// truncated: bs_p2_xmm[108] ^= temp;
/// truncated: bs_p2_xmm[110] ^= bs_p2_xmm[108];
/// interaction with truncated: //bs_p2_xmm[111]:0x3b ,0? False, omit? True
temp = bs_p2_xmm[111];
/// omit x const: //temp:0x8b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x34,temp);
/// truncated: bs_p2_xmm[109] ^= temp;
/// truncated: bs_p2_xmm[111] ^= bs_p2_xmm[109];
//butterfly_w0x2( vec[2:108-109], 0x6c )
/// interaction with truncated: //bs_p2_xmm[109]:0xfe ,0? False, omit? True
temp = bs_p2_xmm[109];
/// omit x const: //temp:0x54 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6c,temp);
/// truncated: bs_p2_xmm[108] ^= temp;
/// truncated: bs_p2_xmm[109] ^= bs_p2_xmm[108];
//butterfly_w0x2( vec[2:110-111], 0x6e )
/// interaction with truncated: //bs_p2_xmm[111]:0xc5 ,0? False, omit? True
temp = bs_p2_xmm[111];
/// omit x const: //temp:0xee ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6e,temp);
/// truncated: bs_p2_xmm[110] ^= temp;
/// truncated: bs_p2_xmm[111] ^= bs_p2_xmm[110];
//butterfly_w0x10( vec[16:112-127], 0x70 )
/// interaction with truncated: //bs_p2_xmm[120]:0x8 ,0? False, omit? True
temp = bs_p2_xmm[120];
/// omit x const: //temp:0xe ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[112] ^= temp;
/// truncated: bs_p2_xmm[120] ^= bs_p2_xmm[112];
/// interaction with truncated: //bs_p2_xmm[121]:0xc2 ,0? False, omit? True
temp = bs_p2_xmm[121];
/// omit x const: //temp:0x76 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[113] ^= temp;
/// truncated: bs_p2_xmm[121] ^= bs_p2_xmm[113];
/// interaction with truncated: //bs_p2_xmm[122]:0x7 ,0? False, omit? True
temp = bs_p2_xmm[122];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[114] ^= temp;
/// truncated: bs_p2_xmm[122] ^= bs_p2_xmm[114];
/// interaction with truncated: //bs_p2_xmm[123]:0xce ,0? False, omit? True
temp = bs_p2_xmm[123];
/// omit x const: //temp:0x71 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[115] ^= temp;
/// truncated: bs_p2_xmm[123] ^= bs_p2_xmm[115];
/// interaction with truncated: //bs_p2_xmm[124]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[124];
/// omit x const: //temp:0xb ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[116] ^= temp;
/// truncated: bs_p2_xmm[124] ^= bs_p2_xmm[116];
/// interaction with truncated: //bs_p2_xmm[125]:0xc1 ,0? False, omit? True
temp = bs_p2_xmm[125];
/// omit x const: //temp:0x7d ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[117] ^= temp;
/// truncated: bs_p2_xmm[125] ^= bs_p2_xmm[117];
/// interaction with truncated: //bs_p2_xmm[126]:0x0 ,0? False, omit? True
temp = bs_p2_xmm[126];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[118] ^= temp;
/// truncated: bs_p2_xmm[126] ^= bs_p2_xmm[118];
/// interaction with truncated: //bs_p2_xmm[127]:0xc6 ,0? False, omit? True
temp = bs_p2_xmm[127];
/// omit x const: //temp:0x7f ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p2_xmm[119] ^= temp;
/// truncated: bs_p2_xmm[127] ^= bs_p2_xmm[119];
//butterfly_w0x8( vec[8:112-119], 0x70 )
/// interaction with truncated: //bs_p2_xmm[116]:0xf ,0? False, omit? True
temp = bs_p2_xmm[116];
/// omit x const: //temp:0xf2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p2_xmm[112] ^= temp;
/// truncated: bs_p2_xmm[116] ^= bs_p2_xmm[112];
/// interaction with truncated: //bs_p2_xmm[117]:0xb8 ,0? False, omit? True
temp = bs_p2_xmm[117];
/// omit x const: //temp:0xa4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p2_xmm[113] ^= temp;
/// truncated: bs_p2_xmm[117] ^= bs_p2_xmm[113];
/// interaction with truncated: //bs_p2_xmm[118]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[118];
/// omit x const: //temp:0x34 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p2_xmm[114] ^= temp;
/// truncated: bs_p2_xmm[118] ^= bs_p2_xmm[114];
/// interaction with truncated: //bs_p2_xmm[119]:0xba ,0? False, omit? True
temp = bs_p2_xmm[119];
/// omit x const: //temp:0x88 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p2_xmm[115] ^= temp;
/// truncated: bs_p2_xmm[119] ^= bs_p2_xmm[115];
//butterfly_w0x4( vec[4:112-115], 0x70 )
/// interaction with truncated: //bs_p2_xmm[114]:0x19 ,0? False, omit? True
temp = bs_p2_xmm[114];
/// omit x const: //temp:0xf6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3b,temp);
/// truncated: bs_p2_xmm[112] ^= temp;
/// truncated: bs_p2_xmm[114] ^= bs_p2_xmm[112];
/// interaction with truncated: //bs_p2_xmm[115]:0x33 ,0? False, omit? True
temp = bs_p2_xmm[115];
/// omit x const: //temp:0x6a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3b,temp);
/// truncated: bs_p2_xmm[113] ^= temp;
/// truncated: bs_p2_xmm[115] ^= bs_p2_xmm[113];
//butterfly_w0x2( vec[2:112-113], 0x70 )
/// interaction with truncated: //bs_p2_xmm[113]:0xd3 ,0? False, omit? True
temp = bs_p2_xmm[113];
/// omit x const: //temp:0xcc ,0? False, omit? True
temp = tbl_gf256_mul_const(0x70,temp);
/// truncated: bs_p2_xmm[112] ^= temp;
/// truncated: bs_p2_xmm[113] ^= bs_p2_xmm[112];
//butterfly_w0x2( vec[2:114-115], 0x72 )
/// interaction with truncated: //bs_p2_xmm[115]:0xe0 ,0? False, omit? True
temp = bs_p2_xmm[115];
/// omit x const: //temp:0xb6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x72,temp);
/// truncated: bs_p2_xmm[114] ^= temp;
/// truncated: bs_p2_xmm[115] ^= bs_p2_xmm[114];
//butterfly_w0x4( vec[4:116-119], 0x74 )
/// interaction with truncated: //bs_p2_xmm[118]:0x1a ,0? False, omit? True
temp = bs_p2_xmm[118];
/// omit x const: //temp:0xff ,0? False, omit? True
temp = tbl_gf256_mul_const(0x39,temp);
/// truncated: bs_p2_xmm[116] ^= temp;
/// truncated: bs_p2_xmm[118] ^= bs_p2_xmm[116];
/// interaction with truncated: //bs_p2_xmm[119]:0x89 ,0? False, omit? True
temp = bs_p2_xmm[119];
/// omit x const: //temp:0x67 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x39,temp);
/// truncated: bs_p2_xmm[117] ^= temp;
/// truncated: bs_p2_xmm[119] ^= bs_p2_xmm[117];
//butterfly_w0x2( vec[2:116-117], 0x74 )
/// interaction with truncated: //bs_p2_xmm[117]:0x66 ,0? False, omit? True
temp = bs_p2_xmm[117];
/// omit x const: //temp:0xea ,0? False, omit? True
temp = tbl_gf256_mul_const(0x74,temp);
/// truncated: bs_p2_xmm[116] ^= temp;
/// truncated: bs_p2_xmm[117] ^= bs_p2_xmm[116];
//butterfly_w0x2( vec[2:118-119], 0x76 )
/// interaction with truncated: //bs_p2_xmm[119]:0xef ,0? False, omit? True
temp = bs_p2_xmm[119];
/// omit x const: //temp:0x52 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x76,temp);
/// truncated: bs_p2_xmm[118] ^= temp;
/// truncated: bs_p2_xmm[119] ^= bs_p2_xmm[118];
//butterfly_w0x8( vec[8:120-127], 0x78 )
/// interaction with truncated: //bs_p2_xmm[124]:0xc ,0? False, omit? True
temp = bs_p2_xmm[124];
/// omit x const: //temp:0xc2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p2_xmm[120] ^= temp;
/// truncated: bs_p2_xmm[124] ^= bs_p2_xmm[120];
/// interaction with truncated: //bs_p2_xmm[125]:0x79 ,0? False, omit? True
temp = bs_p2_xmm[125];
/// omit x const: //temp:0x84 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p2_xmm[121] ^= temp;
/// truncated: bs_p2_xmm[125] ^= bs_p2_xmm[121];
/// interaction with truncated: //bs_p2_xmm[126]:0x3 ,0? False, omit? True
temp = bs_p2_xmm[126];
/// omit x const: //temp:0x35 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p2_xmm[122] ^= temp;
/// truncated: bs_p2_xmm[126] ^= bs_p2_xmm[122];
/// interaction with truncated: //bs_p2_xmm[127]:0x7c ,0? False, omit? True
temp = bs_p2_xmm[127];
/// omit x const: //temp:0xdd ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p2_xmm[123] ^= temp;
/// truncated: bs_p2_xmm[127] ^= bs_p2_xmm[123];
//butterfly_w0x4( vec[4:120-123], 0x78 )
/// interaction with truncated: //bs_p2_xmm[122]:0x1f ,0? False, omit? True
temp = bs_p2_xmm[122];
/// omit x const: //temp:0x72 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3e,temp);
/// truncated: bs_p2_xmm[120] ^= temp;
/// truncated: bs_p2_xmm[122] ^= bs_p2_xmm[120];
/// interaction with truncated: //bs_p2_xmm[123]:0xa8 ,0? False, omit? True
temp = bs_p2_xmm[123];
/// omit x const: //temp:0xc9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3e,temp);
/// truncated: bs_p2_xmm[121] ^= temp;
/// truncated: bs_p2_xmm[123] ^= bs_p2_xmm[121];
//butterfly_w0x2( vec[2:120-121], 0x78 )
/// interaction with truncated: //bs_p2_xmm[121]:0x92 ,0? False, omit? True
temp = bs_p2_xmm[121];
/// omit x const: //temp:0x41 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x78,temp);
/// truncated: bs_p2_xmm[120] ^= temp;
/// truncated: bs_p2_xmm[121] ^= bs_p2_xmm[120];
//butterfly_w0x2( vec[2:122-123], 0x7a )
/// interaction with truncated: //bs_p2_xmm[123]:0x3a ,0? False, omit? True
temp = bs_p2_xmm[123];
/// omit x const: //temp:0xd4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7a,temp);
/// truncated: bs_p2_xmm[122] ^= temp;
/// truncated: bs_p2_xmm[123] ^= bs_p2_xmm[122];
//butterfly_w0x4( vec[4:124-127], 0x7c )
/// interaction with truncated: //bs_p2_xmm[126]:0x1c ,0? False, omit? True
temp = bs_p2_xmm[126];
/// omit x const: //temp:0x7f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3c,temp);
/// truncated: bs_p2_xmm[124] ^= temp;
/// truncated: bs_p2_xmm[126] ^= bs_p2_xmm[124];
/// interaction with truncated: //bs_p2_xmm[127]:0xd4 ,0? False, omit? True
temp = bs_p2_xmm[127];
/// omit x const: //temp:0x4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3c,temp);
/// truncated: bs_p2_xmm[125] ^= temp;
/// truncated: bs_p2_xmm[127] ^= bs_p2_xmm[125];
//butterfly_w0x2( vec[2:124-125], 0x7c )
/// interaction with truncated: //bs_p2_xmm[125]:0x26 ,0? False, omit? True
temp = bs_p2_xmm[125];
/// omit x const: //temp:0xec ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7c,temp);
/// truncated: bs_p2_xmm[124] ^= temp;
/// truncated: bs_p2_xmm[125] ^= bs_p2_xmm[124];
//butterfly_w0x2( vec[2:126-127], 0x7e )
/// interaction with truncated: //bs_p2_xmm[127]:0xf2 ,0? False, omit? True
temp = bs_p2_xmm[127];
/// omit x const: //temp:0x4e ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7e,temp);
/// truncated: bs_p2_xmm[126] ^= temp;
/// truncated: bs_p2_xmm[127] ^= bs_p2_xmm[126];
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
bs_p1_xmm[64] = tbl_gf256_mul(bs_p2_xmm[64],bs_p1_xmm[64]);
bs_p1_xmm[65] = tbl_gf256_mul(bs_p2_xmm[65],bs_p1_xmm[65]);
bs_p1_xmm[66] = tbl_gf256_mul(bs_p2_xmm[66],bs_p1_xmm[66]);
bs_p1_xmm[67] = tbl_gf256_mul(bs_p2_xmm[67],bs_p1_xmm[67]);
bs_p1_xmm[68] = tbl_gf256_mul(bs_p2_xmm[68],bs_p1_xmm[68]);
bs_p1_xmm[69] = tbl_gf256_mul(bs_p2_xmm[69],bs_p1_xmm[69]);
bs_p1_xmm[70] = tbl_gf256_mul(bs_p2_xmm[70],bs_p1_xmm[70]);
bs_p1_xmm[71] = tbl_gf256_mul(bs_p2_xmm[71],bs_p1_xmm[71]);
bs_p1_xmm[72] = tbl_gf256_mul(bs_p2_xmm[72],bs_p1_xmm[72]);
bs_p1_xmm[73] = tbl_gf256_mul(bs_p2_xmm[73],bs_p1_xmm[73]);
bs_p1_xmm[74] = tbl_gf256_mul(bs_p2_xmm[74],bs_p1_xmm[74]);
bs_p1_xmm[75] = tbl_gf256_mul(bs_p2_xmm[75],bs_p1_xmm[75]);
bs_p1_xmm[76] = tbl_gf256_mul(bs_p2_xmm[76],bs_p1_xmm[76]);
bs_p1_xmm[77] = tbl_gf256_mul(bs_p2_xmm[77],bs_p1_xmm[77]);
bs_p1_xmm[78] = tbl_gf256_mul(bs_p2_xmm[78],bs_p1_xmm[78]);
bs_p1_xmm[79] = tbl_gf256_mul(bs_p2_xmm[79],bs_p1_xmm[79]);
bs_p1_xmm[80] = tbl_gf256_mul(bs_p2_xmm[80],bs_p1_xmm[80]);
bs_p1_xmm[81] = tbl_gf256_mul(bs_p2_xmm[81],bs_p1_xmm[81]);
bs_p1_xmm[82] = tbl_gf256_mul(bs_p2_xmm[82],bs_p1_xmm[82]);
bs_p1_xmm[83] = tbl_gf256_mul(bs_p2_xmm[83],bs_p1_xmm[83]);
bs_p1_xmm[84] = tbl_gf256_mul(bs_p2_xmm[84],bs_p1_xmm[84]);
bs_p1_xmm[85] = tbl_gf256_mul(bs_p2_xmm[85],bs_p1_xmm[85]);
bs_p1_xmm[86] = tbl_gf256_mul(bs_p2_xmm[86],bs_p1_xmm[86]);
bs_p1_xmm[87] = tbl_gf256_mul(bs_p2_xmm[87],bs_p1_xmm[87]);
bs_p1_xmm[88] = tbl_gf256_mul(bs_p2_xmm[88],bs_p1_xmm[88]);
bs_p1_xmm[89] = tbl_gf256_mul(bs_p2_xmm[89],bs_p1_xmm[89]);
bs_p1_xmm[90] = tbl_gf256_mul(bs_p2_xmm[90],bs_p1_xmm[90]);
bs_p1_xmm[91] = tbl_gf256_mul(bs_p2_xmm[91],bs_p1_xmm[91]);
bs_p1_xmm[92] = tbl_gf256_mul(bs_p2_xmm[92],bs_p1_xmm[92]);
bs_p1_xmm[93] = tbl_gf256_mul(bs_p2_xmm[93],bs_p1_xmm[93]);
bs_p1_xmm[94] = tbl_gf256_mul(bs_p2_xmm[94],bs_p1_xmm[94]);
bs_p1_xmm[95] = tbl_gf256_mul(bs_p2_xmm[95],bs_p1_xmm[95]);
/// truncated: bs_p1_xmm[96] = tbl_gf256_mul(bs_p2_xmm[96],bs_p1_xmm[96]);
/// truncated: bs_p1_xmm[97] = tbl_gf256_mul(bs_p2_xmm[97],bs_p1_xmm[97]);
/// truncated: bs_p1_xmm[98] = tbl_gf256_mul(bs_p2_xmm[98],bs_p1_xmm[98]);
/// truncated: bs_p1_xmm[99] = tbl_gf256_mul(bs_p2_xmm[99],bs_p1_xmm[99]);
/// truncated: bs_p1_xmm[100] = tbl_gf256_mul(bs_p2_xmm[100],bs_p1_xmm[100]);
/// truncated: bs_p1_xmm[101] = tbl_gf256_mul(bs_p2_xmm[101],bs_p1_xmm[101]);
/// truncated: bs_p1_xmm[102] = tbl_gf256_mul(bs_p2_xmm[102],bs_p1_xmm[102]);
/// truncated: bs_p1_xmm[103] = tbl_gf256_mul(bs_p2_xmm[103],bs_p1_xmm[103]);
/// truncated: bs_p1_xmm[104] = tbl_gf256_mul(bs_p2_xmm[104],bs_p1_xmm[104]);
/// truncated: bs_p1_xmm[105] = tbl_gf256_mul(bs_p2_xmm[105],bs_p1_xmm[105]);
/// truncated: bs_p1_xmm[106] = tbl_gf256_mul(bs_p2_xmm[106],bs_p1_xmm[106]);
/// truncated: bs_p1_xmm[107] = tbl_gf256_mul(bs_p2_xmm[107],bs_p1_xmm[107]);
/// truncated: bs_p1_xmm[108] = tbl_gf256_mul(bs_p2_xmm[108],bs_p1_xmm[108]);
/// truncated: bs_p1_xmm[109] = tbl_gf256_mul(bs_p2_xmm[109],bs_p1_xmm[109]);
/// truncated: bs_p1_xmm[110] = tbl_gf256_mul(bs_p2_xmm[110],bs_p1_xmm[110]);
/// truncated: bs_p1_xmm[111] = tbl_gf256_mul(bs_p2_xmm[111],bs_p1_xmm[111]);
/// truncated: bs_p1_xmm[112] = tbl_gf256_mul(bs_p2_xmm[112],bs_p1_xmm[112]);
/// truncated: bs_p1_xmm[113] = tbl_gf256_mul(bs_p2_xmm[113],bs_p1_xmm[113]);
/// truncated: bs_p1_xmm[114] = tbl_gf256_mul(bs_p2_xmm[114],bs_p1_xmm[114]);
/// truncated: bs_p1_xmm[115] = tbl_gf256_mul(bs_p2_xmm[115],bs_p1_xmm[115]);
/// truncated: bs_p1_xmm[116] = tbl_gf256_mul(bs_p2_xmm[116],bs_p1_xmm[116]);
/// truncated: bs_p1_xmm[117] = tbl_gf256_mul(bs_p2_xmm[117],bs_p1_xmm[117]);
/// truncated: bs_p1_xmm[118] = tbl_gf256_mul(bs_p2_xmm[118],bs_p1_xmm[118]);
/// truncated: bs_p1_xmm[119] = tbl_gf256_mul(bs_p2_xmm[119],bs_p1_xmm[119]);
/// truncated: bs_p1_xmm[120] = tbl_gf256_mul(bs_p2_xmm[120],bs_p1_xmm[120]);
/// truncated: bs_p1_xmm[121] = tbl_gf256_mul(bs_p2_xmm[121],bs_p1_xmm[121]);
/// truncated: bs_p1_xmm[122] = tbl_gf256_mul(bs_p2_xmm[122],bs_p1_xmm[122]);
/// truncated: bs_p1_xmm[123] = tbl_gf256_mul(bs_p2_xmm[123],bs_p1_xmm[123]);
/// truncated: bs_p1_xmm[124] = tbl_gf256_mul(bs_p2_xmm[124],bs_p1_xmm[124]);
/// truncated: bs_p1_xmm[125] = tbl_gf256_mul(bs_p2_xmm[125],bs_p1_xmm[125]);
/// truncated: bs_p1_xmm[126] = tbl_gf256_mul(bs_p2_xmm[126],bs_p1_xmm[126]);
/// truncated: bs_p1_xmm[127] = tbl_gf256_mul(bs_p2_xmm[127],bs_p1_xmm[127]);
//ibutterfly_w0x2( vec[2:0-1], 0x0 )
bs_p1_xmm[1] ^= bs_p1_xmm[0];
//ibutterfly_w0x2( vec[2:2-3], 0x2 )
bs_p1_xmm[3] ^= bs_p1_xmm[2];
temp = bs_p1_xmm[3];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[2] ^= temp;
//ibutterfly_w0x4( vec[4:0-3], 0x0 )
bs_p1_xmm[2] ^= bs_p1_xmm[0];
bs_p1_xmm[3] ^= bs_p1_xmm[1];
//ibutterfly_w0x2( vec[2:4-5], 0x4 )
bs_p1_xmm[5] ^= bs_p1_xmm[4];
temp = bs_p1_xmm[5];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[4] ^= temp;
//ibutterfly_w0x2( vec[2:6-7], 0x6 )
bs_p1_xmm[7] ^= bs_p1_xmm[6];
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[6] ^= temp;
//ibutterfly_w0x4( vec[4:4-7], 0x4 )
bs_p1_xmm[6] ^= bs_p1_xmm[4];
temp = bs_p1_xmm[6];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[4] ^= temp;
bs_p1_xmm[7] ^= bs_p1_xmm[5];
temp = bs_p1_xmm[7];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[5] ^= temp;
//ibutterfly_w0x8( vec[8:0-7], 0x0 )
bs_p1_xmm[4] ^= bs_p1_xmm[0];
bs_p1_xmm[5] ^= bs_p1_xmm[1];
bs_p1_xmm[6] ^= bs_p1_xmm[2];
bs_p1_xmm[7] ^= bs_p1_xmm[3];
//ibutterfly_w0x2( vec[2:8-9], 0x8 )
bs_p1_xmm[9] ^= bs_p1_xmm[8];
temp = bs_p1_xmm[9];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[8] ^= temp;
//ibutterfly_w0x2( vec[2:10-11], 0xa )
bs_p1_xmm[11] ^= bs_p1_xmm[10];
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[10] ^= temp;
//ibutterfly_w0x4( vec[4:8-11], 0x8 )
bs_p1_xmm[10] ^= bs_p1_xmm[8];
temp = bs_p1_xmm[10];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[8] ^= temp;
bs_p1_xmm[11] ^= bs_p1_xmm[9];
temp = bs_p1_xmm[11];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[9] ^= temp;
//ibutterfly_w0x2( vec[2:12-13], 0xc )
bs_p1_xmm[13] ^= bs_p1_xmm[12];
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0xc,temp);
bs_p1_xmm[12] ^= temp;
//ibutterfly_w0x2( vec[2:14-15], 0xe )
bs_p1_xmm[15] ^= bs_p1_xmm[14];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0xe,temp);
bs_p1_xmm[14] ^= temp;
//ibutterfly_w0x4( vec[4:12-15], 0xc )
bs_p1_xmm[14] ^= bs_p1_xmm[12];
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[12] ^= temp;
bs_p1_xmm[15] ^= bs_p1_xmm[13];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[13] ^= temp;
//ibutterfly_w0x8( vec[8:8-15], 0x8 )
bs_p1_xmm[12] ^= bs_p1_xmm[8];
temp = bs_p1_xmm[12];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[8] ^= temp;
bs_p1_xmm[13] ^= bs_p1_xmm[9];
temp = bs_p1_xmm[13];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[9] ^= temp;
bs_p1_xmm[14] ^= bs_p1_xmm[10];
temp = bs_p1_xmm[14];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[10] ^= temp;
bs_p1_xmm[15] ^= bs_p1_xmm[11];
temp = bs_p1_xmm[15];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[11] ^= temp;
//ibutterfly_w0x10( vec[16:0-15], 0x0 )
bs_p1_xmm[8] ^= bs_p1_xmm[0];
bs_p1_xmm[9] ^= bs_p1_xmm[1];
bs_p1_xmm[10] ^= bs_p1_xmm[2];
bs_p1_xmm[11] ^= bs_p1_xmm[3];
bs_p1_xmm[12] ^= bs_p1_xmm[4];
bs_p1_xmm[13] ^= bs_p1_xmm[5];
bs_p1_xmm[14] ^= bs_p1_xmm[6];
bs_p1_xmm[15] ^= bs_p1_xmm[7];
//ibutterfly_w0x2( vec[2:16-17], 0x10 )
bs_p1_xmm[17] ^= bs_p1_xmm[16];
temp = bs_p1_xmm[17];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[16] ^= temp;
//ibutterfly_w0x2( vec[2:18-19], 0x12 )
bs_p1_xmm[19] ^= bs_p1_xmm[18];
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[18] ^= temp;
//ibutterfly_w0x4( vec[4:16-19], 0x10 )
bs_p1_xmm[18] ^= bs_p1_xmm[16];
temp = bs_p1_xmm[18];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[16] ^= temp;
bs_p1_xmm[19] ^= bs_p1_xmm[17];
temp = bs_p1_xmm[19];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[17] ^= temp;
//ibutterfly_w0x2( vec[2:20-21], 0x14 )
bs_p1_xmm[21] ^= bs_p1_xmm[20];
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[20] ^= temp;
//ibutterfly_w0x2( vec[2:22-23], 0x16 )
bs_p1_xmm[23] ^= bs_p1_xmm[22];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[22] ^= temp;
//ibutterfly_w0x4( vec[4:20-23], 0x14 )
bs_p1_xmm[22] ^= bs_p1_xmm[20];
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[20] ^= temp;
bs_p1_xmm[23] ^= bs_p1_xmm[21];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[21] ^= temp;
//ibutterfly_w0x8( vec[8:16-23], 0x10 )
bs_p1_xmm[20] ^= bs_p1_xmm[16];
temp = bs_p1_xmm[20];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[16] ^= temp;
bs_p1_xmm[21] ^= bs_p1_xmm[17];
temp = bs_p1_xmm[21];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[17] ^= temp;
bs_p1_xmm[22] ^= bs_p1_xmm[18];
temp = bs_p1_xmm[22];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[18] ^= temp;
bs_p1_xmm[23] ^= bs_p1_xmm[19];
temp = bs_p1_xmm[23];
temp = tbl_gf256_mul_const(0x5,temp);
bs_p1_xmm[19] ^= temp;
//ibutterfly_w0x2( vec[2:24-25], 0x18 )
bs_p1_xmm[25] ^= bs_p1_xmm[24];
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x18,temp);
bs_p1_xmm[24] ^= temp;
//ibutterfly_w0x2( vec[2:26-27], 0x1a )
bs_p1_xmm[27] ^= bs_p1_xmm[26];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x1a,temp);
bs_p1_xmm[26] ^= temp;
//ibutterfly_w0x4( vec[4:24-27], 0x18 )
bs_p1_xmm[26] ^= bs_p1_xmm[24];
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[24] ^= temp;
bs_p1_xmm[27] ^= bs_p1_xmm[25];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[25] ^= temp;
//ibutterfly_w0x2( vec[2:28-29], 0x1c )
bs_p1_xmm[29] ^= bs_p1_xmm[28];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[28] ^= temp;
//ibutterfly_w0x2( vec[2:30-31], 0x1e )
bs_p1_xmm[31] ^= bs_p1_xmm[30];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[30] ^= temp;
//ibutterfly_w0x4( vec[4:28-31], 0x1c )
bs_p1_xmm[30] ^= bs_p1_xmm[28];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[28] ^= temp;
bs_p1_xmm[31] ^= bs_p1_xmm[29];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[29] ^= temp;
//ibutterfly_w0x8( vec[8:24-31], 0x18 )
bs_p1_xmm[28] ^= bs_p1_xmm[24];
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[24] ^= temp;
bs_p1_xmm[29] ^= bs_p1_xmm[25];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[25] ^= temp;
bs_p1_xmm[30] ^= bs_p1_xmm[26];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[26] ^= temp;
bs_p1_xmm[31] ^= bs_p1_xmm[27];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x7,temp);
bs_p1_xmm[27] ^= temp;
//ibutterfly_w0x10( vec[16:16-31], 0x10 )
bs_p1_xmm[24] ^= bs_p1_xmm[16];
temp = bs_p1_xmm[24];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[16] ^= temp;
bs_p1_xmm[25] ^= bs_p1_xmm[17];
temp = bs_p1_xmm[25];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[17] ^= temp;
bs_p1_xmm[26] ^= bs_p1_xmm[18];
temp = bs_p1_xmm[26];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[18] ^= temp;
bs_p1_xmm[27] ^= bs_p1_xmm[19];
temp = bs_p1_xmm[27];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[19] ^= temp;
bs_p1_xmm[28] ^= bs_p1_xmm[20];
temp = bs_p1_xmm[28];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[20] ^= temp;
bs_p1_xmm[29] ^= bs_p1_xmm[21];
temp = bs_p1_xmm[29];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[21] ^= temp;
bs_p1_xmm[30] ^= bs_p1_xmm[22];
temp = bs_p1_xmm[30];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[22] ^= temp;
bs_p1_xmm[31] ^= bs_p1_xmm[23];
temp = bs_p1_xmm[31];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[23] ^= temp;
//ibutterfly_w0x20( vec[32:0-31], 0x0 )
bs_p1_xmm[16] ^= bs_p1_xmm[0];
bs_p1_xmm[17] ^= bs_p1_xmm[1];
bs_p1_xmm[18] ^= bs_p1_xmm[2];
bs_p1_xmm[19] ^= bs_p1_xmm[3];
bs_p1_xmm[20] ^= bs_p1_xmm[4];
bs_p1_xmm[21] ^= bs_p1_xmm[5];
bs_p1_xmm[22] ^= bs_p1_xmm[6];
bs_p1_xmm[23] ^= bs_p1_xmm[7];
bs_p1_xmm[24] ^= bs_p1_xmm[8];
bs_p1_xmm[25] ^= bs_p1_xmm[9];
bs_p1_xmm[26] ^= bs_p1_xmm[10];
bs_p1_xmm[27] ^= bs_p1_xmm[11];
bs_p1_xmm[28] ^= bs_p1_xmm[12];
bs_p1_xmm[29] ^= bs_p1_xmm[13];
bs_p1_xmm[30] ^= bs_p1_xmm[14];
bs_p1_xmm[31] ^= bs_p1_xmm[15];
//ibutterfly_w0x2( vec[2:32-33], 0x20 )
bs_p1_xmm[33] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[33];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[32] ^= temp;
//ibutterfly_w0x2( vec[2:34-35], 0x22 )
bs_p1_xmm[35] ^= bs_p1_xmm[34];
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[34] ^= temp;
//ibutterfly_w0x4( vec[4:32-35], 0x20 )
bs_p1_xmm[34] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[34];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[35] ^= bs_p1_xmm[33];
temp = bs_p1_xmm[35];
temp = tbl_gf256_mul_const(0x14,temp);
bs_p1_xmm[33] ^= temp;
//ibutterfly_w0x2( vec[2:36-37], 0x24 )
bs_p1_xmm[37] ^= bs_p1_xmm[36];
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0x24,temp);
bs_p1_xmm[36] ^= temp;
//ibutterfly_w0x2( vec[2:38-39], 0x26 )
bs_p1_xmm[39] ^= bs_p1_xmm[38];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x26,temp);
bs_p1_xmm[38] ^= temp;
//ibutterfly_w0x4( vec[4:36-39], 0x24 )
bs_p1_xmm[38] ^= bs_p1_xmm[36];
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[36] ^= temp;
bs_p1_xmm[39] ^= bs_p1_xmm[37];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0x16,temp);
bs_p1_xmm[37] ^= temp;
//ibutterfly_w0x8( vec[8:32-39], 0x20 )
bs_p1_xmm[36] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[36];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[37] ^= bs_p1_xmm[33];
temp = bs_p1_xmm[37];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[33] ^= temp;
bs_p1_xmm[38] ^= bs_p1_xmm[34];
temp = bs_p1_xmm[38];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[34] ^= temp;
bs_p1_xmm[39] ^= bs_p1_xmm[35];
temp = bs_p1_xmm[39];
temp = tbl_gf256_mul_const(0xa,temp);
bs_p1_xmm[35] ^= temp;
//ibutterfly_w0x2( vec[2:40-41], 0x28 )
bs_p1_xmm[41] ^= bs_p1_xmm[40];
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[40] ^= temp;
//ibutterfly_w0x2( vec[2:42-43], 0x2a )
bs_p1_xmm[43] ^= bs_p1_xmm[42];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[42] ^= temp;
//ibutterfly_w0x4( vec[4:40-43], 0x28 )
bs_p1_xmm[42] ^= bs_p1_xmm[40];
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[40] ^= temp;
bs_p1_xmm[43] ^= bs_p1_xmm[41];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x11,temp);
bs_p1_xmm[41] ^= temp;
//ibutterfly_w0x2( vec[2:44-45], 0x2c )
bs_p1_xmm[45] ^= bs_p1_xmm[44];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x2c,temp);
bs_p1_xmm[44] ^= temp;
//ibutterfly_w0x2( vec[2:46-47], 0x2e )
bs_p1_xmm[47] ^= bs_p1_xmm[46];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x2e,temp);
bs_p1_xmm[46] ^= temp;
//ibutterfly_w0x4( vec[4:44-47], 0x2c )
bs_p1_xmm[46] ^= bs_p1_xmm[44];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[44] ^= temp;
bs_p1_xmm[47] ^= bs_p1_xmm[45];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x13,temp);
bs_p1_xmm[45] ^= temp;
//ibutterfly_w0x8( vec[8:40-47], 0x28 )
bs_p1_xmm[44] ^= bs_p1_xmm[40];
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[40] ^= temp;
bs_p1_xmm[45] ^= bs_p1_xmm[41];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[41] ^= temp;
bs_p1_xmm[46] ^= bs_p1_xmm[42];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[42] ^= temp;
bs_p1_xmm[47] ^= bs_p1_xmm[43];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x8,temp);
bs_p1_xmm[43] ^= temp;
//ibutterfly_w0x10( vec[16:32-47], 0x20 )
bs_p1_xmm[40] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[40];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[41] ^= bs_p1_xmm[33];
temp = bs_p1_xmm[41];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[33] ^= temp;
bs_p1_xmm[42] ^= bs_p1_xmm[34];
temp = bs_p1_xmm[42];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[34] ^= temp;
bs_p1_xmm[43] ^= bs_p1_xmm[35];
temp = bs_p1_xmm[43];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[35] ^= temp;
bs_p1_xmm[44] ^= bs_p1_xmm[36];
temp = bs_p1_xmm[44];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[36] ^= temp;
bs_p1_xmm[45] ^= bs_p1_xmm[37];
temp = bs_p1_xmm[45];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[37] ^= temp;
bs_p1_xmm[46] ^= bs_p1_xmm[38];
temp = bs_p1_xmm[46];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[38] ^= temp;
bs_p1_xmm[47] ^= bs_p1_xmm[39];
temp = bs_p1_xmm[47];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[39] ^= temp;
//ibutterfly_w0x2( vec[2:48-49], 0x30 )
bs_p1_xmm[49] ^= bs_p1_xmm[48];
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x30,temp);
bs_p1_xmm[48] ^= temp;
//ibutterfly_w0x2( vec[2:50-51], 0x32 )
bs_p1_xmm[51] ^= bs_p1_xmm[50];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x32,temp);
bs_p1_xmm[50] ^= temp;
//ibutterfly_w0x4( vec[4:48-51], 0x30 )
bs_p1_xmm[50] ^= bs_p1_xmm[48];
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[48] ^= temp;
bs_p1_xmm[51] ^= bs_p1_xmm[49];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x1c,temp);
bs_p1_xmm[49] ^= temp;
//ibutterfly_w0x2( vec[2:52-53], 0x34 )
bs_p1_xmm[53] ^= bs_p1_xmm[52];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x34,temp);
bs_p1_xmm[52] ^= temp;
//ibutterfly_w0x2( vec[2:54-55], 0x36 )
bs_p1_xmm[55] ^= bs_p1_xmm[54];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x36,temp);
bs_p1_xmm[54] ^= temp;
//ibutterfly_w0x4( vec[4:52-55], 0x34 )
bs_p1_xmm[54] ^= bs_p1_xmm[52];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[52] ^= temp;
bs_p1_xmm[55] ^= bs_p1_xmm[53];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x1e,temp);
bs_p1_xmm[53] ^= temp;
//ibutterfly_w0x8( vec[8:48-55], 0x30 )
bs_p1_xmm[52] ^= bs_p1_xmm[48];
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[48] ^= temp;
bs_p1_xmm[53] ^= bs_p1_xmm[49];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[49] ^= temp;
bs_p1_xmm[54] ^= bs_p1_xmm[50];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[50] ^= temp;
bs_p1_xmm[55] ^= bs_p1_xmm[51];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0xf,temp);
bs_p1_xmm[51] ^= temp;
//ibutterfly_w0x2( vec[2:56-57], 0x38 )
bs_p1_xmm[57] ^= bs_p1_xmm[56];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x38,temp);
bs_p1_xmm[56] ^= temp;
//ibutterfly_w0x2( vec[2:58-59], 0x3a )
bs_p1_xmm[59] ^= bs_p1_xmm[58];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x3a,temp);
bs_p1_xmm[58] ^= temp;
//ibutterfly_w0x4( vec[4:56-59], 0x38 )
bs_p1_xmm[58] ^= bs_p1_xmm[56];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[56] ^= temp;
bs_p1_xmm[59] ^= bs_p1_xmm[57];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x19,temp);
bs_p1_xmm[57] ^= temp;
//ibutterfly_w0x2( vec[2:60-61], 0x3c )
bs_p1_xmm[61] ^= bs_p1_xmm[60];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x3c,temp);
bs_p1_xmm[60] ^= temp;
//ibutterfly_w0x2( vec[2:62-63], 0x3e )
bs_p1_xmm[63] ^= bs_p1_xmm[62];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x3e,temp);
bs_p1_xmm[62] ^= temp;
//ibutterfly_w0x4( vec[4:60-63], 0x3c )
bs_p1_xmm[62] ^= bs_p1_xmm[60];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[60] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[61];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x1b,temp);
bs_p1_xmm[61] ^= temp;
//ibutterfly_w0x8( vec[8:56-63], 0x38 )
bs_p1_xmm[60] ^= bs_p1_xmm[56];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[56] ^= temp;
bs_p1_xmm[61] ^= bs_p1_xmm[57];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[57] ^= temp;
bs_p1_xmm[62] ^= bs_p1_xmm[58];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[58] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[59];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0xd,temp);
bs_p1_xmm[59] ^= temp;
//ibutterfly_w0x10( vec[16:48-63], 0x30 )
bs_p1_xmm[56] ^= bs_p1_xmm[48];
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[48] ^= temp;
bs_p1_xmm[57] ^= bs_p1_xmm[49];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[49] ^= temp;
bs_p1_xmm[58] ^= bs_p1_xmm[50];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[50] ^= temp;
bs_p1_xmm[59] ^= bs_p1_xmm[51];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[51] ^= temp;
bs_p1_xmm[60] ^= bs_p1_xmm[52];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[52] ^= temp;
bs_p1_xmm[61] ^= bs_p1_xmm[53];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[53] ^= temp;
bs_p1_xmm[62] ^= bs_p1_xmm[54];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[54] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[55];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x6,temp);
bs_p1_xmm[55] ^= temp;
//ibutterfly_w0x20( vec[32:32-63], 0x20 )
bs_p1_xmm[48] ^= bs_p1_xmm[32];
temp = bs_p1_xmm[48];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[32] ^= temp;
bs_p1_xmm[49] ^= bs_p1_xmm[33];
temp = bs_p1_xmm[49];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[33] ^= temp;
bs_p1_xmm[50] ^= bs_p1_xmm[34];
temp = bs_p1_xmm[50];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[34] ^= temp;
bs_p1_xmm[51] ^= bs_p1_xmm[35];
temp = bs_p1_xmm[51];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[35] ^= temp;
bs_p1_xmm[52] ^= bs_p1_xmm[36];
temp = bs_p1_xmm[52];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[36] ^= temp;
bs_p1_xmm[53] ^= bs_p1_xmm[37];
temp = bs_p1_xmm[53];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[37] ^= temp;
bs_p1_xmm[54] ^= bs_p1_xmm[38];
temp = bs_p1_xmm[54];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[38] ^= temp;
bs_p1_xmm[55] ^= bs_p1_xmm[39];
temp = bs_p1_xmm[55];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[39] ^= temp;
bs_p1_xmm[56] ^= bs_p1_xmm[40];
temp = bs_p1_xmm[56];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[40] ^= temp;
bs_p1_xmm[57] ^= bs_p1_xmm[41];
temp = bs_p1_xmm[57];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[41] ^= temp;
bs_p1_xmm[58] ^= bs_p1_xmm[42];
temp = bs_p1_xmm[58];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[42] ^= temp;
bs_p1_xmm[59] ^= bs_p1_xmm[43];
temp = bs_p1_xmm[59];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[43] ^= temp;
bs_p1_xmm[60] ^= bs_p1_xmm[44];
temp = bs_p1_xmm[60];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[44] ^= temp;
bs_p1_xmm[61] ^= bs_p1_xmm[45];
temp = bs_p1_xmm[61];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[45] ^= temp;
bs_p1_xmm[62] ^= bs_p1_xmm[46];
temp = bs_p1_xmm[62];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[46] ^= temp;
bs_p1_xmm[63] ^= bs_p1_xmm[47];
temp = bs_p1_xmm[63];
temp = tbl_gf256_mul_const(0x2,temp);
bs_p1_xmm[47] ^= temp;
//ibutterfly_w0x40( vec[64:0-63], 0x0 )
bs_p1_xmm[32] ^= bs_p1_xmm[0];
bs_p1_xmm[33] ^= bs_p1_xmm[1];
bs_p1_xmm[34] ^= bs_p1_xmm[2];
bs_p1_xmm[35] ^= bs_p1_xmm[3];
bs_p1_xmm[36] ^= bs_p1_xmm[4];
bs_p1_xmm[37] ^= bs_p1_xmm[5];
bs_p1_xmm[38] ^= bs_p1_xmm[6];
bs_p1_xmm[39] ^= bs_p1_xmm[7];
bs_p1_xmm[40] ^= bs_p1_xmm[8];
bs_p1_xmm[41] ^= bs_p1_xmm[9];
bs_p1_xmm[42] ^= bs_p1_xmm[10];
bs_p1_xmm[43] ^= bs_p1_xmm[11];
bs_p1_xmm[44] ^= bs_p1_xmm[12];
bs_p1_xmm[45] ^= bs_p1_xmm[13];
bs_p1_xmm[46] ^= bs_p1_xmm[14];
bs_p1_xmm[47] ^= bs_p1_xmm[15];
bs_p1_xmm[48] ^= bs_p1_xmm[16];
bs_p1_xmm[49] ^= bs_p1_xmm[17];
bs_p1_xmm[50] ^= bs_p1_xmm[18];
bs_p1_xmm[51] ^= bs_p1_xmm[19];
bs_p1_xmm[52] ^= bs_p1_xmm[20];
bs_p1_xmm[53] ^= bs_p1_xmm[21];
bs_p1_xmm[54] ^= bs_p1_xmm[22];
bs_p1_xmm[55] ^= bs_p1_xmm[23];
bs_p1_xmm[56] ^= bs_p1_xmm[24];
bs_p1_xmm[57] ^= bs_p1_xmm[25];
bs_p1_xmm[58] ^= bs_p1_xmm[26];
bs_p1_xmm[59] ^= bs_p1_xmm[27];
bs_p1_xmm[60] ^= bs_p1_xmm[28];
bs_p1_xmm[61] ^= bs_p1_xmm[29];
bs_p1_xmm[62] ^= bs_p1_xmm[30];
bs_p1_xmm[63] ^= bs_p1_xmm[31];
//ibutterfly_w0x2( vec[2:64-65], 0x40 )
bs_p1_xmm[65] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[65];
temp = tbl_gf256_mul_const(0x40,temp);
bs_p1_xmm[64] ^= temp;
//ibutterfly_w0x2( vec[2:66-67], 0x42 )
bs_p1_xmm[67] ^= bs_p1_xmm[66];
temp = bs_p1_xmm[67];
temp = tbl_gf256_mul_const(0x42,temp);
bs_p1_xmm[66] ^= temp;
//ibutterfly_w0x4( vec[4:64-67], 0x40 )
bs_p1_xmm[66] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[66];
temp = tbl_gf256_mul_const(0x27,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[67] ^= bs_p1_xmm[65];
temp = bs_p1_xmm[67];
temp = tbl_gf256_mul_const(0x27,temp);
bs_p1_xmm[65] ^= temp;
//ibutterfly_w0x2( vec[2:68-69], 0x44 )
bs_p1_xmm[69] ^= bs_p1_xmm[68];
temp = bs_p1_xmm[69];
temp = tbl_gf256_mul_const(0x44,temp);
bs_p1_xmm[68] ^= temp;
//ibutterfly_w0x2( vec[2:70-71], 0x46 )
bs_p1_xmm[71] ^= bs_p1_xmm[70];
temp = bs_p1_xmm[71];
temp = tbl_gf256_mul_const(0x46,temp);
bs_p1_xmm[70] ^= temp;
//ibutterfly_w0x4( vec[4:68-71], 0x44 )
bs_p1_xmm[70] ^= bs_p1_xmm[68];
temp = bs_p1_xmm[70];
temp = tbl_gf256_mul_const(0x25,temp);
bs_p1_xmm[68] ^= temp;
bs_p1_xmm[71] ^= bs_p1_xmm[69];
temp = bs_p1_xmm[71];
temp = tbl_gf256_mul_const(0x25,temp);
bs_p1_xmm[69] ^= temp;
//ibutterfly_w0x8( vec[8:64-71], 0x40 )
bs_p1_xmm[68] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[68];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[69] ^= bs_p1_xmm[65];
temp = bs_p1_xmm[69];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[65] ^= temp;
bs_p1_xmm[70] ^= bs_p1_xmm[66];
temp = bs_p1_xmm[70];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[66] ^= temp;
bs_p1_xmm[71] ^= bs_p1_xmm[67];
temp = bs_p1_xmm[71];
temp = tbl_gf256_mul_const(0x17,temp);
bs_p1_xmm[67] ^= temp;
//ibutterfly_w0x2( vec[2:72-73], 0x48 )
bs_p1_xmm[73] ^= bs_p1_xmm[72];
temp = bs_p1_xmm[73];
temp = tbl_gf256_mul_const(0x48,temp);
bs_p1_xmm[72] ^= temp;
//ibutterfly_w0x2( vec[2:74-75], 0x4a )
bs_p1_xmm[75] ^= bs_p1_xmm[74];
temp = bs_p1_xmm[75];
temp = tbl_gf256_mul_const(0x4a,temp);
bs_p1_xmm[74] ^= temp;
//ibutterfly_w0x4( vec[4:72-75], 0x48 )
bs_p1_xmm[74] ^= bs_p1_xmm[72];
temp = bs_p1_xmm[74];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[72] ^= temp;
bs_p1_xmm[75] ^= bs_p1_xmm[73];
temp = bs_p1_xmm[75];
temp = tbl_gf256_mul_const(0x22,temp);
bs_p1_xmm[73] ^= temp;
//ibutterfly_w0x2( vec[2:76-77], 0x4c )
bs_p1_xmm[77] ^= bs_p1_xmm[76];
temp = bs_p1_xmm[77];
temp = tbl_gf256_mul_const(0x4c,temp);
bs_p1_xmm[76] ^= temp;
//ibutterfly_w0x2( vec[2:78-79], 0x4e )
bs_p1_xmm[79] ^= bs_p1_xmm[78];
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0x4e,temp);
bs_p1_xmm[78] ^= temp;
//ibutterfly_w0x4( vec[4:76-79], 0x4c )
bs_p1_xmm[78] ^= bs_p1_xmm[76];
temp = bs_p1_xmm[78];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[76] ^= temp;
bs_p1_xmm[79] ^= bs_p1_xmm[77];
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0x20,temp);
bs_p1_xmm[77] ^= temp;
//ibutterfly_w0x8( vec[8:72-79], 0x48 )
bs_p1_xmm[76] ^= bs_p1_xmm[72];
temp = bs_p1_xmm[76];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[72] ^= temp;
bs_p1_xmm[77] ^= bs_p1_xmm[73];
temp = bs_p1_xmm[77];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[73] ^= temp;
bs_p1_xmm[78] ^= bs_p1_xmm[74];
temp = bs_p1_xmm[78];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[74] ^= temp;
bs_p1_xmm[79] ^= bs_p1_xmm[75];
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0x15,temp);
bs_p1_xmm[75] ^= temp;
//ibutterfly_w0x10( vec[16:64-79], 0x40 )
bs_p1_xmm[72] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[72];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[73] ^= bs_p1_xmm[65];
temp = bs_p1_xmm[73];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[65] ^= temp;
bs_p1_xmm[74] ^= bs_p1_xmm[66];
temp = bs_p1_xmm[74];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[66] ^= temp;
bs_p1_xmm[75] ^= bs_p1_xmm[67];
temp = bs_p1_xmm[75];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[67] ^= temp;
bs_p1_xmm[76] ^= bs_p1_xmm[68];
temp = bs_p1_xmm[76];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[68] ^= temp;
bs_p1_xmm[77] ^= bs_p1_xmm[69];
temp = bs_p1_xmm[77];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[69] ^= temp;
bs_p1_xmm[78] ^= bs_p1_xmm[70];
temp = bs_p1_xmm[78];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[70] ^= temp;
bs_p1_xmm[79] ^= bs_p1_xmm[71];
temp = bs_p1_xmm[79];
temp = tbl_gf256_mul_const(0xb,temp);
bs_p1_xmm[71] ^= temp;
//ibutterfly_w0x2( vec[2:80-81], 0x50 )
bs_p1_xmm[81] ^= bs_p1_xmm[80];
temp = bs_p1_xmm[81];
temp = tbl_gf256_mul_const(0x50,temp);
bs_p1_xmm[80] ^= temp;
//ibutterfly_w0x2( vec[2:82-83], 0x52 )
bs_p1_xmm[83] ^= bs_p1_xmm[82];
temp = bs_p1_xmm[83];
temp = tbl_gf256_mul_const(0x52,temp);
bs_p1_xmm[82] ^= temp;
//ibutterfly_w0x4( vec[4:80-83], 0x50 )
bs_p1_xmm[82] ^= bs_p1_xmm[80];
temp = bs_p1_xmm[82];
temp = tbl_gf256_mul_const(0x2f,temp);
bs_p1_xmm[80] ^= temp;
bs_p1_xmm[83] ^= bs_p1_xmm[81];
temp = bs_p1_xmm[83];
temp = tbl_gf256_mul_const(0x2f,temp);
bs_p1_xmm[81] ^= temp;
//ibutterfly_w0x2( vec[2:84-85], 0x54 )
bs_p1_xmm[85] ^= bs_p1_xmm[84];
temp = bs_p1_xmm[85];
temp = tbl_gf256_mul_const(0x54,temp);
bs_p1_xmm[84] ^= temp;
//ibutterfly_w0x2( vec[2:86-87], 0x56 )
bs_p1_xmm[87] ^= bs_p1_xmm[86];
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x56,temp);
bs_p1_xmm[86] ^= temp;
//ibutterfly_w0x4( vec[4:84-87], 0x54 )
bs_p1_xmm[86] ^= bs_p1_xmm[84];
temp = bs_p1_xmm[86];
temp = tbl_gf256_mul_const(0x2d,temp);
bs_p1_xmm[84] ^= temp;
bs_p1_xmm[87] ^= bs_p1_xmm[85];
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x2d,temp);
bs_p1_xmm[85] ^= temp;
//ibutterfly_w0x8( vec[8:80-87], 0x50 )
bs_p1_xmm[84] ^= bs_p1_xmm[80];
temp = bs_p1_xmm[84];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[80] ^= temp;
bs_p1_xmm[85] ^= bs_p1_xmm[81];
temp = bs_p1_xmm[85];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[81] ^= temp;
bs_p1_xmm[86] ^= bs_p1_xmm[82];
temp = bs_p1_xmm[86];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[82] ^= temp;
bs_p1_xmm[87] ^= bs_p1_xmm[83];
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x12,temp);
bs_p1_xmm[83] ^= temp;
//ibutterfly_w0x2( vec[2:88-89], 0x58 )
bs_p1_xmm[89] ^= bs_p1_xmm[88];
temp = bs_p1_xmm[89];
temp = tbl_gf256_mul_const(0x58,temp);
bs_p1_xmm[88] ^= temp;
//ibutterfly_w0x2( vec[2:90-91], 0x5a )
bs_p1_xmm[91] ^= bs_p1_xmm[90];
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x5a,temp);
bs_p1_xmm[90] ^= temp;
//ibutterfly_w0x4( vec[4:88-91], 0x58 )
bs_p1_xmm[90] ^= bs_p1_xmm[88];
temp = bs_p1_xmm[90];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[88] ^= temp;
bs_p1_xmm[91] ^= bs_p1_xmm[89];
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x2a,temp);
bs_p1_xmm[89] ^= temp;
//ibutterfly_w0x2( vec[2:92-93], 0x5c )
bs_p1_xmm[93] ^= bs_p1_xmm[92];
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x5c,temp);
bs_p1_xmm[92] ^= temp;
//ibutterfly_w0x2( vec[2:94-95], 0x5e )
bs_p1_xmm[95] ^= bs_p1_xmm[94];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x5e,temp);
bs_p1_xmm[94] ^= temp;
//ibutterfly_w0x4( vec[4:92-95], 0x5c )
bs_p1_xmm[94] ^= bs_p1_xmm[92];
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[92] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[93];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x28,temp);
bs_p1_xmm[93] ^= temp;
//ibutterfly_w0x8( vec[8:88-95], 0x58 )
bs_p1_xmm[92] ^= bs_p1_xmm[88];
temp = bs_p1_xmm[92];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[88] ^= temp;
bs_p1_xmm[93] ^= bs_p1_xmm[89];
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[89] ^= temp;
bs_p1_xmm[94] ^= bs_p1_xmm[90];
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[90] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[91];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x10,temp);
bs_p1_xmm[91] ^= temp;
//ibutterfly_w0x10( vec[16:80-95], 0x50 )
bs_p1_xmm[88] ^= bs_p1_xmm[80];
temp = bs_p1_xmm[88];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[80] ^= temp;
bs_p1_xmm[89] ^= bs_p1_xmm[81];
temp = bs_p1_xmm[89];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[81] ^= temp;
bs_p1_xmm[90] ^= bs_p1_xmm[82];
temp = bs_p1_xmm[90];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[82] ^= temp;
bs_p1_xmm[91] ^= bs_p1_xmm[83];
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[83] ^= temp;
bs_p1_xmm[92] ^= bs_p1_xmm[84];
temp = bs_p1_xmm[92];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[84] ^= temp;
bs_p1_xmm[93] ^= bs_p1_xmm[85];
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[85] ^= temp;
bs_p1_xmm[94] ^= bs_p1_xmm[86];
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[86] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[87];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x9,temp);
bs_p1_xmm[87] ^= temp;
//ibutterfly_w0x20( vec[32:64-95], 0x40 )
bs_p1_xmm[80] ^= bs_p1_xmm[64];
temp = bs_p1_xmm[80];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[64] ^= temp;
bs_p1_xmm[81] ^= bs_p1_xmm[65];
temp = bs_p1_xmm[81];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[65] ^= temp;
bs_p1_xmm[82] ^= bs_p1_xmm[66];
temp = bs_p1_xmm[82];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[66] ^= temp;
bs_p1_xmm[83] ^= bs_p1_xmm[67];
temp = bs_p1_xmm[83];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[67] ^= temp;
bs_p1_xmm[84] ^= bs_p1_xmm[68];
temp = bs_p1_xmm[84];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[68] ^= temp;
bs_p1_xmm[85] ^= bs_p1_xmm[69];
temp = bs_p1_xmm[85];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[69] ^= temp;
bs_p1_xmm[86] ^= bs_p1_xmm[70];
temp = bs_p1_xmm[86];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[70] ^= temp;
bs_p1_xmm[87] ^= bs_p1_xmm[71];
temp = bs_p1_xmm[87];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[71] ^= temp;
bs_p1_xmm[88] ^= bs_p1_xmm[72];
temp = bs_p1_xmm[88];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[72] ^= temp;
bs_p1_xmm[89] ^= bs_p1_xmm[73];
temp = bs_p1_xmm[89];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[73] ^= temp;
bs_p1_xmm[90] ^= bs_p1_xmm[74];
temp = bs_p1_xmm[90];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[74] ^= temp;
bs_p1_xmm[91] ^= bs_p1_xmm[75];
temp = bs_p1_xmm[91];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[75] ^= temp;
bs_p1_xmm[92] ^= bs_p1_xmm[76];
temp = bs_p1_xmm[92];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[76] ^= temp;
bs_p1_xmm[93] ^= bs_p1_xmm[77];
temp = bs_p1_xmm[93];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[77] ^= temp;
bs_p1_xmm[94] ^= bs_p1_xmm[78];
temp = bs_p1_xmm[94];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[78] ^= temp;
bs_p1_xmm[95] ^= bs_p1_xmm[79];
temp = bs_p1_xmm[95];
temp = tbl_gf256_mul_const(0x4,temp);
bs_p1_xmm[79] ^= temp;
//ibutterfly_w0x2( vec[2:96-97], 0x60 )
/// truncated: bs_p1_xmm[97] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[97]:0x5 ,0? False, omit? True
temp = bs_p1_xmm[97];
/// omit x const: //temp:0x80 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x60,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
//ibutterfly_w0x2( vec[2:98-99], 0x62 )
/// truncated: bs_p1_xmm[99] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[99]:0x8d ,0? False, omit? True
temp = bs_p1_xmm[99];
/// omit x const: //temp:0x49 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x62,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
//ibutterfly_w0x4( vec[4:96-99], 0x60 )
/// truncated: bs_p1_xmm[98] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[98]:0xd3 ,0? False, omit? True
temp = bs_p1_xmm[98];
/// omit x const: //temp:0x2b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x33,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[99] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[99]:0x88 ,0? False, omit? True
temp = bs_p1_xmm[99];
/// omit x const: //temp:0x4f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x33,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
//ibutterfly_w0x2( vec[2:100-101], 0x64 )
/// truncated: bs_p1_xmm[101] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[101]:0xcb ,0? False, omit? True
temp = bs_p1_xmm[101];
/// omit x const: //temp:0xe2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x64,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
//ibutterfly_w0x2( vec[2:102-103], 0x66 )
/// truncated: bs_p1_xmm[103] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[103]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x61 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x66,temp);
/// truncated: bs_p1_xmm[102] ^= temp;
//ibutterfly_w0x4( vec[4:100-103], 0x64 )
/// truncated: bs_p1_xmm[102] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[102]:0x31 ,0? False, omit? True
temp = bs_p1_xmm[102];
/// omit x const: //temp:0x2d ,0? False, omit? True
temp = tbl_gf256_mul_const(0x31,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
/// truncated: bs_p1_xmm[103] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[103]:0xda ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x33 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x31,temp);
/// truncated: bs_p1_xmm[101] ^= temp;
//ibutterfly_w0x8( vec[8:96-103], 0x60 )
/// truncated: bs_p1_xmm[100] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[100]:0xd2 ,0? False, omit? True
temp = bs_p1_xmm[100];
/// omit x const: //temp:0x58 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[101] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[101]:0xb2 ,0? False, omit? True
temp = bs_p1_xmm[101];
/// omit x const: //temp:0xcf ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
/// truncated: bs_p1_xmm[102] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[102]:0xe2 ,0? False, omit? True
temp = bs_p1_xmm[102];
/// omit x const: //temp:0xdc ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
/// truncated: bs_p1_xmm[103] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[103]:0x52 ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x35 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1d,temp);
/// truncated: bs_p1_xmm[99] ^= temp;
//ibutterfly_w0x2( vec[2:104-105], 0x68 )
/// truncated: bs_p1_xmm[105] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[105]:0x93 ,0? False, omit? True
temp = bs_p1_xmm[105];
/// omit x const: //temp:0x9c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x68,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
//ibutterfly_w0x2( vec[2:106-107], 0x6a )
/// truncated: bs_p1_xmm[107] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[107]:0x72 ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0xeb ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6a,temp);
/// truncated: bs_p1_xmm[106] ^= temp;
//ibutterfly_w0x4( vec[4:104-107], 0x68 )
/// truncated: bs_p1_xmm[106] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[106]:0xe5 ,0? False, omit? True
temp = bs_p1_xmm[106];
/// omit x const: //temp:0x4d ,0? False, omit? True
temp = tbl_gf256_mul_const(0x36,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
/// truncated: bs_p1_xmm[107] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[107]:0xe1 ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0x83 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x36,temp);
/// truncated: bs_p1_xmm[105] ^= temp;
//ibutterfly_w0x2( vec[2:108-109], 0x6c )
/// truncated: bs_p1_xmm[109] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[109]:0x9d ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0x4f ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6c,temp);
/// truncated: bs_p1_xmm[108] ^= temp;
//ibutterfly_w0x2( vec[2:110-111], 0x6e )
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[110];
/// interaction with truncated: //bs_p1_xmm[111]:0xbe ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0xb9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6e,temp);
/// truncated: bs_p1_xmm[110] ^= temp;
//ibutterfly_w0x4( vec[4:108-111], 0x6c )
/// truncated: bs_p1_xmm[110] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[110]:0x1c ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0xf9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x34,temp);
/// truncated: bs_p1_xmm[108] ^= temp;
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[109];
/// interaction with truncated: //bs_p1_xmm[111]:0x23 ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0xb4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x34,temp);
/// truncated: bs_p1_xmm[109] ^= temp;
//ibutterfly_w0x8( vec[8:104-111], 0x68 )
/// truncated: bs_p1_xmm[108] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[108]:0xc9 ,0? False, omit? True
temp = bs_p1_xmm[108];
/// omit x const: //temp:0x6b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
/// truncated: bs_p1_xmm[109] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[109]:0x39 ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0x9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[105] ^= temp;
/// truncated: bs_p1_xmm[110] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[110]:0xf9 ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0xff ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[106] ^= temp;
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[107];
/// interaction with truncated: //bs_p1_xmm[111]:0xc2 ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0xd3 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1f,temp);
/// truncated: bs_p1_xmm[107] ^= temp;
//ibutterfly_w0x10( vec[16:96-111], 0x60 )
/// truncated: bs_p1_xmm[104] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[104]:0x12 ,0? False, omit? True
temp = bs_p1_xmm[104];
/// omit x const: //temp:0xf5 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[105] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[105]:0x9c ,0? False, omit? True
temp = bs_p1_xmm[105];
/// omit x const: //temp:0xd3 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
/// truncated: bs_p1_xmm[106] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[106]:0x15 ,0? False, omit? True
temp = bs_p1_xmm[106];
/// omit x const: //temp:0xfe ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
/// truncated: bs_p1_xmm[107] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[107]:0x8f ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0x29 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[99] ^= temp;
/// truncated: bs_p1_xmm[108] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[108]:0x1b ,0? False, omit? True
temp = bs_p1_xmm[108];
/// omit x const: //temp:0xf8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
/// truncated: bs_p1_xmm[109] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[109]:0x8b ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0x28 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[101] ^= temp;
/// truncated: bs_p1_xmm[110] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[110]:0x1b ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0xf8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[102] ^= temp;
/// truncated: bs_p1_xmm[111] ^= bs_p1_xmm[103];
/// interaction with truncated: //bs_p1_xmm[111]:0x90 ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0xd0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xf,temp);
/// truncated: bs_p1_xmm[103] ^= temp;
//ibutterfly_w0x2( vec[2:112-113], 0x70 )
/// truncated: bs_p1_xmm[113] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[113]:0xa3 ,0? False, omit? True
temp = bs_p1_xmm[113];
/// omit x const: //temp:0x87 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x70,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
//ibutterfly_w0x2( vec[2:114-115], 0x72 )
/// truncated: bs_p1_xmm[115] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[115]:0x8d ,0? False, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0x14 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x72,temp);
/// truncated: bs_p1_xmm[114] ^= temp;
//ibutterfly_w0x4( vec[4:112-115], 0x70 )
/// truncated: bs_p1_xmm[114] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[114]:0xc2 ,0? False, omit? True
temp = bs_p1_xmm[114];
/// omit x const: //temp:0x70 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3b,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
/// truncated: bs_p1_xmm[115] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[115]:0x2e ,0? False, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0x5b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3b,temp);
/// truncated: bs_p1_xmm[113] ^= temp;
//ibutterfly_w0x2( vec[2:116-117], 0x74 )
/// truncated: bs_p1_xmm[117] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[117]:0x56 ,0? False, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0xc0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x74,temp);
/// truncated: bs_p1_xmm[116] ^= temp;
//ibutterfly_w0x2( vec[2:118-119], 0x76 )
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[118];
/// interaction with truncated: //bs_p1_xmm[119]:0x84 ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x2c ,0? False, omit? True
temp = tbl_gf256_mul_const(0x76,temp);
/// truncated: bs_p1_xmm[118] ^= temp;
//ibutterfly_w0x4( vec[4:116-119], 0x74 )
/// truncated: bs_p1_xmm[118] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[118]:0x5 ,0? False, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0xf6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x39,temp);
/// truncated: bs_p1_xmm[116] ^= temp;
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[117];
/// interaction with truncated: //bs_p1_xmm[119]:0xd2 ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x97 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x39,temp);
/// truncated: bs_p1_xmm[117] ^= temp;
//ibutterfly_w0x8( vec[8:112-119], 0x70 )
/// truncated: bs_p1_xmm[116] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[116]:0xf5 ,0? False, omit? True
temp = bs_p1_xmm[116];
/// omit x const: //temp:0x81 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
/// truncated: bs_p1_xmm[117] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[117]:0x39 ,0? False, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0xe1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[113] ^= temp;
/// truncated: bs_p1_xmm[118] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[118]:0xc7 ,0? False, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0xd9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[114] ^= temp;
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[115];
/// interaction with truncated: //bs_p1_xmm[119]:0xfc ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x14 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x18,temp);
/// truncated: bs_p1_xmm[115] ^= temp;
//ibutterfly_w0x2( vec[2:120-121], 0x78 )
/// truncated: bs_p1_xmm[121] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[121]:0xc5 ,0? False, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0xe0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x78,temp);
/// truncated: bs_p1_xmm[120] ^= temp;
//ibutterfly_w0x2( vec[2:122-123], 0x7a )
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[122];
/// interaction with truncated: //bs_p1_xmm[123]:0x22 ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0xfa ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7a,temp);
/// truncated: bs_p1_xmm[122] ^= temp;
//ibutterfly_w0x4( vec[4:120-123], 0x78 )
/// truncated: bs_p1_xmm[122] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[122]:0xca ,0? False, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0x20 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3e,temp);
/// truncated: bs_p1_xmm[120] ^= temp;
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[121];
/// interaction with truncated: //bs_p1_xmm[123]:0xe7 ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0xf9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3e,temp);
/// truncated: bs_p1_xmm[121] ^= temp;
//ibutterfly_w0x2( vec[2:124-125], 0x7c )
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[124];
/// interaction with truncated: //bs_p1_xmm[125]:0x31 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0x16 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7c,temp);
/// truncated: bs_p1_xmm[124] ^= temp;
//ibutterfly_w0x2( vec[2:126-127], 0x7e )
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[126];
/// interaction with truncated: //bs_p1_xmm[127]:0x96 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0xff ,0? False, omit? True
temp = tbl_gf256_mul_const(0x7e,temp);
/// truncated: bs_p1_xmm[126] ^= temp;
//ibutterfly_w0x4( vec[4:124-127], 0x7c )
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[124];
/// interaction with truncated: //bs_p1_xmm[126]:0x13 ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0xdc ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3c,temp);
/// truncated: bs_p1_xmm[124] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[125];
/// interaction with truncated: //bs_p1_xmm[127]:0xa7 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x96 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x3c,temp);
/// truncated: bs_p1_xmm[125] ^= temp;
//ibutterfly_w0x8( vec[8:120-127], 0x78 )
/// truncated: bs_p1_xmm[124] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[124]:0xeb ,0? False, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0x8e ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[120] ^= temp;
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[121];
/// interaction with truncated: //bs_p1_xmm[125]:0x9b ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0x91 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[121] ^= temp;
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[122];
/// interaction with truncated: //bs_p1_xmm[126]:0xd9 ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0xc5 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[122] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[123];
/// interaction with truncated: //bs_p1_xmm[127]:0x40 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x7b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x1a,temp);
/// truncated: bs_p1_xmm[123] ^= temp;
//ibutterfly_w0x10( vec[16:112-127], 0x70 )
/// truncated: bs_p1_xmm[120] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[120]:0x15 ,0? False, omit? True
temp = bs_p1_xmm[120];
/// omit x const: //temp:0xd4 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[112] ^= temp;
/// truncated: bs_p1_xmm[121] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[121]:0xb4 ,0? False, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0x59 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[113] ^= temp;
/// truncated: bs_p1_xmm[122] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[122]:0x14 ,0? False, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0xd9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[114] ^= temp;
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[115];
/// interaction with truncated: //bs_p1_xmm[123]:0xa6 ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0x8f ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[115] ^= temp;
/// truncated: bs_p1_xmm[124] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[124]:0x1e ,0? False, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0xd1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[116] ^= temp;
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[117];
/// interaction with truncated: //bs_p1_xmm[125]:0xa2 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0x86 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[117] ^= temp;
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[118];
/// interaction with truncated: //bs_p1_xmm[126]:0x1e ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0xd1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[118] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[119];
/// interaction with truncated: //bs_p1_xmm[127]:0xbc ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x57 ,0? False, omit? True
temp = tbl_gf256_mul_const(0xd,temp);
/// truncated: bs_p1_xmm[119] ^= temp;
//ibutterfly_w0x20( vec[32:96-127], 0x60 )
/// truncated: bs_p1_xmm[112] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[112]:0xb ,0? False, omit? True
temp = bs_p1_xmm[112];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[96] ^= temp;
/// truncated: bs_p1_xmm[113] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[113]:0x16 ,0? False, omit? True
temp = bs_p1_xmm[113];
/// omit x const: //temp:0x65 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[97] ^= temp;
/// truncated: bs_p1_xmm[114] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[114]:0x33 ,0? False, omit? True
temp = bs_p1_xmm[114];
/// omit x const: //temp:0xdd ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[98] ^= temp;
/// truncated: bs_p1_xmm[115] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[115]:0x21 ,0? False, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0xb6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[99] ^= temp;
/// truncated: bs_p1_xmm[116] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[116]:0xe ,0? False, omit? True
temp = bs_p1_xmm[116];
/// omit x const: //temp:0x2 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[100] ^= temp;
/// truncated: bs_p1_xmm[117] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[117]:0x25 ,0? False, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0xb8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[101] ^= temp;
/// truncated: bs_p1_xmm[118] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[118]:0xc ,0? False, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0x9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[102] ^= temp;
/// truncated: bs_p1_xmm[119] ^= bs_p1_xmm[103];
/// interaction with truncated: //bs_p1_xmm[119]:0x29 ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0xb1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[103] ^= temp;
/// truncated: bs_p1_xmm[120] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[120]:0x7 ,0? False, omit? True
temp = bs_p1_xmm[120];
/// omit x const: //temp:0x3 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[104] ^= temp;
/// truncated: bs_p1_xmm[121] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[121]:0x28 ,0? False, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0xb7 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[105] ^= temp;
/// truncated: bs_p1_xmm[122] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[122]:0x1 ,0? False, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0x6 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[106] ^= temp;
/// truncated: bs_p1_xmm[123] ^= bs_p1_xmm[107];
/// interaction with truncated: //bs_p1_xmm[123]:0x29 ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0xb1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[107] ^= temp;
/// truncated: bs_p1_xmm[124] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[124]:0x5 ,0? False, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0x8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[108] ^= temp;
/// truncated: bs_p1_xmm[125] ^= bs_p1_xmm[109];
/// interaction with truncated: //bs_p1_xmm[125]:0x29 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0xb1 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[109] ^= temp;
/// truncated: bs_p1_xmm[126] ^= bs_p1_xmm[110];
/// interaction with truncated: //bs_p1_xmm[126]:0x5 ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0x8 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[110] ^= temp;
/// truncated: bs_p1_xmm[127] ^= bs_p1_xmm[111];
/// interaction with truncated: //bs_p1_xmm[127]:0x2c ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0xb9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x6,temp);
/// truncated: bs_p1_xmm[111] ^= temp;



for(unsigned i=96;i<128;i++) bs_p1_xmm[i] = bs_p1_xmm[i-64];


//ibutterfly_w0x40( vec[64:64-127], 0x40 )
/// interaction with truncated: //bs_p1_xmm[96]:0x19 ,0? False, omit? True
///// bs_p1_xmm[96] ^= bs_p1_xmm[64];
/// interaction with truncated: //bs_p1_xmm[96]:0x19 ,0? False, omit? True
temp = bs_p1_xmm[96];
/// omit x const: //temp:0x2e ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2e ,0? False, omit? True
bs_p1_xmm[64] ^= temp;
/// interaction with truncated: //bs_p1_xmm[97]:0x9 ,0? False, omit? True
///// bs_p1_xmm[97] ^= bs_p1_xmm[65];
/// interaction with truncated: //bs_p1_xmm[97]:0x9 ,0? False, omit? True
temp = bs_p1_xmm[97];
/// omit x const: //temp:0xe ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0xe ,0? False, omit? True
bs_p1_xmm[65] ^= temp;
/// interaction with truncated: //bs_p1_xmm[98]:0x1f ,0? False, omit? True
//// bs_p1_xmm[98] ^= bs_p1_xmm[66];
/// interaction with truncated: //bs_p1_xmm[98]:0x1f ,0? False, omit? True
temp = bs_p1_xmm[98];
/// omit x const: //temp:0x25 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x25 ,0? False, omit? True
bs_p1_xmm[66] ^= temp;
/// interaction with truncated: //bs_p1_xmm[99]:0x11 ,0? False, omit? True
///// bs_p1_xmm[99] ^= bs_p1_xmm[67];
/// interaction with truncated: //bs_p1_xmm[99]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[99];
/// omit x const: //temp:0x22 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x22 ,0? False, omit? True
bs_p1_xmm[67] ^= temp;
/// interaction with truncated: //bs_p1_xmm[100]:0x21 ,0? False, omit? True
///// bs_p1_xmm[100] ^= bs_p1_xmm[68];
/// interaction with truncated: //bs_p1_xmm[100]:0x21 ,0? False, omit? True
temp = bs_p1_xmm[100];
/// omit x const: //temp:0x32 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x32 ,0? False, omit? True
bs_p1_xmm[68] ^= temp;
/// interaction with truncated: //bs_p1_xmm[101]:0x16 ,0? False, omit? True
//// bs_p1_xmm[101] ^= bs_p1_xmm[69];
/// interaction with truncated: //bs_p1_xmm[101]:0x16 ,0? False, omit? True
temp = bs_p1_xmm[101];
/// omit x const: //temp:0x2b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2b ,0? False, omit? True
bs_p1_xmm[69] ^= temp;
/// interaction with truncated: //bs_p1_xmm[102]:0x20 ,0? False, omit? True
//// bs_p1_xmm[102] ^= bs_p1_xmm[70];
/// interaction with truncated: //bs_p1_xmm[102]:0x20 ,0? False, omit? True
temp = bs_p1_xmm[102];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p1_xmm[70] ^= temp;
/// interaction with truncated: //bs_p1_xmm[103]:0x34 ,0? False, omit? True
//// bs_p1_xmm[103] ^= bs_p1_xmm[71];
/// interaction with truncated: //bs_p1_xmm[103]:0x34 ,0? False, omit? True
temp = bs_p1_xmm[103];
/// omit x const: //temp:0x18 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x18 ,0? False, omit? True
bs_p1_xmm[71] ^= temp;
/// interaction with truncated: //bs_p1_xmm[104]:0x22 ,0? False, omit? True
///// bs_p1_xmm[104] ^= bs_p1_xmm[72];
/// interaction with truncated: //bs_p1_xmm[104]:0x22 ,0? False, omit? True
temp = bs_p1_xmm[104];
/// omit x const: //temp:0x33 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x33 ,0? False, omit? True
bs_p1_xmm[72] ^= temp;
/// interaction with truncated: //bs_p1_xmm[105]:0x12 ,0? False, omit? True
///// bs_p1_xmm[105] ^= bs_p1_xmm[73];
/// interaction with truncated: //bs_p1_xmm[105]:0x12 ,0? False, omit? True
temp = bs_p1_xmm[105];
/// omit x const: //temp:0x23 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x23 ,0? False, omit? True
bs_p1_xmm[73] ^= temp;
/// interaction with truncated: //bs_p1_xmm[106]:0x20 ,0? False, omit? True
///// bs_p1_xmm[106] ^= bs_p1_xmm[74];
/// interaction with truncated: //bs_p1_xmm[106]:0x20 ,0? False, omit? True
temp = bs_p1_xmm[106];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p1_xmm[74] ^= temp;
/// interaction with truncated: //bs_p1_xmm[107]:0x33 ,0? False, omit? True
///// bs_p1_xmm[107] ^= bs_p1_xmm[75];
/// interaction with truncated: //bs_p1_xmm[107]:0x33 ,0? False, omit? True
temp = bs_p1_xmm[107];
/// omit x const: //temp:0x11 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x11 ,0? False, omit? True
bs_p1_xmm[75] ^= temp;
/// interaction with truncated: //bs_p1_xmm[108]:0x20 ,0? False, omit? True
///// bs_p1_xmm[108] ^= bs_p1_xmm[76];
/// interaction with truncated: //bs_p1_xmm[108]:0x20 ,0? False, omit? True
temp = bs_p1_xmm[108];
/// omit x const: //temp:0x30 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x30 ,0? False, omit? True
bs_p1_xmm[76] ^= temp;
/// interaction with truncated: //bs_p1_xmm[109]:0x31 ,0? False, omit? True
///// bs_p1_xmm[109] ^= bs_p1_xmm[77];
/// interaction with truncated: //bs_p1_xmm[109]:0x31 ,0? False, omit? True
temp = bs_p1_xmm[109];
/// omit x const: //temp:0x12 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x12 ,0? False, omit? True
bs_p1_xmm[77] ^= temp;
/// interaction with truncated: //bs_p1_xmm[110]:0x21 ,0? False, omit? True
///// bs_p1_xmm[110] ^= bs_p1_xmm[78];
/// interaction with truncated: //bs_p1_xmm[110]:0x21 ,0? False, omit? True
temp = bs_p1_xmm[110];
/// omit x const: //temp:0x32 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x32 ,0? False, omit? True
bs_p1_xmm[78] ^= temp;
/// interaction with truncated: //bs_p1_xmm[111]:0x11 ,0? False, omit? True
///// bs_p1_xmm[111] ^= bs_p1_xmm[79];
/// interaction with truncated: //bs_p1_xmm[111]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[111];
/// omit x const: //temp:0x22 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x22 ,0? False, omit? True
bs_p1_xmm[79] ^= temp;
/// interaction with truncated: //bs_p1_xmm[112]:0x15 ,0? False, omit? True
///// bs_p1_xmm[112] ^= bs_p1_xmm[80];
/// interaction with truncated: //bs_p1_xmm[112]:0x15 ,0? False, omit? True
temp = bs_p1_xmm[112];
/// omit x const: //temp:0x2a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2a ,0? False, omit? True
bs_p1_xmm[80] ^= temp;
/// interaction with truncated: //bs_p1_xmm[113]:0x15 ,0? False, omit? True
///// bs_p1_xmm[113] ^= bs_p1_xmm[81];
/// interaction with truncated: //bs_p1_xmm[113]:0x15 ,0? False, omit? True
temp = bs_p1_xmm[113];
/// omit x const: //temp:0x2a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2a ,0? False, omit? True
bs_p1_xmm[81] ^= temp;
/// interaction with truncated: //bs_p1_xmm[114]:0x11 ,0? False, omit? True
///// bs_p1_xmm[114] ^= bs_p1_xmm[82];
/// interaction with truncated: //bs_p1_xmm[114]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[114];
/// omit x const: //temp:0x22 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x22 ,0? False, omit? True
bs_p1_xmm[82] ^= temp;
/// interaction with truncated: //bs_p1_xmm[115]:0x7 ,0? False, omit? True
///// bs_p1_xmm[115] ^= bs_p1_xmm[83];
/// interaction with truncated: //bs_p1_xmm[115]:0x7 ,0? False, omit? True
temp = bs_p1_xmm[115];
/// omit x const: //temp:0x9 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x9 ,0? False, omit? True
bs_p1_xmm[83] ^= temp;
/// interaction with truncated: //bs_p1_xmm[116]:0x16 ,0? False, omit? True
///// bs_p1_xmm[116] ^= bs_p1_xmm[84];
/// interaction with truncated: //bs_p1_xmm[116]:0x16 ,0? False, omit? True
temp = bs_p1_xmm[116];
/// omit x const: //temp:0x2b ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2b ,0? False, omit? True
bs_p1_xmm[84] ^= temp;
/// interaction with truncated: //bs_p1_xmm[117]:0x5 ,0? False, omit? True
///// bs_p1_xmm[117] ^= bs_p1_xmm[85];
/// interaction with truncated: //bs_p1_xmm[117]:0x5 ,0? False, omit? True
temp = bs_p1_xmm[117];
/// omit x const: //temp:0xa ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0xa ,0? False, omit? True
bs_p1_xmm[85] ^= temp;
/// interaction with truncated: //bs_p1_xmm[118]:0x15 ,0? False, omit? True
///// bs_p1_xmm[118] ^= bs_p1_xmm[86];
/// interaction with truncated: //bs_p1_xmm[118]:0x15 ,0? False, omit? True
temp = bs_p1_xmm[118];
/// omit x const: //temp:0x2a ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x2a ,0? False, omit? True
bs_p1_xmm[86] ^= temp;
/// interaction with truncated: //bs_p1_xmm[119]:0x11 ,0? False, omit? True
///// bs_p1_xmm[119] ^= bs_p1_xmm[87];
/// interaction with truncated: //bs_p1_xmm[119]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[119];
/// omit x const: //temp:0x22 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x22 ,0? False, omit? True
bs_p1_xmm[87] ^= temp;
/// interaction with truncated: //bs_p1_xmm[120]:0x12 ,0? False, omit? True
///// bs_p1_xmm[120] ^= bs_p1_xmm[88];
/// interaction with truncated: //bs_p1_xmm[120]:0x12 ,0? False, omit? True
temp = bs_p1_xmm[120];
/// omit x const: //temp:0x23 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x23 ,0? False, omit? True
bs_p1_xmm[88] ^= temp;
/// interaction with truncated: //bs_p1_xmm[121]:0x2 ,0? False, omit? True
///// bs_p1_xmm[121] ^= bs_p1_xmm[89];
/// interaction with truncated: //bs_p1_xmm[121]:0x2 ,0? False, omit? True
temp = bs_p1_xmm[121];
/// omit x const: //temp:0x3 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x3 ,0? False, omit? True
bs_p1_xmm[89] ^= temp;
/// interaction with truncated: //bs_p1_xmm[122]:0x12 ,0? False, omit? True
///// bs_p1_xmm[122] ^= bs_p1_xmm[90];
/// interaction with truncated: //bs_p1_xmm[122]:0x12 ,0? False, omit? True
temp = bs_p1_xmm[122];
/// omit x const: //temp:0x23 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x23 ,0? False, omit? True
bs_p1_xmm[90] ^= temp;
/// interaction with truncated: //bs_p1_xmm[123]:0x11 ,0? False, omit? True
///// bs_p1_xmm[123] ^= bs_p1_xmm[91];
/// interaction with truncated: //bs_p1_xmm[123]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[123];
/// omit x const: //temp:0x22 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x22 ,0? False, omit? True
bs_p1_xmm[91] ^= temp;
/// interaction with truncated: //bs_p1_xmm[124]:0x10 ,0? False, omit? True
///// bs_p1_xmm[124] ^= bs_p1_xmm[92];
/// interaction with truncated: //bs_p1_xmm[124]:0x10 ,0? False, omit? True
temp = bs_p1_xmm[124];
/// omit x const: //temp:0x20 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x20 ,0? False, omit? True
bs_p1_xmm[92] ^= temp;
/// interaction with truncated: //bs_p1_xmm[125]:0x11 ,0? False, omit? True
///// bs_p1_xmm[125] ^= bs_p1_xmm[93];
/// interaction with truncated: //bs_p1_xmm[125]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[125];
/// omit x const: //temp:0x22 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x22 ,0? False, omit? True
bs_p1_xmm[93] ^= temp;
/// interaction with truncated: //bs_p1_xmm[126]:0x11 ,0? False, omit? True
///// bs_p1_xmm[126] ^= bs_p1_xmm[94];
/// interaction with truncated: //bs_p1_xmm[126]:0x11 ,0? False, omit? True
temp = bs_p1_xmm[126];
/// omit x const: //temp:0x22 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x22 ,0? False, omit? True
bs_p1_xmm[94] ^= temp;
/// interaction with truncated: //bs_p1_xmm[127]:0x0 ,0? False, omit? True
///// bs_p1_xmm[127] ^= bs_p1_xmm[95];
/// interaction with truncated: //bs_p1_xmm[127]:0x0 ,0? False, omit? True
temp = bs_p1_xmm[127];
/// omit x const: //temp:0x0 ,0? False, omit? True
temp = tbl_gf256_mul_const(0x2,temp);
/// interaction with truncated: //temp:0x0 ,0? False, omit? True
bs_p1_xmm[95] ^= temp;



//ibutterfly_w0x80( vec[128:0-127], 0x0 )
bs_p1_xmm[64] ^= bs_p1_xmm[0];
bs_p1_xmm[65] ^= bs_p1_xmm[1];
bs_p1_xmm[66] ^= bs_p1_xmm[2];
bs_p1_xmm[67] ^= bs_p1_xmm[3];
bs_p1_xmm[68] ^= bs_p1_xmm[4];
bs_p1_xmm[69] ^= bs_p1_xmm[5];
bs_p1_xmm[70] ^= bs_p1_xmm[6];
bs_p1_xmm[71] ^= bs_p1_xmm[7];
bs_p1_xmm[72] ^= bs_p1_xmm[8];
bs_p1_xmm[73] ^= bs_p1_xmm[9];
bs_p1_xmm[74] ^= bs_p1_xmm[10];
bs_p1_xmm[75] ^= bs_p1_xmm[11];
bs_p1_xmm[76] ^= bs_p1_xmm[12];
bs_p1_xmm[77] ^= bs_p1_xmm[13];
bs_p1_xmm[78] ^= bs_p1_xmm[14];
bs_p1_xmm[79] ^= bs_p1_xmm[15];
bs_p1_xmm[80] ^= bs_p1_xmm[16];
bs_p1_xmm[81] ^= bs_p1_xmm[17];
bs_p1_xmm[82] ^= bs_p1_xmm[18];
bs_p1_xmm[83] ^= bs_p1_xmm[19];
bs_p1_xmm[84] ^= bs_p1_xmm[20];
bs_p1_xmm[85] ^= bs_p1_xmm[21];
bs_p1_xmm[86] ^= bs_p1_xmm[22];
bs_p1_xmm[87] ^= bs_p1_xmm[23];
bs_p1_xmm[88] ^= bs_p1_xmm[24];
bs_p1_xmm[89] ^= bs_p1_xmm[25];
bs_p1_xmm[90] ^= bs_p1_xmm[26];
bs_p1_xmm[91] ^= bs_p1_xmm[27];
bs_p1_xmm[92] ^= bs_p1_xmm[28];
bs_p1_xmm[93] ^= bs_p1_xmm[29];
bs_p1_xmm[94] ^= bs_p1_xmm[30];
bs_p1_xmm[95] ^= bs_p1_xmm[31];

#if 0
/// interaction with truncated: //bs_p1_xmm[96]:0x0 ,0? False, omit? True
bs_p1_xmm[96] ^= bs_p1_xmm[32];
/// interaction with truncated: //bs_p1_xmm[97]:0x0 ,0? False, omit? True
bs_p1_xmm[97] ^= bs_p1_xmm[33];
/// interaction with truncated: //bs_p1_xmm[98]:0x0 ,0? False, omit? True
bs_p1_xmm[98] ^= bs_p1_xmm[34];
/// interaction with truncated: //bs_p1_xmm[99]:0x0 ,0? False, omit? True
bs_p1_xmm[99] ^= bs_p1_xmm[35];
/// interaction with truncated: //bs_p1_xmm[100]:0x0 ,0? False, omit? True
bs_p1_xmm[100] ^= bs_p1_xmm[36];
/// interaction with truncated: //bs_p1_xmm[101]:0x0 ,0? False, omit? True
bs_p1_xmm[101] ^= bs_p1_xmm[37];
/// interaction with truncated: //bs_p1_xmm[102]:0x0 ,0? False, omit? True
bs_p1_xmm[102] ^= bs_p1_xmm[38];
/// interaction with truncated: //bs_p1_xmm[103]:0x0 ,0? False, omit? True
bs_p1_xmm[103] ^= bs_p1_xmm[39];
/// interaction with truncated: //bs_p1_xmm[104]:0x0 ,0? False, omit? True
bs_p1_xmm[104] ^= bs_p1_xmm[40];
/// interaction with truncated: //bs_p1_xmm[105]:0x0 ,0? False, omit? True
bs_p1_xmm[105] ^= bs_p1_xmm[41];
/// interaction with truncated: //bs_p1_xmm[106]:0x0 ,0? False, omit? True
bs_p1_xmm[106] ^= bs_p1_xmm[42];
/// interaction with truncated: //bs_p1_xmm[107]:0x0 ,0? False, omit? True
bs_p1_xmm[107] ^= bs_p1_xmm[43];
/// interaction with truncated: //bs_p1_xmm[108]:0x0 ,0? False, omit? True
bs_p1_xmm[108] ^= bs_p1_xmm[44];
/// interaction with truncated: //bs_p1_xmm[109]:0x0 ,0? False, omit? True
bs_p1_xmm[109] ^= bs_p1_xmm[45];
/// interaction with truncated: //bs_p1_xmm[110]:0x0 ,0? False, omit? True
bs_p1_xmm[110] ^= bs_p1_xmm[46];
/// interaction with truncated: //bs_p1_xmm[111]:0x0 ,0? False, omit? True
bs_p1_xmm[111] ^= bs_p1_xmm[47];
/// interaction with truncated: //bs_p1_xmm[112]:0x0 ,0? False, omit? True
bs_p1_xmm[112] ^= bs_p1_xmm[48];
/// interaction with truncated: //bs_p1_xmm[113]:0x0 ,0? False, omit? True
bs_p1_xmm[113] ^= bs_p1_xmm[49];
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? False, omit? True
bs_p1_xmm[114] ^= bs_p1_xmm[50];
/// interaction with truncated: //bs_p1_xmm[115]:0x0 ,0? False, omit? True
bs_p1_xmm[115] ^= bs_p1_xmm[51];
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? False, omit? True
bs_p1_xmm[116] ^= bs_p1_xmm[52];
/// interaction with truncated: //bs_p1_xmm[117]:0x0 ,0? False, omit? True
bs_p1_xmm[117] ^= bs_p1_xmm[53];
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? False, omit? True
bs_p1_xmm[118] ^= bs_p1_xmm[54];
/// interaction with truncated: //bs_p1_xmm[119]:0x0 ,0? False, omit? True
bs_p1_xmm[119] ^= bs_p1_xmm[55];
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? False, omit? True
bs_p1_xmm[120] ^= bs_p1_xmm[56];
/// interaction with truncated: //bs_p1_xmm[121]:0x0 ,0? False, omit? True
bs_p1_xmm[121] ^= bs_p1_xmm[57];
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? False, omit? True
bs_p1_xmm[122] ^= bs_p1_xmm[58];
/// interaction with truncated: //bs_p1_xmm[123]:0x0 ,0? False, omit? True
bs_p1_xmm[123] ^= bs_p1_xmm[59];
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? False, omit? True
bs_p1_xmm[124] ^= bs_p1_xmm[60];
/// interaction with truncated: //bs_p1_xmm[125]:0x0 ,0? False, omit? True
bs_p1_xmm[125] ^= bs_p1_xmm[61];
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? False, omit? True
bs_p1_xmm[126] ^= bs_p1_xmm[62];
/// interaction with truncated: //bs_p1_xmm[127]:0x0 ,0? False, omit? True
bs_p1_xmm[127] ^= bs_p1_xmm[63];
#endif


bs_p1_xmm[1] ^= bs_p1_xmm[2];
bs_p1_xmm[2] ^= bs_p1_xmm[3];
bs_p1_xmm[5] ^= bs_p1_xmm[6];
bs_p1_xmm[6] ^= bs_p1_xmm[7];
bs_p1_xmm[9] ^= bs_p1_xmm[10];
bs_p1_xmm[10] ^= bs_p1_xmm[11];
bs_p1_xmm[13] ^= bs_p1_xmm[14];
bs_p1_xmm[14] ^= bs_p1_xmm[15];
bs_p1_xmm[4] ^= bs_p1_xmm[8];
bs_p1_xmm[5] ^= bs_p1_xmm[9];
bs_p1_xmm[6] ^= bs_p1_xmm[10];
bs_p1_xmm[7] ^= bs_p1_xmm[11];
bs_p1_xmm[8] ^= bs_p1_xmm[12];
bs_p1_xmm[9] ^= bs_p1_xmm[13];
bs_p1_xmm[10] ^= bs_p1_xmm[14];
bs_p1_xmm[11] ^= bs_p1_xmm[15];
bs_p1_xmm[1] ^= bs_p1_xmm[4];
bs_p1_xmm[2] ^= bs_p1_xmm[5];
bs_p1_xmm[3] ^= bs_p1_xmm[6];
bs_p1_xmm[4] ^= bs_p1_xmm[7];
bs_p1_xmm[9] ^= bs_p1_xmm[12];
bs_p1_xmm[10] ^= bs_p1_xmm[13];
bs_p1_xmm[11] ^= bs_p1_xmm[14];
bs_p1_xmm[12] ^= bs_p1_xmm[15];
bs_p1_xmm[2] ^= bs_p1_xmm[8];
bs_p1_xmm[3] ^= bs_p1_xmm[9];
bs_p1_xmm[4] ^= bs_p1_xmm[10];
bs_p1_xmm[5] ^= bs_p1_xmm[11];
bs_p1_xmm[6] ^= bs_p1_xmm[12];
bs_p1_xmm[7] ^= bs_p1_xmm[13];
bs_p1_xmm[8] ^= bs_p1_xmm[14];
bs_p1_xmm[9] ^= bs_p1_xmm[15];
bs_p1_xmm[17] ^= bs_p1_xmm[18];
bs_p1_xmm[18] ^= bs_p1_xmm[19];
bs_p1_xmm[21] ^= bs_p1_xmm[22];
bs_p1_xmm[22] ^= bs_p1_xmm[23];
bs_p1_xmm[25] ^= bs_p1_xmm[26];
bs_p1_xmm[26] ^= bs_p1_xmm[27];
bs_p1_xmm[29] ^= bs_p1_xmm[30];
bs_p1_xmm[30] ^= bs_p1_xmm[31];
bs_p1_xmm[20] ^= bs_p1_xmm[24];
bs_p1_xmm[21] ^= bs_p1_xmm[25];
bs_p1_xmm[22] ^= bs_p1_xmm[26];
bs_p1_xmm[23] ^= bs_p1_xmm[27];
bs_p1_xmm[24] ^= bs_p1_xmm[28];
bs_p1_xmm[25] ^= bs_p1_xmm[29];
bs_p1_xmm[26] ^= bs_p1_xmm[30];
bs_p1_xmm[27] ^= bs_p1_xmm[31];
bs_p1_xmm[17] ^= bs_p1_xmm[20];
bs_p1_xmm[18] ^= bs_p1_xmm[21];
bs_p1_xmm[19] ^= bs_p1_xmm[22];
bs_p1_xmm[20] ^= bs_p1_xmm[23];
bs_p1_xmm[25] ^= bs_p1_xmm[28];
bs_p1_xmm[26] ^= bs_p1_xmm[29];
bs_p1_xmm[27] ^= bs_p1_xmm[30];
bs_p1_xmm[28] ^= bs_p1_xmm[31];
bs_p1_xmm[18] ^= bs_p1_xmm[24];
bs_p1_xmm[19] ^= bs_p1_xmm[25];
bs_p1_xmm[20] ^= bs_p1_xmm[26];
bs_p1_xmm[21] ^= bs_p1_xmm[27];
bs_p1_xmm[22] ^= bs_p1_xmm[28];
bs_p1_xmm[23] ^= bs_p1_xmm[29];
bs_p1_xmm[24] ^= bs_p1_xmm[30];
bs_p1_xmm[25] ^= bs_p1_xmm[31];
bs_p1_xmm[33] ^= bs_p1_xmm[34];
bs_p1_xmm[34] ^= bs_p1_xmm[35];
bs_p1_xmm[37] ^= bs_p1_xmm[38];
bs_p1_xmm[38] ^= bs_p1_xmm[39];
bs_p1_xmm[41] ^= bs_p1_xmm[42];
bs_p1_xmm[42] ^= bs_p1_xmm[43];
bs_p1_xmm[45] ^= bs_p1_xmm[46];
bs_p1_xmm[46] ^= bs_p1_xmm[47];
bs_p1_xmm[36] ^= bs_p1_xmm[40];
bs_p1_xmm[37] ^= bs_p1_xmm[41];
bs_p1_xmm[38] ^= bs_p1_xmm[42];
bs_p1_xmm[39] ^= bs_p1_xmm[43];
bs_p1_xmm[40] ^= bs_p1_xmm[44];
bs_p1_xmm[41] ^= bs_p1_xmm[45];
bs_p1_xmm[42] ^= bs_p1_xmm[46];
bs_p1_xmm[43] ^= bs_p1_xmm[47];
bs_p1_xmm[33] ^= bs_p1_xmm[36];
bs_p1_xmm[34] ^= bs_p1_xmm[37];
bs_p1_xmm[35] ^= bs_p1_xmm[38];
bs_p1_xmm[36] ^= bs_p1_xmm[39];
bs_p1_xmm[41] ^= bs_p1_xmm[44];
bs_p1_xmm[42] ^= bs_p1_xmm[45];
bs_p1_xmm[43] ^= bs_p1_xmm[46];
bs_p1_xmm[44] ^= bs_p1_xmm[47];
bs_p1_xmm[34] ^= bs_p1_xmm[40];
bs_p1_xmm[35] ^= bs_p1_xmm[41];
bs_p1_xmm[36] ^= bs_p1_xmm[42];
bs_p1_xmm[37] ^= bs_p1_xmm[43];
bs_p1_xmm[38] ^= bs_p1_xmm[44];
bs_p1_xmm[39] ^= bs_p1_xmm[45];
bs_p1_xmm[40] ^= bs_p1_xmm[46];
bs_p1_xmm[41] ^= bs_p1_xmm[47];
bs_p1_xmm[49] ^= bs_p1_xmm[50];
bs_p1_xmm[50] ^= bs_p1_xmm[51];
bs_p1_xmm[53] ^= bs_p1_xmm[54];
bs_p1_xmm[54] ^= bs_p1_xmm[55];
bs_p1_xmm[57] ^= bs_p1_xmm[58];
bs_p1_xmm[58] ^= bs_p1_xmm[59];
bs_p1_xmm[61] ^= bs_p1_xmm[62];
bs_p1_xmm[62] ^= bs_p1_xmm[63];
bs_p1_xmm[52] ^= bs_p1_xmm[56];
bs_p1_xmm[53] ^= bs_p1_xmm[57];
bs_p1_xmm[54] ^= bs_p1_xmm[58];
bs_p1_xmm[55] ^= bs_p1_xmm[59];
bs_p1_xmm[56] ^= bs_p1_xmm[60];
bs_p1_xmm[57] ^= bs_p1_xmm[61];
bs_p1_xmm[58] ^= bs_p1_xmm[62];
bs_p1_xmm[59] ^= bs_p1_xmm[63];
bs_p1_xmm[49] ^= bs_p1_xmm[52];
bs_p1_xmm[50] ^= bs_p1_xmm[53];
bs_p1_xmm[51] ^= bs_p1_xmm[54];
bs_p1_xmm[52] ^= bs_p1_xmm[55];
bs_p1_xmm[57] ^= bs_p1_xmm[60];
bs_p1_xmm[58] ^= bs_p1_xmm[61];
bs_p1_xmm[59] ^= bs_p1_xmm[62];
bs_p1_xmm[60] ^= bs_p1_xmm[63];
bs_p1_xmm[50] ^= bs_p1_xmm[56];
bs_p1_xmm[51] ^= bs_p1_xmm[57];
bs_p1_xmm[52] ^= bs_p1_xmm[58];
bs_p1_xmm[53] ^= bs_p1_xmm[59];
bs_p1_xmm[54] ^= bs_p1_xmm[60];
bs_p1_xmm[55] ^= bs_p1_xmm[61];
bs_p1_xmm[56] ^= bs_p1_xmm[62];
bs_p1_xmm[57] ^= bs_p1_xmm[63];
bs_p1_xmm[65] ^= bs_p1_xmm[66];
bs_p1_xmm[66] ^= bs_p1_xmm[67];
bs_p1_xmm[69] ^= bs_p1_xmm[70];
bs_p1_xmm[70] ^= bs_p1_xmm[71];
bs_p1_xmm[73] ^= bs_p1_xmm[74];
bs_p1_xmm[74] ^= bs_p1_xmm[75];
bs_p1_xmm[77] ^= bs_p1_xmm[78];
bs_p1_xmm[78] ^= bs_p1_xmm[79];
bs_p1_xmm[68] ^= bs_p1_xmm[72];
bs_p1_xmm[69] ^= bs_p1_xmm[73];
bs_p1_xmm[70] ^= bs_p1_xmm[74];
bs_p1_xmm[71] ^= bs_p1_xmm[75];
bs_p1_xmm[72] ^= bs_p1_xmm[76];
bs_p1_xmm[73] ^= bs_p1_xmm[77];
bs_p1_xmm[74] ^= bs_p1_xmm[78];
bs_p1_xmm[75] ^= bs_p1_xmm[79];
bs_p1_xmm[65] ^= bs_p1_xmm[68];
bs_p1_xmm[66] ^= bs_p1_xmm[69];
bs_p1_xmm[67] ^= bs_p1_xmm[70];
bs_p1_xmm[68] ^= bs_p1_xmm[71];
bs_p1_xmm[73] ^= bs_p1_xmm[76];
bs_p1_xmm[74] ^= bs_p1_xmm[77];
bs_p1_xmm[75] ^= bs_p1_xmm[78];
bs_p1_xmm[76] ^= bs_p1_xmm[79];
bs_p1_xmm[66] ^= bs_p1_xmm[72];
bs_p1_xmm[67] ^= bs_p1_xmm[73];
bs_p1_xmm[68] ^= bs_p1_xmm[74];
bs_p1_xmm[69] ^= bs_p1_xmm[75];
bs_p1_xmm[70] ^= bs_p1_xmm[76];
bs_p1_xmm[71] ^= bs_p1_xmm[77];
bs_p1_xmm[72] ^= bs_p1_xmm[78];
bs_p1_xmm[73] ^= bs_p1_xmm[79];
bs_p1_xmm[81] ^= bs_p1_xmm[82];
bs_p1_xmm[82] ^= bs_p1_xmm[83];
bs_p1_xmm[85] ^= bs_p1_xmm[86];
bs_p1_xmm[86] ^= bs_p1_xmm[87];
bs_p1_xmm[89] ^= bs_p1_xmm[90];
bs_p1_xmm[90] ^= bs_p1_xmm[91];
bs_p1_xmm[93] ^= bs_p1_xmm[94];
bs_p1_xmm[94] ^= bs_p1_xmm[95];
bs_p1_xmm[84] ^= bs_p1_xmm[88];
bs_p1_xmm[85] ^= bs_p1_xmm[89];
bs_p1_xmm[86] ^= bs_p1_xmm[90];
bs_p1_xmm[87] ^= bs_p1_xmm[91];
bs_p1_xmm[88] ^= bs_p1_xmm[92];
bs_p1_xmm[89] ^= bs_p1_xmm[93];
bs_p1_xmm[90] ^= bs_p1_xmm[94];
bs_p1_xmm[91] ^= bs_p1_xmm[95];
bs_p1_xmm[81] ^= bs_p1_xmm[84];
bs_p1_xmm[82] ^= bs_p1_xmm[85];
bs_p1_xmm[83] ^= bs_p1_xmm[86];
bs_p1_xmm[84] ^= bs_p1_xmm[87];
bs_p1_xmm[89] ^= bs_p1_xmm[92];
bs_p1_xmm[90] ^= bs_p1_xmm[93];
bs_p1_xmm[91] ^= bs_p1_xmm[94];
bs_p1_xmm[92] ^= bs_p1_xmm[95];
bs_p1_xmm[82] ^= bs_p1_xmm[88];
bs_p1_xmm[83] ^= bs_p1_xmm[89];
bs_p1_xmm[84] ^= bs_p1_xmm[90];
bs_p1_xmm[85] ^= bs_p1_xmm[91];
bs_p1_xmm[86] ^= bs_p1_xmm[92];
bs_p1_xmm[87] ^= bs_p1_xmm[93];
bs_p1_xmm[88] ^= bs_p1_xmm[94];
bs_p1_xmm[89] ^= bs_p1_xmm[95];
/// truncated: /// + 0: bs_p1_xmm[97] = bs_p1_xmm[98];
/// truncated: /// + 0: bs_p1_xmm[98] = bs_p1_xmm[99];
/// truncated: /// + 0: bs_p1_xmm[101] = bs_p1_xmm[102];
/// truncated: /// + 0: bs_p1_xmm[102] = bs_p1_xmm[103];
/// truncated: /// + 0: bs_p1_xmm[105] = bs_p1_xmm[106];
/// truncated: /// + 0: bs_p1_xmm[106] = bs_p1_xmm[107];
/// truncated: /// + 0: bs_p1_xmm[109] = bs_p1_xmm[110];
/// truncated: /// + 0: bs_p1_xmm[110] = bs_p1_xmm[111];
/// truncated: /// + 0: bs_p1_xmm[100] = bs_p1_xmm[104];
/// truncated: /// + 0: bs_p1_xmm[101] = bs_p1_xmm[105];
/// truncated: /// + 0: bs_p1_xmm[102] = bs_p1_xmm[106];
/// truncated: /// + 0: bs_p1_xmm[103] = bs_p1_xmm[107];
/// truncated: /// + 0: bs_p1_xmm[104] = bs_p1_xmm[108];
/// truncated: /// + 0: bs_p1_xmm[105] = bs_p1_xmm[109];
/// truncated: /// + 0: bs_p1_xmm[106] = bs_p1_xmm[110];
/// truncated: /// + 0: bs_p1_xmm[107] = bs_p1_xmm[111];
/// truncated: /// + 0: bs_p1_xmm[97] = bs_p1_xmm[100];
/// truncated: /// + 0: bs_p1_xmm[98] = bs_p1_xmm[101];
/// truncated: /// + 0: bs_p1_xmm[99] = bs_p1_xmm[102];
/// truncated: /// + 0: bs_p1_xmm[100] = bs_p1_xmm[103];
/// truncated: /// + 0: bs_p1_xmm[105] = bs_p1_xmm[108];
/// truncated: /// + 0: bs_p1_xmm[106] = bs_p1_xmm[109];
/// truncated: /// + 0: bs_p1_xmm[107] = bs_p1_xmm[110];
/// truncated: /// + 0: bs_p1_xmm[108] = bs_p1_xmm[111];
/// truncated: /// + 0: bs_p1_xmm[98] = bs_p1_xmm[104];
/// truncated: /// + 0: bs_p1_xmm[99] = bs_p1_xmm[105];
/// truncated: /// + 0: bs_p1_xmm[100] = bs_p1_xmm[106];
/// truncated: /// + 0: bs_p1_xmm[101] = bs_p1_xmm[107];
/// truncated: /// + 0: bs_p1_xmm[102] = bs_p1_xmm[108];
/// truncated: /// + 0: bs_p1_xmm[103] = bs_p1_xmm[109];
/// truncated: /// + 0: bs_p1_xmm[104] = bs_p1_xmm[110];
/// truncated: /// + 0: bs_p1_xmm[105] = bs_p1_xmm[111];
/// truncated: /// + 0: bs_p1_xmm[113] = bs_p1_xmm[114];
/// truncated: /// + 0: bs_p1_xmm[114] = bs_p1_xmm[115];
/// truncated: /// + 0: bs_p1_xmm[117] = bs_p1_xmm[118];
/// truncated: /// + 0: bs_p1_xmm[118] = bs_p1_xmm[119];
/// truncated: /// + 0: bs_p1_xmm[121] = bs_p1_xmm[122];
/// truncated: /// + 0: bs_p1_xmm[122] = bs_p1_xmm[123];
/// truncated: /// + 0: bs_p1_xmm[125] = bs_p1_xmm[126];
/// truncated: /// + 0: bs_p1_xmm[126] = bs_p1_xmm[127];
/// truncated: /// + 0: bs_p1_xmm[116] = bs_p1_xmm[120];
/// truncated: /// + 0: bs_p1_xmm[117] = bs_p1_xmm[121];
/// truncated: /// + 0: bs_p1_xmm[118] = bs_p1_xmm[122];
/// truncated: /// + 0: bs_p1_xmm[119] = bs_p1_xmm[123];
/// truncated: /// + 0: bs_p1_xmm[120] = bs_p1_xmm[124];
/// truncated: /// + 0: bs_p1_xmm[121] = bs_p1_xmm[125];
/// truncated: /// + 0: bs_p1_xmm[122] = bs_p1_xmm[126];
/// truncated: /// + 0: bs_p1_xmm[123] = bs_p1_xmm[127];
/// truncated: /// + 0: bs_p1_xmm[113] = bs_p1_xmm[116];
/// truncated: /// + 0: bs_p1_xmm[114] = bs_p1_xmm[117];
/// truncated: /// + 0: bs_p1_xmm[115] = bs_p1_xmm[118];
/// truncated: /// + 0: bs_p1_xmm[116] = bs_p1_xmm[119];
/// truncated: /// + 0: bs_p1_xmm[121] = bs_p1_xmm[124];
/// truncated: /// + 0: bs_p1_xmm[122] = bs_p1_xmm[125];
/// truncated: /// + 0: bs_p1_xmm[123] = bs_p1_xmm[126];
/// truncated: /// + 0: bs_p1_xmm[124] = bs_p1_xmm[127];
/// truncated: /// + 0: bs_p1_xmm[114] = bs_p1_xmm[120];
/// truncated: /// + 0: bs_p1_xmm[115] = bs_p1_xmm[121];
/// truncated: /// + 0: bs_p1_xmm[116] = bs_p1_xmm[122];
/// truncated: /// + 0: bs_p1_xmm[117] = bs_p1_xmm[123];
/// truncated: /// + 0: bs_p1_xmm[118] = bs_p1_xmm[124];
/// truncated: /// + 0: bs_p1_xmm[119] = bs_p1_xmm[125];
/// truncated: /// + 0: bs_p1_xmm[120] = bs_p1_xmm[126];
/// truncated: /// + 0: bs_p1_xmm[121] = bs_p1_xmm[127];
bs_p1_xmm[16] ^= bs_p1_xmm[32];
bs_p1_xmm[17] ^= bs_p1_xmm[33];
bs_p1_xmm[18] ^= bs_p1_xmm[34];
bs_p1_xmm[19] ^= bs_p1_xmm[35];
bs_p1_xmm[20] ^= bs_p1_xmm[36];
bs_p1_xmm[21] ^= bs_p1_xmm[37];
bs_p1_xmm[22] ^= bs_p1_xmm[38];
bs_p1_xmm[23] ^= bs_p1_xmm[39];
bs_p1_xmm[24] ^= bs_p1_xmm[40];
bs_p1_xmm[25] ^= bs_p1_xmm[41];
bs_p1_xmm[26] ^= bs_p1_xmm[42];
bs_p1_xmm[27] ^= bs_p1_xmm[43];
bs_p1_xmm[28] ^= bs_p1_xmm[44];
bs_p1_xmm[29] ^= bs_p1_xmm[45];
bs_p1_xmm[30] ^= bs_p1_xmm[46];
bs_p1_xmm[31] ^= bs_p1_xmm[47];
bs_p1_xmm[32] ^= bs_p1_xmm[48];
bs_p1_xmm[33] ^= bs_p1_xmm[49];
bs_p1_xmm[34] ^= bs_p1_xmm[50];
bs_p1_xmm[35] ^= bs_p1_xmm[51];
bs_p1_xmm[36] ^= bs_p1_xmm[52];
bs_p1_xmm[37] ^= bs_p1_xmm[53];
bs_p1_xmm[38] ^= bs_p1_xmm[54];
bs_p1_xmm[39] ^= bs_p1_xmm[55];
bs_p1_xmm[40] ^= bs_p1_xmm[56];
bs_p1_xmm[41] ^= bs_p1_xmm[57];
bs_p1_xmm[42] ^= bs_p1_xmm[58];
bs_p1_xmm[43] ^= bs_p1_xmm[59];
bs_p1_xmm[44] ^= bs_p1_xmm[60];
bs_p1_xmm[45] ^= bs_p1_xmm[61];
bs_p1_xmm[46] ^= bs_p1_xmm[62];
bs_p1_xmm[47] ^= bs_p1_xmm[63];
/// interaction with truncated: //bs_p1_xmm[96]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[80] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[97]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[81] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[98]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[82] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[99]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[83] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[100]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[84] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[101]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[85] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[102]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[86] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[103]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[87] ^= bs_p1_xmm[103];
/// interaction with truncated: //bs_p1_xmm[104]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[88] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[105]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[89] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[106]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[90] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[107]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[91] ^= bs_p1_xmm[107];
/// interaction with truncated: //bs_p1_xmm[108]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[92] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[109]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[93] ^= bs_p1_xmm[109];
/// interaction with truncated: //bs_p1_xmm[110]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[94] ^= bs_p1_xmm[110];
/// interaction with truncated: //bs_p1_xmm[111]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[95] ^= bs_p1_xmm[111];
/// truncated: /// + 0: bs_p1_xmm[96] = bs_p1_xmm[112];
/// truncated: /// + 0: bs_p1_xmm[97] = bs_p1_xmm[113];
/// truncated: /// + 0: bs_p1_xmm[98] = bs_p1_xmm[114];
/// truncated: /// + 0: bs_p1_xmm[99] = bs_p1_xmm[115];
/// truncated: /// + 0: bs_p1_xmm[100] = bs_p1_xmm[116];
/// truncated: /// + 0: bs_p1_xmm[101] = bs_p1_xmm[117];
/// truncated: /// + 0: bs_p1_xmm[102] = bs_p1_xmm[118];
/// truncated: /// + 0: bs_p1_xmm[103] = bs_p1_xmm[119];
/// truncated: /// + 0: bs_p1_xmm[104] = bs_p1_xmm[120];
/// truncated: /// + 0: bs_p1_xmm[105] = bs_p1_xmm[121];
/// truncated: /// + 0: bs_p1_xmm[106] = bs_p1_xmm[122];
/// truncated: /// + 0: bs_p1_xmm[107] = bs_p1_xmm[123];
/// truncated: /// + 0: bs_p1_xmm[108] = bs_p1_xmm[124];
/// truncated: /// + 0: bs_p1_xmm[109] = bs_p1_xmm[125];
/// truncated: /// + 0: bs_p1_xmm[110] = bs_p1_xmm[126];
/// truncated: /// + 0: bs_p1_xmm[111] = bs_p1_xmm[127];
bs_p1_xmm[16] ^= bs_p1_xmm[64];
bs_p1_xmm[17] ^= bs_p1_xmm[65];
bs_p1_xmm[18] ^= bs_p1_xmm[66];
bs_p1_xmm[19] ^= bs_p1_xmm[67];
bs_p1_xmm[20] ^= bs_p1_xmm[68];
bs_p1_xmm[21] ^= bs_p1_xmm[69];
bs_p1_xmm[22] ^= bs_p1_xmm[70];
bs_p1_xmm[23] ^= bs_p1_xmm[71];
bs_p1_xmm[24] ^= bs_p1_xmm[72];
bs_p1_xmm[25] ^= bs_p1_xmm[73];
bs_p1_xmm[26] ^= bs_p1_xmm[74];
bs_p1_xmm[27] ^= bs_p1_xmm[75];
bs_p1_xmm[28] ^= bs_p1_xmm[76];
bs_p1_xmm[29] ^= bs_p1_xmm[77];
bs_p1_xmm[30] ^= bs_p1_xmm[78];
bs_p1_xmm[31] ^= bs_p1_xmm[79];
bs_p1_xmm[32] ^= bs_p1_xmm[80];
bs_p1_xmm[33] ^= bs_p1_xmm[81];
bs_p1_xmm[34] ^= bs_p1_xmm[82];
bs_p1_xmm[35] ^= bs_p1_xmm[83];
bs_p1_xmm[36] ^= bs_p1_xmm[84];
bs_p1_xmm[37] ^= bs_p1_xmm[85];
bs_p1_xmm[38] ^= bs_p1_xmm[86];
bs_p1_xmm[39] ^= bs_p1_xmm[87];
bs_p1_xmm[40] ^= bs_p1_xmm[88];
bs_p1_xmm[41] ^= bs_p1_xmm[89];
bs_p1_xmm[42] ^= bs_p1_xmm[90];
bs_p1_xmm[43] ^= bs_p1_xmm[91];
bs_p1_xmm[44] ^= bs_p1_xmm[92];
bs_p1_xmm[45] ^= bs_p1_xmm[93];
bs_p1_xmm[46] ^= bs_p1_xmm[94];
bs_p1_xmm[47] ^= bs_p1_xmm[95];
/// interaction with truncated: //bs_p1_xmm[96]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[48] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[97]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[49] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[98]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[50] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[99]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[51] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[100]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[52] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[101]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[53] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[102]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[54] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[103]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[55] ^= bs_p1_xmm[103];
/// interaction with truncated: //bs_p1_xmm[104]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[56] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[105]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[57] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[106]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[58] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[107]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[59] ^= bs_p1_xmm[107];
/// interaction with truncated: //bs_p1_xmm[108]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[60] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[109]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[61] ^= bs_p1_xmm[109];
/// interaction with truncated: //bs_p1_xmm[110]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[62] ^= bs_p1_xmm[110];
/// interaction with truncated: //bs_p1_xmm[111]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[63] ^= bs_p1_xmm[111];
/// interaction with truncated: //bs_p1_xmm[112]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[64] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[113]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[65] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[66] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[115]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[67] ^= bs_p1_xmm[115];
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[68] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[117]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[69] ^= bs_p1_xmm[117];
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[70] ^= bs_p1_xmm[118];
/// interaction with truncated: //bs_p1_xmm[119]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[71] ^= bs_p1_xmm[119];
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[72] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[121]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[73] ^= bs_p1_xmm[121];
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[74] ^= bs_p1_xmm[122];
/// interaction with truncated: //bs_p1_xmm[123]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[75] ^= bs_p1_xmm[123];
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[76] ^= bs_p1_xmm[124];
/// interaction with truncated: //bs_p1_xmm[125]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[77] ^= bs_p1_xmm[125];
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[78] ^= bs_p1_xmm[126];
/// interaction with truncated: //bs_p1_xmm[127]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[79] ^= bs_p1_xmm[127];
bs_p1_xmm[1] ^= bs_p1_xmm[16];
bs_p1_xmm[2] ^= bs_p1_xmm[17];
bs_p1_xmm[3] ^= bs_p1_xmm[18];
bs_p1_xmm[4] ^= bs_p1_xmm[19];
bs_p1_xmm[5] ^= bs_p1_xmm[20];
bs_p1_xmm[6] ^= bs_p1_xmm[21];
bs_p1_xmm[7] ^= bs_p1_xmm[22];
bs_p1_xmm[8] ^= bs_p1_xmm[23];
bs_p1_xmm[9] ^= bs_p1_xmm[24];
bs_p1_xmm[10] ^= bs_p1_xmm[25];
bs_p1_xmm[11] ^= bs_p1_xmm[26];
bs_p1_xmm[12] ^= bs_p1_xmm[27];
bs_p1_xmm[13] ^= bs_p1_xmm[28];
bs_p1_xmm[14] ^= bs_p1_xmm[29];
bs_p1_xmm[15] ^= bs_p1_xmm[30];
bs_p1_xmm[16] ^= bs_p1_xmm[31];
bs_p1_xmm[33] ^= bs_p1_xmm[48];
bs_p1_xmm[34] ^= bs_p1_xmm[49];
bs_p1_xmm[35] ^= bs_p1_xmm[50];
bs_p1_xmm[36] ^= bs_p1_xmm[51];
bs_p1_xmm[37] ^= bs_p1_xmm[52];
bs_p1_xmm[38] ^= bs_p1_xmm[53];
bs_p1_xmm[39] ^= bs_p1_xmm[54];
bs_p1_xmm[40] ^= bs_p1_xmm[55];
bs_p1_xmm[41] ^= bs_p1_xmm[56];
bs_p1_xmm[42] ^= bs_p1_xmm[57];
bs_p1_xmm[43] ^= bs_p1_xmm[58];
bs_p1_xmm[44] ^= bs_p1_xmm[59];
bs_p1_xmm[45] ^= bs_p1_xmm[60];
bs_p1_xmm[46] ^= bs_p1_xmm[61];
bs_p1_xmm[47] ^= bs_p1_xmm[62];
bs_p1_xmm[48] ^= bs_p1_xmm[63];
bs_p1_xmm[65] ^= bs_p1_xmm[80];
bs_p1_xmm[66] ^= bs_p1_xmm[81];
bs_p1_xmm[67] ^= bs_p1_xmm[82];
bs_p1_xmm[68] ^= bs_p1_xmm[83];
bs_p1_xmm[69] ^= bs_p1_xmm[84];
bs_p1_xmm[70] ^= bs_p1_xmm[85];
bs_p1_xmm[71] ^= bs_p1_xmm[86];
bs_p1_xmm[72] ^= bs_p1_xmm[87];
bs_p1_xmm[73] ^= bs_p1_xmm[88];
bs_p1_xmm[74] ^= bs_p1_xmm[89];
bs_p1_xmm[75] ^= bs_p1_xmm[90];
bs_p1_xmm[76] ^= bs_p1_xmm[91];
bs_p1_xmm[77] ^= bs_p1_xmm[92];
bs_p1_xmm[78] ^= bs_p1_xmm[93];
bs_p1_xmm[79] ^= bs_p1_xmm[94];
bs_p1_xmm[80] ^= bs_p1_xmm[95];
/// truncated: /// + 0: bs_p1_xmm[97] = bs_p1_xmm[112];
/// truncated: /// + 0: bs_p1_xmm[98] = bs_p1_xmm[113];
/// truncated: /// + 0: bs_p1_xmm[99] = bs_p1_xmm[114];
/// truncated: /// + 0: bs_p1_xmm[100] = bs_p1_xmm[115];
/// truncated: /// + 0: bs_p1_xmm[101] = bs_p1_xmm[116];
/// truncated: /// + 0: bs_p1_xmm[102] = bs_p1_xmm[117];
/// truncated: /// + 0: bs_p1_xmm[103] = bs_p1_xmm[118];
/// truncated: /// + 0: bs_p1_xmm[104] = bs_p1_xmm[119];
/// truncated: /// + 0: bs_p1_xmm[105] = bs_p1_xmm[120];
/// truncated: /// + 0: bs_p1_xmm[106] = bs_p1_xmm[121];
/// truncated: /// + 0: bs_p1_xmm[107] = bs_p1_xmm[122];
/// truncated: /// + 0: bs_p1_xmm[108] = bs_p1_xmm[123];
/// truncated: /// + 0: bs_p1_xmm[109] = bs_p1_xmm[124];
/// truncated: /// + 0: bs_p1_xmm[110] = bs_p1_xmm[125];
/// truncated: /// + 0: bs_p1_xmm[111] = bs_p1_xmm[126];
/// truncated: /// + 0: bs_p1_xmm[112] = bs_p1_xmm[127];
bs_p1_xmm[2] ^= bs_p1_xmm[32];
bs_p1_xmm[3] ^= bs_p1_xmm[33];
bs_p1_xmm[4] ^= bs_p1_xmm[34];
bs_p1_xmm[5] ^= bs_p1_xmm[35];
bs_p1_xmm[6] ^= bs_p1_xmm[36];
bs_p1_xmm[7] ^= bs_p1_xmm[37];
bs_p1_xmm[8] ^= bs_p1_xmm[38];
bs_p1_xmm[9] ^= bs_p1_xmm[39];
bs_p1_xmm[10] ^= bs_p1_xmm[40];
bs_p1_xmm[11] ^= bs_p1_xmm[41];
bs_p1_xmm[12] ^= bs_p1_xmm[42];
bs_p1_xmm[13] ^= bs_p1_xmm[43];
bs_p1_xmm[14] ^= bs_p1_xmm[44];
bs_p1_xmm[15] ^= bs_p1_xmm[45];
bs_p1_xmm[16] ^= bs_p1_xmm[46];
bs_p1_xmm[17] ^= bs_p1_xmm[47];
bs_p1_xmm[18] ^= bs_p1_xmm[48];
bs_p1_xmm[19] ^= bs_p1_xmm[49];
bs_p1_xmm[20] ^= bs_p1_xmm[50];
bs_p1_xmm[21] ^= bs_p1_xmm[51];
bs_p1_xmm[22] ^= bs_p1_xmm[52];
bs_p1_xmm[23] ^= bs_p1_xmm[53];
bs_p1_xmm[24] ^= bs_p1_xmm[54];
bs_p1_xmm[25] ^= bs_p1_xmm[55];
bs_p1_xmm[26] ^= bs_p1_xmm[56];
bs_p1_xmm[27] ^= bs_p1_xmm[57];
bs_p1_xmm[28] ^= bs_p1_xmm[58];
bs_p1_xmm[29] ^= bs_p1_xmm[59];
bs_p1_xmm[30] ^= bs_p1_xmm[60];
bs_p1_xmm[31] ^= bs_p1_xmm[61];
bs_p1_xmm[32] ^= bs_p1_xmm[62];
bs_p1_xmm[33] ^= bs_p1_xmm[63];
/// interaction with truncated: //bs_p1_xmm[96]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[66] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[97]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[67] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[98]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[68] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[99]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[69] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[100]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[70] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[101]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[71] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[102]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[72] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[103]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[73] ^= bs_p1_xmm[103];
/// interaction with truncated: //bs_p1_xmm[104]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[74] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[105]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[75] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[106]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[76] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[107]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[77] ^= bs_p1_xmm[107];
/// interaction with truncated: //bs_p1_xmm[108]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[78] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[109]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[79] ^= bs_p1_xmm[109];
/// interaction with truncated: //bs_p1_xmm[110]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[80] ^= bs_p1_xmm[110];
/// interaction with truncated: //bs_p1_xmm[111]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[81] ^= bs_p1_xmm[111];
/// interaction with truncated: //bs_p1_xmm[112]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[82] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[113]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[83] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[84] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[115]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[85] ^= bs_p1_xmm[115];
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[86] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[117]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[87] ^= bs_p1_xmm[117];
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[88] ^= bs_p1_xmm[118];
/// interaction with truncated: //bs_p1_xmm[119]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[89] ^= bs_p1_xmm[119];
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[90] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[121]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[91] ^= bs_p1_xmm[121];
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[92] ^= bs_p1_xmm[122];
/// interaction with truncated: //bs_p1_xmm[123]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[93] ^= bs_p1_xmm[123];
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[94] ^= bs_p1_xmm[124];
/// interaction with truncated: //bs_p1_xmm[125]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[95] ^= bs_p1_xmm[125];
/// truncated: /// + 0: bs_p1_xmm[96] = bs_p1_xmm[126];
/// truncated: /// + 0: bs_p1_xmm[97] = bs_p1_xmm[127];
bs_p1_xmm[4] ^= bs_p1_xmm[64];
bs_p1_xmm[5] ^= bs_p1_xmm[65];
bs_p1_xmm[6] ^= bs_p1_xmm[66];
bs_p1_xmm[7] ^= bs_p1_xmm[67];
bs_p1_xmm[8] ^= bs_p1_xmm[68];
bs_p1_xmm[9] ^= bs_p1_xmm[69];
bs_p1_xmm[10] ^= bs_p1_xmm[70];
bs_p1_xmm[11] ^= bs_p1_xmm[71];
bs_p1_xmm[12] ^= bs_p1_xmm[72];
bs_p1_xmm[13] ^= bs_p1_xmm[73];
bs_p1_xmm[14] ^= bs_p1_xmm[74];
bs_p1_xmm[15] ^= bs_p1_xmm[75];
bs_p1_xmm[16] ^= bs_p1_xmm[76];
bs_p1_xmm[17] ^= bs_p1_xmm[77];
bs_p1_xmm[18] ^= bs_p1_xmm[78];
bs_p1_xmm[19] ^= bs_p1_xmm[79];
bs_p1_xmm[20] ^= bs_p1_xmm[80];
bs_p1_xmm[21] ^= bs_p1_xmm[81];
bs_p1_xmm[22] ^= bs_p1_xmm[82];
bs_p1_xmm[23] ^= bs_p1_xmm[83];
bs_p1_xmm[24] ^= bs_p1_xmm[84];
bs_p1_xmm[25] ^= bs_p1_xmm[85];
bs_p1_xmm[26] ^= bs_p1_xmm[86];
bs_p1_xmm[27] ^= bs_p1_xmm[87];
bs_p1_xmm[28] ^= bs_p1_xmm[88];
bs_p1_xmm[29] ^= bs_p1_xmm[89];
bs_p1_xmm[30] ^= bs_p1_xmm[90];
bs_p1_xmm[31] ^= bs_p1_xmm[91];
bs_p1_xmm[32] ^= bs_p1_xmm[92];
bs_p1_xmm[33] ^= bs_p1_xmm[93];
bs_p1_xmm[34] ^= bs_p1_xmm[94];
bs_p1_xmm[35] ^= bs_p1_xmm[95];
/// interaction with truncated: //bs_p1_xmm[96]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[36] ^= bs_p1_xmm[96];
/// interaction with truncated: //bs_p1_xmm[97]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[37] ^= bs_p1_xmm[97];
/// interaction with truncated: //bs_p1_xmm[98]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[38] ^= bs_p1_xmm[98];
/// interaction with truncated: //bs_p1_xmm[99]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[39] ^= bs_p1_xmm[99];
/// interaction with truncated: //bs_p1_xmm[100]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[40] ^= bs_p1_xmm[100];
/// interaction with truncated: //bs_p1_xmm[101]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[41] ^= bs_p1_xmm[101];
/// interaction with truncated: //bs_p1_xmm[102]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[42] ^= bs_p1_xmm[102];
/// interaction with truncated: //bs_p1_xmm[103]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[43] ^= bs_p1_xmm[103];
/// interaction with truncated: //bs_p1_xmm[104]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[44] ^= bs_p1_xmm[104];
/// interaction with truncated: //bs_p1_xmm[105]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[45] ^= bs_p1_xmm[105];
/// interaction with truncated: //bs_p1_xmm[106]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[46] ^= bs_p1_xmm[106];
/// interaction with truncated: //bs_p1_xmm[107]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[47] ^= bs_p1_xmm[107];
/// interaction with truncated: //bs_p1_xmm[108]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[48] ^= bs_p1_xmm[108];
/// interaction with truncated: //bs_p1_xmm[109]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[49] ^= bs_p1_xmm[109];
/// interaction with truncated: //bs_p1_xmm[110]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[50] ^= bs_p1_xmm[110];
/// interaction with truncated: //bs_p1_xmm[111]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[51] ^= bs_p1_xmm[111];
/// interaction with truncated: //bs_p1_xmm[112]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[52] ^= bs_p1_xmm[112];
/// interaction with truncated: //bs_p1_xmm[113]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[53] ^= bs_p1_xmm[113];
/// interaction with truncated: //bs_p1_xmm[114]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[54] ^= bs_p1_xmm[114];
/// interaction with truncated: //bs_p1_xmm[115]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[55] ^= bs_p1_xmm[115];
/// interaction with truncated: //bs_p1_xmm[116]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[56] ^= bs_p1_xmm[116];
/// interaction with truncated: //bs_p1_xmm[117]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[57] ^= bs_p1_xmm[117];
/// interaction with truncated: //bs_p1_xmm[118]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[58] ^= bs_p1_xmm[118];
/// interaction with truncated: //bs_p1_xmm[119]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[59] ^= bs_p1_xmm[119];
/// interaction with truncated: //bs_p1_xmm[120]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[60] ^= bs_p1_xmm[120];
/// interaction with truncated: //bs_p1_xmm[121]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[61] ^= bs_p1_xmm[121];
/// interaction with truncated: //bs_p1_xmm[122]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[62] ^= bs_p1_xmm[122];
/// interaction with truncated: //bs_p1_xmm[123]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[63] ^= bs_p1_xmm[123];
/// interaction with truncated: //bs_p1_xmm[124]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[64] ^= bs_p1_xmm[124];
/// interaction with truncated: //bs_p1_xmm[125]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[65] ^= bs_p1_xmm[125];
/// interaction with truncated: //bs_p1_xmm[126]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[66] ^= bs_p1_xmm[126];
/// interaction with truncated: //bs_p1_xmm[127]:0x0 ,0? True, omit? True
/// + 0: bs_p1_xmm[67] ^= bs_p1_xmm[127];


for(unsigned i=0;i<95;i++) rp_xmm[i] = bs_p1_xmm[i];
rp_xmm[95] = _mm_setzero_si128();

}
