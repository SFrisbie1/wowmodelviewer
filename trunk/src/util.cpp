#include "util.h"
#include "CxImage/ximage.h"
#ifdef _WIN32
#include <wx/msw/winundef.h>
#endif
#include <wx/choicdlg.h>
#include <wx/dir.h>

wxString gamePath;
wxString cfgPath;
wxString bgImagePath;

wxArrayString mpqArchives;

bool useLocalFiles = false;
bool useRandomLooks = true;
bool bHideHelmet = false;
bool bKnightEyeGlow = true;
bool bV310 = false;
bool bShowParticle = true;

// Model Export Options
// General Options
bool modelExportInitOnly = true;
bool modelExport_PreserveDir = true;
// Lightwave Options
bool modelExport_PreserveLWDir = true;
bool modelExport_LW_ExportLights = true;
bool modelExport_LW_ExportDoodads = true;
int modelExport_LW_DoodadsAs = 0;

long langID = -1;
long interfaceID = -1;
int ssCounter = 100; // ScreenShot Counter
int imgFormat = 0;

/*
wxString langCSConv[] =
{
	_T("iso-8859-1"),
	_T(""),
	_T(""),
	_T(""),
	_T("gb2312"),
	_T("big5"),
	_T(""),
	_T(""),
};
wxString CSConvStr;
*/

wxString CSConv(wxString str)
{
	if (langID <= 0) // || langCSConv[langID] == _T(""))
		return str;
	return wxConvLocal.cWC2WX(wxConvUTF8.cMB2WC(str.mb_str())); // from private.h
	//CSConvStr = wxCSConv(langCSConv[langID]).cWC2WX(wxConvUTF8.cMB2WC(str));
	//return CSConvStr;
}

float frand()
{
    return rand()/(float)RAND_MAX;
}

float randfloat(float lower, float upper)
{
	return lower + (upper-lower)*(rand()/(float)RAND_MAX);
}

int randint(int lower, int upper)
{
    return lower + (int)((upper+1-lower)*frand());
}

void fixname(std::string &name)
{
	for (size_t i=0; i<name.length(); i++) {
		if (i>0 && name[i]>='A' && name[i]<='Z' && isalpha(name[i-1])) {
			name[i] |= 0x20;
		} else if ((i==0 || !isalpha(name[i-1])) && name[i]>='a' && name[i]<='z') {
			name[i] &= ~0x20;
		}
	}
}
void fixnamen(char *name, size_t len)
{
	for (size_t i=0; i<len; i++) {
		if (i>0 && name[i]>='A' && name[i]<='Z' && isalpha(name[i-1])) {
			name[i] |= 0x20;
		} else if ((i==0 || !isalpha(name[i-1])) && name[i]>='a' && name[i]<='z') {
			name[i] &= ~0x20;
		}
	}
}

int wxStringToInt(const wxString& str)
{
	long number = 0;
	str.ToLong(&number);
	return number;
}

float round(float input, int limit = 2){
	if (limit > 0){
		input *= (10^limit);
	}
	input = int(input+0.5);
	if (limit > 0){
		input /= (10^limit);
	}
	return input;
}

void MakeDirs(wxString base, wxString paths){
	wxString NewBase = base;
	//wxLogMessage("MKDIR Paths\nBasePath: %s\nOthers Paths: %s", base, paths);
	wxString Paths[30];
	unsigned int PathNum = 0;
	while (paths.Find('\\')>0){
		Paths[PathNum] = paths.BeforeFirst('\\');
		wxString rep = Paths[PathNum];
		paths.Replace(rep.Append('\\'),"");
		//wxLogMessage("\nBuilding Paths: %s\npaths:%s",Paths[PathNum],paths);
		PathNum++;
	}
	Paths[PathNum] = paths;
	PathNum++;

	for (unsigned int x=0;x<PathNum;x++){
		NewBase = wxString(NewBase << '\\' << Paths[x]);
		//wxLogMessage("Attempting to create the following directory: %s",NewBase);
		mkdir(NewBase.c_str());
	}
}

void getGamePath()
{
#ifdef _WIN32
	HKEY key;
	DWORD t, s;
	LONG l;
	unsigned char path[1024];
	memset(path, 0, sizeof(path));

	wxString sNames[5];
	int nNames = 0;
	int sName = 0;

	// if it failed, look for World of Warcraft install
	const wxString regpaths[] = { 
		_T("SOFTWARE\\Blizzard Entertainment\\World of Warcraft"),
/* for beta
		_T("SOFTWARE\\Blizzard Entertainment\\World of Warcraft\\1"),
		_T("SOFTWARE\\Blizzard Entertainment\\World of Warcraft\\2"),
		_T("SOFTWARE\\Blizzard Entertainment\\World of Warcraft\\3"),
*/
		_T("SOFTWARE\\Blizzard Entertainment\\World of Warcraft\\PTR")
		 };
	int sTypes[2];

	for (size_t i=0; i<WXSIZEOF(regpaths); i++) {
		l = RegOpenKeyEx((HKEY)HKEY_LOCAL_MACHINE, regpaths[i], 0, KEY_QUERY_VALUE, &key);

		if (l == ERROR_SUCCESS) {
			s = sizeof(path);
			l = RegQueryValueEx(key, _T("InstallPath"), 0, &t,(LPBYTE)path, &s);
			if (l == ERROR_SUCCESS && wxDir::Exists(path)) {
				sNames[nNames] = path;
				if (i==1)
					sTypes[nNames] = 1;
				else
					sTypes[nNames] = 0;
				nNames++;
			}
			RegCloseKey(key);
		}
	}
	if (nNames == 1)
		sName = 0;
	else if (nNames >= 1) {
		sName = wxGetSingleChoiceIndex(_T("Please select a Path:"), _T("Path"), nNames, sNames);
		if (sName == -1)
			sName = 0;
	} else
		sName = -1;

//	if (sTypes[sName] == 1)
//		bPTR = true;

	// If we found an install then set the game path, otherwise just set to C:\ for now
	if (sName >= 0) {
		gamePath = sNames[sName];
		gamePath.append(_T("Data\\"));
	} else {
		gamePath = _T("C:\\");
	}
#else // linux - not sure what it should be set to for Mac osx
	gamePath = _T("/data/");
	
#endif
}

