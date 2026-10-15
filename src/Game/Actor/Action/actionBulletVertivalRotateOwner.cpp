#include "Game/Actor/Action/actionBulletVertivalRotateOwner.h"
#include <math/seadQuat.h>
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

BulletVertivalRotateOwner::BulletVertivalRotateOwner(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BulletVertivalRotateOwner::~BulletVertivalRotateOwner() = default;

bool BulletVertivalRotateOwner::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: owner-position component loads and normalization/cross-product stores differ.
void BulletVertivalRotateOwner::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor);
    if (!bullet) {
        setFailed();
        return;
    }
    const sead::Vector3f position = bullet->getMtx().getTranslation();
    ksys::act::ActorLinkConstDataAccess owner;
    ksys::act::acquireActor(&bullet->_ba0, &owner);
    sead::Vector3f center = owner.getActorMtx().getTranslation();
    center.y += *mOffsetY_s;
    sead::Vector3f direction = position - center;
    _50 = direction.normalize();
    _58 = 1;
    _38.value = 0;
    _38.prev_value = 0;
    _44.value = 0;
    _44.prev_value = 0;
    const f32 side = direction.dot(owner.getActorMtx().getBase(0));
    const f32 angle = std::atan2(direction.cross(sead::Vector3f::ey).length(),
                               direction.dot(sead::Vector3f::ey));
    _54 = side >= 0.0f ? -angle : angle;
    mFlags.set(Flag::Changeable);
}

void BulletVertivalRotateOwner::leave_() {
    ksys::act::ai::Action::leave_();
}

void BulletVertivalRotateOwner::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotSpdAccRatio_s, "RotSpdAccRatio");
    getStaticParam(&mOffsetY_s, "OffsetY");
}

// NON_MATCHING: normalized movement stores and quaternion rotation scheduling differ.
void BulletVertivalRotateOwner::calc_() {
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor);
    if (!bullet) {
        setFailed();
        return;
    }
    _38.lerp(*mRotSpeed_s, *mRotSpdAccRatio_s, *mRotSpeed_s * 0.1f);
    _38.updateStats();
    ksys::act::ActorLinkConstDataAccess owner;
    ksys::act::acquireActor(&bullet->_ba0, &owner);
    sead::Vector3f center = owner.getActorMtx().getTranslation();
    center.y += *mOffsetY_s;
    _54 += f32(_58) * _38.mean;
    _54 = ksys::util::sub_71011EF0CC(_54);
    sead::Quatf rotation;
    rotation.setAxisRadian(owner.getActorMtx().getBase(2), _54);
    sead::Matrix33f matrix;
    matrix.fromQuat(rotation);
    sead::Vector3f offset;
    offset.setRotated(matrix, sead::Vector3f::ey);
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f movement = center + offset * _50 - position;
    const f32 distance = movement.normalize();
    _44.lerp(distance, 0.1f);
    _44.updateStats();
    ksys::act::sub_7100EE57FC(mActor, position + movement * _44.mean);
}

}  // namespace uking::action
