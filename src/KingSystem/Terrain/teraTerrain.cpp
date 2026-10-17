#include "KingSystem/Terrain/teraSystem.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <g3d/aglNW4FToNN.h>
#include "KingSystem/Terrain/teraResourceNode.h"
#include <cmath>
#include <prim/seadBitUtil.h>
#include <filedevice/seadFileDevice.h>
#include <nn/gfx/gfx_ResTexture.h>
#include <nn/g3d/ResModel.h>
#include <nn/g3d/ResMaterial.h>
#include <math/seadMathCalcCommon.h>
#include <common/aglDrawContext.h>
#include <gfx/seadViewport.h>
#include <mc/seadCoreInfo.h>
#include <thread/seadThread.h>

namespace ksys::tera {

bool Terrain::sub_710114D7B8() {
    return mImageResourceMgr->sub_7101131D64();
}

void* Terrain::sub_710114DEB8(s32 a, s32 b) {
    return &_360->mRecords[b * 3 + a];
}

void sub_71012EB7DC(CellQuadMaybe* out, const sead::Vector2f* a, const sead::Vector2f* b) {
    out->_18 = b->x - a->x;
    out->_1c = b->y - a->y;
    out->_20 = (b->x - a->x) + (a->x + a->x) - 1.0f;
    out->_24 = -((b->y - a->y) + (a->y + a->y) - 1.0f);
}

void sub_71012EB840(CellQuadMaybe* out, const sead::Vector2f* a, const sead::Vector2f* b) {
    out->_20 = b->x - a->x;
    out->_24 = b->y - a->y;
    out->_28 = sead::BitUtil::bitCast<u32>(a->x);
    out->_2c = sead::BitUtil::bitCast<u32>(a->y);
}

// NON_MATCHING: the original addresses the _8 pointer (entry + 8) once and reads _0 through -8;
// ours keeps the entry base instead (one ldur vs ldr difference).
void Core::Grass::sub_710114EE5C(bool on) {
    s32 count = mEntries.size();
    if (count == 0)
        return;
    Entry* entry = &mEntries[0];
    if (on) {
        do {
            entry->_8->mFlags |= 0x20;
            entry->_0->mFlags |= 0x20;
            ++entry;
        } while (--count);
    } else {
        do {
            entry->_8->mFlags &= ~0x20;
            entry->_0->mFlags &= ~0x20;
            ++entry;
        } while (--count);
    }
}

// Placeholder: the object whose float at 0x17ac and flag byte at 0xc 0x7101151a2c updates.
struct Unk_7101151A2C {
    u8 _0[0xc];
    u8 _c;
    u8 _d[0x17ac - 0xd];
    f32 _17ac;
};

void sub_7101151A2C(Unk_7101151A2C* self) {
    if (self->_17ac < 128.0f)
        self->_17ac = 128.0f;
    if (self->_c & 1) {
        self->_17ac = 0.0f;
        self->_c &= ~1;
    }
}

s32 Terrain::resourceIsLoading(u32 threshold, bool update) {
    if ((~_a58 & 6) != 0)
        return 0;
    if (mImageResourceMgr->_62a0 == 0)
        return 0;
    if (update) {
        mImageResourceMgr->sub_7101131D64();
    }
    return mImageResourceMgr->_626c > threshold ? 2 : 1;
}

bool Terrain::setPackModeMaybe(const ImageTypeMaybe& type, s32 index, u8 value) {
    s32 offset;
    switch (type.type) {
    case 0:
        offset = 0;
        break;
    case 1:
        offset = 1;
        break;
    case 3:
        if (type.index == 0)
            offset = 2;
        else if (type.index == 1)
            offset = 3;
        else
            return false;
        break;
    default:
        return false;
    }
    _388[offset][index] = value;
    return true;
}



void Terrain::clearImageResourceMgrFlagMaybe() {
    if (!mImageResourceMgr)
        return;
    auto& lock = mImageResourceMgr->mCS28;
    lock.lock();
    mImageResourceMgr->_6473 &= ~4;
    lock.unlock();
}

void Core::Grass::sub_7101151A1C() {
    _c |= 1;
}

u8* Core::Grass::sub_7101152DA0(s32 index) {
    return &mEntries[index]._274;
}

s32 sub_710114190C(const nn::g3d::ResMaterial* material, const char* name);

void Terrain::Unk4ae0::Unk_10::sub_710114161C() {
    _490[0] = _8->FindMaterialIndex("OpaqueNear");
    _490[1] = _8->FindMaterialIndex("OpaqueMiddle");
    _490[2] = _8->FindMaterialIndex("OpaqueFar");
    _490[3] = _8->FindMaterialIndex("Translucent");

    _6ec[0] = 11;
    _6ec[1] = 12;
    _6ec[2] = 13;
    _6ec[3] = 5;
    _6ec[4] = 3;

    const nn::g3d::ResMaterial* material = &_8->mMaterials[_490[0]];
    _6d0[0] = sub_710114190C(material, "tera_height");
    _6d0[1] = sub_710114190C(material, "tera_normal");
    _6d0[2] = sub_710114190C(material, "tera_material");
    _6d0[3] = sub_710114190C(material, "tera_material_linear");
    _6d0[4] = sub_710114190C(material, "tera_water");
    _6d0[5] = sub_710114190C(material, "_a0");
    _6d0[6] = sub_710114190C(material, "_n0");
}

SEAD_SINGLETON_DISPOSER_IMPL(Terrain)

// NON_MATCHING: the original stores `exists` after loading _428 (scheduling).
bool Terrain::sub_710114D928(System* system, Unk_7101106F44* area, const ImageTypeMaybe& type) {
    sead::FixedSafeString<256> path;
    mImageResourceMgr->sub_7101130FBC(&path, system, area, type);
    bool exists = false;
    _428->tryIsExistFile(&exists, path);
    return exists;
}

// NON_MATCHING: our sead::Viewport destructor is out of line (the original has no destructor call).
void Terrain::sub_710114C648(agl::DrawContext* context) {
    RenderSet& set = mRenderSets[sead::CoreInfo::getCurrentCoreId()];
    set.mRenderBuffer.bind(context);
    sead::Viewport viewport(set.mRenderBuffer);
    set.mRenderBuffer.fastClear(
        context, 0, 2, sead::Color4f::cBlack, 1.0f, 0, viewport,
        !(_a58 & 0x8000) || _a40->mThread != sead::ThreadMgr::instance()->getCurrentThread());
}

// NON_MATCHING: our sead::Viewport destructor is out of line (the original inlines it away), and the
// colour flag update is scheduled differently.
void Terrain::sub_710114C3C4(agl::DrawContext* context, const agl::TextureData& texture, u32 mip,
                             u32 layer, u32 index, u32 flags) {
    RenderSet& set = mRenderSets[sead::CoreInfo::getCurrentCoreId()];
    if (flags & 1) {
        set.mRenderBuffer.setRenderTargetColorNullAll();
        set.mRenderBuffer.setRenderTargetDepth(nullptr);
        set.mColorFlags = 0;
    }

    agl::RenderTargetColor& target = set.mColorTargets[index];
    target.applyTextureData(texture, target.getMipLevel(), target.getLayer());
    target.setLayer(layer);
    target.setMipLevel(mip);
    set.mRenderBuffer.setRenderTargetColor(&target, index);
    set.mColorFlags = (set.mColorFlags | 1 << index) | (flags << 29 & 0x80000000);

    if (!(flags & 2))
        return;

    const f32 width = static_cast<u32>(sead::Mathi::max(texture.getWidth() >> mip, 1));
    const f32 height =
        static_cast<u32>(sead::Mathi::max(texture.getMinHeight_(), texture.getHeight() >> mip));
    set.mRenderBuffer.setPhysicalArea(sead::BoundBox2f({0.0f, 0.0f}, {width, height}));
    set.mRenderBuffer.setVirtualSize({width, height});
    if (set.mColorFlags & 0x80000000) {
        sub_710114C648(context);
        return;
    }
    set.mRenderBuffer.bind(context);
    sead::Viewport viewport(set.mRenderBuffer);
    viewport.apply(context, set.mRenderBuffer);
}

// NON_MATCHING: our sead::Viewport destructor is out of line.
void Terrain::sub_710114C72C(agl::DrawContext* context, const agl::TextureData& texture,
                             const agl::GPUMemVoidAddr& storage, u32 mip, u32 flags) {
    RenderSet& set = mRenderSets[sead::CoreInfo::getCurrentCoreId()];
    if (flags & 1) {
        set.mRenderBuffer.setRenderTargetColorNullAll();
        set.mRenderBuffer.setRenderTargetDepth(nullptr);
        set.mColorFlags = 0;
    }

    agl::RenderTargetDepth& target = set.mDepthTarget;
    target.applyTextureData(texture, target.getMipLevel(), target.getLayer());
    target.setStorage(storage);
    target.setLayer(0);
    target.setMipLevel(mip);
    set.mRenderBuffer.setRenderTargetDepth(&target);
    set.mColorFlags = (set.mColorFlags | (flags << 29 & 0x80000000)) | 0x40000000;

    if (!(flags & 2))
        return;

    const f32 width = sead::Mathu::max(texture.getWidth(), 1);
    const f32 height = static_cast<u32>(
        sead::Mathi::max(texture.getMinHeight_(), texture.getHeight()));
    set.mRenderBuffer.setPhysicalArea(sead::BoundBox2f({0.0f, 0.0f}, {width, height}));
    set.mRenderBuffer.setVirtualSize({width, height});
    if (set.mColorFlags & 0x80000000) {
        sub_710114C648(context);
        return;
    }
    set.mRenderBuffer.bind(context);
    sead::Viewport viewport(set.mRenderBuffer);
    viewport.apply(context, set.mRenderBuffer);
}

agl::TextureSampler* Terrain::sub_710114CA64(s32 index, u32 flags) {
    RenderSet& set = mRenderSets[sead::CoreInfo::getCurrentCoreId()];
    agl::TextureSampler* sampler = &set.mSamplers[index];
    if (flags & 1) {
        sampler->setFilter(1, 1, 2);
        sampler->setWrap(NVN_WRAP_MODE_CLAMP_TO_EDGE, NVN_WRAP_MODE_CLAMP_TO_EDGE,
                         NVN_WRAP_MODE_CLAMP_TO_EDGE);
        sampler->setLOD(0.0f, 14.0f, 0.0f);
        sampler->resetCompSel();
        sampler->setBorderColor(sead::Color4f::cBlack);
    }
    return sampler;
}

void Terrain::sub_710114C9D0(agl::DrawContext* context) {
    RenderSet& set = mRenderSets[sead::CoreInfo::getCurrentCoreId()];
    if (set.mColorFlags & 1)
        set.mColorTargets[0].invalidateGPUCache(context);
    if (set.mColorFlags & 2)
        set.mColorTargets[1].invalidateGPUCache(context);
    set.mColorFlags = 0;
}

void Terrain::sub_710114D8C0(sead::Heap* heap, System* system) {
    _360->sub_71013008E4(heap, system);
}

void Terrain::sub_710114D8C8(sead::Heap* heap) {
    _360->sub_71013009C4(heap);
}

// NON_MATCHING: the flag selection has different temporary allocation.
void Terrain::sub_710114D804(bool enabled, const sead::Matrix44f* projection,
                           const sead::Matrix34f* view) {
    if (enabled)
        _a58 |= 0x1000;
    else
        _a58 &= ~0x1000;
    mProjectionMatrix = *projection;
    mViewMatrix = *view;
}

void Terrain::sub_710114D73C() {
    if ((~_a58 & 6) == 0)
        _360->sub_710130085C();
}

bool Terrain::sub_710114D7C8() const {
    return _a40->mThread == sead::ThreadMgr::instance()->getCurrentThread();
}

void Terrain::sub_710114DEAC(bool visible) {
    _360->sub_7101300AAC(visible);
}

void* Terrain::sub_710114DE10() const {
    return _370->_4ae0->_0;
}

const char* Terrain::sub_710114DE20(s32 index) const {
    return _370->_4ae0->_10.mMaterialNames->mNames[index]->name;
}

// NON_MATCHING: Unk370::sub_710113F34C is inlined here (the original calls it from another TU).
bool Terrain::sub_710114D920() const {
    return _370->sub_710113F34C();
}

s32 Terrain::sub_710114DE3C() const {
    return _370->_4ae0->_10._700;
}

void Terrain::sub_710114DDF8(u32 index, const sead::Vector3f* position, bool update) {
    _360->sub_7101300B4C(index, position, update);
}

void Terrain::sub_710114DE04(u32 index, const sead::Vector3f* position, bool update) {
    _360->sub_7101300F1C(index, position, update);
}

void Terrain::setPauseState(bool paused) {
    _a58 = paused ? _a58 | 8 : _a58 & ~u32(8);
    auto* grass = _360->_138;
    grass->mFlags = paused ? grass->mFlags | 0x10000 : grass->mFlags & ~u32(0x10000);
}

s32 Terrain::sub_710114DD84(s32 index) { return _360->mStates[index].mIndex; }

void Terrain::sub_710114DDA4(const Core::Unk_71013010d4* states, u32 count) {
    for (u32 i = 0; i < count; ++i)
        _360->sub_71013010D4(states[i], i);
}

Core::Grass* Terrain::sub_710114DE4C() { return _360->_138; }
Core::Grass* Terrain::sub_710114DE58() { return _360->_138; }
void* Terrain::sub_710114DE64() { return _360->_140; }
Core::Unk_140* Terrain::sub_710114DE70() { return _360->_140; }
// NON_MATCHING: the compiler orders the AND before the OR; the original orders them oppositely.
void Terrain::sub_710114DE7C(bool value) {
    if (value)
        _360->_37c |= 1;
    else
        _360->_37c &= ~1;
}
bool Terrain::sub_710114DE9C() { return (_360->_37c & 1) != 0; }
gsys::Model* Terrain::sub_710114DEE0() { return _360->_f8; }
bool Terrain::sub_710114DD40() { return false; }
f64 Terrain::sub_710114D9E8() { return _a48; }
void* Terrain::sub_710114DED4() { return _360->_f0; }
void* Terrain::sub_710114D8D0() { return _360 ? _360->_168 : nullptr; }
sead::Vector2f Terrain::sub_710114D8E4(const System* system) {
    return system->_10 * _3c8;
}
f32 Terrain::sub_710114D8F8(const System* system) { return system->_18 * _3c8; }

bool Core::Grass::sub_7101150BE0(const sead::Vector3f* pos, f32 radius, f32 value) {
    const Unk_7101150c24 arg{1, pos, radius, value, true, true, true, false, false};
    return (sub_7101150C24(&arg) & 1) != 0;
}

bool Core::Grass::sub_7101150F08(const sead::Vector3f* pos, f32 a, f32 b) {
    const Unk_7101150c24 arg{4, pos, a, b, true, false, false, false, false};
    return (sub_7101150C24(&arg) & 1) != 0;
}

// NON_MATCHING: the compiler stores the trailing flag after the preceding flags.
bool Core::Grass::sub_7101150F48(const sead::Vector3f* pos, f32 a, f32 b) {
    const Unk_7101150c24 arg{1, pos, a, b, true, true, false, false, false};
    return (sub_7101150C24(&arg) & 1) != 0;
}

// NON_MATCHING: the compiler separates adjacent flag stores and schedules argument stores differently.
bool Core::Grass::sub_7101150F88(const sead::Vector3f* pos, f32 a, f32 b, bool flag) {
    const Unk_7101150c24 arg{2, pos, a, b, true, false, false, false, flag};
    return (sub_7101150C24(&arg) & 1) != 0;
}

bool Core::Grass::sub_7101150FD4(const sead::Vector3f* pos, f32 a, f32 b) {
    const Unk_7101150c24 arg{8, pos, a, b, true, true, true, false, true};
    return (sub_7101150C24(&arg) & 1) != 0;
}

bool Core::Grass::sub_710115101C(const sead::Vector3f* pos, f32 radius) {
    const Unk_7101150c24 arg{1, pos, radius, 10.0f, false, false, true, false, true};
    return (sub_7101150C24(&arg) & 1) != 0;
}

bool Terrain::Unk370::sub_710113F34C() const {
    const Unk4ae0* data = _4ae0;
    if (!data->_10._888)
        return false;
    return data->_3ad8;
}

nn::gfx::ResTexture* MaterialTextureMaybe::getTexture() const {
    return agl::g3d::ResMaterial::GetTexture(material, index);
}

u32 MaterialTextureMaybe::getWidthMaybe() const {
    return getTexture()->GetTextureInfo()->GetWidth();
}

// NON_MATCHING: loop counter kept as 64-bit in ours (the original sign-extends a 32-bit counter); first lookup
// becomes a select.
void Terrain::Unk4ae0::Unk_10::setUpAttributeTableMaybe(sead::Heap* heap, const AttributeMap* main_map,
                                                        const AttributeMap* sub_map) {
    _738.tryAllocBuffer(_728->mCount, heap);

    const u32 count = _728->mCount;
    for (s32 i = 0; i < count; ++i) {
        const sead::SafeString main_name = _728->mNames[i]->name;
        const sead::SafeString sub_name = _730->mNames[i]->name;
        const s32* main = nullptr;
        if (const auto* node = main_map->find(main_name))
            main = &node->value();
        const s32* sub = nullptr;
        if (const auto* node = sub_map->find(sub_name))
            sub = &node->value();

        if (!main || !sub) {
            if (auto* debug = Terrain::instance()->_a50) {
                auto entry = debug->_70.log(
                    "マテリアルの対応アトリビュートが見つかりません -> No : %d | ファイル : %s | アトリビュート(Main) : %s | アトリビュート(Sub) : %s",
                    i, _718->mNames[i]->name, main_name.cstr(), sub_name.cstr());
                if (entry.buffer)
                    entry.buffer->setDisplayTime(10.0f);
            }
        }

        _738[i].a = main ? *main : -1;
        _738[i].b = sub ? *sub : -1;
    }
}

// NON_MATCHING: loop counter kept as 64-bit in ours (the original sign-extends a 32-bit counter); first lookup
// becomes a select.
void Water::setUpAttributeTable(sead::Heap* heap, const AttributeMap* main_map, const AttributeMap* sub_map) {
    mAttributes.tryAllocBuffer(_710->mCount, heap);

    const u32 count = _710->mCount;
    for (s32 i = 0; i < count; ++i) {
        const sead::SafeString main_name = _710->mNames[i]->name;
        const sead::SafeString sub_name = _718->mNames[i]->name;
        const s32* main = nullptr;
        if (const auto* node = main_map->find(main_name))
            main = &node->value();
        const s32* sub = nullptr;
        if (const auto* node = sub_map->find(sub_name))
            sub = &node->value();

        if (!main || !sub) {
            if (auto* debug = Terrain::instance()->_a50) {
                auto entry = debug->_70.log(
                    "[tera::Water::setUpAttributeTable] マテリアルの対応アトリビュートが見つかりません -> No : %d | ファイル : %s | アトリビュート(Main) : %s | アトリビュート(Sub) : %s",
                    i, _700->mNames[i]->name, main_name.cstr(), sub_name.cstr());
                if (entry.buffer)
                    entry.buffer->setDisplayTime(10.0f);
            }
        }

        mAttributes[i].main = main ? *main : -1;
        mAttributes[i].sub = sub ? *sub : -1;
    }
}

// NON_MATCHING: loop counter kept as 64-bit in ours (the original sign-extends a 32-bit counter); first lookup
// becomes a select.
void Terrain::Unk4ae0::Unk_f98::setUpAttributeTableMaybe(sead::Heap* heap, const AttributeMap* main_map,
                                                         const AttributeMap* sub_map) {
    _718.tryAllocBuffer(_708->mCount, heap);

    const u32 count = _708->mCount;
    for (s32 i = 0; i < count; ++i) {
        const sead::SafeString main_name = _708->mNames[i]->name;
        const sead::SafeString sub_name = _710->mNames[i]->name;
        const s32* main = nullptr;
        if (const auto* node = main_map->find(main_name))
            main = &node->value();
        const s32* sub = nullptr;
        if (const auto* node = sub_map->find(sub_name))
            sub = &node->value();

        if (!main || !sub) {
            if (auto* debug = Terrain::instance()->_a50) {
                auto entry = debug->_70.log(
                    "マテリアルの対応アトリビュートが見つかりません -> No : %d | ファイル : %s | アトリビュート(Main) : %s | アトリビュート(Sub) : %s",
                    i, _6f8->mNames[i]->name, main_name.cstr(), sub_name.cstr());
                if (entry.buffer)
                    entry.buffer->setDisplayTime(10.0f);
            }
        }

        _718[i].a = main ? *main : -1;
        _718[i].b = sub ? *sub : -1;
    }
}

const sead::Vector2f sUnk_7101EC503C[4] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {-0.5f, 0.5f}, {0.5f, 0.5f}};
const ImageTypeMaybe sUnk_7101EC54A8 = {{0xff, 0}};
const ImageTypeMaybe sUnk_7101EC54AC = {{0, 0}};
const ImageTypeMaybe sUnk_7101EC54B4 = {{1, 0}};
const ImageTypeMaybe sUnk_7101EC54B8 = {{3, 0}};
const ImageTypeMaybe sUnk_7101EC54BC = {{3, 1}};

