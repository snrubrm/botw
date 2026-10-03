#include "Game/AI/AI/aiEnemyVacuumBombSelectBase.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

EnemyVacuumBombSelectBase::EnemyVacuumBombSelectBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyVacuumBombSelectBase::~EnemyVacuumBombSelectBase() { ; }

bool EnemyVacuumBombSelectBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyVacuumBombSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71003C3198())
        changeChild("所持", params);
    else
        changeChild("非所持", params);
}

bool EnemyVacuumBombSelectBase::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyVacuumBombSelectBase::isFinished() const {
    return getCurrentChild()->isFinished();
}

void EnemyVacuumBombSelectBase::calc_() {}

void EnemyVacuumBombSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

bool EnemyVacuumBombSelectBase::m34(ksys::act::BaseProcLink* link) {
    return false;
}

void EnemyVacuumBombSelectBase::loadParams_() {
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x7100b0ce00
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
}

bool EnemyVacuumBombSelectBase::sub_71003C3198() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    for (auto& key : mPartsKey_s) {
        if (!key.isEmpty()) {
            auto& link = enemy->getActorPartsActor(key);
            if (m34(&link))
                return true;
        }
    }
    return false;
}

}  // namespace uking::ai
