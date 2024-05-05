#include<iostream>
#include<string>
#include<cassert>

int main(void)
{

	std::string reverse_words(const std::string & str);

   /* std::string str = "String; 2be reversed...";
    assert(reverse_words(str) == "gnirtS; eb2 desrever...");*/

    std::string str;
    std::getline(std::cin, str);
    std :: cout << reverse_words(str) << std::endl; 


	return 0;
}

/*
Function Name        : reverse_words
Function Return type : string
Function Parameter   :  [I/P] The function recevied only one parameter 
                        which is string
Funtion Definition   : 'reverse_words' function will reverse the 
                        words not special characters.
                        Example : I/P => Hello@#$ Bye!!!
                                  O/P => olleH@#$ eyB!!!
*/
std::string reverse_words(const std::string& strInput)
{
    std::string strResult;
    bool bWordCheck = false;
    std::string word;

    /*
    loop is important to identify the character.
    */
    for (char c : strInput) 
    {
        // isalnum() will identify character is num or character
        // if codition gets true the that will be pushed in string using push_back() function
        // if condition gets false it will go in else block.
        // when space is found bWordCheck gets true and reverse() gets called.
        // otherwise its just push the character in the string 
        if (std::isalnum(c)) 
        {
            word.push_back(c);
            bWordCheck = true;
        }
        else 
        {
            if (bWordCheck)
            {
                std::reverse(word.begin(), word.end());
                strResult += word;
                word.clear();
            }
            strResult.push_back(c);
            bWordCheck = false;
        }
    }

 
    // bWordCheck is true when last words are still push in the string but not reverse
    // bWordCheck is false when special charater are found so no need to reverse
    if (bWordCheck)
    {
        std::reverse(word.begin(), word.end());
        strResult += word;
    }

    return strResult;
}
