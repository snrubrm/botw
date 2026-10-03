#include "Game/AI/AI/aiDungeonRotateTag4WindApp.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ai {

DungeonRotateTag4WindApp::DungeonRotateTag4WindApp(const InitArg& arg)
    : WholeDungeonRotateTag(arg) {}

DungeonRotateTag4WindApp::~DungeonRotateTag4WindApp() = default;

bool DungeonRotateTag4WindApp::init_(sead::Heap* heap) {
    return WholeDungeonRotateTag::init_(heap);
}

void DungeonRotateTag4WindApp::enter_(ksys::act::ai::InlineParamPack* params) {
    WholeDungeonRotateTag::enter_(params);
    _48 = 0;
    _40 = 0;
    _44 = 0;
    const f32 tilt = *mTiltAngle_m;
    ui::sub_7100A9D168(sead::Mathf::deg2rad(tilt), 0, sead::Mathf::deg2rad(-tilt));
    m44();
}

bool DungeonRotateTag4WindApp::m34() {
    return ui::sub_7100A9BAEC(18);
}

bool DungeonRotateTag4WindApp::m35() {
    return ui::sub_7100A9D0F4();
}

bool DungeonRotateTag4WindApp::m36() {
    return ui::sub_7100A9D118();
}

bool DungeonRotateTag4WindApp::m37() {
    return ui::sub_7100A9D140();
}

void DungeonRotateTag4WindApp::calc_() {
    WholeDungeonRotateTag::calc_();
}

void DungeonRotateTag4WindApp::leave_() {
    WholeDungeonRotateTag::leave_();
}

void DungeonRotateTag4WindApp::m39() {
    _44 = 1;
    _40 = *mTiltAngle_m;
}

void DungeonRotateTag4WindApp::m40() {
    _44 = 2;
    _40 = -*mTiltAngle_m;
}

void DungeonRotateTag4WindApp::m41() {
    _40 = 0;
    _44 = 0;
}

// NON_MATCHING: scheduling of the SafeString stores in the tail-merged blocks (two instructions swapped)
void DungeonRotateTag4WindApp::m43(int state) {
    switch (state) {
    case 0:
        ksys::gdt::setBoolByKey(true, "RemainsWind_RotHorizontal");
        ksys::gdt::setBoolByKey(false, "RemainsWind_Rotate");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotLeft");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotRight");
        break;
    case 1:
        ksys::gdt::setBoolByKey(true, "RemainsWind_RotLeft");
        ksys::gdt::setBoolByKey(false, "RemainsWind_Rotate");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotHorizontal");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotRight");
        break;
    case 2:
        ksys::gdt::setBoolByKey(true, "RemainsWind_RotRight");
        ksys::gdt::setBoolByKey(false, "RemainsWind_Rotate");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotHorizontal");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotLeft");
        break;
    case 3:
        ksys::gdt::setBoolByKey(true, "RemainsWind_Rotate");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotHorizontal");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotLeft");
        ksys::gdt::setBoolByKey(false, "RemainsWind_RotRight");
        break;
    default:
        break;
    }
}

void DungeonRotateTag4WindApp::m44() {
    _48 = _44;
    m43(_44);
    WholeDungeonRotateTag::m44();
}

void DungeonRotateTag4WindApp::m45() {
    _48 = _44;
    m43(3);
    WholeDungeonRotateTag::m45();
}

void DungeonRotateTag4WindApp::loadParams_() {
    WholeDungeonRotateTag::loadParams_();
}

}  // namespace uking::ai
