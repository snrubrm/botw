#include "Game/AI/AI/aiPriestBossBananaMode.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::ai {

PriestBossBananaMode::PriestBossBananaMode(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossBananaMode::~PriestBossBananaMode() = default;

bool PriestBossBananaMode::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossBananaMode::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_7100505BE4()->_28.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&sub_7100505BE4()->_28, &accessor);
        accessor.getActorMtx().getTranslation(_a4);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_a4, "TargetPos", -1);
    pack.addActor(sub_7100505BE4()->_28, "TargetActor", -1);
    changeChild("バナナ夢中", &pack);
    mFlags.set(ksys::act::ai::ActionBase::Flag::Changeable);

    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100505BE4() && sub_7100505BE4()->sub_71007194CC(&accessor))
        _68 = *accessor.getMessageTransceiverId();
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
        _40._18._4 = 2;
        _40._18._0 = true;
    }
    _40.sub_710070DBB0(_68, true);
    _b0.makeAllZero();
    const f32 time_up = *mTimeUpFrames_s;
    if (time_up > 0) {
        _98.value = time_up;
        _98.previous_value = time_up;
    }
}

// NON_MATCHING: operand order of the and in isOnBit (see PriestBossIronBallRoot::m41)
// NON_MATCHING: the Flag temporaries share one stack slot in the original; and/orr operand order of
// the BitFlag tests (see PriestBossIronBallRoot::m41)
void PriestBossBananaMode::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("バナナ夢中") && !_b0.isOnBit(Flag(Flag::_1)))
            changeChild("解除");
        else
            setFinished();
        return;
    }

    if (!isCurrentChild("バナナ夢中")) {
        if (_b0.isOnBit(Flag(Flag::_3)))
            return;
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
            _40._18._4 = 2;
            _40._18._0 = false;
        }
        _40.sub_710070DBB0(_68, true);
        _b0.setBit(Flag(Flag::_3));
        return;
    }

    if (*mTimeUpFrames_s > 0) {
        _98.update();
        if (_98.value <= sead::Mathf::epsilon() && !_b0.isOnBit(Flag(Flag::_0)))
            changeChild("解除");
    }

    if (!_b0.isOnBit(Flag(Flag::_0)) && _b0.isOnBit(Flag(Flag::_2)) &&
        !sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_8))) {
        if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()) &&
            _b0.isOnBit(Flag(Flag::_0))) {
            mActor->resetConnectedCalcChild(false);
        }
        changeChild("解除");
        return;
    }

    if (sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_7))) {
        if (mActor->getASList()->x(69, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
                _40._18._4 = 1;
                _40._18._0 = true;
            }
            _40.sub_710070DBB0(_68, true);
            _b0.setBit(Flag(Flag::_0));
        } else if (_b0.isOnBit(Flag(Flag::_0)) && !_b0.isOnBit(Flag(Flag::_1)) &&
                   !mActor->getConnectedCalcChild()) {
            changeChild("解除");
            return;
        }
    } else if (_b0.isOnBit(Flag(Flag::_1)) || _b0.isOnBit(Flag(Flag::_0))) {
        if (mActor->getASList()->x(67, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
                _40._18._4 = 2;
                _40._18._0 = false;
            }
            _40.sub_710070DBB0(_68, true);
            _b0.setBit(Flag(Flag::_1));
            _b0.setBit(Flag(Flag::_3));

            auto* actor = mActor;
            const s32 heal = *mHealAmount_s;
            if (s32* life = actor->getLife()) {
                const s32 max_life = actor->getMaxLife();
                *life += heal;
                if (*life > max_life)
                    *life = max_life;
                else if (*life < 0)
                    *life = 0;
            }
        }
    } else {
        changeChild("解除");
    }

    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&sub_7100505BE4()->_28, &accessor) && accessor.hasProc()) {
        sead::Vector3f target_pos;
        accessor.getActorMtx().getTranslation(target_pos);
        const f32 dy = target_pos.y - mActor->getMtx().getTranslation().y;
        if (accessor.sub_7100D10FB8() || sead::Mathf::abs(dy) > 2.5f) {
            changeChild("解除");
        } else {
            getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
            getCurrentChild()->setDynamicParamImpl(sub_7100505BE4()->_28, "TargetActor",
                                                   &ksys::act::ai::ParamPack::setActor);
        }
    }
}

void PriestBossBananaMode::leave_() {
    PriestBossMode::leave_();
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
        _40._18._4 = 0;
    }
    _40.sub_710070DBB0(_68, true);
    if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()) &&
        _b0.isOnBit(Flag(Flag::_0))) {
        mActor->resetConnectedCalcChild(false);
    }
    *mReturnFromBananaMode_a = true;
}

void PriestBossBananaMode::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mHealAmount_s, "HealAmount");
    getStaticParam(&mTimeUpFrames_s, "TimeUpFrames");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

// NON_MATCHING: operand order of the orr in setBit (see PriestBossIronBallRoot::m41)
bool PriestBossBananaMode::handleAck_(const ksys::MessageAck& ack) {
    if (ack.getType() != 0x80000d8)
        return false;
    _b0.setBit(Flag(Flag::_2));
    return true;
}

}  // namespace uking::ai
