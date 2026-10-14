#include "Game/Actor/AI/aiPriestBossGiantDownSeq.h"
#include "Game/Actor/aiUnk_710071E0D8.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::ai {

PriestBossGiantDownSeq::PriestBossGiantDownSeq(const InitArg& arg) : PriestBoss(arg) {}

PriestBossGiantDownSeq::~PriestBossGiantDownSeq() = default;

bool PriestBossGiantDownSeq::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

// NON_MATCHING: dead SEAD_ENUM stack round trip (value 0) before the mode store, as in PriestBossGiantStageRotate::leave_
void PriestBossGiantDownSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
    _104 = false;
    _105 = false;
    mActor->getMtx().getTranslation(_f8);
    if (auto* unit = sub_7100505BE4()) {
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_80._18.mLock);
            _80._18._c = false;
            _80._18._8 = 1;
        }
        _80.sub_710070DBB0(unit->_1a0, true);
        _104 = true;
    }

    auto* controller = mActor->getCharacterController();
    if (int(controller->sub_7100F5F0E4()) != 3 && *mRecoverIfAlreadyDown_s) {
        *mIsActive_a = false;
        if (controller->sub_7100F5F14C()) {
            if (mActor->getASList()->x_1(0, 0) == mHitGroundASName_s)
                changeChild("ダウン");
            else
                changeChild("復帰");
            return;
        }
    }
    changeChild("空中");
}

// NON_MATCHING: the original retains an unused enum read between the lock and payload stores.
void PriestBossGiantDownSeq::leave_() {
    PriestBoss::leave_();
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
    PriestBoss::loadParams_();
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
    ksys::act::ActorLinkConstDataAccess accessor;
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
    PriestBoss::calc_();
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
