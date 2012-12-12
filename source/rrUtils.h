#ifndef rrUtilsH
#define rrUtilsH

//---------------------------------------------------------------------------
#if defined(WIN32)
#include <windows.h>
#endif

#include <float.h>    //ms compatible IEEE functions, e.g. _isnan
#include <vector>
#include <string>
#include "rrExporter.h"
#include "rrConstants.h"
#include "rrStringList.h"
#include "rrSimulationSettings.h"
#include "rrStringUtils.h"
using std::vector;
using std::string;
namespace rr
{


RR_DECLSPEC const char*   	getVersion();


//Misc.
RR_DECLSPEC std::size_t     IndexOf(std::vector<std::string>& vec, const std::string& elem );
RR_DECLSPEC bool            IsNaN(const double& aNum);
RR_DECLSPEC bool            IsNullOrEmpty(const string& str);    //Can't be null, but empty
RR_DECLSPEC void            Pause(bool doIt = true, const string& msg = EmptyString);

//String utilities
RR_DECLSPEC string          RemoveTrailingSeparator(const string& fldr, const char sep = PathSeparator);//"\\");

//File  Utilities
RR_DECLSPEC bool            FileExists(const string& fileN);
RR_DECLSPEC bool            FolderExists(const string& folderN);
RR_DECLSPEC bool            CreateFolder(const string& path);

#undef CreateFile
RR_DECLSPEC bool     		CreateFile(const string& fName, int mode = ios::trunc);

RR_DECLSPEC const string	getParentFolder(const string& path);
RR_DECLSPEC const string    getCurrentExeFolder();
RR_DECLSPEC string          GetUsersTempDataFolder();
RR_DECLSPEC const string    getCWD();
RR_DECLSPEC const char		getPathSeparator();

RR_DECLSPEC vector<string>  GetLinesInFile(const string& fName);
RR_DECLSPEC string  		GetFileContent(const string& fName);
RR_DECLSPEC void            CreateTestSuiteFileNameParts(int caseNr, const string& postFixPart, string& FilePath, string& modelFileName, string& settingsFileName);
RR_DECLSPEC string          GetTestSuiteSubFolderName(int caseNr);

//CArray utilities
RR_DECLSPEC bool            CopyCArrayToStdVector(const int* src,     vector<int>& dest, int size);

RR_DECLSPEC bool            CopyCArrayToStdVector(const double* src,  vector<double>& dest, int size);
RR_DECLSPEC double*         CreateVector(const vector<double>& vec);

RR_DECLSPEC bool            CopyValues(vector<double>& dest, double* source, const int& nrVals, const int& startIndex);

RR_DECLSPEC vector<double>  CreateVector(const double* src, const int& size);

RR_DECLSPEC bool            CopyCArrayToStdVector(const bool* src,    vector<bool>& dest, int size);
RR_DECLSPEC bool            CopyStdVectorToCArray(const vector<double>& src, double* dest,  int size);
RR_DECLSPEC bool            CopyStdVectorToCArray(const vector<bool>&   src,  bool*  dest,  int size);

//SelectionList
RR_DECLSPEC StringList      getSelectionListFromSettings(const SimulationSettings& settings);

#if defined(WIN32)// DLL Functions
RR_DECLSPEC HINSTANCE       LoadDLL(const string& dll);
RR_DECLSPEC bool       		UnLoadDLL(HINSTANCE dllHandle);
RR_DECLSPEC FARPROC 		GetFunctionPtr(const string& funcName, HINSTANCE DLLHandle);
#endif

} // rr Namespace
#endif
