#include "Game/gameHorseMgr.h"
#include <prim/seadScopedLock.h>
#include <prim/seadStringUtil.h>
#include "Game/UI/euiMessageMgr.h"
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtManager.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/System/PlayReportMgr.h"

namespace uking {

HorseMgr::HorseMgr() : _e0(), mReinitSlot(this, &HorseMgr::onGameDataReinit) {
    _180 = _184 = _188 = _18c = _190 = _194 = _198 = _19c = _1a0 = _1a4 = _1a8 = _1ac = _1b0 =
        ksys::gdt::InvalidHandle;
}


SEAD_SINGLETON_DISPOSER_IMPL(HorseMgr)

// 0x7100e89040: whether no owned horse or registered amiibo hash matches `name`.
bool HorseMgr::isUnregisteredHorseAmiibo(const sead::SafeString& name) {
    if (name.isEmpty())
        return false;
    for (s32 i = 0; i < 5; ++i) {
        const char* hash = nullptr;
        if (ksys::gdt::Manager::instance()->getParam().get().getStr64(&hash, "Horse_AmiiboUidHash", i)) {
            if (name == hash)
                return false;
        }
    }
    for (auto& link : _e0) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&link, &accessor)) {
            if (act::sub_7100E6EDFC(accessor) == name && !accessor.isStateSleep())
                return false;
        }
    }
    return true;
}

// 0x7100e892d0: stores the amiibo uid hash on the new horse, replaces the horse linked in _e0 that carried the
// same hash, moves a dead horse carrying the hash up the dead-horse records and records the hash in the ten
// Horse_UsedAmiiboUidHash slots.
// NON_MATCHING: the link loop keeps a 32-bit counter and sign-extends it into the _e0 index (we widen the counter to
// 64 bits); the used-hash loop's compare block is laid out before the loop body in the original.
void HorseMgr::registerAmiiboMaybe(act::HorseBase* horse, const sead::SafeString& uid_hash) {
    using ksys::gdt::Manager;
    if (!horse || uid_hash.isEmpty())
        return;

    horse->_c00.copy(uid_hash);

    bool registered = false;
    for (u32 i = 0; i < 10; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_e0[i], &accessor)) {
            if (act::sub_7100E6EDFC(accessor) == uid_hash) {
                // The original checks the sleep state and drops the result.
                accessor.isStateSleep();
                accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                _e0[i].reset();
            }
        }
        if (!registered && !_e0[i].hasProc()) {
            _e0[i].acquire(horse, false);
            registered = true;
        }
    }
    if (!registered)
        _e0[0].acquire(horse, false);

    for (s32 i = 0; i < 5; ++i) {
        const char* hash = nullptr;
        if (Manager::instance()->getParam().get1().getStr64(&hash, "DeadHorse_AmiiboUidHash", i)) {
            if (uid_hash == hash) {
                sub_7100E8720C(i);
                --i;
            }
        }
    }

    if (!isFlagOn(Flag::_0))
        return;

    for (s32 i = 0; i < 10; ++i) {
        const char* hash = nullptr;
        if (Manager::instance()->getParam().get().getStr64(&hash, "Horse_UsedAmiiboUidHash", i) &&
            hash[0] != '\0') {
            if (uid_hash == hash)
                return;
        } else if (Manager::instance()->setStr64(uid_hash.cstr(), "Horse_UsedAmiiboUidHash", i)) {
            return;
        }
    }

    for (s32 i = 1; i < 10; ++i) {
        const char* hash = nullptr;
        if (Manager::instance()->getParam().get().getStr64(&hash, "Horse_UsedAmiiboUidHash", i))
            Manager::instance()->setStr64(hash, "Horse_UsedAmiiboUidHash", i - 1);
    }
    Manager::instance()->setStr64(uid_hash.cstr(), "Horse_UsedAmiiboUidHash", 9);
}

// NON_MATCHING: The compiler tail-calls hasProcById rather than normalizing its bool result.
void HorseMgr::setHorsePosForMap() {
    sead::Vector3f pos;
    if (ksys::gdt::Manager::instance()->getParam().get().getVec3f(&pos, "Horse_Pos"))
        ksys::gdt::Manager::instance()->setVec3f(pos, "Horse_Pos_For_Map");
}

void HorseMgr::onGameDataReinit(ksys::gdt::Manager::ReinitEvent* event) {
    initHorseGameDataIters();
}

HorseMgr::~HorseMgr() {
    _80.deleteProc();
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->removeReinitCallback(mReinitSlot);
}

void HorseMgr::initHorseGameDataItersAndStuff(sead::Heap* heap, bool on) {
    _228.change(1 << Flag(Flag::_0), on);
    initHorseGameDataIters();
    ksys::gdt::Manager::instance()->addReinitCallback(mReinitSlot);
}

void HorseMgr::initHorseGameDataIters() {
    _180 = ksys::gdt::Manager::instance()->getVec3fHandle("Horse_Pos");
    _184 = ksys::gdt::Manager::instance()->getF32Handle("Horse_RotY");
    _188 = ksys::gdt::Manager::instance()->getVec3fHandle("Horse_Pos_For_Map");
    _18c = ksys::gdt::Manager::instance()->getVec3fHandle("Last_Ridden_Horse_Pos");
    _190 = ksys::gdt::Manager::instance()->getF32Handle("Last_Ridden_Horse_RotY");
    _194 = ksys::gdt::Manager::instance()->getS32Handle("Horse_Extra_Charge_Num");
    _198 = ksys::gdt::Manager::instance()->getS32Handle("Last_Ridden_Horse_Extra_Charge_Num");
    _19c = ksys::gdt::Manager::instance()->getF32ArrayHandle("Horse_Familiarity");
    _1a0 = ksys::gdt::Manager::instance()->getS32Handle("Horse_ActiveIndex");
    _1a4 = ksys::gdt::Manager::instance()->getStr64ArrayHandle("Horse_ActorName");
    _1a8 = ksys::gdt::Manager::instance()->getBoolHandle("Horse_Is_LastRidden_Owned");
    _1ac = ksys::gdt::Manager::instance()->getBoolHandle("Horse_Large_Exists");
    _1b0 = ksys::gdt::Manager::instance()->getBoolHandle("Horse_Zelda_Exists");
}

bool HorseMgr::isLinkedToActor(ksys::act::Actor* actor) {
    if (actor && _30.hasProcById(actor))
        return true;
    return false;
}

ksys::act::Actor* HorseMgr::getRegisteringHorseActor() const {
    return sead::DynamicCast<ksys::act::Actor>(_30.getProc(nullptr));
}

// NON_MATCHING: the original shares one stack slot between the two SafeString temporaries.
bool HorseMgr::isAmiiboUsed(const sead::SafeString& uid_hash) {
    for (s32 i = 0; i < 10; ++i) {
        const char* hash = nullptr;
        if (ksys::gdt::Manager::instance()->getParam().get().getStr64(&hash, "Horse_UsedAmiiboUidHash", i) &&
            uid_hash == hash) {
            return true;
        }
    }
    return false;
}

