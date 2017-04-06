//
//  View.hpp
//  Equalizer
//
//  Created by Cameron Browning on 4/4/17.
//
//

#ifndef View_hpp
#define View_hpp

#include "poScene/View.h"

#include <stdio.h>

using namespace po::scene;



class DNAFrag;
typedef std::shared_ptr<View> ViewRef;

class View : public po::scene::View{
    
public:
    static ViewRef create();
    
protected:
    View();
    
private:
    
   // the whole visual canvas
};

#endif /* View_hpp */
