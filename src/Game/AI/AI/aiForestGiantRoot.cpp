#include "Game/AI/AI/aiForestGiantRoot.h"
#include <prim/seadFormatPrint.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: register allocation only: the original keeps the two vtable addresses of _538 / _548 in x8 / x9
// and stores them after the second float; ours reuses x8.
ForestGiantRoot::ForestGiantRoot(const InitArg& arg) : EnemyRoot(arg) {}

ForestGiantRoot::~ForestGiantRoot() {
    deleteWeakPoints();
}

// NON_MATCHING: stack layout only: the original puts the name string at sp+8 and the formatter / accessor slot at
// sp+0x30; ours has them the other way round (same code otherwise).
void ForestGiantRoot::deleteWeakPoints() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<16> name;
        for (u32 i = 0; i < 4; ++i) {
            (sead::StringCutOffPrintFormatter(&name) << "WeakPoint%d", i) << sead::flush;
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            enemy->sub_7100D3CFEC(name);
        }
    }
}

bool ForestGiantRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void ForestGiantRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void ForestGiantRoot::m37() {
    bool is_sleep;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e84.isOnBit(8))
        is_sleep = true;
    else
        is_sleep = sub_71005DD798(mActor, 19, nullptr, 0, 0);

    ksys::act::ai::InlineParamPack params;
    params.addBool(is_sleep, "IsSleep", -1);
    changeChild("リアクション", &params);
}

void ForestGiantRoot::leave_() {
    _230.sub_7100706C3C();
    EnemyRoot::leave_();
}

bool ForestGiantRoot::handleMessage_(const ksys::Message* message) {
    if (_230.sub_7100707224(message))
        return true;
    return EnemyRoot::handleMessage_(message);
}

bool ForestGiantRoot::handleAck_(const ksys::MessageAck* ack) {
    return _230.sub_71007073D0(ack);
}

// NON_MATCHING: register allocation only: the original computes &mIsDamageToEnemy_s into x20 before the fourth
// WeakPointNode getStaticParam call (x20 holds the formatter output pointer until then).
void ForestGiantRoot::loadParams_() {
    EnemyRoot::loadParams_();
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 4; ++i) {
        (sead::StringCutOffPrintFormatter(&key) << "WeakPointNode%d", i) << sead::flush;
        getStaticParam(&mWeakPointNode_s[i], key);
    }
    getStaticParam(&mIsDamageToEnemy_s, "IsDamageToEnemy");
    getAITreeVariable(&mIgnoreGiantArmorCondition_a, "IgnoreGiantArmorCondition");
    getAITreeVariable(&mGiantNecklaceUnit_a, "GiantNecklaceUnit");
    _230.sub_7100706E98(this);
}

}  // namespace uking::ai
