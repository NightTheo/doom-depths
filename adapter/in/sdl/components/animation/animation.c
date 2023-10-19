
//
// Created by Theo OMNES on 19/10/2023.
//

#include "animation.h"

Animation next_frame(Animation animation) {
    animation.current_frame = (animation.current_frame + 1) % animation.number_of_frames;
    animation.sprite_rect.x = animation.start_frame + animation.current_frame * animation.sprite_rect.w;
    return animation;
}