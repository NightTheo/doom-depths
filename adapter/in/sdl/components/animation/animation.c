
//
// Created by Theo OMNES on 19/10/2023.
//

#include "animation.h"

Animation next_frame(Animation animation) {
    animation.current_frame = (animation.current_frame + 1) % animation.number_of_frames;
    uint8_t row = animation.current_frame / animation.sprite_sheet.columns;
    uint8_t column = animation.current_frame % animation.sprite_sheet.columns;
    animation.sprite_rect.x = animation.start_frame + column * animation.sprite_rect.w;
    animation.sprite_rect.y = animation.start_frame + row * animation.sprite_rect.h;
    return animation;
}

