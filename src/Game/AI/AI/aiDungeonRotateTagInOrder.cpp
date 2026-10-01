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

void DungeonRotateTagInOrder::calc_() {
    auto* actor = mActor;
    bool skip = true;
    if (_38 != actor->checkBasicSig()) {
        _38 = actor->checkBasicSig();
        skip = *mRotateTurnOn_s && !actor->checkBasicSig();
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転"))
            changeChild("待機");
    } else if (child->isChangeable()) {
        if (isCurrentChild("待機") && !skip)
            changeChild("回転");
    }
}

}  // namespace uking::ai
