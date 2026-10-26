#include "Game/Actor/aiUnk_7102450fa8.h"
#include <basis/seadNew.h>
#include <new>
#include "Game/Actor/aiPriestBossPhaseMembers.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/VFR.h"

sead::Vector3f sUnk_71025c8cf8(0, 0, 900);
sead::Vector3f sUnk_71025c8d04(0, -4, 900);
f32 sUnk_7102450fa0 = 50.0f;
const sead::SafeArray<const char*, 3> sUnk_7102450f80 = {
    {"Priest_Boss_FireArrow", "Priest_Boss_IceArrow", "Priest_Boss_ElectricArrow"}};
const char* const sUnk_7102450f98 = "Grave";
// The Priest Boss enemies' shared navmesh material filter (vtable 0x7102450e90, installed in their
// NavMeshCharacter by PriestBossActorEnemyRoot::init_).
Unk_7102450e90 sUnk_71025c8d10;

s32 Unk_7102450fa8::sub_7100719FCC() const {
    return _88 ? _88->_ac : -1;
}

// The result goes through a Phase temporary (the return value is stored to the stack and reloaded).
s32 Unk_7102450fa8::sub_7100719FE4(s32 idx) {
    if (_88) {
        const Phase phase = _88->m6(idx);
        return phase;
    }
    return 3;
}

s32 Unk_7102450fa8::sub_7100719FA4() {
    if (_88) {
        const Phase phase = _88->_a8;
        return phase;
    }
    return 0;
}

bool Unk_7102450fa8::sub_710071A020(sead::Vector3f* out, s32 idx) {
    if (!_88)
        return false;
    _88->m7(out, idx);
    return true;
}

s32 Unk_7102450fa8::sub_710071A048(s32 idx) {
    return _88 ? *_88->_b0(idx - 2) : -1;
}

bool Unk_7102450fa8::sub_7100719978(s32 idx) const {
    if (idx == 2 || u32(idx - 2) > 8)
        return false;
    return _80 >> idx & 1;
}

bool Unk_7102450fa8::sub_71007194CC(ksys::act::ActorLinkConstDataAccess* accessor) {
    return ksys::act::acquireActor(&_18, accessor);
}

bool Unk_7102450fa8::sub_71007194D4(int idx, ksys::act::ActorLinkConstDataAccess* accessor) {
    if (idx < 0 || idx >= _8.size())
        return false;

    ksys::act::acquireActor(&_8[idx]._e0, accessor);
    return accessor->hasProc();
}

// NON_MATCHING: the loop exit compare is canonicalised (original: cmp #32 / b.le; ours: cmp #33 / b.lt).
// An s64 index gives the original latch but narrows the inlined Buffer::operator[] compare to 32 bits.
int Unk_7102450fa8::sub_7100719534(ksys::act::BaseProc* proc) {
    for (int i = 0; i <= 32; ++i) {
        if (_8[i]._e0.hasProcById(proc))
            return i;
    }
    return -1;
}

// NON_MATCHING: loop exit compare (original: cmp #32 / b.le; ours: cmp #33 / b.lt)
// An s64 index gives the original latch but narrows the inlined Buffer::operator[] compare to 32 bits.
int Unk_7102450fa8::sub_71007195B0(const ksys::act::BaseProcLink& link) {
    for (int i = 0; i <= 32; ++i) {
        if (_8[i]._e0 == link)
            return i;
    }
    return -1;
}

bool Unk_7102450fa8::sub_710071962C(sead::Vector3f* out) {
    out->set(sUnk_71025c8cf8);
    return true;
}

// 0x710071964c: takes the arena settings of the linked actor (its position, the radius of its
// GeneralSensor body and its transceiver id).
void Unk_7102450fa8::sub_710071964C(const Unk3& arg) {
    _1a0 = arg._10;
    sUnk_71025c8cf8.set(arg._0);
    sUnk_71025c8d04 = arg._0 + sead::Vector3f(0.0f, -4.0f, 0.0f);
    sUnk_7102450fa0 = arg._c;
    setFlag(Flag::_5);
}

