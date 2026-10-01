#include "Game/AI/AI/aiGetItemNormal.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

GetItemNormal::GetItemNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool GetItemNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GetItemNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::enableAttClient(mActor, "NoticeDo");
    changeChild("待機");
    _38 = true;
}

void GetItemNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GetItemNormal::loadParams_() {}

}  // namespace uking::ai
