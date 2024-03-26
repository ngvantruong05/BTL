////
////#include "BaseObject.h"
////#include "CommonFunction.h"
////
////using namespace std;
////BaseObject::BaseObject() {
////    rect_.x = 0;
////    rect_.y = 0;
////    p_object_ = NULL;
////}
////
////BaseObject::~BaseObject() {
////    if (p_object_ != NULL) {
////        SDL_DestroyTexture(p_object_);
////    }
////}
////
////bool BaseObject::LoadImg(const char* file_name) {
////    p_object_ = SDLCommonFunction::loadTexture(file_name);
////    if (p_object_ == NULL)
////        return false;
////    return true;
////}
////
////void BaseObject::Show() {
////    SDL_RenderCopy(g_renderer, p_object_, nullptr, &rect_);
////}
//
//
//#include "BaseObject.h"
//#include "CommonFunction.h"
//
//BaseObject::BaseObject()
//{
//    rect_.x = 0;
//    rect_.y = 0;
//    p_object_ = NULL;
//}
//
//BaseObject::~BaseObject()
//{
//    if (p_object_ != NULL){
//        SDL_FreeSurface(p_object_);
//    }
//}
//
//bool BaseObject::loadImg(const char* file_name)
//{
//    p_object_ = CommonFunction::load_image(file_name);
//    if (p_object_ == NULL)
//        return false;
//    return true;
//}
//
//void BaseObject::show(SDL_Surface* des)
//{
//    if (p_object_ != NULL)
//    {
//        CommonFunction::ApplySurface(p_object_, des, rect_.x, rect_.y);
//    }
//}