// NON_MATCHING: ours merges the member range test into one compare (the original tests 0 and > 8 separately).
bool Unk_7102450fa8::sub_71007196EC(s32 idx, const sead::Vector3f& pos) {
    const u32 member = idx - 2;
    if (member == 0 || member > 8)
        return false;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (idx < _8.size()) {
        ksys::act::acquireActor(&_8[idx]._e0, &accessor);
        if (accessor.hasProc() && accessor.isStateSleep()) {
            sead::Matrix34f mtx;
            mtx = accessor.getActorMtx();
            mtx.setTranslation(pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
            if (!(_80 & (1u << idx))) {
                _80 |= 1u << idx;
                ++_74;
                _50[member] = _74 % 2 != 0 ? _74 / 2 + 1 : -(_74 / 2);
            }
            return true;
        }
    }
    return false;
}

// NON_MATCHING: as sub_71007196EC (ours merges the member range test into one compare)
// 0x710071984c
bool Unk_7102450fa8::sub_710071984C(s32 idx, const sead::Matrix34f& mtx) {
    const u32 member = idx - 2;
    if (member == 0 || member > 8)
        return false;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (idx < _8.size()) {
        ksys::act::acquireActor(&_8[idx]._e0, &accessor);
        if (accessor.hasProc() && accessor.isStateSleep()) {
            accessor.setProperties(mtx, &sead::Vector3f::zero, &sead::Vector3f::zero, nullptr, false, 0, -1);
            if (!(_80 & (1u << idx))) {
                _80 |= 1u << idx;
                ++_74;
                _50[member] = _74 % 2 != 0 ? _74 / 2 + 1 : -(_74 / 2);
            }
            return true;
        }
    }
    return false;
}

// 0x7100719b78: the position of the entry `idx` in the phase member list.
// The original falls off the end when there is no member list (it does not store a false result).
bool Unk_7102450fa8::sub_7100719B78(sead::Vector3f* out, s32 idx) {
    if (_90)
        return _90->sub_710071CDCC(out, idx);
    return false;
}

void Unk_7102450fa8::sub_71007199A8() {
    _80 = 0;
    _50.fill(0);
    _70 = 0;
    _74 = 0;
}

s32 Unk_7102450fa8::sub_7100719F70() {
    if (_88) {
        const Phase phase = _88->m4();
        return phase;
    }
    return 0;
}

void Unk_7102450fa8::sub_710071A1C0(u32 a, u32 b) {
    _3f0.pushBack({a, b});
}

bool Unk_7102450fa8::sub_710071A200() const {
    if (_348 > 0) {
        if (_34c >= _348)
            return true;
    }
    return false;
}

void Unk_7102450fa8::sub_710071A258() {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (_8.size() > 1) {
        ksys::act::acquireActor(&_8[1]._e0, &accessor);
        if (accessor.hasProc() && !accessor.sub_7100D10FB8())
            _350.update();
    }
    _3e0.update();
}

void Unk_7102450fa8::sub_710071A2E8() {
    if (sub_710071A22C()) {
        _35c.update();
        return;
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    if (_8.size() > 1) {
        ksys::act::acquireActor(&_8[1]._e0, &accessor);
        if (accessor.hasProc() && !accessor.sub_7100D10FB8())
            _35c.update();
    }
}

// NON_MATCHING: the original loads both procs before ~ActorLinkConstDataAccess, compares after it and branches to the
// constant 1 (ours: cset after the destructor).
bool Unk_7102450fa8::sub_710071A38C(const ksys::act::ActorLinkConstDataAccess* accessor) {
    if (_3e0.value <= sead::Mathf::epsilon() || !_3d0.hasProc())
        return false;

    ksys::act::ActorLinkConstDataAccess other;
    ksys::act::acquireActor(&_3d0, &other);
    return other.getProc() == accessor->getProc();
}

bool Unk_7102450fa8::sub_710071A22C() {
    if (_3c8 <= 0.0f)
        return false;
    return _350.value <= sead::Mathf::epsilon();
}

bool Unk_7102450fa8::sub_710071A2D0() {
    return _35c.value <= sead::Mathf::epsilon();
}

void Unk_7102450fa8::sub_71007190CC(const ksys::MesTransceiverId& dest) {
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_18.getProc(nullptr)))
        actor->sendMessage(dest, ksys::MessageType(0x80000d9), this, true);
}

// 0x7100719d5c (placeholder name): removes the formation member (3 .. 10) that belongs to `actor`
// from the linked actor pool.
// NON_MATCHING: only the 33-entry search loop's exit compare differs (original: cmp #32 / b.le; ours:
// cmp #33 / b.lt). An s64 index gives the original latch but narrows the inlined Buffer::operator[]
// compare to 32 bits, so no natural source form produces both.
void Unk_7102450fa8::sub_7100719D5C(ksys::act::Actor* actor) {
    for (int i = 0; i <= 32; ++i) {
        if (!_8[i]._e0.hasProcById(actor))
            continue;

        if (i == 2 || u32(i - 2) > 8)
            return;

        sead::ScopedLock<sead::JobQueueLock> lock(&_9c);
        for (s32 j = 0; j < _a0.size(); ++j) {
            if (_a0[j]->hasProcById(actor)) {
                _a0.erase(j);
                break;
            }
        }
        return;
    }
}

