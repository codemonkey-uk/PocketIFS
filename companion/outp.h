// outp.h

#ifndef outp_i
#define outp_i

#include <map>

struct Outp
{
    typedef std::map< p, std::map<p,bool> > linemap;
    std::map< p, std::map<p,bool> > lines;
    p current;

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

    inline int FlushLines(p from)
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

                    int r = FlushLines(j->first);
                    if (j->first != from)
                    {
                        if (r>0)
                        {
                            cout << " ";
                        }
                        cout << j->first.p_x << "," << j->first.p_y;
                        r++;
                    }
                    return r;
                }
            }
        }
        return 0;
    }

    inline void FlushLines()
    {
        for (linemap::iterator i=lines.begin(); i!=lines.end();++i)
        {
            while (FlushLines(i->first))
                cout << " " << i->first.p_x << "," << i->first.p_y << endl;
        }
    }
};

#endif // outp_i