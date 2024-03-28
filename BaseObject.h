//////#ifndef BASE_OBJECT_H_
//////#define BASE_OBJECT_H_
//////#include <SDL.h>
//////#include <SDL_image.h>
//////#include "CommonFunction.h"
//////class BaseObject {
//////protected:
//////    SDL_Rect rect_;
//////    SDL_Texture* p_object_;
//////public:
//////    BaseObject();
//////    ~BaseObject();
//////    void Show();
//////    bool LoadImg(const char* file_name);
//////    void SetRect(int x, int y) {
//////        rect_.x = x;
//////        rect_.y = y;
//////    }
//////    SDL_Rect GetRect() const { return rect_; }
//////    SDL_Texture* GetObject() { return p_object_; }
//////};
//////
//////#endif
////
////// Lớp đối tượng cơ sở có các thuộc tính chung
////// Các đối tượng khác kế thừa từ lớp này
////
////#ifndef BASE_OBJECT_H_
////#define BASE_OBJECT_H_
////#include "CommonFunction.h"
////
////class BaseObject //Lớp cơ sở
////{
////public:
////    BaseObject(); //Constructer
////    ~BaseObject(); //Hàm hủy
////    void show(SDL_Surface* des); // Surface truyền vào
////    bool loadImg(const char* file_name);
////    void SetRect(const int& x, const int& y){
////        rect_.x = x;
////        rect_.y = y;
////    }
////    SDL_Rect GetRect() const{
////        return rect_;
////    }
////    SDL_Surface* GetObject(){
////        return p_object_;
////    }
////protected:
////    SDL_Rect rect_;
////    SDL_Surface* p_object_; //Surface nguồn
////};
////
////
////#endif // BASE_OBJECT_H_
////
////
//// BaseObject.h
//#ifndef BASE_OBJECT_H
//#define BASE_OBJECT_H
//
//#include "CommonFunction.h"

////////class BaseObject {
////////public:
////////    int GetX() const { return x; } // Phương thức trả về giá trị của x
////////    int GetY() const { return y; } // Phương thức trả về giá trị của y
////////    void SetX(int newX) { x = newX; } // Phương thức thiết lập giá trị mới cho x
////////    void SetY(int newY) { y = newY; } // Phương thức thiết lập giá trị mới cho y
////////    void Move(SDL_Event& event);
////////private:
////////    int x;
////////    int y;
////////};
//
//class BaseObject {
//public:
//    BaseObject(); // Constructor mặc định
//    ~BaseObject(); // Destructor
//
//    // Hàm để tải hình ảnh từ tệp và tạo texture
//    //bool LoadImage(std::string path);
//
//    // Hàm để thiết lập vị trí ban đầu của đối tượng
//    void SetPosition(int x, int y);
//
//    // Hàm để di chuyển đối tượng
//    void Move(int dx, int dy);
//
//    // Hàm để vẽ đối tượng lên màn hình
//    void Render();
//
//protected:
//    int x;
//    int y;
//
//    SDL_Texture* texture_; // Texture của đối tượng
//    SDL_Rect rect_; // Hình chữ nhật đại diện cho vị trí và kích thước của đối tượng
//};

//#endif // BASE_OBJECT_H

#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <SDL.h>

class BaseObject {
public:
    BaseObject();
    ~BaseObject();
    int GetX() const { return x; } // Phương thức trả về giá trị của x
    int GetY() const { return y; } // Phương thức trả về giá trị của y
    void SetX(int newX) { x = newX; } // Phương thức thiết lập giá trị mới cho x
    void SetY(int newY) { y = newY; } // Phương thức thiết lập giá trị mới cho y
    void SetPosition(int x, int y);
    void Move(SDL_Event& event);
private:
    int x;
    int y;
    int width;
    int height;

    SDL_Rect rect_;
};

#endif // BASE_OBJECT_H