void Unk_7102450fa8::sub_7100719ED0() {
    sead::ScopedLock<sead::JobQueueLock> lock(&_9c);
    _a0.clear();
}

Unk_7102450fa8::Unk_7102450fa8()
    : _38(Phase::_4), _3c(Phase::_0), _40(0.0f), _44(0.0f), _48(0.0f), _4c(0.0f), _74(0), _7c(0), _80(0),
      _88(nullptr), _90(nullptr), _98(0), _198(0), _248{}, _2b0(sUnk_7102450f80[0]), _348(0), _34c(0),
      _3c8(0.0f), _3cc(false), _438(0.0f), _43c(0.0f), _440(0.0f), _444(false) {
    // The shared navmesh material filter keeps the meta AI unit it decides for.
    sUnk_71025c8d10._8 = this;
}

Unk_7102450fa8::~Unk_7102450fa8() {
    _8.freeBuffer();
}

Unk_7102450fa8* Unk_7102450fa8::sub_7100718360(sead::Heap* heap) {
    return new (heap, std::nothrow) Unk_7102450fa8;
}

// 0x7100718f78 (placeholder name): searches the AI tree below `ai` for the Priest Boss node.
// NON_MATCHING: the instructions are the same but clang lays the "this node is the boss" return out
// after the loop and shares one return slot; the original falls through to it and returns ai directly.
uking::ai::PriestBoss* Unk_7102450fa8::sub_7100718F78(ksys::act::ai::Ai* ai) {
    if (sead::DynamicCast<uking::ai::PriestBoss>(ai))
        return static_cast<uking::ai::PriestBoss*>(ai);

    const s32 num_children = ai->getNumChildren();
    for (s32 i = 0; i < num_children; ++i) {
        auto* child = ai->getChild(i);
        if (sead::IsDerivedFrom<ksys::act::ai::Ai>(child)) {
            if (auto* found = sub_7100718F78(static_cast<ksys::act::ai::Ai*>(child)))
                return found;
        }
    }
    return nullptr;
}

// 0x710071a06c (placeholder name): whether the member registered in the ring buffer for `actor` is in the
// Calc state.
// NON_MATCHING: the member search loop compares `i < 33` where the original has `i <= 32`, and clang merges the
// two range tests of the ring-buffer entry into one unsigned compare (the original keeps them separate and
// carries a three-valued result into the return).
bool Unk_7102450fa8::sub_710071A06C(ksys::act::Actor* actor) {
    s32 idx = -1;
    for (s32 i = 0; i < 33; ++i) {
        if (_8[i]._e0.hasProcById(actor)) {
            idx = i;
            break;
        }
    }

    bool found = false;
    bool result = false;
    for (s32 i = 0; i < _3f0.size(); ++i) {
        const Unk4& entry = _3f0[i];
        if (entry._0 != idx)
            continue;

        found = true;
        if (entry._4 < 0 || entry._4 >= _8.size())
            break;

        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_8[entry._4]._e0, &accessor);
        if (accessor.hasProc())
            result = accessor.isStateCalc();
        break;
    }
    return found && result;
}

// 0x71007199bc (placeholder name): fills the AI's inline params for member `idx` (3 .. 10) with an empty AS
// name, the side offset, the duration and deceleration frames and the delay frames.
// NON_MATCHING: clang merges the member range test into one unsigned compare over idx - 3 (the original tests
// idx - 2 against zero and 8) and keeps the frame rate in a float register across the param calls (the
// original computes both delay factors into integer registers beforehand), so ours also saves d8.
bool Unk_7102450fa8::sub_71007199BC(ksys::act::ai::InlineParamPack* pack, s32 idx) {
    const u32 member = u32(idx - 2);
    if (member == 0 || member > 8)
        return false;
    if (!(_80 & (1u << idx)))
        return false;

    const s32 side = sead::Mathi::abs(_50[s32(member)]);
    const f32 fps = f32(ksys::VFR::instance()->getFrameRate());
    const s32 frames = s32(_48 * fps);
    const f32 duration = frames * side + frames * (side - 1) * -0.3f;
    const sead::Vector3f offset(side * _44, 0.0f, 0.0f);
    const s32 delay = (_74 / 2 - side) * s32(fps * _4c);

    pack->addString("", "ASName", -1);
    pack->addVec3(offset, "Offset", -1);
    pack->addInt(s32(duration), "DurationFrame", -1);
    pack->addInt(s32(duration) / 6, "DecelerationFrame", -1);
    pack->addInt(delay, "DelayFrame", -1);
    return true;
}
