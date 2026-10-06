#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Event/evtEventSystem.h"

namespace ksys::act {

// Own file: the callers of these functions (e.g. sub_7100888278, getArmorChargeAttackAddLevel) are in other
// translation units in the original; a same-file definition would be inlined into them.

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
        ActorConstDataAccess accessor;
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
        mode = evt::EventSystem::instance()->_c8.hasProc() ? 4 : 0;
    }
    _2d30 = a1;
    _2d34 = mode;
    _2d48.reset();
    _2d38 = sead::Vector3f::zero;
    _2d58 = sead::Vector3f::zero;
    return true;
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

}  // namespace ksys::act
