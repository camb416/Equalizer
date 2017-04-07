//
//  View.hpp
//  Equalizer
//
//  Created by Cameron Browning on 4/4/17.
//
//

#ifndef DNAFrag_hpp
#define DNAFrag_hpp

#include "cinder/Timeline.h"

#include "poScene/View.h"

#include <stdio.h>

using namespace po::scene;

namespace equalizer{

class DNAFrag;
typedef std::shared_ptr<DNAFrag> DNAFragRef;

class DNAFrag : public po::scene::View{
    
public:
    static DNAFragRef create();
    void draw();
    void update();
    void setup();
    void setHeight(float _h){dSize.y = _h;};
    void setWidth(float _w){ dSize.x = _w; };
    void setPos(ci::vec2 _pos, bool isOrigin = false){ dPos = _pos; if(isOrigin) pos = oPos = dPos;};
    void setPos(float _vPos){dPos.y = _vPos;};
    void setSize(ci::vec2 _size, bool isOrigin = false){ dSize = _size; if(isOrigin) size = oSize = dSize; };
    void returnHome(){dPos = oPos;};
    
    void tweenPos(float _newY, float _numSeconds = 3.0f);
    void turnOffTimeline();
    
    void setDestinations();
    
    void tweenColor(float _color, float _duration);
    void tweenHeight(float _height, float _duration);
    void tweenWidth(float _width, float _duration);
   
    
    void setColor(ci::Color _c);
    
    ci::vec2 getPos(){ return pos; };

    

    
protected:
    DNAFrag();
    
private:
    ci::vec2 oPos;
    ci::vec2 dPos;
    ci::vec2 pos;
    
    ci::Anim<float> grayVal;
    ci::Anim<float> height;
    ci::Anim<float> width;
    ci::Color color;
    
    ci::vec2 size;
    ci::vec2 dSize;
    ci::vec2 oSize;
    
    bool useTimeline;
    ci::Anim<float> tweenedY;
};
}

#endif /* View_hpp */
