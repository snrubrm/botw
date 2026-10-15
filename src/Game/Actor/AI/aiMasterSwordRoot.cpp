#include "Game/Actor/AI/aiMasterSwordRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"

namespace uking::ai {

MasterSwordRoot::MasterSwordRoot(const InitArg& arg) : WeaponRootAI(arg) {}

MasterSwordRoot::~MasterSwordRoot() = default;

bool MasterSwordRoot::init_(sead::Heap* heap) {
    *static_cast<Unk_71025afb58**>(mMagicCreateUnit_a) = &_f8;
    return WeaponRootAI::init_(heap);
}

void MasterSwordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004A3410();
    if (_e8) {
        sub_7100E21228();
        _e8 = false;
        return;
    }
    WeaponRootAI::enter_(params);
}

// NON_MATCHING: the original copies Vector3f::zero to a stack temporary before each addVec3 (two
// named `const sead::Vector3f` copies reproduce it exactly; not applied, see lane1 log s65).
void MasterSwordRoot::sub_71004A3AFC() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    sub_7100E1EE94(ksys::phys::MotionType(2));
    ksys::act::ai::InlineParamPack params;
    params.addString(weapon->m164(), "NodeName", -1);
    params.addVec3(sead::Vector3f::zero, "RotOffset", -1);
    params.addVec3(sead::Vector3f::zero, "TransOffset", -1);
    changeChild("マスターソードチャレンジ", &params);
}

void MasterSwordRoot::leave_() {
    if (_f8._8.isAllocatedOrFailed())
        _f8._8.deleteProc();
    WeaponRootAI::leave_();
}

void MasterSwordRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

// NON_MATCHING: the range parameter offset is split between pointer selection and the load.
void MasterSwordRoot::sub_71004A3410() {
    _f8._8.deleteProc();
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    const auto* rod = weapon->getParam()->getRes().mGParamList->getRod();
    if (!rod || rod->mMagicName.ref().isEmpty())
        return;
    const s32* scale_time_param;
    const f32* scale_param;
    const f32* range_param;
    const char* body_name;
    if (weapon->m142()) {
        scale_time_param = &rod->mScaleTimeByEnemy.ref();
        scale_param = &rod->mMagicRadiusByEnemy.ref();
        range_param = &rod->mMagicRangeByEnemy.ref();
        body_name = "AtkEnemyBody";
    } else {
        scale_time_param = &rod->mScaleTime.ref();
        scale_param = &rod->mMagicRadius.ref();
        range_param = &rod->mMagicRange.ref();
        body_name = "AtkPlayerBody";
    }
    const s32 scale_time = *scale_time_param;
    const f32 scale = *scale_param;
    const f32 range = *range_param;
    const s32 attack_power = rod->mMagicPower.ref();
    ksys::act::InstParamPack pack;
    pack->addPosition(weapon->getMtx().getTranslation());
    pack->add(attack_power, "AttackPower");
    pack->add(static_cast<f32>(scale_time), "ScaleTime");
    pack->add(range, "Range");
    ksys::act::ActorCreator::addScale(pack, scale);
    pack->add(sead::SafeString(body_name), "RigidBodyName");
    u32 flags;
    if ((weapon->_af8._0 | 1) == 7)
        flags = weapon->_af8._4;
    else if (weapon->_d08)
        flags = weapon->_cf4;
    else
        flags = weapon->_c20._4;
    pack->add((flags & 0x40000000) != 0, "AttackAttrEventKill");
    pack->addResourceLane(2);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        rod->mMagicName.ref().cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &_f8._8, &pack, nullptr, 2);
}

void MasterSwordRoot::calc_() {
    if (isCurrentChild("Fixed配置")) {
        auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        if (weapon && weapon->m185() && weapon->m187()) {
            auto* sword = static_cast<act::Weapon*>(mActor);
            // The original repeats this RTTI query and discards its result after validating the actor.
            const auto* type_info = act::Weapon::getRuntimeTypeInfoStatic();
            sword->checkDerivedRuntimeTypeInfo(type_info);
            if (sword->m198())
                sub_71004A3AFC();
            else
                sword->set920(0xff);
            return;
        }
    } else if (isCurrentChild("マスターソードチャレンジ")) {
        auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        if (weapon) {
            auto* fixed = sead::DynamicCast<act::Weapon>(mActor);
            if (fixed && fixed->m190()) {
                weapon->m199();
                sead::Matrix34f home;
                weapon->getHomeMtx(&home);
                weapon->getMainBody()->setTransform(home, ksys::phys::PropagateToLinkedMotions{true});
                sub_7100E1F710();
                return;
            }
            auto* carried = sead::DynamicCast<act::Weapon>(mActor);
            if (carried && carried->sub_71002ECDC0()) {
                weapon->_925 = false;
                _e8 = true;
                sub_7100E1F34C();
                return;
            }
        }
    }
    if (_f8._8.hasProcCreationFailed() || !_f8._8.isAllocatedOrFailed()) {
        if (_f8._8.hasProcCreationFailed())
            _f8._8.deleteProcIfFailed();
        sub_71004A3410();
    }
    WeaponRootAI::calc_();
}

}  // namespace uking::ai
