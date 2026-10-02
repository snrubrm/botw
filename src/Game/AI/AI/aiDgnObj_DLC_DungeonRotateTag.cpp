#include "Game/AI/AI/aiDgnObj_DLC_DungeonRotateTag.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DgnObj_DLC_DungeonRotateTag::DgnObj_DLC_DungeonRotateTag(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_DungeonRotateTag::~DgnObj_DLC_DungeonRotateTag() = default;

bool DgnObj_DLC_DungeonRotateTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_DungeonRotateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
}

void DgnObj_DLC_DungeonRotateTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_DungeonRotateTag::loadParams_() {
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mRegistFromBeginning_m, "RegistFromBeginning");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

void DgnObj_DLC_DungeonRotateTag::m34() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor) {
        gear_mgr->sub_71006692F0(mActor, false);
        *mRotationOffset_a = gear_mgr->_1098;
    }
}

void DgnObj_DLC_DungeonRotateTag::m35() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006694B4(mActor);
}

}  // namespace uking::ai
