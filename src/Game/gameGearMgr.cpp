#include "Game/gameGearMgr.h"
#include <math/seadMathCalcCommon.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/Vibration.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "Game/Scene/gameScene.h"
#include <cmath>

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(GearMgr)

void GearMgr::sub_7100669EE4() {
    ksys::tera::sub_7100F418B8(nullptr);
    for (size_t i = 0; i < 0x80; ++i)
        mEntries[i].reset();
    ksys::phys::System::instance()->removeSystemGroupHandler(_1050);
    _1050 = nullptr;
}


// NON_MATCHING: the original zeroes `_10a4` with a word store (and uses the whole word in its read-modify-write
// helpers: the field is probably a 32-bit flag word that other translation units test through a byte load);
// the entry loops are also register-allocated differently.
GearMgr::GearMgr() {
    clear_();
}

// NON_MATCHING: see the constructor (word store to `_10a4`, entry loop registers).
GearMgr::~GearMgr() {
    clear_();
}

void GearMgr::clear_() {
    _28 = 0;
    _2c = 0;
    for (size_t i = 0; i < 0x80; ++i)
        mEntries[i].reset();
    _1030.reset();
    _10a4w = 0;
    _10c0 = 0;
    _10c4 = 0;
    _1050 = nullptr;
    _10c8 = 1.0f;
    _10cc = 0;
    _10dc = 0;
    _10dd = 0;
    _10a8[0] = 0;
    _10a8[1] = 0;
    _10b0[0] = 0;
    _10b0[1] = 0;
    _10b8[0] = 1.0f;
    _10b8[1] = 1.0f;
    _10a0 = 0;
    _1098 = 0;
    _109c = 0;
}

void GearMgr::init() {
    clear_();
    _1050 = ksys::phys::System::instance()->addSystemGroupHandler(ksys::phys::ContactLayerType::Entity);
    ksys::tera::sub_7100F418B8(&_10e0);
    if (ksys::gdt::getFlag_Used_App_FinalTrial()) {
        _10a4w = (_10a4w & ~0x28u) | 8;
        _10a8[0] |= 1;
        _10a8[1] = _10a8[0];
        _10b0[0] = _10a8[0];
        _10b0[1] = _10a8[0];
    }
}

bool GearMgr::sub_71006690B8(ksys::act::BaseProc* proc) {
    if (!proc)
        return false;

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& link = mEntries[i].mLink;
        if (link.hasProc() && link.hasProcById(proc)) {
            mCS.unlock();
            return true;
        }
    }
    mCS.unlock();
    return false;
}

// NON_MATCHING: regalloc only (the original keeps `this` in x19 and `&mCS` in x20).
void GearMgr::sub_71006692F0(ksys::act::Actor* actor, bool join_system_group) {
    if (!actor)
        return;

    if (sub_71006690B8(actor))
        return;

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& entry = mEntries[i];
        if (!entry.mLink.hasProc()) {
            entry.mLink.acquire(actor, false);
            entry._10 = join_system_group;
            if (join_system_group) {
                if (auto* physics = actor->getPhysics())
                    physics->sub_7100FBDFA4(_1050);
            }
            break;
        }
    }
    mCS.unlock();
}

void GearMgr::sub_71006693F4(Entry* entry) {
    if (entry->_10) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(entry->mLink.getProc(nullptr, nullptr))) {
            if (auto* physics = actor->getPhysics()) {
                physics->sub_7100FBDFA4(physics->get178(0));
                physics->sub_7100FBDFA4(physics->get178(1));
            }
        }
    }
    entry->mLink.reset();
}

void GearMgr::sub_71006694B4(ksys::act::Actor* actor) {
    if (!actor)
        return;

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& entry = mEntries[i];
        if (entry.mLink.hasProc() && entry.mLink.hasProcById(actor)) {
            if (entry._10) {
                if (auto* physics = actor->getPhysics()) {
                    physics->sub_7100FBDFA4(physics->get178(0));
                    physics->sub_7100FBDFA4(physics->get178(1));
                }
            }
            entry.mLink.reset();
            break;
        }
    }
    mCS.unlock();
}

