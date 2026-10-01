#include "Game/Actor/actNPC.h"

namespace uking::act {

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

void NPC::onPreDeleteStart_(PrepareArg& arg) {
    NPCBase::onPreDeleteStart_(arg);
}

Unk_7100d3cd74* NPC::m101() {
    return &_fa8;
}

HorseRideInfo* NPC::getPlayerRideInfo() {
    return &_f28;
}

}  // namespace uking::act