// NON_MATCHING: The compiler tail-calls hasProcById rather than normalizing its bool result.
bool HorseMgr::sub_7100E84AB8(ksys::act::Actor* actor) {
    if (actor && mOwnedHorse.hasProcById(actor))
        return true;
    return false;
}

// 0x7100e88bcc: registers `actor` as the horse being received: writes its data to the Horse_* flags of
// record 5 and squares its traverse distance into _dc.
void HorseMgr::setRiddenHorseMaybe(ksys::act::Actor* actor) {
    if (!actor) {
        _30.reset();
        return;
    }
    if (!actor->getHorseOptionsMaybe())
        return;
    if (_30.hasProcById(actor))
        return;
    _30.acquire(actor, false);

    HorseData data;
    data.actorName = actor->getName().cstr();
    if (sead::IsDerivedFrom<act::HorseBase>(actor)) {
        auto* horse = static_cast<act::HorseBase*>(actor);
        const sead::SafeString* mane_name;
        {
            auto lock = sead::makeScopedLock(horse->_890);
            mane_name = &horse->_8d0._40;
        }
        data.maneName = mane_name->cstr();
        data.amiiboUidHash = horse->_c00.cstr();
        data.familiarity = horse->sub_7100E6AD4C();
        data.collarType = horse->_b78;
        data.footType = horse->_b7c;
    }
    sub_7100E8533C(&data, 5);

    const sead::SafeString name(data.actorName);
    if (!ksys::map::PlacementMgr::instance() || !ksys::map::PlacementMgr::instance()->mPlacementActors)
        return;
    const f32 distance = ksys::map::getActorTraverseDist(name, 1.0f);
    _dc = distance * distance;
}

bool HorseMgr::sub_7100E8527C(ksys::act::BaseProcLink* link, const sead::SafeString& name,
                                      bool flag) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(link, &accessor))
        return false;
    if (!act::sub_7100E6DC50(accessor))
        return false;
    if (mOwnedHorse == *link)
        return true;
    if (!sub_7100E84AE4(accessor, name, flag))
        return false;
    _70 = *link;
    return true;
}

// NON_MATCHING: one instruction is scheduled differently (the accessor's last field is zeroed before
// the acquire call; the target after it).
bool HorseMgr::sub_7100E84A04(ksys::act::Actor* actor, const sead::SafeString& name, bool flag) {
    if (!actor)
        return false;
    if (mOwnedHorse.hasProcById(actor))
        return true;

    ksys::act::ActorLinkConstDataAccess accessor(actor);
    if (!sub_7100E84AE4(accessor, name, flag))
        return false;
    sub_7100E84F0C(actor);
    _d4 = -1;
    return true;
}

// The mane name groups sub_7100E84AE4 picks the record's mane from (definitions below).
extern const sead::SafeString sUnk_7102603C98[4];
extern const sead::SafeString sUnk_7102603CD8[2];

// 0x7100e84ae4: the registration body sub_7100E84A04 runs with the acquired horse accessor: fills the
// horse record of the next free slot from the horse, writes it, reports the registration and sets the
// RiddenAnimalType flags. False when all five records are in use.
// NON_MATCHING: the original converts the horse type through a SEAD_ENUM temporary for the mane group
// select (an extra stack round trip) and colours the data base / name registers differently; same calls.
bool HorseMgr::sub_7100E84AE4(const ksys::act::ActorLinkConstDataAccess& accessor,
                              const sead::SafeString& name, bool flag) {
    const s32 index = getNumRegisteredHorses();
    if (u32(index) > 4)
        return false;

    HorseData data;
    data.actorName = accessor.getName().cstr();
    data.userName = name.cstr();
    data.maneName =
        (act::sub_7100E6ECC4(accessor) == 6 ? sUnk_7102603CD8[0] : sUnk_7102603C98[0]).cstr();
    data.reinsName = getHorseReinsName(act::sub_7100E6ECC4(accessor)).cstr();
    data.saddleName = getHorseSaddleName(act::sub_7100E6ECC4(accessor)).cstr();
    data.amiiboUidHash = act::sub_7100E6EDFC(accessor).cstr();

    if (act::sub_7100E6ECC4(accessor) == 4) {
        sead::FormatFixedSafeString<256> set_name("ActorType/%s", accessor.getProfile().cstr());
        eui::MessageSet* set = eui::MessageMgr::instance()->getMessageSet(set_name);
        if (set) {
            sead::FormatFixedSafeString<256> label("%s_Name", data.actorName);
            eui::MessageString message = set->tryFindMessage(label.cstr());
            if (message.getString()) {
                sead::FixedSafeString<256> text;
                sead::StringUtil::convertUtf16ToUtf8(text.getBuffer(), text.getBufferSize(),
                                                    message.getString(), -1);
                if (!text.isEmpty())
                    data.userName = text.cstr();
            }
        }
    }

    sub_7100E8533C(&data, index);
    ksys::PlayReportMgr::instance()->reportDebug("HorseRegistered", accessor.getName());
    _d4 = index;
    if (flag)
        setFlagOn(Flag::_1);
    else
        setFlagOff(Flag::_1);

    switch (RiddenAnimalType(act::sub_7100E6ECC4(accessor))) {
    case RiddenAnimalType::_6:
        setFlagOn(Flag::_5);
        break;
    case RiddenAnimalType::_3:
        setFlagOn(Flag::_6);
        break;
    }
    return true;
}

bool HorseMgr::sub_7100E85334(const ksys::act::BaseProcLink& link) const {
    return mOwnedHorse == link;
}

// The validity test of a horse record that x_3, sub_7100E8883C and sub_7100E8612C's callee all inline; it is
// the original's own (all five names non-empty, familiarity in [0, 1], collar and foot type not negative).
static bool isValid(const HorseMgr::HorseData& data) {
    return !sead::SafeString(data.actorName).isEmpty() && !sead::SafeString(data.userName).isEmpty() &&
           !sead::SafeString(data.reinsName).isEmpty() && !sead::SafeString(data.saddleName).isEmpty() &&
           !sead::SafeString(data.maneName).isEmpty() && data.familiarity <= 1.0f &&
           data.familiarity >= 0.0f && (data.collarType | data.footType) >= 0;
}

