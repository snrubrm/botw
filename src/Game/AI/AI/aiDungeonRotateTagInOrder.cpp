#include "Game/AI/AI/aiDungeonRotateTagInOrder.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DungeonRotateTagInOrder::DungeonRotateTagInOrder(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool DungeonRotateTagInOrder::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTagInOrder::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    if (mActor->checkBasicSig())
        changeChild("回転");
    else
        changeChild("待機");
}

void DungeonRotateTagInOrder::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTagInOrder::loadParams_() {
    getStaticParam(&mRotateTurnOn_s, "RotateTurnOn");
}

}  // namespace uking::ai
