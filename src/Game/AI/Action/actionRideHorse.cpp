#include "Game/AI/Action/actionRideHorse.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::act {
// Declaration-only native helper (0x7100e6dc50); namespace and signature are inferred from the call sites.
bool sub_7100E6DC50(const ksys::act::ActorConstDataAccess& accessor);
}  // namespace uking::act

namespace uking::action {

RideHorse::RideHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RideHorse::~RideHorse() = default;

bool RideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the branch on the acquired flag tests the masked value (w8) in the original and the
// raw return value (w0) here; everything else is identical.
void RideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* ride_info = mActor->getPlayerRideInfo();
    if (!ride_info) {
        setFailed();
        return;
    }
    if (ride_info->_30 & 1) {
        setFinished();
        return;
    }
    if (!mTargetActor_d->hasProc()) {
        setFailed();
        return;
    }
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    if (act::sub_7100E6DC50(accessor)) {
        if (auto* horse = accessor.getHorseOptions()) {
            _180 = horse->sub_7100E8BFD4();
            if (_180) {
                if (auto* controller = mActor->getCharacterController()) {
                    controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
                    sub_710073FA90(&_6c, mActor);
                    _68 = 0;
                    playAS("HorseRideonStart", false, 0, 0, -1.0f);
                    return;
                }
            }
        }
    }
    setFailed();
}

bool RideHorse::sub_710023A050(ksys::act::BaseProcLink* link) {
    if (link->hasProc() && !link->isAccessingSpecifiedProcUnsafe(mActor)) {
        auto* proc = link->getProc(nullptr, mActor);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            return mActor->getConnectedCalcParent() == actor;
    }
    return false;
}

void RideHorse::sub_710023A4C8() {
    auto* ride_info = mActor->getPlayerRideInfo();
    if (ride_info->_30 & 1)
        ride_info->sub_7100E7C0EC();
    if (_180) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(mTargetActor_d, &accessor);
        if (act::sub_7100E6DC50(accessor)) {
            if (auto* horse = accessor.getHorseOptions())
                static_cast<act::Unk_7100e8b2b8*>(horse)->_8 &= ~0x100u;
        }
        _180 = false;
    }
}

void RideHorse::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F60604();
    mActor->sub_71011DA834(&_90);
    if (!isFinished())
        sub_710023A4C8();
}

void RideHorse::loadParams_() {
    getStaticParam(&mJumpHeightOffset_s, "JumpHeightOffset");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mFarRotSpeed_s, "FarRotSpeed");
    getStaticParam(&mNearRotSpeed_s, "NearRotSpeed");
    getStaticParam(&mRideRotSpeed_s, "RideRotSpeed");
    getStaticParam(&mLoopASInterpolateTime_s, "LoopASInterpolateTime");
    getStaticParam(&mPredictedRidePosOffset_s, "PredictedRidePosOffset");
    getStaticParam(&mPreRideSklRootOffset_s, "PreRideSklRootOffset");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool RideHorse::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003) {
        mActor->sub_71011DA834(&_90);
        sub_710023A4C8();
    }
    return false;
}

void RideHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
