#include "Game/Actor/AI/aiPriestBossGiantStageRotate.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

PriestBossGiantStageRotate::PriestBossGiantStageRotate(const InitArg& arg) : PriestBoss(arg) {}

PriestBossGiantStageRotate::~PriestBossGiantStageRotate() = default;

bool PriestBossGiantStageRotate::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossGiantStageRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
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

// NON_MATCHING: the original has a dead SEAD_ENUM stack round trip (value 0) before storing the mode inside the lock
// 0x710051bfa4
// NON_MATCHING: enum stack slots, packed direction stores and accessor cleanup scheduling differ.
void PriestBossGiantStageRotate::sub_710051BFA4() {
    auto* unit = sub_7100505BE4();
    ksys::act::ActorLinkConstDataAccess accessor;
    if (unit->sub_71007194CC(&accessor)) {
        if (_140.isOnBit(Flag(Flag::_3))) {
            sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
            _58._18._8 = 4;
            _58._18._c = false;
            _58._18._0 = _d0;
        } else if (_140.isOnBit(Flag(Flag::_4))) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
                _58._18._c = false;
                _58._18._8 = 5;
            }
            for (s32 i = 0; i < 8; ++i) {
                ksys::act::ActorLinkConstDataAccess child;
                if (unit->sub_71007194D4(i + 11, &child)) {
                    {
                        sead::ScopedLock<sead::JobQueueLock> lock(&_d8._18.mLock);
                        _d8._18._0 = 1;
                        _d8._18._4 = sead::Vector3f::zero;
                    }
                    _d8.sub_710070DBB0(*child.getMessageTransceiverId(), false);
                }
            }
        } else if (_140.isOnBit(Flag(Flag::_5))) {
            sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
            _58._18._c = false;
            _58._18._8 = 6;
        }
        _58.sub_710070DD78(accessor, true);
    }
    setFinished();
}

// 0x710051c5dc
// NON_MATCHING: received-command switch order and enum temporary stack slots differ.
void PriestBossGiantStageRotate::calc_() {
    PriestBoss::calc_();
    if (_88._30) {
        switch (_88._34._8) {
        case 5:
            _140.setBit(Flag(Flag::_4));
            // fallthrough
        case 6:
            _140.setBit(Flag(Flag::_5));
            break;
        case 3:
            _140.setBit(Flag(Flag::_3));
            break;
        }
        _88.x();
    }
    if (*mSendOnThrowASEvent_s && mActor->getASList()->x(
            0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        sub_710051C210();
    }
    auto* child = getCurrentChild();
    if (!child)
        return;
    child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    if (isCurrentChild("開始")) {
        if (child->isFinished() || child->isFailed()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("回転終了待機", &pack);
        }
    } else if (isCurrentChild("回転終了待機")) {
        if (_140.isOnBit(Flag(Flag::_4)) || _140.isOnBit(Flag(Flag::_3)) ||
            _140.isOnBit(Flag(Flag::_5))) {
            sub_710051BFA4();
            setFinished();
        }
    }
}

void PriestBossGiantStageRotate::leave_() {
    PriestBoss::leave_();
    sub_710051C44C();
    if (!_140.isOnBit(Flag(Flag::_1)) && !_140.isOnBit(Flag(Flag::_0)) && !_140.isOnBit(Flag(Flag::_2)))
        return;
    if (_140.isOnBit(Flag(Flag::_6)) || !sub_7100505BE4())
        return;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
        _58._18._c = false;
        _58._18._8 = 1;
    }
    _58.sub_710070DBB0(sub_7100505BE4()->_1a0, false);
}

void PriestBossGiantStageRotate::loadParams_() {
    PriestBoss::loadParams_();
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

// 0x710051c44c
// NON_MATCHING: the Unk1 enum temporary is above the accessor in the original (sp+0x28 vs ours sp+0) and the accessor
// address is recomputed for the destructor instead of being kept in a second callee-saved register
void PriestBossGiantStageRotate::sub_710051C44C() {
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    unit->sub_71007194D4(1, &accessor);
    if (accessor.hasProc()) {
        _118.sub_710070E2BC(false, -1);
        _118.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
}

}  // namespace uking::ai
