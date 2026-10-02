#include "Game/AI/Action/actionMove2HomePos.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/Vibration.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

Move2HomePos::Move2HomePos(const InitArg& arg) : Move2HomePosBase(arg) {}

Move2HomePos::~Move2HomePos() = default;

bool Move2HomePos::init_(sead::Heap* heap) {
    return Move2HomePosBase::init_(heap);
}

// NON_MATCHING: instruction scheduling in the inlined matrix multiplication
void Move2HomePos::enter_(ksys::act::ai::InlineParamPack* params) {
    Move2HomePosBase::enter_(params);
    auto* actor = mActor;
    _78 = -1;
    _44.set(sead::Vector3f::zero);
    _38.set(_44 - sead::Vector3f::ey * *mDynMoveDis_d);

    sead::Vector3f home_pos;
    actor->getHomePos(&home_pos);

    auto* body = m32();
    if (body && !body->isAddedToWorld()) {
        sead::Matrix34f mtx;
        actor->getHomeMtx(&mtx);
        sead::Matrix34f offset;
        offset.makeT(_38);
        mtx.setMul(mtx, offset);
        actor->setMtx(mtx, true, true);
        actor->nullsub_4648();
        body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
    }

    if (*mIsVibration_s) {
        ksys::Vibration::Unk2 request;
        request._20 = *mVibPattern_s;
        request._18 = *mVibPower_s;
        request._1c = *mVibRange_s;
        request._28.set(*mVibDirection_s);
        request._0 = home_pos;
        request._10 = &actor->getMessageTransceiver();
        request._25 = 1;
        ksys::Vibration::instance()->sub_71010BB428(request);
    }
}

void Move2HomePos::leave_() {
    Move2HomePosBase::leave_();
    if (_78 >= 0)
        ksys::Vibration::instance()->sub_71010BB810(_78);
}

void Move2HomePos::loadParams_() {
    Move2HomePosBase::loadParams_();
    getStaticParam(&mVibDirection_s, "VibDirection");
    getStaticParam(&mVibPattern_s, "VibPattern");
    getStaticParam(&mVibPower_s, "VibPower");
    getStaticParam(&mVibRange_s, "VibRange");
    getStaticParam(&mIsVibration_s, "IsVibration");
}

void Move2HomePos::calc_() {
    Move2HomePosBase::calc_();
}

// NON_MATCHING: the original never sets the return register (w0 is whatever the last call returned)
bool Move2HomePos::handleMessage_(const ksys::Message& message) {
    if (message.getType() != 0x2000001)
        return false;
    _78 = *static_cast<const int*>(message.getUserData());
    return true;
}

}  // namespace uking::action
