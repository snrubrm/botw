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

void RemainsWaterBulletController::calc_() {
    sub_71005474E4();

    if (!mRemainsWaterBattleInfo_a)
        return;
    auto* info = sead::DynamicCast<Unk_7102419cb0>(
        *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
    if (!info)
        return;

    if (info->_34) {
        sub_7100547D20(-1);
        info->_34 = false;
        sub_71005478C8();
        return;
    }

    if (_36c != info->_38) {
        sub_7100547D20(-1);
        _36c = info->_38;
    }
    if (_36c <= 3)
        sub_7100547FF4();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("射出前待機")) {
            if (!sub_7100548220(false))
                sub_71005478C8();
        } else if (isCurrentChild("射出後待機")) {
            sub_71005484D4();
        } else if (isCurrentChild("冷却中")) {
            sub_710054779C();
        } else if (isCurrentChild("誘導弾発射")) {
            sub_7100548220(true);
        } else {
            sub_71005484D4();
        }
        return;
    }

    if (!child->isChangeable())
        return;

    if (isCurrentChild("射出前待機")) {
        sub_7100548220(false);
    } else if (isCurrentChild("射出後待機")) {
        if (!(_38.mTimer.value <= sead::Mathf::epsilon()))
            _38.sub_7100D3BCE4();
        sub_7100548638();
        if (_38.mTimer.value <= sead::Mathf::epsilon() && _370 <= 0) {
            if (_370 != 0 || (info->_30 && !info->_33)) {
                if (sub_7100548A38()) {
                    _38.mTimer = ksys::Timer(*mSecondBulletTimer_s, *mSecondBulletTimer_s);
                    ++_370;
                }
            }
        }
        if (_370 == 1 && _330.size() == 0) {
            _370 = 0;
            _38.mTimer.reset(*mFirstBulletTimer_s);
        }
        if (sub_7100548B34())
            sub_710054779C();
    }
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

// NON_MATCHING: stack slot of the MessageType temporary (sp+4 in the original) and regalloc
void RemainsWaterBulletController::sub_7100547D20(s32 type) {
    ksys::act::ActorConstDataAccess accessor;
    if (type == -1 || type == 0) {
        for (auto& bullet : _f0) {
            if (ksys::act::acquireActor(&bullet.mLink.mLink, &accessor)) {
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004),
                            nullptr);
                bullet.mLink.mLink.reset();
            }
        }
    }
    if (type == -1 || type == 1) {
        for (auto& bullet : _1e0) {
            if (ksys::act::acquireActor(&bullet.mLink.mLink, &accessor)) {
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004),
                            nullptr);
                bullet.mLink.mLink.reset();
            }
        }
    }
}

// NON_MATCHING: the original loads _374 before the parameter (see log: matches with a separate
// `delay` local)
void RemainsWaterBulletController::sub_7100548638() {
    _2d0.clear();
    for (auto& bullet : _f0) {
        if (bullet.mLink.mLink.hasProc() && !bullet._28)
            _2d0.pushBack(&bullet);
    }
    for (auto& bullet : _1e0) {
        if (bullet.mLink.mLink.hasProc() && !bullet._28)
            _2d0.pushBack(&bullet);
    }

    for (s32 i = 0; i < _330.size();) {
        if (!_330[i]->mLink.mLink.hasProc()) {
            _330.erase(i);
            if (_370 > 0)
                --_370;
            _38.mTimer = ksys::Timer(*mNextBulletTimerSuccess_s, *mNextBulletTimerSuccess_s);
            continue;
        }

        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_330[i]->mLink.mLink, &accessor) &&
            accessor.isStateSleep()) {
            sub_7100549108(_330[i]);
            _330.erase(i);
            if (_370 > 0)
                --_370;
            const f32 time =
                *mNextBulletTimerFail_s + (_374.value <= sead::Mathf::epsilon() ? 0.0f : 30.0f);
            _38.mTimer = ksys::Timer(time, time);
        } else {
            ++i;
        }
    }
}

// NON_MATCHING: same as sub_7100548638 (matches with a separate `delay` local)
void RemainsWaterBulletController::sub_71005484D4() {
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info) {
            for (auto*& ptr : info->_8)
                ptr = nullptr;
        }
    }
    _370 = 0;
    const f32 time =
        *mFirstBulletTimer_s + (_374.value <= sead::Mathf::epsilon() ? 0.0f : 30.0f);
    _38.mTimer = ksys::Timer(time, time);
    _330.clear();
    sub_7100548638();
    if (mRemainsWaterBattleInfo_a) {
        auto* info = sead::DynamicCast<Unk_7102419cb0>(
            *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a));
        if (info)
            info->_3c = 1;
    }
    changeChild("射出後待機");
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
