#include "KingSystem/ActorSystem/actPlayerInfo.h"

// In its own file: the original calls PlayerInfo::getPlayerPos() out of line.
// NON_MATCHING: the original calls PlayerInfo::getPlayerPos() with bl + ret (it returns a pointer there; ours tail calls)
const sead::Vector3f& getPlayerPosition() {
    if (auto* info = ksys::act::PlayerInfo::instance())
        return info->getPlayerPos();
    return sead::Vector3f::zero;
}
