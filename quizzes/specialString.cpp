#include <cstring>
#include <cstdio>
#include <iostream>

class String
{
	public:
		String(); 
		String(const char* str);
		String(const String& other);
		~String();

		char& operator[](size_t index);

		void operator=(const String& other);
		void operator=(const char* str);
		void operator=(const char c);
		static size_t GetInstances();
		const char* CStr() const; 
	private:
		char* Init(const char* str);
		static size_t m_instance;
		char* m_str;
};

String::String() : m_str(Init("ABC"))
{
    ++m_instance;
}

String::String(const char* str) : m_str(Init(str))
{
    m_instance++;
}
String::String(const String& other) : m_str(Init(other.m_str))
{
    m_instance++;
}

String::~String()
{
	delete[] m_str;

	m_instance--;

    m_str = NULL;
}

char& String::operator[](size_t index)
{
	return m_str[index];
}

void String::operator=(const String& other)
{
	if (this != &other)
    {
        delete[] m_str;     
        m_str = Init(other.m_str);  
    }
}

void String::operator=(const char* str)
{
	delete[] m_str;
    m_str = Init(str);
}

void String::operator=(const char c)
{
	size_t i = 0;

	for(i = 0; i < strlen(m_str); i++)
	{
		m_str[i] = c;
	}

}

size_t String::GetInstances()
{
	return m_instance;	
}
const char* String::CStr() const
{
	 return m_str; 
}

char* String::Init(const char* str)
{
	char* temp = new char[strlen(str) + 1];
	strcpy(temp, str);
	return temp;
}

size_t String::m_instance = 0;

int main()
{
    /*String s1("1234");
    s1 = '@'; 
	s1[0] = 'r'; 
	printf("%s\n", s1.CStr());

    String s2("1234");
    std::cout << s2.GetInstances() << std::endl; 
	s2 = '&';
	s2[0] = s1[0]; 
	printf("%s\n", s2.CStr()); 
    std::cout << String::GetInstances() << std::endl; */
	String s1("1234");  
    s1 = '@'; // will change s1 to "@@@@"   
	printf("%s\n", s1.CStr()); 
    String* s2 = new String;   
	String s3;         
    std::cout<< s2->GetInstances();   
	printf("\n%s\n", s2->CStr());  

	s2[0] = s1[0]; 
	s3[0] = s1[0]; 
	printf("\n%s\n", s2->CStr()); 
	printf("\n%s\n", s3.CStr()); 
    delete s2;  
    std::cout << String::GetInstances(); 
}