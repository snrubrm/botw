#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/Actor/Player/Action/actionPlayerBackJump.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameRuneMgr.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"
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

// In this file because the original calls x_16, sub_710088A388, sub_71008823AC and sub_7100888278 out of line.
// Starts the change from the current equipment type (_d30) towards _d68: the per-type put-away work (rune item,
// sword, bow, both hands), then the shared follow-up; _d30 becomes type 0. The arguments are unused.
void Player::x_8(bool, bool) {
    if (_d68 == getEquipmentTypeName(2)) {
        if (_d30 == getEquipmentTypeName(6)) {
            uking::RuneMgr::instance()->setHandled();
            _d30 = getEquipmentTypeName(0);
        }
        if (sub_71007D86B4(this) &&
            mASList->x_5(1, 1, &as::ASList::Unk2::sub_71011631D0) != 0.0f) {
            x_18(true);
        }
        return;
    }

    if (_d30 == getEquipmentTypeName(1)) {
        x_16();
        sub_710088A388();
    } else if (!_c40.isOnBit(3)) {
        if (_d30 == getEquipmentTypeName(3)) {
            sub_71008823AC();
        } else if (_d30 == getEquipmentTypeName(5)) {
            if (getConnectedCalcChild()) {
                getConnectedCalcChild()->deleteLater(BaseProc::DeleteReason::_0);
                resetConnectedCalcChild(false);
            }
            uking::RuneMgr::instance()->setHandled();
        } else if (_d30 == getEquipmentTypeName(6)) {
            if (_d68 != getEquipmentTypeName(5))
                uking::RuneMgr::instance()->setHandled();
        }
    } else if (!(mASList->x_1(2, 0) == "WeaponEquipNG" && _1cdc == 0 &&
                 _d68 != getEquipmentTypeName(7)) &&
               !(_d68 == getEquipmentTypeName(1) && _d24 == 0)) {
        getWeapons()->mWeapons[1]._10 = true;
        _c40.resetBit(3);
        sub_7100888278();
        snd::Unk_7102502138::instance()->sub_710103B430(false);
    }

    if (_d11) {
        if (auto* pause_menu = uking::ui::PauseMenuDataMgr::instance())
            pause_menu->unholdGrabbedItems();
    }
    if (sub_71007D86B4(this)) {
        if (_d68 != getEquipmentTypeName(7))
            x_18(true);
    } else if (mASList->x_7(1, 1, &as::ASList::Unk2::sub_710002E82C) && !_c40.isOnBit(4)) {
        x_18(true);
    }
    if (!m225())
        x_24(3.0f);
    _d30 = getEquipmentTypeName(0);
}

// In this file because the original calls sub_710088A220, sub_710088B2EC and x_33 out of line.
// Placeholder name: puts the equipment away, depending on the current (_d30) and requested (_d68) types.
void Player::sub_710088CEC8() {
    if (_d68 == getEquipmentTypeName(7))
        return;
    if (_d30 == getEquipmentTypeName(1) || _d68 == getEquipmentTypeName(1)) {
        sub_710088A220();
        return;
    }
    if (_c40.isOnBit(3) || _d68 == getEquipmentTypeName(2)) {
        sub_710088B2EC();
        return;
    }
    if ((_d30 != getEquipmentTypeName(0) || _c40.isOnBit(3)) && _d30 != getEquipmentTypeName(4)) {
        x_33();
        return;
    }
    if (_d68 != getEquipmentTypeName(0) && _d68 != getEquipmentTypeName(4))
        x_33();
}

}  // namespace ksys::act
