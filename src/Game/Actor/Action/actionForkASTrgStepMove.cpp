#include "Game/Actor/Action/actionForkASTrgStepMove.h"
#include <algorithm>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkASTrgStepMove::ForkASTrgStepMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgStepMove::~ForkASTrgStepMove() = default;

bool ForkASTrgStepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgStepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _84 = mActor->getVelocity();
    _84.y = 0;
    const f32 speed = _84.normalize();
    _50.value = speed;
    _50.prev_value = speed;
    _5c = -1.0f;
    sub_710073FA90(&_60, mActor);
}

void ForkASTrgStepMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgStepMove::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mCloseDist_s, "CloseDist");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinishDist_s, "FinishDist");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the original reloads the TargetPos pointer each time (ours keeps &mParams.mTargetPos_d in a
// register) and the Timer address is formed separately.
void ForkASTrgStepMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sub_71007320F0(mActor, *mParams.mWeaponIdx_s);
    sub_710073FA94(&_60, mActor);
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x2f, &query, 0, 0)) {
        _5c = query._10;
        mActor->getMtx().getBase(_84, 2);
        sead::Vector3f to_target = *mParams.mTargetPos_d - mActor->getMtx().getTranslation();
        to_target.y = 0.0f;
        const f32 distance = to_target.length();
        const f32 close_dist = *mParams.mCloseDist_s;
        const f32 remaining = std::max(
            distance - (close_dist + sub_71007320F0(mActor, *mParams.mWeaponIdx_s)), 0.0f);
        const f32 speed = remaining / query._10 * 1.3f;
        _50.value = speed;
        _50.prev_value = speed;
        _50.setToMin(*mParams.mSpeed_s);
        mFlags.reset(Flag::Changeable);
    } else if (_5c > 0.0f) {
        ksys::Timer::update(&_5c, -1.0f);
        _50 *= 0.94f;
        sub_7100738660(controller, 0.7f);
        mFlags.reset(Flag::Changeable);
    } else {
        _50 *= 0.5f;
        sead::Vector3f dir = *mParams.mTargetPos_d;
        dir -= mActor->getMtx().getTranslation();
        dir.y = 0.0f;
        const sead::Vector3f up = getUpDir(controller->get70());
        ksys::util::sub_71011EFA00(&dir, dir, up);
        dir.normalize();
        sub_710074006C(&_60, dir, up, true, 0.12f, *mParams.mRotSpd_s, *mParams.mRotSpd_s * 0.1f);
        sub_7100740E04(_60, controller);
        mFlags.set(Flag::Changeable);
    }
    _50.updateStats();
    controller->sub_7100F5E7F0(_50.value * 30.0f);
    sub_710072C1B4(controller, mActor->getMtx().getBase(2));
    const sead::Vector2f to_target(mParams.mTargetPos_d->x - mActor->getMtx()(0, 3),
                                   mParams.mTargetPos_d->z - mActor->getMtx()(2, 3));
    if (to_target.length() <= *mParams.mFinishDist_s)
        setFinished();
}

}  // namespace uking::action
