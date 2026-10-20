#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/XLink/xlinkChemicalEventState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndMiiSound.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/XLink/xlinkUser.h"
#include "Game/Scene/gameScene.h"
#include <gsys/gsysModel.h>
#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include <aal/aalSoundSource.h>
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2SystemSLink.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>

#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/System/physClosestPointQueryWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"

namespace ksys::xlink {

// Native twenty-entry chemical key table at 0x7102516100.
const char* const sUnk_7102516100[20] = {
    "Chemical_Fire", "Chemical_Smoke", "Chemical_SmokeCook", "Chemical_Electricity",
    "Chemical_IceMeltSlow", "Chemical_IceMeltFast", "Chemical_Explosion",
    "Chemical_Explosion_Inside", "Chemical_Wet", "Chemical_Steam", "Chemical_FireExtinction",
    "Chemical_ElecConnect", "Chemical_ElectricWater", "Chemical_ElectricAir", "Chemical_IceMagic",
    "Chemical_Lightning", "Chemical_Lightning_Water", "Chemical_LightningSign",
    "Chemical_LightningSign_OT", "Chemical_BlueFire"
};

// NON_MATCHING: effect / sound selection, string comparisons and handle temporaries differ.
void ChemicalEventState::sub_710122E018(act::Actor* actor, XLink* effect, XLink* sound,
                                      Unk_71012419b4* handles, act::Chemical* chemical, u32 kind,
                                      bool emit_start, bool force_fallback, bool aoc) {
    if (auto* player = act::ActorSystem::instance()->getPlayerLink()) {
        if (player->m206() && sead::IsDerivedFrom<act::WeaponBase>(actor) &&
            static_cast<act::WeaponBase*>(actor)->isParentPlayer()) {
            if (kind == 10)
                return;
            if (kind < 3 || kind == 19)
                emit_start = false;
        }
    }
    const char* key = sUnk_7102516100[kind];
    if (effect && !effect->_cc.isOnBit(10)) {
        if (auto* instance = effect->_48) {
            if (kind == 17)
                instance->setPropertyValue(4, chemical->_bc & 2 ? chemical->_1c4 : 0.0f);
            instance->searchAndEmit(key, &handles->mELink);
        }
    }
    const bool active = handles->mELink.isActive();
    if (!sound || (kind != 10 && !active) || sound->_cc.isOnBit(10))
        return;
    const char* start = nullptr;
    switch (kind) {
    case 0:
    case 19: {
        bool indoor = false;
        bool queried = false;
        if (actor) {
            queried = sub_710122E8CC(&indoor, actor);
        } else if (aoc && chemical) {
            const sead::Vector3f position = chemical->sub_7100D9155C();
            queried = sub_710122EABC(&indoor, position);
        }
        if (queried && indoor)
            key = kind == 0 ? "Chemical_Fire_InDoor" : "Chemical_BlueFire_InDoor";
        start = kind == 0 ? "Chemical_BurnStart" : "Chemical_BlueFire_BurnStart";
        break;
    }
    case 1: start = "Chemical_SmokeStart"; break;
    case 2: start = "Chemical_SmokeCookStart"; break;
    case 3: start = "Chemical_Electricity_Start"; break;
    case 9: start = "Chemical_SteamStart"; break;
    case 11: start = "Chemical_ElecConnect_Start"; break;
    case 12: start = "Chemical_ElectricWater_Start"; break;
    }
    auto* instance = sound->_50;
    if (!instance)
        return;
    if (handles->mSLink.isActive() && !handles->mSLink.getEvent()->getBitFlag().isOnBit(4)) {
        const char* current_key = xlink2::solveOffset<char>(
            handles->mSLink.getEvent()->getAssetCallTable()->keyNamePos);
        if (sead::SafeString(current_key) == key)
            return;
        handles->mSLink.fadeIfLoopSound();
    }
    instance->searchAndEmit(key, &handles->mSLink);
    if (actor && emit_start && start && !(actor->get4f8() > 0.0f)) {
        const int type = sub_7101240FE8(actor);
        if (type != 1 && type != 2)
            actor = act::Reaction::instance()->_38;
        if (force_fallback)
            actor = act::Reaction::instance()->_38;
        if (!actor)
            return;
        auto* start_link = actor->getXLink();
        if (!start_link || start_link->_cc.isOnBit(10) || !start_link->_50)
            return;
        auto handle = start_link->_50->searchAndEmit(start);
        if (handle.isActive() && chemical)
            handle.setPosition(chemical->sub_7100D9155C());
    }
}

// NON_MATCHING: query and contact iterator temporaries use different stack slots.
bool ChemicalEventState::sub_710122E8CC(bool* indoor, act::Actor* actor) const {
    if (!actor)
        return false;
    phys::SensorCollisionMask mask(phys::SensorCollisionMask::CustomReceiverTag{});
    phys::receiverMaskEnableLayer(&mask, phys::ContactLayer::SensorInDoor);
    const sead::Vector3f position = actor->getMtx().getTranslation();
    phys::SphereBasedClosestPointQuery query(position, 0.000001f, mask, nullptr, 1,
                                            "ChemicalController InDoor", 0,
                                            phys::LowPriority::Yes);
    query.getContactPointInfo()->subscribeLayer(phys::ContactLayer::SensorInDoor);
    const bool hit = query.execute(false);
    if (query._18 == 1) {
        *indoor = hit;
        if (hit && query.getContactPointInfo()) {
            for (const auto* point : *query.getContactPointInfo()) {
                const u32 type = (point->material_mask_b.getRawData() >> 20) & 7;
                if (type == 3 || type == 4) {
                    *indoor = false;
                    break;
                }
            }
        }
    }
    return query._18 == 1;
}

// NON_MATCHING: query and contact iterator temporaries use different stack slots.
bool ChemicalEventState::sub_710122EABC(bool* indoor, const sead::Vector3f& position) const {
    phys::SensorCollisionMask mask(phys::SensorCollisionMask::CustomReceiverTag{});
    phys::receiverMaskEnableLayer(&mask, phys::ContactLayer::SensorInDoor);
    phys::SphereBasedClosestPointQuery query(position, 0.000001f, mask, nullptr, 1,
                                            "ChemicalController InDoor", 0,
                                            phys::LowPriority::Yes);
    query.getContactPointInfo()->subscribeLayer(phys::ContactLayer::SensorInDoor);
    const bool hit = query.execute(false);
    if (query._18 == 1) {
        *indoor = hit;
        if (hit && query.getContactPointInfo()) {
            for (const auto* point : *query.getContactPointInfo()) {
                const u32 type = (point->material_mask_b.getRawData() >> 20) & 7;
                if (type == 3 || type == 4) {
                    *indoor = false;
                    break;
                }
            }
        }
    }
    return query._18 == 1;
}

// NON_MATCHING: explicit XLink fallback selects and the map-type comparison differ.
void ChemicalEventState::sub_710122E56C(XLink* supplied, Unk_71012419b4* handles,
                                      act::Chemical* chemical, u32 kind, bool emit_start,
                                      bool force_fallback, act::Actor* actor) {
    auto* reaction = act::Reaction::instance();
    if (!reaction || !reaction->_38)
        return;
    auto* fallback = reaction->_38->getXLink();
    XLink* effect = fallback;
    XLink* sound = fallback;
    if (!force_fallback) {
        effect = supplied;
        sound = supplied;
        if (supplied && !supplied->_cc.isOnBit(10)) {
            effect = supplied->_48 ? supplied : fallback;
            sound = supplied->_50 ? supplied : fallback;
        }
    }
    const bool aoc = StageInfo::getCurrentMapType() == "AocField";
    if (aoc && actor && isFarChemicalActorNameMaybe(actor->getName()))
        sound = fallback;
    sub_710122E018(actor, effect, sound, handles, chemical, kind, emit_start, force_fallback, aoc);
}



// NON_MATCHING: the two actor fallback selects are scheduled in the opposite order.
void ChemicalEventState::sub_710122DE90(act::Actor* actor, Unk_71012419b4* handles,
                                      act::Chemical* chemical, u32 kind, bool a,
                                      bool force_fallback) {
    auto* reaction = act::Reaction::instance();
    if (!reaction || !reaction->_38)
        return;
    auto* fallback = reaction->_38;
    const int effect_type = sub_7101240FE8(actor);
    auto* effect_actor = (effect_type | 2) == 2 ? actor : fallback;
    const int sound_type = sub_7101240FE8(actor);
    auto* sound_actor = sound_type == 1 || sound_type == 2 ? actor : fallback;
    if (force_fallback) {
        effect_actor = fallback;
        sound_actor = fallback;
    }
    const bool aoc = StageInfo::getCurrentMapType() == "AocField";
    if (aoc && actor && isFarChemicalActorNameMaybe(actor->getName()))
        sound_actor = fallback;
    sub_710122E018(actor, effect_actor ? effect_actor->getXLink() : nullptr,
                  sound_actor ? sound_actor->getXLink() : nullptr, handles, chemical, kind, a,
                  force_fallback, aoc);
}

void ChemicalEventState::transferFrom(ChemicalEventState& other) {
    mActiveMask = other.mActiveMask;
    for (s32 i = 0; i < mHandles.size(); ++i) {
        mHandles[i] = other.mHandles[i];
        other.mHandles[i].mELink.reset();
        other.mHandles[i].mSLink.reset();
    }
}

void ChemicalEventState::fade() {
    if (mFaded)
        return;
    mFaded = true;
    for (s32 i = 0; i < mHandles.size(); ++i) {
        auto& handles = mHandles[i];
        handles.mELink.fade();
        handles.mSLink.fade();
    }
    mActiveMask = 0;
}

KSYS_VISIBILITY_HIDDEN const f32 sUnk_7102516320[2] = {0.25f, 0.6f};

XLink::CreateArg::CreateArg() = default;
XLink::RebuildArg::RebuildArg() = default;

void XLink::sub_7101230100(const RebuildArg& arg) {
    if (_48) {
        xlink2::UserInstance::RebuildArg rebuild_arg;
        rebuild_arg.rootMtx.setRawMtx(arg.rootMtx, 0);
        rebuild_arg.rootPos = arg.rootPos;
        rebuild_arg._18 = arg._10;
        _48->rebuild(rebuild_arg);
    }
    if (_50) {
        xlink2::UserInstance::RebuildArg rebuild_arg;
        rebuild_arg.rootMtx.setRawMtx(arg.rootMtx, 0);
        rebuild_arg.rootPos = arg.rootPos;
        rebuild_arg._18 = arg._10;
        _50->rebuild(rebuild_arg);
    }
}

// NON_MATCHING: Boolean argument masks are hoisted, increasing register saves and stack size.
void XLink::sub_710123445C(const char* name, bool a, bool b) {
    if (!mMiiSound)
        return;
    if (!mMiiSound->mHandle.requestedLoad()) {
        mMiiSound->sub_71012CD7A4();
        if (mMiiSound->mHandle.isBusy()) {
            mMiiSound->mPendingName.copy(name);
            mMiiSound->_119 = a;
            mMiiSound->_11a = b;
        }
    }
    if (mMiiSound->mHandle.isSuccess())
        sub_7101234334(name, a, false, b);
}

void XLink::setExtraLabels(const char* const* labels, s32 count) {
    if (mUser)
        mUser->setExtraLabels(labels, count);
}

void XLink::x_5() {
    if (_a0 && _cc.isOn(0x20))
        _a0->sub_7101235444();
}

void XLink::silenceFootsteps() {
    if (_a0)
        _a0->_1c.set(0x10);
}

void XLink::unsilenceFootsteps() {
    if (_a0)
        _a0->_1c.reset(0x10);
}

// NON_MATCHING: the final actor-flag Boolean return uses bit extraction instead of native branch returns.
bool XLink::sub_7101233168() {
    if (_cc.isOn(0x800))
        return true;
    return mActor && mActor->getActorFlags2().isOn(act::Actor::ActorFlag2::_40);
}

// Sound consumer12D03E8 uses the return as a multiplicative floating-point volume.
f32 XLink::sub_71012342A0() {
    if (_cc.isOn(0x4000)) {
        auto* manager = snd::SoundMgr::instance()->_a8;
        if (manager && manager->_49)
            return manager->sub_710104B558(mActor);
    }
    return -1.0f;
}

void XLink::sub_71012342D8(bool value) {
    _cc.change(0x40000, value);
    _cc.set(0x20000);
}

bool XLink::sub_71012342F8() {
    if (_cc.isOn(0x2000000) || _cc.isOnAll(0x1800))
        return true;
    return mActor && mActor->getActorFlags2().isOn(act::Actor::ActorFlag2::_40);
}

act::ai::RootAi* XLink::getRootAi() const {
    return mActor ? mActor->getRootAi() : nullptr;
}

gsys::ModelAnimation* XLink::getModelAnimation() const {
    return mModel ? mModel->getAnimation() : nullptr;
}

as::ASList* XLink::getASList() const {
    return mActor ? mActor->getASList() : nullptr;
}

void XLink::sub_710123051C(aal::IAssetInfoReadable* reader) {
    if (_50)
        _50->setAssetInfoReader(reader);
}

void XLink::prepareDelete() {
    _cc.setBit(10);
    mUser->mXLink = nullptr;
    if (_48) {
        _48->fadeIfLoopEffect();
        _48->mBitFlag.setBit(3);
    }
    if (_50) {
        _50->fadeIfLoopSound();
        sub_71012305AC();
        _50->mBitFlag.setBit(3);
    } else {
        _cc.setBit(21);
    }
}

// NON_MATCHING: fading-list bound scheduling and loop register allocation.
void XLink::sub_71012305AC() {
    for (auto& event : *_50->getEventList()) {
        for (auto& executor : event.getAliveAssetExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (!handle->isPaused() && !handle->isVirtualized()) {
                auto* source = handle->getSoundSource();
                if (!source || !source->isInnerPaused())
                    continue;
            }
            handle->stop(-1.0f, 0.0f);
        }
        for (auto& executor : event.getFadeBySystemExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (!handle->isPaused() && !handle->isVirtualized()) {
                auto* source = handle->getSoundSource();
                if (!source || !source->isInnerPaused())
                    continue;
            }
            handle->stop(-1.0f, 0.0f);
        }
    }
}

// NON_MATCHING: fading-list bound scheduling, loop registers and lock stack slot.
void XLink::sub_7101230968() {
    auto* user = _50;
    if (!user)
        return;
    sead::ScopedLock<xlink2::ILockProxy> lock(xlink2::SystemSLink::sLockProxy);
    for (auto& event : *user->getEventList()) {
        for (auto& executor : event.getAliveAssetExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (handle->getSoundGroupName().findIndex("Voice") != -1)
                handle->stop(-1.0f, 0.0f);
        }
        for (auto& executor : event.getFadeBySystemExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (handle->getSoundGroupName().findIndex("Voice") != -1)
                handle->stop(-1.0f, 0.0f);
        }
    }
}

void XLink::sub_7101230E18() {
    if (_50) {
        _50->searchAndEmit("Disappear_Ancient");
        sub_7101230968();
        _cc.setBit(25);
    }
}

bool XLink::sub_7101230714() {
    if (_48 && _48->getEventList()->size() > 0) {
        _48->fadeIfLoopEffect();
        _48->postCalc();
        return false;
    }
    return true;
}

bool XLink::x_1() {
    if (_cc.isOnBit(9)) {
        if (_48 && _48->getEventList()->size() != 0)
            return true;
        if (_50 && _50->getEventList()->size() != 0)
            return true;
    }
    if (_48 && _48->getBitFlag().isOnBit(2))
        return true;
    if (_50 && _50->getBitFlag().isOnBit(2))
        return true;
    if (_48 && _48->isCurrentActionNeedToCalc())
        return true;
    if (_50 && _50->isCurrentActionNeedToCalc())
        return true;
    return false;
}

bool XLink::x_2() {
    if (_48 && _48->getEventList()->size() != 0)
        return false;
    if (_50 && _50->getEventList()->size() != 0)
        return false;
    return true;
}

void XLink::sub_7101230FC8(bool paused, bool skip_environment) {
    if (!_73.isZero())
        return;
    auto* user = _50;
    if (!user || user->getEventList()->size() == 0)
        return;
    auto* groups = aal::SystemAccessor::getGroupMgr();
    if (!groups)
        return;
    auto* world = groups->findGroup("World");
    aal::Group* env = nullptr;
    aal::Group* chemical = nullptr;
    if (skip_environment) {
        env = groups->findGroup("Env");
        chemical = groups->findGroup("Chemical");
    }
    sead::ScopedLock<xlink2::ILockProxy> lock(xlink2::SystemSLink::sLockProxy);
    for (auto& event : *user->getEventList()) {
        for (auto& executor : event.getAliveAssetExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            auto* group = handle->getSoundGroup();
            if (aal::GroupMgr::isUnderAncestorOrSelf(group, env) ||
                aal::GroupMgr::isUnderAncestorOrSelf(group, chemical) ||
                !aal::GroupMgr::isUnderAncestorOrSelf(group, world))
                continue;
            if (_50->getResourceAccessor().getCustomParamValueBool(12, *executor.getAssetCallTable()))
                continue;
            handle->pause(sead::BitFlag8(2), paused, 0.1f);
        }
    }
}

void XLink::sub_71012311D8(bool paused) {
    sub_7101230FC8(paused, false);
}

void XLink::x_4(bool paused) {
    if (paused) {
        if (!_cc.isOnBit(8)) {
            sub_7101230FC8(true, true);
            _cc.setBit(8);
        }
    } else if (_cc.isOnBit(8)) {
        sub_7101230FC8(false, true);
        _cc.resetBit(8);
    }
}

void XLink::toggle(MaskBit bit) {
    if (!_73.isOnBit(bit))
        return;
    const bool was_set = !_73.isZero();
    _73.resetBit(bit);
    if (!was_set || !_73.isZero())
        return;
    if (_48)
        _48->setIsActive(true);
    if (_50)
        _50->setIsActive(true);
}

void XLink::setMask(MaskBit bit) {
    if (_73.isOnBit(bit))
        return;
    if (_73.isZero()) {
        _73.setDirect(sead::BitFlag8::makeMask(bit));
        sleep_();
    }
    _73.setBit(bit);
}

void XLink::sleep(MaskBit bit) {
    if (_73.isOnBit(bit))
        return;
    if (_73.isZero()) {
        if (getSceneStatus() == 4) {
            _73.setBit(bit);
            sleep_();
        } else {
            Manager::instance()->queueSleep(this);
        }
    }
    _73.setBit(bit);
}

void XLink::sleep_() {
    if (_73.isZero())
        return;
    if (_48 && !_48->getBitFlag().isOnBit(1)) {
        _48->postCalc();
        _48->sleep();
    }
    if (!_50 || _50->getBitFlag().isOnBit(1))
        return;
    sub_71012305AC();
    _50->postCalc();
    _50->sleep();
    if (mMiiSound && mMiiSound->mHandle.requestedLoad())
        mMiiSound->requestUnloadMaybe();
}

void XLink::sleepELink() {
    if (_48 && !_48->getBitFlag().isOnBit(1)) {
        _48->postCalc();
        _48->sleep();
    }
}

void XLink::resetELinkEvents() {
    if (_48)
        _48->killAll();
}

void XLink::sub_71012313DC(u32 property, s32 value, bool force) {
    if (_48 && (force || _48->isPropertyAssigned(property)))
        _48->setPropertyValue(property, value);
    if (_50 && (force || _50->isPropertyAssigned(property)))
        _50->setPropertyValue(property, value);
}

void XLink::sub_7101231468(u32 property, f32 value, bool force) {
    if (_48 && (force || _48->isPropertyAssigned(property)))
        _48->setPropertyValue(property, value);
    if (_50 && (force || _50->isPropertyAssigned(property)))
        _50->setPropertyValue(property, value);
}

}  // namespace ksys::xlink
