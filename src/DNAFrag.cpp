//
//  View.cpp
//  Equalizer
//
//  Created by Cameron Browning on 4/4/17.
//
//
#include "cinder/Rand.h"
#include "cinder/Log.h"

#include "DNAFrag.hpp"

namespace equalizer{
    
    DNAFrag::DNAFrag(){
        // constructor
    }
    DNAFragRef DNAFrag::create(){
        DNAFragRef node (new DNAFrag());
        node->setup();
        return node;
    }
    void DNAFrag::setup(){
        pos = ci::vec2(0);
        
        grayVal = ci::randFloat();
        
        
        size = ci::vec2(10,10);
        
        useTimeline = false;
        
        height = size.y;
        
    }
    
    void DNAFrag::setColor(ci::Color _c){
        
        color = _c;
        
    }
    
    void DNAFrag::tweenColor(float _color, float _time){
        ci::app::timeline().appendTo( &grayVal, _color, _time, ci::EaseInOutCubic());

    }

    void DNAFrag::update(){
        
        if(tweenedY.isComplete() && grayVal.isComplete() && height.isComplete()){
            useTimeline = false;
        } else {
            useTimeline = true;
        }
        
       // color = ci::Color(grayVal, grayVal, grayVal);
        size.y = height;


        
        
        if(useTimeline){
            pos.y = tweenedY;
        } else {
            pos += (dPos-pos)/4.0f;
        }
        
        size += (dSize-size)/4.0f;
    }
    
    void DNAFrag::setDestinations(){
        dPos = pos; // cancel any active procedural animations
        dSize = size;
        //color = ci::Color(0,0,0);
        
    }
    
    void DNAFrag::turnOffTimeline(){
       // useTimeline = false;
        setDestinations();
    }
    
    void DNAFrag::tweenHeight(float _height, float _speed){
         useTimeline = true;
        ci::app::timeline().appendTo ( &height, _height, _speed, ci::EaseInOutCubic());
        
    }
    
    void DNAFrag::tweenPos(float _newY, float _numSeconds){
        // do a tween
        useTimeline = true;
        tweenedY = pos.y;
        // color = ci::Color(1,0,0);
        ci::app::timeline().appendTo ( &tweenedY, _newY, _numSeconds, ci::EaseInOutCubic()).finishFn( std::bind( &DNAFrag::turnOffTimeline,this ));
        
        // another way to do this:
        //       ci::app::timeline().apply ( &tweenedY, _newY, 3.0f, ci::EaseInOutCubic()).finishFn(  [&]() {
        //            // Do something in this lambda function. Example: just quit.
        //           turnOffTimeline();
        //       });
        
    }
    
    
    
    void DNAFrag::draw(){
       // CI_LOG_V("DNAFrag::draw()");
        ci::gl::color(color);
        ci::gl::drawSolidRoundedRect(ci::Rectf(pos.x-size.x/2.0f,pos.y-size.y/2.0f,pos.x+size.x/2.0f,pos.y+size.y/2.0f), 1);
    }
    
    
}
