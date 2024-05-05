// To add path in env use following command
//  export BuildNum=100
//  export SourcePath=/home/aishwarya/code
//  Tip this command are use for tempory purpose. Only limited to terminal session

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int updateVersion(const std::string&, const std::string&, const std::string&);
 
int main() 
{
    // Get the Path from the environment variable
    std::string sourcePath = std::getenv("SourcePath");
    if(sourcePath.length() == 0)
    {
        std::cerr << "Error: SourcePath environment variable is not set." << std::endl;
        return 1;
    }
  
    // Get the build number from the environment variable
    const char* buildNumStr = std::getenv("BuildNum");
    if (!buildNumStr) 
    {
        std::cerr << "Error: BuildNum environment variable is not set." << std::endl;
        return 1;
    }

    std::string buildNum = buildNumStr;

    // Update SConstruct file 
    std::string sconstructPath = sourcePath + "/develop/global/src/SConstruct";
    int ret = updateVersion(sconstructPath, "point=", buildNum);
    if(ret == -1)
    {
         std::cerr << "Error: Unable to open file " << sconstructPath << std::endl;
    }
    else if(ret == 1)
    {
        std::cout<< "not found"<<std::endl;
    }
    else
    {
        std::cout << "Build version updated to " << buildNum << std::endl;
    }
    
    // Update VERSION file
    std::string versionPath = sourcePath + "/develop/global/src/VERSION";
    ret = updateVersion(versionPath, "ADLMSDK_VERSION_POINT=",buildNum);

    if(ret == -1)
    {
         std::cerr << "Error: Unable to open file " << sconstructPath << std::endl;
    }
    else if(ret == 1)
    {
        std::cout<< "not found"<<std::endl;
    }
    else
    {
        std::cout << "Build version updated to " << buildNum << std::endl;
    }

    return 0;
}

/*
Function name : updateVersion

Function return type : int
                        0 => succesful return
                        1 => operation not done
                        -1 => file opening failure (errornous return)

Function parameter : 1] [IP] filePath is a type of string &(reference) data type
                        which will accpect filepath as a parameter. 
                     2] [IP] searchString is type of string & data type
                        which will accpect string which is going to search in the file
                     3] [IP] newString is type of string & data type 
                        which will accpect replace string.
  
Function definition : 
                    If file open operation failed then it will return -1;
                    Function will open the file which will send as a parameter.
                    Search string in buffer data of file content.
                    If Search string is found it will replace the string with new String.
                    If Search is string is not found it will return 1.
                    If new String is replaced then it will return 0.
                     
*/
// Function to update the version number in a file
int updateVersion(const std::string& filePath, const std::string& searchString, const std::string& newString) 
{
    // File open in read mode
    std::ifstream inFile(filePath);
    if (!inFile) 
    {
        // File opened failed.
        return -1;
    }

    // read the whole data of opened file
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();

    // Find the searchString , it will return postion of the string
    size_t pos = fileContent.find(searchString);

    if (pos != std::string::npos)
    {
        // string will replace with new string
        fileContent.replace(pos + searchString.length(), newString.length(), newString);
        // file close
        inFile.close();

        // file opened in write mode
        std::ofstream outFile(filePath);
        outFile << fileContent;
        outFile.close();
        std::cout << "File Updated at this location. " << filePath << std::endl;
    }
    else 
    {
        std::cerr << "Error: StrisearchString \"" << searchString << "\" not found in this file " << filePath << std::endl;
        inFile.close();
        return 1;
    }
    return 0;
}


