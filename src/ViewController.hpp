//
//  ViewController.hpp
//  Equalizer
//
//  Created by Cameron Browning on 4/4/17.
//
//

#ifndef ViewController_hpp
#define ViewController_hpp

#include "cinder/Perlin.h"

#include "poScene/ViewController.h"

#include "DNAFrag.hpp"

#include <stdio.h>

class EqualizerApp;

namespace equalizer{
    
    class ViewController;
     typedef std::shared_ptr<ViewController> ViewControllerRef;

    

    class ViewController : public po::scene::ViewController{
   
    public:
        
        static ViewControllerRef create();
        void setup();
        void update();
        
        void keyPressed(ci::app::KeyEvent &key);
        
        //DNAFragRef f;
        
        std::vector<std::vector<DNAFragRef>> dnaFrags;
        
        
        
         int numDNACols;
         int numDNARows;
         int numDNAFrags;
        
        float columnGutter;
        float fragWidth;
        
        void randomizePositions();
        void randomizeVerticalPositions();
        void randomizeSizes();
        void randomizeByTween();
        void randomizeColors();
        void centerLine();
        void gridify();
        void horiz();
        void noise();
        void resetWidths();
        
        float screenWidth;
        float screenHeight;
        
        void returnToOrigins();
        
        float maxFragHeight;
        float minFragHeight;
        float fragHeightDelta;
        
        
        void scrollDown();
        void noiseDown();
        
        void rain();
        
        void wind();
        
        void stopTweens();
        
        void tweenToFullBleed();
        
        
        int animState;
        
        float mTime;
        
        void setPreset(int which);
        
    protected:
        ViewController();
    
    private:
        // properties go here
        ci::Perlin					mPerlin;
        int mOctaves;
        int mSeed;
    
};
    }

#endif /* ViewController_hpp */
