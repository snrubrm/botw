#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <gsys/gsysModel.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

const f32 sUnk_7101ec27f4 = 1000000.0f;

// Counter at 0x710260ddd8 (placeholder name; used for the request ids stored in NavMeshCharacter::_290).
sead::Atomic<u32> sUnk_710260ddd8;

// 0x7100f809bc initializes this counter to 1. The allocator below is its only reader.
sead::Atomic<u32> sUnk_710260de50{1};

// NON_MATCHING: the compiler compares the bounded low half in 32-bit registers; the native comparison is 64-bit.
u32 sub_7100F7F92C() {
    while (true) {
        const u32 id = sUnk_710260de50.fetchAdd(1);
        if (u16(id) < 0x7fff)
            return id;
        sUnk_710260de50 = 1;
    }
}

u8 NavMeshCharacter::sub_7100F74F94(const NavMeshCharacter* nav) {
    if (!nav)
        return 0;
    return nav->_1d8;
}

bool NavMeshCharacter::sub_7100F74FA0(s32 type, s32 other) {
    const NavMeshCharacterType character_type = type;
    if (character_type == NavMeshCharacterType::Player)
        return true;
    return int(character_type) != NavMeshCharacterType::SmallAnimal &&
           other == NavMeshCharacterType::SmallAnimal;
}

void NavMeshCharacter::init(const InitArg& arg, sead::Heap* heap, HavokAI* havok_ai) {
    sub_7100F75680(arg, heap, havok_ai);
}

NavMeshCharacter::~NavMeshCharacter() {
    finalize();
}

void NavMeshCharacter::sub_7100F75AB8() {
    if (_2e0) {
        HavokAI::instance()->sub_7100F83A94(_2e0);
        _2e0 = nullptr;
    }
}

void NavMeshCharacter::sub_7100F75F8C(const sead::Vector3f& target) {
    auto lock = sead::makeScopedLock(_1e0);
    if (target.isNan())
        return;

    _d4[0].x = target.x;
    _d4[0].y = target.y;
    _d4[0].z = target.z;
    _1da = 1;
    if (!(_220.fetchOr(0x1000) & 0x1000))
        _290 = sUnk_710260ddd8.fetchAdd(1);
}

void NavMeshCharacter::sub_710019960C(sead::Vector3f* const* begin, sead::Vector3f* const* end) {
    auto lock = sead::makeScopedLock(_1e0);
    s32 count = 0;
    for (auto it = begin; count < 16 && it != end; ++it) {
        const sead::Vector3f* point = *it;
        if (point->isNan())
            return;
        _d4[count].x = point->x;
        _d4[count].y = point->y;
        _d4[count].z = point->z;
        ++count;
    }
    _1da = count;
    if (!(_220.fetchOr(0x1000) & 0x1000))
        _290 = sUnk_710260ddd8.fetchAdd(1);
}

void NavMeshCharacter::sub_7100394884(sead::ObjList<sead::Vector3f>::iterator begin,
                                      sead::ObjList<sead::Vector3f>::iterator end) {
    auto lock = sead::makeScopedLock(_1e0);
    s32 count = 0;
    for (auto it = begin; count < 16 && it != end; ++it) {
        if (it->isNan())
            return;
        _d4[count].x = it->x;
        _d4[count].y = it->y;
        _d4[count].z = it->z;
        ++count;
    }
    _1da = count;
    if (!(_220.fetchOr(0x1000) & 0x1000))
        _290 = sUnk_710260ddd8.fetchAdd(1);
}

void NavMeshCharacter::sub_710038AE34(sead::ObjList<sead::Vector3f>::iterator begin,
                                      sead::ObjList<sead::Vector3f>::iterator end) {
    auto lock = sead::makeScopedLock(_1e0);
    s32 count = 0;
    for (auto it = begin; count < 16 && it != end; ++it) {
        if (it->isNan())
            return;
        _d4[count].x = it->x;
        _d4[count].y = it->y;
        _d4[count].z = it->z;
        ++count;
    }
    _1da = count;
    if (!(_220.fetchOr(0x1000) & 0x1000))
        _290 = sUnk_710260ddd8.fetchAdd(1);
}

void NavMeshCharacter::sub_7100F75AF0() {
    if (_2e0)
        HavokAI::instance()->sub_7100F83A9C(_2e0);
}

Unk_7100f7e9f0 NavMeshCharacter::sub_7100F760F0(sead::Vector3f* out, const sead::Vector3f& to, f32 value) {
    if (to.isNan())
        return Unk_7100f7e9f0();

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F88FD0(this, out, to, value);
}

bool NavMeshCharacter::sub_7100F76168(f32 value, bool flag, NavMeshFaceCallback* callback) {
    if (sead::Mathf::isNan(value))
        return false;

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F87594(this, nullptr, getRadiusMaybe(), value, flag, callback);
}

