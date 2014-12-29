// ifs.h
// C/C++ port from PocketC of ifs.i from PocketIFS
// (c) T.Frogley 2015

#ifndef ifs_i
#define ifs_i

#include "shape.h"
#include "trans.h"

struct ifs
{
    pointer_s ifs_shape;
    pointer_t ifs_trans;
};

#define sizeof_ifs sizeof(ifs)

typedef ifs* pointer_ifs;

inline pointer_ifs NewIFS(pointer_s shape, pointer_t trans)
{
	pointer_ifs result;
	if ((result=(pointer_ifs)malloc(sizeof(ifs)))){
		result->ifs_shape=shape;
		result->ifs_trans=trans;
	}
	return result;
}

inline void DeleteIFS(pointer_ifs p)
{
	DeleteShape( p->ifs_shape );
	DeleteTrans( p->ifs_trans );
	free(p);
}

#ifndef RECURSIVE_DEPTH
Draw(pointer ifs,
  float a, float b, float c,float d,
  float e, float f)
{
	pointer head;
	pointer t,s;
	pointer head,tail;
	pointer shape;
	pointer trans;

	shape = ifs[ifs_shape];
	trans = ifs[ifs_trans];

	tail = head =
	  NewTrans(a,b, c,d,e,f);

	//empty
	s = NewTrans2();

	//eat up events
	while(event(0));

#ifdef PROFILE
Profile_Start();
#endif

	do{
	  DrawShapeTrans(shape,
	    head[t_a], head[t_b],
	    head[t_c], head[t_d],
	    head[t_e], head[t_f],
	    1);

#ifdef PROFILE
	profile_operations
	  =profile_operations+1;
#endif

	  t=trans;
	  s[t_a]=(t[t_a]*head[t_a])
	    +(t[t_c]*head[t_b]);
	  s[t_b]=(t[t_b]*head[t_a])
	    +(t[t_d]*head[t_b]);
	  s[t_c]=(t[t_a]*head[t_c])
	    +(t[t_c]*head[t_d]);
	  s[t_d]=(t[t_b]*head[t_c])
	    +(t[t_d]*head[t_d]);
	  s[t_e]=(t[t_e]*head[t_a])
	    +(t[t_f]*head[t_b])
	    +head[t_e];
	  s[t_f]=(t[t_e]*head[t_c])
	    +(t[t_f]*head[t_d])
	    +head[t_f];
	  s[t_next] = 0;
	  tail[t_next] = s;
	  tail = s;

	  while(t = t[t_next]){
	    tail[t_next] = NewTrans(
	      (t[t_a]*head[t_a])
	        +(t[t_c]*head[t_b]),
	      (t[t_b]*head[t_a])
	        +(t[t_d]*head[t_b]),
	      (t[t_a]*head[t_c])
	        +(t[t_c]*head[t_d]),
	      (t[t_b]*head[t_c])
	        +(t[t_d]*head[t_d]),
	      (t[t_e]*head[t_a])
	        +(t[t_f]*head[t_b])
	        +head[t_e],
	      (t[t_e]*head[t_c])
	        +(t[t_f]*head[t_d])
	        +head[t_f]
	    );
	    if (tail[t_next])
	      tail = tail[t_next];
	  }

	  if(event(0))
#ifndef PROFILE
	    if (confirm(INTERRUPTMSG))
	      break;
	    else //eat events
	      while(event(0));
#else
	      break;
#endif
	  s = head;
	}while(head = head[t_next]);

#ifdef PROFILE
Profile_Stop();
#endif

	//free memory
	if (s) free(s);
 	if (head) DeleteTrans(head);
}
#else //if RECURSIVE_DEPTH
inline void DrawR(pointer_ifs ifs,
  float a, float b, float c,float d,
  float e, float f, int level)
{
	float a1,b1,c1,d1,e1,f1;
	pointer_t trans;

	DrawShapeTrans(ifs->ifs_shape->s_points,
	  a, b, c, d, e, f,
	  1);

#ifdef PROFILE
	profile_operations
	  =profile_operations+1;
#endif

	if (level<=0) return;
	trans = ifs->ifs_trans;

	do{
	  a1=(trans->t_a*a)
	    +(trans->t_c*b);
	  b1=(trans->t_b*a)
	    +(trans->t_d*b);
	  c1=(trans->t_a*c)
	    +(trans->t_c*d);
	  d1=(trans->t_b*c)
	    +(trans->t_d*d);
	  e1=(trans->t_e*a)
	    +(trans->t_f*b)
	   +e;
	  f1=(trans->t_e*c)
	    +(trans->t_f*d)
	    +f;
	  DrawR(ifs,
	    a1, b1, c1, d1, e1, f1,
	    level-1);
	  trans = trans->t_next;
	}while(trans);
}
void Draw(pointer_ifs ifs,
  float a, float b, float c,float d,
  float e, float f)
{
#ifdef PROFILE
Profile_Start();
#endif

  DrawR(ifs,a,b,c,d,e,f,
    RECURSIVE_DEPTH);

#ifdef PROFILE
Profile_Stop();
#endif
}
#endif//RECURSIVE_DEPTH
/*
SaveIFS(pointer s, pointer t)
{
	if (mmfind(MEMOID)){
	if (confirm(CONFIRMDELETEMSG
	)) mmdelete();else return;}

	mmnew();
	mmputs(MEMOID + "\n");
	WriteShapeToMemo(s);
	WriteTransToMemo(t);
}
*/
#endif//ifs_i