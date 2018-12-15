#include <iostream>
#include <fstream>
#include <math.h>
#include <set>

using namespace std;
struct point
{
    double x, y, polar;
    char wid;
    point* pair;
    point(){}
    point(double x_, double y_, double p_, char w_) : x(x_), y(y_), polar(p_), wid(w_) {}
};

struct comparer
{
    bool operator()(const point* lhs, const point* rhs) const
    {
        return lhs->polar < rhs->polar;
    }
};

void advance_point(point &p, const point &ref, double w, double  h, double value = 1)
{
    if((ref.x == 0) || (ref.x == w))
    {
        p.x = ref.x;
        p.y = ref.y + (value -2 * value * ref.x/w);
    }else
    {
        p.x = ref.x - (value -2 * value * ref.y/h);
        p.y = ref.y;
    }
    p.polar = atan2(p.x - w/2, p.y- h/2); 
}

bool same_side(point t, point s,double w, double h)
{
    return ( (t.x == s.x && (t.x == 0 || t.x == w)) || ( t.y == s.y && (t.y == 0 || t.y == h) ));
}

int main()
{
    ifstream input_file("input3.txt");
    double wires, w, h;
    set<point*, comparer> all_points;
    set<char> w_cut;
    input_file >> wires >> w >> h;
    int x1, y1, x2, y2;
    for(int count = 0, wn='a'; count < wires; ++count, wn++)
    {
        input_file >> x1 >> y1 >> x2 >> y2;
        point* p1 = new point(x1, y1, atan2(x1 - w/2, y1 - h/2), wn);
        point* p2 = new point(x2, y2, atan2(x2 - w/2, y2 - h/2), wn);
        p1->pair = p2;
        p2->pair = p1;
        all_points.insert(p1);
        all_points.insert(p2);
    }
    set<point*>::iterator it_aux = all_points.begin();
    point s, t = **it_aux;
    for(auto const& l_point: all_points )
    {
        advance_point(s, *l_point, w, h);
        if(w_cut.find(l_point->wid) == w_cut.end())
        {
            w_cut.insert(l_point->wid);
        }else
        {
            advance_point(t, **it_aux, w, h);
            while( (*it_aux)->x != l_point->pair->x || (*it_aux)->y != l_point->pair->y)
            {
                w_cut.erase(w_cut.find((*it_aux)->wid));
                it_aux++;                
                advance_point(t, **it_aux, w, h);
            }
            it_aux++;
        }

        if(w_cut.size() == wires && not same_side(t, s, w, h))
        {
            cout << "1" << endl;
            if(all_points.find(&s) != all_points.end())
            {
                advance_point(s, s, w, h, -0.5); 
            }
            if(all_points.find(&t) != all_points.end())
            {
                advance_point(t, t, w, h, -0.5); 
            }
            cout << t.x << " " << t.y << " " << s.x << " " << s.y << endl;
            return 0; 
        }
    }

    for(auto const& ponto: all_points)
    {
        delete ponto;
    }

    cout << "2" << endl;
    cout << "DIAGONALS" << endl;
}

