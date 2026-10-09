#include "Game/AI/Action/actionGuardianMiniNeckSpinBeam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMini.h"

namespace uking::action {

GuardianMiniNeckSpinBeam::GuardianMiniNeckSpinBeam(const InitArg& arg) : NeckSpinBeam(arg) {}

GuardianMiniNeckSpinBeam::~GuardianMiniNeckSpinBeam() = default;

void GuardianMiniNeckSpinBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpinBeam::enter_(params);
    _190 = 0;
    _194 = sead::Mathf::pi2();
    _194 *= *mSpinNum_s;
    _198 = sub_71005DB4DC(mActor);
    sead::Vector3f direction;
    if (sub_7100197BE4(&direction)) {
        _b8.sub_71006F3BC4(&direction);
        _19c = direction;
    }
}

void GuardianMiniNeckSpinBeam::loadParams_() {
    NeckSpinBeam::loadParams_();
    getStaticParam(&mSpinNum_s, "SpinNum");
    getStaticParam(&mMaxLengthTime_s, "MaxLengthTime");
    getStaticParam(&mIsStraight_s, "IsStraight");
}

void GuardianMiniNeckSpinBeam::calc_() {
    NeckSpinBeam::calc_();
    sead::Vector3f direction;
    if (sub_7100197BE4(&direction)) {
        _b8.sub_71006F3BC4(&direction);
        _19c = direction;
    }
    _190 += sead::Mathf::abs(m32());
    if (_190 >= _194) {
        sub_71005DB44C(mActor, _198, 0.f);
        setFinished();
    }
}

void GuardianMiniNeckSpinBeam::m33() {
    const f32 speed = *mSpinSpeed_s;
    if (speed <= sead::Mathf::epsilon() && speed >= -sead::Mathf::epsilon())
        return;
    NeckSpin::m33();
}

const sead::SafeString& GuardianMiniNeckSpinBeam::m34() {
    if (!mBeamActorName_s.isEmpty())
        return mBeamActorName_s;
    auto* params = mActor->getParam()->getRes().mGParamList;
    if (params) {
        auto* guardian = params->getGuardianMini();
        if (guardian)
            return guardian->mLineBeamName.ref();
    }
    return sead::SafeString::cEmptyString;
}

const sead::SafeString& GuardianMiniNeckSpinBeam::m35() {
    if (!mBeamActorKey_s.isEmpty())
        return mBeamActorKey_s;
    auto* params = mActor->getParam()->getRes().mGParamList;
    if (params) {
        auto* guardian = params->getGuardianMini();
        if (guardian)
            return guardian->mBeamName.ref();
    }
    return sead::SafeString::cEmptyString;
}

}  // namespace uking::action
