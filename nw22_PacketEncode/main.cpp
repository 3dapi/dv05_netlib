
#include <windows.h>
#include <stdio.h>
#include <string.h>

#include <d3dx9.h>

int PacketEncode(void* pOut
				 , int nPacketType
				 , void* pMessage
				 , int iLenMessage
				 , int iLenPacketHeader = 1
				 , int iLenPacketType   = 4)
{
	unsigned char* pDst = (unsigned char*)pOut;

	pDst[0] = iLenPacketHeader + iLenPacketType + iLenMessage;

	memcpy(pDst + iLenPacketHeader                 , &nPacketType, iLenPacketType);
	memcpy(pDst + iLenPacketHeader + iLenPacketType, pMessage, iLenMessage);

	return pDst[0];
}

int PacketDecode(int* nPacketType
				 , void* pMessage
				 , int* iLenMessage
				 , void* pIn
				 , int iLenPacketHeader = 1
				 , int iLenPacketType   = 4)
{
	unsigned char* pSrc = (unsigned char*)pIn;

	int iLen = pSrc[0] - iLenPacketHeader - iLenPacketType;

	memcpy(&nPacketType, pSrc + iLenPacketHeader, iLenPacketType);
	memcpy(pMessage    , pSrc + iLenPacketHeader + iLenPacketType, iLen);
	
	if(iLenMessage)
		*iLenMessage = iLen;

	return pSrc[0];
}



struct CharInf
{
	int			iId;		// Identity
	int			iHp;		// Helth Point
	int			iMp;		// Mana Point
	D3DXVECTOR3 vcP;		// Position
};


enum EPacketType
{
	ECharInfo = 0x0,
	ECharMove = 0x1,
};

void main()
{
	CharInf TestChar;
	TestChar.iId = 0x1234;
	TestChar.iHp = 0x5678;
	TestChar.iMp = 0x12345678;
	
	int		iSrcType = ECharInfo;
	char	sOut[256]={0};
	PacketEncode(sOut, iSrcType, &TestChar, sizeof(TestChar));


	char	sDst[256]={0};
	int		iDstType = 0x0;
	int		iDstLen  = 0;
	PacketDecode(&iDstType, sDst, &iDstLen, sOut);

	if(ECharInfo == iDstType)
	{
		CharInf chInf;
		memcpy(&chInf, sDst, sizeof chInf );
		printf("%x %x  %x\n", chInf.iId, chInf.iHp, chInf.iMp);
	}
	
	else if(ECharMove == iDstType)
	{
		// 적절한 코드 선택
	}


}












