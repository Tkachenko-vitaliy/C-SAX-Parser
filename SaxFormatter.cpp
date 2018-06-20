#include "SaxFormatter.h"

CSaxFormatter::CSaxFormatter()
{
	m_nIdentValue=0; m_bValue=false; m_bOpen=false;
	m_nIndentCount=1; 
	m_chIndentSymbol[0]='\t'; m_chIndentSymbol[1]='\0';
}

void CSaxFormatter::DoIndent()
{
	for (unsigned int i=0; i<m_nIdentValue; i++)
	{
		for (unsigned int j=0; j<m_nIndentCount; j++)
		{
			Output(m_chIndentSymbol);
		}
	}
}


void CSaxFormatter::OnElementBegin(const char* szName)
{
	if (m_bOpen)
		Output(">");
	DoBreakLine();
	DoIndent();
	Output("<"); Output(szName);
	m_bOpen=true;
	m_bValue=false;
	Incr();
}

void CSaxFormatter::OnCloseSingleElement(const char* szName)
{
	Output("/>");
	Decr();
	m_bOpen=false;
}

void CSaxFormatter::OnElementEnd(const char* szName)
{
	if (m_bOpen)
		Output(">");
	if (!m_bValue && !m_bOpen)
	{
		DoBreakLine();
		Decr();
		DoIndent();
	}
	else
	{
		Decr();
	}
	Output("</"); Output(szName); Output(">");
	m_bOpen=false;
	m_bValue=false;
}

void CSaxFormatter::OnAttribute(const char* szName, const char* szValue)
{
	Output(" "); Output(szName); Output("="); Output("\""); Output(szValue); Output("\"");
}

void CSaxFormatter::OnCDATA(const char* szValue)
{
	if (m_bOpen)
		Output(">");
	DoBreakLine();
	DoIndent();
	Output("<![CDATA[ "); Output(szValue); Output(" ]]>");
	m_bValue=false;
	m_bOpen=false;
}

void CSaxFormatter::OnComment(const char* szText)
{
	if (m_bOpen)
		Output(">");
	DoBreakLine();
	DoIndent();
	Output("<!-- "); Output(szText); Output(" -->");
	m_bValue=false;
	m_bOpen=false;
}

void CSaxFormatter::OnDeclaration(const char* szVersion,const char* szEncoding, const char* szStandAlone)
{
	DoIndent();
	Output("<?xml ");
	if (szVersion)
		{Output("version=\""); Output(szVersion); Output("\"");}
	if (szEncoding) 
		{Output(" encoding=\""); Output(szEncoding); Output("\"");}
	if (szStandAlone)
		{Output("standalone=\""); Output(szStandAlone); Output("\"");}
	Output(" ?>"); 
}

void CSaxFormatter::OnProcessing(const char* szValue)
{
	if (m_bOpen)
		Output(">");
	DoBreakLine();
	DoIndent();
	Output("<? "); Output(szValue); Output(" ?>");
	DoBreakLine();
}

void CSaxFormatter::OnText(const char* szValue)
{
	if (m_bOpen)
	{
		Output(">");
		m_bValue=true;
	}
	else
	{
		DoIndent();
	}
	Output(szValue);
	m_bOpen=false;
}

void CSaxFormatter::SetIndentAsTab()
{
    m_chIndentSymbol[0] = '\t';
}

void CSaxFormatter::SetIndentAsBlank()
{
    m_chIndentSymbol[0] = ' ';
}

inline void CSaxFormatter::DoBreakLine()
{
    Output("\n");
}

inline void CSaxFormatter::Incr()
{
    m_nIdentValue++;
}

inline void CSaxFormatter::SetIndentCount(unsigned int nCount)
{
    m_nIndentCount = nCount;
}

inline void CSaxFormatter::Decr()
{
    m_nIdentValue--;
}
