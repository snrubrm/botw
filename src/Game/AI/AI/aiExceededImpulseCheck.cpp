#include "Game/AI/AI/aiExceededImpulseCheck.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"

namespace uking::ai {

ExceededImpulseCheck::ExceededImpulseCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ExceededImpulseCheck::~ExceededImpulseCheck() = default;

bool ExceededImpulseCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ExceededImpulseCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("オフ");
}

void ExceededImpulseCheck::calc_() {
    auto* actor = mActor;
    if (!isCurrentChild("オフ"))
        return;
    auto* link = actor->getImpulseBaseProcLink();
    if (link && link->_10._c > 0 && link->_10._8 > 0)
        changeChild("オン");
}

void ExceededImpulseCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ExceededImpulseCheck::loadParams_() {}

}  // namespace uking::ai
