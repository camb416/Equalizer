//
//  ViewController.cpp
//  Equalizer
//
//  Created by Cameron Browning on 4/4/17.
//
//

#include "cinder/Rand.h"
#include "cinder/Log.h"

#include "ViewController.hpp"

using namespace std;


namespace equalizer{
    
    ViewControllerRef ViewController::create(){
       // CI_LOG_V("ViewController::create()");
        ViewControllerRef node (new ViewController());
        node->setup();
        return node;
    }
    ViewController::ViewController(){
        //CI_LOG_V("ViewController constructor");
    }
    
    
    void ViewController::randomizePositions(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->setPos(ci::vec2(ci::randFloat()*screenWidth, ci::randFloat() * screenHeight));
                
            }
        }
    }
    
    void ViewController::randomizeVerticalPositions(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->setPos(ci::randFloat() * screenHeight);
                
            }
        }
    }
    
    void ViewController::randomizeSizes(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->tweenHeight(ci::randFloat() * (maxFragHeight-minFragHeight)+ minFragHeight, ci::randFloat()*0.5f + 0.5f);
            }
        }
    }
    
    void ViewController::returnToOrigins(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->returnHome();
            }
        }
    }
    
    void ViewController::randomizeByTween(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->tweenPos(ci::randFloat() * screenHeight, ci::randFloat(3.0f)+3.0f);
            }
        }
    }
    
    void ViewController::randomizeColors(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->tweenColor(ci::randFloat(), ci::randFloat(0.5f)+1.0f);
                       
            }
        }
    }
    
    void ViewController::gridify(){
        
       columnGutter = 8;
    fragWidth = (screenWidth-((numDNACols+1)*columnGutter))/numDNACols;

        
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                float tweenLength = ci::randFloat(2.5f) + 0.5f;
                
                float fragHeight = (screenHeight - (columnGutter * (numDNARows+1)))/numDNARows;
                
                f->tweenHeight(fragHeight, ci::randFloat(1.0f)+0.5f);
                f->tweenWidth(fragWidth, ci::randFloat(1.0f) + 0.5f);
                
                
                f->tweenPos(i*(fragHeight+columnGutter)+columnGutter + fragHeight/2.0f,tweenLength);
            }
        }
    }
    
    void ViewController::centerLine(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                float tweenLength = ci::randFloat(2.5f) + 0.5f;
                f->tweenColor(0, tweenLength);
                f->tweenPos(screenHeight/2.0f,tweenLength);
                f->tweenHeight(minFragHeight, 3.0f);
            }
        }
    }
    
    void ViewController::keyPressed(ci::app::KeyEvent &key){
        CI_LOG_V(key.getChar());
        
        switch(key.getChar()){
                case 'o':
                case 'O':
                returnToOrigins();
                break;
                case 'r':
                case 'R':
                randomizePositions();
                break;
                case 's':
                case 'S':
                randomizeSizes();
                break;
                case 'v':
                case 'V':
                randomizeVerticalPositions();
                break;
                case 't':
                case 'T':
                randomizeByTween();
                break;
                case 'c':
                case 'C':
                randomizeColors();
                break;
                case '-':
                case '_':
                centerLine();
                break;
                case 'g':
                case 'G':
                gridify();
                break;
                case 'h':
                case 'H':
                horiz();
                break;
            default:
                
                break;
        }
        
    }
    
    void ViewController::setup(){
        
        mOctaves = 4;
        mSeed = clock();
        mPerlin = ci::Perlin(mOctaves, mSeed);
        
      ci::app::getWindow()->getSignalKeyDown().connect(std::bind(&ViewController::keyPressed, this, std::placeholders::_1));
        
       screenWidth = 1440;
      screenHeight = 215;
        maxFragHeight = screenHeight/8;
       minFragHeight = 5;
        

        
        
        
        
        columnGutter = 1;
        numDNARows = 8;
        numDNACols = 74;
        
        fragWidth = (screenWidth-((numDNACols+1)*columnGutter))/numDNACols;
        
        numDNAFrags = numDNARows * numDNACols;
        
     
        
        for(int j = 0; j< numDNACols; j++){
            std::vector<DNAFragRef> col;
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = equalizer::DNAFrag::create();
                f->setWidth(fragWidth);
                
                
                float thisHeight = ci::randFloat(minFragHeight, maxFragHeight);
                
                f->setSize(ci::vec2(fragWidth,thisHeight), true);
                
                float maxYPos = screenHeight - columnGutter - thisHeight/2.0f;
                
                float thisX = j*(fragWidth+columnGutter)+ columnGutter + fragWidth/2.0f;
                float thisY = ci::randFloat(columnGutter + thisHeight/2.0f, maxYPos);
                f->tweenHeight(thisHeight, 1.0f);
                f->setPos(ci::vec2(thisX,thisY), true);

                float nX = j * 0.005f;
                float nY = i * 0.005f;
                float nZ = ci::app::getElapsedSeconds() * 0.1f;
                ci::vec3 v( nX, nY, nZ );
                float noise = mPerlin.fBm( v );
                
                f->setColor(ci::Color(noise,noise,noise));
                
                
                col.push_back(f);
                getView()->addSubview(f);
            }
            dnaFrags.push_back(col);
        }
       
        // randomizePositions();
        gridify();
    }
    
    void ViewController::horiz(){
        for(int j = 0; j< numDNACols; j++){
        
            for(int i=0;i<numDNARows;i++){
                DNAFragRef d = dnaFrags.at(j).at(i);
            float yPos = d->getPos().y;
            float yScale = sin(yPos/215.0f*M_PI)*215.0f/(float)numDNARows;
                d->tweenHeight(yScale, 1.0f);
        }
        }

    }
    void ViewController::update(){
        for(int j = 0; j< numDNACols; j++){

            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);

      //  CI_LOG_V("ViewController::update()");
//        float nX = (float)j * 0.1f;
//        float nY = (float)i * 0.1f;
//        float nZ = (float)ci::app::getElapsedSeconds() * 1.0f;
//        ci::vec3 v( nX, nY, nZ );
//        float noise = mPerlin.fBm( v );
//         //       CI_LOG_V(noise);
//        f->setColor(ci::Color(noise,noise,noise));
            }
        }
    }
    
}