void GearMgr::sub_710066956C(ksys::act::BaseProc* proc, bool join_system_group) {
    if (!proc)
        return;

    mCS.lock();
    _1030.mLink.acquire(proc, false);
    _1030._10 = join_system_group;
    mCS.unlock();
}

void GearMgr::sub_71006695DC(ksys::act::BaseProc* proc) {
    mCS.lock();
    if (_1030.mLink.hasProc() && _1030.mLink.hasProcById(proc))
        _1030.mLink.reset();
    mCS.unlock();
}

void GearMgr::sub_71006698B0(bool on) {
    mCS.lock();
    if (on)
        _10a8[_28] |= 4;
    else
        _10a8[_28] &= ~4u;
    mCS.unlock();
}

KSYS_VISIBILITY_HIDDEN f32 sUnk_710243C148 = 12.0f;

// Rumble request tuning read by sub_7100669980 (0x710243c1a0: 0.3, 1.0, 1.0, 1.0).
struct Unk_710243C1A0 {
    f32 _18;
    f32 _24;
    f32 _1c;
    f32 _20;
};
KSYS_VISIBILITY_HIDDEN Unk_710243C1A0 sUnk_710243C1A0 = {0.3f, 1.0f, 1.0f, 1.0f};
// Static switches that add the flag bits of the rumble request.
KSYS_VISIBILITY_HIDDEN u8 sUnk_71025C5D10 = 0;
KSYS_VISIBILITY_HIDDEN u8 sUnk_71025C5D14 = 0;
KSYS_VISIBILITY_HIDDEN u8 sUnk_71025C5D18 = 0;
KSYS_VISIBILITY_HIDDEN u8 sUnk_710243C14C = 0;
// Selects the physics frame time instead of the VFR delta (0x7100669c8c).
KSYS_VISIBILITY_HIDDEN u8 sUnk_71025C5D1C = 0;

// NON_MATCHING: the request field order / flag merges differ slightly.
void GearMgr::sub_7100669980() {
    ksys::Vibration::Unk2 request;
    ksys::sub_7100D8C6AC(&request._0);
    if (!sUnk_71025C5D10) {
        request._18 = sUnk_710243C1A0._18;
        request._1c = sUnk_710243C1A0._1c;
        request._20 = s32(std::ceil(sUnk_710243C1A0._20));
        request._24 = u8(s32(sUnk_710243C1A0._24));
        u8 flags = 0;
        if (sUnk_71025C5D14)
            flags |= 1;
        if (sUnk_71025C5D18)
            flags |= 2;
        if (sUnk_710243C14C)
            flags |= 4;
        request._25 = flags;
    } else {
        request._18 = 0;
        request._1c = 0;
        request._24 = 0;
    }
    ksys::Vibration::instance()->sub_71010BB428(request);
}

void GearMgr::sub_710066990C(bool on) {
    mCS.lock();
    if (on)
        _10a8[_28] |= 1;
    else
        _10a8[_28] &= ~1u;
    _10d0 = ksys::Timer(sUnk_710243C148, sUnk_710243C148);
    mCS.unlock();
}

void GearMgr::sub_7100669AF8(f32 value) {
    mCS.lock();
    _10c4 = value;
    mCS.unlock();
}

bool GearMgr::sub_7100669B48() {
    _10b0[_2c] |= 2;
    return (_10b0[_2c ^ 1] >> 1) & 1;
}

// NON_MATCHING: block layout (the original branches to the end on `value < 0`) and the flag word is
// loaded whole (`ldr` + `tbnz`) instead of as a byte.
bool GearMgr::sub_7100669A60(f32 value) {
    bool lowered = false;
    if (value >= 0.0f) {
        if (!(_10a8[_28 ^ 1] & 4)) {
            mCS.lock();
            const u32 idx = _2c;
            if (_10b8[idx] > value) {
                _10b8[idx] = value;
                lowered = true;
            }
            mCS.unlock();
        }
    }
    return lowered;
}

void GearMgr::sub_7100669144(f32 gear_ratio) {
    const Fraction fraction = sub_7100669F50(gear_ratio > 0.0f ? 1.0f / gear_ratio : 0.0f);
    _10c8 = sead::Mathu::lcm(u32(_10c8), fraction.denominator);
}

