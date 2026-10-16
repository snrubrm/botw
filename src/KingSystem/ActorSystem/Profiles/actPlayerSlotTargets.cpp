#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>
#include "Game/gameSceneSubsys14.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7101E7C2B4.h"
#include "Game/Actor/actCameraUtil.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/StageInfo.h"
#include "Game/Actor/Player/Action/actionPlayerBackJump.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"

namespace ksys::act {

void Player::x_40() {
    _1d6c = 1.0f;
    _c40.reset(0x1200000);
    _1d64 = 0.0f;
    _1d68 = 0.0f;
    _1f8c = 0;
    _1f84 = 0;
    if (_c44.isOnBit(8)) {
        if (mASList->x_1(1, 1) != "WeaponThrow") {
            _c44.resetBit(8);
            x_18(true);
        }
    }
}

// These two sit in their own file: Player::m296 / m298 tail-call them in the original.
s32 Player::sub_7100892824() {
    if (_cf4.isOnBit(15))
        return _17f1 ? 1 : 2;
    if (!m224())
        return 0;
    if (_d24 != 0)
        return 0;
    if (mASList->sub_710115ED5C(0x42, 0x24) && mASList->sub_710115ED5C(0x42, 0x26))
        return 0;
    return _1f8c == 2 ? 1 : 2;
}

s32 Player::sub_71008923B0(int a1) {
    switch (a1) {
    case 0:
        return 4;
    case 1:
        return 2;
    case 2:
        return 5;
    default:
        return 0;
    }
}

// Placeholder name: whether AS slot 0 plays a sword cut (CutL1, CutS1-4, CutSF, CutDash).
bool Player::sub_71008923D0() {
    return mASList->x_1(0, 0) == "CutL1" || mASList->x_1(0, 0) == "CutS1" ||
           mASList->x_1(0, 0) == "CutS2" || mASList->x_1(0, 0) == "CutS3" ||
           mASList->x_1(0, 0) == "CutS4" || mASList->x_1(0, 0) == "CutSF" ||
           mASList->x_1(0, 0) == "CutDash";
}

// NON_MATCHING: the inlined copy of x_40 has its stores scheduled differently (the original keeps the order of the
// out-of-line x_40)
void Player::x_16() {
    _c40.resetBit(24);
    if (x_17())
        x_18(true);
    x_40();
    x_19(-1.0f);
}

// NON_MATCHING: load scheduling only (_1770.y before the parameter buffer, the angle mask before _1c84).
// In this file because the original calls sub_710087F360 out of line.
// Sets the move animation rate (AS slot 0): the stick tilt (or 1.5 / _1fa8), capped while the scene limits it,
// slowed in deep water and stopped when facing the grabbed / pushed actor.
void Player::x_27() {
    f32 rate;
    if (m178()) {
        _1fa8 = 1.5f;
        _c48.resetBit(27);
        rate = 1.5f;
    } else {
        rate = _1fa8;
        if (!(rate > 1.0f))
            rate = std::min(_17d0->getLeftStick().length(), 1.0f);
    }

    if (GameSceneSubsys14::instance()->sub_7100904F10() && !m178()) {
        const f32 max = getParam()->getRes().mGParamList->getPlayer()->mStickMaxInStore.ref();
        if (rate > max)
            rate = max;
    }

    if (_cfc.isOn(0x12)) {
        f32 depth;
        if (_cfc.isOnBit(4))
            depth = getParam()->getRes().mGParamList->getPlayer()->mWaterDepthInGrudge.ref();
        else
            depth = _20d4 - _1770.y;
        const auto* param = getParam()->getRes().mGParamList->getPlayer();
        depth -= param->mMoveIgnoreWaterHeight.ref();
        f32 factor;
        if (depth > 0.0f) {
            const f32 ratio = std::min(
                depth / (param->mMoveDecRateMaxHeight.ref() - param->mMoveIgnoreWaterHeight.ref()), 1.0f);
            factor = sead::Mathf::min(1.0f - param->mMoveDecRateByBog.ref() * ratio, 1.0f);
        } else {
            factor = 1.0f;
        }
        rate *= factor;
    }

    if (_cfc.isOnBit(6) || _c48.isOnBit(27)) {
        auto* child = sead::DynamicCast<Actor>(getConnectedCalcChild());
        if (child) {
            if (auto* body = child->getPhysicsMainBody()) {
                sead::Vector3f dir;
                _1b18.getBase(dir, 2);
                dir.normalize();
                const sead::Vector3f start = body->getCenterOfMassInWorld();
                const sead::Vector3f end = start + dir * _1fec * 1.5f;
                sead::Vector3f hit;
                if (sub_710087F360(start, end, nullptr, &hit)) {
                    _1c84 = sead::Mathf::atan2Idx(hit.x, hit.z);
                } else {
                    _cfc.reset(0x60);
                    _c48.resetBit(27);
                }
            }
        }
    }

    if (_cfc.isOnBit(5) || _c48.isOnBit(27)) {
        if (_cfc.isOnBit(6)) {
            _c48.setBit(27);
            _1c78 = _1c74;
        }
        if (util::sub_71011EE4C0(s64(_1c84) - (util::sUnk_7101EC6BA0 & (_1c74 ^ 0x80000000))) < 0x4000000)
            rate = 0.0f;
        else if (rate > 0.15f)
            rate = 0.15f;
    }

    if (x_44())
        rate *= getParam()->getRes().mGParamList->getPlayer()->mStickDiamTired.ref();
    mASList->sub_710115EFD0(0, false, false, rate);
}

// In this file because the original calls x_7, x_10, sub_71008821BC and sub_7100887B68 out of line.
// Finishes the equip change requested in _d68: runs the per-type follow-up (sword, shield, bow, bomb grab, rune
// item), then makes _d68 the current type in _d30 (type 7 becomes type 0) and resets _d68.
void Player::sub_710088D654() {
    if (m225() || m226()) {
        if (_d68 == getEquipmentTypeName(7) && _1e3c.value <= sead::Mathf::epsilon()) {
            const f32 time = getParam()->getRes().mGParamList->getPlayer()->mNoEnergyDashInterval.ref();
            _1e3c = ksys::Timer(time, time);
        }
    }

    x_8(false, false);
    if (_d68 == getEquipmentTypeName(1)) {
        x_10(false);
    } else if (_d68 == getEquipmentTypeName(2)) {
        x_7();
        _d68 = getEquipmentTypeName(0);
        return;
    } else if (_d68 == getEquipmentTypeName(3)) {
        sub_71008821BC();
    } else if (_d68 == getEquipmentTypeName(4)) {
        if (auto* child = static_cast<Actor*>(getConnectedCalcChild())) {
            sub_71005DC41C(child);
            mASList->x_6(0x11, 0, 0.0f);
            sub_7100887B68(-1.0f);
            _c48.resetBit(10);
            mASList->goLimpFromHeadShotMaybe(
                0x31, child->getParam()->getRes().mGParamList->getLiftable()->mLiftType.ref(), 0);
        }
    } else if (_d68 == getEquipmentTypeName(5)) {
    } else if (_d68 == getEquipmentTypeName(6)) {
        if (_17d0->playerCheckController(13) && !m202() && !_c44.isOnBit(13) && !m178())
            _c44.setBit(10);
    }

    if (_d68 == getEquipmentTypeName(7))
        _d30 = getEquipmentTypeName(0);
    else
        _d30 = _d68;
    _d68 = getEquipmentTypeName(0);
}

// NON_MATCHING: the original merges the TeamGolemLittle / _cf0 bit 30 tests with orr (ours branches twice),
// plus small scheduling differences.
// In this file because the original calls sub_710088873C and sub_7100888618 out of line.
// Releases the grabbed actor: a sleeping RemoteBomb is deleted; otherwise it is dropped in front of the player
// (or, with `event`, deleted during Demo005_0 and sent message 0x8000002). Then resets the grab state.
void Player::m228(bool event) {
    if (_c4c.isOnBit(14) || sub_71007D86B4(this) || gdt::getFlag_HatenoDye_Start())
        return;

    if (auto* child = getConnectedCalcChild()) {
        const sead::SafeString name = child->getName();
        if (child->getState() == BaseProc::State::Sleep && name.startsWith("RemoteBomb"))
            child->deleteLater(BaseProc::DeleteReason::_0);

        bool released = false;
        if (auto* subsys = GameSceneSubsys12::instance()) {
            if (subsys->sub_71006652C8()) {
                if (sub_710088873C()) {
                    if (auto* pause_menu = uking::ui::PauseMenuDataMgr::instance())
                        pause_menu->unholdGrabbedItems();
                }
                released = true;
            }
        }

        BaseProcLink link;
        link.acquire(child, false);
        ActorLinkConstDataAccess accessor;
        acquireActor(&link, &accessor);
        const bool is_golem = accessor.hasTag("TeamGolemLittle");
        if (!released && !is_golem && !_cf0.isOnBit(30)) {
            sead::Vector3f dir;
            _1b18.getBase(dir, 2);
            dir.normalize();
            const sead::Vector3f pos = dir * -0.2f;
            if (auto* actor = sead::DynamicCast<Actor>(child)) {
                if (!event) {
                    sub_71005DC350(actor, pos);
                } else {
                    if (auto* active_event = evt::Manager::instance()->getActiveEvent()) {
                        if (active_event->mEventName == "Demo005_0")
                            actor->deleteEx(Actor::DeleteType::_1, BaseProc::DeleteReason::_0);
                    }
                    sendMessage(*actor->getMesTransceiverId(), MessageType(0x8000002), nullptr, true);
                }
            }
        }
        resetConnectedCalcChild(false);
    }

    _c40.resetBit(17);
    _d11 = false;
    _20f8 = 0;
    _c44.resetBit(21);
    if (_d30 == getEquipmentTypeName(4))
        _d30 = getEquipmentTypeName(0);
    if (m203()) {
        if (_d68 == getEquipmentTypeName(7)) {
            x_24(-1.0f);
            _d68 = getEquipmentTypeName(0);
        }
    }
    if ((!_c44.isOnBit(8) || _d11) && !sub_7100888618())
        x_18(true);
}

// NON_MATCHING: the inlined makeRTIdx matrix is built in a different order (scheduling only).
// In this file because the original calls sub_710088CEC8, sub_710087F654 and sub_710087F360 out of line.
// Placeholder name: puts the player back at the saved position _230c (facing _2324) after drowning / falling
// out of bounds: snaps it to the ground just behind, resets the controller, moves the ridden horse along,
// restores _20b8 stamina and notifies the camera.
void Player::sub_710086D5B8() {
    sub_710088CEC8();
    if (auto* aoc = aoc::Manager::instance())
        aoc->x(&_230c, nullptr, nullptr);

    sead::Vector3f back{_1770.x - _230c.x, 0.0f, _1770.z - _230c.z};
    back.normalize();
    _1770 = _230c;
    _177c = _230c;
    x_53(_2324);
    _d1c = 0;
    _20bc.value = 0;
    _20bc.prev_value = 0;

    sead::Vector3f start = _1770 - back * 0.35f;
    sead::Vector3f end = start;
    start.y += 1.45f;
    end.y += 0.4f;
    if (StageInfo::sIsCDungeon)
        end.y += 0.2f;
    if (!sub_710087F654(start, end, phys::GroundHit(0), nullptr, false, false, 0.0f)) {
        end.y = _1770.y + -0.1f;
        if (StageInfo::sIsCDungeon)
            end.y += -0.2f;
        sead::Vector3f hit_pos;
        sead::Vector3f hit_normal;
        if (sub_710087F360(start, end, &hit_pos, &hit_normal)) {
            const f32 slope =
                std::atan2(hit_normal.y, sead::Vector2f(hit_normal.x, hit_normal.z).length());
            const u32 angle = util::sUnk_7101EC6BA0 &
                              (u32(sead::Mathf::rad2idx(-slope)) + (util::sUnk_7101EC6BA0 & 0x40000000));
            if (util::sub_71011EE4C0(angle) <
                u32(s64(uking::sUnk_7101e7c2f8 * (0x80000000u / 180.0f)))) {
                _1770 = hit_pos;
            }
        }
    }

    if (auto* controller = getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F5F458(MotionType::_0);
    }

    sead::Matrix34f mtx;
    mtx.makeRTIdx({0, _2324.value, 0}, _1770);
    setMtx(mtx, true, true);
    nullsub_4648();
    if (isRidingHorse()) {
        auto* info = getPlayerRideInfo();
        if (!info->_18.isAccessingSpecifiedProcUnsafe(info->mActor)) {
            auto* horse = sead::DynamicCast<Actor>(info->_18.getProc(nullptr, info->mActor));
            if (horse) {
                if (_cf4.isOnBit(9))
                    horse->setMtx(mtx, false, true);
                else
                    sendMessage(*horse->getMesTransceiverId(), MessageType(0x3000007), nullptr, true);
            }
        }
    }
    addExtraStamina(_20b8, 0.0f);
    m323();

    ActorLinkConstDataAccess camera;
    getRoot6SomeActor(&camera);
    sendMessage(*camera.getMessageTransceiverId(), MessageType(0x880000c), nullptr, true);
}

}  // namespace ksys::act
