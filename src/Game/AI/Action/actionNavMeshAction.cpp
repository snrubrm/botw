#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71007320F0.h"

namespace uking::action {

// NON_MATCHING: the 0x90-0xa3 zero/-1 stores are merged differently (stp xzr,x8 @0x90 vs str/stur/str)
NavMeshAction::NavMeshAction(const InitArg& arg) : ActionEx(arg) {}

void NavMeshAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void NavMeshAction::leave_() {
    ActionEx::leave_();
}

void NavMeshAction::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinRadius_s, "FinRadius");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mAccRatio_s, "AccRatio");
    getStaticParam(&mParams.mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void NavMeshAction::calc_() {
    m32();
    m33();
    if (sub_71001F08E4())
        setFinished();
}

// NON_MATCHING: the three products of the dot product with the actor's z axis are scheduled in a
// different order (everything else is identical).
bool NavMeshAction::sub_71001F08E4() {
    auto* actor = mActor;
    const sead::Vector3f target = *m35();
    sead::Vector3f dir = target - mActor->getMtx().getTranslation();
    const f32 distance = dir.length();
    dir.y = 0.0f;
    dir.normalize();
    const f32 fin_radius = *mParams.mFinRadius_s + sub_71007320F0(actor, *mParams.mWeaponIdx_s);
    if (distance <= fin_radius) {
        const f32 dot = dir.x * actor->getMtx().m[0][2] + dir.y * actor->getMtx().m[1][2] +
                        dir.z * actor->getMtx().m[2][2];
        if (dot >= sead::Mathf::cos(*mParams.mFinRotate_s)) {
            if (sub_710072F944(actor, target, nullptr, fin_radius, 3.0f))
                return true;
        }
    }
    return false;
}

sead::Vector3f* NavMeshAction::m35() {
    return mParams.mTargetPos_d;
}

void NavMeshAction::m36(ksys::phys::CharacterController* controller, f32 speed,
                        const sead::Vector3f& up) {
    if (!controller)
        return;
    controller->sub_7100F5E7F0(speed * 30.0f);
    sub_710072C1B4(controller, up);
}

void NavMeshAction::m37(const sead::Matrix34f& mtx) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FC8C(mtx);
}

f32 NavMeshAction::sub_71001F1350() const {
    return *mParams.mSpeed_s;
}

f32 NavMeshAction::sub_71001F135C() const {
    return *mParams.mRotSpd_s;
}

}  // namespace uking::action
