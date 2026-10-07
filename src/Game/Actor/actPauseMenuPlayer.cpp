#include "Game/Actor/actPauseMenuPlayer.h"
#include "Game/UI/uiOnUiActorMgr.h"
#include "Game/UI/uiUtils.h"
#include <basis/seadNew.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

bool sub_7100A95270(sead::BufferedSafeString* out);

namespace uking::act {

PauseMenuPlayer::PauseMenuPlayer(const CreateArg& arg) : PlayerOrEnemy(arg) {
    _c34 = false;
    _c35[0] = 1;
    _1c0 = 13;
}

// NON_MATCHING: separate stores of the inherited byte fields instead of a halfword store.
ksys::act::BaseProc* PauseMenuPlayer::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) PauseMenuPlayer(arg);
}

PauseMenuPlayer::~PauseMenuPlayer() = default;

void PauseMenuPlayer::calcMaybe() {}

bool PauseMenuPlayer::prepareInit_(sead::Heap*, PrepareArg&) {
    if (uking::ui::OnUiActorMgr::instance())
        uking::ui::OnUiActorMgr::instance()->sub_7100906F08(this);
    return true;
}

ksys::act::PlayerArmors* PauseMenuPlayer::getArmors() {
    if (uking::ui::OnUiActorMgr::instance())
        return uking::ui::OnUiActorMgr::instance()->getArmors();
    return nullptr;
}

bool PauseMenuPlayer::m81(const ksys::Message& message) {
    switch (u32(message.getType())) {
    case 0x4000002:
        if (!mActorFlags2.isOn(ActorFlag2::_20))
            ksys::eft::searchAndEmitSLink(this, "equip_puton", false);
        return true;
    case 0x4000003:
        if (!mActorFlags2.isOn(ActorFlag2::_20))
            ksys::eft::searchAndEmitSLink(this, "equip_takeoff", false);
        return true;
    default:
        return PlayerOrEnemy::m81(message);
    }
}

void PauseMenuPlayer::preDelete3_(const PreDeleteArg& arg) {
    if (getChemicalStuff())
        getChemicalStuff()->_c &= ~0x1000000;
    if (uking::ui::OnUiActorMgr::instance())
        uking::ui::OnUiActorMgr::instance()->mActor = nullptr;
    _c34 = false;
    _c3c = 0;
    _c40 = 0;
    Actor::preDelete3_(arg);
}

bool PauseMenuPlayer::m165(sead::BufferedSafeString* out) {
    if (uking::ui::OnUiActorMgr::instance() &&
        uking::ui::OnUiActorMgr::instance()->_b0.findIndex("Arrow") != -1) {
        out->format("%s", uking::ui::OnUiActorMgr::instance()->_b0.cstr());
        return true;
    }
    return sub_7100A95270(out);
}

// NON_MATCHING: the SafeString argument stores merge after the conditional selection.
void PauseMenuPlayer::m114() {
    auto* as_list = sub_71011C9A88();
    if (!as_list)
        return;
    ksys::as::ASList::Unk4 event;
    if (as_list->x(61, &event, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        as_list->startAnimationMaybe(-1.0f, -1.0f,
                                    event.name.isEmpty() ? "FaceDefault" : event.name.cstr(),
                                    1, 0, true);
    }
    if (as_list->sub_710115FBC8(82, &event, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        sub_71012410C8(getXLink(), event.name.cstr(), 1, nullptr);
    if (as_list->sub_710115FBC8(85, &event, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        uking::ui::sub_7100A94BAC();
}

void PauseMenuPlayer::finalizeInit_(InitContext* context) {
    if (_c35[0])
        mASList->x_2(66, 33, true, false);
    else
        mASList->x_2(66, 33, false, false);
    coldHotStatusEffectStuff();
    if (getLodState())
        getLodState()->mFlags10.set(2);
    Actor::finalizeInit_(context);
    _c34 = false;
    _c3c = 0;
    _c40 = 0;
    mActorFlags2.set(ActorFlag2::_200);
    _c44 = 0;
    if (getChemicalStuff())
        getChemicalStuff()->_c |= 0x1000000;
}

// NON_MATCHING: the ecosystem singleton lookup is shared before the temperature branch.
void PauseMenuPlayer::coldHotStatusEffectStuff() {
    auto* mgr = uking::ui::OnUiActorMgr::instance();
    if (!mgr || !mgr->getArmors()) {
        mASList->x_6(23, 0, 0.0f);
        return;
    }
    auto* armors = mgr->getArmors();
    auto* chemical = getChemicalStuff();
    if (!chemical)
        return;
    const f32 temperature = chemical->sub_7100D91958();
    const s32 hot_level = _c3c + armors->getArmorEffectLevelResistHot();
    const s32 cold_level = _c40 + armors->getArmorEffectLevelResistCold();
    mASList->x_6(24, 0, temperature);
    ksys::eco::StatusEffectInfo effect;
    f32 animation_temperature;
    if (temperature > 0.0f) {
        ksys::eco::Ecosystem::instance()->getStatusEffectInfo(
            ksys::eco::StatusEffect_ResistHot, hot_level, &effect);
        animation_temperature = sead::Mathf::clampMin(temperature - effect.val._f32, 0.0f);
    } else {
        ksys::eco::Ecosystem::instance()->getStatusEffectInfo(
            ksys::eco::StatusEffect_ResistCold, cold_level, &effect);
        animation_temperature = sead::Mathf::clampMax(temperature - effect.val._f32, 0.0f);
    }
    mASList->x_6(23, 0, animation_temperature);
}

void PauseMenuPlayer::sub_71006E9E24() {
    _c3c = 0;
    _c40 = 0;
    _c44 = 0;
}

void PauseMenuPlayer::sub_71006EA6B8(s32 bit) {
    _c4c.setBit(bit);
}

}  // namespace uking::act
