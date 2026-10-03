#include "Game/AI/AI/aiDgnObj_DLC_DungeonRotateTag.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DgnObj_DLC_DungeonRotateTag::DgnObj_DLC_DungeonRotateTag(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_DungeonRotateTag::~DgnObj_DLC_DungeonRotateTag() = default;

bool DgnObj_DLC_DungeonRotateTag::init_(sead::Heap* heap) {
    if (auto* mgr = GearMgr::instance())
        mgr->sub_7100669144(*mGearRatio_m);
    if (*mRegistFromBeginning_m)
        m34();
    return true;
}

void DgnObj_DLC_DungeonRotateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
}

void DgnObj_DLC_DungeonRotateTag::calc_() {
    auto* gear_mgr = GearMgr::instance();
    if (!gear_mgr)
        return;
    auto* actor = mActor;
    if (!actor)
        return;

    const bool registered = gear_mgr->sub_71006690B8(actor);
    if (actor->hasPlacementLinkForBasicSig()) {
        const bool signal = actor->checkBasicSig();
        if (registered) {
            if (!signal)
                m35();
        } else if (signal) {
            m34();
        }
    }

    if (registered) {
        if (!isCurrentChild("待機"))
            return;
        if (gear_mgr->_10a8[gear_mgr->_28 ^ 1] & 4)
            return;
        changeChild("回転");
    } else {
        if (!isCurrentChild("回転"))
            return;
        changeChild("待機");
    }
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
