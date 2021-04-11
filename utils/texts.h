
#ifndef TEXTS_H
#define TEXTS_H

namespace texts 
{
 
    // fonts
    TTF_Font* init_font(int size)
    {   
        TTF_Init();
        TTF_Font *sans = TTF_OpenFont("fonts/OpenSans.ttf", size);
        if(!sans) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        };
        return sans;

    }
    TTF_Font *sans_big = init_font(30);
     TTF_Font *sans = init_font(20);
     TTF_Font *sans_small = init_font(10);

    // renders message in debug menu
    void render_message(std::string message, std::vector<int> position, TTF_Font *font)
    {
        //position: {x,y,h,w}
        const char * message_arg = message.c_str();
        SDL_Color white = {255, 255, 255};  
        SDL_Surface* surface_message = TTF_RenderText_Blended_Wrapped(font, message_arg, white, 180); 
        SDL_Texture* message_texture = SDL_CreateTextureFromSurface(RENDERER, surface_message); 
        SDL_Rect message_rect; 
        message_rect.x = position[0];  
        message_rect.y = position[1]; 
        message_rect.w = position[2];
        message_rect.h = position[3]; 
        SDL_RenderCopy(RENDERER, message_texture,  NULL , &message_rect); 
        SDL_FreeSurface(surface_message);
        SDL_DestroyTexture(message_texture);
    };

    // renders whole index in the debug menu
    void render_index(std::string vector_name, std::vector<int> &dest_index, std::vector<int> position, TTF_Font *font)
    {
        //position: {x,y,h,w}
        std::string v_txt;
        v_txt += vector_name;
        v_txt += ": ";
        for(int i=0; i < dest_index.size(); i++)
        {
            v_txt += std::to_string(dest_index[i]);
            v_txt += "; ";
        };
        texts::render_message(v_txt, position, font);
    }
}



#endif

