#include "Game/AI/AI/aiRemainsWaterBattleRoot.h"
#include "Game/AI/aiUnk_7102419cb0.h"
#include "Game/gameIceBlockMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

RemainsWaterBattleRoot::RemainsWaterBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWaterBattleRoot::~RemainsWaterBattleRoot() = default;

bool RemainsWaterBattleRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _80.mTimer = ksys::Timer(0, 0);
    _98.mTimer = ksys::Timer(*mFirstBulletTimer_s, *mFirstBulletTimer_s);
    _b0 = 0;
    _b4 = false;
    _b5 = false;
    _b6 = false;
    _b7 = false;
    _b8 = false;
    _b9 = false;
    _ba = false;
    sub_7100545B8C();
    _c0.initWithName(mActor, "Demo344_1", "Demo344_1");
    _c0.loadEvent();
}

void RemainsWaterBattleRoot::leave_() {
    _c0.unloadEvent();
}

void RemainsWaterBattleRoot::sub_7100545B8C() {
    if (!mRemainsWaterBattleInfo_a)
        return;
    auto* info = sead::DynamicCast<Unk_7102419cb0>(
        *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
    if (!info)
        return;

    switch (info->_3c) {
    case 1:
        if (!isCurrentChild("攻撃中"))
            changeChild("攻撃中");
        break;
    case 0:
        if (!isCurrentChild("生成中"))
            changeChild("生成中");
        break;
    case 2:
        if (!isCurrentChild("へたれ中"))
            changeChild("へたれ中");
        break;
    }
}

bool RemainsWaterBattleRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x8000069)
        return false;

    _b9 = true;
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info) {
            ++info->_38;
            info->_34 = true;
        }
    }
    _98.mTimer = ksys::Timer(*mAfterDamageTimer_s, *mAfterDamageTimer_s);
    _b5 = false;
    if (auto* mgr = IceBlockMgr::instance())
        mgr->_14e = true;
    return true;
}

void RemainsWaterBattleRoot::loadParams_() {
    getStaticParam(&mCallClearDemoTimer_s, "CallClearDemoTimer");
    getStaticParam(&mAfterDamageTimer_s, "AfterDamageTimer");
    getStaticParam(&mAfterPaooonTimer_s, "AfterPaooonTimer");
    getStaticParam(&mAfterHellTimer_s, "AfterHellTimer");
    getStaticParam(&mFirstBulletTimer_s, "FirstBulletTimer");
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

}  // namespace uking::ai
