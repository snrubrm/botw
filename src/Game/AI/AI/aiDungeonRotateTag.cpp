#include "Game/AI/AI/aiDungeonRotateTag.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DungeonRotateTag::DungeonRotateTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool DungeonRotateTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor->checkBasicSig() && actor->hasPlacementLinkForBasicSig())
        changeChild("待機");
    else
        changeChild("回転");
}

void DungeonRotateTag::calc_() {
    auto* actor = mActor;
    if (!actor->hasPlacementLinkForBasicSig())
        return;

    if (isCurrentChild("待機") && actor->checkBasicSig())
        changeChild("回転");
    else if (isCurrentChild("回転") && !actor->checkBasicSig())
        changeChild("待機");
}

void DungeonRotateTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTag::loadParams_() {}

}  // namespace uking::ai
