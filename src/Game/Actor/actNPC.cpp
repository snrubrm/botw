#include "Game/Actor/actNPC.h"
#include <limits>
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Mii/miiNetfp.h"
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

namespace uking::act {

// 0x7100d2d424 (unnamed in the CSV): unregisters the damage callbacks and frees the callback table.
void sub_7100D2D424(uking::act::DamageManagerBase* manager);
// 0x7100e97d8c (unnamed in the CSV): frees the object returned by NPC::m119 (phantoms and the
// physics helper arrays) and runs its deleting destructor.
void sub_7100E97D8C(void* obj);

// The callers pass the NPC and its target link; namespace scope is inferred.
// NON_MATCHING: the compiler normalizes the inverted result instead of using the native branches.
bool sub_7100713524(const ksys::act::Actor* actor, const ksys::act::BaseProcLink* link) {
    if (!DamageInfoMgr::instance())
        return true;
    return !DamageInfoMgr::sub_71006741E4(link, actor);
}

// NON_MATCHING: the loop reloads its bound and the substring result uses a different comparison.
f32 NPC::sub_7100022B9C(const sead::SafeString& name) const {
    if (mCurveSpeeds.isBufferReady()) {
        for (s32 i = 0; i < mCurveSpeeds.size(); ++i) {
            if (mCurveSpeeds[i].name == name) {
                const f32 speed = mCurveSpeeds[i].speed;
                if (!(speed < std::numeric_limits<f32>::epsilon()))
                    return speed;
                break;
            }
        }
    }
    return name.findIndex("Walk") >= 0 ? 1.309f : 2.356f;
}

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

void NPC::setEquippedWeaponsJobsPaused(bool on) {
    if (auto* weapon = getWeapons()->getEquippedWeapon(0))
        weapon->sub_7100EF91B0(on, true);
    if (auto* weapon = getWeapons()->getEquippedWeapon(1))
        weapon->sub_7100EF91B0(on, true);
    if (auto* weapon = getWeapons()->getEquippedWeapon(2))
        weapon->sub_7100EF91B0(on, true);
    if (auto* weapon = getWeapons()->getEquippedWeapon(3))
        weapon->sub_7100EF91B0(on, true);
    if (auto* weapon = getWeapons()->getEquippedWeapon(4))
        weapon->sub_7100EF91B0(on, true);
    if (auto* weapon = getWeapons()->getEquippedWeapon(5))
        weapon->sub_7100EF91B0(on, true);
}

// NON_MATCHING: the unrolled checks use different branch and boolean accumulation.
bool NPC::sub_7100020F44() {
    bool any = false;
    for (int i = 0; i < 6; ++i) {
        ksys::act::acc::WeaponBase weapon;
        auto& link = getWeapons()->mWeapons[i].link;
        if (!link.hasProc())
            continue;
        ksys::act::acquireActor(&link, &weapon);
        if (!weapon.sub_7100EFB798())
            return false;
        any = true;
    }
    return any;
}

void NPC::sub_7100021AB4() {
    for (int i = 0; i < 6; ++i) {
        ksys::act::acc::WeaponBase weapon;
        auto& link = getWeapons()->mWeapons[i].link;
        if (link.hasProc()) {
            ksys::act::acquireActor(&link, &weapon);
            weapon.sub_7100EFB63C(this, true);
        }
    }
}

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
    mCurveSpeeds.freeBuffer();
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

void NPC::sub_7100020D40() {
    const f32 speed = getVelocity().length();
    if (!(speed <= std::numeric_limits<f32>::epsilon() &&
          speed >= -std::numeric_limits<f32>::epsilon()))
        return;
    auto* awareness = getAwareness();
    if (!awareness)
        return;
    Unk_71024516a0 filter;
    ksys::act::ActorLinkConstDataAccess accessor;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (entry->_a8 < 1.0f) {
            ksys::act::acquireActor(&entry->_0.mLink, &accessor);
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000be), nullptr,
                        true);
        }
    }
}

bool NPC::sub_7100020E78() {
    for (s32 i = 0; i < 6; ++i) {
        ksys::act::acc::WeaponBase weapon;
        auto& link = getWeapons()->mWeapons[i].link;
        if (link.hasProc()) {
            ksys::act::acquireActor(&link, &weapon);
            if (!getParam()->getRes().mGParamList->getNpc()->mIsOffPodFromWeapon.ref() &&
                weapon.sub_7100EFA6B8())
                return true;
        }
    }
    return false;
}

bool NPC::sub_7100021178() {
    for (s32 i = 0; i < 6; ++i) {
        if (auto* weapon = getWeapons()->getEquippedWeapon(i)) {
            const f32 value = weapon->m139();
            if (value > 0.0f && value < 1.0f)
                return true;
        }
    }
    return false;
}

// NON_MATCHING: the compiler shares the failure paths and uses fewer saved registers.
bool NPC::sub_71000212F4() {
    bool has_weapon = false;
    for (s32 i = 0; i < 6; ++i) {
        ksys::act::ActorLinkConstDataAccess weapon;
        auto& link = getWeapons()->mWeapons[i].link;
        if (link.hasProc()) {
            has_weapon = true;
            ksys::act::acquireActor(&link, &weapon);
            if (!weapon.sub_7100D0EFA4(1))
                return false;
        }
    }
    return has_weapon;
}

void NPC::sub_710002168C() {
    for (s32 i = 0; i < 6; ++i) {
        if (auto* weapon = getWeapons()->getEquippedWeapon(i)) {
            if (auto* bind = weapon->getModelBindInfo()) {
                bind->_20 = this;
                weapon->sub_71011CB390();
                bind->_20 = nullptr;
            } else {
                weapon->sub_71011CB390();
            }
        }
    }
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

bool NPC::sub_7100022AA4() {
    if (!(_fe8 & 4) || !sub_71000228F8())
        return false;
    if (auto* awareness = getAwareness()) {
        auto* sensor = awareness->_260[2];
        if (!sensor || !sensor->_50)
            return false;
    }
    return sead::SafeString(getASList()->sub_710115ECF4(59, 1)) != "SitOnObject" &&
           !(_fe8 & 0x10000);
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

bool ActorLinkConstDataAccess::sub_71000230C8() const {
    auto* npc = getNPC(mProc);
    if (!npc || !(npc->_fe8 & 4) || !npc->sub_71000228F8())
        return false;
    if (auto* awareness = npc->getAwareness()) {
        auto* sensor = awareness->_260[2];
        if (!sensor || !sensor->_50)
            return false;
    }
    return sead::SafeString(npc->getASList()->sub_710115ECF4(59, 1)) != "SitOnObject" &&
           !(npc->_fe8 & 0x10000);
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

// Source placement is inferred from the neighboring NPC accessor functions.
bool sub_7100023244(ksys::act::BaseProcAccessor* accessor) {
    auto* npc = ksys::act::getNPC(accessor->getProc());
    if (!npc)
        return false;
    auto* schedule = npc->getSchedule();
    return schedule && !schedule->_88.isEmpty();
}

namespace uking::act {
void NPC::m61(f32 rate) {
    sub_71000217F8(rate);
}
}  // namespace uking::act
