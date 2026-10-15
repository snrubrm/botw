#include "Game/Actor/AI/aiGolemRootBase.h"
#include "Game/Actor/aiUnk_71006F5B14.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGolem.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectChemicalType.h"
#include "KingSystem/Chemical/chmShape.h"
#include <limits>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

GolemRootBase::GolemRootBase(const InitArg& arg) : EnemyRoot(arg) {}

GolemRootBase::~GolemRootBase() {
    sub_71004012F8();
    sub_71004014A4();
    _2f0._8.freeBuffer();
}

// NON_MATCHING: output-slot placement, zero initialization and position-copy stores differ.
void GolemRootBase::sub_7100402194() {
    if (sub_71006F5694(mActor) != Unk_71006F5DB0::Normal)
        return;

    u32 texture = 0;
    if (mGolemTextureName_m.isEmpty()) {
        u32 value = 255;
        auto* stats = StatisticsMgr::instance()->getStatsPointer("rock_distribution");
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        if (!StatisticsMgr::instance()->sub_7100E33EA0(&value, 1, stats, &position) || value == 255)
            return;
        texture = value;
    } else if (!ksys::tera::sub_710110C1E4(&texture, mGolemTextureName_m)) {
        return;
    }

    if (auto* model = mActor->getModel())
        Unk_710260af28::instance()->sub_7100F1E4DC(model, static_cast<f32>(texture));
    xlinkEventOn(mActor, 25, s32(texture), false);
    auto* parts = mActor->m101();
    if (!parts)
        return;

    {
        auto& link = parts->getActorPartsActor(mUpperArmL_PartsKey_s);
        ksys::act::acc::Bullet accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.startXLinkEvent19Maybe(texture, mActor);
    }
    {
        auto& link = parts->getActorPartsActor(mLowerArmL_PartsKey_s);
        ksys::act::acc::Bullet accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.startXLinkEvent19Maybe(texture, mActor);
    }
    {
        auto& link = parts->getActorPartsActor(mUpperArmR_PartsKey_s);
        ksys::act::acc::Bullet accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.startXLinkEvent19Maybe(texture, mActor);
    }
    {
        auto& link = parts->getActorPartsActor(mLowerArmR_PartsKey_s);
        ksys::act::acc::Bullet accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.startXLinkEvent19Maybe(texture, mActor);
    }
}

void GolemRootBase::sub_71004012F8() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    {
        auto& link = enemy->_1128.getActorPartsActor(mUpperArmL_PartsKey_s);
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(mUpperArmL_PartsKey_s);
    }

    {
        auto& link = enemy->_1128.getActorPartsActor(mLowerArmL_PartsKey_s);
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(mLowerArmL_PartsKey_s);
    }

    {
        auto& link = enemy->_1128.getActorPartsActor(mUpperArmR_PartsKey_s);
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(mUpperArmR_PartsKey_s);
    }

    {
        auto& link = enemy->_1128.getActorPartsActor(mLowerArmR_PartsKey_s);
        ksys::act::ActorLinkConstDataAccess accessor;
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
    ksys::act::ActorLinkConstDataAccess accessor;
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

// NON_MATCHING: entry initialization, shader-name copies and chemical snapshot scheduling differ.
bool GolemRootBase::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;
    const Unk_71006F5DB0 element = sub_71006F5694(mActor);
    if (!sub_7100401A14(heap) && !sub_71005D6D10())
        return false;
    if (!sub_7100401D68(heap) && !sub_71005D6D10())
        return false;
    auto* chemicals = mActor->getChemicalContainer();
    if (!chemicals || element == Unk_71006F5DB0::Normal)
        return true;
    const s32 count = chemicals->_58.size() + chemicals->_80;
    if (count > 0)
        _2f0._8.tryAllocBuffer(count, heap);
    if (!_2f0._8.getBufferPtr())
        return false;
    sub_71006F5D3C(element, mActor);
    for (s32 i = 0; i < _2f0._8.size(); ++i) {
        auto* chemical = chemicals->sub_7100E37788(i);
        if (!chemical)
            continue;
        sead::SafeString active = mBodyActiveAS_s;
        sead::SafeString deactive = mBodyDeactiveAS_s;
        sead::SafeString mimic = mBodyMimicAS_s;
        s32 bank = *mBodyShaderSeqBank_s;
        s32 part = 0;
        const auto& name = chemical->mShape->getName();
        if (name.findIndex("ArmR") != -1) {
            active = mArmRActiveAS_s;
            deactive = mArmRDeactiveAS_s;
            bank = *mArmRShaderSeqBank_s;
            mimic = mArmRMimicAS_s;
            part = 1;
        } else if (name.findIndex("ArmL") != -1) {
            active = mArmLActiveAS_s;
            deactive = mArmLDeactiveAS_s;
            bank = *mArmLShaderSeqBank_s;
            mimic = mArmLMimicAS_s;
            part = 2;
        }
        auto& entry = _2f0._8[i];
        entry.mActor = mActor;
        entry.mChemical = chemicals->sub_7100E37788(i);
        entry.mElement = element;
        entry._a8 = part;
        entry._30 = active;
        entry._40 = deactive;
        entry._50 = mimic;
        entry.mASSlot = *mShaderASTargetBone_s;
        entry.mASBank = bank;
        entry._b5 = mActor->getParam()->getRes().mGParamList->getGolem()->mIsDefaultChemicalOn.ref();
        entry.sub_7100708B64();
        _2f0._8[i]._1c = 300.0f;
    }
    *static_cast<Unk_71025afb58**>(mGolemChemicalController_a) = &_2f0;
    return true;
}

