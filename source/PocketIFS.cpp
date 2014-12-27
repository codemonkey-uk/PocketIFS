//PocketIFS
//(c) T.Frogley 2015

//config
//#define NOISY
//#define PROFILE

int depth = 6;
#define RECURSIVE_DEPTH depth

#ifdef PROFILE
#include "profile.i"
#endif

#include "pifs_text.h"
//#include "GNUGPL"

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

    int d = atoi(argv[1]);
    if (d!=0) depth=d;
    /*
	clear();
	msg=GNUGPLmsgEnglish(
	  APPNAME, VERSION,
	  REV_DATE, "T. Frogley");
	puts(msg+'\n');

	if (!mathlib()){
		alert(NOMATHLIBMSG);
		return;
	}

	graph_on();
	title(APPNAME+VERSION);

	alert(msg);
    */
	loaded = 0;
	//if (mmfind(MEMOID)){
	//  if (confirm(LOADMEMOMSG))
	//  {
	    // mmgetl();
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
	//  }
	//}
    /*
	if (s==0){
	  s=GetShape();
	  ELOShape(s);
	  CenterShape(s);
	}
	if (t==0){
	  p=t=GetTrans(s);
	  while(confirm("Another?")){
	    p[t_next] = GetTrans(s);
	    p=p[t_next];
	  }
	}
    */
	ifs = NewIFS(s,t);

    // WriteShapeToCout(s->s_points);
    // WriteTransToCout(t);

	// clearg();
	Draw(ifs,
	  cos(0),
	  -sin(0),
	  sin(0),
	  cos(0),
	  0,0);

#ifdef NOISY
	beep(1);
#endif

#ifdef RECURSIVE_DEPTH
	// waitp();
#endif
/*
	if (loaded == 0){
	  if (confirm(SAVE2MEMOMSG))
		SaveIFS(s,t);
#ifdef NOISY
		beep(1);
#endif
	}

	waitp();

	graph_off();
*/
	DeleteIFS(ifs);
}
