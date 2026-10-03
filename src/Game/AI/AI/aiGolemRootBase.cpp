#include "Game/AI/AI/aiGolemRootBase.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

GolemRootBase::GolemRootBase(const InitArg& arg) : EnemyRoot(arg) {}

GolemRootBase::~GolemRootBase() {
    sub_71004012F8();
    sub_71004014A4();
    _2f0._8.freeBuffer();
}

void GolemRootBase::sub_71004012F8() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    {
        auto& link = enemy->_1128.getActorPartsActor(mUpperArmL_PartsKey_s);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(mUpperArmL_PartsKey_s);
    }

    {
        auto& link = enemy->_1128.getActorPartsActor(mLowerArmL_PartsKey_s);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(mLowerArmL_PartsKey_s);
    }

    {
        auto& link = enemy->_1128.getActorPartsActor(mUpperArmR_PartsKey_s);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(mUpperArmR_PartsKey_s);
    }

    {
        auto& link = enemy->_1128.getActorPartsActor(mLowerArmR_PartsKey_s);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(mLowerArmR_PartsKey_s);
    }
}

void GolemRootBase::sub_71004014A4() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor(mChemicalFieldKey_s);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    enemy->sub_7100D3CFEC(mChemicalFieldKey_s);
}

void GolemRootBase::m38() {
    EnemyRoot::m38();
}

bool GolemRootBase::m35() {
    if (EnemyRoot::m35())
        return true;
    if (!_2f0._18.isOnBit(0) && sub_71007090F4(&_2f0))
        return true;
    return false;
}

bool GolemRootBase::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void GolemRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor))
        static_cast<act::Enemy*>(actor)->_a68 &= ~1;

    EnemyRoot::enter_(params);
    sub_71006F5D3C(sub_71006F5694(mActor), mActor);
}

void GolemRootBase::leave_() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor))
        static_cast<act::Enemy*>(actor)->_a68 |= 1;

    if (auto* body = mActor->getRigidBodyByName(sub_71007A250C()->cstr())) {
        for (int i = 0, n = body->getRigidBodies().size(); i < n; ++i) {
            auto* rigid_body = body->getRigidBody(i);
            if (rigid_body->isAddedToWorld())
                rigid_body->removeFromWorld();
        }
    }
    EnemyRoot::leave_();
}

void GolemRootBase::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mShaderASTargetBone_s, "ShaderASTargetBone");
    getStaticParam(&mBodyShaderSeqBank_s, "BodyShaderSeqBank");
    getStaticParam(&mArmRShaderSeqBank_s, "ArmRShaderSeqBank");
    getStaticParam(&mArmLShaderSeqBank_s, "ArmLShaderSeqBank");
    getStaticParam(&mUpperArmL_PartsKey_s, "UpperArmL_PartsKey");
    getStaticParam(&mLowerArmL_PartsKey_s, "LowerArmL_PartsKey");
    getStaticParam(&mUpperArmR_PartsKey_s, "UpperArmR_PartsKey");
    getStaticParam(&mLowerArmR_PartsKey_s, "LowerArmR_PartsKey");
    getStaticParam(&mChemicalFieldKey_s, "ChemicalFieldKey");
    getStaticParam(&mBodyDeactiveAS_s, "BodyDeactiveAS");
    getStaticParam(&mArmRDeactiveAS_s, "ArmRDeactiveAS");
    getStaticParam(&mArmLDeactiveAS_s, "ArmLDeactiveAS");
    getStaticParam(&mBodyActiveAS_s, "BodyActiveAS");
    getStaticParam(&mArmRActiveAS_s, "ArmRActiveAS");
    getStaticParam(&mArmLActiveAS_s, "ArmLActiveAS");
    getStaticParam(&mBodyMimicAS_s, "BodyMimicAS");
    getStaticParam(&mArmRMimicAS_s, "ArmRMimicAS");
    getStaticParam(&mArmLMimicAS_s, "ArmLMimicAS");
    getMapUnitParam(&mGolemTextureName_m, "GolemTextureName");
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemRootBase::m37() {
    EnemyRoot::m37();
}

}  // namespace uking::ai
