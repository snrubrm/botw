#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <cmath>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

// Separate TU from actPlayer.cpp: Player::m273 / m274 / m275 call these out of line in the original
// (a same-TU definition is inlined as a constant).
s32 Player::playerWeapons_return0() {
    return 0;
}

s32 Player::playerWeapons_return1() {
    return 1;
}

s32 Player::playerWeapons_return2() {
    return 2;
}

// NON_MATCHING: our build merges the two identical branches and tail-calls hasProc; the original keeps both.
// Placeholder name: whether weapon slot 2 holds a weapon. The original compares _d30 with the equipment type 3
// name first; both outcomes make the same check.
bool Player::sub_7100881EDC() {
    if (_d30 == getEquipmentTypeName(3))
        return getWeapons()->mWeapons[playerWeapons_return2()].link.hasProc();
    return getWeapons()->mWeapons[playerWeapons_return2()].link.hasProc();
}

// NON_MATCHING: as sub_7100881EDC (two identical branches merged in our build).
// Placeholder name: whether weapon slot 1 holds a weapon, after comparing _d30 with the equipment type 1 name.
bool Player::sub_7100888294() {
    if (_d30 == getEquipmentTypeName(1))
        return getWeapons()->mWeapons[playerWeapons_return1()].link.hasProc();
    return getWeapons()->mWeapons[playerWeapons_return1()].link.hasProc();
}

// NON_MATCHING: as sub_7100881EDC (two identical branches merged in our build).
// Placeholder name: whether weapon slot 0 holds a weapon, after comparing _d30 with the equipment type 1 name.
bool Player::sub_71008921A8() {
    if (_d30 == getEquipmentTypeName(1))
        return getWeapons()->mWeapons[playerWeapons_return0()].link.hasProc();
    return getWeapons()->mWeapons[playerWeapons_return0()].link.hasProc();
}

// NON_MATCHING: the original writes _d12 / _d13 with one strh per branch; ours sinks two strb.
// In this file because the original calls x_5 and x_35 out of line (actPlayer.cpp / actPlayerOutOfLine.cpp
// inline one of them).
// Placeholder name: grab start (PlayerGrabReady::enter_). Faces the grabbed actor (the connected calc child, else
// the attention target), stores its m38 value and main body volume, starts its lift type animation and records
// whether it is a hide barrel or a remote bomb (sphere / cube).
void Player::sub_710088755C() {
    _1c68 = x_5();
    _20bc.value = 0;
    _20bc.prev_value = 0;
    if (x_35())
        x_18(true);
    _d11 = true;

    auto* child = static_cast<Actor*>(getConnectedCalcChild());
    if (child) {
        _20f8 = child->m38();
        if (auto* body = child->getMainBody())
            _20fc = body->getVolume();
        mASList->x_6(0x19, 0, _20f8);
        const auto& child_pos = child->getMtx().m;
        sub_7100868220(
            std::atan2(child_pos[0][3] - _1770.x, child_pos[2][3] - _1770.z));
        mASList->goLimpFromHeadShotMaybe(
            0x31, child->getParam()->getRes().mGParamList->getLiftable()->mLiftType.ref(), 0);
        mASList->x_6(0x11, 0, 0.0f);
        const auto& name = child->getName();
        if (name.findIndex("HideBarrel") != -1)
            _c44.set(0x200000);
        if (name.findIndex("RemoteBomb") == -1) {
            _d12 = false;
            _d13 = false;
        } else if (name.findIndex("RemoteBombCube") == -1) {
            _d12 = true;
            _d13 = false;
        } else {
            _d12 = false;
            _d13 = true;
        }
        return;
    }

    ActorLinkConstDataAccess accessor;
    Attention::instance()->sub_7100D7482C(&accessor);
    _20f8 = accessor.sub_7100D14114();
    _20fc = accessor.sub_7100D141B0();
    mASList->x_6(0x19, 0, _20f8);
    const auto& mtx = accessor.getActorMtx();
    sub_7100868220(std::atan2(mtx(0, 3) - _1770.x, mtx(2, 3) - _1770.z));
    mASList->goLimpFromHeadShotMaybe(0x31, accessor.getLiftType(), 0);
    mASList->x_6(0x11, 0, 0.0f);
    if (accessor.getName().findIndex("HideBarrel") != -1)
        _c44.set(0x200000);
    if (accessor.getName().findIndex("RemoteBomb") == -1) {
        _d12 = false;
        _d13 = false;
    } else if (accessor.getName().findIndex("RemoteBombCube") == -1) {
        _d12 = true;
        _d13 = false;
    } else {
        _d12 = false;
        _d13 = true;
    }
}

}  // namespace ksys::act
