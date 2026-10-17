#include "Game/Actor/actNPC.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Mii/miiNetfp.h"
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Mii/miiUMii.h"

namespace uking::act {

// 0x7100d2d424 (unnamed in the CSV): unregisters the damage callbacks and frees the callback table.
void sub_7100D2D424(uking::act::DamageManagerBase* manager);
// 0x7100e97d8c (unnamed in the CSV): frees the object returned by NPC::m119 (phantoms and the
// physics helper arrays) and runs its deleting destructor.
void sub_7100E97D8C(void* obj);

bool NPC::isGoron(ksys::act::Actor* actor) {
    return actor && actor->getUMii() &&
           *actor->getUMii()->getBody().race == ksys::mii::UMii::Body::Race_Goron;
}

bool NPC::isZora(ksys::act::Actor* actor) {
    return isZora_(actor);
}

ksys::act::BaseProc* NPC::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) NPC(arg);
}

// 0x71025aea70 (placeholder name): the NPC animation-driven speed resource handle.
ksys::res::Handle sUnk_71025AEA70;

// 0x710001c790 (CSV name): loads the shared NPC animation-driven speed table for the GameScene.
void loadAnimationDrivenSpeedNPC() {
    ksys::res::LoadRequest request;
    request.mRequester = "GameNPC";
    request.mLoadCompressed = false;
    sUnk_71025AEA70.load("AnimationDrivenSpeed/NPCSpeed.byml", &request, nullptr);
}

// NON_MATCHING: member types are incomplete
NPC::~NPC() = default;

void NPC::m79() {
    if (sub_7100020F44())
        sub_7100021AB4();
}

bool NPC::startPreparingForPreDelete_() {
    if (!(_fe8 & 0x10000)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_f70, &accessor))
            accessor.deleteEx(DeleteReason::_0);
    } else if (!_f28._18.isAccessingSpecifiedProcUnsafe(_f28.mActor)) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(
            _f28._18.getProc(nullptr, _f28.mActor));
        if (actor)
            actor->deleteEx(DeleteType::_1, DeleteReason::_0, nullptr);
    }
    return Actor::startPreparingForPreDelete_();
}

void NPC::onDeleteRequested_(DeleteReason reason) {
    Actor::onDeleteRequested_(reason);
    getWeapons()->sub_7100EFCC20(DeleteReason(0));
}

void NPC::preDelete2_(const PreDeleteArg& arg) {
    NPCBase::preDelete2_(arg);
    if (_cf8) {
        _cf8->m6();
        delete _cf8;
        _cf8 = nullptr;
    }
    _c78.free();
    sub_7100D2D424(&_da0);
    // called through a pointer in the original (not devirtualised)
    (&_da0)->preDelete1();
    (&_da0)->preDelete2();
    _f88.sub_710091BA3C();
    if (_10b8) {
        operator delete[](static_cast<u8*>(_10b8) - 8);
        _10b8 = nullptr;
        _10b0 = 0;
    }
    if (_10e0) {
        sub_7100E97D8C(_10e0);
        _10e0 = nullptr;
    }
}

bool NPC::m148(s32 idx, Actor* weapon, bool a3, bool a4) {
    return getWeapons()->equipWeapon(idx, weapon, a3, a4);
}

uking::act::DamageManagerBase* NPC::getDamageMgr() {
    return &_da0;
}

void NPC::sub_71000225B0(int idx, const Unk_71002eda38& arg) {
    auto* weapon = sead::DynamicCast<Weapon>(getWeapons()->getEquippedWeapon(idx));
    if (weapon)
        weapon->sub_71002EDA38(arg);
}

void NPC::sub_7100022660(int idx, const Unk_71002edaec& arg) {
    auto* weapon = sead::DynamicCast<Weapon>(getWeapons()->getEquippedWeapon(idx));
    if (weapon)
        weapon->sub_71002EDAEC(arg);
}

bool NPC::sub_71000224F0(int idx, const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5) {
    return getWeapons()->dropWeapon(idx, pos, a2, a3, a4, a5);
}

bool NPC::sub_7100022554(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5) {
    return getWeapons()->dropAllWeapons(pos, a2, a3, a4, a5);
}

