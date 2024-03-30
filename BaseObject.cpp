//////
//////#include "BaseObject.h"
//////#include "CommonFunction.h"
//////
//////using namespace std;
//////BaseObject::BaseObject() {
//////    rect_.x = 0;
//////    rect_.y = 0;
//////    p_object_ = NULL;
//////}
//////
//////BaseObject::~BaseObject() {
//////    if (p_object_ != NULL) {
//////        SDL_DestroyTexture(p_object_);
//////    }
//////}
//////
//////bool BaseObject::LoadImg(const char* file_name) {
//////    p_object_ = SDLCommonFunction::loadTexture(file_name);
//////    if (p_object_ == NULL)
//////        return false;
//////    return true;
//////}
//////
//////void BaseObject::Show() {
//////    SDL_RenderCopy(g_renderer, p_object_, nullptr, &rect_);
//////}
////
////
////#include "BaseObject.h"
////#include "CommonFunction.h"
////
////BaseObject::BaseObject()
////{
////    rect_.x = 0;
////    rect_.y = 0;
////    p_object_ = NULL;
////}
////
////BaseObject::~BaseObject()
////{
////    if (p_object_ != NULL){
////        SDL_FreeSurface(p_object_);
////    }
////}
////
////bool BaseObject::loadImg(const char* file_name)
////{
////    p_object_ = CommonFunction::load_image(file_name);
////    if (p_object_ == NULL)
////        return false;
////    return true;
////}
////
////void BaseObject::show(SDL_Surface* des)
////{
////    if (p_object_ != NULL)
////    {
////        CommonFunction::ApplySurface(p_object_, des, rect_.x, rect_.y);
////    }
////}

//#include "BaseObject.h"

////////void BaseObject::Move(SDL_Event& event) {
////////    if (event.type == SDL_KEYDOWN) {
////////        if (event.key.keysym.sym == SDLK_LEFT) {
////////            x -= SPEED;
////////        } else if (event.key.keysym.sym == SDLK_RIGHT) {
////////            x += SPEED;
////////        } else if (event.key.keysym.sym == SDLK_UP) {
////////            y -= SPEED;
////////        } else if (event.key.keysym.sym == SDLK_DOWN) {
////////            y += SPEED;
////////        }
////////    }
////////}

//BaseObject::BaseObject() {
//    texture_ = nullptr;
//    rect_ = {0, 0, 0, 0};
//}
//
//BaseObject::~BaseObject() {
//    // Hủy texture nếu đã tồn tại
//    if (texture_ != nullptr) {
//        SDL_DestroyTexture(texture_);
//        texture_ = nullptr;
//    }
//}
//
//bool BaseObject::LoadImage(std::string path) {
//    // Load hình ảnh từ tệp
//    SDL_Surface* surface = IMG_Load(path.c_str());
//    if (surface == nullptr) {
//        std::cerr << "Unable to load image " << path << "! SDL_Error: " << IMG_GetError() << std::endl;
//        return false;
//    }
//
//    // Tạo texture từ surface
//    texture_ = SDL_CreateTextureFromSurface(gRenderer, surface);
//    if (texture_ == nullptr) {
//        std::cerr << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
//        SDL_FreeSurface(surface);
//        return false;
//    }
//
//    // Thiết lập kích thước cho rect_
//    rect_.w = surface->w;
//    rect_.h = surface->h;
//
//    // Giải phóng surface
//    SDL_FreeSurface(surface);
//
//    return true;
//}
//
//void BaseObject::SetPosition(int x, int y) {
//    rect_.x = x;
//    rect_.y = y;
//}
//
//void BaseObject::Move(int dx, int dy) {
//    rect_.x += dx;
//    rect_.y += dy;
//}
//
//void BaseObject::Render() {
//    // Vẽ texture lên renderer
//    SDL_RenderCopy(gRenderer, texture_, nullptr, &rect_);
//}



#include "BaseObject.h"
#include "CommonFunction.h"

BaseObject::BaseObject() : x(0), y(0), width(100), height(100) {}

BaseObject::~BaseObject() {}

void BaseObject::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void BaseObject::Move(SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_LEFT) {
        x -= SPEED;
    } else if (event.key.keysym.sym == SDLK_RIGHT) {
        x += SPEED;
    } else if (event.key.keysym.sym == SDLK_UP) {
        y -= SPEED/2;
    } else if (event.key.keysym.sym == SDLK_DOWN) {
        y += SPEED/2;
    }

    if (x < 0) {
        x = 0;
    } else if (x + width > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - width;
    }

    if (y < SCREEN_HEIGHT/2) {
        y = SCREEN_HEIGHT/2;
    } else if (y + height > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - height;
    }
}

