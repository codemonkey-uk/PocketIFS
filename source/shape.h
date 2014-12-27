//shape.h
//(c) T.Frogley 2015

#ifndef shape_h
#define shape_h

#include <iostream>
#include <cmath>

using std::endl;
using std::cin;
using std::cout;
using std::string;

//alternative getline function
inline string getline(std::istream& i)
{
   string s;
   while(i.good()){
      char c;
      i.get(c);
      if (i.gcount()==1 && c!='\n')
         s += c;
      else break;

   }
   return s;
}

inline void line(int c, int x1, int y1, int x2, int y2)
{
    // cout << c << endl;
    cout << x1 << "," << y1 << " " << x2 << "," << y2 << endl;
}

inline void DrawX(int c, int x, int y, int l)
{
    line(c,x-l,y-l,x+l,y+l);
    line(c,x-l,y+l,x+l,y-l);
}

struct p
{
    int p_x;
    int p_y;
    p* p_next;
};

#define sizeof_p sizeof(p)

typedef p* pointer_p;

extern int centre_x;
extern int centre_y;

inline pointer_p NewPoint(int x, int y)
{
	pointer_p result;
	result = (pointer_p)malloc(sizeof_p);
	if (result){
		result->p_x=x;
		result->p_y=y;
		result->p_next=0;
	}
	return result;
}

inline void DeletePoint(pointer_p p)
{
	pointer_p t;
	do{
	  t = p->p_next;
	  free(p);
	}while((p=t));
}

/*
inline pointer GetPoint()
{
	pointer result;
	waitp();
	result = NewPoint(
		penx(), peny()
	);
	return result;
}
*/

inline void DrawLine(
  pointer_p cur,
  int c)
{
	pointer_p next;
	next=cur->p_next;
	line(c,cur->p_x+centre_x,
	  cur->p_y+centre_y,
	  next->p_x+centre_x,
	  next->p_y+centre_y);
}

float Dist(pointer_p a,pointer_p b)
{
	return sqrt(
	  ((a->p_x-b->p_x)*
	   (a->p_x-b->p_x))+
	  ((a->p_y-b->p_y)*
	   (a->p_y-b->p_y))
	);
}

float Length(pointer_p a)
{
	float l;
	l = 0;
	do{
		if (a->p_next)
		  l = l + Dist(a,a->p_next);
	}while((a = a->p_next));
	return l;
}

//shape
struct s
{
    float s_cx;
    float s_cy;
    pointer_p s_points;
};

#define sizeof_s sizeof(s)

typedef s* pointer_s;

inline void DeleteShape(pointer_s s)
{
    DeletePoint(s->s_points);
    free(s);
}
/*
void CenterShape(pointer_s sh)
{
	int i;
	pointer_p s;
	i =centre_y=centre_x=0;
	s=sh->s_points;
	do{
	  centre_x = centre_x+s->p_x;
	  centre_y = centre_y+s->p_y;
	  i++;
	}while((s=s->p_next));
	centre_x=centre_x/i;
	centre_y=centre_y/i;
	s=sh->s_points;
	do{
		s->p_x=s->p_x-centre_x;
		s->p_y=s->p_y-centre_y;
	}while((s=s->p_next));
}

//end-line optimise shape
void ELOShape(pointer_p p)
{
	pointer a,b,c;
	a=b=c=0;
	do{
		c=b;
		b=a;
		a = p;
	}while(p = p->p_next);
	if (c){
		if(a->p_x==c->p_x && a->p_y==c->p_y)
		{
			free(a);
			b->p_next=0;
		}
	}
}
*/

void DrawShape(
  pointer_p cur, int col)
{
	do{
		DrawLine(cur,col);
		cur = cur->p_next;
	}while(cur->p_next);
}

void WriteShapeToCout(pointer_p cur)
{
	cout << centre_x << endl;
	cout << centre_y << endl;
	do{
		cout << cur->p_x << endl;
		cout << cur->p_y << endl;
		cur = cur->p_next;
	}while(cur);
	printf("!\n");
}

inline pointer_s ReadShapeFromCin()
{
	pointer_p head,cur;
	string x,y;
	cin >> centre_x;
	cin >> centre_y;
	cin >> x;
	cin >> y;

	// if (!cin.good()) return 0;

	head=cur=NewPoint(atoi(x.c_str()),atof(y.c_str()));

	x = getline(cin);
	while(cur && x!="!"){
		y = getline(cin);
		if (!cin.good()){
			//DeletePoint(head);
			//return 0;
			break;
		}
		cur->p_next=
		  NewPoint(atoi(x.c_str()),atof(y.c_str()));
		DrawLine(cur,1);
		cur=cur->p_next;
		cin >> x;
	}

	pointer_s result;
	result=(pointer_s)malloc(sizeof_p);
	result->s_points=head;
	result->s_cx=centre_x;
	result->s_cy=centre_y;
	return result;
}
/*
pointer GetShape()
{
	pointer head,cur,next;
	centre_y=centre_x=0;
	cur = head = GetPoint();
	DrawX(1,cur->p_x,
		cur->p_y,1);
	do{
		do{
			next=cur[p_next]=
			  GetPoint();
		}while(Length(cur)<4);
		if (Dist(head,next)<4){
		  next[p_x]=head[p_x];
		  next[p_y]=head[p_y];
		}
		cur[p_next] = next;
		DrawLine(cur, 1);
		cur = cur[p_next];
	}while(Dist(head,next)>4);
	return head;
}
*/
#endif // shape_i