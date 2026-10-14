#include "Game/Actor/AI/aiStalPartRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/aiUnk_71006F5B14.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"

namespace uking::ai {

void Unk_7102424d70::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (*a1 >= 1 && *a4 != 3) {
        *a1 = 0;
        *a5 = -1;
        *a4 = -1;
    }
}

StalPartRoot::StalPartRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartRoot::~StalPartRoot() = default;

bool StalPartRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        _90 = enemy->_e90;
        if (auto* self = sead::DynamicCast<act::Enemy>(mActor))
            self->_e90 = 3;
        sub_71007A3540(enemy);
        sub_71007A3800(enemy);
        sub_710073DE44(enemy);
    }
    const f32 time = *mInvincibleTime_s;
    if (time > 0) {
        _94.reset(time);
        sub_71005A8A8C(true);
    }
    mFlags.set(Flag::Changeable);
    changeChild("通常");
}

void StalPartRoot::calc_() {
    if (!(*mInvincibleTime_s > 0) || _94.value <= sead::Mathf::epsilon())
        return;

    auto* chemical = mActor->getChemicalStuff();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (auto* unit = enemy->m159()) {
            for (int i = 0; i < 12; ++i)
                unit->m13(i);
        }
    }
    if (chemical)
        chemical->sub_7100D8EEE0();
    _94.update();
    if (_94.value <= sead::Mathf::epsilon()) {
        sub_71005A8A8C(false);
        return;
    }
    if (chemical && (chemical->_8 & 2))
        sub_71006F5940(chemical);
}

void StalPartRoot::leave_() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        enemy->_e90 = 3;
    ksys::act::disableAllAttClients(actor);
    sub_71005A8A8C(false);
    actor->resetConnectedCalcParent(false);
    sub_71005DC5DC(actor);
}

void StalPartRoot::loadParams_() {
    getStaticParam(&mInvincibleTime_s, "InvincibleTime");
}

bool StalPartRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        sub_71005A8A8C(false);
    return false;
}

void StalPartRoot::sub_71005A8A8C(bool enable) {
    if (_a0 == enable)
        return;

    auto* actor = mActor;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    auto* body = actor->getMainBody();
    if (enemy) {
        auto* unit = enemy->m159();
        if (enable) {
            setDamageCallbackTiming(enemy, 4, &_38);
            setDamageCallbackTiming(enemy, 5, &_60);
            sub_71006F5940(enemy->getChemicalStuff());
            if (body) {
                body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
                body->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
            }
            if (unit)
                unit->sub_71006DFA04(true);
        } else {
            sub_71005DA114(enemy, &_38);
            sub_71005DA114(enemy, &_60);
            if (auto* chemical = enemy->getChemicalStuff()) {
                sub_71006F5A80(chemical);
                chemical->sub_7100D8EEE0();
            }
            if (body) {
                body->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
                body->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
            }
            if (unit) {
                unit->sub_71006DFA04(false);
                for (int i = 0; i < 12; ++i)
                    unit->m13(i);
            }
            _94.reset(-1.0f);
        }
    }
    _a0 = enable;
}

}  // namespace uking::ai
