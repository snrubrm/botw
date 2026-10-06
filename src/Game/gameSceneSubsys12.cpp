#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/System/Timer.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include <prim/seadScopedLock.h>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

// Scene parameters (initialized data at 0x710243bfb8..0x710243c018): nothing in the binary writes
// them, yet the loads are not folded (hidden visibility, as in actCameraUtil.cpp).
KSYS_VISIBILITY_HIDDEN bool sUnk_710243bfb8 = true;
KSYS_VISIBILITY_HIDDEN bool sUnk_710243bfbc = true;
KSYS_VISIBILITY_HIDDEN s32 sUnk_710243bfc0 = 1;
// Initialized parameter block at 0x710243bfd0..0x710243c020 (20 floats; its address is the base of all
// the loads below).
struct SceneParams {
    f32 _0 = 2.0f;
    f32 _4 = 0.1f;
    f32 _8 = 7.0f;
    f32 _c = 1.0f;
    f32 _10 = 1.3f;
    f32 _14 = 7.0f;
    f32 _18 = 0.2f;
    f32 _1c = 0.73f;
    f32 _20 = 1.25f;
    f32 _24 = 1.4f;
    f32 _28 = 2.8f;
    f32 _2c = 0.3f;
    f32 _30 = 0.5f;
    f32 _34 = 0.2f;
    f32 _38 = 0.6f;
    f32 _3c = 1.0f;
    f32 _40 = 0.0f;
    f32 _44 = 0.15f;
    f32 _48 = 0.3f;
    f32 _4c = 0.0f;
};
KSYS_VISIBILITY_HIDDEN SceneParams sUnk_710243bfd0;

// Zero-initialised pair at 0x71025c5a08 (nothing in the binary writes it; hidden visibility keeps the loads).
struct SceneRange {
    f32 _0;
    f32 _4;
};
KSYS_VISIBILITY_HIDDEN SceneRange sUnk_71025c5a08;

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys12)

// NON_MATCHING: the original merges the two (0.1, 1.0) / (0.1, 0.32) pairs into 64-bit stores, loads
// the identity matrix into q registers in a different order and schedules the store block differently;
// the member values and the amount of work are identical.
GameSceneSubsys12::GameSceneSubsys12() : _27c(sUnk_710243bfd0._0) {
    _d8.makeIdentity();
    _108.makeIdentity();
    _138.makeIdentity();
    for (auto& matrix : _168)
        matrix.makeIdentity();

    // Offsets of the carried items for 1 to 5 items.
    _a98[0][0].set(0.0f, 0.056f, 0.29f);
    _a98[1][0].set(-0.1f, 0.05f, 0.32f);
    _a98[1][1].set(0.1f, 0.05f, 0.34f);
    _a98[2][0].set(-0.1f, 0.03f, 0.37f);
    _a98[2][1].set(0.1f, 0.03f, 0.37f);
    _a98[2][2].set(0.0f, 0.1f, 0.3f);
    _a98[3][0].set(-0.1f, 0.02f, 0.37f);
    _a98[3][1].set(0.1f, 0.02f, 0.37f);
    _a98[3][2].set(-0.08f, 0.1f, 0.3f);
    _a98[3][3].set(0.07f, 0.1f, 0.35f);
    _a98[4][0].set(-0.1f, 0.0f, 0.36f);
    _a98[4][1].set(0.1f, -0.02f, 0.34f);
    _a98[4][2].set(-0.08f, 0.1f, 0.23f);
    _a98[4][3].set(0.0f, 0.14f, 0.35f);
    _a98[4][4].set(0.08f, 0.12f, 0.29f);

    for (auto& v : _bc4) {
        v.x = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
        v.y = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
        v.z = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
    }
}

GameSceneSubsys12::~GameSceneSubsys12() = default;

int GameSceneSubsys12::handleMessage(const ksys::Message& message) {
    return 1;
}

void GameSceneSubsys12::init(sead::Heap* heap) {
    _318.sub_710065D8E4(heap, true);
}

bool GameSceneSubsys12::x() const {
    return _a78.isBitOn(0);
}

Unk_710243be90* GameSceneSubsys12::sub_7100663278(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (auto* entry = _318.sub_710065E2B0(proc))
        return entry;

    bool has_carrier = _300.hasProc() && _310;
    if (!has_carrier) {
        _a78.setBitOff(3);
        if (auto* carrier = sub_7100662C4C()) {
            _300.acquire(carrier, false);
            sub_7100662EF0(carrier);
        }
        has_carrier = _300.hasProc() && _310;
    }
    if (has_carrier) {
        if (auto* entry = _310->sub_710065E2B0(proc))
            return entry;
    }
    proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    return nullptr;
}

bool GameSceneSubsys12::sub_7100663364(sead::Matrix34f* out) {
    if (!_300.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    // The original calls acquireActor but discards its result after the hasProc check.
    ksys::act::acquireActor(&_300, &accessor);
    *out = accessor.getActorMtx();
    return true;
}

s32 GameSceneSubsys12::sub_710066358C() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _300.hasProc() && _310 ? _310->sub_710065F044() : 0;
}

