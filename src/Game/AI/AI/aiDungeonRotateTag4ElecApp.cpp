#include "Game/AI/AI/aiDungeonRotateTag4ElecApp.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ai {

DungeonRotateTag4ElecApp::DungeonRotateTag4ElecApp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTag4ElecApp::~DungeonRotateTag4ElecApp() = default;

bool DungeonRotateTag4ElecApp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTag4ElecApp::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0;
    _48 = 0.0f;
    _4c = 0;
    switch (*mCtrlDgnRemainsElectricBodyPart_m) {
    case 0:
        ksys::gdt::setBoolByKey(true, "RemainsElectric_Drum1Rotate0");
        break;
    case 1:
        ksys::gdt::setBoolByKey(true, "RemainsElectric_Drum2Rotate0");
        break;
    case 2:
        ksys::gdt::setBoolByKey(true, "RemainsElectric_Drum3Rotate0");
        break;
    }
    changeChild("待機");
}

void DungeonRotateTag4ElecApp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTag4ElecApp::loadParams_() {
    getMapUnitParam(&mCtrlDgnRemainsElectricBodyPart_m, "CtrlDgnRemainsElectricBodyPart");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
}

}  // namespace uking::ai
