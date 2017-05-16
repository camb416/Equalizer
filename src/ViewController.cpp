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
                f->setWidth(fragWidth);
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
        
      float newColumnGutter = columnGutter;
    float newFragWidth = (screenWidth-((numDNACols+1)*newColumnGutter))/numDNACols;

        
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                float tweenLength = ci::randFloat(2.5f) + 0.5f;
                
                float fragHeight = (screenHeight - (columnGutter * (numDNARows+1)))/numDNARows;
                
                f->tweenHeight(fragHeight, ci::randFloat(1.0f)+0.5f);
                f->tweenWidth(newFragWidth, ci::randFloat(1.0f) + 0.5f);
                
                
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
    void ViewController::resetWidths(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->setWidth(fragWidth);
            }
        }

    }
    
    void ViewController::stopTweens(){
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                f->setHeight( 5.0f);
            }
        }
    
    }
    
    void ViewController::tweenToFullBleed(){
        // tween to full bleed
        // 1) tween color to black
        // 2) tween size to maxheight
        // 3) tween width to full width (no gutters)
        // 4) tween position to grid
        
        float newColumnGutter = 0;
        float newFragWidth = (screenWidth-((numDNACols+1)*newColumnGutter))/numDNACols;
        
        
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);
                float tweenLength = ci::randFloat(2.5f) + 0.5f;
                
                float newFragHeight = screenHeight/numDNARows;
                
                f->tweenHeight(newFragHeight+2.0f, ci::randFloat(2.5f)+0.5f);
                f->tweenWidth(newFragWidth+2.0f, ci::randFloat(2.5f) + 0.5f);
                
                  f->tweenColor(0,ci::randFloat() + 1.0f);
                f->tweenPos(i*(newFragHeight)+columnGutter + newFragHeight/2.0f,ci::randFloat(2.5f)+0.5f);
            }
        }

        
        
    }
    
    void ViewController::keyPressed(ci::app::KeyEvent &key){
        CI_LOG_V(key.getChar());
        
        switch(key.getChar()){
                case 'm':
                case 'M':
                tweenToFullBleed();
                break;
                case 'x':
                case 'X':
                stopTweens();
                break;
                case 'o':
                case 'O':
                returnToOrigins();
                break;
                case 'f':
                case 'F':
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
                case 'p':
                case 'P':
                noise();
                break;
                case 'd':
                case 'D':
                scrollDown();
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                animState = key.getCode() - 48;
                break;

                case '6':
                case '7':
                case '8':
                case '9':
                setPreset(key.getCode()-48-5);
                break;
                case '[':
                setPreset(5);
                break;
                case 'r':
                case 'R':
                rain();
                break;
                case 'w':
                case 'W':
                resetWidths();
                break;
                case 'i':
                case 'I':
                animState = 5;
                break;
            default:
                
                break;
        }
        
    }
    
    void ViewController::scrollDown(){
        
        
        
        for(int j = 0; j< numDNACols; j++){
            
            vector<float> buffHeights;
            vector<float> buffColors;
            
            for(int i=0;i<numDNARows;i++){
                DNAFragRef d = dnaFrags.at(j).at(i);
                buffHeights.push_back(d->getHeight());
                buffColors.push_back(d->getColor());
            }
            
            dnaFrags.at(j).at(0)->setHeight(buffHeights.at(numDNARows-1));
            dnaFrags.at(j).at(0)->setColor(buffColors.at(numDNARows-1));
            for(int i=1;i<numDNARows;i++){
                DNAFragRef d = dnaFrags.at(j).at(i);
                DNAFragRef d2 = dnaFrags.at(j).at(i-1);
                d->setHeight(buffHeights[i-1]);
                d->setColor(buffColors[i-1]);
                
            }
            buffHeights.clear();
            buffColors.clear();
        }
    }
    
    void ViewController::wind(){
        
        if(ci::app::getElapsedFrames()  % 4 == 0){
        
        std::vector<std::vector<float>> dnaFragHeightBuff;
            std::vector<std::vector<float>> dnaFragColorBuff;
        for(int j = 0; j< numDNACols; j++){
            std::vector<float> colh;
            std::vector<float> colc;
            for(int i=0;i<numDNARows;i++){
                colh.push_back(dnaFrags.at(j).at(i)->getHeight());
                colc.push_back(dnaFrags.at(j).at(i)->getColor());
            }
            dnaFragHeightBuff.push_back(colh);
            dnaFragColorBuff.push_back(colc);
        }
        
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef d = dnaFrags.at(j).at(i);
                float d2h;
                float d2c;
                if(j<numDNACols-1){
                    d2h  = dnaFragHeightBuff.at(j+1).at(i);
                    d2c = dnaFragColorBuff.at(j+1).at(i);
                } else {
                    d2h  = dnaFragHeightBuff.at(0).at(i);
                    d2c = dnaFragColorBuff.at(0).at(i);
                }
                d->setHeight(d2h);
                d->setColor(d2c);
                
                
            }
        }

        dnaFragHeightBuff.clear();
            dnaFragColorBuff.clear();
        }
    }
    
    void ViewController::rain(){
        
        
//        for(int j = 0; j< numDNACols; j++){
//            for(int i=0;i<numDNARows;i++){
//                DNAFragRef d = dnaFrags.at(j).at(i);
//                
//                float r = ci::randFloat();
//                float randHeight = r*(maxFragHeight - minFragHeight) + minFragHeight;
//                
//                d->setWidth(fragWidth);
//                d->setColor(1.0f - r); // 0 to 1
//                d->setHeight(randHeight);
//                //d->setPos(ci::randFloat()*30.0f  - 30.0f, true);
//                //d->tweenPos(ci::randFloat()*30.0f + screenHeight, r*2.0f + 0.5f);
//                d->linearTweenPos(ci::randFloat()*30.0f + screenHeight, r*2.0f + 0.5f);
//            }
//        }

        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef d = dnaFrags.at(j).at(i);
                

                
                d->setWidth(fragWidth);
                d->setPos(d->getPos().y + d->getHeight() / (i+5), true);
                if(d->getPos().y > screenHeight + 30){
                    d->setPos(-30.0f, true);
                }

            }
        }
        
        
    }
    
    void ViewController::noiseDown(){
        CI_LOG_V("noisedown");
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef d = dnaFrags.at(j).at(i);
                
                // float p = mPerlin.fBm(ci::vec3(1.0f,1.0f,1.0f));
                float freq = 0.1f;
                float tFreq = 0.5f;
                // ci::vec2 noiseParam = ci::vec2(d->getPos().x - mTime
                //                              ,d->getPos().y);
                float x_in = j + mTime;
                float y_in = i + 0.5f;
                ci::vec3 noiseParam = ci::vec3(x_in, y_in, 1.0f);
                
                float p = ci::lmap(mPerlin.fBm(noiseParam), -0.5f, 0.5f, 0.0f, 1.0f);
               // (p > 0) ? p = 1.0f : p = 0.0f;
                d->setColor(p);
                //d->setHeight((1.0f-p)*maxFragHeight);
            }
        }

    }
    
    void ViewController::noise(){
        float min = 99999;
        float max = -99999;
        for(int j = 0; j< numDNACols; j++){
            for(int i=0;i<numDNARows;i++){
                DNAFragRef d = dnaFrags.at(j).at(i);

               // float p = mPerlin.fBm(ci::vec3(1.0f,1.0f,1.0f));
                float freq = 0.1f;
                ci::vec3 noiseParam = ci::vec3(d->getPos().x*freq,d->getPos().y*freq, mTime);
                
                float p = mPerlin.noise(noiseParam);
                
                p = p/1.5f+0.75f;
                
                if(p>max) max = p;
                if(p<min) min = p;
           
                d->setColor(p);
                d->setHeight((1.0f-p)*maxFragHeight);
            }
        }
        std:: ostringstream ss;
        ss << min << ", " << max;
        CI_LOG_V(ss.str());
    }
    
    void ViewController::setup(){
        
        animState = 0;
        
        mOctaves = 4;
      // mSeed = clock();
       mPerlin = ci::Perlin(mOctaves, mSeed);
        
      ci::app::getWindow()->getSignalKeyDown().connect(std::bind(&ViewController::keyPressed, this, std::placeholders::_1));
        
       screenWidth = 1440;
      screenHeight = 215;
        maxFragHeight = screenHeight/8;
       minFragHeight = 5;
        fragHeightDelta = maxFragHeight-minFragHeight;
        

        
        
        
        
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
        
        mTime = ci::app::getElapsedSeconds();
        
        switch(animState){
            case 0:
                // normal
                break;
            case 1:
                scrollDown();
                break;
            case 2:
                noise();
                break;
            case 3:
                noiseDown();
                break;
            case 4:
                rain();
                break;
            case 5:
                wind();
                break;
            default:
                animState = 0;
                break;
        }
        for(int j = 0; j< numDNACols; j++){

            for(int i=0;i<numDNARows;i++){
                DNAFragRef f = dnaFrags.at(j).at(i);

                
            }
        }
    }
    
    void ViewController::setPreset(int which){
        

        


                for(int j = 0; j< numDNACols; j++){
                    for(int i=0;i<numDNARows;i++){
                    DNAFragRef f = dnaFrags.at(j).at(i);
                        float yPos, xPos, yScale;
                        ci::vec2 pos;
                        switch(which){
                            case 0:
                                yScale = 0.0f;
                                f->tweenHeight(0.0f, 0.5f);
                                break;
                            case 1:
                                yScale = maxFragHeight;
                                f->tweenHeight(maxFragHeight, 0.5f);
                                break;
                            case 2:
                                yPos = f->getPos().y;
                                yScale = sin(yPos/screenHeight*M_PI)*fragHeightDelta + minFragHeight;
                                f->tweenHeight(yScale, 0.5f);
                                break;
                            case 3:
                                xPos = f->getPos().x;
                                yScale = sin(xPos/screenWidth*M_PI)*fragHeightDelta + minFragHeight;
                                f->tweenHeight(yScale, 0.5f);
                                break;
                            case 4:
                                pos = f->getPos();
                                yScale = sin(pos.y/screenHeight*M_PI+pos.x/2.0f)*fragHeightDelta + minFragHeight;
                                f->tweenHeight(yScale, 0.5f);
                                break;
                            case 5:
                                pos = f->getPos();
                                yScale = sin(pos.y/screenHeight*M_PI-pos.x/16.0f)*fragHeightDelta + minFragHeight;
                                f->tweenHeight(yScale, 0.5f);
                            break;
                        }
                        //f->tweenColor((yScale-minFragHeight)/(maxFragHeight-minFragHeight),0.5f);

                    }
                }
        }
    
    
}
