/*
<svg xmlns="http://www.w3.org/2000/svg"
    xmlns:xlink="http://www.w3.org/1999/xlink">

  <polygon points="50,5   100,5  125,30  125,80 100,105
                   50,105  25,80  25, 30"
          style="stroke:#660000; fill:#cc3333; stroke-width: 3;"/>

</svg>
*/

//IO headers
#include <iostream>
#include <fstream>

#include "geometry/vector2d.h"
#include "geometry/aabb2d.h"

#include "poly.h"

using namespace std;

//alternative getline function
inline string getline(istream& i)
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

typedef Geometry::VectorN<double, 2> Point;

typedef Geometry::VectorN<int, 3> Colour;

string Colour2Stroke(const Colour& rhs)
{
    char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    string result = "#";
    result += hex[ rhs[0]/16 ];
    result += hex[ rhs[0]%16 ];
    result += hex[ rhs[1]/16 ];
    result += hex[ rhs[1]%16 ];
    result += hex[ rhs[2]/16 ];
    result += hex[ rhs[2]%16 ];
    return result;
}

int main(int argv, char** argc)
{
    cout << "<svg xmlns=\"http://www.w3.org/2000/svg\"" << endl;
    cout << "\txmlns:xlink=\"http://www.w3.org/1999/xlink\">" << endl;

    std::string shape = (argv>1) ? argc[1] : "polyline";
    std::string stroke = "#000000";

    //get the polys from std-in
    while(cin.good() && !cin.eof()){
        try{
            //get the poly
            string l = getline(cin);
            Poly< Point > p(l);
            if (p.Count()==1)
            {
                stroke = Colour2Stroke( ParsePoint<Colour>(l) );
                continue;
            }
            else if (p.Count()>1)
            {
                cout << "<" << shape << " points=\"";
                cout << p;
                cout << "\" ";
                cout << "style=\"stroke:"<<stroke<<"; fill:none; stroke-width: 1;\"";
                cout << "/>" << endl;
            }
        }
        catch(exception&){
            cerr << "problem with the IO - quit";
            break;
        }
    }

    cout << "</svg>"<< endl;
}
