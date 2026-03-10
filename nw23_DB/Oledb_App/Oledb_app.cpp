// Client Application
//
////////////////////////////////////////////////////////////////////////////////

#pragma comment(lib, "Winmm.lib")

#include <windows.h>
#include <Mmsystem.h>
#include <stdio.h>


#include "../include/LcDB/ILcDB.h"


ILcDB*		g_pDataBase=nullptr;											// DataBase Instance


int main()
{
	char	sDBtype[32];
	char	sFile[MAX_PATH];
	char	sSQL[512];
	
	strcpy(sDBtype, "excel");
	strcpy(sFile, "database/user.xls");
	strcpy(sSQL, "Select * from [Sheet1$]");


	if(FAILED(LnDB_CreateAndConnect("OLEDB", &g_pDataBase, sDBtype, sFile)))
		return -1;


	INT		nBufSize= 1024;
	char**	sDataBuf= nullptr;
	INT*	nDataBuf= nullptr;
	INT		iColumn	= 0;


//	for(int j=0; j<3; ++j)
	{
		iColumn = g_pDataBase->SqlBind(sSQL, &sDataBuf, &nDataBuf, nBufSize);

		if(SUCCEEDED(iColumn))
		{
			printf("이름                   경험치                       체력\n");
			printf("--------------------------------------------------\n");

			while(1)
			{
				if(FAILED(g_pDataBase->SqlExec()))
					break;

				for(int i=0; i<iColumn; ++i)
				{
					printf("%12s(%2d)	", sDataBuf[i], nDataBuf[i]);
				}

				printf("\n");
			}

			g_pDataBase->SqlClose();

			printf("--------------------------------------------------\n\n");
		}
	}


	g_pDataBase->Close();
	g_pDataBase->Destroy();

	delete g_pDataBase;
	
	return 1;
}