bool NavMeshCharacter::sub_7100F761C8(const sead::Vector3f& pos, f32 value, bool flag,
                                      NavMeshFaceCallback* callback) {
    if (pos.isNan() || sead::Mathf::isNan(value))
        return false;

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F87594(this, &pos, getRadiusMaybe(), value, flag, callback);
}

void NavMeshCharacter::sub_7100F76260(const sead::Vector3f& pos) {
    auto lock = sead::makeScopedLock(_1e0);
    if (pos.isNan())
        return;
    _1b8.x = pos.x;
    _1b8.y = pos.y;
    _1b8.z = pos.z;
    _220 |= 0x2000;
    _220 &= ~0x20000u;
}

// NON_MATCHING: the original builds the mask from a stack temporary (`1 << bit`) and branches on `on`; ours is a csel
void NavMeshCharacter::sub_7100F76344(bool on) {
    _10->_170.changeBit(1, on);
}

Unk_7100f7e9f0 NavMeshCharacter::sub_7100F76078(sead::Vector3f* out, const sead::Vector3f& to,
                                                f32 a3) {
    if (to.isNan())
        return Unk_7100f7e9f0();

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F88B1C(this, out, to, a3);
}

void NavMeshCharacter::sub_7100F7604C(f32 value) {
    _10->_78->_1c = value;
}

void NavMeshCharacter::sub_7100F7605C(f32 value) {
    _10->_78->_18 = value;
}

void NavMeshCharacter::sub_7100F7606C(u32 value) {
    _10->_16c = value;
}

void NavMeshCharacter::sub_7100F76314() {
    _220 |= 0x20000;
    _220 &= ~0x2000u;
}

void NavMeshCharacter::sub_7100F765E8(const sead::Vector3f& pos) {
    if (pos.isNan())
        return;

    auto lock = sead::makeScopedLock(_1e0);
    _254.x = pos.x;
    _254.y = pos.y;
    _254.z = pos.z;
    _220 |= 4;
}

void NavMeshCharacter::sub_7100F76694(const sead::Vector3f& direction) {
    if (direction.isNan())
        return;

    sead::Vector3f dir(direction.x, 0.0f, direction.z);
    if (dir.normalize() != 0.0f) {
        _260 = dir;
        _248 = dir;
    }
}

void NavMeshCharacter::sub_7100F76380(const sead::Vector3f& pos, const sead::Vector3f& dir_a,
                                      const sead::Vector3f& vec, const sead::Vector3f& dir_b) {
    sub_7100F765E8(pos);

    if (!dir_a.isNan()) {
        sead::Vector3f dir(dir_a.x, 0.0f, dir_a.z);
        if (dir.normalize() != 0.0f)
            _260 = dir;
    }

    if (!vec.isNan()) {
        _26c.x = vec.x;
        _26c.y = vec.y;
        _26c.z = vec.z;
    }

    if (!dir_b.isNan()) {
        sead::Vector3f dir(dir_b.x, 0.0f, dir_b.z);
        if (dir.normalize() != 0.0f)
            _278 = dir;
    }
}

void NavMeshCharacter::sub_7100F7D2C8() {
    s32 value = _d0.load();
    while (value >= 1) {
        if (_d0.compareExchange(value, value - 1))
            break;
        value = _d0.load();
    }
}

// NON_MATCHING: the original hoists a zero-extension of `expected` (and x9, x1, #0xffffffff) out of the
// compare-exchange loop and rotates the loop so that a failed exchange jumps straight back to ldxr
void NavMeshCharacter::sub_7100F7D308(s32 expected) {
    while (true) {
        const s32 value = _d0.load();
        if (value < 1 || value - 1 != expected)
            return;
        if (_d0.compareExchange(value, expected))
            return;
    }
}

void NavMeshCharacter::sub_7100F76778() {
    _220 |= 0x4000;
}

void NavMeshCharacter::sub_7100F76790() {
    _220 |= 0x8000;
}

void NavMeshCharacter::sub_7100F7D350() {
    _d0 = 0;
}

