#include "Game/AI/AI/aiEnemyVacuumBombSelectBase.h"
#include <prim/seadFormatPrint.h>
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

EnemyVacuumBombSelectBase::EnemyVacuumBombSelectBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
EnemyVacuumBombSelectBase::~EnemyVacuumBombSelectBase() {
    ;
}

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
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 5; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "PartsKey%d", i) << sead::flush;
        getStaticParam(&mPartsKey_s[i], key.cstr());
    }
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
