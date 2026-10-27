#include "Game/Actor/AI/aiViewWaitEndWhenAimed.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include <gsys/gsysModel.h>
#include <math/seadMathCalcCommon.h>

// 0x71005e0cb0: whether the player targeted by `actor` (or by the actor itself for non-enemies) is
// being aimed at: within `range` * the player's radius, within `angle` of the direction from the
// bone/actor position, and on the expected side. `mode` additionally accepts the other aimed poses.
// NON_MATCHING: clang selects the target link with a csel where the original branches to the dummy
// link; the rest of the body is instruction-for-instruction identical.
bool sub_71005E0CB0(bool* out, ksys::act::Actor* actor, const gsys::BoneAccessKeyEx* key,
                    bool mode, f32 angle, f32 range) {
    const ksys::act::BaseProcLink& link =
        sead::IsDerivedFrom<uking::act::Enemy>(actor)
            ? static_cast<uking::act::Enemy*>(actor)->_c48._8
            : ksys::act::sUnk_71026505e0;
    if (!link.hasProc())
        return false;

    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&link, &accessor);
    if (!accessor.isPlayerProfile())
        return false;

    if (mode) {
        if (!accessor.m180() && !accessor.m181() && !accessor.x_29() && !accessor.m179())
            return false;
    } else {
        if (!accessor.m180() && !accessor.m181())
            return false;
    }

    sead::Matrix34f mtx;
    if (auto* model = actor->getModel()) {
        if (key->getKey().model_unit_index != -1 && key->getKey().bone_index != -1)
            model->getBoneWorldMatrix(key->getKey(), &mtx);
        else
            mtx = actor->getMtx();
    } else {
        mtx = actor->getMtx();
    }

    const sead::Vector3f pos = mtx.getTranslation();
    const sead::Vector3f player_pos = accessor.getPosCopyMagnesis();
    const f32 radius = accessor.m248();
    sead::Vector3f to_player = pos - player_pos;
    const f32 dist = to_player.normalize();
    if (dist >= radius * range)
        return false;

    const sead::Vector3f forward = accessor.getPosCopyMagnesis2();
    *out = (to_player.x * forward.z - to_player.z * forward.x) < 0.0f;
    return to_player.dot(forward) >= sead::Mathf::cos(angle);
}

namespace uking::ai {

ViewWaitEndWhenAimed::ViewWaitEndWhenAimed(const InitArg& arg) : TimeredViewWait(arg) {}

// NON_MATCHING: the natural base destructor call remains TimeredViewWait; original own/base definitions are preserved.
ViewWaitEndWhenAimed::~ViewWaitEndWhenAimed() = default;

bool ViewWaitEndWhenAimed::init_(sead::Heap* heap) {
    if (!TimeredViewWait::init_(heap))
        return false;

    if (!mBoneName_s.isEmpty() && mActor->getModel())
        _a0.search(mActor->getModel(), mBoneName_s);
    else
        _a0.getKey().reset();
    return true;
}

void ViewWaitEndWhenAimed::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredViewWait::enter_(params);
}

void ViewWaitEndWhenAimed::calc_() {
    bool direction = false;
    if (sub_71005E0CB0(&direction, mActor, &_a0, true, *mAimedAngle_s, *mBowRange_s)) {
        const int end_time = *mEndTime_s;
        if (end_time <= 0) {
            setFinished();
            return;
        }
        if (_70 >= end_time)
            _70 = end_time;
    }
    TimeredViewWait::calc_();
}

void ViewWaitEndWhenAimed::leave_() {
    TimeredViewWait::leave_();
}

void ViewWaitEndWhenAimed::loadParams_() {
    TimeredViewWait::loadParams_();
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mAimedAngle_s, "AimedAngle");
    getStaticParam(&mBowRange_s, "BowRange");
    getStaticParam(&mBoneName_s, "BoneName");
}

}  // namespace uking::ai