void NPC::m149() {
    if (_da0.getField54() == -1)
        return;

    // Discarded calls (results unused in the original).
    _da0.getDamage();
    _da0.getAttackOtherMaterialMask();

    ksys::phys::MaterialMask mask(0x13u);
    if (auto* weapon = sead::DynamicCast<Weapon>(mWeapons.getEquippedWeapon(1)))
        weapon->sub_71002ED4CC(&mask);

    sead::Matrix34f mtx;
    if (_da0.getAttackSourceMtx(&mtx))
        _e30.sub_71006E4478(_da0.getAttacker(), mtx);

    DamageReactionInfo info;
    sub_7100732B28(&info, this);
    info._19 = false;
    info._1a = false;
    info._30 = &mask;
    sub_7100733418(this, &info, &_10e8);
}

bool NPC::sub_71000228F8() {
    for (const auto& weapon : mWeapons.mWeapons) {
        ksys::act::acc::Weapon accessor;
        if (weapon.link.hasProc())
            ksys::act::acquireActor(&weapon.link, &accessor);
        if (accessor.isShield())
            return true;
    }
    return false;
}

bool NPC::sub_7100022B54() {
    if (!(_fe8 & 4))
        return false;
    if (sub_71005DB7E4(this, 0))
        return false;
    return sub_71000228F8();
}

bool NPC::sub_7100022D44(bool on, int mode, const sead::Vector3f& pos,
                         ksys::act::BaseProcLink* link, const sead::Vector3f& pos2) {
    auto* bone_control = getBoneControl();
    if (!bone_control)
        return false;
    auto* obj = bone_control->_0;
    if (!obj)
        return false;

    obj->sub_7100D85774();
    _11c8 = on;
    _11cc = mode;
    _11e0.reset();
    if (mode == 2) {
        if (!link)
            return false;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (!accessor.linkAcquire(&_11e0))
            return false;
    }
    _11d0 = pos;
    _11f0 = pos2;
    return true;
}

bool NPC::sub_7100022E3C(bool on) {
    if (on && _11c8)
        return true;

    auto* bone_control = getBoneControl();
    if (!bone_control)
        return false;
    auto* obj = bone_control->_0;
    if (!obj)
        return false;

    obj->sub_7100D85774();
    _11c8 = on;
    _11cc = 0;
    _11e0.reset();
    _11d0 = sead::Vector3f::zero;
    _11f0 = sead::Vector3f::zero;
    return true;
}

void NPC::onPreDeleteStart_(PrepareArg& arg) {
    NPCBase::onPreDeleteStart_(arg);
}

void NPC::m73() {
    sub_71006E3340(&_10e8, this);
}

void* NPC::m119() {
    return _10e0;
}

void NPC::m117(ksys::act::Unk117* arg) {
    mWeapons.sub_7100EFD458(arg);
    if (_fe8 & 0x10000)
        _f28.sub_7100E7C4F8(arg);
}

Unk_7100d3cd74* NPC::m101() {
    return &_fa8;
}

HorseRideInfo* NPC::getPlayerRideInfo() {
    return &_f28;
}

ksys::act::Unk_71025ae640* NPC::getAtk() {
    return &_c78;
}

ksys::act::Unk_71025b08f8* NPC::m126() {
    return _cf8;
}

}  // namespace uking::act

namespace ksys::act {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

static inline uking::act::NPC* getNPC(BaseProc* proc) {
    auto* actor = static_cast<Actor*>(getProcIfActor(proc));
    return sead::DynamicCast<uking::act::NPC>(actor);
}

bool ActorLinkConstDataAccess::sub_7100022ED8() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_fe8 & 4;
}

bool ActorLinkConstDataAccess::sub_7100022FD0() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_fe8 & 0x2000;
}

bool ActorLinkConstDataAccess::sub_7100023358() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_fe8 & 0x40000;
}

bool ActorLinkConstDataAccess::sub_7100023450() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_1048 == 3;
}

const sead::Vector3f& ActorLinkConstDataAccess::sub_710002354C() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!sead::IsDerivedFrom<uking::act::NPC>(actor))
        return sead::Vector3f::zero;
    return static_cast<uking::act::NPC*>(actor)->_1098;
}

}  // namespace ksys::act

namespace uking::act {
void NPC::m61(f32 rate) {
    sub_71000217F8(rate);
}
}  // namespace uking::act