s32 ImageTypeMaybe::sub_710114A5A0() const {
    return 1;
}

s32 ImageTypeMaybe::sub_710114A5A8() const {
    switch (type) {
    case 0:
        return 1;
    case 1:
        return 1;
    case 2:
        return 0;
    case 3:
        return 1;
    default:
        return 1;
    }
}

s32 ImageTypeMaybe::sub_710114A5CC() const {
    switch (type) {
    case 0:
        return 5;
    case 1:
        return 29;
    case 2:
        return 1;
    case 3:
        if (index == 0)
            return 29;
        if (index == 1)
            return 39;
        return 0;
    default:
        return 0;
    }
}

s32 ImageTypeMaybe::sub_710114A62C() const {
    return type != 1;
}

u32 getImageSizeMaybe(const ImageSizeMaybe& size) {
    static constexpr u32 sSizes[] = {0x20, 0x40, 0x60, 0x80, 0xc0, 0x100, 0x180, 0x200, 0x300, 0x400};
    return sSizes[u32(size)];
}

sead::Vector4f sub_7101123224(s32 index) {
    return Terrain::instance()->_370->_4ae0->_10._878[index];
}

// NON_MATCHING: the original stores each coordinate separately (x / z of both corners first, then the
// heights), reloading the inputs in between.
void sub_7101128B24(f32 low, f32 high, f32 t_min, f32 t_max, sead::BoundBox3f* box,
                    const sead::Vector2f& min, const sead::Vector2f& max,
                    const Unk_7101128B24Transform& transform) {
    box->setMin({min.x * transform.scale + transform.offset.x, (high - low) * t_min + low,
                 min.y * transform.scale + transform.offset.y});
    box->setMax({max.x * transform.scale + transform.offset.x, (high - low) * t_max + low,
                 max.y * transform.scale + transform.offset.y});
}

