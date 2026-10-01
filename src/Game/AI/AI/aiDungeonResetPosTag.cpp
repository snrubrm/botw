#include "Game/AI/AI/aiDungeonResetPosTag.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DungeonResetPosTag::DungeonResetPosTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonResetPosTag::~DungeonResetPosTag() = default;

bool DungeonResetPosTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
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
