
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_TH
#include "CommonFunction.h"
#include "BaseObject.h"
#include <vector>

//
//class MainObject : public BaseObject
//{
//public:
//    MainObject();
//    ~MainObject();
//
////    void HandleInputAction(SDL_Event events, Mix_Chunk* fire_sound[0]);
//    void HandleMove();
//
//    // Đạn của nhân vật lưu trong vector
////    void SetAmoList(std::vector<AmoObject*> amo_list)
////    {
////        p_amo_list = amo_list;
////    }
////    std::vector<AmoObject*> GetAmoList() const
////    {
////        return p_amo_list;
////    }
////    void MakeAmo(SDL_Surface* des);
////    void RemoveAmo(const int& idx);
//
//private:
//    int x_val_;
//    int y_val_;
////    std::vector<AmoObject*> p_amo_list;
//};
using namespace std;

class MainObject {
public:
    MainObject();
    ~MainObject();


    // Hàm để di chuyển đạn và gà
    void MoveBullets();
    void MoveChickens();

    // Hàm để thêm đạn và gà vào game
    void AddBullet(int x, int y);
    const std::vector<SDL_Rect>& GetBullets() const;

private:
    int x;
    int y;
    vector<SDL_Rect> bullets_; // Danh sách các đạn
    vector<SDL_Rect> chickens_; // Danh sách các gà
};

#endif // MAIN_OBJECT_H_
