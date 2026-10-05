#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include <basis/seadNew.h>
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/gameRoot38.h"

namespace ksys::act {

void DynamicActor::m160() {
    Actor::x_2();
}

void DynamicActor::m76(VFR::ScopedDeltaSetter* setter) {
    if (mActorFlags2.isOn(ActorFlag2::_200))
        sub_7100EE9B68(this, setter);
    if (auto* object = m159()) {
        object->_a = mActorFlags2.isOn(ActorFlag2::_40) ? object->_a | 2 : object->_a & ~2;
        object->m6();
    }
    if (auto* chemical = getChemicalStuff()) {
        chemical->_c = (_a68 & 2) ? chemical->_c | 0x800000 : chemical->_c & ~0x800000;
    }
    _a68 &= ~2;
    if (_a50)
        _a50->m6();
    if (auto* damage = sead::DynamicCast<uking::dmg::DamageManagerBase>(mDamageMgr))
        damage->m43();
    m160();
    if (mChemical && mChemical->sub_7100E39458() && _a60)
        _a60->_c |= 4;
    if (hasTag(this, tags::RotMoveFollowPreCalc) && getModel()) {
        sead::Matrix34f home;
        getHomeMtx(&home);
        getModel()->setMatrix(home);
    }
}

BaseProc* DynamicActor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) DynamicActor(arg);
}

BaseProc::IsSpecialJobTypeResult DynamicActor::isSpecialJobType_(JobType type) {
    if (mActorFlags2.isOn(ActorFlag2::_200) && uking::Root38::instance()->testFlag(2))
        return IsSpecialJobTypeResult::Yes;
    return Actor::isSpecialJobType_(type);
}

void DynamicActor::onDeleteRequested_(DeleteReason reason) {
    Actor::onDeleteRequested_(reason);
    if (_a50)
        _a50->sub_71006E4668();
}

void DynamicActor::onSleepRequested_(SleepWakeReason reason) {
    Actor::onSleepRequested_(reason);
    if (_a50)
        _a50->sub_71006E4668();
}

bool DynamicActor::m157(sead::Heap* heap) {
    if (!sub_71006D28AC(this))
        return true;
    mDamageMgr = gameObjectInitField(this, heap);
    return mDamageMgr != nullptr;
}

bool DynamicActor::constructActorAtk(sead::Heap* heap) {
    if (!actorHasTgtBody(this))
        return true;
    _850 = ActorAtk::makeForActor(this, heap);
    return _850 != nullptr;
}

bool DynamicActor::initField858(sead::Heap* heap) {
    if (!getCharacterController()) {
        auto* body = getMainBody();
        if (!body || !body->getContactPointInfo())
            return true;
    }
    _858 = new (heap, 8) Unk_7102459df8(this);
    return _858 != nullptr;
}

bool DynamicActor::initField868(sead::Heap* heap) {
    if (!getRagdollInstance())
        return true;
    _868 = new (heap, 8) Unk_71006ecc78(this);
    if (!_868)
        return false;
    return _868->sub_71006ECC78(heap);
}

// NON_MATCHING: most member types are still unknown (placeholders)
DynamicActor::~DynamicActor() = default;

void DynamicActor::onPreDeleteStart_(PrepareArg&) {}

void DynamicActor::m156() {
    const s32 max_life = getMaxLife();
    if (s32* life = getLife())
        *life = max_life;
}

int DynamicActor::getExtraHeapSize() {
    return hasTag(this, tags::TreasureBox) ? 0xa90 : 0;
}

void DynamicActor::onEnterDelete_() {
    Actor::onEnterDelete_();
}

void DynamicActor::sub_71006DD92C(bool enable) {
    if (!_868)
        return;
    if (enable)
        _868->sub_71006EDD5C();
    else
        _868->sub_71006EDCB8();
}

s32* DynamicActor::getLife() {
    return &mLife;
}

uking::dmg::DamageManagerBase* DynamicActor::getDamageMgr() {
    return mDamageMgr;
}

