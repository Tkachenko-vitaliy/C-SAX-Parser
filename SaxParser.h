// SaxParser.h: interface for the CSaxParser class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <istream>
#include <string>
#include <vector>

class CXSPHandler
{
public:
	virtual void OnOpenTag() {}
	virtual void OnCloseTag() {}
	virtual void OnNotLeadingChar(char c) {}
	virtual void OnDocumentBegin() {}
	virtual void OnDocumentEnd() {}
	virtual void OnElementBegin(const char* szName) {}
	virtual void OnElementEnd(const  char* szName) {}
	virtual void OnCloseSingleElement(const  char* szName) {}
	virtual void OnAttribute(const char* szName, const char* szValue) {}
	virtual void OnText(const char* szValue) {}
	virtual void OnCDATA(const char* szValue) {}
	virtual void OnComment(const char* szText) {}
	virtual void OnDeclaration(const char* szVersion,const char* szEncoding, const char* szStandAlone) {}
	virtual void OnProcessing(const char* szValue) {}
};

//Encoding types. Important: 16-bit encoding is not supported! (may be in the next version)
#define SPENC_UNKNOWN	0	/* Unknown encoding (Autodetection) */
#define SPENC_LEGACY	1	/* Some kind of 8-bit encoding*/
#define SPENC_UTF_8		2	/* UTF-8 */

#define SPE_OK					0
#define SPE_EMPTY				1
#define SPE_INVALID_FORMAT		2
#define SPE_INVALID_INSTANCE	3
#define SPE_TOO_BIG_VALUE		4
#define SPE_PROCESSING_NAME		5
#define SPE_RESERVED_NAME		6
#define SPE_MISSING_CLOSING		7
#define SPE_INVALID_DECL		8
#define SPE_VERSION				9
#define SPE_ENCODING			10
#define SPE_ELEMENT_NAME		11
#define SPE_MATCH				12
#define SPE_COMMENT				13
#define SPE_CDATA				14
#define SPE_EMPTY_REF			15
#define SPE_REF_SYMBOL			16
#define SPE_ATTR_NAME			17
#define SPE_ATTR_DESCR			18
#define SPE_ROOT_DATA			19
#define SPE_UNKNOWN_ENTITY		20
#define SPE_ROOT_CLOSE			21
#define SPE_DTD_SUPPORT			22
#define SPE_EOF					23
#define SPE_CDATA_CLOSE			24
#define SPE_MISSING_SEMI		25
#define SPE_MISSING_QUOTE		26
#define SPE_TEXT_BEFORE_ROOT	27
#define SPE_TEXT_AFTER_ROOT		28
#define SPE_WHITESPASE_OPEN		29
#define SPE_WHITESPASE_CLOSE	30
#define SPE_WHITESPACE_PROCESS	31	
#define SPE_COMMENT_CLOSE		32
#define SPE_ENCODING32			33
#define SPE_ENTITY_DOC_OPEN		34
#define SPE_CDATA_DOC_OPEN		35
#define SPE_DECLARATION_CLOSE	36
#define SPE_PROCESSING_CLOSE	37
#define SPE_DUBLICATE_ATTRIBUTE	38
#define SPE_INPUT_DATA_ERROR    39

class CSaxParserException : public std::exception
{

public:
    const char *what() const override;

    unsigned int GetCode() const { return m_nCode; }
    unsigned int GetLine() const { return m_nLine; }
    unsigned int GetColumn() const { return m_nColumn; }

private:
    friend class CSaxParser;

    CSaxParserException(unsigned int code, unsigned int line, unsigned int column) :
        m_nCode(code), m_nLine(line), m_nColumn(column)
    {

    }

    unsigned int m_nCode;
    unsigned int m_nLine;
    unsigned int m_nColumn;
};

class CSaxParser  
{
public:
	CSaxParser();
	
	void SetLimitValue(unsigned int nLimit); //Set a limit for value length (tag content). 0 means the limit is not set
	unsigned int GetLimitValue() const; //Return a limit for value length 
    void Parse(std::istream* pStream, CXSPHandler* pHandler, int encoding = SPENC_UNKNOWN); //Parse a document
	
private:
    unsigned int m_nLine;
    unsigned int m_nColumn;
    unsigned int m_nLimit;
    std::vector<std::string> m_StackItems;
    int m_nEncoding;
    bool m_bReadHeader;
    bool m_bEmpty;

    CXSPHandler* m_pHandler;
    std::istream* m_pStream;
    
    char GetChar();
    char ReadChar();
	void ReadSignature();
	void SkipWhiteSpace();
	bool IsEOF();
	void IncLine();
	void IncColumn();
    unsigned int GetLine() const;
    unsigned int GetColumn() const;
    void ThrowException(unsigned int code);
    void RethrowException(CSaxParserException& e, unsigned int nCheckCode, unsigned int nSubstituteCode);

	void PutBack(unsigned char c);
		
	void EnterProcessing();
	void EnterDeclaration();
	void EnterOpenElement(char c);
	void EnterClosingElement();
	void EnterComment();
	void EnterCDATA();
	void EnterDTD(char c);
	void EnterEntity(void* pData);
	void EnterAttribute(void* pAttr, char c);

    class CSPBuffer
    {
    public:
        CSPBuffer();
        void Put(char c);
        char Extract();
        char Get(unsigned int pos) const;
        void PutBack(char c);
        unsigned char Current() const;
        bool IsEmpty() const;
        char operator[](unsigned int i) const;
        const char* GetData() const;
        void Clear();
    private:
        unsigned int m_nCount;
        unsigned int m_nPos;
        char m_Data[4];
    };

    CSPBuffer m_buffer;

};