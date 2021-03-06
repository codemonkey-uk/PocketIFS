// outp.h

#ifndef outp_i
#define outp_i

#include <map>
#include <vector>

struct Outp
{
    typedef std::map< p, std::map<p,bool> > linemap;
    std::map< p, std::map<p,bool> > lines;
    p current;
    std::ostream& o;

    Outp(std::ostream& _o) : o(_o) {}

    inline void StartLine(int x, int y)
    {
        current.p_x = x;
        current.p_y = y;
    }

    inline void AddPoint(int x, int y)
    {
        p nxt;
        nxt.p_x = x;
        nxt.p_y = y;
        lines[current][nxt]=false;
        lines[nxt][current]=false;
        current = nxt;
    }

    inline void EndLine()
    {
        // no-op
    }

    inline int FlushLines(p from, bool svg)
    {
        linemap::iterator i = lines.find(from);
        if (i!=lines.end())
        {
            for (std::map<p,bool>::iterator j=i->second.begin(); j!=i->second.end(); ++j)
            {
                if (j->second==false)
                {
                    j->second=true;
                    lines[j->first][from]=true;

                    int r = FlushLines(j->first, svg);
                    if (j->first != from)
                    {
                        if (r>0)
                        {
                            o << " ";
                        }
                        else if (svg)
                        {
                            o << "<polyline points=\"";
                        }
                        o << j->first.p_x << "," << j->first.p_y;
                        r++;
                    }
                    return r;
                }
            }
        }
        return 0;
    }

    inline void FlushLines(bool svg)
    {
        int x1,y1,x2,y2;
        linemap::iterator i=lines.begin();
        x2 = x1 = i->first.p_x;
        y2 = y1 = i->first.p_y;
        for (; i!=lines.end();++i)
        {
            if (i->first.p_x > x2)
                x2 = i->first.p_x;
            if (i->first.p_x < x1)
                x1 = i->first.p_x;
            if (i->first.p_y > y2)
                y2 = i->first.p_y;
            if (i->first.p_y < y1)
                y1 = i->first.p_y;
        }

        if (svg)
        {
            o << "<svg xmlns=\"http://www.w3.org/2000/svg\"" << endl;
            o << "\twidth=\"" << (x2-x1) << "px\" height=\"" << (y2-y1) << "px\"" << endl;
            o << "\tviewBox=\"" << x1 << " " << y1 << " " << (x2-x1) << " " << (y2-y1) <<"\"" << endl;
            o << "\txmlns:xlink=\"http://www.w3.org/1999/xlink\">" << endl;
            o << "<defs><style type=\"text/css\"><![CDATA[" << endl;
            o << "polyline { stroke:#000000; fill:none; stroke-width: 1 }" << endl;
            o << "]]></style></defs>" << endl;
        }

        std::vector<linemap::iterator> jobs;
        jobs.reserve( lines.size() );

        for (linemap::iterator i=lines.begin(); i!=lines.end();++i)
            jobs.push_back( i );

        // this ordering helps start polylines at line ends
        std::sort(jobs.begin(), jobs.end(), Compare);

        for (int i=0; i!=lines.size();++i)
        {
            if (FlushLines(jobs[i]->first, svg))
            {
                o << " " << jobs[i]->first.p_x << "," << jobs[i]->first.p_y;
                if (svg)
                    o << "\"/>";
                o << endl;
                i=0;
                std::sort(jobs.begin(), jobs.end(), Compare);
            }
        }

        if (svg)
        {
            o << "</svg>"<< endl;
        }
    }

    private:
    inline static bool IsFalse( const std::pair<p,bool>& p ){
        return p.second == false;
    }
    inline static bool Compare( linemap::iterator a, linemap::iterator b )
    {
        int sa=std::count_if(a->second.begin(), a->second.end(), IsFalse);
        int sb=std::count_if(b->second.begin(), b->second.end(), IsFalse);
        // odd before even, small before large
        return ((sa&1) > (sb&1)) || ((sa&1) == (sb&1) && sa < sb);
    }
};

#endif // outp_i