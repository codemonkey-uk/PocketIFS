//trans.h
// C/C++ port from PocketC of trans.i from PocketIFS
//(c) T.Frogley 2015

#ifndef trans_i
#define trans_i

//trans
struct t
{
    float t_a;
    float t_b;
    float t_c;
    float t_d;
    float t_e;
    float t_f;
    t* t_next;
};

typedef t* pointer_t;
#define sizeof_t sizeof(t)

pointer_t NewTrans(
  float a, float b, float c,float d,
  float e, float f)
{
	pointer_t p;
	if ((p = (pointer_t)malloc(sizeof_t)))
	{
		p->t_a=a;
		p->t_b=b;
		p->t_c=c;
		p->t_d=d;
		p->t_e=e;
		p->t_f=f;
		p->t_next=0;
	}
	return p;
}

pointer_t NewTrans2()
{
	pointer_t p;
	if ((p = (pointer_t)malloc(sizeof_t))){
		// settype(p,6,'f');
	}
	return p;
}

void DeleteTrans(pointer_t p)
{
	pointer_t  t;
	do{
	  t = p->t_next;
	  free(p);
	}while((p=t));
}

void WriteTransToCout(pointer_t p)
{
  do{
      cout << p->t_a << "\n" <<
      p->t_b << "\n" <<
      p->t_c << "\n" <<
      p->t_d << "\n" <<
      p->t_e << "\n" <<
      p->t_f << "\n";
  }while((p = p->t_next));
  cout << "!\n";
}

inline pointer_t ReadTransFromCin()
{
	pointer_t head,cur;
	string a;
	float b,c,d,e,f;
	cin >> a;
	cin >> b;
	cin >> c;
	cin >> d;
	cin >> e;
	cin >> f;

	if (!cin.good()) return 0;

	head=cur=
	  NewTrans(atof(a.c_str()),b,c,d,e,f);
	cin >> a;
	while(cur && a!="!"){
		cin >> b;
		cin >> c;
		cin >> d;
		cin >> e;
		cin >> f;
		if (!cin.good()){
			DeleteTrans(head);
			return 0;
		}
		cur->t_next=
		  NewTrans(atof(a.c_str()),b,c,d,e,f);
		cur=cur->t_next;
		cin >> a;
	}
	return head;
}

void DrawShapeTrans(
  pointer_s s,
  float a, float b, float c,float d,
  float e, float f,
  int col)
{
  pointer_p cur;
  pointer_p nxt;
  int x1,y1,x2,y2;

  cur = s->s_points;
  nxt = cur->p_next;

  x2 = cur->p_x*a +
      cur->p_y*b +
      e + s->s_cx;
  y2 = cur->p_x*c +
      cur->p_y*d +
      f + s->s_cy;

  // initial point in line
  int n = 1;
  cout << x2 << "," << y2;

  do{
    x1=x2; y1=y2;
    x2 = nxt->p_x*a +
      nxt->p_y*b +
      e + s->s_cx;
    y2 = nxt->p_x*c +
      nxt->p_y*d +
      f + s->s_cy;

    // skip points in line on same pixel as last
    if (x2!=x1 || y2!=y1)
    {
        n++;
        cout << " " << x2 << "," << y2;
    }

    cur = nxt;
  }while((nxt = nxt->p_next));

  // single pixel line (point) still needs start & end pair
  if (n==1) cout << " " << x2 << "," << y2;

  cout << endl;
}

/*
#include "pifs_icons.i"

Toggle(int mode)
{
	rect(3,160-(mode+1)*10,1,
	  159-mode*10,10,
	  0);
}

pointer GetTrans(pointer head)
{
	float p,q,r,s,e,f;
	float a,b,c,d;
	int oldmode,cx,cy,px,py;
	int mode;
	int lock;

	bitmap(160-10,1,ROTATE);
	bitmap(160-20,1,SCALE);
	bitmap(160-30,1,MOVE);
	bitmap(160-40,1,LOCK);
	bitmap(160-50,1,HAPPY);

	p=q=0;
	r=s=1;

	Toggle(mode);

	while(event(1)!=2);
	cy=peny();
	cx=penx();

	do{

	py=peny();
	if (lock) px=py;
	else px=penx();

	if (mode==0){
		q =(float)(py-cy)
		  *7/160;
		p =(float)(px-cx)
		  *7/160;
	}
	else if (mode==1){
		s = (float)(py-cy)
		  /80;
		r = (float)(px-cx)
		  /80;
	}
	else{
		e=penx()-cx;
		f=peny()-cy;
	}

	a = r * cos(p);
	b = -s * sin(q);
	c = r * sin(p);
	d = s * cos(q);
	DrawShapeTrans(head,
	  a, b,  c, d, e, f,
	  3);
	if (event(1)==3){

		do{
		  while(event(1)!=2);
		  cx = penx();
		  cy = peny();
		  if (cy<=10){
		    if (cx>=110){
		      Toggle(mode);
	 	      oldmode=mode;
	 	      mode = (159-cx)/10;
		      Toggle(mode);
		      if(mode==3){
		        lock=!lock;
		        mode=oldmode;
		       Toggle(mode);
		      }
		    }
		  }
		  else break;
		}while(mode!=4);

		if (mode==4){
		  Toggle(mode);
		  mode = oldmode;
		  Toggle(mode);
		  if (confirm("Happy?"))
		    break;
		}
		if (lock) cx=cy;
		if (mode==0){
			cx = cx - p/7*160;
			cy = cy - q/7*160;
		}
		else if (mode==1){
			cx = cx - r*80;
			cy = cy - s*80;
		}
		else{
			cx=penx()-e;
			cy=peny()-f;
		}
	}
	DrawShapeTrans(head,
	  a, b,  c, d, e, f,
	  3);
	}while(1);
	DrawShapeTrans(head,
	  a, b,  c, d, e, f,
	  1);
	Toggle(mode);
	return
	  NewTrans(a, b, c, d, e, f);
}
*/
#endif//trans_i