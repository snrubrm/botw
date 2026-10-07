#include "Game/AI/Action/actionRemainsElectricWeakPointWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/GameData/gdtManagerInline.h"

namespace uking::action {

RemainsElectricWeakPointWait::RemainsElectricWeakPointWait(const InitArg& arg)
    : ksys::act::ai::Action(arg), _58(mActor) {}

RemainsElectricWeakPointWait::~RemainsElectricWeakPointWait() = default;

bool RemainsElectricWeakPointWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsElectricWeakPointWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsElectricWeakPointWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsElectricWeakPointWait::loadParams_() {}

void RemainsElectricWeakPointWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

// NON_MATCHING: output pointer registers and the equivalent life-test branch form differ.
void Unk_71023b3310::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                         uking::dmg::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;
    if (*a4 == 4) {
        if (auto* manager = ksys::gdt::Manager::instance()) {
            bool battle = false;
            ksys::gdt::getBoolByNameNoBool2(manager, &battle, "Electric_Relic_Battle");
            if (!battle) {
                *a1 = 0;
                *a2 = 0;
                *a3 = 0;
                *a4 = -1;
                *a5 = -1;
                return;
            }
        }
        auto* actor = mDamageManager->mActor;
        if (!actor)
            return;
        auto* life = actor->getLife();
        if (!life || *life > 0) {
            auto* entry = sub_71007A255C(actor, 0);
            if (!entry)
                return;
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&entry->_e8, &accessor);
            const auto& name = accessor.getName();
            if (name == "BombArrow_A") {
                *a1 = 1;
                *a2 = 0;
                *a3 = 0;
            } else {
                *a1 = 0;
                *a2 = 0;
                *a3 = 0;
                *a4 = -1;
                *a5 = -1;
            }
            return;
        }
    }
    *a1 = 0;
    *a4 = -1;
    *a5 = -1;
}