void GearMgr::sub_7100669B38() {
    _10a4w |= 0x20;
}

void GearMgr::sub_7100669194(ksys::act::BaseProcLink* link, bool join_system_group) {
    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& entry = mEntries[i];
        if (entry.mLink.hasProc() && entry.mLink == *link) {
            mCS.unlock();
            return;
        }
    }
    mCS.unlock();

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& entry = mEntries[i];
        if (!entry.mLink.hasProc()) {
            entry.mLink = *link;
            entry._10 = join_system_group;
            if (join_system_group) {
                if (auto* actor = sead::DynamicCast<ksys::act::Actor>(link->getProc(nullptr, nullptr))) {
                    if (auto* physics = actor->getPhysics())
                        physics->sub_7100FBDFA4(_1050);
                }
            }
            break;
        }
    }
    mCS.unlock();
}

// NON_MATCHING: the two zero bytes `_10dc` and `_10dd` are separate stores in the original; clang merges
// them into one halfword store here.
void GearMgr::sub_7100668D44() {
    f32 value = _10c0;
    if (value < 0.0f)
        value = 0.0f;
    else if (value > 1.0f)
        value = 1.0f;

    _1100.sub_7100E726E0(value);
    ksys::xlink::Manager::instance()->setGlobalProperty(0x2c, value);
    ksys::xlink::Manager::instance()->setGlobalProperty(0x2d, _1100._4);

    bool cog_wheel_stop;
    if (_10c0 + _10b8[_2c ^ 1] <= 1.1920929e-07f)
        cog_wheel_stop = true;
    else
        cog_wheel_stop = (_10a8[_28 ^ 1] >> 2) & 1;
    ksys::gdt::setFlag_FinalTrial_CogWheelStop(cog_wheel_stop);

    if ((_10a8[0] ^ _10a8[1]) & 1)
        _10a4w |= 2;
    else
        _10a4w &= ~2u;

    const u32 flags = _10a8[_28];
    const bool scene_ready = getSceneStatus() == 0;
    const bool paused = ksys::phys::System::instance()->isPaused();
    const bool fading = ::ui::isFadeDemoOrFadeScreenOpened();
    const bool can_update = scene_ready && !paused && !fading;

    _28 ^= 1;
    _10a8[_28] = flags;
    _10dd = 0;
    if (_10dc && !(_10a8[_28 ^ 1] & 4))
        _10dd = 1;

    _10dc = (_10a8[_28 ^ 1] >> 2) & 1;
    if (_10a8[_28 ^ 1] & 4) {
        _10c0 = 0;
        _10b8[_2c] = _10b8[_2c ^ 1];
        if (can_update)
            _10d0.update();
    } else {
        if (!(_10a4w & 8)) {
            if (!(_10a4w & 0x20))
                return;
            _10a4w = (_10a4w & ~0x28u) | 8;
            ksys::gdt::setFlag_Used_App_FinalTrial(true);
        }
        if (can_update)
            sub_7100669C8C();
    }
}

void GearMgr::postCalc_() {
    for (size_t i = 0; i < 0x80; ++i) {
        auto& entry = mEntries[i];
        if (!entry.mLink.hasProc())
            continue;

        auto* actor = sead::DynamicCast<ksys::act::Actor>(entry.mLink.getProc(nullptr, nullptr));
        if (!actor)
            continue;
        if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
            continue;
        if (!actor->hasPlacementLinkForBasicSig())
            break;
        if (actor->checkBasicSig())
            break;

        const bool joined_system_group = entry._10;
        mCS.lock();
        _1030.mLink = entry.mLink;
        _1030._10 = joined_system_group;
        mCS.unlock();
        sub_71006693F4(&entry);
        mCS.lock();
        _10a8[_28] &= ~4u;
        mCS.unlock();
        break;
    }

    auto* link = &_1030.mLink;
    if (!link->hasProc())
        return;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(link->getProc(nullptr, nullptr));
    if (!actor)
        return;
    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
        return;
    if (!actor->hasPlacementLinkForBasicSig() || !actor->checkBasicSig())
        return;

    sub_7100669194(link, _1030._10);
    mCS.lock();
    if (link->hasProc() && *link == _1030.mLink)
        link->reset();
    mCS.unlock();

    mCS.lock();
    _10a8[_28] |= 4;
    mCS.unlock();
}

