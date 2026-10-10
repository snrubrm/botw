#include "Game/AI/Action/actionGolemThrowPartsToTargetBase.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_7102450410.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

GolemThrowPartsToTargetBase::GolemThrowPartsToTargetBase(const InitArg& arg) : ActionWithAS(arg) {}

GolemThrowPartsToTargetBase::~GolemThrowPartsToTargetBase() = default;

bool GolemThrowPartsToTargetBase::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemThrowPartsToTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    setDamageCallbackTiming(mActor, 4, &_f0);
    mFlags.reset(Flag::Changeable);
}

void GolemThrowPartsToTargetBase::leave_() {
    sub_710018D8DC();
    sub_71005DA114(mActor, &_f0);
    ActionWithPosAngReduce::leave_();
}

void GolemThrowPartsToTargetBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    _60.sub_71005E1BE8(this, 0);
    _a0.sub_71005E1BE8(this, 1);
    _e0 = false;
    _e1 = false;
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemThrowPartsToTargetBase::calc_() {
    ActionWithAS::calc_();
    sub_710018D8DC();
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
            sub_710018D998();
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

// NON_MATCHING: the original tests the three out/in pointers with cset/and (non-short-circuit) and only body with cbz; the natural short-circuit form branches per pointer.
void GolemThrowPartsToTargetBase::m32(sead::Vector3f* linear_velocity,
                                      sead::Vector3f* angular_velocity, sead::Matrix34f* mtx,
                                      ksys::phys::RigidBody* body) {
    if (body && linear_velocity && angular_velocity && mtx) {
        body->getTransform(mtx);
        *angular_velocity = body->getAngularVelocity() * (1.0f / 30.0f);
        *linear_velocity = body->getLinearVelocity() * (1.0f / 30.0f);
    }
}

// NON_MATCHING: the compiler reloads the empty-string byte for each part instead of sharing it.
void GolemThrowPartsToTargetBase::sub_710018D8DC() {
    if (_e0) {
        _e0 = false;
        if (!_60._30.isEmpty()) {
            sub_7100725960(mActor, _60._30, false);
            sub_71007259CC(mActor, _60._30, false);
        }
    }
    if (_e1) {
        _e1 = false;
        if (!_a0._30.isEmpty()) {
            sub_7100725960(mActor, _a0._30, false);
            sub_71007259CC(mActor, _a0._30, false);
        }
    }
}

void GolemThrowPartsToTargetBase::sub_710018D998() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    bool burning = false;
    bool ice = false;
    if (auto* chemical = enemy->sub_71011D8A54(mChmObjectName_s)) {
        burning = chemical->_c0 == 2;
        ice = !(chemical->_bf & 2) && (chemical->mMaterial->attribute.ref() & 0x8000);
        if (auto* controller = sead::DynamicCast<Unk_7102450410>(*mGolemChemicalController_a)) {
            if (auto* entry = controller->sub_7100708E90(chemical))
                entry->sub_7100708A0C();
        }
    }
    if (auto* instance = enemy->getPhysics()) {
        if (instance->getRagdollInstance()) {
            sub_710018DC70(enemy, _60, burning, ice);
            _e0 = true;
            sub_710018DC70(enemy, _a0, burning, ice);
            _e1 = true;
        }
        if (auto* body = instance->findX(*sub_71007A24D0(), mTgtBodyName_s))
            body->setContactLayer(ksys::phys::ContactLayer::SensorNoHit);
    }
}

// NON_MATCHING: local matrix and velocity stack slots differ.
void GolemThrowPartsToTargetBase::sub_710018DC70(act::Enemy* enemy,
                                               const Unk_71005e1be8& part, bool burning, bool ice) {
    const auto& link = enemy->_1128.getActorPartsActor(part._0);
    if (!link.hasProc())
        return;

    ksys::act::acc::Bullet accessor;
    ksys::act::acquireActor(&link, &accessor);
    if (accessor.isStateSleep()) {
        if (auto* body = enemy->findPhysicsBodyByName(sub_71007A24E4()->cstr(), part._10.cstr())) {
            sead::Vector3f linear_velocity;
            sead::Vector3f angular_velocity;
            sead::Matrix34f matrix;
            m32(&linear_velocity, &angular_velocity, &matrix, body);
            accessor.setGolemPartInitialBurn(burning, enemy);
            accessor.setGolemPartInitialIceMagic(ice, enemy);
            accessor.setProperties(matrix, &linear_velocity, &angular_velocity, nullptr, false, 2, -1);
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
        }
        if (auto* body = enemy->findPhysicsBodyByName(sub_71007A250C()->cstr(), part._20.cstr()))
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
    }
}

}  // namespace uking::action