// 0x7100e84f0c: the post-registration step sub_7100E84A04 runs on the new horse: copies the live horse's
// mane name, familiarity and collar / foot type into record _d4 and writes the record back, then links it as
// the owned horse, writes Horse_ActiveIndex and creates its reins / saddle actors.
// NON_MATCHING: both isFlagOn tests order the `and` operands flags-first (commutative; see isFlagOn).
void HorseMgr::sub_7100E84F0C(ksys::act::Actor* actor) {
    if (!actor) {
        sub_7100E857CC(_d4, true, false, -1);
    } else {
        HorseData data;
        if (sub_7100E854EC(&data, _d4) && isValid(data)) {
            auto* horse = static_cast<act::HorseBase*>(actor);
            const sead::SafeString* mane_name;
            {
                auto lock = sead::makeScopedLock(horse->_890);
                mane_name = &horse->_8d0._40;
            }
            data.maneName = mane_name->cstr();
            data.familiarity = horse->sub_7100E6AD4C();
            data.collarType = horse->_b78;
            data.footType = horse->_b7c;
            sub_7100E8533C(&data, _d4);

            if (isFlagOn(Flag::_1)) {
                actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            } else {
                ksys::act::BaseProc* proc = mOwnedHorse.getProc(nullptr, nullptr);
                if (sead::IsDerivedFrom<act::HorseBase>(proc))
                    proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                mOwnedHorse.acquire(actor, false);

                {
                    const sead::SafeString name(data.actorName);
                    if (ksys::map::PlacementMgr::instance() &&
                        ksys::map::PlacementMgr::instance()->mPlacementActors) {
                        const f32 distance = ksys::map::getActorTraverseDist(name, 1.0f);
                        _d8 = distance * distance;
                    }
                }

                _d0 = _d4;
                if (isFlagOn(Flag::_0))
                    ksys::gdt::Manager::instance()->setS32(_d4, _1a0);

                horse->sub_7100E6E518(data.reinsName, _c8);
                horse->sub_7100E6E7DC(data.saddleName, _c8);
            }
        }
    }
    setFlagOff(Flag::_1);
}

// 0x7100e83cd4: polls the two creation handles: _80 (the selected horse, record _d0) and _90 (the
// last-ridden horse, record 5). A ready actor that is not a horse is deleted; otherwise it is linked and
// its record is applied. True while one of the handles is not ready yet.
// NON_MATCHING: same instructions and block count; the isValid chain's last compare branches to the valid
// body, so the invalid-record block is laid out inline and the body out of line (target: the reverse).
bool HorseMgr::isGenerating() {
    if (_80.isAllocatedOrFailed() && !_80.hasProcCreationFailed()) {
        if (!_80.isProcReady())
            return true;

        HorseData data;
        if (x_8(&data, _d0) && isValid(data)) {
            auto* proc = _80.releaseAndWakeProc();
            if (!sead::IsDerivedFrom<act::HorseBase>(proc)) {
                auto lock = sead::makeScopedLock(_230);
                _d0 = -1;
                proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            } else {
                auto* horse = static_cast<act::HorseBase*>(proc);
                mOwnedHorse.acquire(horse, false);
                sub_7100E842F8(horse, horse->getHorseOptionsMaybe(), &data, true);

                bool is_ride = false;
                bool last_ridden = false;
                ksys::gdt::Manager::instance()->getParam().get().getBool(&is_ride, "Horse_IsRide");
                ksys::gdt::Manager::instance()->getBool(_1a8, &last_ridden);
                if (!is_ride || !last_ridden)
                    horse->sleep(ksys::act::BaseProc::SleepWakeReason::_0);

                {
                    const sead::SafeString name(data.actorName);
                    if (ksys::map::PlacementMgr::instance() &&
                        ksys::map::PlacementMgr::instance()->mPlacementActors) {
                        const f32 distance = ksys::map::getActorTraverseDist(name, 1.0f);
                        _d8 = distance * distance;
                    }
                }

                if (last_ridden)
                    _30.acquire(horse, false);
            }
        } else {
            auto lock = sead::makeScopedLock(_230);
            _d0 = -1;
            _80.deleteProc();
        }
    }

    if (_90.isAllocatedOrFailed() && !_90.hasProcCreationFailed()) {
        if (!_90.isProcReady())
            return true;

        HorseData data;
        if (x_8(&data, 5) && data.actorName[0] != sead::SafeString::cNullChar) {
            auto* proc = _90.releaseAndWakeProc();
            if (!sead::IsDerivedFrom<ksys::act::Actor>(proc)) {
                proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                return false;
            }
            auto* actor = static_cast<ksys::act::Actor*>(proc);

            _30.acquire(actor, false);
            auto* horse = sead::DynamicCast<act::HorseBase>(actor);
            sub_7100E842F8(horse, actor->getHorseOptionsMaybe(), &data, false);

            bool is_ride = false;
            ksys::gdt::Manager::instance()->getParam().get().getBool(&is_ride, "Horse_IsRide");
            if (!is_ride)
                actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);

            {
                const sead::SafeString name(data.actorName);
                if (ksys::map::PlacementMgr::instance() &&
                    ksys::map::PlacementMgr::instance()->mPlacementActors) {
                    const f32 distance = ksys::map::getActorTraverseDist(name, 1.0f);
                    _dc = distance * distance;
                }
            }
        } else {
            _90.deleteProc();
        }
    }

    return false;
}

// 0x7100e83a08 (CSV x_8): the Horse_* flags of horse `index` through the regular getters.
// NON_MATCHING: register allocation (this / result registers swapped) and the placement of the first `and`.
bool HorseMgr::x_8(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    bool ok = Manager::instance()->getStr64(_1a4, &data->actorName, index);
    ok &= Manager::instance()->getF32(_19c, &data->familiarity, index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->userName, "Horse_UserName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->reinsName, "Horse_ReinsName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->saddleName, "Horse_SaddleName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->maneName, "Horse_ManeName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->amiiboUidHash, "Horse_AmiiboUidHash", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->collarType, "Horse_CollarType", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->footType, "Horse_FootType", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->rideTimeSec, "Horse_RideTimeSec", index);
    ok &= Manager::instance()->getParam().get().getBool(&data->familiarityChecked,
                                                        "Horse_IsFamiliarityChecked", index);
    return ok;
}

// 0x7100e854ec: the Horse_* flags of horse `index`; the first two are read through their handles (buffer 1, failing
// while `_40000` is set), the others by name.
// NON_MATCHING: the original lays out the handle unwrapping of the first two reads differently (the direct path first).
bool HorseMgr::sub_7100E854EC(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    bool ok = Manager::instance()->getStr64Buffer1(_1a4, &data->actorName, index);
    ok &= Manager::instance()->getF32Buffer1(_19c, &data->familiarity, index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->userName, "Horse_UserName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->reinsName, "Horse_ReinsName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->saddleName, "Horse_SaddleName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->maneName, "Horse_ManeName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->amiiboUidHash, "Horse_AmiiboUidHash",
                                                          index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->collarType, "Horse_CollarType", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->footType, "Horse_FootType", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->rideTimeSec, "Horse_RideTimeSec", index);
    ok &= Manager::instance()->getParam().get1().getBool(&data->familiarityChecked,
                                                         "Horse_IsFamiliarityChecked", index);
    return ok;
}

