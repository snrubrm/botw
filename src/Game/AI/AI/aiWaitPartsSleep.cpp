#include "Game/AI/AI/aiWaitPartsSleep.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

WaitPartsSleep::WaitPartsSleep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitPartsSleep::~WaitPartsSleep() = default;

bool WaitPartsSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitPartsSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("行動", params);
}

// NON_MATCHING: the original loads the list head (enemy + 0x1130) before computing the end (enemy + 0x1128) and
// keeps the node in x21 / the end in x20; ours computes the end first (register assignment only)
void WaitPartsSleep::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (child->isFinished())
            setFinished();
        else
            child->setFailed();
    } else if (child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            child->setFailed();
    } else if (child->isChangeable()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            ksys::act::ActorConstDataAccess accessor;
            for (auto* part : enemy->_1128.mList) {
                ksys::act::acquireActor(&part->mLink, &accessor);
                if (accessor.isStateCalc())
                    return;
            }
        }
        setFinished();
    }
}

void WaitPartsSleep::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitPartsSleep::loadParams_() {}

}  // namespace uking::ai
