#include "KingSystem/Resource/resUnk_71024F9938.h"
#include <heap/seadHeapMgr.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <codec/seadHashCRC32.h>
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resBfRes.h"
#include "Game/gameGraphics.h"

namespace ksys::res {

Unk_71024f9938::Unk_71024f9938() = default;

// NON_MATCHING: the native destructor inlines pool cleanup with different register allocation.
Unk_71024f9938::~Unk_71024f9938() {
    sub_7100FDCF20();
}

// NON_MATCHING: typed pointer iteration and free-list reset scheduling differ.
void Unk_71024f9938::sub_7100FDCF20() {
    if (!_10.isBufferReady())
        return;
    for (const auto hash : _10)
        _8->sub_71012003D0(hash);
    if (!_10.isBufferReady())
        return;
    for (auto& hash : _10)
        _20.free(&hash);
    _10.clear();
    delete[] static_cast<u8*>(_20.work());
    _20.reset();
    _10 = {};
}

// NON_MATCHING: free-list initialization scheduling differs.
bool Unk_71024f9938::sub_7100FDD00C(const InitArg& arg) {
    const s32 capacity = arg.capacity;
    _8 = arg.resource;
    if (capacity < 1)
        return false;
    auto* work = new (arg.heap, 8, std::nothrow) u8[size_t(capacity) * 16];
    if (!work)
        return false;
    _20.setWork(work, 8, capacity);
    _10.setBuffer(capacity, work + size_t(capacity) * 8);
    return true;
}

bool Unk_71024f9938::sub_7100FDD0F0() const {
    return _8 != nullptr;
}

// NON_MATCHING: search control flow differs and the compiler removes the free-list null branch.
nn::gfx::ResTexture* Unk_71024f9938::sub_7100FDD100(const sead::SafeString& name,
                                                Unk_71024f9a70* loader) {
    const u32 hash = sead::HashCRC32::calcStringHash(name.cstr());
    u32* existing = nullptr;
    const s32 count = _10.size();
    for (s64 i = 0; i < count; ++i) {
        auto* entry = _10.unsafeAt(i);
        if (*entry == hash) {
            existing = entry;
            break;
        }
    }
    if (existing)
        return _8->sub_710120033C(hash);
    auto* texture = _8->sub_7101200038(hash, name, loader);
    if (texture && _10.size() < _10.capacity()) {
        auto* entry = static_cast<u32*>(_20.alloc());
        *entry = hash;
        _10.pushBack(entry);
    }
    return texture;
}

Unk_71024f9958::InitArg::InitArg() = default;
Unk_71024f9958::InitArg::~InitArg() = default;

Unk_71024f9958::Unk_71024f9958() = default;

Unk_71024f9958::~Unk_71024f9958() {
    sub_7100FDD264();
}

// NON_MATCHING: the compiler folds the native repeated heap guard across adjacent cleanup blocks.
void Unk_71024f9958::sub_7100FDD264() {
    if (!_8)
        return;
    sead::ScopedCurrentHeapSetter heap(_8);
    if (_20) {
        if (_20->getBufferPtr()) {
            const s32 count = _20->size();
            for (s32 i = 0; i < count; ++i) {
                if (auto* resource = (*_20)[i])
                    resource->sub_71011FFE74(_10->get(i));
            }
            _20->freeBuffer();
            _10->freeBuffer();
        }
        if (_8 && _20) {
            sead::ScopedCurrentHeapSetter heap(_8);
            delete _20;
            _20 = nullptr;
        }
        if (_8 && _10) {
            sead::ScopedCurrentHeapSetter heap(_8);
            delete _10;
            _10 = nullptr;
        }
    }
    if (_18) {
        _18->freeBuffer();
        if (_8 && _18) {
            sead::ScopedCurrentHeapSetter heap(_8);
            delete _18;
            _18 = nullptr;
        }
    }
    _8 = nullptr;
}

// NON_MATCHING: typed allocations, model casts and iteration scheduling differ.
bool Unk_71024f9958::sub_7100FDD4A8(const InitArg& arg) {
    if (!arg.heap) {
        stubbedLogFunction();
        return false;
    }
    if (_8)
        return false;
    _8 = arg.heap;
    const s32 model_count = (arg.model ? arg.model->getUnits().size() : 0) +
                            (arg.units ? arg.units->size() : 0) + (arg.unit ? 1 : 0);
    if (model_count > 0) {
        _18 = new (arg.heap, std::nothrow) sead::Buffer<gsys::ModelNW*>;
        if (!_18 || !_18->tryAllocBuffer(model_count, arg.heap, 8)) {
            sub_7100FDD264();
            return false;
        }
        s32 index = 0;
        if (arg.model) {
            const s32 count = arg.model->getUnits().size();
            for (s32 i = 0; i < count; ++i)
                (*_18)[index++] = sead::DynamicCast<gsys::ModelNW>(arg.model->getUnits().unsafeAt(i)->mModelUnit);
        }
        if (arg.units) {
            const s32 count = arg.units->size();
            for (s32 i = 0; i < count; ++i)
                (*_18)[index++] = arg.units->at(i);
        }
        if (arg.unit)
            (*_18)[index] = arg.unit;
    }
    _28 = arg.name;
    const s32 resource_count = (arg.resources ? arg.resources->size() : 0) +
                               (arg.resource ? 1 : 0);
    if (resource_count > 0) {
        _20 = new (arg.heap, std::nothrow) sead::Buffer<BfRes*>;
        if (!_20 || !_20->tryAllocBuffer(resource_count, arg.heap, 8)) {
            sub_7100FDD264();
            return false;
        }
        _10 = new (arg.heap, std::nothrow) sead::Buffer<sead::TListNode<Unk_71024f9958*>>;
        if (!_10 || !_10->tryAllocBuffer(resource_count, arg.heap, 8)) {
            sub_7100FDD264();
            return false;
        }
        s32 index = 0;
        if (arg.resources) {
            const s32 count = arg.resources->size();
            for (s32 i = 0; i < count; ++i) {
                auto* resource = arg.resources->at(i);
                (*_20)[index] = resource;
                if (resource) {
                    (*_10)[index].mData = this;
                    resource->sub_71011FFDF4(_10->get(index));
                }
                ++index;
            }
        }
        if (arg.resource) {
            (*_20)[index] = arg.resource;
            (*_10)[index].mData = this;
            arg.resource->sub_71011FFDF4(_10->get(index));
        }
    }
    const s32 count = _18->size();
    for (s32 i = 0; i < count; ++i) {
        if (auto* model = (*_18)[i])
            Graphics::instance()->sub_7100F2E0F4(model, nullptr);
    }
    return true;
}

void Unk_71024f9958::sub_7100FDD9C0(const nn::gfx::ResTexture* texture) {
    if (!_18 || !_18->getBufferPtr())
        return;
    const s32 count = _18->size();
    for (s32 i = 0; i < count; ++i) {
        if (auto* model = (*_18)[i])
            Graphics::instance()->sub_7100F2E0F4(model, nullptr);
    }
}

void Unk_71024f9958::sub_7100FDDA60(const sead::PtrArray<nn::gfx::ResTexture>* textures) {
    if (!_18 || !_18->getBufferPtr())
        return;
    const s32 count = _18->size();
    for (s32 i = 0; i < count; ++i) {
        if (auto* model = (*_18)[i]) {
            for (auto it = textures->dataBegin(), end = textures->dataEnd(); it != end; ++it)
                Graphics::instance()->sub_7100F2E0F4(model, *it);
        }
    }
}

}  // namespace ksys::res