// NON_MATCHING: only the operand order of the `and` on the flags differs (see isFlagOn).
void HorseMgr::sub_7100E8533C(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    if (!isFlagOn(Flag::_0))
        return;
    Manager::instance()->setStr64(data->actorName, _1a4, index);
    Manager::instance()->setF32(data->familiarity, _19c, index);
    Manager::instance()->setStr64(data->userName, "Horse_UserName", index);
    Manager::instance()->setStr64(data->reinsName, "Horse_ReinsName", index);
    Manager::instance()->setStr64(data->saddleName, "Horse_SaddleName", index);
    Manager::instance()->setStr64(data->maneName, "Horse_ManeName", index);
    Manager::instance()->setStr64(data->amiiboUidHash, "Horse_AmiiboUidHash", index);
    Manager::instance()->setS32(data->collarType, "Horse_CollarType", index);
    Manager::instance()->setS32(data->footType, "Horse_FootType", index);
    Manager::instance()->setS32(data->rideTimeSec, "Horse_RideTimeSec", index);
    Manager::instance()->setBool(data->familiarityChecked, "Horse_IsFamiliarityChecked", index);
}

// NON_MATCHING: only the isOnBit `and` operand order differs (the original has the flags first; see
// isFlagOn above).
// 0x7100e85bc0 (NPC receive horse): deletes the owned horse (and any pending create handle), clears the
// selected index and resets Horse_ActiveIndex.
void HorseMgr::sub_7100E85BC0() {
    ksys::act::ActorLinkConstDataAccess accessor;
    auto lock = sead::makeScopedLock(_230);
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        mOwnedHorse.reset();
        _80.deleteProc();
    } else if (_80.isAllocatedOrFailed()) {
        _80.deleteProc();
    } else if (_d0 == -1) {
        return;
    }
    _d0 = -1;
    if (isFlagOn(Flag::_0))
        ksys::gdt::Manager::instance()->setS32(-1, _1a0);
}

void HorseMgr::sub_7100E8998C(s32 mode) {
    if (mode != 2)
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    if (!(_30 == mOwnedHorse) && ksys::act::acquireActor(&_30, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    setFlagOn(Flag::_4);
}

// NON_MATCHING: the original also stores the unused RiddenAnimalType values (the x() result, 6) on the stack.
void HorseMgr::x_0(act::HorseBase* horse) {
    horse->x();
    if (_40.hasProcById(horse))
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&_40, &accessor))
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    _40.acquire(horse, false);
}

// NON_MATCHING: the original also stores the unused RiddenAnimalType values (the x() result, 3) on the stack.
void HorseMgr::x_2(act::HorseBase* horse) {
    horse->x();
    if (_50.hasProcById(horse))
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&_50, &accessor))
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    _50.acquire(horse, false);
}

void HorseMgr::sub_7100E89A44() {
    setFlagOff(Flag::_4);
}

void HorseMgr::sub_7100E89A70(s32 seconds, bool selected) {
    s32 index;
    if (selected) {
        index = _d0;
        if (index < 0)
            return;
    } else {
        index = 5;
    }
    s32 time = 0;
    if (ksys::gdt::Manager::instance()->getParam().get().getS32(&time, "Horse_RideTimeSec", index))
        ksys::gdt::Manager::instance()->setS32(time + seconds, "Horse_RideTimeSec", index);
}

void HorseMgr::sub_7100E89DAC(ksys::act::BaseProcLink* link, bool flag, ksys::gdt::FlagHandle handle) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(link, &accessor)) {
        if (accessor.getMapObject())
            ksys::gdt::Manager::instance()->setBool(false, handle);
        else
            ksys::gdt::Manager::instance()->setBool(flag || accessor.isStateCalc(), handle);
    } else {
        ksys::gdt::Manager::instance()->setBool(flag, handle);
    }
}