bool Unk_710250fc48::sub_710114EA70() const {
    if (!(_8 & 1))
        return false;
    auto* terrain = Terrain::instance();
    if (terrain && terrain->_a50 && (terrain->_a50->_18 & 8))
        return false;
    return true;
}

// 0x710250fc7c (placeholder name): a writable angle in degrees (initially 20) next to the
// Unk_710250fc48 vtable. Nothing in our build writes it, so as a TU static it would be folded.
f32 sUnk_710250FC7C KSYS_VISIBILITY_HIDDEN = 20.0f;

// NON_MATCHING: the original addresses sUnk_710250FC7C directly (a TU-local variable that is written
// elsewhere) instead of through the GOT, which also moves the _130 load.
f32 sub_7101152DC0(const Unk_7101152DC0* obj) {
    return sead::Mathf::max(obj->_130,
                            std::tan(sUnk_710250FC7C * sead::Mathf::pi2() / 360.0f * 0.5f));
}

// 0x7101152e10 (placeholder name): tan of the angle in 0x710250fc7c, converted from degrees.
f32 sub_7101152E10() {
    return std::tan(sUnk_710250FC7C * sead::Mathf::pi2() / 360.0f * 0.5f);
}

// ApertureMapsCollector::Unk_2948 code (0x7101127xxx) follows sub_7101123224; in teraScene.cpp it would inline into
// ApertureMapsCollector::sub_71010FFE70, which calls it.
void ApertureMapsCollector::Unk_2948::sub_710112727C(Unk_71010FEDBC* a, Unk_71010FEDBC* b, Unk_71010FEDBC* c,
                                     Unk_71010FEDBC* d, s32 x, s32 y) {
    _8 = a;
    _10 = b;
    _18 = c;
    _20 = d;
    _28 = d + 1;
    _38 = a->_20._8;
    _3c = a->_20._9 + x;
    _40 = d[1]._20._9 + y;
    _1310.sub_7101127304(a->_20._e >> (a->_20._9 + x));
    _6070.sub_7101127304(_28->_20._e >> (_28->_20._9 + y));
}

