#include "Game/AI/Action/actionFollowIgniteToBonePos.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FollowIgniteToBonePos::FollowIgniteToBonePos(const InitArg& arg) : RotateTurnToTarget(arg) {}

FollowIgniteToBonePos::~FollowIgniteToBonePos() = default;

bool FollowIgniteToBonePos::init_(sead::Heap* heap) {
    if (!RotateTurnToTarget::init_(heap))
        return false;
    if (!_c0.init(heap))
        return false;
    _c0._38 = sead::DelegateR<FollowIgniteToBonePos, sead::Vector3f>(
        this, &FollowIgniteToBonePos::sub_710005B104);
    return true;
}

// NON_MATCHING: scheduling of the offset loads / first additions (all instructions identical)
sead::Vector3f FollowIgniteToBonePos::sub_710005B104() {
    sead::Matrix34f mtx;
    if (!mBoneName_s.isEmpty() && mActor->sub_71011D57F8(&mtx, mBoneName_s)) {
        sead::Vector3f pos;
        mtx.getTranslation(pos);
        const sead::Matrix34f actor_mtx = mActor->getMtx();
        sead::Vector3f side, up, front;
        actor_mtx.getBase(side, 0);
        actor_mtx.getBase(up, 1);
        actor_mtx.getBase(front, 2);
        pos += side * *mLocalOffSetX_s;
        pos += up * *mLocalOffSetY_s;
        pos += front * *mLocalOffSetZ_s;
        pos.y = 0.0f;
        return pos;
    }
    return mActor->getMtx().getTranslation();
}

void FollowIgniteToBonePos::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
    _c0.enter(params);
}

void FollowIgniteToBonePos::leave_() {
    RotateTurnToTarget::leave_();
    _c0.leave();
}

void FollowIgniteToBonePos::loadParams_() {
    RotateTurnToTarget::loadParams_();
    getStaticParam(&mLocalOffSetX_s, "LocalOffSetX");
    getStaticParam(&mLocalOffSetY_s, "LocalOffSetY");
    getStaticParam(&mLocalOffSetZ_s, "LocalOffSetZ");
    getStaticParam(&mIsIgnitePosYZero_s, "IsIgnitePosYZero");
    getStaticParam(&mBoneName_s, "BoneName");
    _c0.loadParams();
}

void FollowIgniteToBonePos::calc_() {
    RotateTurnToTarget::calc_();
    _c0.calc();
}

bool FollowIgniteToBonePos::handleMessage_(const ksys::Message* message) {
    return _c0.handleMessage(*message);
}

}  // namespace uking::action
