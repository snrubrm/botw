#include "Game/AI/aiUnk_710073EBD4.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <geom/seadGeometry.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"

ksys::act::BaseProcLink& sub_710073E9A8(ksys::act::Actor* actor, const sead::SafeString& name) {
    if (sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return static_cast<uking::act::Enemy*>(actor)->_1128.getActorPartsActor(name);
    return ksys::act::getDummyBaseProcLink();
}

void sub_71006DED9C(const ksys::act::ActorConstDataAccess& accessor, ksys::act::BaseProc* proc);

void sub_710073EA44(ksys::act::Actor* actor, const sead::SafeString& name, const sead::Matrix34f& mtx,
                    const sead::Vector3f* vel, const sead::Vector3f* ang_vel, bool a6) {
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return;
    auto* enemy = static_cast<uking::act::Enemy*>(actor);
    auto& link = enemy->getActorPartsActor(name);
    if (!link.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    acquireActor(&link, &accessor);
    accessor.setProperties(mtx, vel, ang_vel, nullptr, true, 2, -1);
    {
        ksys::act::ActorConstDataAccess accessor2;
        acquireActor(&link, &accessor2);
        sub_71006DED9C(accessor2, enemy);
        if (a6)
            enemy->sub_7100D3D2B4(name);
    }
}

Unk_710073ebd4::Unk_710073ebd4(ksys::act::Actor* actor)
    : mActor(sead::DynamicCast<uking::act::Enemy>(actor)) {}

Unk_710073ebd4::~Unk_710073ebd4() {}

bool Unk_710073ebd4::sub_710073ECC0() {
    auto* model = mActor->getModel();
    if (!mBaseNode_s.isEmpty() && model)
        mBone = model->searchBone(mBaseNode_s);
    else
        mBone.reset();
    return true;
}

void Unk_710073ebd4::sub_710073ED20(const ksys::act::ai::ActionBase* action) {
    action->getStaticParam(&mSeqBank_s, "SeqBank");
    action->getStaticParam(&mTargetBone_s, "TargetBone");
    action->getStaticParam(&mPartsKey_s, "PartsKey");
    action->getStaticParam(&mShootSpeed_s, "ShootSpeed");
    action->getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    action->getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    action->getStaticParam(&mBaseNode_s, "BaseNode");
    action->getStaticParam(&mShootOffset_s, "ShootOffset");
    action->getStaticParam(&mShootRotate_s, "ShootRotate");
    action->getStaticParam(&mShootRotSpeed_s, "ShootRotSpeed");
    action->getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    action->getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    action->getDynamicParam(&mDynTargetPos_d, "TargetPos");
}

void Unk_710073ebd4::sub_710073EEE4(const ksys::act::ai::ActionBase* action) {
    action->getDynamicParam(&mDynTargetVel_d, "TargetVel");
}

bool Unk_710073ebd4::sub_710073EF50(const ksys::act::ai::ActionBase*) {
    mWork = mPartsKey_s;
    auto* actor = mActor;
    if (sead::IsDerivedFrom<uking::act::Enemy>(actor)) {
        auto* enemy = static_cast<uking::act::Enemy*>(actor);
        auto& link = enemy->getActorPartsActor(mWork);
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            return accessor.isStateSleep();
        }
    }
    return false;
}

void Unk_710073ebd4::sub_710073F040() {
    if (!mDynTargetPos_d)
        return;
    sead::Vector3f target;
    sub_710073F3FC(&target, 0.0f);
    sead::Matrix34f mtx;
    sead::Vector3f vel;
    sead::Vector3f ang_vel;
    sub_710073F1BC(&mtx, &vel, &ang_vel, &target, true, &sead::Vector3f::ez, 1.0f);
    sub_710073EA44(mActor, mWork, mtx, &vel, &ang_vel, !mIsReuseBullet);
}

void Unk_710073ebd4::sub_710073F0C8(sead::Matrix34f* mtx, sead::Vector3f* vel,
                                  sead::Vector3f* ang_vel, bool actor_space,
                                  const sead::Vector3f* direction, f32 scale) {
    sead::Vector3f target;
    sub_710073F3FC(&target, 0.0f);
    sub_710073F1BC(mtx, vel, ang_vel, &target, actor_space, direction, scale);
}

void Unk_710073ebd4::sub_710073F14C(const sead::Vector3f* target) {
    sead::Matrix34f mtx;
    sead::Vector3f vel;
    sead::Vector3f ang_vel;
    sub_710073F1BC(&mtx, &vel, &ang_vel, target, true, &sead::Vector3f::ez, 1.0f);
    sub_710073EA44(mActor, mWork, mtx, &vel, &ang_vel, !mIsReuseBullet);
}

// NON_MATCHING: The same-TU parts lookup is inlined; vector output scheduling also differs.
void Unk_710073ebd4::sub_710073F1BC(sead::Matrix34f* mtx, sead::Vector3f* vel,
                                  sead::Vector3f* ang_vel, const sead::Vector3f* target,
                                  bool actor_space, const sead::Vector3f* direction, f32 scale) {
    sead::Matrix34f pose;
    sead::Matrix33f base_rotation;
    sub_710073F7F0(&pose, &base_rotation);
    const sead::Vector3f position = pose.getTranslation();
    f32 gravity;
    {
        auto& link = sub_710073E9A8(mActor, mWork);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        sead::Vector3f gravity_vector;
        sub_710072DC50(&gravity_vector, mActor);
        gravity = gravity_vector.y * (1.0f / 900.0f);
    }
    sead::Vector3f front;
    if (actor_space)
        front.setRotated(mActor->getMtx(), *direction);
    else
        front.setRotated(base_rotation, *direction);
    sead::Vector3f velocity;
    sub_71005DDF80(&velocity, target, &position, &front, mDirMinAngle_s, mDirMaxAngle_s,
                   *mShootSpeed_s, gravity * scale, *mMaxNoiseDist_s);
    sead::Vector3f angular_velocity;
    angular_velocity.setRotated(base_rotation, *mShootRotSpeed_s);
    *mtx = pose;
    *vel = velocity;
    *ang_vel = angular_velocity;
}

// NON_MATCHING: The same-TU parts lookup inlines, and vector validation and temporary allocation differ.
void Unk_710073ebd4::sub_710073F3FC(sead::Vector3f* out, f32 lead_time) {
    sead::Matrix34f pose;
    sub_710073F7F0(&pose, nullptr);
    const sead::Vector3f position = pose.getTranslation();
    sead::Vector3f target = *mDynTargetPos_d;
    if (mOffsetHeight_s)
        target.y += *mOffsetHeight_s;
    f32 gravity;
    {
        auto& link = sub_710073E9A8(mActor, mWork);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        sead::Vector3f gravity_vector;
        sub_710072DC50(&gravity_vector, mActor);
        gravity = gravity_vector.y;
    }
    if (mDynTargetVel_d &&
        !mDynTargetVel_d->equals(sead::Vector3f::zero, sead::Mathf::epsilon()) &&
        !mDynTargetVel_d->isNan()) {
        sead::Vector3f predicted = target;
        sead::Vector3f velocity;
        sub_710072D344(&velocity, position, predicted, *mShootSpeed_s, gravity * (1.0f / 900.0f));
        const f32 distance = sead::Vector2f(predicted.x - position.x, predicted.z - position.z).length();
        const f32 speed = sead::Vector2f(velocity.x, velocity.z).length();
        sead::Vector3f direction = mDynTargetVel_d ? *mDynTargetVel_d : sead::Vector3f::zero;
        const f32 target_speed = direction.normalize();
        if (!direction.isNan() && direction != sead::Vector3f(0.0f, 0.0f, 0.0f)) {
            sead::Sphere3f sphere(mActor->getMtx().getTranslation(), 1.0f);
            sead::Ray3f ray(target, direction);
            f32 intersection = 0.0f;
            f32 travel;
            if (!((sphere.getCenter() - target).length() <= 1.0f)) {
                travel = (distance / speed + lead_time) * target_speed;
                if (sead::Geometry::calcIntersectionRayToSphere(ray, sphere, &intersection, nullptr)) {
                    if (!(intersection > travel))
                        travel = intersection;
                }
            } else {
                travel = 0.0f;
            }
            target.setScaleAdd(travel, direction, predicted);
        }
    }
    out->set(target);
}

// NON_MATCHING: The base orientation copy stays after the transform math instead of across the
// trigonometric calls, changing stack size and register allocation.
void Unk_710073ebd4::sub_710073F7F0(sead::Matrix34f* out, sead::Matrix33f* base_rotation) {
    sead::Matrix34f base;
    if (mBone.isValid()) {
        mActor->getModel()
            ->getUnits()
            .unsafeAt(mBone.model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&base, mBone.bone_index);
    } else {
        base = mActor->getMtx();
    }
    sead::Matrix34f offset;
    offset.makeRT(*mShootRotate_s, *mShootOffset_s);
    out->setMul(base, offset);
    if (base_rotation)
        *base_rotation = sead::Matrix33f(base);
}

bool Unk_710073ebd4::sub_710073FA54() {
    if (auto* as_list = mActor->getASList())
        return as_list->x(0x47, nullptr, *mTargetBone_s, *mSeqBank_s,
                          &ksys::as::ASList::Unk2::sub_71011637EC, true);
    return false;
}