// NON_MATCHING: part-name dispatch, parameter-pack temporaries and creator scheduling differ.
bool GolemRootBase::sub_7100401A14(sead::Heap* heap) {
    auto* parts = mActor->m101();
    if (!parts)
        return true;
    sead::Vector3f position = mActor->getMtx().getTranslation();
    position.y += 1.0f;
    const sead::SafeString* keys[] = {&mUpperArmL_PartsKey_s, &mLowerArmL_PartsKey_s,
                                    &mUpperArmR_PartsKey_s, &mLowerArmR_PartsKey_s};
    for (s32 i = 0; i < 4; ++i) {
        const auto* golem = mActor->getParam()->getRes().mGParamList->getGolem();
        const sead::SafeString* name = &sead::SafeString::cEmptyString;
        switch (i) {
        case 0:
            name = &golem->mUpperArmLActor.ref();
            break;
        case 1:
            name = &golem->mLowerArmLActor.ref();
            break;
        case 2:
            name = &golem->mUpperArmRActor.ref();
            break;
        case 3:
            name = &golem->mLowerArmRActor.ref();
            break;
        }
        const auto& key = *keys[i];
        if (name->isEmpty()) {
            if (!key.isEmpty())
                return false;
            continue;
        }
        if (key.isEmpty() || !parts->sub_7100D3CED8(key, heap))
            return false;
        ksys::act::InstParamPack pack;
        pack.getBuffer().addPosition(position);
        ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
        auto* created = ksys::act::ActorCreator::instance()->createActor(
            name->cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true, false);
        if (!created) {
            if (!sub_71005D6D10())
                return false;
            continue;
        }
        if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(created)) {
            bullet->sub_710000497C(mActor);
            bullet->sub_71000048BC(mActor);
            bullet->_bd0._0.acquire(mActor, false);
        }
        created->setDeleteDistance(std::numeric_limits<f32>::infinity());
        sub_7100738C88(created, mActor);
        sub_7100738D28(created, mActor);
        parts->sub_7100D3D108(key, created);
    }
    return true;
}

// NON_MATCHING: actor creation and parameter-pack lifetimes use different scheduling.
bool GolemRootBase::sub_7100401D68(sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    const auto* params = mActor->getParam()->getRes().mGParamList->getChemicalType();
    const auto& name = params ? params->mEmitChemicalActor.ref() : sead::SafeString::cEmptyString;
    if (!enemy || name.isEmpty())
        return true;
    if (!enemy->sub_7100D3CED8(mChemicalFieldKey_s, heap))
        return false;
    ksys::act::InstParamPack pack;
    pack.getBuffer().addMatrix(enemy->getMtx());
    ksys::act::ActorCreator::addScale(pack, 10.0f);
    pack.getBuffer().add(10.0f, "ScaleTime");
    pack.getBuffer().add(true, "IsReuseActor");
    auto* created = ksys::act::ActorCreator::instance()->createActor(
        name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true, false);
    if (!created)
        return sub_71005D6D10();
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(created)) {
        bullet->sub_710000497C(mActor);
        bullet->sub_71000048BC(mActor);
        bullet->_bd0._0.acquire(mActor, false);
    }
    enemy->sub_7100D3D108(mChemicalFieldKey_s, created);
    return true;
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

void GolemRootBase::calc_() {
    if (!mActor->isSpecialJobTypesMaskOverride0())
        sub_7100402194();
    for (int i = 0; i < _2f0._8.size(); ++i)
        _2f0._8[i].sub_71007083DC();
    EnemyRoot::calc_();
    ksys::act::Reaction::instance()->sub_7100EC29D0(mActor);
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
