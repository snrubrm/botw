#include "Game/AI/AI/aiRemainsWaterBulletController.h"
#include "Game/AI/aiUnk_7102419cb0.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

RemainsWaterBulletController::RemainsWaterBulletController(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainsWaterBulletController::~RemainsWaterBulletController() {
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info) {
            for (auto*& ptr : info->_8)
                ptr = nullptr;
        }
    }
    sub_7100546D30(-1);
}

bool RemainsWaterBulletController::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterBulletController::enter_(ksys::act::ai::InlineParamPack* params) {
    _2d0.clear();
    _330.clear();
    _374 = ksys::Timer(0, 0);
    const sead::Vector3f half_width = *mInsideAreaWidth_s * 0.5f;
    _354.set(*mInsideAreaCenter_s - half_width, half_width + *mInsideAreaCenter_s);
    sub_71005474E4();
    if (ksys::gdt::getFlag_Water_Relic_ChanceTime())
        sub_710054779C();
    else
        sub_71005478C8();
}

void RemainsWaterBulletController::leave_() {
    sub_7100546D30(-1);
    sub_7100547D20(-1);
    _2d0.clear();
    _330.clear();
}

void RemainsWaterBulletController::sub_7100546D30(s32 type) {
    if (type == -1 || type == 0) {
        for (auto& bullet : _f0) {
            if (bullet.mHandle.isAllocatedOrFailed())
                bullet.mHandle.deleteProc();
        }
    }
    if (type == -1 || type == 1) {
        for (auto& bullet : _1e0) {
            if (bullet.mHandle.isAllocatedOrFailed())
                bullet.mHandle.deleteProc();
        }
    }
}

// NON_MATCHING: the original keeps two "destructor + constant" exits (ours merges the result) and
// puts the MessageType temporary below the accessor on the stack
bool RemainsWaterBulletController::sub_7100548A38() {
    const s32 num = _2d0.size();
    if (num < 1)
        return false;

    {
        ksys::act::ActorConstDataAccess accessor;
        auto* bullet = _2d0.at(sead::GlobalRandom::instance()->getU32(num));
        if (bullet && !bullet->_28 &&
            ksys::act::acquireActor(&bullet->mLink.mLink, &accessor)) {
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800006b),
                        nullptr);
            bullet->_28 = true;
            _330.pushBack(bullet);
            return true;
        }
    }
    return false;
}

void RemainsWaterBulletController::sub_710054779C() {
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info) {
            for (auto*& ptr : info->_8)
                ptr = nullptr;
        }
    }
    ksys::gdt::setFlag_Water_Relic_ChanceTime(true);
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info)
            info->_3c = 2;
    }
    changeChild("冷却中");
}

void RemainsWaterBulletController::sub_71005478C8() {
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info) {
            for (auto*& ptr : info->_8)
                ptr = nullptr;
        }
    }
    ksys::gdt::setFlag_Water_Relic_ChanceTime(false);
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info)
            info->_3c = 0;
    }
    changeChild("射出前待機");
}

bool RemainsWaterBulletController::sub_7100548B34() {
    for (auto& bullet : _f0) {
        if (bullet.mLink.mLink.hasProc())
            return false;
    }
    for (auto& bullet : _1e0) {
        if (bullet.mLink.mLink.hasProc())
            return false;
    }
    return true;
}

void RemainsWaterBulletController::loadParams_() {
    getStaticParam(&mInsideAreaRadius_s, "InsideAreaRadius");
    getStaticParam(&mFirstBulletTimer_s, "FirstBulletTimer");
    getStaticParam(&mSecondBulletTimer_s, "SecondBulletTimer");
    getStaticParam(&mNextBulletTimerSuccess_s, "NextBulletTimerSuccess");
    getStaticParam(&mNextBulletTimerFail_s, "NextBulletTimerFail");
    getStaticParam(&mChaseBulletNum_s, "ChaseBulletNum");
    getStaticParam(&mExplodeBulletNum_s, "ExplodeBulletNum");
    getStaticParam(&mChaseBulletActorName_s, "ChaseBulletActorName");
    getStaticParam(&mExplodeBulletActorName_s, "ExplodeBulletActorName");
    getStaticParam(&mInsideAreaCenter_s, "InsideAreaCenter");
    getStaticParam(&mInsideAreaWidth_s, "InsideAreaWidth");
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

}  // namespace uking::ai
