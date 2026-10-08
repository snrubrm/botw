#include "Game/AI/AI/aiGuardianMiniRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GuardianMiniRoot::GuardianMiniRoot(const InitArg& arg) : EnemyRoot(arg) {}

GuardianMiniRoot::~GuardianMiniRoot() = default;

bool GuardianMiniRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void GuardianMiniRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void GuardianMiniRoot::leave_() {
    EnemyRoot::leave_();
    mActor->sub_71011DA868(&_288);
    stopXLinks();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62DD0(1.0f);
}

// NON_MATCHING: loop strength reduction only: the original keeps `this + 0x330` / `this + 0x393` as two induction
// pointers (x24 / x26, `this` is dead after them); ours keeps `this` and a scaled offset (one extra register).
void GuardianMiniRoot::stopXLinks() {
    s32 i = 0;
    for (auto& handles : _330) {
        handles.mELink.kill();
        handles.mSLink.fade();
        _393[i++] = false;
    }
}

void GuardianMiniRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mNeckRotRatio_s, "NeckRotRatio");
    getStaticParam(&mJustGuardNumForBreak_s, "JustGuardNumForBreak");
    getStaticParam(&mRotStopSpeed_s, "RotStopSpeed");
    getAITreeVariable(&mDamagedCount_a, "DamagedCount");
    getAITreeVariable(&mIsTransformedGuardianMini_a, "IsTransformedGuardianMini");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

bool sub_71004282EC(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    const bool* value = nullptr;
    auto* root_ai = actor->getRootAi();
    if (!root_ai)
        return false;
    if (!root_ai->getMapUnitParam(&value, "IsAnnihilateDungeonEnemy"))
        return false;
    return *value;
}

// NON_MATCHING: same values, calls and branches; differs in register allocation and three
// scheduling items: _210 is stored before the deg computation (ours sinks it after the a-csels),
// _20c is copied with integer loads plus fmov (ours uses float loads), and the final snap select
// is csel-le (all of `fr <= 60`, `!(fr > 60)` and `60 >= fr` lower to ls/gt instead).
bool GuardianMiniRoot::handleMessage_(const ksys::Message* message) {
    if (!_228.m2(*message))
        return EnemyRoot::handleMessage_(message);
    if (_228._34._10)
        return false;
    f32 angle = _210;
    if (angle >= 6.2831855f)
        angle += -6.2831855f;
    else if (angle <= -6.2831855f)
        angle += 6.2831855f;
    _210 = angle;
    const s32 deg = s32(angle * 57.295776f);
    const f32 c = _228._34._c;
    _20c = c;
    s32 a = deg > 359 ? deg - 360 : deg;
    a = deg > 0 ? a : deg + 360;
    f32 adjust;
    const s32 r = a % 120;
    if (r == 0) {
        adjust = 0.0f;
    } else {
        adjust = f32(120 - r) * 0.017453292f;
        if (c < 0.0f)
            adjust += -2.0943952f;
    }
    const f32 y = _228._34._0.y;
    const f32 side = c < 0.0f ? -y : y;
    _214 = adjust + (angle + side);
    const s32 deg2 = s32(_214 * 57.295776f);
    const s32 r2 = deg2 % 120;
    _218 = deg2;
    if (r2 != 0) {
        const f32 fr = r2 > 0 ? (f32)r2 : -(f32)r2;
        const s32 q = deg2 / 120;
        const f32 fq = deg2 > 119 ? (f32)q : -(f32)q;
        const s32 qi = (s32)fq;
        s32 snapA, snapB;
        if (deg2 < 0) {
            snapA = qi * -120;
            snapB = -120 - qi * 120;
        } else {
            snapA = qi * 120;
            snapB = qi * 120 + 120;
        }
        if (fr <= 60.0f)
            _218 = snapA;
        else
            _218 = snapB;
    }
    s32 v = _218;
    if (v > 359) {
        v += -360;
        _218 = v;
    } else if (v <= -360) {
        v += 360;
        _218 = v;
    }
    _20c = c > 0.0f ? c : -c;
    _21c = false;
    return true;
}

}  // namespace uking::ai
