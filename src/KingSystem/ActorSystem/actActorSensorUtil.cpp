#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"

using ksys::act::Actor;
using ksys::act::ActorAtk;
using ksys::act::Unk_7102459df8;

const ActorAtk::Unk_710079e64c::Unk1* sub_71007A255C(Actor* actor, int idx) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return nullptr;
    return atk->sub_710079E2C0(idx);
}

const ActorAtk::Struct7::AttackInfo* getAttackInfo(Actor* actor, int idx) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return nullptr;
    return atk->getAttackInfo(idx);
}

bool sub_71007A2604(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return false;
    return atk->m10();
}

s32 sub_71007A26AC(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return 0;
    return atk->sub_710079E270();
}

bool hasAttackInfo(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return false;
    return atk->hasAttackInfoMaybe();
}

s32 getNumAttackInfoMaybe(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return 0;
    return atk->getNumAttackInfoMaybe();
}

void* getActorAttackSensor(Actor* actor) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return nullptr;
    return atk->_40;
}

void sub_71007A44E4(Actor* actor, bool on) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return;
    if (!on)
        atk->_78 &= ~1;
    else
        atk->_78 |= 1;
}

void sub_71007A458C(Actor* actor, bool on) {
    auto* atk = sead::DynamicCast<ActorAtk>(actor->getAtk());
    if (!atk)
        return;
    if (!on)
        atk->_78 &= ~2;
    else
        atk->_78 |= 2;
}

Unk_7102459df8::Unk_710079d5a0::Unk1* sub_71007A40D0(Actor* actor, int idx) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return nullptr;
    return obj->sub_710079CF98(idx);
}

bool sub_71007A4178(Actor* actor, bool ignore_creator) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    if (ignore_creator && actor->getCreateArgBaseProcLink().hasProc() &&
        actor->getCreateArgBaseProcLink() == obj->sub_710079CF6C(0)->_18) {
        return false;
    }
    return obj->sub_710079CEE8();
}

s32 sub_71007A425C(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return 0;
    return obj->sub_710079CF08();
}

bool sub_71007A42FC(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    return obj->sub_710079CF20();
}

bool isLandedMaybe(Actor* actor, bool ignore_creator) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    if (ignore_creator && actor->getCreateArgBaseProcLink().hasProc() &&
        actor->getCreateArgBaseProcLink() == obj->sub_710079CF6C(0)->_18) {
        return false;
    }
    return obj->sub_710079CE78();
}

Unk_7102459df8::Unk_7102459e60::Unk1* sub_71007A471C(Actor* actor, int idx) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return nullptr;
    return obj->sub_710079CF40(idx);
}

s32 sub_71007A47C4(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return 0;
    return obj->sub_710079CE98();
}

bool isBgGroundHit(Actor* actor, bool ignore_creator) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return false;
    if (ignore_creator && actor->getCreateArgBaseProcLink().hasProc() &&
        actor->getCreateArgBaseProcLink() == obj->sub_710079CF6C(0)->_18) {
        return false;
    }
    return obj->sub_710079CEB0();
}

Unk_7102459df8::Unk_7102459e88::Unk1* sub_71007A4948(Actor* actor, int idx) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return nullptr;
    return obj->sub_710079CF6C(idx);
}

s32 sub_71007A49F0(Actor* actor) {
    auto* obj = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!obj)
        return 0;
    return obj->sub_710079CED0();
}
