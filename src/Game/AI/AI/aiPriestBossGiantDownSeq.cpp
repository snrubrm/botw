#include "Game/AI/AI/aiPriestBossGiantDownSeq.h"
#include "Game/AI/aiUnk_710071E0D8.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossGiantDownSeq::PriestBossGiantDownSeq(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossGiantDownSeq::~PriestBossGiantDownSeq() = default;

bool PriestBossGiantDownSeq::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossGiantDownSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

// NON_MATCHING: the original retains an unused enum read between the lock and payload stores.
void PriestBossGiantDownSeq::leave_() {
    PriestBossMode::leave_();
    if (!_104 || _105 || !sub_7100505BE4())
        return;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_80._18.mLock);
        _80._18._c = false;
        _80._18._8 = 1;
    }
    _80.sub_710070DBB0(sub_7100505BE4()->_1a0, false);
}

void PriestBossGiantDownSeq::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mRecoverIfAlreadyDown_s, "RecoverIfAlreadyDown");
    getStaticParam(&mIsUseRecover_s, "IsUseRecover");
    getStaticParam(&mHitGroundASName_s, "HitGroundASName");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
}



// NON_MATCHING: the original recomputes `sp + 8` (the accessor) for the destructor call; ours keeps it in x19
void PriestBossGiantDownSeq::sub_7100519264() {
    _b0.x();
    auto* unit = sub_7100505BE4();
    ksys::act::ActorConstDataAccess accessor;
    if (unit->sub_71007194CC(&accessor)) {
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_80._18.mLock);
            _80._18._c = false;
            _80._18._8 = 5;
        }
        _80.sub_710070DD78(accessor, true);
    }
}

void PriestBossGiantDownSeq::calc_() {
    PriestBossMode::calc_();
    if (isFinished() || isFailed())
        return;

    if (_b0._30)
        sub_7100519264();

    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    if (isCurrentChild("空中")) {
        if (mActor->getASList()->x(0x38, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            sub_710071E0D8(false, mActor);
            *mIsActive_a = false;
            changeChild("落下");
        }
    } else if (isCurrentChild("落下")) {
        if (mActor->getCharacterController()->sub_7100F5F14C())
            changeChild("ダウン");
    } else if (isCurrentChild("ダウン")) {
        if (child->isFinished()) {
            if (*mIsUseRecover_s)
                changeChild("復帰");
            else
                setFinished();
        }
    } else if (isCurrentChild("復帰")) {
        if (mActor->getASList()->x(0x44, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            sub_710071E0D8(true, mActor);
            *mIsActive_a = true;
            *mDestinationPos_a = _f8;
        }
        if (child->isFinished() || child->isFailed())
            setFinished();
    }
}

bool PriestBossGiantDownSeq::handleMessage_(const ksys::Message* message) {
    if (!_b0._30 && _b0.m2(*message))
        return true;
    return false;
}

bool PriestBossGiantDownSeq::handleAck_(const ksys::MessageAck* ack) {
    if (!_80.sub_710070E070(*ack))
        return false;
    _105 = true;
    return true;
}

}  // namespace uking::ai
