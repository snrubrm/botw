#include "Game/AI/Action/actionExpandChemicalField.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

ExpandChemicalField::ExpandChemicalField(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandChemicalField::~ExpandChemicalField() = default;

bool ExpandChemicalField::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ExpandChemicalField::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* lod = actor->getLodState()) {
        lod->mFlags10.setBit(6);
        if (*mIsReuseActor_m)
            actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    }
    if (auto* chemical = actor->getChemicalStuff()) {
        chemical->sub_7100D91098(true);
        if (*mIsUseAtCollision_m)
            chemical->_c |= 0x20;
    }
    _7c = actor->getScale().x;
    const f32 scale_time = *mScaleTime_m;
    if (scale_time > 1.0f) {
        _78 = actor->getScale().x / scale_time;
        actor->setScale(sead::Vector3f::ones * _78);
    } else {
        _78 = 0.0f;
    }
    if (*mIsUseAtCollision_m) {
        const s32 type = *mAttackType_m == 0 ? 0x8000 : *mAttackType_m;
        const s32 attr = *mAttackAttr_m;
        sub_71007A2C9C(actor);
        getActorAttackSensor(actor)->activateAttackSensor(
            type, attr, *mAttackPower_m,
            actor->getParam()->getRes().mGParamList->getAttack()->mImpulse.ref(), 0.0f, 0, 1,
            *mAttackDirType_m, false, 0, -1);
        const s32 target = *mAttackTarget_m;
        if (target >= 0) {
            if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Atk().cstr())) {
                const s32 count = set->getRigidBodies().size();
                const auto layer = target == 2 ? ksys::phys::ContactLayer::SensorAttackPlayer :
                                   target == 1 ? ksys::phys::ContactLayer::SensorAttackEnemy :
                                                 ksys::phys::ContactLayer::SensorAttackCommon;
                for (s32 i = 0; i < count; ++i) {
                    if (auto* body = set->getRigidBody(i))
                        body->setContactLayerAndHandler(layer, nullptr);
                }
            }
        }
    }
    if (!mXLinkKey_m.isEmpty())
        xlinkSearchAndEmit(actor, mXLinkKey_m.cstr(), 2, &_80);
}

void ExpandChemicalField::leave_() {
    if (*mIsUseAtCollision_m)
        sub_71007A2E04(mActor);
    if (auto* lod = mActor->getLodState()) {
        lod->mFlags10.resetBit(6);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
    }
    xlink::fadeIfLoopEffect(_80.mELink);
    xlink::fadeIfLoopSound(_80.mSLink);
}

void ExpandChemicalField::loadParams_() {
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackAttr_m, "AttackAttr");
    getMapUnitParam(&mAttackType_m, "AttackType");
    getMapUnitParam(&mCutGrassType_m, "CutGrassType");
    getMapUnitParam(&mAttackTarget_m, "AttackTarget");
    getMapUnitParam(&mAttackDirType_m, "AttackDirType");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mIsReuseActor_m, "IsReuseActor");
    getMapUnitParam(&mIsUseAtCollision_m, "IsUseAtCollision");
    getMapUnitParam(&mXLinkKey_m, "XLinkKey");
}

void ExpandChemicalField::sub_7100129760() {
    if (*mIsReuseActor_m) {
        auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor);
        auto* link = bullet ? &bullet->_bd0._0 : &mActor->getCreateArgBaseProcLink();
        if (link->hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            if (!accessor.isDeletedOrDeleting()) {
                mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
                return;
            }
        }
    }
    mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

void ExpandChemicalField::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