bool GameSceneSubsys12::sub_71006652C8() const {
    return _300.hasProc() && !_a78.isBitOn(0);
}

s32 GameSceneSubsys12::sub_7100664D24() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _318.sub_710065F044();
}

s32 GameSceneSubsys12::sub_7100664D64() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _300.hasProc() && _310 ? _310->sub_710065F07C() : 0;
}

void GameSceneSubsys12::sub_7100664F00(const sead::Matrix34f& matrix) {
    _d8 = matrix;
    if (_a78.isBitOn(2))
        ksys::Timer::update(&_270, 1.0f);
}

bool GameSceneSubsys12::sub_7100664F30() const {
    return _a78.isBitOn(2);
}

void GameSceneSubsys12::sub_7100664F3C(const sead::Matrix34f& matrix) {
    _108 = matrix;
}

void GameSceneSubsys12::sub_7100664F64(const sead::Matrix34f& matrix) {
    _138 = matrix;
}

void GameSceneSubsys12::sub_7100665304() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    _270 = 0.0f;
    _a78.setBitOn(2);
    if (_300.hasProc() && _310)
        _310->sub_710065F9AC();
}

ksys::act::BaseProcLink* GameSceneSubsys12::sub_7100664BC8(s32 index) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (_300.hasProc() && _310)
        return _310->sub_710065F80C(index);
    return nullptr;
}

ksys::act::BaseProcLink* GameSceneSubsys12::sub_7100664DBC(s32 index) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _318.sub_710065F80C(index);
}

f32 GameSceneSubsys12::sub_7100664ACC(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    return _300.hasProc() && _310 ? _310->sub_710065FA28(proc, _270) : 0.0f;
}

bool GameSceneSubsys12::sub_7100664A64(ksys::act::BaseProcLink* link, bool immediately) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (!_a78.isBitOn(0))
        return _318.sub_710065F258(link, immediately);
    return false;
}

f32 GameSceneSubsys12::sub_7100665408(Unk_710243be90* entry) const {
    const bool flag = _a78 & 8;
    const f32 min = flag ? sUnk_710243bfd0._24 : sUnk_71025c5a08._0;
    const f32 max = flag ? sUnk_710243bfd0._28 : sUnk_71025c5a08._4;
    return sead::GlobalRandom::instance()->getF32Range(min, max);
}

f32 GameSceneSubsys12::sub_7100665484(Unk_710243be90* entry) const {
    if (!(_a78 & 8))
        return sUnk_710243bfd0._30;
    const f32 min = sUnk_710243bfd0._2c;
    const f32 max = sUnk_710243bfd0._30;
    return sead::GlobalRandom::instance()->getF32Range(min, max);
}

f32 GameSceneSubsys12::sub_71006654F0(Unk_710243be90* entry) const {
    if (entry && (entry->_28 & 0x100))
        return sUnk_710243bfd0._38;
    return sUnk_710243bfd0._34;
}

void GameSceneSubsys12::sub_7100662AF8(const char* name, sead::Heap* heap) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (!(_a78 & 1))
        _318.sub_710065DACC(name, heap);
}

bool GameSceneSubsys12::sub_71006649C4(ksys::act::BaseProcLink* link) {
    bool removed = false;
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (!(_a78 & 1) && _300.hasProc() && _310 && _310->sub_710065F258(link, true)) {
        if (auto* mgr = uking::ui::PauseMenuDataMgr::instance())
            mgr->removeGrabbedItem(link);
        _318.sub_710065F258(link, false);
        removed = true;
    }
    return removed;
}

void GameSceneSubsys12::sub_7100665360() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    _d4 = 0;
    _a78.setBitOff(0);
    _a78.setBitOff(2);
    _270 = 0.0f;
    sub_7100664484(4, _310);
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_300, &accessor))
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

// NON_MATCHING: the original count clamp contains an int-float-int round trip, and copy stores differ.
void GameSceneSubsys12::sub_7100664CC0(sead::Vector3f* out, s32 count, s32 index) {
    if (out) {
        const s32 row = sead::Mathi::clamp(count - 1, 0, 4);
        *out = _a98[row][index];
    }
}

// NON_MATCHING: the original loads _d0 later (scheduling) and moves x1 before the float argument.
f32 GameSceneSubsys12::sub_7100664B3C(ActorContextStuff* context, f32 scale) {
    if (_300.hasProc() && _310 == context && _a78.isBitOn(0)) {
        const f32 doubled_scale = scale + scale;
        const f32 limited_scale = sead::Mathf::min(sUnk_710243bfd0._1c, doubled_scale * sUnk_710243bfd0._20);
        return _d0 * (limited_scale / doubled_scale - 1.0f) + 1.0f;
    }
    return 1.0f;
}