namespace {
struct TypeParams {
    f32 _38;
    f32 _3c;
    f32 _40;
    f32 _48;
};

const TypeParams sTypeParams[NavMeshCharacterType::size()] = {
    {1.0f, 1.0f, 1.0f, 0.01f}, {2.0f, 1.0f, 1.0f, 0.1f},   {1.0f, 1.0f, 1.0f, 0.01f},
    {1.0f, 0.1f, 1.0f, 0.01f}, {1.0f, 1.0f, 1.0f, 0.01f},  {1.0f, 1.0f, 1.0f, 0.01f},
    {1.0f, 1.0f, 1.0f, 0.01f}, {1.0f, 1.0f, 1.0f, 0.01f},  {1.0f, 1.0f, 1.0f, 0.01f},
    {2.0f, 0.5f, 50.0f, 0.1f}, {1.0f, 1.0f, 10.0f, 0.1f},  {2.0f, 0.5f, 50.0f, 0.1f},
    {1.0f, 1.0f, 10.0f, 0.01f}, {1.0f, 1.0f, 10.0f, 0.01f}, {1.0f, 1.0f, 10.0f, 0.01f},
    {1.0f, 1.0f, 1.0f, 0.01f}, {1.0f, 2.0f, 1.0f, 0.01f},  {1.0f, 1.0f, 1.0f, 0.01f},
    {1.0f, 1.0f, 1.0f, 0.01f}, {1.0f, 1.0f, 1.0f, 0.01f},  {1.0f, 1.0f, 1.0f, 0.01f},
};
}  // namespace

void NavMeshCharacter::sub_7100F7E598(InitArg* arg, NavMeshCharacterType type) {
    arg->_38 = sTypeParams[type]._38;
    arg->_3c = sTypeParams[type]._3c;
    arg->_40 = sTypeParams[type]._40;
    arg->_48 = sTypeParams[type]._48;
    switch (type) {
    case NavMeshCharacterType::Player:
        arg->_58 = 1;
        arg->_59 = 1;
        break;
    case NavMeshCharacterType::Horse:
    case NavMeshCharacterType::NPC:
    case NavMeshCharacterType::NPCGoron:
    case NavMeshCharacterType::NPCSwimmer:
        arg->_54 = 10;
        break;
    default:
        break;
    }
}

void NavMeshCharacter::sub_7100F7E624(NavMeshCharacterUnk8A0* obj, s32 type) {
    const auto& params = sTypeParams[type];
    obj->_64 = params._38;
    obj->_70 = params._3c;
    obj->_74 = params._40;
    obj->_68 = params._48;
}

void NavMeshCharacter::sub_7100F7D1B4(const NavMeshCharacter* other) {
    _a8[0] = other->_8->_98;
    _d0 = 1;
}

// NON_MATCHING: register allocation only (the original keeps the index in w8 and moves it to w0 in each
// return block; ours keeps it in w0)
s32 NavMeshCharacter::sub_7100F7D1CC(const NavMeshCharacter* other) {
    s32 result = -1;
    const s32 index = _d0.load();
    if (index <= 9) {
        _a8[index] = other->_8->_98;
        if (_d0.compareExchange(index, index + 1))
            result = index;
    }
    return result;
}

// NON_MATCHING: register allocation only (the original returns through w8, like sub_7100F7D1CC)
s32 NavMeshCharacter::sub_7100F7D234(const NavMeshObjMaybe* other) {
    const s32 index = _d0.load();
    if (index > 9)
        return -1;
    _a8[index] = other->_ac;
    if (!_d0.compareExchange(index, index + 1))
        return -1;
    return index;
}

void NavMeshCharacter::sub_7100F7D298(s32 index, const NavMeshCharacter* other) {
    if (index < 0 || _d0.load() <= index)
        return;
    _a8[index] = other->_8->_98;
}

void NavMeshCharacter::sub_7100F75F3C(u8 value) {
    auto lock = sead::makeScopedLock(_1e0);
    _1d9 = value;
    _220 |= 8;
}

NavMeshObjMaybe::NavMeshObjMaybe()
    : _8(nullptr), _10(nullptr), _98(nullptr), _a0(nullptr), _a8(0), _ac(0) {}

NavMeshObjMaybe::~NavMeshObjMaybe() {
    sub_7100F7F6A0();
}

// NON_MATCHING: the native wrapper clears the upper mode bits before forwarding.
void NavMeshObjMaybe::sub_7100F7EF8C(RigidBody* body, u32 mode, bool forceTolerance,
                                    NavMeshSubMaterial material, u16 group,
                                    const sead::SafeString& name) {
    sub_7100F7EF9C(body->getHkBody(), mode, forceTolerance, material, group, name);
}

bool NavMeshObjMaybe::sub_7100F7F428(RigidBody* body) {
    return sub_7100F7F430(body->getHkBody());
}

void NavMeshObjMaybe::sub_7100F7FAC8(bool on) {
    if (!_8)
        return;
    const u32 value = _ac & 0xffff;
    if (value < 15 || value > 21)
        return;
    auto* havok_ai = _98 ? _98 : HavokAI::instance();
    havok_ai->sub_7100F831C0(this, on);
}

void NavMeshObjMaybe::sub_7100F7FB0C(bool on) {
    if (_8) {
        auto* havok_ai = _98 ? _98 : HavokAI::instance();
        havok_ai->sub_7100F832B4(this, on);
    }
}

