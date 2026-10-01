#include "Game/AI/AI/aiDungeonRotateTag4FireApp.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

DungeonRotateTag4FireApp::DungeonRotateTag4FireApp(const InitArg& arg)
    : WholeDungeonRotateTag(arg) {}

DungeonRotateTag4FireApp::~DungeonRotateTag4FireApp() = default;

bool DungeonRotateTag4FireApp::init_(sead::Heap* heap) {
    return WholeDungeonRotateTag::init_(heap);
}

void DungeonRotateTag4FireApp::enter_(ksys::act::ai::InlineParamPack* params) {
    WholeDungeonRotateTag::enter_(params);
}

void DungeonRotateTag4FireApp::calc_() {
    WholeDungeonRotateTag::calc_();
}

void DungeonRotateTag4FireApp::leave_() {
    WholeDungeonRotateTag::leave_();
}

bool DungeonRotateTag4FireApp::m37() {
    return false;
}

void DungeonRotateTag4FireApp::m39() {
    _44 = 2;
    _40 = *mTiltAngle_m;
}

void DungeonRotateTag4FireApp::m40() {
    _40 = 0;
    _44 = 0;
}

void DungeonRotateTag4FireApp::m41() {}

void DungeonRotateTag4FireApp::m43(int state) {
    switch (state) {
    case 0:
        ksys::gdt::setFlag_RemainsFire_Rotate0(true);
        ksys::gdt::setFlag_RemainsFire_RotateTo90(false);
        ksys::gdt::setFlag_RemainsFire_Rotate90(false);
        ksys::gdt::setFlag_RemainsFire_RotateTo0(false);
        break;
    case 1:
        ksys::gdt::setFlag_RemainsFire_RotateTo90(true);
        ksys::gdt::setFlag_RemainsFire_Rotate0(false);
        ksys::gdt::setFlag_RemainsFire_Rotate90(false);
        ksys::gdt::setFlag_RemainsFire_RotateTo0(false);
        break;
    case 2:
        ksys::gdt::setFlag_RemainsFire_Rotate90(true);
        ksys::gdt::setFlag_RemainsFire_Rotate0(false);
        ksys::gdt::setFlag_RemainsFire_RotateTo90(false);
        ksys::gdt::setFlag_RemainsFire_RotateTo0(false);
        break;
    case 3:
        ksys::gdt::setFlag_RemainsFire_RotateTo0(true);
        ksys::gdt::setFlag_RemainsFire_Rotate0(false);
        ksys::gdt::setFlag_RemainsFire_RotateTo90(false);
        ksys::gdt::setFlag_RemainsFire_Rotate90(false);
        break;
    default:
        break;
    }
}

void DungeonRotateTag4FireApp::m44() {
    _48 = _44;
    m43(_44);
    changeChild("待機");
}

void DungeonRotateTag4FireApp::m45() {
    _48 = _44;
    int state = _44;
    if (state == 0)
        state = 3;
    else if (state == 2)
        state = 1;
    m43(state);
    WholeDungeonRotateTag::m45();
}

void DungeonRotateTag4FireApp::loadParams_() {
    WholeDungeonRotateTag::loadParams_();
}

}  // namespace uking::ai
