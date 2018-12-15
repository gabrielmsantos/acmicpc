#include <iostream>
#include <fstream>
#include <math.h>
#include <set>

using namespace std;

struct point
{
    double x, y;
    double polar;
    char wid;
    point* pair;

    point(){}
    point(double x_, double y_, double p_, char w_) : x(x_), y(y_), polar(p_), wid(w_) {}

    bool operator< (const point &other) const
    {
        return polar < other.polar;
    }
};

void advance_point(point &p, const point &ref,const int w, const int  h, double value = 1)
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

void print_wire(const point &p1, const point &p2)
{
    cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << endl;
}

int main()
{
    ifstream input_file("input.txt");
    unsigned int wires, w, h;
    set<point> all_points;
    set<char> w_cut;
    // read first line of input file
    input_file >> wires >> w >> h;
    cout << "There are " << wires << " wires." << endl;

    int x1, y1, x2, y2;
    double cx, cy;
    cx = w/2;
    cy = h/2;
    // read segments #  O(nlogn) Polar Sort
    for(unsigned int count = 0, wn='a'; count < wires; ++count, wn++)
    {
        input_file >> x1 >> y1 >> x2 >> y2;
        point* p1 = new point(x1, y1, atan2(x1 - cx, y1 - cy), wn);
        point* p2 = new point(x2, y2, atan2(x2 - cx, y2 - cy), wn);
        p1->pair = p2;
        p2->pair = p1;
        all_points.insert(*p1);
        all_points.insert(*p2);

        cout << "(" << x1 << ", " << y1 << ")["<< p1->polar <<"] ("<< x2 << ", " << y2 << ")["<< p2->polar << "] -- " << "PAIR: (" << p1->pair->x << ", " << p1->pair->y << ")" << p1->wid <<endl;
    }
    
    for(auto const& ponto: all_points)
    {
        print_wire(ponto, *ponto.pair);
    }

    set<point>::iterator it_aux = all_points.begin();
    point s, t = *it_aux;
    for(auto const& l_point: all_points )
    {
        // Advancing S        
        advance_point(s, l_point, w, h);
        cout << "P " << l_point.x << ", " << l_point.y << " (" << l_point.pair->x << ", " << l_point.pair->y <<")  :: S: "<< s.x << ", "<< s.y << endl;
        if(w_cut.find(l_point.wid) == w_cut.end())
        {
            w_cut.insert(l_point.wid);
        }else
        {
            // Advancing T
            cout << "GOTO : (" << l_point.pair->x << ", " << l_point.pair->y << ")" << endl;
            advance_point(t, *it_aux, w, h);
            cout << "T:"<< t.x << ", " << t.y << endl;
            while(it_aux != all_points.end() && (it_aux->x != l_point.pair->x || it_aux->y != l_point.pair->y))
            {
                w_cut.erase(w_cut.find(it_aux->wid));
                it_aux++;                
                advance_point(t, *it_aux, w, h);
                cout << "T:"<< t.x << ", " << t.y << "(" << it_aux->x << ", "<< it_aux->y<< ")" << endl;
            }
            it_aux++;
        }

        if(w_cut.size() == wires)
        {
            cout << "1" << endl;
            print_wire(t, s);
            set<point>::iterator it_p = all_points.find(s);
            if(it_p != all_points.end())
            {
                advance_point(s, *it_p, w, h, -0.5); 
            }
            
            it_p = all_points.find(t);
            if(it_p != all_points.end())
            {
                advance_point(t, *it_p, w, h, -0.5); 
            }

            print_wire(t, s);
           return 0; 
        }
    }

    cout << "2" << endl;
    cout << "DIAGONALS" << endl;
}

