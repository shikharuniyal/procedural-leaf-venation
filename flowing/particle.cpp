#include<iostream>
#include"particle.hpp"
#include"config.hpp"

particle::particle() {};
particle::particle(RealVector p,RealVector v, float min_s,float max_s){
    pos = p;
    vel  =v;
    mns = min_s;
    mas = max_s;
}

// to simulate the movement of the particle
void particle::update(){
    pos = pos.add(vel);
    if(pos.x> GetScreenWidth()) pos.x = 0;
    if(pos.x<0 ) pos.x = GetScreenWidth();
    if(pos.y> GetScreenHeight()) pos.y = 0;
    if(pos.y<0 ) pos.y = GetScreenHeight();
}

void particle::applyForce(RealVector force){
    vel = vel.add(force);
    vel = vel.limit(mns,mas);
}

void particle::show(){
    DrawCircle(pos.x,pos.y,Par_rad,{255, 87, 51, 255});
}