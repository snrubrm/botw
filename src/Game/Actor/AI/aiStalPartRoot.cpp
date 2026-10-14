#include "Game/Actor/AI/aiStalPartRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

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

}  // namespace uking::ai
