#include "Game/AI/AI/aiPriestBossGiantStageRotate.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossGiantStageRotate::PriestBossGiantStageRotate(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossGiantStageRotate::~PriestBossGiantStageRotate() = default;

bool PriestBossGiantStageRotate::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossGiantStageRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
    _140.makeAllZero();
    if (!*mSendOnThrowASEvent_s)
        sub_710051C210();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    if (*mIsUseStartAction_s)
        changeChild("開始", &pack);
    else
        changeChild("回転終了待機", &pack);
}

// NON_MATCHING: block layout of the three command cases (the original places command 2 right after the compares)
// and the xz direction copy into the message payload is a single 8-byte load/store in the original (ours: ldp/stp)
void PriestBossGiantStageRotate::sub_710051C210() {
    auto* unit = sub_7100505BE4();
    if (!unit || !unit->isFlagOn(Unk_7102450fa8::Flag::_5))
        return;

    const s32 command = *mSendCommand_s;
    if (command == 0) {
        sead::Vector3f dir = sub_71005D9330(mActor);
        dir -= mActor->getMtx().getTranslation();
        dir.y = 0;
        dir.normalize();
        _d0.set(dir.x * sUnk_7102450fa0 + sUnk_71025c8cf8.x,
                dir.z * sUnk_7102450fa0 + sUnk_71025c8cf8.z);
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
            _58._18._0 = _d0;
            _58._18._c = false;
            _58._18._8 = 0;
        }
        _140.setBit(Flag(Flag::_0));
    } else if (command == 1) {
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
            _58._18._c = false;
            _58._18._8 = 2;
        }
        _140.setBit(Flag(Flag::_2));
    } else if (command == 2) {
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
            _58._18._c = false;
            _58._18._8 = 1;
        }
        _140.setBit(Flag(Flag::_1));
    }

    _58.sub_710070DBB0(unit->_1a0, true);
}

void PriestBossGiantStageRotate::leave_() {
    PriestBossMode::leave_();
}

void PriestBossGiantStageRotate::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mSendCommand_s, "SendCommand");
    getStaticParam(&mSendOnThrowASEvent_s, "SendOnThrowASEvent");
    getStaticParam(&mIsUseStartAction_s, "IsUseStartAction");
}

bool PriestBossGiantStageRotate::handleMessage_(const ksys::Message* message) {
    if (!_88._30 && _88.m2(*message))
        return true;
    return false;
}

// NON_MATCHING: operand order of the orr in setBit (same as PriestBossIronBallRoot::m41)
bool PriestBossGiantStageRotate::handleAck_(const ksys::MessageAck* ack) {
    if (!_58.sub_710070E070(*ack))
        return false;
    _140.setBit(Flag(Flag::_6));
    return true;
}

}  // namespace uking::ai
