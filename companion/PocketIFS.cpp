// PocketIFS.cpp
// C/C++ port from PocketC of PocketIFS
// (c) T.Frogley 2015

// TODO:
// * Add number of iterations as argument for iterative mode
// * more output format modes / rasterised pixel output

//config
#define PROFILE

#ifdef PROFILE
#include "profile.h"
#endif

#include "pifs_text.h"
#include "GNUGPL.h"

#include "ifs.h"

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

    msg=GNUGPLmsgEnglish(
      APPNAME, VERSION,
      REV_DATE, "T. Frogley");

    alert(msg);

    int default_mode = MODE_RECURSIVE;
    int default_depth = 6;

    int mode = default_mode;
    int mode_arg = default_depth;
    bool just_leaf = false;
    bool raw_points = false;

    // read mode and mode-argument from commandline
    int state = 0;
    for (int i=1; i!=argc; ++i)
    {
        const char* c = argv[i];
        if (*c=='-') c++;
        if (*c=='-') c++;

        if (state == MODE_NONE)
        {
            if (*c=='r' || *c=='d') mode = MODE_RECURSIVE;
            if (*c=='t') mode = MODE_TIMED;
            if (strcmp("leaf", c)==0) just_leaf = true;
            if (strcmp("raw", c)==0) raw_points = true;
            state = mode;
        }
        else if (state == MODE_RECURSIVE)
        {
            mode_arg = atoi(c);
            cerr << "Rendering (recursive) to depth: " << mode_arg << endl;
            state = MODE_NONE;
        }
        else if (state == MODE_TIMED)
        {
            mode_arg = (int) (atof(c) * CLOCKS_PER_SEC);
            cerr << "Rendering (iterative) for " << (float)mode_arg/CLOCKS_PER_SEC << "s" << endl;
            state = MODE_NONE;
        }
    }

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

    Outp out;

    Draw(ifs,
      cos(0),
      -sin(0),
      sin(0),
      cos(0),
      0,0,
      mode, mode_arg, just_leaf,
      &out);

    out.FlushLines(!raw_points);
    DeleteIFS(ifs);
}
