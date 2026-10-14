#include "Game/Actor/AI/aiWillBallRoot.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"

namespace uking::ai {

WillBallRoot::WillBallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallRoot::~WillBallRoot() = default;

bool WillBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _174 = false;
    _176 = false;
    _120.x();
    _90.x();
    if (mActor->getRootAi()->getI() == 6) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        // C++14 evaluation order: the original evaluates the destination first
        _80.operator=(act::PlayerInfo::getSomeProcLink());
        if (_80.hasProc()) {
            const auto& mtx = mActor->getMtx();
            const sead::Vector3f pos{mtx(0, 3), mtx(1, 3), mtx(2, 3)};
            sub_71005F5CEC(0, pos, *mCount_m);
        } else {
            changeChild("待機");
        }
    } else {
        changeChild("待機");
    }
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->_14c = 0;
    _170 = static_cast<f32>(*mMagneLightningTime_s);
}

void WillBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallRoot::loadParams_() {
    getStaticParam(&mMagneLightningTime_s, "MagneLightningTime");
    getStaticParam(&mMinimizedTime_s, "MinimizedTime");
    getStaticParam(&mImmidiateLightningXZ_s, "ImmidiateLightningXZ");
    getStaticParam(&mImmidiateLightningY_s, "ImmidiateLightningY");
    getStaticParam(&mImmidiateLightningXZTarget_s, "ImmidiateLightningXZTarget");
    getStaticParam(&mImmidiateLightningYTarget_s, "ImmidiateLightningYTarget");
    getStaticParam(&mLightningTimeMinimizeDist_s, "LightningTimeMinimizeDist");
    getStaticParam(&mIsExplode_s, "IsExplode");
    getMapUnitParam(&mCount_m, "Count");
}

bool WillBallRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000007) {
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        return true;
    }

    if (!isCurrentChild("待機"))
        return _120.m2(*message);
    if (_90._30)
        return false;
    if (auto* grab = mActor->m128(); grab && grab->m2())
        return false;
    if (!_90.m2(*message))
        return false;
    if (_90._38._48 == 2 || _90._38._48 == 3) {
        _90.x();
        return false;
    }
    return true;
}

// 0x71005f5cec
void WillBallRoot::sub_71005F5CEC(s32 command, const sead::Vector3f& base_pos, s32 wait_time) {
    _120.x();
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_80, &accessor);
    accessor.getActorMtx();
    ksys::act::ai::InlineParamPack params;
    params.addActor(_80, "TargetActor", -1);
    params.addVec3(base_pos, "BasePos", -1);
    params.addInt(wait_time, "WaitTime", -1);
    params.addInt(command, "Command", -1);
    changeChild("念受信", &params);
}

}  // namespace uking::ai
