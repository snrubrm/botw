#include "Game/AI/AI/aiDungeonRotateTag4ElecApp.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ui {
bool sub_7100A9D2D0(s32 index);
bool sub_7100A9D308(s32 index);
bool sub_7100A9D344(s32 index);
bool sub_7100A9D380(s32 index);
bool sub_7100A9D3BC(s32 index);
}  // namespace uking::ui

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

void DungeonRotateTag4ElecApp::calc_() {
    auto* child = getCurrentChild();
    const s32 part = *mCtrlDgnRemainsElectricBodyPart_m;
    const s32 index = part >= 0 && part < 3 ? part + 24 : -1;
    if (ui::sub_7100A9D2D0(index)) {
        if (ui::sub_7100A9D308(index)) {
            _50 = 0;
            _48 = 0.0f;
        } else if (ui::sub_7100A9D344(index)) {
            _50 = 1;
            _48 = 90.0f;
        } else if (ui::sub_7100A9D380(index)) {
            _50 = 2;
            _48 = 180.0f;
        } else if (ui::sub_7100A9D3BC(index)) {
            _50 = 3;
            _48 = -90.0f;
        }
        if (_4c != _50)
            sub_710037816C();
    } else if (child->isFinished() || child->isFailed()) {
        _4c = _50;
        switch (*mCtrlDgnRemainsElectricBodyPart_m) {
        case 0:
            ksys::gdt::setBoolByKey(_50 == 0, "RemainsElectric_Drum1Rotate0");
            break;
        case 1:
            ksys::gdt::setBoolByKey(_50 == 0, "RemainsElectric_Drum2Rotate0");
            break;
        case 2:
            ksys::gdt::setBoolByKey(_50 == 0, "RemainsElectric_Drum3Rotate0");
            break;
        }
        changeChild("待機");
    }
}

void DungeonRotateTag4ElecApp::loadParams_() {
    getMapUnitParam(&mCtrlDgnRemainsElectricBodyPart_m, "CtrlDgnRemainsElectricBodyPart");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
}

}  // namespace uking::ai
