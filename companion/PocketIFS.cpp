// PocketIFS.cpp
// C/C++ port from PocketC of PocketIFS
// (c) T.Frogley 2015

//config
#define PROFILE

int depth = 6;
#define RECURSIVE_DEPTH depth

#ifdef PROFILE
#include "profile.h"
#endif

#include "pifs_text.h"
#include "GNUGPL.h"

#include "ifs.h"

int centre_x = 0;
int centre_y = 0;

using std::cerr;

void alert(std::string msg)
{
    cerr << msg << endl;
}

int main(int argc, char** argv)
{
    pointer_ifs ifs;
    pointer_s s;
    pointer_t t;
    pointer_p p;
    std::string msg;
    int loaded;

    // read recursive depth from commandline
    if (argc>1)
    {
        int d = atoi(argv[1]);
        if (d!=0) depth=d;
    }

    msg=GNUGPLmsgEnglish(
      APPNAME, VERSION,
      REV_DATE, "T. Frogley");

    alert(msg);

    loaded = 0;

    std::string h;
    h = getline(cin);

    s = ReadShapeFromCin();
    if (s){
      t=ReadTransFromCin();
      if (t) loaded = 1;
      else DeleteShape(s);
    }

    if (!loaded)
      alert(LOADFAILMSG);

    ifs = NewIFS(s,t);

    Draw(ifs,
      cos(0),
      -sin(0),
      sin(0),
      cos(0),
      0,0);

    DeleteIFS(ifs);
}
