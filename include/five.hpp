#include <string>



class Five {
private:
    unsigned char* digits; 
    size_t size;           

    void validateDigit(unsigned char digit);
    void removeLeadingZeros();
    int compare(const Five& other); 

public:
    Five();                               
    Five(const std::string& value);       
    Five(const Five& other);              
    Five(const size_t& n, unsigned char t = 0);

    virtual ~Five();

    Five operator+(const Five& other);    
    Five operator-(const Five& other); 

    bool operator>(const Five& other);   
    bool operator<(const Five& other);        
    bool operator==(const Five& other);     
    Five operator=(const Five& other);

    std::string getString();
    size_t getSize();
    unsigned char getDigit(size_t index);

};

