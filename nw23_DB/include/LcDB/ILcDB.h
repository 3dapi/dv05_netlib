// Interface for the ILcDB class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ILcDB_H_
#define _ILcDB_H_


#ifndef interface
#define interface struct
#endif

#ifndef LC_CLASS_DESTROYER
#define LC_CLASS_DESTROYER( CLASS_NAME )	\
virtual ~CLASS_NAME(){}
#endif


interface ILcDB
{
	LC_CLASS_DESTROYER(	ILcDB	);

	virtual INT		Create(void* p1=nullptr, void* p2=nullptr, void* p3=nullptr, void* p4=nullptr)=0;
	virtual void	Destroy()=0;
	virtual	INT		Query(char* sCmd, void* pData)=0;


	virtual INT		Connect(void* pDataType, void* p1=nullptr, void* p2=nullptr, void* p3=nullptr)=0;
	virtual void	Close()=0;

	virtual INT		SqlBind(char* sSQL, char*** sOutputBufc,INT** nDataBufc, INT nBufSize)=0;
	virtual INT		SqlExec()=0;
	virtual INT		SqlClose()=0;	
};



INT		LnDB_Create(char* sCmd, ILcDB** pData);

INT		LnDB_CreateAndConnect(char* sCmd				// "ODBC" or "OLEDB"
							  , ILcDB** pData			// In-out Data
							  , void* p1				// DataBase Type: "MDB", "excel", "DSN", ...
							  , void* p2=nullptr			// DataBase Name
							  , void* p3=nullptr			// User Id
							  , void* p4=nullptr			// Password
							  , void* p5=nullptr			// Host Computer
							  );


#ifdef _DEBUG
	#pragma comment(lib, "../LIB/LcDB_.lib")
#else
	#pragma comment(lib, "../LIB/LcDB.lib")
#endif



#endif

