#include "Game/AI/AI/aiEnemyDemoSumonRecgTgt.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::ai {

EnemyDemoSumonRecgTgt::EnemyDemoSumonRecgTgt(const InitArg& arg) : EnemyRecognizeTargetBase(arg) {}

EnemyDemoSumonRecgTgt::~EnemyDemoSumonRecgTgt() = default;

bool EnemyDemoSumonRecgTgt::init_(sead::Heap* heap) {
    return EnemyRecognizeTargetBase::init_(heap);
}

void EnemyDemoSumonRecgTgt::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRecognizeTargetBase::enter_(params);
}

void EnemyDemoSumonRecgTgt::calc_() {
    EnemyRecognizeTargetBase::calc_();
}

void EnemyDemoSumonRecgTgt::leave_() {
    EnemyRecognizeTargetBase::leave_();
}

void EnemyDemoSumonRecgTgt::loadParams_() {
    EnemyRecognizeTargetBase::loadParams_();
    getStaticParam(&mOnlyOne_s, "OnlyOne");
    getStaticParam(&mIsBroadCastOnlyOne_s, "IsBroadCastOnlyOne");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mEntryPoint_s, "EntryPoint");
}

bool EnemyDemoSumonRecgTgt::m34() {
    if (!*mOnlyOne_s)
        return true;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        return !enemy->_e84.isOnBit(9);
    return false;
}

bool EnemyDemoSumonRecgTgt::m35() {
    if (*mOnlyOne_s) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e84.set(0x200);
        if (*mIsBroadCastOnlyOne_s)
            sub_71005E02E0(mActor, &_158, nullptr);
    }
    ksys::evt::Metadata metadata(mDemoName_s.cstr(), mEntryPoint_s.cstr(), "");
    mActor->emitBasicSigOn();
    return true;
}

}  // namespace uking::ai
