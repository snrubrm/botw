#include "Game/Actor/Action/actionFallAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

FallAttack::FallAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FallAttack::~FallAttack() = default;

bool FallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;

    setDamageCallbackTiming(actor, 4, &_60);
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkBodyName_s.cstr()))
        body->setTransform(actor->getMtx());

    sead::Vector3f dir;
    dir.set(controller->get70());
    _58 = dir.normalize();
    dir *= *mGravity_s;
    controller->sub_7100F5EE1C(dir);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

// NON_MATCHING: same calls and arithmetic; the original loads `_58` into a callee-saved register before the sqrt, puts the
// 16-byte direction vector below the Unk_71002edaec request on the stack (frame 0x90, ours 0x80) and keeps four fp registers.
void FallAttack::leave_() {
    auto* actor = mActor;
    sub_71005DA114(actor, &_60);
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;

    sead::Vector3f dir;
    dir.set(controller->get70());
    const f32 length = dir.length();
    if (length > 0.0f)
        dir *= _58 / length;
    controller->sub_7100F5EE1C(dir);
    const uking::act::Unk_71002edaec request(1);
    sub_71005D79AC(actor, *mWeaponIdx_s, request);
    sub_71007A2D7C(actor, mAtkBodyName_s);
    controller->sub_7100F60604();
}

void FallAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAtkBodyName_s, "AtkBodyName");
    getStaticParam(&mJustAvoidDist_s, "JustAvoidDist");
}

// NON_MATCHING: stack slots and the shared attack-sensor activation tail differ.
void FallAttack::calc_() {
    if (sub_71005DAFB0(mActor)) {
        setFailed();
        return;
    }
    auto* actor = mActor;
    sub_71005DAB2C(actor, *mJustAvoidDist_s, *mJustAvoidDist_s, sead::Mathf::pi(), 0);
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(actor, &query, 0, 0)) {
        const u32 flags = m32();
        sub_71005D7ADC(actor, *mWeaponIdx_s, flags, &query.name, nullptr,
                       1, 1, 0, 1, 1.0f, 1.0f);
        auto* weapon = sub_71005D83E8(actor, *mWeaponIdx_s);
        auto* sensor = getActorAttackSensor(actor);
        if (weapon) {
            const u32 type = weapon->sub_71002ECB78();
            const u32 attributes = weapon->getFlags(flags);
            const s32 power = weapon->getEffectiveAttackPower(mActor);
            const u32 impulse_flags = 4;
            const s32 impulse = weapon->sub_71002ECAFC(impulse_flags);
            const u32 guard_flags = 4;
            const s32 guard = weapon->sub_71002ECB3C(guard_flags);
            sensor->activateAttackSensor(type, attributes, power, impulse, 0.0f, guard, 1,
                                         sub_71007A3A8C(&query.name), false, 1, -1);
        } else {
            const u32 attributes = m33();
            s32 power = static_cast<ksys::act::PlayerOrEnemy*>(actor)->getEnemyAtkPower();
            const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
            if (power < 1)
                power = 1;
            const s32 impulse = attack->mImpulseLarge.ref();
            const s32 guard = attack->mGuardBreakPower.ref();
            sensor->activateAttackSensor(0x2000, attributes, power, impulse, 0.0f, guard, 1,
                                         sub_71007A3A8C(&query.name), false, 1, -1);
        }
        sub_71007A2C30(actor, mAtkBodyName_s, nullptr);
    } else if (sub_71005DD74C(actor, nullptr, 0, 0)) {
        const act::Unk_71002edaec request(1);
        sub_71005D79AC(actor, *mWeaponIdx_s, request);
    }
}

int FallAttack::m32() {
    return 12;
}

int FallAttack::m33() {
    return 4;
}

bool FallAttack::isFinished() const {
    return isBgGroundHit(mActor, false);
}

}  // namespace uking::action
