////#ifndef BASE_OBJECT_H_
////#define BASE_OBJECT_H_
////#include <SDL.h>
////#include <SDL_image.h>
////#include "CommonFunction.h"
////class BaseObject {
////protected:
////    SDL_Rect rect_;
////    SDL_Texture* p_object_;
////public:
////    BaseObject();
////    ~BaseObject();
////    void Show();
////    bool LoadImg(const char* file_name);
////    void SetRect(int x, int y) {
////        rect_.x = x;
////        rect_.y = y;
////    }
////    SDL_Rect GetRect() const { return rect_; }
////    SDL_Texture* GetObject() { return p_object_; }
////};
////
////#endif
//
//// Lớp đối tượng cơ sở có các thuộc tính chung
//// Các đối tượng khác kế thừa từ lớp này
//
//#ifndef BASE_OBJECT_H_
//#define BASE_OBJECT_H_
//#include "CommonFunction.h"
//
//class BaseObject //Lớp cơ sở
//{
//public:
//    BaseObject(); //Constructer
//    ~BaseObject(); //Hàm hủy
//    void show(SDL_Surface* des); // Surface truyền vào
//    bool loadImg(const char* file_name);
//    void SetRect(const int& x, const int& y){
//        rect_.x = x;
//        rect_.y = y;
//    }
//    SDL_Rect GetRect() const{
//        return rect_;
//    }
//    SDL_Surface* GetObject(){
//        return p_object_;
//    }
//protected:
//    SDL_Rect rect_;
//    SDL_Surface* p_object_; //Surface nguồn
//};
//
//
//#endif // BASE_OBJECT_H_