Unk_71024f67c8::~Unk_71024f67c8() = default;

Unk_71024f67c8* Unk_71024f67c8::sub_7100F73640(const InitArg& arg, sead::Heap* heap) {
    auto* chain = new (heap) Unk_71024f67c8;
    chain->sub_7100F73714(arg, heap);
    return chain;
}

void Unk_71024f67c8::sub_7100F73B7C() {
    mEntries.freeBuffer();
    delete this;
}

// NON_MATCHING: the original builds the identity on the stack before the loop body and orders the
// scale copies differently (scheduling / regalloc).
void Unk_71024f67c8::sub_7100F73C7C(bool reset) {
    if (reset)
        mModel->getUnits()(0)->mModelUnit->clearBoneLocalMatrix();

    for (s32 i = 0; i < mEntries.size(); ++i) {
        const sead::Matrix34f base = sead::Matrix34f::ident;
        Entry& entry = mEntries[i];
        sead::Matrix34f local;
        const auto& key = entry.mBone.getKey();
        mModel->getUnits()(key.model_unit_index)
            ->mModelUnit->getBoneLocalMatrix(&local, &entry.mScale, key.bone_index);
        if (i == 0)
            entry._54 = sead::Vector3f::ones;
        else
            entry._54 = mEntries[i - 1].mScale;
        local.m[0][3] *= entry._54.x;
        local.m[1][3] *= entry._54.y;
        local.m[2][3] *= entry._54.z;
        entry._60 = local;
        entry._90.setMul(base, local);
    }
}

void Unk_71024f67c8::sub_7100F73E50() {
    sead::Matrix34f parent = sead::Matrix34f::ident;
    for (s32 i = 0; i < mEntries.size(); ++i) {
        Entry& entry = mEntries[i];
        entry._90.setMul(parent, entry._60);
        parent = entry._90;
    }
}

// NON_MATCHING: the original clamps with compares and selects (fcsel / fccmp), ours with fmin.
void Unk_71024f67c8::sub_7100F74E20(f32 value) {
    _108 = sead::Mathf::clamp(value, 0.0f, 1.0f);
}

sead::Matrix34f* Unk_71024f67c8::sub_7100F74E44() {
    return &mEntries[_c8]._90;
}

sead::Matrix34f* Unk_71024f67c8::sub_7100F74E68() {
    return &mEntries[_cc]._90;
}

sead::Matrix34f* Unk_71024f67c8::sub_7100F74E8C() {
    return &mEntries[_d0]._90;
}

sead::Matrix34f* Unk_71024f67c8::sub_7100F74EB0() {
    return &mEntries[_d4]._90;
}

// NON_MATCHING: the original loads the scale components with ldp and divides in a different order.
void Unk_71024f67c8::sub_7100F74ED4(const sead::Matrix34f& matrix) {
    Entry& entry = mEntries[_d0];
    entry._60 = matrix;
    entry._60.m[0][3] /= entry.mScale.x;
    entry._60.m[1][3] /= entry.mScale.y;
    entry._60.m[2][3] /= entry.mScale.z;
    mModel->setBoneLocalMatrix(entry.mBone.getKey(), entry._60, entry.mScale);
}

sead::Matrix34f* Unk_71024f67c8::sub_7100F74F44() {
    return &mEntries[_d4]._60;
}

void Unk_71024f67c8::sub_7100F74F68(s32 index) {
    Entry& entry = mEntries[index];
    mModel->setBoneLocalMatrix(entry.mBone.getKey(), entry._60, entry.mScale);
}

}  // namespace ksys::phys

// Constant virtuals in the physics address range (placeholder names, no data references).
s32 sub_7100F7C5D0() { return 1; }
s32 sub_7100F7C5D8() { return 0; }
s32 sub_7100F7C6E0() { return 1; }
s32 sub_7100F7C9A8() { return 1; }
s32 sub_7100F7C9B0() { return 1; }
s32 sub_7100F7D0F4() { return 1; }
s32 sub_7100F7D0FC() { return 1; }
s32 sub_7100F7E514() { return 1; }
s32 sub_7100F7E51C() { return 1; }
s32 sub_7100F7E524() { return 1; }
s32 sub_7100F7E580() { return 1; }
s32 sub_7100F7E588() { return 1; }
s32 sub_7100F7E590() { return 1; }
s32 sub_7100F84290() { return 1; }
s32 sub_7100F84298() { return 1; }
s32 sub_7100F842A0() { return 1; }
s32 sub_7100F893C4() { return 1; }
s32 sub_7100F89488() { return 1; }
s32 sub_7100F89490() { return 1; }
s32 sub_7100F89498() { return 1; }
s32 sub_7100F80858() { return 160; }
