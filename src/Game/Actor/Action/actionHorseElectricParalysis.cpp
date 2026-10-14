#include "Game/Actor/Action/actionHorseElectricParalysis.h"
#include "Game/Actor/actHorse.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

HorseElectricParalysis::HorseElectricParalysis(const InitArg& arg) : StopBase(arg) {}

HorseElectricParalysis::~HorseElectricParalysis() = default;

bool HorseElectricParalysis::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void HorseElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void HorseElectricParalysis::leave_() {
    StopBase::leave_();
    if (auto* rideable_base = mActor->m132()) {
        rideable_base->_18._52 &= ~8;
        if (auto* rideable = sead::DynamicCast<act::Rideable>(rideable_base)) {
            if (*mCanRiddenWhenLeave_s) {
                const s32* life = mActor->getLife();
                if (!life || *life >= 1) {
                    rideable->sub_7100E8BD80();
                    rideable->Unk_7100e8b2b8::_8 &= ~0x200u;
                }
            }
            rideable->_148 = sead::Vector3f::zero;
        }
    }
    for (int i = 0; i < mActor->getASList()->getSlot0BankCount(); ++i)
        mActor->getASList()->x_3(0, i, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (_70)
        _70->removeFromWorld();
}

void HorseElectricParalysis::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
    getStaticParam(&mCanRiddenWhenLeave_s, "CanRiddenWhenLeave");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mThrowOffAttackRigidBodyName_s, "ThrowOffAttackRigidBodyName");
    getDynamicParam(&mIsEnableThrowOffAttack_d, "IsEnableThrowOffAttack");
}

// NON_MATCHING: &_68 is kept in a callee-saved register here (recomputed before Timer::update in the original).
void HorseElectricParalysis::calc_() {
    StopBase::calc_();
    if (_68 >= *mPauseDelayFrames_s) {
        if (auto* rideable = mActor->m132())
            rideable->_18._52 |= 8;
        for (int i = 0; i < mActor->getASList()->getSlot0BankCount(); ++i)
            mActor->getASList()->x_3(0, i, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
        if (_70 && (_70->isAddedToWorld() || _70->isAddingBodyToWorld()))
            _70->removeFromWorld();
    } else {
        if (_70 && !_70->isAddedToWorld() && !_70->isAddingBodyToWorld())
            _70->addToWorld();
    }
    ksys::Timer::update(&_68, 1.0f);
    if (auto* horse = sead::DynamicCast<act::Horse>(mActor)) {
        if (!horse->_1028._8.isOnBit(4))
            setFinished();
    }
}

}  // namespace uking::action
