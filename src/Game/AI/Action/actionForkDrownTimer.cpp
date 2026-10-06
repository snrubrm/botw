#include "Game/AI/Action/actionForkDrownTimer.h"
#include <random/seadGlobalRandom.h>
#include "Game/Damage/dmgDamageManagerBase.h"
#include "Game/Damage/dmgStruct20.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkDrownTimer::ForkDrownTimer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDrownTimer::~ForkDrownTimer() = default;

bool ForkDrownTimer::init_(sead::Heap* heap) {
    const s32 time = *mTime_s;
    _40 = time;
    _44 = time;
    _30.mValue = time;
    return true;
}

void ForkDrownTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkDrownTimer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDrownTimer::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
}

// NON_MATCHING: the original keeps the compare of the freshly randomised timer as an unfolded float compare (we fold
// `(float)time > 0` to an integer compare) and tests the random range with `subs` + `b.eq` (we get `sub` + `cbz`)
void ForkDrownTimer::calc_() {
    auto* actor = mActor;
    bool is_in_water = false;
    if (actor->get68f()) {
        const f32 y = actor->getMtx().m[1][3];
        is_in_water = actor->get6f0() - y >= *mInWaterDepth_s;
    }
    if (is_in_water) {
        _30.sub_7100D3BC4C(-1.0f);
        if (!(_30.mValue <= 0.0f))
            return;
    } else {
        s32 time = _40;
        const s32 range = _44 - _40;
        if (range != 0)
            time += sead::GlobalRandom::instance()->getU32(range);
        _30.mValue = time;
        if (!(_30.mValue <= 0.0f))
            return;
    }
    if (auto* manager = mActor->getDamageMgr()) {
        uking::dmg::Struct20_2 damage;
        damage.mField_18 = 0x20;
        damage.mField_14 = 0x16;
        damage.mField_8 = 0;
        if (manager->mStruct20_b)
            manager->mStruct20_b->combineMaybe(&damage);
    }
}

}  // namespace uking::action
