#include "Game/AI/AI/aiNPCRunaway.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

namespace uking::ai {

NPCRunaway::NPCRunaway(const InitArg& arg) : ksys::act::ai::Ai(arg), _90(), _e8() {}

NPCRunaway::~NPCRunaway() = default;

bool NPCRunaway::init_(sead::Heap* heap) {
    _80 = sead::DynamicCast<act::NPC>(mActor);
    _88 = mActor->getParam()->getRes().mGParamList->getNpc()->mTolerantTime.ref();
    return true;
}

void NPCRunaway::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCRunaway::leave_() {
    mActor->getLodState()->mFlags8.reset(0x40000);
    sub_71005D7518(mActor, true);
}

void NPCRunaway::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mCorneredDistance_s, "CorneredDistance");
    getStaticParam(&mStandRateTime_s, "StandRateTime");
    getStaticParam(&mStandingTime_s, "StandingTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

// 0x71004dd700
void NPCRunaway::sub_71004DD700() {
    _90[1] = ksys::Timer(300.0f, 300.0f);
    sub_71007130BC(mActor, true);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("待機", &pack);
}

// 0x71004dea74
void NPCRunaway::sub_71004DEA74() {
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, "", 0);
    sub_71007130BC(mActor, false);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mTargetVel_d, "TargetVel", -1);
    changeChild("逃走", &pack);
}

// 0x71004dec8c
void NPCRunaway::sub_71004DEC8C() {
    if (_80) {
        if (_8c) {
            _80->_1048 = 0;
            sub_7100713564(mActor, 0);
        } else {
            _80->_1048 = 1;
            sub_7100713564(mActor, 1);
        }
    }
    _90[2] = ksys::Timer(5.0f, 5.0f);
    sub_71007130BC(mActor, true);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("お礼", &pack);
}

// 0x71004df0b0
void NPCRunaway::sub_71004DF0B0(const sead::Vector3f& pos) {
    if (_80) {
        _80->_1048 = 2;
        sub_7100713564(mActor, 2);
    }
    _90[5] = ksys::Timer(600.0f, 600.0f);
    sub_71005D7644(mActor, false);
    sub_71005D76E0(mActor, true);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("気絶前振り向き", &pack);
}

// 0x71004df1d0
void NPCRunaway::sub_71004DF1D0() {
    if (_80) {
        if (_8c) {
            _80->_1048 = 0;
            sub_7100713564(mActor, 0);
        } else {
            _80->_1048 = 1;
            sub_7100713564(mActor, 1);
        }
    }
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, "", 0);
    sub_71007130BC(mActor, true);
    sub_71005D7644(mActor, false);
    _90[4] = ksys::Timer(*mStandingTime_s * 30.0f, *mStandingTime_s * 30.0f);
    changeChild("立ち上がる", nullptr);
}

// 0x71004deba0
bool NPCRunaway::sub_71004DEBA0() {
    for (s32 i = 0; i < 10; ++i) {
        if (!_e8[i].hasProc())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_e8[i], &accessor);
        const sead::Vector3f other_pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - other_pos;
        const f32 distance = diff.length();
        if (distance < *mReleaseDistance_s)
            return false;
    }
    return true;
}

}  // namespace uking::ai
