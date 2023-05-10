#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;
void Show(int& Input)
{
    cout<<Input<<endl;
}
int main()
{
//    struct Pos{
//        double x;
//        double y;
//    };
//    Pos a{3,3};
//    unique_ptr<Pos> Pointer(new Pos{4,4});
////    Pointer->x = 3.3;
////    Pointer->y =4.4;
//    cout<<a.x<<"  "<<a.y<<endl;
//    cout<<Pointer->x<<"  "<<Pointer->y<<endl;
    int a[5][2] = {{1,1}, {2,2},{3,3}, {4,4}, {5,5}};
    for(auto &i:a){
        for (auto &y:i) {
            cout<<y<<endl;
        }
    }
    cout<<"Now Print Vector"<<endl;
    vector<int>b{1,2,3,4,5};
    for_each(b.begin(),b.end(), Show);
    vector<unique_ptr<int>>
}