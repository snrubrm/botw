#include "Game/AI/AI/aiBowEquiped.h"
#include "Game/Actor/actWeapon.h"
#include "Game/gameGraphics.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

BowEquiped::BowEquiped(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the shared failure copy differs from native duplicated failure blocks.
void BowEquiped::sub_7100337F48(sead::BufferedSafeString* name, ksys::act::InstParamPack* pack) {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        if (weapon->bowGetArrowName(name)) {
            pack->getBuffer().addDeleteDistanceSq(998001.0f);
            pack->getBuffer().addPosition(weapon->getMtx().getTranslation());
            if (weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200))
                pack->getBuffer().addPlayerControl();
            return;
        }
    }
    name->copy(sead::SafeString::cEmptyString);
}

bool BowEquiped::sub_7100337AA4(ksys::act::BaseProc* proc) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return false;
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(proc);
    if (!bullet)
        return false;
    bullet->sub_710000497C(weapon->getParentActor());
    weapon->setConnectedCalcChild(bullet, true);
    bullet->setMatrix(weapon->getMtx(), nullptr);
    if (weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200)) {
        bullet->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_200);
        if (auto* model = bullet->getModel())
            model->bind(Graphics::instance()->mModelScenes[1]);
        if (auto* lod = bullet->getLodState())
            lod->mFlags26.setBit(0);
    }
    return true;
}

bool BowEquiped::sub_7100337C40() {
    sead::FixedSafeString<32> name;
    ksys::act::InstParamPack pack;
    sub_7100337F48(&name, &pack);
    if (name.isEmpty())
        return false;
    ksys::act::ActorCreator::instance()->requestCreateActor(
        name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_38, &pack, nullptr, 1);
    return true;
}

bool BowEquiped::isChangeable() const {
    return !_38.isAllocatedOrFailed();
}

void BowEquiped::sub_7100337E2C(ksys::phys::ContactLayer first, ksys::phys::ContactLayer second) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (weapon && !weapon->m213()) {
        if (auto* body = mActor->getMainBody())
            body->setContactLayerAndGroundHit(first, ksys::phys::GroundHit::HitAll);
        if (auto* physics = mActor->getPhysics()) {
            if (auto* set = physics->findBodyByName("Chemical")) {
                if (set->getRigidBodies().size() != 0) {
                    if (auto* body = set->getRigidBody(0))
                        body->setContactLayerAndGroundHit(second, ksys::phys::GroundHit::HitAll);
                }
            }
        }
    }
}

void BowEquiped::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getConnectedCalcChild()) {
        sub_7100337E2C(ksys::phys::ContactLayer::EntityHitOnlyWater,
                       ksys::phys::ContactLayer::SensorChemical);
        _48 = false;
        changeChild("射撃");
    } else {
        _48 = false;
        changeChild("装備");
    }
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    _49 = weapon && weapon->m153();
}

void BowEquiped::leave_() {
    if (_38.isAllocatedOrFailed())
        _38.deleteProc();
    if (auto* child = mActor->getConnectedCalcChild())
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor))
        weapon->_e50 &= ~0xc0;
}

void BowEquiped::sub_71003377B8() {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        const bool equipped = weapon->m153();
        if (equipped) {
            if (!_49)
                xlinkSearchAndEmit(mActor, "UnEquip", 2, nullptr);
        } else if (_49) {
            xlinkSearchAndEmit(mActor, "Equip", 2, nullptr);
        }
        _49 = equipped;
    }
}

bool BowEquiped::sub_710033788C() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon || weapon->m188())
        return false;
    if (weapon->_af8._0 == 2)
        return true;
    if (!weapon->isParentPlayer() &&
        !weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200)) {
        return false;
    }
    return weapon->_af8._0 == 3;
}

}  // namespace uking::ai
