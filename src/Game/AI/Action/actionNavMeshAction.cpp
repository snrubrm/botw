#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/AI/aiUnk_71007320F0.h"

namespace uking::action {

// NON_MATCHING: the 0x90-0xa3 zero/-1 stores are merged differently (stp xzr,x8 @0x90 vs str/stur/str)
NavMeshAction::NavMeshAction(const InitArg& arg) : ActionEx(arg) {}

// NON_MATCHING: the NavMeshCharacter setters are inline-only in the original and use one custom ldxr/stxr loop
// `(old & ~bit) | bit`; the sead::Atomic version has one `and` less (see NavMeshCharacter::inlineSetField2BC)
void NavMeshAction::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    auto* nav = actor->m45();
    if (!nav) {
        setFailed();
        return;
    }
    const f32 speed = actor->getVelocity().length();
    _60.value = speed;
    _60.prev_value = speed;
    sub_7100741034(&_6c, actor);
    _9c = nav->_8->_6c;
    _a0 = nav->_8->_a0->_10;
    nav->inlineSetField2BC(*mParams.mSpeed_s * 30.0f);
    nav->inlineSetField2C0(*mParams.mSpeed_s * 2 * 30.0f);
    _90 = nullptr;
    _98 = -1.0f;
}

// NON_MATCHING: same custom ldxr/stxr read-modify-write as enter_
void NavMeshAction::leave_() {
    auto* nav = mActor->m45();
    if (!nav)
        return;
    nav->inlineSetField2BC(_9c);
    nav->inlineSetField2C0(_a0);
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
