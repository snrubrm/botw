#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "Game/gameRuneMgr.h"
#include "Game/Actor/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/System/VFR.h"

namespace ksys::act {

// Own file: the callers of these functions (e.g. sub_7100888278, getArmorChargeAttackAddLevel) are in other
// translation units in the original; a same-file definition would be inlined into them.

// NON_MATCHING: register allocation / scheduling of the bone key addresses.
void Player::x_31() {
    _c40.setBit(7);
    auto* list = mASList;
    list->sub_710115C9E0(1);
    list->mSlots[1].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[1].sub_7101165008(_19f0[25], 0, true);
    list->mSlots[1].sub_7101164E38(false);

    list = mASList;
    list->sub_710115C9E0(2);
    list->mSlots[2].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[2].sub_7101165008(_19f0[2], 0, true);
    list->mSlots[2].sub_7101165008(_19f0[25], 3, true);
    list->mSlots[2].sub_7101165008(_19f0[50], 3, true);
    list->mSlots[2].sub_7101164E38(false);
}

// NON_MATCHING: register allocation / scheduling of the bone key addresses (as in x_31).
// Placeholder name: the same AS slot 1 / 2 bone key setup as x_31 with the bones 4 / 2 / 4 / 50.
void Player::sub_7100855494() {
    _c40.setBit(7);
    auto* list = mASList;
    list->sub_710115C9E0(1);
    list->mSlots[1].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[1].sub_7101165008(_19f0[4], 0, true);
    list->mSlots[1].sub_7101164E38(false);

    list = mASList;
    list->sub_710115C9E0(2);
    list->mSlots[2].sub_7101165008(_19f0[0], 3, true);
    list->mSlots[2].sub_7101165008(_19f0[2], 0, true);
    list->mSlots[2].sub_7101165008(_19f0[4], 3, true);
    list->mSlots[2].sub_7101165008(_19f0[50], 3, true);
    list->mSlots[2].sub_7101164E38(false);
}

void Player::switchToAnimSequenceMaybe(const char* name, bool a2, f32 a3) {
    if (!a2 && mASList->x_1(0, 0) == name)
        return;
    auto* list = mASList;
    if (!list->x_7(0, 0, &as::ASList::Unk2::sub_710002E82C)) {
        sead::Matrix34f mtx;
        mModel->getUnits()(_19f0[0].model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&mtx, _19f0[0].bone_index);
        const sead::Vector2f p0 = {mtx(0, 3), mtx(2, 3)};
        mModel->getUnits()(_19f0[1].model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&mtx, _19f0[1].bone_index);
        const sead::Vector2f p1 = {mtx(0, 3), mtx(2, 3)};
        if ((p1 - p0).length() > 0.5f)
            a3 = 0.0f;
    }
    list->startAnimationMaybe(a3, -1.0f, name, 0, 0, true);
    _c48.setBit(12);
    _2104 = a3;
    if (mASList->x_7(0, 1, &as::ASList::Unk2::sub_710002E82C))
        mASList->sub_710115F2EC(0, 0, 0.0f);
    else
        mASList->sub_710115F2EC(0, 0, 1.0f);
}

void Player::x_23(const char* name, bool a2, f32 a3) {
    if (!a2 && mASList->x_1(1, 1) == name)
        return;
    auto* list = mASList;
    if (list->x_7(1, 1, &as::ASList::Unk2::sub_710002E82C))
        list->startAnimationMaybe(a3, -1.0f, name, 1, 1, true);
    else
        list->sub_710115B140(name, 1, 1, 1, 0);
    _c48.setBit(13);
    mASList->sub_710115F2EC(1, 0, 0.0f);
    mASList->sub_710115F2EC(1, 1, 1.0f);
    _c50.setBit(26);
}

void Player::sub_7100855BB4(const char* name, bool a2, f32 a3) {
    if (!a2 && mASList->x_1(0, 1) == name)
        return;
    mASList->startAnimationMaybe(a3, -1.0f, name, 0, 1, true);
    mASList->sub_710115F2EC(0, 0, 0.0f);
    mASList->sub_710115F2EC(0, 1, 1.0f);
    _c50.setBit(27);
}

bool Player::sub_7100859EDC(bool a1, int mode, const sead::Vector3f* pos, BaseProcLink* link,
                            const sead::Vector3f* pos2) {
    _2d30 = a1;
    _2d34 = mode;
    _2d48.reset();
    if (mode == 1) {
        if (!link)
            return false;
        ActorLinkConstDataAccess accessor;
        acquireActor(link, &accessor);
        if (!accessor.linkAcquire(&_2d48))
            return false;
    }
    _2d38 = *pos;
    _2d58 = *pos2;
    return true;
}

bool Player::sub_7100859FC0(bool a1) {
    s32 mode = 0;
    if (a1) {
        if (_2d30)
            return true;
        mode = evt::EventSystem::instance()->mSpeaker.mLink.hasProc() ? 4 : 0;
    }
    _2d30 = a1;
    _2d34 = mode;
    _2d48.reset();
    _2d38 = sead::Vector3f::zero;
    _2d58 = sead::Vector3f::zero;
    return true;
}

// Placeholder name: stores a new colour in _e60 and passes it on to Unk_710260af28 with the model.
void Player::sub_710085A64C(const sead::Color4f& color) {
    if (_e60 == color)
        return;
    _e60 = color;
    Unk_710260af28::instance()->sub_7100F1E2F4(mModel, color);
}

void Player::x_18(bool a1) {
    if (!mASList->x_7(1, 1, &as::ASList::Unk2::sub_710002E82C))
        return;
    mASList->sub_710115B01C(1, 1, a1);
    mASList->sub_710115F2EC(1, 0, 1.0f);
    mASList->sub_710115F2EC(1, 1, 0.0f);
    sub_7100855AF8();
}

void Player::sub_7100855AF8() {
    if (!mASList->x_7(3, 1, &as::ASList::Unk2::sub_710002E82C))
        return;
    mASList->sub_710115B01C(3, 1, true);
    if (mASList->x_7(3, 2, &as::ASList::Unk2::sub_710002E82C))
        return;
    mASList->sub_710115F2EC(3, 0, 1.0f);
    mASList->sub_710115F2EC(3, 1, 0.0f);
}

f32 Player::sub_7100885630(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_ArmorChargeAttackAddLevel, level, &info);
    return info.val._f32;
}