// 0x7100e86f80: the DeadHorse_* flags of dead horse `index` through buffer 0 (the other dead-horse
// reader, sub_7100E89B20, uses buffer 1).
bool HorseMgr::sub_7100E86F80(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    bool ok = Manager::instance()->getParam().get().getStr64(&data->actorName, "DeadHorse_ActorName", index);
    ok &= Manager::instance()->getParam().get().getF32(&data->familiarity, "DeadHorse_Familiarity", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->collarType, "DeadHorse_CollarType", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->footType, "DeadHorse_FootType", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->userName, "DeadHorse_UserName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->reinsName, "DeadHorse_ReinsName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->saddleName, "DeadHorse_SaddleName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->maneName, "DeadHorse_ManeName", index);
    ok &= Manager::instance()->getParam().get().getStr64(&data->amiiboUidHash, "DeadHorse_AmiiboUidHash",
                                                          index);
    ok &= Manager::instance()->getParam().get().getS32(&data->rideTimeSec, "DeadHorse_RideTimeSec", index);
    ok &= Manager::instance()->getParam().get().getS32(&data->deadCause, "DeadHorse_DeadCause", index);
    return ok;
}

// 0x7100e89b20: the DeadHorse_* flags of dead horse `index` (no `this`).
bool HorseMgr::sub_7100E89B20(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    bool ok = Manager::instance()->getParam().get1().getStr64(&data->actorName, "DeadHorse_ActorName", index);
    ok &= Manager::instance()->getParam().get1().getF32(&data->familiarity, "DeadHorse_Familiarity", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->collarType, "DeadHorse_CollarType", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->footType, "DeadHorse_FootType", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->userName, "DeadHorse_UserName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->reinsName, "DeadHorse_ReinsName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->saddleName, "DeadHorse_SaddleName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->maneName, "DeadHorse_ManeName", index);
    ok &= Manager::instance()->getParam().get1().getStr64(&data->amiiboUidHash, "DeadHorse_AmiiboUidHash",
                                                          index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->rideTimeSec, "DeadHorse_RideTimeSec", index);
    ok &= Manager::instance()->getParam().get1().getS32(&data->deadCause, "DeadHorse_DeadCause", index);
    return ok;
}

// NON_MATCHING: only the operand order of the `and` on the flags differs (see isFlagOn).
void HorseMgr::sub_7100E88A08(HorseData* data, s32 index) {
    using ksys::gdt::Manager;
    if (!isFlagOn(Flag::_0))
        return;
    Manager::instance()->setStr64(data->actorName, "DeadHorse_ActorName", index);
    Manager::instance()->setF32(data->familiarity, "DeadHorse_Familiarity", index);
    Manager::instance()->setS32(data->collarType, "DeadHorse_CollarType", index);
    Manager::instance()->setS32(data->footType, "DeadHorse_FootType", index);
    Manager::instance()->setStr64(data->userName, "DeadHorse_UserName", index);
    Manager::instance()->setStr64(data->reinsName, "DeadHorse_ReinsName", index);
    Manager::instance()->setStr64(data->saddleName, "DeadHorse_SaddleName", index);
    Manager::instance()->setStr64(data->maneName, "DeadHorse_ManeName", index);
    Manager::instance()->setStr64(data->amiiboUidHash, "DeadHorse_AmiiboUidHash", index);
    Manager::instance()->setS32(data->rideTimeSec, "DeadHorse_RideTimeSec", index);
    Manager::instance()->setS32(data->deadCause, "DeadHorse_DeadCause", index);
}

// 0x7100e8720c: moves the dead horse records up one slot from `index` (the last one is cleared).
void HorseMgr::sub_7100E8720C(s32 index) {
    if (!isFlagOn(Flag::_0) || u32(index) >= 5)
        return;
    for (s32 i = index; i < 5; ++i) {
        HorseData data;
        if (i + 1 < 5)
            sub_7100E89B20(&data, i + 1);
        sub_7100E88A08(&data, i);
    }
}

// 0x7100e86340: picks the horse with the highest familiarity out of the five records (ties: the one with the highest
// gear top charge count). The original compares the charge count of the best record with itself.
// NON_MATCHING: the original indexes the best record with a clamped index (`index < 5 ? index : 0`, like
// SafeArray::operator[]) which a HorseData* parameter cannot express; the loop registers differ because of it.
bool HorseMgr::sub_7100E86340(HorseData* data, s32* index) {
    s32 best = -1;
    s32 best_charge = -1;
    for (s32 i = 0; i != 5; ++i) {
        const HorseData& d = data[i];
        if (x_8(&data[i], i) && !sead::SafeString(d.actorName).isEmpty() &&
            !sead::SafeString(d.userName).isEmpty() && !sead::SafeString(d.reinsName).isEmpty() &&
            !sead::SafeString(d.saddleName).isEmpty() && !sead::SafeString(d.maneName).isEmpty() &&
            d.familiarity >= 0.0f && d.familiarity <= 1.0f && d.collarType >= 0 && d.footType >= 0) {
            if (best < 0) {
                best = i;
            } else {
                const HorseData& b = data[best];
                if (d.familiarity == b.familiarity) {
                    if (best_charge < 0)
                        best_charge = ksys::act::getHorseGearTopChargeNum(ksys::act::InfoData::instance(),
                                                                         b.actorName);
                    const s32 charge =
                        ksys::act::getHorseGearTopChargeNum(ksys::act::InfoData::instance(), b.actorName);
                    if (charge > best_charge) {
                        best = i;
                        best_charge = charge;
                    }
                } else if (d.familiarity > b.familiarity) {
                    best = i;
                    best_charge = -1;
                }
            }
        }
    }
    if (best < 0)
        return false;
    *index = best;
    return true;
}

// NON_MATCHING: the original lays out the loop blocks differently (the early exits of the validity checks come
// after the success path) and has the flags first in the isOnBit `and`.
s32 HorseMgr::getNumRegisteredHorses() {
    s32 count = 5;
    if (isFlagOn(Flag::_0)) {
        count = 0;
        auto lock = sead::makeScopedLock(_230);
        for (s32 i = 0; i != 5; ++i) {
            HorseData data;
            if (!sub_7100E854EC(&data, i) || !isValid(data)) {
                if (i == _d0) {
                    _d0 = -1;
                    ksys::gdt::Manager::instance()->setS32(-1, _1a0);
                }
            } else {
                if (i != count) {
                    sub_7100E8533C(&data, count);
                    if (i == _d0) {
                        _d0 = count;
                        ksys::gdt::Manager::instance()->setS32(count, _1a0);
                    }
                }
                ++count;
            }
        }
    }
    return count;
}

// 0x7100e82768: creates the stage generator's horse unless the owned horse exists or the saved
// last-ridden-horse flag is set. The game data read's result is discarded by the original; only the
// value it writes is tested (logged as a discarded call).
// NON_MATCHING: the original keeps the shift base 1 in x22 and gives the flag temporaries and the bool
// separate stack slots (0x40 frame); ours rematerialises the 1 and reuses one slot (0x30 frame).
void HorseMgr::initAndCreateHorseForStageGen(sead::Heap* heap, bool flag) {
    if (mOwnedHorse.hasProc())
        return;
    getNumRegisteredHorses();
    bool found = x_4(RiddenAnimalType::_6, false) || x_5(RiddenAnimalType::_6, false);
    if (found)
        setFlagOn(Flag::_5);
    else
        setFlagOff(Flag::_5);
    found = x_4(RiddenAnimalType::_3, false) || x_5(RiddenAnimalType::_3, false);
    if (found)
        setFlagOn(Flag::_6);
    else
        setFlagOff(Flag::_6);
    x_6(heap);
    bool lastRidden = false;
    ksys::gdt::Manager::instance()->getBool(_1a8, &lastRidden);
    if (lastRidden)
        return;
    createHorse(heap, flag);
}

// 0x7100e830cc (CSV x_6): creates the horse for the stage generator from the selected horse record
// (Horse_ActiveIndex) at the saved last-ridden position and rotation.
// NON_MATCHING: the only difference is where the shared void-return epilogue is laid out (ours puts it
// after the fifth name check, the original after the final unlock), which costs one extra `b`.
void HorseMgr::x_6(sead::Heap* heap) {
    s32 index = -1;
    const bool ok = ksys::gdt::Manager::instance()->getS32(_1a0, &index);
    if (u32(index) > 4 || !ok)
        return;

    HorseData data;
    if (!x_8(&data, index) || !isValid(data))
        return;

    sead::Vector3f pos;
    if (!ksys::gdt::Manager::instance()->getVec3f(_180, &pos))
        return;

    f32 angle;
    if (!ksys::gdt::Manager::instance()->getF32(_184, &angle))
        angle = 0.0f;

    ksys::aoc::Manager::instance()->x(&pos, nullptr, nullptr);

    ksys::act::InstParamPack params;
    params->addPosition(pos);
    params->addRotation({0.0f, -angle, 0.0f});
    params->add(sead::SafeString(data.maneName), "HorseManeName");
    params->add(sead::SafeString(data.reinsName), "HorseReinsName");
    params->add(sead::SafeString(data.saddleName), "HorseSaddleName");
    params->add(true, "IsIncreaseSkeletalSlotNumLimit");

    if (ksys::act::ActorCreator::instance()->requestCreateActor(data.actorName, heap, &_80, &params,
                                                                nullptr, 1)) {
        auto lock = sead::makeScopedLock(_230);
        _d0 = index;
    }
}

// The reins / saddle name strings createHorse adds (defined with the tack name tables below).
extern const sead::SafeString sUnk_7102603D38;
extern const sead::SafeString sUnk_7102603D68;

// 0x7100e835c0 (CSV createHorse): creates the saved horse (record 5) at the last-ridden position. A
// horse of type 9 is not created unless `flag` is set: its saved name is cleared instead.
void HorseMgr::createHorse(sead::Heap* heap, bool flag) {
    HorseData data;
    if (!x_8(&data, 5) || data.actorName[0] == sead::SafeString::cNullChar)
        return;

    if (!flag && ksys::act::getHorseUnitRiddenAnimalType(ksys::act::InfoData::instance(),
                                                        data.actorName) == 9) {
        ksys::gdt::Manager::instance()->setStr64("", _1a4, 5);
        return;
    }

    sead::Vector3f pos;
    if (!ksys::gdt::Manager::instance()->getVec3f(_18c, &pos))
        return;

    f32 angle;
    if (!ksys::gdt::Manager::instance()->getF32(_190, &angle))
        angle = 0.0f;

    bool demo;
    if (!ksys::gdt::Manager::instance()->getParam().get().getBool(&demo, "IsPlayed_Demo146_0"))
        demo = false;

    ksys::aoc::Manager::instance()->x(&pos, nullptr, nullptr);

    ksys::act::InstParamPack params;
    params->addPosition(pos);
    params->addRotation({0.0f, -angle, 0.0f});
    if (demo) {
        params->add(sUnk_7102603D38, "HorseReinsName");
        params->add(sUnk_7102603D68, "HorseSaddleName");
    }

    ksys::act::ActorCreator::instance()->requestCreateActor(data.actorName, heap, &_90, &params,
                                                            nullptr, 1);
}

// 0x7100e857cc: removes horse `index` from the live records (see the header).
// NON_MATCHING: three residues: the original hoists the Flag temporary's stack spill above the index
// check, keeps a loop entry guard that our build folds away (index is already known to be <= 4), and
// orders the `and` of the flag test with the flags first (commutative; see TIPS). Same instruction
// count (253).
void HorseMgr::sub_7100E857CC(s32 index, bool a2, bool a3, s32 a4) {
    if (u32(index) > 4)
        return;
    if (!isFlagOn(Flag::_0))
        return;

    auto lock = sead::makeScopedLock(_230);
    u32 overflow = 0;
    if (a3) {
        s32 dead = getNumDeadHorsesRegistered();
        if (dead >= 5) {
            sub_7100E8720C(0);
            dead = 4;
            overflow = 1;
        }
        HorseData data;
        x_8(&data, index);
        data.deadCause = a4;
        sub_7100E88A08(&data, dead);
    }

    for (s32 i = index; i < 5; ++i) {
        HorseData data;
        if (i + 1 < 5)
            sub_7100E854EC(&data, i + 1);
        sub_7100E8533C(&data, i);
    }

    s32 selected = _d0;
    if (selected == index) {
        _d0 = -1;
        _80.deleteProc();
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
            if (a3) {
                _b0 = *accessor.getMessageTransceiverId();
            } else if (a2) {
                accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
        mOwnedHorse.reset();
        selected = _d0;
    } else if (selected > index) {
        --selected;
        _d0 = selected;
    }

    ksys::gdt::Manager::instance()->setS32(selected, _1a0);

    bool found = x_4(RiddenAnimalType::_6, true) || x_5(RiddenAnimalType::_6, overflow | a3);
    if (found)
        setFlagOn(Flag::_5);
    else
        setFlagOff(Flag::_5);

    found = x_4(RiddenAnimalType::_3, true) || x_5(RiddenAnimalType::_3, overflow | a3);
    if (found)
        setFlagOn(Flag::_6);
    else
        setFlagOff(Flag::_6);
}

// 0x7100e85cac: creates the horse of record `index` at `pos` on `heap` (NPCDeliverHorse::oneShot_): replaces
// the owned horse, adds the position and tack names to the parameter pack and sets the delivery flag; the
// actor passed in (if any) becomes the linked delivery actor.
// NON_MATCHING: same calls and blocks; our invalid-record join is laid out before the body (the target
// branches past it), the flag mask is materialised per arm, and the last flag test orders the `and`
// operands flags-first (commutative).
void HorseMgr::sub_7100E85CAC(sead::Heap* heap, s32 index, const sead::Vector3f& pos,
                              ksys::act::Actor* actor, bool flag) {
    auto lock = sead::makeScopedLock(_230);

    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        mOwnedHorse.reset();
    }

    HorseData data;
    if (!x_8(&data, index) || !isValid(data))
        return;

    ksys::act::InstParamPack params;
    params->addPosition(pos);
    params->add(sead::SafeString(data.maneName), "HorseManeName");
    params->add(sead::SafeString(data.reinsName), "HorseReinsName");
    params->add(sead::SafeString(data.saddleName), "HorseSaddleName");
    params->add(true, "IsIncreaseSkeletalSlotNumLimit");

    ksys::act::ActorCreator::instance()->requestCreateActor(data.actorName, heap, &_80, &params,
                                                            nullptr, 1);

    if (flag)
        setFlagOn(Flag::_8);
    else
        setFlagOff(Flag::_8);

    if (actor)
        _a0.acquire(actor, false);
    else
        _a0.reset();

    _d0 = index;

    if (isFlagOn(Flag::_0))
        ksys::gdt::Manager::instance()->setS32(index, _1a0);
}

act::HorseBase* HorseMgr::getOwnedHorseBase() const {
    return sead::DynamicCast<act::HorseBase>(mOwnedHorse.getProc(nullptr));
}

void HorseMgr::sub_7100E887B8(ksys::act::BaseProc* proc, bool a2, bool a3, s32 a4) {
    if (!proc || !mOwnedHorse.hasProcById(proc))
        return;
    auto lock = sead::makeScopedLock(_230);
    sub_7100E857CC(_d0, a2, a3, a4);
}

// NON_MATCHING: only the operand order of the `and` on the flags differs.
s32 HorseMgr::getNumDeadHorsesRegistered() {
    if (!isFlagOn(Flag::_0))
        return 5;
    s32 count = 0;
    for (s32 i = 0; i != 5; ++i) {
        HorseData data;
        if (sub_7100E89B20(&data, i) && isValid(data)) {
            if (i != count)
                sub_7100E88A08(&data, count);
            ++count;
        }
    }
    return count;
}

// NON_MATCHING: the original tests the flag with `cmp w8, #0 / cset ne` before the `and` (we get `and` + `and #1`).
bool HorseMgr::isSelectedHorseFamiliarityChecked() {
    bool result = false;
    {
        auto lock = sead::makeScopedLock(_230);
        if (static_cast<u32>(_d0) <= 4) {
            bool checked = false;
            result = ksys::gdt::Manager::instance()->getParam().get().getBool(
                         &checked, "Horse_IsFamiliarityChecked", _d0) &&
                     checked;
        }
    }
    return result;
}

// NON_MATCHING: the two cross-call position locals land in the opposite FP callee-saved registers
// (ours x in s10 / z in s9; the original x in s9 / z in s10).
// 0x7100e87760 (placeholder name): whether the owned horse can be called by `actor`: true when the call
// query accepts it or it stands within `radius` of the actor; otherwise sets Horse_UnreachableCause to 1.
bool HorseMgr::x_1(f32 radius, ksys::act::Actor* actor) {
    const f32 x = actor->getMtx().m[0][3];
    const f32 z = actor->getMtx().m[2][3];
    bool reachable = false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        if (_270.sub_7100E8A100(this, actor)) {
            reachable = true;
        } else {
            if (accessor.isStateCalc()) {
                const sead::Matrix34f& mtx = accessor.getActorMtx();
                const f32 dx = x - mtx.m[0][3];
                const f32 dz = z - mtx.m[2][3];
                if (dx * dx + dz * dz <= radius * radius) {
                    actor->sendMessage(*accessor.getMessageTransceiverId(),
                                       ksys::MessageType(0x3800001), actor, true);
                    reachable = true;
                }
            }
            if (!reachable)
                ksys::gdt::Manager::instance()->setS32(1, "Horse_UnreachableCause");
        }
    }
    return reachable;
}

// NON_MATCHING: only the operand order of the and / orr on the flags differs (the original has the flags first) and the
// placement of the final `*type = ...` store.
s32 HorseMgr::sub_7100E8612C(RiddenAnimalType* type) {
    _228.resetBit(9);
    _228.resetBit(10);
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor) && _d0 >= 0) {
        *type = RiddenAnimalType(act::sub_7100E6ECC4(accessor));
        return _d0;
    }
    sead::SafeArray<HorseData, 5> data;
    s32 found;
    if (sub_7100E86340(data.getBufferPtr(), &found)) {
        const s32 index = found;
        _d0 = index;
        if (isFlagOn(Flag::_0))
            ksys::gdt::Manager::instance()->setS32(index, _1a0);
        setFlagOn(Flag::_9);
        *type = RiddenAnimalType(ksys::act::getHorseUnitRiddenAnimalType(
            ksys::act::InfoData::instance(), data[index].actorName));
    } else {
        if (_d0 >= 0)
            _d0 = -1;
        setFlagOn(Flag::_10);
        *type = RiddenAnimalType::_1;
        return -1;
    }
    return _d0;
}

