#include "Game/AI/AI/aiKokkoRoot.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

// 0x710045746c
void Unk_71023fff70::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 == -1)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(manager->getAttacker(), &accessor);
    if (accessor.getName() == _28) {
        *a1 = 0;
        *a5 = -1;
        auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(
            reinterpret_cast<dmg::DamageCallbackInfo*>(a6));
        if (info)
            info->mFlags = 0;
    }
}

KokkoRoot::KokkoRoot(const InitArg& arg) : PreyRoot(arg) {}

KokkoRoot::~KokkoRoot() = default;

bool KokkoRoot::init_(sead::Heap* heap) {
    return PreyRoot::init_(heap);
}

void KokkoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
    _220 = 0;
    _228.reset();
    _238 = ksys::Timer(-1, -1, 0);
    _248._28 = mAvoidCountActorName_s;
    setDamageCallbackTiming(mActor, 0, &_248);
}

void KokkoRoot::leave_() {
    sub_71005DA114(mActor, &_248);
    PreyRoot::leave_();
}

void KokkoRoot::loadParams_() {
    PreyRoot::loadParams_();
    getStaticParam(&mStartSpecialAttackCount_s, "StartSpecialAttackCount");
    getStaticParam(&mAvoidCountActorName_s, "AvoidCountActorName");
}

void KokkoRoot::m40() {
    if (!isCurrentChild("怒り"))
        PreyRoot::m40();
}

void KokkoRoot::m41() {
    if (!isCurrentChild("怒り"))
        PreyRoot::m41();
}

void KokkoRoot::m43() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("怒り")) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_d70.sub_71002DC32C();
        _220 = 0;
        ksys::act::enableAttClient(mActor, "Grab");
        sub_71005047A8();
    } else {
        PreyRoot::m43();
    }
}

void KokkoRoot::m44() {
    if (sub_7100504EBC(0x40))
        changeToAngry();
    else
        sub_71005047A8();
}

void KokkoRoot::m46() {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(1.0f, "Power", -1);
    pack.addVec3(mActor->getMtx().getBase(2), "TargetDir", -1);
    pack.addBool(false, "IsShootByPlayer", -1);
    changeChild("落下", &pack);
}

void KokkoRoot::sub_7100456DE4(const ksys::act::BaseProcLink& link) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (!enemy->_d70.sub_71002DCCBC(-1))
            enemy->_d70.sub_71002DC32C();
        enemy->_d70.sub_71002DC628(link, 1);
    }
    sub_7100504A9C(0x40, true);
    ksys::gdt::setBoolByKey(true, "Kokko_Event_Running");
    changeToAngry();
}

void KokkoRoot::sub_7100456EEC() {
    if (auto* manager = ksys::evt::Manager::instance()) {
        const ksys::evt::Metadata metadata("Demo013_0");
        if (manager->callEvent(metadata, mActor)) {
            if (auto* controller = mActor->getCharacterController()) {
                controller->sub_7100F5E7F0(0.0f);
                controller->sub_7100F5FB24(sead::Vector3f::zero);
            }
        }
    }
}

void KokkoRoot::changeToAngry() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    ksys::act::disableAttClient(mActor, "Grab");

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("怒り", &pack);
}

}  // namespace uking::ai
