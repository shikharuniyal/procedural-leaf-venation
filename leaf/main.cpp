#include "raylib.h"
#include <unistd.h>
#include <vector>
#include <iostream>
#include<random>
#include<math.h>
#include<string>
#include<algorithm>
#include <iostream>
#include <sstream>
#include<stdio.h>
#include<cmath>
#include <unordered_map>
#include "raymath.h"

#define AUXIN_RATE 700
#define w 1440
#define h 1200
#define PROXIMITY 10

typedef struct{
    Vector2 gg;
    double distan;
}leaf_node;
void refresh_auxins(std::vector<Vector2> &arr){
    //arr.clear();
    int i = 0;
    while(i!=AUXIN_RATE){
        double my_num = (double)rand()/RAND_MAX;
        Vector2 auz;
        auz.x = (int)((double)1.0*my_num*(w-20));
        my_num = (double)rand()/RAND_MAX;
        auz.y =my_num*(h-20);
        arr.push_back(auz);
        i++;
    }
    
}

/////CONVEX HULL APPROACH for points enclosure of hte points in the plane of 2D vectors


float cross(const Vector2 &O, const Vector2 &A, const Vector2 &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

std::vector<Vector2> convexHull(std::vector<Vector2> pts) {
    int n = pts.size(), k = 0;
    if (n <= 3) return pts;
    std::sort(pts.begin(), pts.end(), [](const Vector2 &a, const Vector2 &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });


    std::vector<Vector2> H(2*n);
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(H[k-2], H[k-1], pts[i]) <= 0) k--;
        H[k++] = pts[i];
    }
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], pts[i]) <= 0) k--;
        H[k++] = pts[i];
    }

    H.resize(k-1);
    return H;
}


void check_prox(std::vector<Vector2> &auxins,std::vector<Vector2> &veins){
    if(auxins.empty() || veins.empty()) return;
    for(int j  =0 ;j<veins.size();j++){
        Vector2 p = veins[j];
        for(int i = auxins.size();i-- >0;){
            Vector2 a = auxins[i];
            double dis = Vector2Distance(a, p);
            if((dis)<(2*PROXIMITY)){
                auxins.erase(auxins.begin()+i);
                std::cout<<"index removed \t"<<i<<std::endl;
            }
        }
    }
    
}
int main(void)
{
    int VEIN_RAD = 2;
    std::vector<Vector2> veins;
    std::vector<Vector2> auxins;
    std::vector<int> indx;
    InitWindow(w,h, "raylib rotating square");
    int i = 0;
    SetTargetFPS(60);
    Vector2 p;
    p.x = w/2;
    p.y = (h*2/3)+300;
 
    double ran = (double)rand()/RAND_MAX;
    std::cout<<ran;
    std::string st ="";
    int intPart = (int)ran;

    while(intPart!=0){
        int d = intPart%10;
        char c = '0'+d;
        st+=c;
        intPart /=10;
    }
    reverse(st.begin(), st.end());
    
    st +=".";
    int d =0;
    double fracP = ran - (int)ran;
    for(int i =0 ;i <3 ;i++){
        fracP *= (int)fracP;
        char c = '0'+d;
        st+= c;
        fracP -=d;
    }
 
    double my_num = (double)rand()/RAND_MAX;
    std::ostringstream oss;
    oss<<my_num;
    std::string mystr = oss.str();

    veins.push_back(p);

    refresh_auxins(auxins);
    check_prox(auxins,veins);

    std::vector<Vector2> CVmap; // stores the direction
    std::vector<Vector2> closest_vein;      //individual closest vein per auxin
    CVmap.resize(veins.size(), {0.0f, 0.0f});
    closest_vein.resize(auxins.size());

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);
        if(IsKeyPressed(KEY_W)){
            refresh_auxins(auxins);
            check_prox(auxins,veins);
        }
        
        if(IsKeyDown(KEY_T)){
            
            //computing the existing arrays for the auxins and veins indexing
            if(!veins.empty()){
                
                CVmap.assign(veins.size(), {0.0f, 0.0f});
                closest_vein.assign(auxins.size(),{0.0f, 0.0f});
                //check_prox(auxins,veins);

            }

            // this part computes the direction towards which the vein must grow CVmap stores the mapping of veins and their directions in different arrays with same indexing
            for(int i = 0;i<auxins.size();i++){
                Vector2 a = auxins[i];
                int cvein_idx = 0;
                double smol = sqrt(pow(abs(a.x - veins[cvein_idx].x),2)+pow(abs(a.y - veins[cvein_idx].y),2));
                for(int j = 1;j<veins.size();j++){
                    Vector2 p = veins[j];
                    double sample = sqrt(pow(abs(a.x -p.x),2)+pow(abs(a.y - p.y),2));
                    
                    if(sample<smol){
                        cvein_idx = j;
                        smol = sample;
                    }
                }
                closest_vein[i] = veins[cvein_idx];
                CVmap[cvein_idx] = Vector2Add(CVmap[cvein_idx],Vector2Subtract(a,veins[cvein_idx]));
                
            }

            //normalization
            for(int k =0;k<CVmap.size();k++)
            if(Vector2Length(CVmap[k]) >0.0f)
                CVmap[k] =Vector2Normalize(CVmap[k]);


            //now the actually adding of the new vein node to the veins vector
            std::vector<Vector2> new_veins;
            for(int n = 0;n<CVmap.size();n++){
                if(CVmap[n].x == 0.0f && CVmap[n].y == 0.0f ) continue;
                Vector2 new_vein;
                new_vein.x = veins[n].x+ CVmap[n].x* (VEIN_RAD) *2;
                new_vein.y = veins[n].y+ CVmap[n].y* VEIN_RAD *2;    
                new_veins.push_back(new_vein);
            }
            for(int i  =0;i<new_veins.size();i++){
                veins.push_back(new_veins[i]);
            }
            check_prox(auxins, veins); 

        }




        for (size_t i = 0; i < auxins.size(); ++i) {
                //DrawLineV(auxins[i], closest_vein[i], ORANGE);
            }
        


        for(int i = 0;i<std::max(veins.size(),auxins.size());++i){
            if(i<veins.size()){
                Vector2 p = veins[i];
                DrawCircle(p.x,p.y,VEIN_RAD,BLUE);
                DrawRing(p,PROXIMITY+2,PROXIMITY,0,360,1000,RED);
                if(i<CVmap.size()){
                    Vector2 start = veins[i];  
                    Vector2 end   = Vector2Add(start, Vector2Scale(CVmap[i],100));
                }
                //DrawLineV(start, end, WHITE); 
            }
            if(i<auxins.size()){
                Vector2 p = auxins[i];
                DrawCircle(p.x,p.y,VEIN_RAD,GREEN);
                DrawRing(p,PROXIMITY+2,PROXIMITY,0,360,1000,PURPLE);
            }
        }
        
        
        std::vector<Vector2> hull = convexHull(veins);
        for (int i = 0; i < hull.size(); i++) {
            Vector2 a = hull[i];
            Vector2 b = hull[(i+1) % hull.size()];
            DrawLineV(a, b, ORANGE);
        }
     

        if(IsKeyDown(KEY_SPACE)){
            if(indx.size()!=0){
                std::cout<<"removing an auxin"<<std::endl;
                auxins.erase(auxins.begin() + indx.back() );
                indx.pop_back();
            }
            else std::cout<<"removed all auxins"<<std::endl;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;

}