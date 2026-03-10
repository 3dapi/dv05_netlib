// Interface for the CLcOdbc class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _LcOdbc_H_
#define _LcOdbc_H_


class CLcOdbc : public CLcDB
{
protected:
	HANDLE			m_hEnv;						// DataBase Allocation Handle(SQLHENV)

	HANDLE			m_hDbc;						// ODBC Handle(SQLHDBC)
	HANDLE			m_hStm;						// ODBC Statement Handle(SQLHSTMT)
	
	SHORT			m_nField;
	char**			m_pDataBuf;
	INT*			m_nDataBuf;

public:	
	CLcOdbc();
	virtual ~CLcOdbc();

	virtual INT		Create(void* p1=0, void* p2=0, void* p3=0, void* p4=0);
	virtual void	Destroy();
	virtual	INT		Query(char* sCmd, void* pData);


	virtual INT		Connect(void* pDataType, void* p1=0, void* p2=0, void* p3=0);
	virtual void	Close();

	virtual INT		SqlBind(char* sSQL, char*** sOutputBufc,INT** nDataBufc, INT nBufSize);
	virtual INT		SqlExec();
	virtual INT		SqlClose();
	
protected:
	INT		ConnectDsn(char* sDsn);
	INT		ConnectSql(char* sDsn, char* sUID, char* sPWD);
	INT		ConnectMdb(char* sFile);
	INT		ConnectExcel(char* sFile);

	INT		GetColumNum();
};

#endif


