
C++ SAX parser is designed for parsing of XML document using SAX model. It scans input XML document and calls appropriate functions for every XML tree item (element, element content, attribute, text, remark, etc).

The implementation is located in files SaxParser (h,cpp). In order to run, create CSaxParser class and call Parse method.

void Parse(std::istream* pStream, CXSPHandler* pHandler, int encoding = SPENC_UNKNOWN);

This method accepts 3 parameters:
1)	Input stream from which the document content is going to be read;
2)	the user-implemented interface for callback calls;
3)	supposed document encoding

If some error occurs, the exception CSaxParserException will be thrown.
If necessary, you can set a limit for tree item length. If some item length exceeds the limit, an error will be generated.

An example of using you can see in SaxParserText.cpp. It accepts the input text file in XML format and creates output XML text file with tree view formatting. Thus, if the input text is presented in “plain” form (continuous solid text stream), the output file will be presented in tree view form with indents and breaklines.

If you have quiestions, write me to Tkachenko_vitaliy@hotmail.com
