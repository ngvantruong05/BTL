//
//#include "MainObject.h"
//
//MainObject::MainObject()
//{
//    // Tọa độ đối tượng chính
//    rect_.x = 0;
//    rect_.y = 0;
//    rect_.w = WIDTH_MAIN_OBJECT;
//    rect_.h = HEIGHT_MAIN_OBJECT;
//    x_val_ = 0;
//    y_val_ = 0;
//}
//
//MainObject::~MainObject()
//{
//
//}
//
////// Xử lý sự kiện nhân vật chính
////void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* fire_sound[2])
////{
////    if (events.type == SDL_KEYDOWN) // Sự kiện khi ấn phím
////    {
////        switch(events.key.keysym.sym)
////        {
////        case SDLK_UP:
////            y_val_ -= HEIGHT_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        case SDLK_DOWN:
////            y_val_ += HEIGHT_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        case SDLK_LEFT:
////            x_val_ -= WIDTH_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        case SDLK_RIGHT:
////            x_val_ += WIDTH_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        default:
////            break;
////        }
////    }
////    else if (events.type == SDL_KEYUP) // Sự kiện khi nhả phím
////    {
////        switch(events.key.keysym.sym)
////        {
////        case SDLK_UP:
////            y_val_ += HEIGHT_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        case SDLK_DOWN:
////            y_val_ -= HEIGHT_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        case SDLK_LEFT:
////            x_val_ += WIDTH_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        case SDLK_RIGHT:
////            x_val_ -= WIDTH_MAIN_OBJECT/SPEED_MAIN;
////            break;
////        case SDLK_KP0:
////        {
////            AmoObject* p_amo = new AmoObject();
////            p_amo->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
////            p_amo->loadImg("images/laser.png");
////            p_amo->set_type(AmoObject::LAZER);
////            Mix_PlayChannel(-1, fire_sound[0], 0);
////
////            p_amo->SetRect(this->rect_.x + 20, this->rect_.y + 22);
////            p_amo->set_is_move(true);
////            p_amo->Set_y_val(20);
////            p_amo_list.push_back(p_amo);
////        }
////        default:
////            break;
////        }
////    }
////    else if (events.type == SDL_MOUSEBUTTONDOWN) // Sự kiện khi ấn chuột. Bắn đạn
////    {
////        AmoObject* p_amo = new AmoObject();
////        if (events.button.button == SDL_BUTTON_LEFT)
////        {
////            p_amo->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
////            p_amo->loadImg("images/laser.png");
////            p_amo->set_type(AmoObject::LAZER);
////            Mix_PlayChannel(-1, fire_sound[0], 0);
////        }
////        else if (events.button.button == SDL_BUTTON_RIGHT)
////        {
////            p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
////            p_amo->loadImg("images/sphere.png");
////            p_amo->set_type(AmoObject::SPHERE);
////            Mix_PlayChannel(-1, fire_sound[1], 0);
////        }
////        p_amo->SetRect(this->rect_.x + 20, this->rect_.y + 22);
////        p_amo->set_is_move(true);
////        p_amo->Set_y_val(20);
////        p_amo_list.push_back(p_amo);
////    }
////    else if (events.type == SDL_MOUSEBUTTONUP)
////    {
////
////    }
////}
//
//// Load bắn đạn của nhân vật chính
////void MainObject::MakeAmo(SDL_Surface* des)
////{
////    for (int i = 0; i < p_amo_list.size(); i++)
////    {
////        AmoObject* p_amo = p_amo_list.at(i);
////        if (p_amo != NULL)
////        {
////            if (p_amo->get_is_move())
////            {
////                p_amo->show(des);
////                p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
////            }
////            else
////            {
////                if (p_amo != NULL)
////                {
////                    p_amo_list.erase(p_amo_list.begin() + i);
////                    delete p_amo;
////                    p_amo = NULL;
////                }
////            }
////        }
////    }
////}
//
//// Di chuyển nhân vật
//void MainObject::HandleMove()
//{
//    rect_.x += x_val_;
//    if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH + 30)
//    {
//        rect_.x -= x_val_;
//    }
//    rect_.y += y_val_;
//    if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
//    {
//        rect_.y -= y_val_;
//    }
//}
//
//// Xoá đạn
////void MainObject::RemoveAmo(const int& idx)
////{
////    for (int i = 0; i < p_amo_list.size(); i++)
////    {
////        if (p_amo_list.size() > 0 && idx < p_amo_list.size())
////        {
////            AmoObject* p_amo = p_amo_list.at(idx);
////            p_amo_list.erase(p_amo_list.begin() + idx);
////            if(p_amo != NULL)
////            {
////                delete p_amo;
////                p_amo = NULL;
////            }
////        }
////    }
////}

#include "MainObject.h"

MainObject::MainObject() {
    // Khởi tạo đối tượng MainObject
}


MainObject::~MainObject() {
    // Hủy đối tượng MainObject
}

void MainObject::MoveBullets() {
    for (int i = 0; i < bullets_.size(); ++i) {
        bullets_[i].y -= SPEED/20;
        if (bullets_[i].y + HEIGHT_MAIN_OBJECT < 0) {
            bullets_.erase(bullets_.begin() + i);
        }
    }
}

void MainObject::MoveChickens() {
     // Sinh gà ngẫu nhiên từ trên xuống
    if (rand() % 1000 < 5) { // Sinh gà với xác suất 5% trong mỗi lần di chuyển
        int x = rand() % SCREEN_WIDTH; // Sinh tọa độ x ngẫu nhiên
        int y = -HEIGHT_MAIN_OBJECT - 100; // Gà được sinh ở trên cùng của màn hình
        SDL_Rect chickenRect = {x, y, WIDTH_MAIN_OBJECT, HEIGHT_MAIN_OBJECT};
        chickens_.push_back(chickenRect); // Thêm gà vào danh sách
    }
    for (int i = 0; i < chickens_.size(); ++i) {
        chickens_[i].y += SPEED/20; // Tăng tọa độ y để di chuyển xuống dưới
        // Xử lý việc gà chạm đáy màn hình
        if (chickens_[i].y > SCREEN_HEIGHT) {
            chickens_.erase(chickens_.begin() + i); // Xóa gà ra khỏi danh sách nếu chạm đáy màn hình
        }
    }
}

void MainObject::AddBullet(int x,int y) {
    // Thêm một viên đạn mới vào danh sách
    SDL_Rect bullet = {x - WIDTH_MAIN_OBJECT / 2, y, WIDTH_MAIN_OBJECT / 2, HEIGHT_MAIN_OBJECT};
    bullets_.push_back(bullet);
}

const std::vector<SDL_Rect>& MainObject::GetBullets() const {
    return bullets_;
}
const std::vector<SDL_Rect>& MainObject::GetChickens() const {
    return chickens_;
}