// 0x7100e82b10: scans the five horse records for a complete, in-range one of `type` (the `dead`
// path reads the Horse_* flags of buffer 1, the other one buffer 0 through x_8).
// NON_MATCHING: the two loop copies are laid out differently (see x_5); the calls and checks match.
bool HorseMgr::x_4(RiddenAnimalType type, bool dead) {
    for (s32 i = 0; i < 5; ++i) {
        HorseData data;
        if ((dead ? sub_7100E854EC(&data, i) : x_8(&data, i)) &&
            data.actorName[0] != sead::SafeString::cNullChar &&
            data.userName[0] != sead::SafeString::cNullChar &&
            data.reinsName[0] != sead::SafeString::cNullChar &&
            data.saddleName[0] != sead::SafeString::cNullChar &&
            data.maneName[0] != sead::SafeString::cNullChar &&
            data.familiarity <= 1.0f && data.familiarity >= 0.0f &&
            (data.collarType | data.footType) >= 0 &&
            ksys::act::getHorseUnitRiddenAnimalType(ksys::act::InfoData::instance(),
                                                    data.actorName) == int(type))
            return true;
    }
    return false;
}

// 0x7100e82df8: scans the five horse records for a complete, in-range one of `type`.
bool HorseMgr::x_5(RiddenAnimalType type, bool dead) {
    for (s32 i = 0; i < 5; ++i) {
        HorseData data;
        if ((dead ? sub_7100E89B20(&data, i) : sub_7100E86F80(&data, i)) &&
            data.actorName[0] != sead::SafeString::cNullChar &&
            data.userName[0] != sead::SafeString::cNullChar &&
            data.reinsName[0] != sead::SafeString::cNullChar &&
            data.saddleName[0] != sead::SafeString::cNullChar &&
            data.maneName[0] != sead::SafeString::cNullChar &&
            data.familiarity <= 1.0f && data.familiarity >= 0.0f &&
            (data.collarType | data.footType) >= 0 &&
            ksys::act::getHorseUnitRiddenAnimalType(ksys::act::InfoData::instance(),
                                                    data.actorName) == int(type))
            return true;
    }
    return false;
}

