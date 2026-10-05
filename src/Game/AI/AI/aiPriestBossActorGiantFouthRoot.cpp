#include "Game/AI/AI/aiPriestBossActorGiantFouthRoot.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossActorGiantFouthRoot::PriestBossActorGiantFouthRoot(const InitArg& arg)
    : PriestBossActorGiantRoot(arg) {}

PriestBossActorGiantFouthRoot::~PriestBossActorGiantFouthRoot() = default;

bool PriestBossActorGiantFouthRoot::init_(sead::Heap* heap) {
    return PriestBossActorGiantRoot::init_(heap);
}

// NON_MATCHING: the compiler folds the state selection into a conditional increment.
void PriestBossActorGiantFouthRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorGiantRoot::enter_(params);
    sub_71005089F4(m34() ? State::_9 : State::_8);
    _120.reset(0.0f);
}

void PriestBossActorGiantFouthRoot::calc_() {
    PriestBossActorGiantRoot::calc_();
}

void PriestBossActorGiantFouthRoot::leave_() {
    PriestBossActorGiantRoot::leave_();
}

void PriestBossActorGiantFouthRoot::loadParams_() {
    PriestBossActorGiantRoot::loadParams_();
    getStaticParam(&mStompDistance_s, "StompDistance");
    getStaticParam(&mStompInAreaTimer_s, "StompInAreaTimer");
    getStaticParam(&mStompAction_s, "StompAction");
    getStaticParam(&mStompAlwaysChange_s, "StompAlwaysChange");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

const char* PriestBossActorGiantFouthRoot::m36() {
    return "第四段階";
}

// NON_MATCHING: block layout only (the original loads `_9c` separately in each branch of the flag test; ours hoists
// the load above it)
PriestBossActorGiantRoot::Attack PriestBossActorGiantFouthRoot::m46() {
    auto* unit = sub_7100505BE4();
    if (m34())
        return Attack::_9;

    if (unit->isFlagOn(Unk_7102450fa8::Flag::_3))
        return _9c != State::_6 ? Attack::_6 : Attack::_1;

    if (_9c == State::_1) {
        auto* meta_ai = sead::DynamicCast<Unk_7102450fa8>(
            *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
        if (meta_ai && (meta_ai->_444 || !sead::GlobalRandom::instance()->getBool())) {
            meta_ai->_444 = false;
            return Attack::_5;
        }
        return Attack::_8;
    }
    return Attack::_1;
}

// NON_MATCHING: `always_change` is computed with `cset` / `and` instead of branches, and the timer value is re-read
// from `this + 0x120` instead of through the pointer used for update()
bool PriestBossActorGiantFouthRoot::m48() {
    if (!*mStompAction_s)
        return false;

    bool always_change = false;
    if (*mStompAlwaysChange_s)
        always_change = _9c == State::_8;
    if (_9c == State::_10)
        return false;

    auto* child = getCurrentChild();
    const f32 stomp_distance = *mStompDistance_s;
    const sead::Vector3f& pos = sub_71005D9330(mActor);
    const auto& mtx = mActor->getMtx();
    const f32 dx = pos.x - mtx.m[0][3];
    const f32 dz = pos.z - mtx.m[2][3];
    if (std::sqrt(dx * dx + dz * dz) < stomp_distance)
        _120.update();
    else
        _120 = ksys::Timer(*mStompInAreaTimer_s, *mStompInAreaTimer_s);

    if (!(_120.value <= sead::Mathf::epsilon()))
        return false;
    if (!(child->isFinished() || (child->isFailed() | always_change)))
        return false;

    _120 = ksys::Timer(*mStompInAreaTimer_s, *mStompInAreaTimer_s);
    return true;
}

}  // namespace uking::ai