// NON_MATCHING: the original clamp contains an int-float-int round trip.
void GameSceneSubsys12::sub_7100664C30(sead::Vector3f* out, s32 count, s32 index) {
    if (out) {
        const s32 row = sead::Mathi::clamp(count - 1, 0, 4);
        const sead::Vector3f v = _a98[row][index];
        out->set(sUnk_710243bfd0._3c * v.x - sUnk_710243bfd0._40,
                 sUnk_710243bfd0._3c * v.y - sUnk_710243bfd0._44,
                 sUnk_710243bfd0._3c * v.z - sUnk_710243bfd0._48);
    }
}

// NON_MATCHING: matrix/vector store scheduling and quaternion temporary allocation differ.
void GameSceneSubsys12::sub_7100664F8C(s32 index, const sead::Matrix34f& matrix) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    _168[index] = matrix;
    const s32 count = sub_710066358C();
    if (index >= count || (_d4 & (1 << index)) || !_300.hasProc() || !_310)
        return;
    if (index >= _310->_638.size())
        return;
    auto* entry = _310->_638.at(index);
    if (!entry)
        return;
    sead::Matrix34f transform;
    transform.setMul((entry->_28 & 8) ? _138 : _108, _168[index]);
    transform.setMul(_d8, transform);
    const sead::Vector3f position = transform.getTranslation();
    sead::Quatf rotation;
    transform.toQuat(rotation);
    sead::Vector3f entry_position;
    sead::Quatf entry_rotation;
    entry->sub_71006620CC(&entry_position, &entry_rotation);
    entry->_6c = index;
    entry->_88 = position - entry_position;
    rotation.inverse();
    entry->_78.setMul(rotation, entry_rotation);
    _d4 |= 1 << index;
}

// NON_MATCHING: identity matrix loads and the progress reset are scheduled differently.
s32 GameSceneSubsys12::sub_7100664E0C(void* unused,
                                       sead::Buffer<sead::FixedSafeString<64>>* names) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    const s32 count = _300.hasProc() && _310 ? _310->sub_710065F894(unused, names) : 0;
    _a78.setBitOn(0);
    _a78.setBitOff(2);
    _d0 = 0.0f;
    _d8 = sead::Matrix34f::ident;
    _108 = sead::Matrix34f::ident;
    _138 = sead::Matrix34f::ident;
    _270 = 0.0f;
    return count;
}

void GameSceneSubsys12::sub_7100662B58(const char* name, sead::Heap* heap) {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (_a78.isBitOn(0))
        return;
    _a78.setBitOn(4);
    if (!_300.hasProc()) {
        _a78.setBitOff(3);
        _a78.setBitOff(5);
        if (auto* carrier = sub_7100662C4C()) {
            _300.acquire(carrier, false);
            sub_7100662EF0(carrier);
        }
    }
    if (_300.hasProc() && _310)
        _310->sub_710065DACC(name, heap);
}

void GameSceneSubsys12::sub_71006643EC() {
    sead::ScopedLock<sead::CriticalSection> lock(&_38);
    if (_a78.isBitOn(1))
        return;
    _a78.setBitOn(1);
    if (_300.hasProc() && _310)
        _310->sub_710065E440();
    if (auto* pause = uking::ui::PauseMenuDataMgr::instance()) {
        if (!pause->isNothingBeingGrabbed())
            pause->unholdGrabbedItems();
    }
    _318.sub_710065E4BC(true);
}

// 0x7100662ef0
void GameSceneSubsys12::sub_7100662EF0(ksys::act::Actor* actor) {
    if (!_300.hasProcById(actor))
        return;

    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    ksys::act::ActorConstDataAccess child;
    player.acquireConnectedCalcChild(&child);
    if (!child.hasProc(actor) && sUnk_710243bfbc && player.hasProc()) {
        mTransceiver.sendMessage(*player.getMessageTransceiverId(), ksys::MessageType(0x8000016),
                                 actor, true);
        mTransceiver.sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x1800004),
                                 nullptr, true);
    }
}

s32 GameSceneSubsys12::sub_710066551C() const {
    return sUnk_710243bfc0;
}

// NON_MATCHING: every path except the context-loop early exit ends in an unused volatile load of _a78
// (`ldr wzr, [this, #0xa78]`) in the original; the source of that load is unknown, the rest matches.
void GameSceneSubsys12::sub_71006633E4() {
    const bool mode_1 = ksys::act::BaseProcMgr::instance()->getMode() == ksys::act::BaseProcMgr::Mode(1);
    _318.sub_710065DC14();
    if (mode_1)
        _318.x();
    else
        _318.x_0();

    for (auto* context : _a80) {
        if (context->sub_710065E638())
            return;
    }

    if (_300.hasProc() && _310) {
        if (_310->sub_710065DC14())
            _a78.setBitOn(4);
        else
            _a78.setBitOff(4);
        if (_a78.isBitOn(4))
            return;

        s32 count = 0;
        {
            sead::ScopedLock<sead::CriticalSection> lock(&_38);
            if (_300.hasProc() && _310)
                count = _310->sub_710065F044();
        }
        if (count > 0)
            return;
        if (ksys::ui::sub_7100EDC4B8())
            return;

        _a80.pushFront(_310);
        _300.reset();
        _310 = nullptr;
    } else {
        _a78.setBitOff(4);
    }
}