bool HorseMgr::sub_7100E86CF4() {
    return _80.isAllocatedOrFailed() && !_80.isProcReady() && !_80.hasProcCreationFailed();
}

bool HorseMgr::sub_7100E86D44() {
    if (_80.isAllocatedOrFailed()) {
        setFlagOn(Flag::_8);
        return true;
    }
    return false;
}

bool HorseMgr::sub_7100E87710() {
    if (mOwnedHorse.hasProc()) {
        setFlagOn(Flag::_3);
        return true;
    }
    return false;
}

bool HorseMgr::sub_7100E875EC() {
    bool result = false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        setFlagOn(Flag::_2);
        result = true;
    }
    return result;
}

bool HorseMgr::sub_7100E87340(const sead::SafeString& name, sead::Heap* heap) {
    bool result = false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, true);
        result = true;
        act::sub_7100E6E140(accessor, name, heap);
    }
    return result;
}

bool HorseMgr::sub_7100E87424(const sead::SafeString& name, sead::Heap* heap) {
    bool result = false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, true);
        result = true;
        act::sub_7100E6E404(accessor, name, heap);
    }
    return result;
}

bool HorseMgr::sub_7100E87508(const sead::SafeString& name, sead::Heap* heap) {
    bool result = false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, true);
        result = true;
        act::sub_7100E6E6C8(accessor, name, heap);
    }
    return result;
}

void HorseMgr::sub_7100E873BC(const sead::SafeString& name, sead::Heap* heap) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        act::sub_7100E6E140(accessor, name, heap);
    }
}

void HorseMgr::sub_7100E874A0(const sead::SafeString& name, sead::Heap* heap) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        act::sub_7100E6E404(accessor, name, heap);
    }
}

void HorseMgr::sub_7100E87584(const sead::SafeString& name, sead::Heap* heap) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mOwnedHorse, &accessor)) {
        act::sub_7100E6E98C(accessor, false);
        act::sub_7100E6E6C8(accessor, name, heap);
    }
}

extern const sead::SafeString sUnk_7102603C98[4] = {
    "Horse_Link_Mane", "Horse_Link_Mane_Reduction", "Horse_Link_Mane_01",
    "Horse_Link_Mane_01_Reduction",
};
extern const sead::SafeString sUnk_7102603CD8[2] = {"Horse_Link_Mane_00L", "Horse_Link_Mane_00L_Reduction"};

