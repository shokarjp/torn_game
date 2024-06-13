#include "ch_collision.h"

void  CH_ImposeCollision(GFX_Rect* a, GFX_Rect* b, V2F* velocity)
{
      
        i32 dx = a->pos.x - b->pos.x;
        i32 dy = a->pos.y - b->pos.y;
        
        i32 int_x = abs(dx) - ((a->size.x / 2) + (b->size.x/2) );
        i32 int_y = abs(dy) - ((a->size.y / 2) + (b->size.y/2) );


        if (int_x < 0.0f && int_y < 0.0f)
        {
            
            
            if (int_x >= int_y)
            {   
                velocity->x = 0;
    
                if (dx > 0.0f) {  a->pos.x =  round(a->pos.x +  int_x ) ;  } 
                else  a->pos.x  = round( a->pos.x + -int_x ) ;
                
                
            }
            else{
                 
                velocity->y = 0;
    
                if (dy > 0.0f) {  a->pos.y =  round(a->pos.y +  int_y ) ;  } 
                else  a->pos.y  = round( a->pos.y + -int_y ) ;
                
            }

        }
            
    
}