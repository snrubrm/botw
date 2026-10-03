#include "Game/AI/Action/actionPlayerWarpEffectValueSetter.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

PlayerWarpEffectValueSetter::PlayerWarpEffectValueSetter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerWarpEffectValueSetter::~PlayerWarpEffectValueSetter() = default;

bool PlayerWarpEffectValueSetter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerWarpEffectValueSetter::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 frame = *mSetFrame_d;
    const f32 time = frame > 0.0f ? frame : 1.0f;
    _3c = time;
    _30 = ksys::Timer(time, time);
    const f32 ratio = sead::Mathf::clamp(_30.value / _3c, 0.0f, 1.0f);
    if (auto* player = ksys::act::PlayerInfo::instance()->getPlayer()) {
        if (*mChangeType_d)
            static_cast<ksys::act::Player*>(player)->sub_710084BA90(1.0f - ratio);
        else
            static_cast<ksys::act::Player*>(player)->sub_710084BA90(ratio);
    }
}

void PlayerWarpEffectValueSetter::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerWarpEffectValueSetter::loadParams_() {
    getDynamicParam(&mChangeType_d, "ChangeType");
    getDynamicParam(&mSetFrame_d, "SetFrame");
}

void PlayerWarpEffectValueSetter::calc_() {
    if (isFinished() || isFailed())
        return;
    _30.update();
    const f32 ratio = sead::Mathf::clamp(_30.value / _3c, 0.0f, 1.0f);
    if (auto* player = ksys::act::PlayerInfo::instance()->getPlayer()) {
        if (*mChangeType_d)
            static_cast<ksys::act::Player*>(player)->sub_710084BA90(1.0f - ratio);
        else
            static_cast<ksys::act::Player*>(player)->sub_710084BA90(ratio);
    }
    if (_30.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action
