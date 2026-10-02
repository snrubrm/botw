#include "Game/AI/AI/aiRemainsWaterRoot.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

RemainsWaterRoot::RemainsWaterRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsWaterRoot::~RemainsWaterRoot() = default;

bool RemainsWaterRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsWaterRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

void RemainsWaterRoot::calc_() {
    RemainsRoot::calc_();
    m35(false);
}

void RemainsWaterRoot::leave_() {
    RemainsRoot::leave_();
    auto** info = static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a);
    if (info && *info == &_58)
        *info = nullptr;
}

void RemainsWaterRoot::loadParams_() {
    RemainsRoot::loadParams_();
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

void RemainsWaterRoot::m35(bool x) {
    if (x) {
        sub_710054BAC8(true);
        return;
    }

    auto* child = getCurrentChild();
    if (child && (child->isFinished() || child->isFailed() || child->isChangeable()))
        sub_710054BAC8(false);
}

void RemainsWaterRoot::sub_710054BAC8(bool x) {
    switch (sub_710054BD54(x)) {
    case 0:
        if (isCurrentChild("水中待機"))
            return;
        changeChild("水中待機");
        if (mRemainsWaterBattleInfo_a &&
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) == &_58) {
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) = nullptr;
        }
        break;
    case 1:
        if (isCurrentChild("水上待機"))
            return;
        if (mRemainsWaterBattleInfo_a &&
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) == &_58) {
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) = nullptr;
        }
        changeChild("水上待機");
        break;
    case 2:
        if (isCurrentChild("遺物戦中")) {
            if (mRemainsWaterBattleInfo_a &&
                !*static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a)) {
                *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) = &_58;
                for (auto*& ptr : _58._8)
                    ptr = nullptr;
                _58._30 = false;
                _58._31 = false;
                _58._32 = false;
                _58._33 = false;
                _58._34 = false;
                _58._38 = 0;
                _58._3c = 0;
                if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint1())
                    ++_58._38;
                if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint2())
                    ++_58._38;
                if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint3())
                    ++_58._38;
                if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint4())
                    ++_58._38;
            }
            return;
        }
        if (mRemainsWaterBattleInfo_a) {
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) = &_58;
            for (auto*& ptr : _58._8)
                ptr = nullptr;
            _58._30 = false;
            _58._31 = false;
            _58._32 = false;
            _58._33 = false;
            _58._34 = false;
            _58._38 = 0;
            _58._3c = 0;
            if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint1())
                ++_58._38;
            if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint2())
                ++_58._38;
            if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint3())
                ++_58._38;
            if (ksys::gdt::getFlag_Water_Relic_BreakWeakPoint4())
                ++_58._38;
        }
        changeChild("遺物戦中");
        break;
    default:
        if (isCurrentChild("通常行動"))
            return;
        m36();
        if (mRemainsWaterBattleInfo_a &&
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) == &_58) {
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a) = nullptr;
        }
        break;
    }
}

s32 RemainsWaterRoot::sub_710054BD54(bool x) {
    if (x) {
        if (!ksys::gdt::getFlag_IsPlayed_Demo112_0())
            return 0;
        if (ksys::gdt::getFlag_Water_Relic_Step4())
            return 3;
        return ksys::gdt::getFlag_Water_Relic_BattleTime() ? 2 : 1;
    }
    if (isCurrentChild("水中待機"))
        return ksys::gdt::getFlag_IsPlayed_Demo112_0();
    if (isCurrentChild("水上待機"))
        return ksys::gdt::getFlag_Water_Relic_BattleTime() ? 2 : 1;
    return isCurrentChild("遺物戦中") ? 2 : 3;
}

void RemainsWaterRoot::m36() {
    xlinkEventOn(mActor, 25, 1, false);
    changeChild("通常行動");
}

}  // namespace uking::ai
