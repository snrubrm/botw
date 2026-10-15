#include "Game/Actor/Action/actionChuchuPreAttack.h"
#include <prim/seadFormatPrint.h>
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

ChuchuPreAttack::ChuchuPreAttack(const InitArg& arg) : GelJumpBase(arg) {}

ChuchuPreAttack::~ChuchuPreAttack() = default;

bool ChuchuPreAttack::init_(sead::Heap* heap) {
    return GelJumpBase::init_(heap);
}

void ChuchuPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GelJumpBase::enter_(params);
    _168 = false;
    setDamageCallbackTiming(mActor, 4, &_140);
    if (!mSubAS_s.isEmpty())
        playAS(mSubAS_s.cstr(), false, 0, *mSubASSlot_s, -1.0f);
}

void ChuchuPreAttack::leave_() {
    sub_71005DA114(mActor, &_140);
    if (!mLeaveSubAS_s.isEmpty())
        playAS(mLeaveSubAS_s.cstr(), true, 0, *mSubASSlot_s, -1.0f);
    GelJumpBase::leave_();
}

void ChuchuPreAttack::loadParams_() {
    GelJumpBase::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mPosReduceRatioByDamage_s, "PosReduceRatioByDamage");
    getStaticParam(&mDamageAS_s, "DamageAS");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
    getStaticParam(&mDamageSubAS_s, "DamageSubAS");
}

void ChuchuPreAttack::m32(u32 index) {
    sead::FixedSafeString<32> key;
    (sead::StringCutOffPrintFormatter(&key) << "PreJumpAttack%d", index) << sead::flush;
    ksys::eft::searchAndEmitSLink(mActor, key.cstr(), false);
}

// NON_MATCHING: damage-type tests become a bitset and force-selection tails merge.
void ChuchuPreAttack::calc_() {
    auto* controller = mActor->getCharacterController();
    if (_168) {
        if (isFinishedAS(0, 0) || isBgGroundHit(mActor, false)) {
            playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
            if (!mSubAS_s.isEmpty())
                playAS(mSubAS_s.cstr(), false, 0, *mSubASSlot_s, -1.0f);
            _168 = false;
        }
        if (controller)
            sub_7100737C0C(controller, *mPosReduceRatioByDamage_s, controller->get7c());
    } else {
        GelJumpBase::calc_();
    }
    if (isFinished() || isFailed())
        return;
    auto* actor = mActor;
    auto* damage = sub_710072BA90(actor);
    if (!damage)
        return;
    const s32 type = damage->getField54();
    if (!controller || (type != 5 && u32(type - 1) >= 2))
        return;
    sead::Vector3f direction;
    sub_71005E2318(&direction, mActor, damage);
    damage = sub_710072BA90(mActor);
    const f32* force = mHitImpactForceSmallSwordS_s;
    if (damage) {
        switch (damage->getField50()) {
        case 1:
            force = sub_7100736B68(damage->getField54()) ? mHitImpactForceLargeSwordL_s :
                                                               mHitImpactForceLargeSwordS_s;
            break;
        case 2:
            force = sub_7100736B68(damage->getField54()) ? mHitImpactForceSpearL_s :
                                                               mHitImpactForceSpearS_s;
            break;
        default:
            if (sub_7100736B68(damage->getField54()))
                force = mHitImpactForceSmallSwordL_s;
            break;
        }
    }
    sead::Vector3f velocity;
    sub_71005E22D4(&velocity, actor, direction, *force);
    sead::Vector3f knockback = velocity;
    const f32 speed = knockback.normalize();
    sub_710073770C(controller, speed, knockback);
    _168 = true;
    playAS(mDamageAS_s.cstr(), false, 0, 0, -1.0f);
    if (!mDamageSubAS_s.isEmpty())
        playAS(mDamageSubAS_s.cstr(), false, 0, *mSubASSlot_s, -1.0f);
}

}  // namespace uking::action
