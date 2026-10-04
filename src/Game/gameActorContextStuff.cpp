#include "Game/gameActorContextStuff.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"

#include <prim/seadScopedLock.h>

ActorContextStuff::ActorContextStuff(ksys::act::BaseProc* proc)
    : sead::TListNode<ActorContextStuff*>(this), _638(5, _648.getBufferPtr()),
      _670(5, _680.getBufferPtr()) {
    _708.acquire(proc, false);
}

ActorContextStuff::~ActorContextStuff() {
    erase();
    ksys::phys::System::instance()->removeSystemGroupHandler(_6b0);
}

// NON_MATCHING: the handler-index argument uses w2 rather than x2, and flag stores are scheduled differently.
void ActorContextStuff::sub_710065D8E4(sead::Heap* heap, bool a2) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    _6a8 = ksys::phys::System::instance()->sub_71012168C8(ksys::phys::ContactLayerType::Entity, 0);
    _6b0 = ksys::phys::System::instance()->addSystemGroupHandler(ksys::phys::ContactLayerType::Entity, 0);
    for (s32 i = 0; i < _70.size(); ++i) {
        _70[i].sub_710066074C(this, i, a2, _6a8, heap);
        _670.pushBack(&_70[i]);
    }
    if (a2)
        _68 |= 2;
    else
        _68 &= ~2;
}

// NON_MATCHING: the parameter pack and temporary string occupy different stack slots.
void ActorContextStuff::sub_710065DACC(const char* name, sead::Heap* heap) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    if (_6c >= _6b8.size())
        return;
    auto& handle = _6b8[_6c];
    if (handle.isAllocatedOrFailed())
        return;
    ksys::act::InstParamPack params;
    params->add(true, "IsPlayerPut");
    params->add(3, "@I");
    if (ksys::act::ActorCreator::instance()->requestCreateActor(name, heap, &handle, &params, nullptr, 2))
        ++_6c;
}

Unk_710243be90* ActorContextStuff::sub_710065E2B0(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i) {
        if (_638.at(i)->sub_7100661538(proc)) {
            _638.at(i)->sub_7100660AD8(static_cast<ksys::act::Actor*>(proc));
            _638.unsafeAt(i)->_48->setSystemGroupHandler(_6a8);
            return _638.at(i);
        }
    }
    return nullptr;
}

void ActorContextStuff::sub_710065E440() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i)
        _638.at(i)->sub_710066136C();
}

void ActorContextStuff::sub_710065E4BC(bool delete_actor) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    for (auto& handle : _6b8) {
        if (handle.isAllocatedOrFailed())
            handle.deleteProc();
    }
    _6c = 0;
    while (auto* entry = _638.popBack()) {
        entry->sub_71006613B0(delete_actor);
        _670.pushBack(entry);
    }
    auto* scene = GameSceneSubsys12::instance();
    if ((scene && scene->_a78.isBitOn(1)) || ksys::evt::Manager::instance()->hasActiveEvent()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_708, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool ActorContextStuff::sub_710065E638() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    if (!sub_710065E710())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_708, &accessor))
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    return true;
}

bool ActorContextStuff::sub_710065E710() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    bool cleared = false;
    for (auto& entry : _70) {
        cleared = entry.sub_71006606E8();
        if (!cleared)
            break;
    }
    return cleared;
}

bool ActorContextStuff::sub_710065E788(sead::Matrix34f* matrix, s32 index) {
    if (sub_710065E834())
        return sub_710065E88C(matrix, index);
    if (_68 & 2)
        return sub_710065DE90(matrix, index);
    return sub_710065ECF8(matrix, index);
}

bool ActorContextStuff::sub_710065E834() const {
    if (auto* scene = GameSceneSubsys12::instance()) {
        if (scene->_300.hasProc() && scene->_310 == this)
            return scene->sub_7100664F30();
    }
    return false;
}

// NON_MATCHING: stack allocation and matrix arithmetic/store scheduling differ.
bool ActorContextStuff::sub_710065ECF8(sead::Matrix34f* matrix, s32 index) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    if (index >= _638.size())
        return false;
    auto* entry = _638.at(index);
    if (!entry)
        return false;
    if (_68 & 1) {
        entry->sub_71006620F8(matrix);
    } else {
        ksys::act::ActorConstDataAccess accessor;
        // Both return values are discarded by the original before using the body matrix.
        ksys::act::acquireActor(&_708, &accessor);
        sead::Matrix34f body_matrix;
        accessor.sub_7100D11860(&body_matrix);
        sead::Vector3f position = body_matrix.getTranslation();
        sead::Vector3f offset;
        sead::Vector3f angles;
        if (auto* scene = GameSceneSubsys12::instance()) {
            const s32 count = sub_710065F044();
            scene->sub_7100664C30(&offset, count, index);
            sub_710065F12C(&angles, index);
        }
        offset.rotate(body_matrix);
        position += offset;
        sead::Matrix33f rotation;
        rotation.makeR(angles);
        sead::Matrix34CalcCommon<f32>::multiply(*matrix, body_matrix, rotation);
        matrix->setTranslation(position);
    }
    return true;
}

void ActorContextStuff::x_0() {
    for (auto& entry : _70)
        entry.sub_7100661988();
}

