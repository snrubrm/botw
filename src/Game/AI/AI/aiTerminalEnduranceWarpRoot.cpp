#include "Game/AI/AI/aiTerminalEnduranceWarpRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

TerminalEnduranceWarpRoot::TerminalEnduranceWarpRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TerminalEnduranceWarpRoot::~TerminalEnduranceWarpRoot() = default;

bool TerminalEnduranceWarpRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TerminalEnduranceWarpRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::enableAllAttClients(mActor);
    const bool on = mActor->checkBasicSig();
    _38.x();
    if (on)
        changeChild("On待機");
    else
        changeChild("Off待機");
}

// NON_MATCHING: regalloc (the original materialises &_38 before disableAllAttClients)
void TerminalEnduranceWarpRoot::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("起動"))
        return;
    if (!child->isChangeable() && !child->isFinished())
        return;

    if (mActor->checkBasicSig()) {
        if (isCurrentChild("On待機")) {
            if (_38._30) {
                ksys::act::disableAllAttClients(mActor);
                _38.x();
                changeChild("起動");
            }
        } else if (isCurrentChild("Off待機")) {
            _38.x();
            changeChild("On待機");
        }
    } else if (isCurrentChild("On待機")) {
        _38.x();
        changeChild("Off待機");
    }
}

void TerminalEnduranceWarpRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TerminalEnduranceWarpRoot::loadParams_() {}

bool TerminalEnduranceWarpRoot::handleMessage_(const ksys::Message* message) {
    return _38.sub_710070A674(*message);
}

}  // namespace uking::ai
