#include "Game/AI/AI/aiLastBossThunderRoot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LastBossThunderRoot::LastBossThunderRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossThunderRoot::~LastBossThunderRoot() = default;

bool LastBossThunderRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossThunderRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("予兆");
    _38 = false;
}

void LastBossThunderRoot::calc_() {
    if (_38) {
        if (!_e0.hasProc()) {
            changeChild("削除");
            return;
        }
    } else {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
        if (parent && !_e0.hasProc())
            _e0.acquire(parent, false);
        if (_e0.hasProc()) {
            _40.x(_e0);
            _40._68 = sead::Matrix34f(sead::Matrix33f::ident);
            _40._98 = 3;
            mActor->sub_71011DA824(&_40);
            _38 = true;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("予兆")) {
            mActor->resetConnectedCalcParent(false);
            changeChild("攻撃発生");
        } else if (isCurrentChild("攻撃発生")) {
            changeChild("削除");
        }
    }
}

void LastBossThunderRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossThunderRoot::loadParams_() {}

}  // namespace uking::ai