void ActorContextStuff::x() {
    for (auto& entry : _70)
        entry.sub_71006619DC();
}

// NON_MATCHING: Vector3's assignment emits scalar stores instead of the original aggregate copy.
void ActorContextStuff::sub_710065F12C(sead::Vector3f* out, s32 index) {
    if (out) {
        if (auto* scene = GameSceneSubsys12::instance())
            *out = scene->_bc4[index];
    }
}

// NON_MATCHING: register allocation exchanges the context count and scene registers.
void ActorContextStuff::sub_710065F16C(sead::Vector3f* out, s32 index) {
    if (out) {
        if (auto* scene = GameSceneSubsys12::instance()) {
            const s32 count = sub_710065F044();
            scene->sub_7100664C30(out, count, index);
        }
    }
}

f32 ActorContextStuff::sub_710065F1F0(f32 scale) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    if (auto* scene = GameSceneSubsys12::instance())
        return scene->sub_7100664B3C(this, scale);
    return 1.0f;
}

bool ActorContextStuff::sub_710065F954() const {
    if (auto* scene = GameSceneSubsys12::instance()) {
        if (scene->_300.hasProc() && scene->_310 == this)
            return scene->x();
    }
    return false;
}

// NON_MATCHING: the compiler combines the progress clamp and exchanges the saved float registers.
f32 ActorContextStuff::sub_710065FA28(ksys::act::BaseProc* proc, f32 time) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i) {
        if (!_638.at(i)->sub_7100661538(proc))
            continue;
        const s32 index = _638.unsafeAt(i)->_68;
        // 65fac8/65fad4 and65fb30/65fb38 retain the original nested lock/unlock pair.
        sead::ScopedLock<sead::CriticalSection> entry_lock(&_28);
        if (index < 0 || index >= _70.size())
            return 0.0f;
        const auto& entry = _70[index];
        if (entry._74 <= 0.0f)
            return entry._70 > time ? 0.0f : 1.0f;
        const f32 progress = (time - entry._70) / entry._74;
        if (progress < 0.0f)
            return 0.0f;
        if (progress > 1.0f)
            return 1.0f;
        return progress;
    }
    return 0.0f;
}

s32 ActorContextStuff::sub_710065F044() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    return _638.size();
}

// NON_MATCHING: the compiler uses an increasing induction variable for the unrolled reduction.
s32 ActorContextStuff::sub_710065F07C() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    s32 count = 0;
    for (s32 i = 0; i < _638.size(); ++i)
        count += (_638.unsafeAt(i)->_28 >> 3) & 1;
    return count;
}

void ActorContextStuff::sub_710065F9AC() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i)
        _638.at(i)->sub_71006618AC();
}

ksys::act::BaseProcLink* ActorContextStuff::sub_710065F80C(s32 index) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    if (index >= 0 && index < sub_710065F044())
        return &_638.at(index)->_30;
    return nullptr;
}

s32 ActorContextStuff::sub_710065F894(void*, sead::Buffer<sead::FixedSafeString<64>>* names) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    s32 copied = 0;
    for (s32 i = 0; i < count; ++i) {
        if (copied >= names->size())
            break;
        copied += _638.at(i)->sub_710066178C(&(*names)[copied]);
    }
    return copied;
}

// NON_MATCHING: the compiler shares removal/reindex code and chooses different loop indices.
bool ActorContextStuff::sub_710065F258(ksys::act::BaseProcLink* link, bool immediately) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    s32 found = -1;
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i) {
        if (_638.at(i)->sub_7100661540(*link)) {
            found = i;
            break;
        }
    }
    if (found < 0) {
        const s32 remaining = _638.size();
        for (s32 i = 0; i < remaining; ++i) {
            if (_638.at(i)->sub_7100661650(link)) {
                found = i;
                break;
            }
        }
    }
    if (found < 0)
        return false;
    auto* entry = _638.at(found);
    _638.erase(found);
    entry->sub_7100661494(immediately);
    _670.pushBack(entry);
    {
        sead::ScopedLock<sead::CriticalSection> reindex_lock(&_28);
        refreshEntryIndices();
        if (_638.size() < 1) {
            if (auto* scene = GameSceneSubsys12::instance())
                scene->sub_7100664484(6, this);
        }
    }
    --_6c;
    return true;
}

// NON_MATCHING: the compiler shares removal/reindex code and chooses different loop indices.
bool ActorContextStuff::sub_710065F544(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    s32 found = -1;
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i) {
        if (_638.at(i)->sub_7100661538(proc)) {
            found = i;
            break;
        }
    }
    if (found < 0) {
        const s32 remaining = _638.size();
        for (s32 i = 0; i < remaining; ++i) {
            if (_638.at(i)->sub_7100661548(proc)) {
                found = i;
                break;
            }
        }
    }
    if (found < 0)
        return false;
    auto* entry = _638.at(found);
    _638.erase(found);
    _670.pushBack(entry);
    {
        sead::ScopedLock<sead::CriticalSection> reindex_lock(&_28);
        refreshEntryIndices();
        if (_638.size() < 1) {
            if (auto* scene = GameSceneSubsys12::instance())
                scene->sub_7100664484(6, this);
        }
    }
    --_6c;
    return true;
}
