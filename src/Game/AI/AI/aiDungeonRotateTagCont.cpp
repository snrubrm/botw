#include "Game/AI/AI/aiDungeonRotateTagCont.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DungeonRotateTagCont::DungeonRotateTagCont(const InitArg& arg) : DungeonRotateTagInOrder(arg) {}

DungeonRotateTagCont::~DungeonRotateTagCont() = default;

bool DungeonRotateTagCont::init_(sead::Heap* heap) {
    if (!DungeonRotateTagInOrder::init_(heap))
        return false;
    *mIsContinueRotateOrMove_a = false;
    return true;
}

void DungeonRotateTagCont::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateTagInOrder::enter_(params);
    *mIsContinueRotateOrMove_a = false;
    _38 = false;
}

void DungeonRotateTagCont::calc_() {
    *mIsContinueRotateOrMove_a = mActor->checkBasicSig();
    DungeonRotateTagInOrder::calc_();
}

void DungeonRotateTagCont::leave_() {
    DungeonRotateTagInOrder::leave_();
}

void DungeonRotateTagCont::loadParams_() {
    DungeonRotateTagInOrder::loadParams_();
    getAITreeVariable(&mIsContinueRotateOrMove_a, "IsContinueRotateOrMove");
}

}  // namespace uking::ai
