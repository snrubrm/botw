#include "Game/AI/Action/actionAnmBlownOff.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <cfloat>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"

namespace uking::action {

AnmBlownOff::AnmBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmBlownOff::~AnmBlownOff() = default;

bool AnmBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original keeps `dir` below `velocity` in the stack frame (we put the later local first)
void AnmBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mAS_s.isEmpty())
        playAS(mAS_s.cstr(), false, 0, 0, -1.0f);
    sead::Vector3f dir(0.0f, 0.0f, 1.0f);
    auto* manager = sub_710072BA90(mActor);
    f32 speed_scale = 1.0f;
    if (manager) {
        speed_scale = manager->sub_71006D8DE8();
        if (*mUseKnockbackDir_s)
            manager->m30(&dir);
        else
            manager->m29(&dir);
    }
    _a0 = false;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mBlownHeight_s);
        sub_710072C1B4(controller, dir);
        sub_7100737708(controller, speed_scale * *mSpeed_s);
        if (controller->sub_7100F5F14C()) {
            _a0 = true;
            _9c = 2.0f;
        }
    }
    if (*mIsItemDrop_s) {
        auto* actor = mActor;
        sead::Vector3f velocity;
        sub_7100094B38(&velocity);
        const s32* life = actor->getLife();
        const s32 current_life = life ? *life : 1;
        if (current_life > actor->getParam()->getRes().mGParamList->getEnemy()->mDropLife.ref())
            playerOrEnemyDropAllWeapons(actor, velocity);
        else
            m33(velocity);
    }
    _90 = ksys::Timer(*mOnGroundTime_s, *mOnGroundTime_s);
}

void AnmBlownOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmBlownOff::loadParams_() {
    getStaticParam(&mOnGroundTime_s, "OnGroundTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mBlownHeight_s, "BlownHeight");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mIsFinishByAnm_s, "IsFinishByAnm");
    getStaticParam(&mIsWaitForAnmEnd_s, "IsWaitForAnmEnd");
    getStaticParam(&mIsItemDrop_s, "IsItemDrop");
    getStaticParam(&mIsFinishByWater_s, "IsFinishByWater");
    getStaticParam(&mUseKnockbackDir_s, "UseKnockbackDir");
    getStaticParam(&mAS_s, "AS");
}

void AnmBlownOff::calc_() {
    if (*mIsFinishByAnm_s && isFinishedAS(0, 0)) {
        setFinished();
        return;
    }
    auto* actor = mActor;
    if (*mIsFinishByWater_s && actor->getVelocity().y < 0.0f && actor->get68f()) {
        auto* controller = actor->getCharacterController();
        if (!controller || !controller->mFlags.isOnBit(0))
            setFinished();
        return;
    }
    if (auto* controller = actor->getCharacterController()) {
        if (controller->sub_7100F5F14C()) {
            if (_a0) {
                ksys::Timer::update(&_9c, -1.0f);
                if (_9c <= 0.0f)
                    _a0 = false;
            } else {
                _90.update();
                if (_90.value <= FLT_EPSILON && (!*mIsWaitForAnmEnd_s || isFinishedAS(0, 0)))
                    setFinished();
            }
        } else {
            _a0 = false;
        }
        sub_7100737C0C(controller, *mPosReduceRatio_s, -sead::Vector3f::ey);
        m32(controller);
    }
    _a0 = false;
}

// NON_MATCHING: the original stores out->x = 0 before computing the address of out->y (scheduling only)
void AnmBlownOff::sub_7100094B38(sead::Vector3f* out) {
    auto* actor = mActor;
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor)) {
        const f32 speed = *mWeaponDropSpeedXZ_s;
        if (!(speed <= FLT_EPSILON && speed >= -FLT_EPSILON)) {
            dynamic_actor->sub_71006DD908(out);
            out->y = 0.0f;
            const f32 xz_speed = *mWeaponDropSpeedXZ_s;
            const f32 length = out->length();
            if (length > 0.0f)
                *out *= xz_speed / length;
            out->y = *mWeaponDropSpeedY_s;
            return;
        }
    }
    out->x = 0.0f;
    out->z = 0.0f;
    out->y = *mWeaponDropSpeedY_s;
}

void AnmBlownOff::m32(ksys::phys::CharacterController* controller) {
    sub_7100738660(controller, *mRotReduceRatio_s);
}

void AnmBlownOff::m33(const sead::Vector3f& velocity) {
    sub_71005D8748(mActor, velocity, true, false, nullptr, false);
}

}  // namespace uking::action