Unk_71025ae640* DynamicActor::getAtk() {
    return _850;
}

Actor* DynamicActor::m48() {
    return nullptr;
}

Unk_7100e4e084* DynamicActor::m100() {
    return &_870;
}

Actor::Unk3* DynamicActor::m135() {
    return &_a78;
}

Unk_71006e45c4* DynamicActor::m128() {
    return _a50;
}

Unk_71025b08f8* DynamicActor::m126() {
    return _858;
}

Unk_71025ae620* DynamicActor::getDropData() {
    return _a60;
}

}  // namespace ksys::act

namespace ksys::act {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

bool ActorConstDataAccess::sub_71006DE298(const sead::SafeString& name) const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!actor)
        return false;
    return actorAIGetBool(actor, name, false);
}

bool ActorConstDataAccess::sub_71006DE338(const sead::SafeString& name) const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!actor)
        return false;
    return getBoolParam(actor, name, false);
}

bool ActorConstDataAccess::sub_71006E3E00() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!actor)
        return false;
    return actorAIGetBool(actor, "IsEnemyLiftable", true);
}

bool ActorConstDataAccess::sub_71006E3FB4() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    auto* dynamic_actor = sead::DynamicCast<DynamicActor>(actor);
    if (!dynamic_actor)
        return false;
    return dynamic_actor->_a69 != 0;
}

bool ActorConstDataAccess::isBgGroundHit() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!actor)
        return false;
    debugLog(1, "isBgGroundHit");
    debugLog(2, "isBgGroundHit");
    return ::isBgGroundHit(actor, false);
}

void Unk_71006e4478::sub_71006E4478(BaseProcLink* link, const sead::Matrix34f& mtx) {
    _0 = *link;
    _10 = mtx;
    ActorConstDataAccess accessor;
    acquireActor(&_0, &accessor);
    _4c = accessor.getPreviousPos2();
    _5d = false;
    if (hasTag(link, tags::Arrow)) {
        sead::Vector3f translation;
        _10.getTranslation(translation);
        _10.setTranslation(translation - accessor.getVelocity());
        _4c -= accessor.getVelocity();
        _5d = true;
    }
    _40 = accessor.getVelocity();
    _5c = false;
}

void DynamicActor::m36(const sead::Vector3f& a1, const sead::Vector3f& a2, bool a3, bool a4,
                       bool a5) {
    if (_a70) {
        Unk_71006dc134 request{a1, a2, nullptr, false, false};
        _a70->invoke(&request);
        sub_71011D8718(request._0, request._c, request._20, request._21, a4, -1, a3, a5);
    } else {
        sub_71011D8718(a1, a2, false, false, a4, -1, a3, a5);
    }
}

Actor* DynamicActor::m31() {
    if (mActorFlags2.isOn(ActorFlag2::_40000000))
        return sead::DynamicCast<Actor>(getConnectedCalcParent());
    if (_a80.hasProc())
        return sead::DynamicCast<Actor>(_a80.getProc(nullptr, nullptr));
    return Actor::m31();
}

bool DynamicActor::m53() {
    if (auto* unit = m159())
        return unit->m9();
    return false;
}

void DynamicActor::m73() {
    if (auto* a = m159())
        a->m7();
    if (_a50)
        _a50->m8();
    if (auto* mgr = getDamageMgr()) {
        if (mgr->getField54() == 0x22)
            sendMessage(*mMsgTransceiver.getId(), MessageType(0x3000004), nullptr, true);
    }
}

void DynamicActor::sub_71006DD908(sead::Vector3f* out) {
    if (_868)
        _868->sub_71006EE128(out);
}

}  // namespace ksys::act

namespace ksys::act {

void DynamicActor::sub_71006DC81C() {
    if (_850) {
        _850->free();
        delete _850;
        _850 = nullptr;
    }
}

void DynamicActor::sub_71006DC864() {
    if (_868) {
        _868->sub_71006ECD08();
        delete _868;
        _868 = nullptr;
    }
}

}  // namespace ksys::act
