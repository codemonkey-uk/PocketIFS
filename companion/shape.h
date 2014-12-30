//shape.h
// C/C++ port from PocketC of shape.i from PocketIFS
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

struct p
{
    int p_x;
    int p_y;
    p* p_next;
};

#define sizeof_p sizeof(p)

typedef p* pointer_p;

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

bool operator<(const p& lhs, const p& rhs)
{
	return lhs.p_x < rhs.p_x || (lhs.p_x == rhs.p_x && lhs.p_y < rhs.p_y);
}

bool operator!=(const p& lhs, const p& rhs)
{
	return lhs.p_x != rhs.p_x || lhs.p_y != rhs.p_y;
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

inline void WriteShapeToCout(pointer_s s)
{
	cout << s->s_cx << endl;
	cout << s->s_cx << endl;
	pointer_p cur = s->s_points;
	do{
		cout << cur->p_x << endl;
		cout << cur->p_y << endl;
		cur = cur->p_next;
	}while(cur);
	cout << "!\n";
}

inline pointer_s ReadShapeFromCin()
{
	pointer_p head,cur;
	string x,y;
	int cx, cy;
	cin >> cx;
	cin >> cy;
	cin >> x;
	cin >> y;

	if (!cin.good()) return 0;

	head=cur=NewPoint(atoi(x.c_str()),atof(y.c_str()));

	x = getline(cin);
	while(cur && x!="!"){
		y = getline(cin);
		if (!cin.good()){
			DeletePoint(head);
			return 0;
		}
		cur->p_next=
		  NewPoint(atoi(x.c_str()),atof(y.c_str()));
		cur=cur->p_next;
		cin >> x;
	}

	pointer_s result;
	result=(pointer_s)malloc(sizeof_p);
	result->s_points=head;
	result->s_cx=cx;
	result->s_cy=cy;
	return result;
}

#endif // shape_i