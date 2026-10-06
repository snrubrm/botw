#include "Game/AI/aiGuardianAimBeamState.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

GuardianAimBeamState::GuardianAimBeamState() = default;

GuardianAimBeamState::~GuardianAimBeamState() = default;

// NON_MATCHING: only store packing differs: the original pairs the first two random floats (`stp`) and
// writes the ELink position / scale as `stp w10,w10 [+0xb8]; stp z,w10 [+0xb0]` before reading the flags
bool GuardianAimBeamState::init(ksys::act::Actor* actor, const sead::SafeString& a1,
                                const sead::SafeString& a2, const sead::SafeString& a3,
                                const sead::SafeString& a4, const sead::SafeString& a5,
                                const sead::SafeString& a6, f32 a7, f32 a8, f32 a9, f32 a10,
                                const sead::Vector3f& target_pos, const sead::SafeString& node_name,
                                const sead::Vector3f& node_offset) {
    _0 = actor;
    _84 = a7;
    _94 = a8;
    _98 = a9;
    _28 = ksys::eft::searchAndEmitELink(actor, a1.cstr());
    _38 = ksys::eft::searchAndEmitELink(_0, a2.cstr());
    if (!a3.isEmpty())
        _48 = ksys::eft::searchAndEmitELink(_0, a3.cstr());
    _28.setPosition(target_pos);
    _9c = a10;
    _78 = sead::Vector3f(sead::GlobalRandom::instance()->getF32Range(-_84, _84),
                         sead::GlobalRandom::instance()->getF32Range(-_84, _84),
                         sead::GlobalRandom::instance()->getF32Range(-_84, _84));
    _88 = sead::Vector3f::zero;
    _58 = ksys::eft::searchAndEmitSLink(_0, a4.cstr(), false);
    _8 = a6;
    _18 = a5;
    if (node_name.isEmpty() || !actor->getModel())
        _a0.getKey().reset();
    else
        _a0.search(actor->getModel(), node_name);
    _e8 = node_offset;
    _d8 = 0;
    return true;
}

// NON_MATCHING: the original fades the two SLink handles with `Event::fade(0)`; lib/xlink2's
// HandleSLink::fade() has no frame argument (it always passes -1).
void GuardianAimBeamState::sub_71006F2D08() {
    _38.fade();
    _28.fade();
    _48.fade();
    _58.fade(0);
    _68.fade(0);
    _d8 = 0;
}

}  // namespace uking::ai
