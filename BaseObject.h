
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
