#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"

namespace ksys::act {

Unk_7102459df8::Unk_710079d5a0::Unk1* sub_71007A40D0(Actor* actor, int idx) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return nullptr;
    return unk->sub_710079CF98(idx);
}

bool sub_71007A4178(Actor* actor, bool flag) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return false;
    if (flag && actor->mCreateArgBaseProcLink.hasProc() &&
        actor->mCreateArgBaseProcLink == unk->sub_710079CF6C(0)->_18) {
        return false;
    }
    return unk->sub_710079CEE8();
}

s32 sub_71007A425C(Actor* actor) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return 0;
    return unk->sub_710079CF08();
}

bool sub_71007A42FC(Actor* actor) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return false;
    return unk->sub_710079CF20();
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

bool sub_71007A4638(Actor* actor, bool flag) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return false;
    if (flag && actor->mCreateArgBaseProcLink.hasProc() &&
        actor->mCreateArgBaseProcLink == unk->sub_710079CF6C(0)->_18) {
        return false;
    }
    return unk->sub_710079CE78();
}

Unk_7102459df8::Unk_7102459e60::Unk1* sub_71007A471C(Actor* actor, int idx) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return nullptr;
    return unk->sub_710079CF40(idx);
}

s32 sub_71007A47C4(Actor* actor) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return 0;
    return unk->sub_710079CE98();
}

bool sub_71007A4864(Actor* actor, bool flag) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return false;
    if (flag && actor->mCreateArgBaseProcLink.hasProc() &&
        actor->mCreateArgBaseProcLink == unk->sub_710079CF6C(0)->_18) {
        return false;
    }
    return unk->sub_710079CEB0();
}

Unk_7102459df8::Unk_7102459e88::Unk1* sub_71007A4948(Actor* actor, int idx) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return nullptr;
    return unk->sub_710079CF6C(idx);
}

s32 sub_71007A49F0(Actor* actor) {
    auto* unk = sead::DynamicCast<Unk_7102459df8>(actor->m126());
    if (!unk)
        return 0;
    return unk->sub_710079CED0();
}

}  // namespace ksys::act
