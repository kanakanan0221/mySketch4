//
//  Particle.cpp
//  CMA2
//
//  Created by kanako on 2016/02/28.
//
//

#include "Particle.hpp"

Particle::Particle(){
    setIntialCondition(0, 0, 0, 0);
    damping = 0.01f;
    
}

void Particle::resetForce(){
    frc.set(0, 0);
}

void Particle::addForce(float x , float y){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
    
}
void Particle::addDampingFoece(){
    frc.x = frc.x - vel.x* damping;
    frc.y = frc.y - vel.y * damping;
}
void Particle::setIntialCondition(float px, float py,float vx, float vy){
    pos.set(px,py);
    vel.set(vx, vy);
    
}
void Particle::update(){
    vel = vel+ frc;
    pos = pos + vel;
}
void Particle::draw(){
    ofCircle(pos.x, pos.y, 3);
}
