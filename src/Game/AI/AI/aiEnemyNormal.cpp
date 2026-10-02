#include "Game/AI/AI/aiEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyNormal::EnemyNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the original keeps the sender base vptr stores (_130/_2e0) after the payload resets;
// our `= default` Unk_7102357d20 dtor is elided (same issue as every other sender owner's dtor)
EnemyNormal::~EnemyNormal() {
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
}

bool EnemyNormal::init_(sead::Heap* heap) {
    _3ac.reset(4);
    _3ac.set(2);
    return true;
}

void EnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNormal::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSoundLostTimer_s, "SoundLostTimer");
    getStaticParam(&mNoActionReactTimeMin_s, "NoActionReactTimeMin");
    getStaticParam(&mNoActionReactTimeMax_s, "NoActionReactTimeMax");
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
    getStaticParam(&mNpcTerritoryArea_s, "NpcTerritoryArea");
    getStaticParam(&mNoPlayerTerritoryArea_s, "NoPlayerTerritoryArea");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mEnlargeAwnRatio_s, "EnlargeAwnRatio");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mSpeadDist2_s, "SpeadDist2");
    getStaticParam(&mHomePosRadius_s, "HomePosRadius");
    getStaticParam(&mSubsTerritoryArea_s, "SubsTerritoryArea");
    getStaticParam(&mLostExtinguishFireDist_s, "LostExtinguishFireDist");
    getStaticParam(&mShortRangeTerritoryArea_s, "ShortRangeTerritoryArea");
    getStaticParam(&mCloseRangeTerritoryArea_s, "CloseRangeTerritoryArea");
    getStaticParam(&mPressBreakObject_s, "PressBreakObject");
    getStaticParam(&mTerritoryHeight_s, "TerritoryHeight");
    getStaticParam(&mIsMindDoubtTarget_s, "IsMindDoubtTarget");
    getStaticParam(&mFortressTag_s, "FortressTag");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getAITreeVariable(&mPlayerSoundSealRefCount_a, "PlayerSoundSealRefCount");
    getAITreeVariable(&mSealNoPlayerAwnRequestCount_a, "SealNoPlayerAwnRequestCount");
}

void EnemyNormal::m35() {
    m64();
    m37();
}

void EnemyNormal::m42() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(*mEnlargeAwnRatio_s);
}

void EnemyNormal::m48(sead::Vector3f* pos) {
    mActor->getHomePos(pos);
}

s32 EnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    return sTable[idx];
}

void EnemyNormal::m64() {
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DCBDC(8);
    sub_71005D8E9C(mActor);
}

bool EnemyNormal::m65(sead::Heap* heap) {
    _48 = new (heap) Unk_710039D8F0;
    return _48 != nullptr;
}

bool EnemyNormal::m73() {
    return isCurrentChild("プレイヤー発見") || isCurrentChild("諦め");
}

void EnemyNormal::m43() {
    sub_71003A19AC();
}

}  // namespace uking::ai
