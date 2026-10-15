#include "Game/Actor/AI/aiWeaponEquipedAI.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMini.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMiniWeapon.h"
#include "Game/Actor/actModelMaterialUtil.h"

namespace uking::ai {

WeaponEquipedAI::WeaponEquipedAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponEquipedAI::~WeaponEquipedAI() {
    sub_7100E1DC50();
}

void WeaponEquipedAI::sub_7100E1DC50() {
    if (_40.getEvent() && _40.getEvent()->getCreateId() == u32(_40.getCreateId()) &&
        !_40.getEvent()->getBitFlag().isOnBit(4)) {
        xlink::fade(_40, -1);
    }
}

// NON_MATCHING: initial state value stores are merged and use a different base register.
void WeaponEquipedAI::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m153())
        sub_7100E1C850();
    else
        sub_7100E1CB40();
    _39 = false;
    weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m195()) {
        sub_7100E1CE30(false);
        sub_7100E1D1DC();
    }
    weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    _3c = -1;
    if (weapon && weapon->isParentPlayer())
        _3c = 0;
    _38 = false;
}

void WeaponEquipedAI::sub_7100E1C850() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!weapon)
        return;
    sub_7100E1D7A8();
    auto* current_weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!current_weapon || !current_weapon->m213()) {
        if (auto* chemical = mActor->sub_71011D8A44(0))
            chemical->sub_7100D90AF4(false);
    }
    current_weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!current_weapon || !current_weapon->m213()) {
        if (auto* chemical = mActor->sub_71011D8A44(0))
            chemical->_bf |= 2;
    }
    sub_7100E1DB34(ksys::phys::ContactLayer::EntityHitOnlyWater,
                   ksys::phys::ContactLayer::SensorHitOnlyInDoor);
    ksys::act::ai::InlineParamPack pack;
    pack.addString(weapon->m164(), "NodeName", -1);
    sead::Vector3f rotation;
    weapon->m165(&rotation);
    pack.addVec3(rotation, "RotOffset", -1);
    sead::Vector3f translation;
    weapon->m166(&translation);
    pack.addVec3(translation, "TransOffset", -1);
    changeChild("納刀", &pack);
}

void WeaponEquipedAI::sub_7100E1CB40() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!weapon)
        return;
    sub_7100E1DB34(ksys::phys::ContactLayer::EntityHitOnlyWater,
                   ksys::phys::ContactLayer::SensorChemical);
    auto* current_weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!current_weapon || !current_weapon->m213()) {
        if (auto* chemical = mActor->sub_71011D8A44(0))
            chemical->_bf &= ~2;
    }
    if (auto* chemical = mActor->sub_71011D8A44(0)) {
        chemical->sub_7100D91098(false);
        chemical->sub_7100D90C2C(false);
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addString(weapon->m164(), "NodeName", -1);
    sead::SafeString node_name = sead::SafeString::cEmptyString;
    weapon->m197(&node_name);
    pack.addString(node_name, "MyNodeName", -1);
    sead::Vector3f rotation;
    weapon->m165(&rotation);
    pack.addVec3(rotation, "RotOffset", -1);
    sead::Vector3f translation;
    weapon->m166(&translation);
    pack.addVec3(translation, "TransOffset", -1);
    changeChild("抜刀", &pack);
}

void WeaponEquipedAI::sub_7100E1CE30(bool visible) {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!weapon || !weapon->getModel())
        return;
    auto* model = weapon->getModel();
    const auto* params = weapon->getParam()->getRes().mGParamList->getGuardianMiniWeapon();
    if (!params)
        return;
    const sead::SafeString materials = params->mVisibleOffMatName.ref();
    if (!materials.isEmpty()) {
        for (auto it = materials.tokenBegin(","); materials.tokenEnd(",") != it; ++it) {
            sead::FixedSafeString<32> material;
            it.get(&material);
            if (!material.isEmpty()) {
                const auto key = model->searchMaterial(material);
                if (key.isValid())
                    uking::act::setMaterialVisible(model, key, visible);
            }
        }
    }
    _39 = !visible;
}

void WeaponEquipedAI::sub_7100E1D1DC() {
    if (!mActor || !mActor->getASList() ||
        !mActor->getASList()->sub_710115AA68("ChangeColor"))
        return;
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!weapon)
        return;
    auto* parent = weapon->getParentActor();
    if (!parent)
        return;
    const auto* params = parent->getParam()->getRes().mGParamList->getGuardianMini();
    if (!params)
        return;
    auto* as_list = weapon->getASList();
    if (!as_list)
        return;
    as_list->startAnimationMaybe(-1.0f, -1.0f, "ChangeColor", 0, 1, true);
    as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_7101163298,
                 static_cast<f32>(params->mColorType.ref()));
    as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_7101163100, 0.0f);
}

void WeaponEquipedAI::leave_() {
    if (_39)
        sub_7100E1CE30(true);
    xlink::kill(_40);
    sub_7100E1E024();
    if (_38) {
        sub_7100E1DB34(ksys::phys::ContactLayer::EntityHitOnlyWater,
                       ksys::phys::ContactLayer::SensorChemical);
        ksys::act::sub_7100EE544C(mActor);
        if (auto* physics = mActor->getPhysics())
            physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
        if (auto* xlink = mActor->getXLink())
            xlink->_cc.reset(0x800);
        _38 = false;
    }
}

// 0x7100e1e024
void WeaponEquipedAI::sub_7100E1E024() {
    if (_50.getEvent() && _50.getEvent()->getCreateId() == u32(_50.getCreateId()) &&
        !_50.getEvent()->getBitFlag().isOnBit(4)) {
        xlink::fade(_50, -1);
    }
}

// 0x7100e1e104
void WeaponEquipedAI::sub_7100E1E104() {
    sead::SafeString name;
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m233()) {
        name = "SpearAttack";
        _50 = ksys::eft::searchAndEmitELink(mActor, name.cstr());
    }
}

// 0x7100e1d7a8
void WeaponEquipedAI::sub_7100E1D7A8() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m213())
        return;
    if (auto* chemical = mActor->sub_71011D8A44(0)) {
        chemical->sub_7100D8EEE0();
        mActor->getRootAi()->setChemicalFlags3cMaybe(1, false);
        chemical->sub_7100D90C2C(true);
    }
}

// 0x7100e1db34
void WeaponEquipedAI::sub_7100E1DB34(ksys::phys::ContactLayer main_layer, ksys::phys::ContactLayer chemical_layer) {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m213())
        return;
    if (auto* body = mActor->getMainBody())
        body->setContactLayerAndGroundHit(main_layer, ksys::phys::GroundHit::HitAll);
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("Chemical")) {
            if (auto* chemical_body = set->getRigidBodies().at(0))
                chemical_body->setContactLayerAndGroundHit(chemical_layer, ksys::phys::GroundHit::HitAll);
        }
    }
}

}  // namespace uking::ai
