#pragma once 

#include "SaxParser.h"

class CSaxFormatter: public CXSPHandler
{
public:
	CSaxFormatter();

	void OnElementBegin(const char* szName) override;
    void OnElementEnd(const  char* szName) override;
    void OnCloseSingleElement(const  char* szName) override;
    void OnAttribute(const char* szName, const char* szValue) override;
    void OnText(const char* szValue) override;
    void OnCDATA(const char* szValue) override;
    void OnComment(const char* szText) override;
    void OnDeclaration(const char* szVersion, const char* szEncoding, const char* szStandAlone) override;
    void OnProcessing(const char* szValue) override;

	void SetIndentAsTab(); //Set indent as tabulation
	void SetIndentAsBlank(); //Set indent as whitespace
	void SetIndentCount(unsigned int nCount); //Set a number of indent symbols
protected:
	virtual void Output(const char* szText) {}

private:
	unsigned int m_nIndentCount;
	char m_chIndentSymbol[2];
	
	unsigned int m_nIdentValue;
	bool m_bValue;
	bool m_bOpen;
	void Incr();
	void Decr();
	void DoIndent();
	void DoBreakLine();
};