namespace {
// Horse tack names of 0x7100e89eec (placeholder names = addresses): the tables the getters below index.
const f32 sUnk_7101DA2364 = 0.1f;
const sead::SafeString sUnk_7102603CF8 = "Horse_Link_Mane_Grabbed";
const sead::SafeString sUnk_7102603D08 = "Horse_Link_Mane_Grabbed_Large";
const sead::SafeString sUnk_7102603D18 = "Horse_Link_Mane_Grabbed_Nushi";
const sead::SafeString sUnk_7102603D28 = "Horse_Link_Mane_Grabbed_Bone";
}  // namespace
// Referenced with external linkage by createHorse (the original loads them through the GOT).
extern const sead::SafeString sUnk_7102603D38 = "GameRomHorseReins_00";
namespace {
const sead::SafeString sUnk_7102603D48 = "GameRomHorseReins_00L";
const sead::SafeString sUnk_7102603D58 = "GameRomHorseReins_06";
}  // namespace
extern const sead::SafeString sUnk_7102603D68 = "GameRomHorseSaddle_00";
namespace {
const sead::SafeString sUnk_7102603D78 = "GameRomHorseSaddle_00L";
const sead::SafeString sUnk_7102603D88 = "GameRomHorseSaddle_00S";
const sead::SafeString sUnk_7102603D98 = "GameRomHorseSaddle_06";

const sead::SafeString* sManeNames[10] = {
    &sUnk_7102603CF8, &sead::SafeString::cEmptyString, &sUnk_7102603CF8, &sUnk_7102603CF8,
    &sUnk_7102603D28, &sUnk_7102603D08, &sead::SafeString::cEmptyString, &sead::SafeString::cEmptyString,
    &sUnk_7102603D18, &sead::SafeString::cEmptyString,
};
const sead::SafeString* sReinsNames[10] = {
    &sUnk_7102603D38, &sUnk_7102603D38, &sUnk_7102603D38, &sUnk_7102603D58,
    &sead::SafeString::cEmptyString, &sUnk_7102603D48, &sead::SafeString::cEmptyString,
    &sead::SafeString::cEmptyString, &sead::SafeString::cEmptyString, &sead::SafeString::cEmptyString,
};
const sead::SafeString* sSaddleNames[10] = {
    &sUnk_7102603D68, &sUnk_7102603D68, &sUnk_7102603D68, &sUnk_7102603D98,
    &sead::SafeString::cEmptyString, &sUnk_7102603D78, &sUnk_7102603D88,
    &sead::SafeString::cEmptyString, &sead::SafeString::cEmptyString, &sead::SafeString::cEmptyString,
};
}  // namespace

// 0x7100e82094 (placeholder name): the mane name group of the horse type (3 / 4: the normal group, 6: the
// _00L group); otherwise the first or the _01 mane, picked with `random` (10%).
// NON_MATCHING: ours folds the 3 / 4 tests into a range check and selects the default random with csel; the
// original has one compare per case and a branch.
const sead::SafeString* sub_7100E82094(HorseMgr::RiddenAnimalType type, sead::Random* random) {
    const s32 t = type;
    if (t == 6)
        return sUnk_7102603CD8;
    if (t == 4)
        return sUnk_7102603C98;
    if (t == 3)
        return sUnk_7102603C98;
    if (!random)
        random = sead::GlobalRandom::instance();
    const f32 value = random->getF32();
    return &sUnk_7102603C98[value < sUnk_7101DA2364 ? 2 : 0];
}

// 0x7100e8208c / 0x7100e82090 (CSV nullsub_3996 / nullsub_3997): the no-op destructors the mane name group
// initializer (0x7100e89eec) registers with __cxa_atexit.
void nullsub_3996() {}
void nullsub_3997() {}

const sead::SafeString& getHorseManeName(HorseMgr::RiddenAnimalType type) {
    const u32 index = u32(type) - 1;
    if (index < 10)
        return *sManeNames[s32(index)];
    return sead::SafeString::cEmptyString;
}

const sead::SafeString& getHorseReinsName(HorseMgr::RiddenAnimalType type) {
    const u32 index = u32(type) - 1;
    if (index < 10)
        return *sReinsNames[s32(index)];
    return sead::SafeString::cEmptyString;
}

// 0x7100e88610 (placeholder name; HorseMgr::postCalc calls it twice): after the placement and LOD
// checks, whether `actor` is within sqrt(dist_sq) of the player on the XZ plane.
// NON_MATCHING: same instructions, but we store the matrix translation three times at once and merge
// the two "return true" blocks, so the frame and the block layout differ.
bool sub_7100E88610(f32 dist_sq, const ksys::act::Actor* actor) {
    if (actor->get1a0())
        return false;
    if (actor->getMapObject() &&
        actor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
        return false;
    if (actor->getLodState()->mFlags10.isOn(0x40))
        return true;

    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement)
        return true;

    const sead::Matrix34f& mtx = actor->getMtx();
    const sead::Vector3f pos(mtx.m[0][3], mtx.m[1][3], mtx.m[2][3]);
    if (!placement->isStaticCompoundReady(pos, false))
        return false;

    auto* system = ksys::act::ActorSystem::instance();
    if (!system)
        return true;
    auto* link = system->getPlayerLink();
    if (!link)
        return true;
    auto* player = link->getPlayer();
    if (!player)
        return true;

    const f32 dx = player->getMtx().m[0][3] - pos.x;
    const f32 dz = player->getMtx().m[2][3] - pos.z;
    return dx * dx + dz * dz < dist_sq;
}

const sead::SafeString& getHorseSaddleName(HorseMgr::RiddenAnimalType type) {
    const u32 index = u32(type) - 1;
    if (index < 10)
        return *sSaddleNames[s32(index)];
    return sead::SafeString::cEmptyString;
}

}  // namespace uking

// 0x7100e86d84 (CSV name): moves dead horse `index` back to the live records (at the end) and removes it
// from the dead ones; returns its new index, or -1 when the record is incomplete or all five are in use.
// NON_MATCHING: our clang merges the identical `return -1` blocks into one at the end; the original
// materialises -1 and branches to the epilogue in each arm (10 more instructions, 127 vs 117).
s32 resurrectHorseStuff(uking::HorseMgr* mgr, s32 index) {
    uking::HorseMgr::HorseData data;
    if (!uking::HorseMgr::sub_7100E86F80(&data, index))
        return -1;
    if (data.actorName[0] == sead::SafeString::cNullChar)
        return -1;
    if (data.userName[0] == sead::SafeString::cNullChar)
        return -1;
    if (data.reinsName[0] == sead::SafeString::cNullChar)
        return -1;
    if (data.saddleName[0] == sead::SafeString::cNullChar)
        return -1;
    if (data.maneName[0] == sead::SafeString::cNullChar)
        return -1;
    if (!(data.familiarity <= 1.0f))
        return -1;
    if (!(data.familiarity >= 0.0f))
        return -1;
    if ((data.collarType | data.footType) < 0)
        return -1;

    const s32 count = mgr->getNumRegisteredHorses();
    if (u32(count) > 4)
        return -1;

    mgr->sub_7100E8533C(&data, count);
    mgr->sub_7100E8720C(index);
    ksys::PlayReportMgr::instance()->reportDebug("HorseResurrected", data.actorName);
    return count;
}

namespace sead {
// 0x7100e89e60 / 0x7100e89e90 (unnamed in the CSV): the invoke / clone of the ReinitEvent delegate that
// mReinitSlot binds to HorseMgr::onGameDataReinit (the constructor's binding is not decompiled yet).
template class Delegate1<uking::HorseMgr, ksys::gdt::Manager::ReinitEvent*>;
}  // namespace sead
