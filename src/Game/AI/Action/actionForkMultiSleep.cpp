#include "Game/AI/Action/actionForkMultiSleep.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

ForkMultiSleep::ForkMultiSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkMultiSleep::~ForkMultiSleep() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> key;
        for (s32 i = 0; i < *mNum_s; ++i) {
            key.format("%s%d", mPartsBaseName_s.cstr(), i);
            enemy->sub_7100D3CFEC(key);
        }
    }
}

bool ForkMultiSleep::init_(sead::Heap* heap) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> key;
        for (s32 i = 0; i < *mNum_s; ++i) {
            key.format("%s%d", mPartsBaseName_s.cstr(), i);
            enemy->sub_7100D3CED8(key, heap);
        }
    }
    return true;
}

void ForkMultiSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> key;
        for (s32 i = 0; i < *mNum_s; ++i) {
            key.format("%s%d", mPartsBaseName_s.cstr(), i);
            auto& link = enemy->getActorPartsActor(key.cstr());
            if (link.hasProcInCalcState()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            }
        }
    }
    setFinished();
}

void ForkMultiSleep::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkMultiSleep::loadParams_() {
    getStaticParam(&mNum_s, "Num");
    getStaticParam(&mPartsBaseName_s, "PartsBaseName");
}

void ForkMultiSleep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
