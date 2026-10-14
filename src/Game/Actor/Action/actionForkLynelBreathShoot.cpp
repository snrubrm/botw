#include "Game/Actor/Action/actionForkLynelBreathShoot.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

ForkLynelBreathShoot::ForkLynelBreathShoot(const InitArg& arg) : ForkVacuumShootToTarget(arg) {}

ForkLynelBreathShoot::~ForkLynelBreathShoot() = default;

bool ForkLynelBreathShoot::init_(sead::Heap* heap) {
    return ForkVacuumShootToTarget::init_(heap);
}

void ForkLynelBreathShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkVacuumShootToTarget::enter_(params);
}

void ForkLynelBreathShoot::leave_() {
    ForkVacuumShootToTarget::leave_();
}

void ForkLynelBreathShoot::loadParams_() {
    ForkVacuumShootToTarget::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mShootDir_s, "ShootDir");
}

void ForkLynelBreathShoot::calc_() {
    ForkVacuumShootToTarget::calc_();
}

// NON_MATCHING: scheduling of the transformed start point and the copy of the pose translation.
// Shoots the sleeping breath bullet (parts actor): sets its scale time, range and attack power, then
// places it on the shoot pose, pulled back to 90% of the way to any ground between the actor and it.
void ForkLynelBreathShoot::m32() {
    auto* actor = mActor;
    auto* parts = actor->m101();
    if (!parts)
        return;
    ksys::act::acc::Bullet bullet;
    ksys::act::acquireActor(&parts->getActorPartsActor(_20.mWork), &bullet);
    if (!bullet.hasProc() || !bullet.isStateSleep())
        return;

    bullet.setScaleTime(static_cast<f32>(*mEnlargeTime_s), actor);
    bullet.setRange(*mRange_s, actor);
    bullet.setAttackPower(
        static_cast<s32>(
            static_cast<f32>(actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref()) *
            *mAttackRatio_s),
        actor);

    sead::Matrix34f mtx;
    sead::Vector3f vel;
    sead::Vector3f ang_vel;
    _20.sub_710073F0C8(&mtx, &vel, &ang_vel, false, mShootDir_s, 0.0f);

    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f from;
        controller->sub_7100F62E6C(&from);
        sead::Matrix34f controller_mtx;
        controller->physicsXXXGetMtx_1(&controller_mtx);
        from.setMul(controller_mtx, from);
        const sead::Vector3f to = mtx.getTranslation();
        sead::Vector3f hit_pos;
        if (sub_710072E928(from, to, &hit_pos, nullptr, nullptr, 0.0f))
            mtx.setTranslation(from + (hit_pos - from) * 0.9f);
    }

    const sead::Vector3f scale(*mBreathSize_s, *mBreathSize_s, *mBreathSize_s);
    bullet.setProperties(mtx, &vel, &ang_vel, &scale, false, 0, -1);
}

}  // namespace uking::action