void Terrain::Unk_380::sub_71011382EC() {
    for (Item& item : mList.robustRange()) {
        mList.erase(&item);
        mFreeList.free(&item);
    }
}

}  // namespace ksys::tera

// 0x7101147e4c / 0x7101147e54 / 0x7101147e5c / 0x710114a588 (placeholder names): constant helpers of the
// terrain material classes; the CSV rows are unnamed.
void* sub_7101147E4C() {
    return nullptr;
}

s32 sub_7101147E54() {
    return 0;
}

s32 sub_7101147E5C() {
    return 1;
}

s32 sub_710114A588() {
    return 0;
}

// Placeholder: the object accessed at 0x7101148ba4 / 0x7101148bac (two u32 getters at +0x30 / +0x34).
struct Unk_7101148BA4Maybe {
    u8 _0[0x30];
    u32 _30;
    u32 _34;
};

u32 sub_7101148BA4(const Unk_7101148BA4Maybe* self) {
    return self->_30;
}

u32 sub_7101148BAC(const Unk_7101148BA4Maybe* self) {
    return self->_34;
}

namespace ksys::tera {

agl::TextureSampler* Terrain::Unk4ae0::Unk_10::getSamplerMaybe(s32 index) {
    return &_40[index];
}

s32 Terrain::Unk4ae0::Unk_10::getMaterialIndexMaybe(s32 index) const {
    return _490[index];
}

s32 Terrain::Unk4ae0::Unk_10::getShaderParamIndexMaybe(s32 index) const {
    return _6d0[index];
}

s32 Terrain::Unk4ae0::Unk_10::getConstantIndexMaybe(s32 index) const {
    return _6ec[index];
}

Terrain::Unk4ae0::Unk_10::TextureEntry* Terrain::Unk4ae0::Unk_10::getTextureEntryMaybe(s32 index) {
    return &_10[index];
}

agl::TextureSampler* Terrain::Unk4ae0::Unk_f98::getSamplerMaybe(s32 index) {
    return &_40[index];
}

s32 Terrain::Unk4ae0::Unk_f98::getMaterialIndexMaybe(s32 index) const {
    return _480[index];
}

s32 Terrain::Unk4ae0::Unk_f98::getShaderParamIndexMaybe(s32 index) const {
    return _6c8[index];
}

s32 Terrain::Unk4ae0::Unk_f98::getConstantIndexMaybe(s32 index) const {
    return _6e4[index];
}

Terrain::Unk4ae0::Unk_f98::TextureEntry* Terrain::Unk4ae0::Unk_f98::getTextureEntryMaybe(s32 index) {
    return &_10[index];
}

// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
u8* Unk_7101147678::getSamplerMaybe(s32 index) { return &_410[index * 0x170]; }
s32 Unk_7101147678::getMaterialIndexMaybe(s32 index) const { return _47c[index]; }
s32 Unk_7101147678::getShaderParamIndexMaybe(s32 index) const { return _6ac[index]; }
s32 Unk_7101147678::getConstantIndexMaybe(s32 index) const { return _6c0[index]; }
// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
TextureAccessorEntryMaybe* Unk_7101147678::getTextureEntryMaybe(s32 index) { return &_20[index]; }

// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
agl::TextureSampler* Unk_71011477F4::getSamplerMaybe(s32 index) { return &_860[index]; }
s32 Unk_71011477F4::getMaterialIndexMaybe(s32 index) const { return _474[index]; }
s32 Unk_71011477F4::getShaderParamIndexMaybe(s32 index) const { return _6b8[index]; }
s32 Unk_71011477F4::getConstantIndexMaybe(s32 index) const { return _74c[index]; }
// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
TextureAccessorEntryMaybe* Unk_71011477F4::getTextureEntryMaybe(s32 index) { return &_50[index]; }

// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
agl::TextureSampler* Unk_7101147970::getSamplerMaybe(s32 index) { return &_c60[index]; }
s32 Unk_7101147970::getMaterialIndexMaybe(s32 index) const { return _bd8[index]; }
s32 Unk_7101147970::getShaderParamIndexMaybe(s32 index) const { return _1118[index]; }
s32 Unk_7101147970::getConstantIndexMaybe(s32 index) const { return _126c[index]; }
// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
TextureAccessorEntryMaybe* Unk_7101147970::getTextureEntryMaybe(s32 index) { return &_80[index]; }

s32 Unk_7101147B38::getMaterialIndexMaybe(s32 index) const { return _430[index]; }
s32 Unk_7101147B38::getShaderParamIndexMaybe(s32 index) const { return _500[index]; }
s32 Unk_7101147B38::getConstantIndexMaybe(s32 index) const { return _624[index]; }
// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
TextureAccessorEntryMaybe* Unk_7101147B38::getTextureEntryMaybe(s32 index) { return &_160[index]; }

s32 Unk_7101147C48::getMaterialIndexMaybe(s32 index) const { return _8ac[index]; }
s32 Unk_7101147C48::getShaderParamIndexMaybe(s32 index) const { return _bb0[index]; }
s32 Unk_7101147C48::getConstantIndexMaybe(s32 index) const { return _cb4[index]; }
// NON_MATCHING: the original reaches the array through a negative offset (sub, not add); reason unknown.
TextureAccessorEntryMaybe* Unk_7101147C48::getTextureEntryMaybe(s32 index) { return &_100[index]; }

// Empty functions in the terrain TU (CSV nullsub_4571 .. nullsub_4583).
void sub_710114A598() {}
void sub_710114D638() {}
void sub_710114D7C0() {}
void sub_710114D7C4() {}
void sub_710114DD48() {}
void sub_710114DEEC() {}
void sub_710114DEF4() {}
void sub_7101152F30() {}
void sub_71011531BC() {}

s32 sub_710114D7A8() {
    return 0;
}

// 0x710114d908 / 0x710114d914: constants from the terrain constants block.
f32 sub_710114D908() {
    return 105.9f;
}

f32 sub_710114D914() {
    return 1792.0f;
}

KSYS_VISIBILITY_HIDDEN u8 sUnk_7102620B60;
KSYS_VISIBILITY_HIDDEN u8 sUnk_7102620B64;
KSYS_VISIBILITY_HIDDEN u8 sUnk_7102620B68;

u8 sub_710114E6E4() {
    return sUnk_7102620B60;
}

u8* sub_710114E6F0() {
    return &sUnk_7102620B64;
}

u8 sub_710114E6FC() {
    return sUnk_7102620B64;
}

u8* sub_710114E708() {
    return &sUnk_7102620B68;
}

// Constant virtuals (placeholder names).
void sub_71011475BC() {}
void sub_71011478DC() {}
void sub_7101147A58() {}
void sub_7101147D20() {}
void sub_7101147E44() {}
void sub_7101147E48() {}
void sub_7101148018() {}
void sub_7101148484() {}

// 0x7101147b24 / 0x7101147c34 (placeholder names): a 0x170-byte record at a negative offset.
u8* sub_7101147B24(u8* self, s32 index) {
    u8* record = &self[s64(index) * 0x170];
    return record - 0x20d0;
}

u8* sub_7101147C34(u8* self, s32 index) {
    u8* record = &self[s64(index) * 0x170];
    return record - 0x1800;
}

}  // namespace ksys::tera

void sub_710114E380(void* p) { ::operator delete(p); }
void sub_7101152F34(void* p) { ::operator delete(p); }
