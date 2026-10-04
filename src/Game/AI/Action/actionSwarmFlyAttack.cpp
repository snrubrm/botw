#include "Game/AI/Action/actionSwarmFlyAttack.h"
#include "Game/Actor/actSwarm.h"
#include "Game/AI/aiUnk_710072A944.h"

namespace uking::action {

SwarmFlyAttack::SwarmFlyAttack(const InitArg& arg) : SwarmFlyMove(arg) {}

SwarmFlyAttack::~SwarmFlyAttack() = default;

bool SwarmFlyAttack::init_(sead::Heap* heap) {
    return SwarmFlyMove::init_(heap);
}

void SwarmFlyAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmFlyMove::enter_(params);
}

void SwarmFlyAttack::leave_() {
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor))
        sub_7100729F34(swarm);
    SwarmFlyMove::leave_();
}

void SwarmFlyAttack::loadParams_() {
    SwarmFlyMove::loadParams_();
    getStaticParam(&mFailTimeInClosePos_s, "FailTimeInClosePos");
    getStaticParam(&mApplyMaterialAnimNumPerFrame_s, "ApplyMaterialAnimNumPerFrame");
    getStaticParam(&mApplyMaterialAnimDist_s, "ApplyMaterialAnimDist");
}

// NON_MATCHING: the original tests the masked copy (`and w20, w0, #1; tbz w20`), clang tests w0 directly
void SwarmFlyAttack::calc_() {
    if (isFinishedOrFailed())
        return;
    sub_710028508C();
    const bool is_close = sub_7100134380();
    f32 time;
    if (is_close) {
        _15c = is_close;
        _150.update();
        mFlags.reset(Flag::Changeable);
        time = _150.value;
    } else {
        if (_15c) {
            setFinished();
            return;
        }
        time = 0.0f;
        _15c = is_close;
        _150 = ksys::Timer(0.0f, 0.0f, 1.0f);
    }
    if (time > *mFailTimeInClosePos_s) {
        setFailed();
        return;
    }
    if (!is_close && !sub_710013443C())
        setFailed();
    if (sub_7100285AD8())
        return;
    setFailed();
}

}  // namespace uking::action
