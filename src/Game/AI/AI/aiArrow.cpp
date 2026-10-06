#include "Game/AI/AI/aiArrow.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

Arrow::Arrow(const InitArg& arg)
    : ksys::act::ai::Ai(arg), _f0(), _110(), _130(), _150(), _170(), _190() {}

Arrow::~Arrow() {
    _f0.fadeXLink();
    _110.fadeXLink();
    _130.fadeXLink();
    _150.fadeXLink();
    sub_7100463940();
}

void Arrow::sub_7100463940() {
    if (_170.sub_7101241AD8(0))
        xlink::fade(_170.mELink, -1);
}

void Arrow::sub_71004682CC() {
    if (_170.sub_7101241AD8(0))
        xlink::kill(_170.mELink);
}

bool Arrow::sub_71004692FC() {
    if (!_198.hasProc())
        return false;
    ksys::act::acc::WeaponBase weapon;
    ksys::act::acquireActor(&_198, &weapon);
    if (sub_71002F0154(weapon)) {
        bool is_player;
        {
            ksys::act::ActorConstDataAccess parent;
            weapon.acquireParentActor(&parent);
            is_player = parent.isPlayerProfile();
        }
        if (is_player)
            return true;
    }
    return false;
}

bool Arrow::sub_7100467D20() {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor))
        return weapon->_d54 == 1;
    return false;
}

bool Arrow::sub_7100467E24() {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor))
        return weapon->_d54 == 2;
    return false;
}

bool Arrow::sub_7100467F28() {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor))
        return weapon->_e50 & 0x1000;
    return false;
}

bool Arrow::sub_710046757C() {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor))
        return (weapon->_af8._0 | 1) == 7;
    return false;
}

s32 Arrow::sub_710046ABA8() {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor))
        return weapon->_d0c;
    return 1;
}

bool Arrow::sub_710046ACA4(ksys::act::BaseProcLink* out) {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor))
        return weapon->sub_71002EE7E8(out);
    return false;
}

void Arrow::sub_7100469850() {
    _6c = ksys::Timer(10, 10);
    if (auto* body = mActor->getMainBody()) {
        body->setContactLayerAndGroundHit(ksys::phys::ContactLayer::EntitySmallObject,
                                          ksys::phys::GroundHit::HitAll);
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        body->updateCollidableQualityType(false);
    }
    if (auto* chemicals = mActor->getChemicalContainer())
        chemicals->sub_7100E39614(false);
    if (auto* chemicals = mActor->getChemicalContainer()) {
        if (auto* element = chemicals->sub_7100E3718C(0))
            element->_30 &= ~0x200;
    }
    changeChild("跳ね返る");
}

bool Arrow::init_(sead::Heap* heap) {
    spawnElectricWaterBall();
    return true;
}

void Arrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool Arrow::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void Arrow::leave_() {
    if (_1a8.isAllocatedOrFailed())
        _1a8.deleteProc();
    sub_7100463940();
}

void Arrow::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mStickTime_s, "StickTime");
    getStaticParam(&mGroundHitTime_s, "GroundHitTime");
    getStaticParam(&mKillFireTime_s, "KillFireTime");
}

void Arrow::spawnElectricWaterBall() {
    if (_b9 || _1a8.isAllocatedOrFailed())
        return;

    auto* chemical = mActor->sub_71011D8A44(0);
    if (!chemical)
        return;

    if (!(((chemical->mMaterial->attribute.ref() & 0x108) == 0x108 && !(chemical->_be & 4)) ||
          chemical->_1b8 > 0.0f))
        return;

    ksys::act::InstParamPack pack;
    pack->add(0, "AttackPower");
    pack->add(1.0f, "ScaleTime");
    pack->add(0.0f, "Range");
    ksys::act::ActorCreator::addScale(pack, 1.0f);
    pack->addResourceLane(2);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "ElectricWaterBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_1a8, &pack,
        nullptr, 2);
}

void Arrow::m37() {
    _150.fadeXLink();
    _130.fadeXLink();
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c0 != 4)
            chemical->sub_7100D909A4();
    }
    sub_7100463940();
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2c, false);
    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, true);
    changeChild("爆発");
}

void Arrow::m40(ksys::act::BaseProc* proc) {
    sub_71004682CC();
    proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

bool Arrow::m38() {
    auto* chemical = mActor->getChemicalStuff();
    if (!chemical)
        return false;
    return chemical->mMaterial->attribute.ref() & 0x10;
}

void Arrow::m39() {
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D90FF0(false);
}

}  // namespace uking::ai
