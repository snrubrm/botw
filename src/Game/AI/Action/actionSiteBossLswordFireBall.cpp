#include "Game/AI/Action/actionSiteBossLswordFireBall.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

SiteBossLswordFireBall::SiteBossLswordFireBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossLswordFireBall::~SiteBossLswordFireBall() = default;

bool SiteBossLswordFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mWaitASName_s.isEmpty()) {
        mFlags.reset(Flag::Changeable);
    } else {
        playAS(mWaitASName_s.cstr(), true, 0, 0, -1.0f);
        mFlags.set(Flag::Changeable);
    }
    _64.reset(*mAppearInterval_s);
    _60 = false;
}

void SiteBossLswordFireBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordFireBall::loadParams_() {
    getStaticParam(&mAppearInterval_s, "AppearInterval");
    getStaticParam(&mBallAppearOffset_s, "BallAppearOffset");
    getStaticParam(&mFireBallScale_s, "FireBallScale");
    getStaticParam(&mIsShowChildDevice_s, "IsShowChildDevice");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getDynamicParam(&mPartsName_d, "PartsName");
}

void SiteBossLswordFireBall::calc_() {
    _64.update();
    if (mActor->getASList()->x(0x37, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        _60 = true;
        sub_710025D85C();
    }
    if (_64.value <= sead::Mathf::epsilon()) {
        if (!_60)
            sub_710025D85C();
        setFinished();
    }
    if (*mIsShowChildDevice_s) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            auto& child_devices = boss->_1560;
            for (s32 i = 0; i < 20; ++i) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&child_devices._1e0[i], &accessor);
                if (!accessor.isStateCalc()) {
                    child_devices.sub_710066D708(i);
                    break;
                }
            }
        }
    }
}

}  // namespace uking::action
