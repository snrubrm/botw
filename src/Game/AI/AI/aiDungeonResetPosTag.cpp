#include "Game/AI/AI/aiDungeonResetPosTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/gamePlayerResetPosMgr.h"
#include "KingSystem/Map/mapObject.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

DungeonResetPosTag::DungeonResetPosTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonResetPosTag::~DungeonResetPosTag() = default;

// NON_MATCHING: translation snapshot loads and stores are combined differently.
bool DungeonResetPosTag::init_(sead::Heap* heap) {
    auto* actor = mActor;
    if (!actor->hasPlacementLinkForBasicSig()) {
        const sead::Vector3f position = actor->getMtx().getTranslation();
        f32 yaw = 0.0f;
        if (auto* object = actor->getMapObject())
            yaw = sead::Mathf::rad2deg(object->getRotate().y);
        PlayerResetPosMgr::instance()->addResetPos(position, yaw);
    }
    return true;
}

void DungeonResetPosTag::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
}

void DungeonResetPosTag::calc_() {
    auto* actor = mActor;
    if (!actor->hasPlacementLinkForBasicSig())
        return;

    if (actor->checkBasicSig()) {
        if (isCurrentChild("待機"))
            changeChild("復帰位置指定");
    } else if (!isCurrentChild("待機")) {
        changeChild("待機");
    }
}

void DungeonResetPosTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonResetPosTag::loadParams_() {}

}  // namespace uking::ai