// NON_MATCHING: the original reloads _16f4 for the fade chase and shares one chase tail between the camera and
// the final branch.
// Placeholder name: updates the model alpha: 0 with _c48 bit 23; a requested fade (_16f0: towards _16f4 at rate
// _16f8, capped at ItemUseModelAlpha while a camera rune is out); the camera's player alpha rate; ItemUseModelAlpha
// while a camera rune is out; otherwise back towards 1.
void Player::sub_710085A6B8() {
    if (_c48.isOnBit(23)) {
        sub_71011CCB1C(0.0f);
        return;
    }

    if (_16f0) {
        _16f0 = false;
        const f32 target = _16f4;
        auto* rune = uking::RuneMgr::instance();
        if (((rune->_90 >> 4 & 1) && rune->isSelectedRune(2)) ||
            ((rune->_90 >> 4 & 1) && rune->isSelectedRune(3)) ||
            ((rune->_90 >> 4 & 1) && rune->isSelectedRune(4))) {
            const f32 alpha = getParam()->getRes().mGParamList->getPlayer()->mItemUseModelAlpha.ref();
            if (alpha < target) {
                sub_71011CCB1C(alpha);
                return;
            }
        }
        f32 value = m139();
        sead::Mathf::chase(&value, _16f4, _16f8 * _20ec * VFR::instance()->getDeltaFrame());
        sub_71011CCB1C(value);
        return;
    }

    if (_ce0.isOnBit(1)) {
        act::acc::Camera camera;
        sub_710092DAE8(&camera);
        const f32 target = camera.getPlayerAlphaRate() * uking::sUnk_7101e7c264;
        f32 value = m139();
        sead::Mathf::chase(&value, target, uking::sUnk_7101e7c26c * _20ec * VFR::instance()->getDeltaFrame());
        sub_71011CCB1C(value);
        return;
    }

    auto* rune = uking::RuneMgr::instance();
    if (((rune->_90 >> 4 & 1) && rune->isSelectedRune(2)) ||
        ((rune->_90 >> 4 & 1) && rune->isSelectedRune(3)) ||
        ((rune->_90 >> 4 & 1) && rune->isSelectedRune(4))) {
        const f32 value = m139();
        const f32 alpha = getParam()->getRes().mGParamList->getPlayer()->mItemUseModelAlpha.ref();
        if (value == alpha)
            return;
        sub_71011CCB1C(alpha);
        return;
    }

    f32 value = m139();
    if (value >= 1.0f)
        return;
    sead::Mathf::chase(&value, 1.0f, uking::sUnk_7101e7c268 * _20ec * VFR::instance()->getDeltaFrame());
    sub_71011CCB1C(value);
}

}  // namespace ksys::act
