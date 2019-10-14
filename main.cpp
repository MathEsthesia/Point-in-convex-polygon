#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <string>
#include <iomanip>
#include <queue>
#include <map>
#include <ctime>
using namespace std;

struct point{
    long long x,y;
};

long long cross_product(point a, point b){
    return a.x*b.y-b.x*a.y;
}

long long sq_dist(point a, point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

bool is_inside(long long x, long long y, vector<point>&points){
    point p1 = {points[points.size()-1].x-points[0].x, points[points.size()-1].y-points[0].y};
    point p2 = {points[1].x-points[0].x, points[1].y-points[0].y};
    point pq = {x-points[0].x, y-points[0].y};

    if(!(cross_product(p1, pq)<=0 && cross_product(p2,pq)>=0)) return false;

    int l = 0, r = points.size();
    while (r - l > 1) {
        int mid = (l + r) / 2;
        point cur = {points[mid].x-points[0].x, points[mid].y-points[0].y};
        if (cross_product(cur, pq)<0) {
            r = mid;
        } else {
            l = mid;
        }
    }

    if(l == points.size()-1){
        return sq_dist(points[0], {x,y}) <= sq_dist(points[0], points[l]);
    }else{
        point l_l1 = {points[l+1].x-points[l].x, points[l+1].y-points[l].y};
        point lq = {x-points[l].x, y-points[l].y};
        return (cross_product(l_l1,lq) >=0);
    }
}

void pick_p0(vector<point>&points){
    long long min_x=1e9+5;
    long long max_y=-1e9-5;
    int min_i=0;
    for(int i=0;i<points.size();i++){
        if(points[i].x < min_x || (points[i].x == min_x && points[i].y > max_y)){
            min_x=points[i].x;
            max_y=points[i].y;
            min_i = i;
        }
    }

    rotate(points.begin(), points.begin() + min_i, points.end());
}


int main() {
    int n,m,k;
    cin>>n>>m>>k;

    vector<point>points(n);

    for(int i=0;i<n;i++){
        cin>>points[i].x>>points[i].y;
    }

    pick_p0(points);

    for(int i=0;i<m;i++){
        long long x,y;
        cin>>x>>y;
        cout <<  (is_inside(x,y, points) ? "YES\n" : "NO\n");
    }

    return 0;
}