void GearMgr::sub_7100669C88() {}

void GearMgr::sub_7100669ED8() {}

void GearMgr::sub_7100669C8C() {
    const s32 idx = _2c;
    const u32 entry_flags = _10b0[idx];
    if (!(entry_flags & 2))
        return;

    const u32 other_flags = _10a8[_28 ^ 1];
    _10b0[idx] = (other_flags & 1) ? (entry_flags | 1) : (entry_flags & ~1u);

    const u32 b0 = _10b0[0];
    const u32 b1 = _10b0[1];
    _10a4w = ((b0 ^ b1) & 1) ? (_10a4w | 1) : (_10a4w & ~1u);
    const u32 a4 = _10a4w;
    const bool toggle_10 = ((a4 >> 3) & 1) != ((a4 >> 4) & 1);
    _10a4w = (a4 & 8) ? (a4 | 0x10) : (a4 & ~0x10u);
    _10a4w = toggle_10 ? (_10a4w | 4) : (_10a4w & ~4u);

    const u32 flags = _10b0[idx];
    const f32 sign = (flags & 1) ? 1.0f : -1.0f;
    _10d0.update();

    const bool other_one = (other_flags & 1) != 0;
    if (((b0 ^ b1) & 1) != 0) {
        _10b8[0] = 5.0f;
        _10b8[1] = 5.0f;
        _10c0 = 5.0f;
        sub_7100669980();
    } else {
        _10c0 = _10b8[idx];
    }

    const bool stop = other_one ? ksys::gdt::getFlag_FinalTrial_SandwichDetection()
                                : ksys::gdt::getFlag_FinalTrial_SandwichDetection02();
    if (stop) {
        _10b8[0] = 0.0f;
        _10b8[1] = 0.0f;
        _10c0 = 0.0f;
    }

    f32 frame;
    if (sUnk_71025C5D1C)
        frame = ksys::phys::System::instance()->get64();
    else
        frame = ksys::VFR::instance()->getDeltaFrame();

    const f32 step = sign * frame * _10c4 * _10c0;
    const f32 prev = _1098;
    _109c = prev;
    _10cc = step;
    const f32 next = step + prev;
    _10a0 = prev + sign * _10c4 * _10c0 * ksys::phys::System::instance()->get64();
    _1098 = next;
    if (sead::Mathf::abs(next) >= _10c8 * 6.2831855f)
        _1098 = 0;

    _2c ^= 1;
    _10b0[_2c] = flags & ~2u;
    _10b8[_2c] = 1.0f;
}

void GearMgr::postCalc() {
    postCalc_();
}

// NON_MATCHING: the original keeps both bounds in registers (field-wise csel); ours selects the bound through a
// stack address. Control flow and arithmetic are the same.
Fraction sub_7100669F50(f32 value) {
    if (value < 0.0f) {
        const Fraction fraction = sub_7100669F50(-value);
        return {-fraction.numerator, fraction.denominator};
    }

    Fraction lower{0, 1};
    Fraction upper{1, 0};
    f32 lower_error;
    f32 upper_error;
    while (true) {
        const Fraction mediant{upper.numerator + lower.numerator, upper.denominator + lower.denominator};
        if (f32(mediant.numerator) / f32(mediant.denominator) < value)
            lower = mediant;
        else
            upper = mediant;
        lower_error = sead::Mathf::abs(value - f32(lower.numerator) / f32(lower.denominator));
        upper_error = sead::Mathf::abs(value - f32(upper.numerator) / f32(upper.denominator));
        if (u32(mediant.denominator) > 1000 || u32(mediant.numerator) > 1000 || lower_error < 1e-4f ||
            upper_error < 1e-4f) {
            break;
        }
    }

    return lower_error < upper_error ? lower : upper;
}

}  // namespace uking
