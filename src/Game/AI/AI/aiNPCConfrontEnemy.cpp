#include "Game/AI/AI/aiNPCConfrontEnemy.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCConfrontEnemy::NPCConfrontEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg), _98(), _e8() {}

NPCConfrontEnemy::~NPCConfrontEnemy() = default;

bool NPCConfrontEnemy::init_(sead::Heap* heap) {
    _88 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCConfrontEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCConfrontEnemy::leave_() {
    mActor->getLodState()->mFlags8.reset(0x40000);
    sub_71005D7518(mActor, true);
}

void NPCConfrontEnemy::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mRewardDistance_s, "RewardDistance");
    getStaticParam(&mTerrorDistAfterPlayerRescue_s, "TerrorDistAfterPlayerRescue");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

// 0x71004c83dc
bool NPCConfrontEnemy::sub_71004C83DC() {
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

// 0x71004c82d0
void NPCConfrontEnemy::sub_71004C82D0() {
    mActor->x_6();
    _98[0] = ksys::Timer(5.0f, 5.0f);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("お礼", &pack);
}

// 0x71004c8ddc
void NPCConfrontEnemy::sub_71004C8DDC(const sead::Vector3f& pos) {
    _98[1] = ksys::Timer(600.0f, 600.0f);
    sub_71005D76E0(mActor, true);
    ksys::act::setEnabledTalkAndLockOn(mActor, false);
    _88->_1048 = 2;
    sub_7100713564(mActor, 2);
    _88->_1038 = 0;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("気絶前振り向き", &pack);
}

// 0x71004c84c8
void NPCConfrontEnemy::sub_71004C84C8() {
    mActor->x_6();
    if (!_90 && !_91) {
        if (_93) {
            _88->_1048 = 0;
            sub_7100713564(mActor, 0);
        } else {
            _88->_1048 = 1;
            sub_7100713564(mActor, 1);
        }
    }
    if (sub_71005DB7E4(mActor, 0) && !_90 && !_91) {
        sub_71004C82D0();
        return;
    }
    if (sub_71005DB7E4(mActor, 0))
        setFinished();
    else
        changeChild("納刀", nullptr);
}

}  // namespace uking::ai
