#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class CMyString{
public:
	CMyString(char* pData = NULL);
	CMyString(const CMyString& str);
	~CMyString(void);

	CMyString &operator=(const CMyString &str);

private:
	char* m_pData;		
};

CMyString &CMyString::operator=(const CMyString &str){
   
   /* Solution 1    
	if(this == &str)
		return *this;

	delete []m_pData;
	m_pData = NULL;

	m_pData = new char[strlen(str.m_pData)+1];
	strcpy(m_pData, str.m_pData);
	return *this;
	*/

	if(this != &str){
		CMyString strTemp(str);
		
		char* pData = strTemp.m_pData;
		strTemp.m_pData = m_pData;
		m_pData = pData;
	}
	return *this;
}

int main(){
 	char cst[] = "Hello World";
    CMyString str1(cst);
    CMyString str2;
    str2 = str1;

    return 0;
}