#include "Game/Actor/actNPC.h"
#include <basis/seadNew.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::act {

ksys::act::BaseProc* NPC::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) NPC(arg);
}

// NON_MATCHING: member types are incomplete
NPC::~NPC() = default;

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
        ksys::act::ActorConstDataAccess accessor;
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

bool ActorConstDataAccess::sub_7100022ED8() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_fe8 & 4;
}

bool ActorConstDataAccess::sub_7100022FD0() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_fe8 & 0x2000;
}

bool ActorConstDataAccess::sub_7100023358() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_fe8 & 0x40000;
}

bool ActorConstDataAccess::sub_7100023450() const {
    auto* npc = getNPC(mProc);
    if (!npc)
        return false;
    return npc->_1048 == 3;
}

const sead::Vector3f& ActorConstDataAccess::sub_710002354C() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!sead::IsDerivedFrom<uking::act::NPC>(actor))
        return sead::Vector3f::zero;
    return static_cast<uking::act::NPC*>(actor)->_1098;
}

}  // namespace ksys::act
