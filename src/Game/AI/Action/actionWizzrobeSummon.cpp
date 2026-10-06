#include "Game/AI/Action/actionWizzrobeSummon.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

WizzrobeSummon::WizzrobeSummon(const InitArg& arg) : TurnIgnite(arg) {}

// NON_MATCHING: the original inlines TurnIgnite's destructor (vtable stores + ParamPack dtor) into D1; with
// `~TurnIgnite() = default` in its header the vtable D1 slot of TurnIgnite folds into OnetimeStopASPlay's D2.
WizzrobeSummon::~WizzrobeSummon() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<64> name;
        for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
            name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
            enemy->sub_7100D3CFEC(name);
        }
    }
}

bool WizzrobeSummon::init_(sead::Heap* heap) {
    if (!TurnIgnite::init_(heap))
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    sead::FixedSafeString<64> name;
    for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
        name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
        if (!enemy->sub_7100D3CED8(name, heap))
            return false;
    }
    return true;
}

void WizzrobeSummon::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnIgnite::enter_(params);
}

void WizzrobeSummon::leave_() {
    TurnIgnite::leave_();
}

void WizzrobeSummon::loadParams_() {
    TurnIgnite::loadParams_();
    getStaticParam(&mSummonBufferSize_s, "SummonBufferSize");
    getStaticParam(&mWeaponIndex_s, "WeaponIndex");
    getStaticParam(&mSummonBufferKey_s, "SummonBufferKey");
    getAITreeVariable(&mSummonCount_a, "SummonCount");
}

void WizzrobeSummon::m32(ksys::act::BaseProcHandle* handle) {
    if (handle) {
        auto* proc = handle->getProc();
        if (auto* summoned = sead::DynamicCast<ksys::act::Actor>(proc)) {
            auto* actor = mActor;
            sub_7100738C88(summoned, actor);
            sub_7100738D28(summoned, actor);
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                sead::FixedSafeString<64> name;
                for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
                    name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
                    if (!enemy->getActorPartsActor(name).hasProc() &&
                        enemy->sub_7100D3D108(name, proc))
                        break;
                }
            }
        }
        *mSummonCount_a += 1;
    }
    StopASIgnite::m32(handle);
}

const sead::Matrix34f& WizzrobeSummon::m33() {
    sub_71002BEDDC();
    return _f8;
}

void WizzrobeSummon::calc_() {
    TurnIgnite::calc_();
}

}  // namespace uking::action
