#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Framework/frmFramework.h"
#include "Game/gameRoot38.h"
#include "Game/gameGraphics.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/System/StagePreActorCache.h"
#include "KingSystem/Graphics/gfxForestRenderer.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadPtrUtil.h>
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/System/BasicProfiler.h"
#include "KingSystem/ActorSystem/LOD/actLODMgr.h"
#include "KingSystem/ksysDebugInput.h"
#include <cstring>
#include <utility>

namespace ksys::tera {

// NON_MATCHING: clamp comparisons and constant loads are scheduled differently.
s32 sub_710107F9C4(f32 x) {
    return sead::Mathi::clamp(sead::Mathf::floor(x / 1000.0f) + 5, 0, 9);
}

// NON_MATCHING: clamp comparisons and constant loads are scheduled differently.
s32 sub_710107FA0C(f32 z) {
    return sead::Mathi::clamp(sead::Mathf::floor(z / 1000.0f) + 4, 0, 7);
}

// The 4 x 4 sub-cell index of x / z inside their 1000-unit cell (bit 2 / 3: the 500-unit half).
// NON_MATCHING: the shift of the x half bit is scheduled after the z compare (one lsl moves).
s32 sub_710107FA54(f32 x, f32 z) {
    f32 local_x = x - sead::Mathf::floor(x / 1000.0f) * 1000.0f;
    f32 local_z = z - sead::Mathf::floor(z / 1000.0f) * 1000.0f;
    const bool right = local_x >= 500.0f;
    const bool bottom = local_z >= 500.0f;
    local_z -= bottom ? 500.0f : 0.0f;
    local_x -= right ? 500.0f : 0.0f;
    return (local_x >= 250.0f) + (local_z >= 250.0f) * 2 + right * 4 + bottom * 8;
}

bool System::sub_71011171AC(s32 index) {
    return (mScenes[index].collector->_2998 >> 1) & 1;
}

TeraManagerMaybe sUnk_710260B220 KSYS_VISIBILITY_HIDDEN;
KSYS_VISIBILITY_HIDDEN u8 sUnk_710260B184;
KSYS_VISIBILITY_HIDDEN u8 sUnk_710260B188;
// Callback 0x7101200AC0 records terrain bit indices 0..9 here through sub_7100F3F84C.
KSYS_VISIBILITY_HIDDEN u32 sUnk_710260B18C;
KSYS_VISIBILITY_HIDDEN void* sUnk_710260B190;
KSYS_VISIBILITY_HIDDEN void* sUnk_710260B198;

void resetStageRenderersMaybe() {
    if (Terrain::instance()->isGrassEnabled())
        Terrain::instance()->sub_710114DE4C()->sub_7101151A1C();
    if (auto* height_map = Graphics::instance()->getUnk_ab0())
        height_map->_e48 |= 0x80000000;
    auto* terrain = Terrain::instance();
    sUnk_710260B220._18 = 0;
    if (terrain) {
        auto* placement = map::PlacementMgr::instance();
        if (placement && placement->mTeraSystem) {
            terrain->sub_710114DE4C()->mFlags &= ~0x8000;
            terrain->sub_710114DE4C()->sub_7101150A70();
        }
    }
    if (auto* forest = StagePreActorCache::instance()->getForestRenderer())
        forest->sub_7100F03B68();
}

void sub_7100F3DF74() {
    if (sUnk_710260B220._14 != 0 && sUnk_710260B220._14 != 7)
        return;
    if (auto* mgr = act::LODMgr::instance())
        mgr->requestDrawModels();
    if (auto* input = DebugInput::instance())
        input->update();
}

void updateInitialCameraPosMaybe(const sead::Vector3f* pos) {
    sUnk_710260B220._b8 = *pos;
}

// 0x7100f3f784 (CSV TeraResource::loadTerrainModel; the class name is a guess): starts the terrain model load.
void loadTerrainModel() {
    ksys::BasicProfiler::Scope profiler("TeraResource");
    res::LoadRequest request(0, 1, false);
    request._68 = &sUnk_710260B220._1c0;
    request.mRequester = "ksys.cpp";
    request._8 = true;
    sUnk_710260B220._1c0._a = true;
    sUnk_710260B220._260.requestLoad("Model/Terrain.bfres", &request, nullptr);
}

void waitForTerrainModelReady() {
    sUnk_710260B220._260.waitForReady();
    sUnk_710260B220._260.parseResource(&sUnk_710260B220._1c0);
}

// Placeholder: a two-word physics record.
struct Unk_7100F418C8Maybe {
    u32 _0;
    u32 _4;
};

bool checkTeraSystemStatus() {
    if (sUnk_710260B220._14 != 0 && sUnk_710260B220._14 != 7)
        return true;
    if (!sUnk_710260B220._b0)
        return false;
    return static_cast<u8*>(sUnk_710260B220._b0)[0x13d09] != 0;
}

void sub_7100F418A0(void* value) {
    sUnk_710260B190 = value;
}

void sub_7100F418AC(void* value) {
    sUnk_710260B198 = value;
}

void sub_7100F418B8(void* value) {
    sUnk_710260B220._a8 = value;
}

void sub_7100F418C8(Unk_7100F418C8Maybe* obj) {
    obj->_0 = 0;
    obj->_4 = 0;
}

void sub_7100F418D0(Unk_7100F418C8Maybe* obj, u32 value) {
    obj->_0 = 0;
    obj->_4 = value;
}

u32 sub_7100F418F8(const Unk_7100F418C8Maybe* obj) {
    return obj->_4;
}

// 0x7100f41900 (unnamed in the CSV): whether either word of the record is non-zero.
bool sub_7100F41900(const Unk_7100F418C8Maybe* obj) {
    return obj->_0 != 0 || obj->_4 != 0;
}

System* System::instance() {
    return sUnk_710260B220.mSystem;
}



void sub_7101128AC0(f32* out, const f32* a, const f32* b, const f32* transform) {
    out[0] = a[0] * transform[0] + transform[2];
    out[1] = a[1] * transform[0] + transform[3];
    out[2] = b[0] * transform[0] + transform[2];
    out[3] = b[1] * transform[0] + transform[3];
}

void terrainSetCameraLookAtPos(const sead::Vector3f* pos) {
    Terrain* terrain = Terrain::instance();
    if (!terrain)
        return;
    const sead::Vector3f* target = pos;
    if (sUnk_710260B188)
        target = &sUnk_710260B220._c4;
    terrain->sub_710114DE04(0, target, false);
}

void Terrain::Unk4ae0::Unk_10::sub_71011406CC(u32 count) {
    _700 = count;
}

// 0x7101140810 (unnamed in the CSV): runs the material name setup, takes the material count from the
// name table and then allocates the scale table.
void Terrain::Unk4ae0::Unk_10::sub_7101140810(sead::Heap* heap) {
    sub_7101140850();
    _700 = _8 ? s32(mMaterialNames->mCount) : 0;
    sub_71011406D4(heap);
}

// 0x71011406d4 (placeholder name): allocates the scale table for the _700 materials, initialises the
// material texture (R8_G8_B8_A8, one level) and stores the scale of every table entry.
// NON_MATCHING: the fill loop keeps an entry guard the original does not have (a register choice),
// and the 0.25 / 1.0 pair of the second loop is materialised differently; everything else follows.
void Terrain::Unk4ae0::Unk_10::sub_71011406D4(sead::Heap* heap) {
    const s32 count = _700;
    _748 = 0;
    _888 = false;
    if (count == 0)
        return;

    if (count > 0) {
        auto* buffer = new (heap, 8) sead::Vector4f[count];
        if (buffer) {
            const sead::Vector4f value(sead::Color4f::cElementMin, sead::Color4f::cElementMin,
                                       sead::Color4f::cElementMin, sead::Color4f::cElementMax);
            sead::Vector4f* p = buffer;
            for (sead::Vector4f* const end = buffer + count; p != end; ++p)
                *p = value;
            _878.setBuffer(count, buffer);
        }
    }

    initTextureBufferMaybe(&_750, heap, 0, agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm, 1, 1,
                           1, true, true);

    for (u32 i = 0; i < u32(_878.size()); ++i)
        _878(i) = sead::Vector4f(0.25f, 0.25f, 0.25f, 1.0f);
}

void System::sub_7101117874() {
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].collector->sub_7101101578(this, 0xff0000);
}

u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    auto* info = system->sub_710111F504();
    return sub_710110AA5C(0.0f, Terrain::instance()->_3cc, out_height, xz, &info->_20, info);
}

// NON_MATCHING: the original stores area = 0 after loading Vector2f::zero (scheduling).
// NON_MATCHING: the original inlines sub_710110AC74 (ours calls it, as in sub_7101108C44).
u32 sub_71011091DC(f32 a, f32 b, f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info, s32 index,
                   s32 level) {
    s32 area = 0;
    sead::Vector2f pos = sead::Vector2f::zero;
    const u32 result = sub_7101108AE8(&pos, &area, *xz, *info_20, *info, index);
    if (result != 0) {
        Unk_7101108C44Arg arg;
        arg.table = info_20->table;
        arg.index = area;
        arg._c = false;
        TexelPosMaybe texel;
        sub_710110AC74(pos.x, pos.y, &arg, &texel, level);
        const sead::Vector3f value = sub_710110C930(&arg, &texel, level);
        out_normal->set(-value.x, 1.0f, -value.y);
        const f32 scale = static_cast<f32>(info_20->_e) / info->mAreas[area].size;
        out_normal->x = scale * out_normal->x;
        out_normal->y = 1.0f / (b - a);
        out_normal->z = scale * out_normal->z;
        out_normal->normalize();
        *out_height = (b - a) * value.z + a;
    }
    return result;
}

u32 sub_71011094A0(f32* out_height, const sead::Vector2f* xz, System* system, s32 index, s32 flag) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    const s32 height_flag = flag != 0 && (system->mScenes(0).collector->_2998 & 0x20) ? flag : 0;

    auto* areas = system->sub_710111F4F0();
    const f32 scale = Terrain::instance()->_3cc;
    s32 area = 0;
    sead::Vector2f pos = sead::Vector2f::zero;
    const u32 result = sub_7101108AE8(&pos, &area, *xz, areas->_20, *areas, index);
    if (result != 0) {
        Unk_7101108C44Arg arg;
        arg.table = areas->_20.table;
        arg.index = area;
        arg._c = false;
        *out_height = scale * sub_7101108C44(pos, &arg, height_flag) + 0.0f;
    }
    return result;
}

u32 sub_71011096D0(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system, s32 index, s32 flag) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    const s32 height_flag = flag != 0 && (system->mScenes(0).collector->_2998 & 0x20) ? flag : 0;
    auto* areas = system->sub_710111F4F0();
    return sub_71011091DC(0.0f, Terrain::instance()->_3cc, out_height, out_normal, xz, &areas->_20,
                          areas, index, height_flag);
}

// NON_MATCHING: one instruction moved (the zero store of `index` is scheduled earlier than the
// original).
// Placeholder name: the height at `xz` (like sub_71011094A0, from the sampler sub_7101108F0C).
u32 sub_71011095B8(f32* out_height, const sead::Vector2f* xz, System* system, s32 level, s32 flag) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    const s32 height_flag = flag != 0 && (system->mScenes(0).collector->_2998 & 0x20) ? flag : 0;

    auto* areas = system->sub_710111F4F0();
    const f32 scale = Terrain::instance()->_3cc;
    s32 index = 0;
    sead::Vector2f pos = sead::Vector2f::zero;
    const u32 result = sub_7101108AE8(&pos, &index, *xz, areas->_20, *areas, level);
    if (result != 0) {
        Unk_7101108C44Arg arg;
        arg.table = areas->_20.table;
        arg.index = index;
        arg._c = false;
        *out_height = scale * sub_7101108F0C(pos.x, pos.y, &arg, height_flag) + 0.0f;
    }
    return result;
}

// inline-only in the original; name is a guess. Wraps a texel coordinate once into [0, size) and splits
// it into the texel index and the fraction; inlined for both axes into 0x710110979c and 0x710110b814.
inline f32 wrapTexelMaybe(u32* index, f32 coord, f32 size) {
    if (coord < 0.0f) {
        if (coord > -size)
            coord = size + coord;
        else
            coord = 0.0f;
    } else if (coord + 1.0f > size) {
        if (coord >= size + size)
            coord = size + -1.0f;
        else
            coord = coord - size;
    }
    const s32 i = sead::Mathf::floor(coord);
    *index = i;
    return coord - static_cast<f32>(i);
}

// NON_MATCHING: instruction order and register allocation (float code).
f32 sub_710110979C(f32 u, f32 v, const TextureSamplerArgMaybe* arg, u32 level) {
    const TextureMipTableMaybe* table = arg->table;
    const auto& mip = table->levels[level];
    const f32 width = mip.width;
    const f32 height = mip.height;
    const f32 x = (u - mip.half_texel_x) * width;
    const f32 y = (v - mip.half_texel_y) * height;

    u32 ix, iy;
    const f32 fx = wrapTexelMaybe(&ix, x, width);
    const f32 fy = wrapTexelMaybe(&iy, y, height);

    const u32 max = table->levels[0].height - 1;
    const u8* data = table->levels[0].address;
    const u32 row0 = sead::Mathu::min(iy, max) * table->levels[0].pitch;
    const u32 col0 = sead::Mathu::min(ix, max) * table->_154;
    const u32 col1 = sead::Mathu::min(ix + 1, max) * table->_154;
    const u32 row1 = sead::Mathu::min(iy + 1, max) * table->levels[0].pitch;

    const f32 p00 = data[row0 + col0];
    const f32 p01 = data[row0 + col1];
    const f32 p10 = data[row1 + col0];
    const f32 p11 = data[row1 + col1];
    const f32 top = p00 / 255.0f + fx * (p01 / 255.0f - p00 / 255.0f);
    const f32 bottom = p10 / 255.0f + fx * (p11 / 255.0f - p10 / 255.0f);
    return top + fy * (bottom - top);
}

// NON_MATCHING: instruction order and register allocation (float code).
u32 sub_710110B814(f32 u, f32 v, const TextureSamplerArgMaybe* arg, u32 level) {
    const TextureMipTableMaybe* table = arg->table;
    const auto& mip = table->levels[level];
    const f32 width = mip.width;
    const f32 height = mip.height;
    const f32 x = (u - mip.half_texel_x) * width;
    const f32 y = (v - mip.half_texel_y) * height;

    u32 ix, iy;
    const f32 fx = wrapTexelMaybe(&ix, x, width);
    const f32 fy = wrapTexelMaybe(&iy, y, height);

    const u32 max = mip.height - 1;
    const u32 row0 = sead::Mathu::min(iy, max) * mip.pitch;
    const u32 col0 = sead::Mathu::min(ix, max) * table->_154;
    const u32 col1 = sead::Mathu::min(ix + 1, max) * table->_154;
    const u32 row1 = sead::Mathu::min(iy + 1, max) * mip.pitch;
    const u8* p00 = &mip.address[row0 + col0];
    const u8* p01 = &mip.address[row0 + col1];
    const u8* p10 = &mip.address[row1 + col0];
    const u8* p11 = &mip.address[row1 + col1];

    const u8* row = fx >= 0.5f ? p01 : p00;
    const u8* row_next = fx >= 0.5f ? p11 : p10;
    const u8* nearest = fy >= 0.5f ? row_next : row;

    const f32 a00 = sead::Mathf::min((p00[2] + 0.5f) / 255.0f, 1.0f);
    const f32 a01 = sead::Mathf::min((p01[2] + 0.5f) / 255.0f, 1.0f);
    const f32 top = a00 + fx * (a01 - a00);
    const f32 a10 = sead::Mathf::min((p10[2] + 0.5f) / 255.0f, 1.0f);
    const f32 a11 = sead::Mathf::min((p11[2] + 0.5f) / 255.0f, 1.0f);
    const f32 value = top + fy * ((a10 + fx * (a11 - a10)) - top);
    const u32 blended = value >= 0.0f ? u32(s32(sead::Mathf::min(value, 1.0f) * 255.0f + 0.5f)) << 8 : 0;
    return u32(nearest[0]) << 24 | u32(nearest[1]) << 16 | nearest[3] | blended;
}

// NON_MATCHING: the area index is kept in a register across the sub_710110C3E8 call here; the original
// reloads it (instruction order and register allocation).
// Placeholder name: like sub_710110B814, over the area texel data of an Unk_710110AC74Table at mip `level`
// (the caller 0x710110bd78 passes an Unk_7101108C44Arg). With arg->_c the texel position comes from
// sub_710110C3E8; otherwise the coordinate is wrapped into [0, 1] around the level offset and scaled to the
// level size. Bytes 0 / 1 / 3 come from the nearest texel, byte 2 is bilinearly filtered.
u32 sub_710110BA6C(f32 u, f32 v, const Unk_7101108C44Arg* arg, u32 level) {
    TexelPosMaybe texel;
    if (arg->_c) {
        sub_710110C3E8(arg->table, &texel, arg->index, level);
    } else {
        const auto& info = arg->table->levels[level];
        f32 x = u - info.offset;
        f32 y = v - info.offset;
        if (x < 0.0f)
            x += 1.0f;
        else if (x > 1.0f)
            x += -1.0f;
        if (y < 0.0f)
            y += 1.0f;
        else if (y > 1.0f)
            y += -1.0f;

        const f32 size = info.size;
        x *= size;
        y *= size;
        texel.fx = wrapTexelMaybe(&texel.x, x, size);
        texel.fy = wrapTexelMaybe(&texel.y, y, size);
    }

    const auto& info = arg->table->levels[level];
    const u32 max = info.size - 1;
    const s32 area = arg->index;
    const u8* data = arg->table->areas[area].levels[level];
    const u32 row0 = sead::Mathu::min(texel.y, max) * info.pitch;
    const u32 col0 = sead::Mathu::min(texel.x, max) * arg->table->texel_size;
    const u32 col1 = sead::Mathu::min(texel.x + 1, max) * arg->table->texel_size;
    const u32 row1 = sead::Mathu::min(texel.y + 1, max) * info.pitch;
    const u8* p00 = &data[row0 + col0];
    const u8* p01 = &data[row0 + col1];
    const u8* p10 = &data[row1 + col0];
    const u8* p11 = &data[row1 + col1];

    const u8* row = texel.fx >= 0.5f ? p01 : p00;
    const u8* row_next = texel.fx >= 0.5f ? p11 : p10;
    const u8* nearest = texel.fy >= 0.5f ? row_next : row;

    const f32 a00 = sead::Mathf::min((p00[2] + 0.5f) / 255.0f, 1.0f);
    const f32 a01 = sead::Mathf::min((p01[2] + 0.5f) / 255.0f, 1.0f);
    const f32 top = a00 + texel.fx * (a01 - a00);
    const f32 a10 = sead::Mathf::min((p10[2] + 0.5f) / 255.0f, 1.0f);
    const f32 a11 = sead::Mathf::min((p11[2] + 0.5f) / 255.0f, 1.0f);
    const f32 value = top + texel.fy * ((a10 + texel.fx * (a11 - a10)) - top);
    const u32 blended = value >= 0.0f ? u32(s32(sead::Mathf::min(value, 1.0f) * 255.0f + 0.5f)) << 8 : 0;
    return u32(nearest[0]) << 24 | u32(nearest[1]) << 16 | nearest[3] | blended;
}

// NON_MATCHING: register allocation (level stays in w20 in ours, the original copies it to w8;
// the tail csel operands are swapped). The body follows the original instruction for instruction.
// Placeholder name: the maximum of the four 16-bit heights around `x` / `y` (0 - 1) in the area of
// `arg` at mip `level`; the max counterpart of sub_7101108C44 and the sampler of sub_71011095B8.
f32 sub_7101108F0C(f32 x, f32 y, const Unk_7101108C44Arg* arg, u32 level) {
    TexelPosMaybe texel;
    if (arg->_c) {
        sub_710110C3E8(arg->table, &texel, arg->index, level);
    } else {
        const f32 offset = arg->table->levels[0].offset;
        f32 tx = x - offset;
        f32 ty = y - offset;
        if (tx < 0.0f)
            tx += 1.0f;
        else if (tx > 1.0f)
            tx += -1.0f;
        if (ty < 0.0f)
            ty += 1.0f;
        else if (ty > 1.0f)
            ty += -1.0f;

        const f32 size = arg->table->levels[level].size;
        tx *= size;
        ty *= size;
        texel.fx = wrapTexelMaybe(&texel.x, tx, size);
        texel.fy = wrapTexelMaybe(&texel.y, ty, size);
    }

    const u32 max = arg->table->levels[level].size - 1;
    const u32 pitch = arg->table->levels[level].pitch;
    const u32 texel_size = arg->table->texel_size;
    const u8* data = arg->table->areas[arg->index].levels[level];
    const auto read = [](const u8* texel) { return u16(texel[0] | texel[1] << 8) / 65535.0f; };
    const u32 row0 = sead::Mathu::min(texel.y, max) * pitch;
    const u32 col0 = sead::Mathu::min(texel.x, max) * texel_size;
    const f32 h00 = read(data + (row0 + col0));
    const u32 col1 = sead::Mathu::min(texel.x + 1, max) * texel_size;
    const f32 h01 = read(data + (row0 + col1));
    const u32 row1 = sead::Mathu::min(texel.y + 1, max) * pitch;
    const f32 h10 = read(data + (row1 + col0));
    const f32 h11 = read(data + (row1 + col1));
    return sead::Mathf::max(sead::Mathf::max(h00, h01), sead::Mathf::max(h10, h11));
}


// NON_MATCHING: register allocation (the area index is kept across the call), as sub_710110BA6C.
// Placeholder name: bilinear height (0 - 1) over the area texel data of an Unk_710110AC74Table at
// mip `level` (the f32 counterpart of sub_710110BA6C). The texel coordinate comes from
// sub_710110C3E8 with arg->_c, otherwise it is wrapped around the level offset; the texels are
// addressed with level 0's size and pitch.
f32 sub_7101109968(f32 u, f32 v, const Unk_7101108C44Arg* arg, u32 level) {
    TexelPosMaybe texel;
    if (arg->_c) {
        sub_710110C3E8(arg->table, &texel, arg->index, level);
    } else {
        const auto& info = arg->table->levels[level];
        f32 x = u - info.offset;
        f32 y = v - info.offset;
        if (x < 0.0f)
            x += 1.0f;
        else if (x > 1.0f)
            x += -1.0f;
        if (y < 0.0f)
            y += 1.0f;
        else if (y > 1.0f)
            y += -1.0f;

        const f32 size = info.size;
        x *= size;
        y *= size;
        texel.fx = wrapTexelMaybe(&texel.x, x, size);
        texel.fy = wrapTexelMaybe(&texel.y, y, size);
    }

    const u32 max = arg->table->levels[0].size - 1;
    const u32 pitch = arg->table->levels[0].pitch;
    const u8* data = arg->table->areas[arg->index].levels[level];
    const u32 row0 = sead::Mathu::min(texel.y, max) * pitch;
    const u32 col0 = sead::Mathu::min(texel.x, max) * arg->table->texel_size;
    const u32 col1 = sead::Mathu::min(texel.x + 1, max) * arg->table->texel_size;
    const u32 row1 = sead::Mathu::min(texel.y + 1, max) * pitch;
    const f32 p00 = data[row0 + col0] / 255.0f;
    const f32 p01 = data[row0 + col1] / 255.0f;
    const f32 p10 = data[row1 + col0] / 255.0f;
    const f32 p11 = data[row1 + col1] / 255.0f;
    const f32 top = p00 + texel.fx * (p01 - p00);
    const f32 bottom = p10 + texel.fx * (p11 - p10);
    return top + texel.fy * (bottom - top);
}

// NON_MATCHING: stack slot layout and register allocation (as sub_710110BD78).
// NON_MATCHING: stack slot layout and register allocation (as sub_710110BD78).
// NON_MATCHING: stack slot layout and register allocation (as sub_710110BD78).
// Placeholder name: the height and the filtered channels at `xz` from the type-3 image with index 0
// of the neighbouring area (record 7); calls sub_7101109968 / sub_710110A130 (or
// sub_710110979C / sub_7101109EA8 on the mip table).
void sub_710110A740(f32* out_height, sead::Vector4f* out, const sead::Vector2f* xz, System* system,
                    bool flag) {
    if (!system->_8)
        return;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return;

    const ImageTypeMaybe& type = sUnk_7101EC54B8;
    const auto* collector = system->mScenes(0).collector;
    if (collector->_0[7]._20._0 & 4) {
        if ((~collector->_0[7]._20._0 & 3) != 0)
            return;
        sead::Vector2f pos = sead::Vector2f::zero;
        s32 index;
        const u32 result =
            sub_7101108AE8(&pos, &index, *xz, collector->_0[7]._20, collector->_0[7], 0xffffffff);
        if (result != 0) {
            Unk_7101108C44Arg arg;
            arg.table = collector->_0[7]._20.table;
            arg.index = index;
            arg._c = false;
            *out_height = sub_7101109968(pos.x, pos.y, &arg, 0);
            *out = sub_710110A130(pos.x, pos.y, &arg, 0);
        }
        return;
    }

    const u32 index =
        flag ? collector->_0[7].sub_71010FEDBC(*xz, collector->_0[7]._20._2, 0.0f) : 0xffffffff;
    Unk_7101106F44* area;
    sead::Vector2f center;
    f32 size;
    const u32 result =
        Unk_7101106F44::sub_7101108860(&area, &center, &size, *xz, system, type, index);
    if (result == 0)
        return;

    const Unk_710250dcd8* image = area->getImageMaybe(type);
    const f32 map_size = size;
    const f32 half = map_size * 0.5f;
    const f32 u = xz->x - (center.x - half);
    const f32 v = xz->y - (center.y - half);
    TextureMipTableMaybe table;
    table.clearMaybe();
    sub_710110DE64(&table, image->getTextureDataMaybe());
    TextureSamplerArgMaybe arg;
    arg.table = &table;
    arg._8 = 0;
    arg._c = true;
    const f32 inv = 1.0f / map_size;
    *out_height = sub_710110979C(u * inv, v * inv, &arg, 0);
    *out = sub_7101109EA8(u * inv, v * inv, &arg, 0);

    area->releaseImageMaybe(type);
}

// NON_MATCHING: register allocation and instruction order (as sub_710110A130).
// Placeholder name: the filtered bytes 1 - 3 of the 8-bit texture of `arg` at mip `level`, as
// (x, y, z, 1) (the four-channel counterpart of sub_710110979C).
sead::Vector4f sub_7101109EA8(f32 u, f32 v, const TextureSamplerArgMaybe* arg, u32 level) {
    const TextureMipTableMaybe* table = arg->table;
    const auto& mip = table->levels[level];
    const f32 width = mip.width;
    const f32 height = mip.height;
    const f32 x = (u - mip.half_texel_x) * width;
    const f32 y = (v - mip.half_texel_y) * height;

    u32 ix, iy;
    const f32 fx = wrapTexelMaybe(&ix, x, width);
    const f32 fy = wrapTexelMaybe(&iy, y, height);

    const u32 max = table->levels[0].height - 1;
    const u8* data = table->levels[0].address;
    const u32 row0 = sead::Mathu::min(iy, max) * table->levels[0].pitch;
    const u32 col0 = sead::Mathu::min(ix, max) * table->_154;
    const u32 col1 = sead::Mathu::min(ix + 1, max) * table->_154;
    const u32 row1 = sead::Mathu::min(iy + 1, max) * table->levels[0].pitch;
    const u8* p00 = &data[row0 + col0];
    const u8* p01 = &data[row0 + col1];
    const u8* p10 = &data[row1 + col0];
    const u8* p11 = &data[row1 + col1];

    const f32 a0 = p00[1] / 255.0f;
    const f32 a1 = p01[1] / 255.0f;
    const f32 a2 = p10[1] / 255.0f;
    const f32 a3 = p11[1] / 255.0f;
    const f32 a_top = a0 + fx * (a1 - a0);
    const f32 a_bottom = a2 + fx * (a3 - a2);
    const f32 x_out = a_top + fy * (a_bottom - a_top);

    const f32 b0 = p00[2] / 255.0f;
    const f32 b1 = p01[2] / 255.0f;
    const f32 b2 = p10[2] / 255.0f;
    const f32 b3 = p11[2] / 255.0f;
    const f32 b_top = b0 + fx * (b1 - b0);
    const f32 b_bottom = b2 + fx * (b3 - b2);
    const f32 y_out = b_top + fy * (b_bottom - b_top);

    const f32 c0 = p00[3] / 255.0f;
    const f32 c1 = p01[3] / 255.0f;
    const f32 c2 = p10[3] / 255.0f;
    const f32 c3 = p11[3] / 255.0f;
    const f32 c_top = c0 + fx * (c1 - c0);
    const f32 c_bottom = c2 + fx * (c3 - c2);
    const f32 z_out = c_top + fy * (c_bottom - c_top);

    return {x_out, y_out, z_out, 1.0f};
}

// Placeholder name: the filtered channels at `xz` from the type-3 image with index 0 of the
// neighbouring area (record 7); the Unk_710110AC74Table / TextureMipTableMaybe counterparts of
// sub_710110A130 and sub_7101109EA8.
void sub_710110A468(sead::Vector4f* out, const sead::Vector2f* xz, System* system, bool flag) {
    if (!system->_8)
        return;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return;

    const ImageTypeMaybe& type = sUnk_7101EC54B8;
    const auto* collector = system->mScenes(0).collector;
    if (collector->_0[7]._20._0 & 4) {
        if ((~collector->_0[7]._20._0 & 3) != 0)
            return;
        sead::Vector2f pos = sead::Vector2f::zero;
        s32 index;
        const u32 result =
            sub_7101108AE8(&pos, &index, *xz, collector->_0[7]._20, collector->_0[7], 0xffffffff);
        if (result != 0) {
            Unk_7101108C44Arg arg;
            arg.table = collector->_0[7]._20.table;
            arg.index = index;
            arg._c = false;
            *out = sub_710110A130(pos.x, pos.y, &arg, 0);
        }
        return;
    }

    const u32 index =
        flag ? collector->_0[7].sub_71010FEDBC(*xz, collector->_0[7]._20._2, 0.0f) : 0xffffffff;
    Unk_7101106F44* area;
    sead::Vector2f center;
    f32 size;
    const u32 result =
        Unk_7101106F44::sub_7101108860(&area, &center, &size, *xz, system, type, index);
    if (result == 0)
        return;

    const Unk_710250dcd8* image = area->getImageMaybe(type);
    const f32 map_size = size;
    const f32 half = map_size * 0.5f;
    const f32 u = xz->x - (center.x - half);
    const f32 v = xz->y - (center.y - half);
    TextureMipTableMaybe table;
    table.clearMaybe();
    sub_710110DE64(&table, image->getTextureDataMaybe());
    TextureSamplerArgMaybe arg;
    arg.table = &table;
    arg._8 = 0;
    arg._c = true;
    const f32 inv = 1.0f / map_size;
    *out = sub_7101109EA8(u * inv, v * inv, &arg, 0);

    area->releaseImageMaybe(type);
}

// NON_MATCHING: register allocation (as sub_7101109968).
// Placeholder name: the three filtered channels (bytes 1 - 3) of the area texel data of `arg` at
// mip `level`, as (x, y, z, 1). Same texel position and addressing as sub_7101109968.
sead::Vector4f sub_710110A130(f32 u, f32 v, const Unk_7101108C44Arg* arg, u32 level) {
    TexelPosMaybe texel;
    if (arg->_c) {
        sub_710110C3E8(arg->table, &texel, arg->index, level);
    } else {
        const auto& info = arg->table->levels[level];
        f32 x = u - info.offset;
        f32 y = v - info.offset;
        if (x < 0.0f)
            x += 1.0f;
        else if (x > 1.0f)
            x += -1.0f;
        if (y < 0.0f)
            y += 1.0f;
        else if (y > 1.0f)
            y += -1.0f;

        const f32 size = info.size;
        x *= size;
        y *= size;
        texel.fx = wrapTexelMaybe(&texel.x, x, size);
        texel.fy = wrapTexelMaybe(&texel.y, y, size);
    }

    const u32 max = arg->table->levels[0].size - 1;
    const u32 pitch = arg->table->levels[0].pitch;
    const u8* data = arg->table->areas[arg->index].levels[level];
    const u32 row0 = sead::Mathu::min(texel.y, max) * pitch;
    const u32 col0 = sead::Mathu::min(texel.x, max) * arg->table->texel_size;
    const u32 col1 = sead::Mathu::min(texel.x + 1, max) * arg->table->texel_size;
    const u32 row1 = sead::Mathu::min(texel.y + 1, max) * pitch;
    const u8* p00 = &data[row0 + col0];
    const u8* p01 = &data[row0 + col1];
    const u8* p10 = &data[row1 + col0];
    const u8* p11 = &data[row1 + col1];

    const f32 a0 = p00[1] / 255.0f;
    const f32 a1 = p01[1] / 255.0f;
    const f32 a2 = p10[1] / 255.0f;
    const f32 a3 = p11[1] / 255.0f;
    const f32 a_top = a0 + texel.fx * (a1 - a0);
    const f32 a_bottom = a2 + texel.fx * (a3 - a2);
    const f32 x = a_top + texel.fy * (a_bottom - a_top);

    const f32 b0 = p00[2] / 255.0f;
    const f32 b1 = p01[2] / 255.0f;
    const f32 b2 = p10[2] / 255.0f;
    const f32 b3 = p11[2] / 255.0f;
    const f32 b_top = b0 + texel.fx * (b1 - b0);
    const f32 b_bottom = b2 + texel.fx * (b3 - b2);
    const f32 y = b_top + texel.fy * (b_bottom - b_top);

    const f32 c0 = p00[3] / 255.0f;
    const f32 c1 = p01[3] / 255.0f;
    const f32 c2 = p10[3] / 255.0f;
    const f32 c3 = p11[3] / 255.0f;
    const f32 c_top = c0 + texel.fx * (c1 - c0);
    const f32 c_bottom = c2 + texel.fx * (c3 - c2);
    const f32 z = c_top + texel.fy * (c_bottom - c_top);

    return {x, y, z, 1.0f};
}

// Placeholder name: the height (0 - 1) at `xz` from the type-3 image with index 0 of the
// neighbouring area (the f32 counterpart of sub_710110BD78).
u32 sub_7101109BD8(f32* out, const sead::Vector2f* xz, System* system, bool flag) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;

    const ImageTypeMaybe& type = sUnk_7101EC54B8;
    const auto* collector = system->mScenes(0).collector;
    if (collector->_0[7]._20._0 & 4) {
        if ((~collector->_0[7]._20._0 & 3) != 0)
            return 0;
        sead::Vector2f pos = sead::Vector2f::zero;
        s32 index;
        const u32 result =
            sub_7101108AE8(&pos, &index, *xz, collector->_0[7]._20, collector->_0[7], 0xffffffff);
        if (result != 0) {
            Unk_7101108C44Arg arg;
            arg.table = collector->_0[7]._20.table;
            arg.index = index;
            arg._c = false;
            *out = sub_7101109968(pos.x, pos.y, &arg, 0);
        }
        return result;
    }

    const u32 index =
        flag ? collector->_0[7].sub_71010FEDBC(*xz, collector->_0[7]._20._2, 0.0f) : 0xffffffff;
    Unk_7101106F44* area;
    sead::Vector2f center;
    f32 size;
    const u32 result =
        Unk_7101106F44::sub_7101108860(&area, &center, &size, *xz, system, type, index);
    if (result == 0)
        return result;

    const Unk_710250dcd8* image = area->getImageMaybe(type);
    const f32 map_size = size;
    const f32 half = map_size * 0.5f;
    const f32 u = xz->x - (center.x - half);
    const f32 v = xz->y - (center.y - half);
    TextureMipTableMaybe table;
    table.clearMaybe();
    sub_710110DE64(&table, image->getTextureDataMaybe());
    TextureSamplerArgMaybe arg;
    arg.table = &table;
    arg._8 = 0;
    arg._c = true;
    const f32 inv = 1.0f / map_size;
    *out = sub_710110979C(u * inv, v * inv, &arg, 0);

    area->releaseImageMaybe(type);
    return result;
}

// NON_MATCHING: the [0, 1] wrap is compiled to selects here (branches with a shared add in the original).
void sub_710110AC74(f32 x, f32 y, const Unk_7101108C44Arg* arg, TexelPosMaybe* out, u32 level) {
    const Unk_710110AC74Table* table = arg->table;
    if (arg->_c) {
        sub_710110C3E8(table, out, arg->index, level);
        return;
    }
    const auto& info = table->levels[level];
    x -= info.offset;
    y -= info.offset;
    if (x < 0.0f)
        x += 1.0f;
    else if (x > 1.0f)
        x += -1.0f;
    if (y < 0.0f)
        y += 1.0f;
    else if (y > 1.0f)
        y += -1.0f;

    const f32 size = info.size;
    x *= size;
    y *= size;
    out->fx = wrapTexelMaybe(&out->x, x, size);
    out->fy = wrapTexelMaybe(&out->y, y, size);
}


// NON_MATCHING: scheduling and register allocation (as in sub_710110B38C).
u32 sub_710110AA5C(f32 a, f32 b, f32* out_height, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info) {
    s32 area = 0;
    sead::Vector2f pos = sead::Vector2f::zero;
    u32 result = sub_7101108AE8(&pos, &area, *xz, *info_20, *info, -1);
    if (result != 0) {
        Unk_7101108C44Arg arg;
        arg.table = info_20->table;
        arg.index = area;
        arg._c = false;
        TexelPosMaybe texel;
        sub_710110AC74(pos.x, pos.y, &arg, &texel, 0);
        const Unk_710110AC74Table* table = arg.table;
        const u32 max = table->levels[0].size - 1;
        const u32 nx = texel.fx < 0.5f ? texel.x : texel.x + 1;
        const u32 ny = texel.fy < 0.5f ? texel.y : texel.y + 1;
        const u32 pitch = table->levels[0].pitch;
        const u32 texel_size = table->texel_size;
        const u8* data = table->areas[arg.index].levels[0];
        f32 height;
        if (s8(data[sead::Mathu::min(nx, max) * texel_size + sead::Mathu::min(ny, max) * pitch + 6]) <
            0) {
            result = -1;
            height = 0.0f;
        } else {
            const u32 row0 = sead::Mathu::min(texel.y, max) * pitch;
            const u32 col0 = sead::Mathu::min(texel.x, max) * texel_size;
            const u32 col1 = sead::Mathu::min(texel.x + 1, max) * texel_size;
            const u32 row1 = sead::Mathu::min(texel.y + 1, max) * pitch;
            const f32 h00 =
                *static_cast<const u16*>(sead::PtrUtil::addOffset(data, row0 + col0)) / 65535.0f;
            const f32 h10 =
                *static_cast<const u16*>(sead::PtrUtil::addOffset(data, row1 + col0)) / 65535.0f;
            const f32 h01 =
                *static_cast<const u16*>(sead::PtrUtil::addOffset(data, row0 + col1)) / 65535.0f;
            const f32 h11 =
                *static_cast<const u16*>(sead::PtrUtil::addOffset(data, row1 + col1)) / 65535.0f;
            const f32 top = h00 + texel.fx * (h01 - h00);
            height = (b - a) * (top + texel.fy * ((h10 + texel.fx * (h11 - h10)) - top)) + a;
        }
        *out_height = height;
    }
    return result;
}


// inline-only in the original; name is a guess: a 16-bit channel of a texel as 0 - 1 (the same load and
// scale repeat in 0x7101108c44, 0x710110aa5c and 0x710110b0e8).
inline f32 texelChannelMaybe(const u8* texel, u32 offset) {
    return *static_cast<const u16*>(sead::PtrUtil::addOffset(texel, offset)) / 65535.0f;
}

// NON_MATCHING: scheduling and register allocation (as in sub_710110B38C).
u32 sub_710110ADF8(f32 a, f32 b, f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info) {
    s32 area = 0;
    sead::Vector2f pos = sead::Vector2f::zero;
    u32 result = sub_7101108AE8(&pos, &area, *xz, *info_20, *info, -1);
    if (result != 0) {
        Unk_7101108C44Arg arg;
        arg.table = info_20->table;
        arg.index = area;
        arg._c = false;
        TexelPosMaybe texel;
        sub_710110AC74(pos.x, pos.y, &arg, &texel, 0);
        const Unk_710110AC74Table* table = arg.table;
        const u32 max = table->levels[0].size - 1;
        const u32 nx = texel.fx < 0.5f ? texel.x : texel.x + 1;
        const u32 ny = texel.fy < 0.5f ? texel.y : texel.y + 1;
        const u32 pitch = table->levels[0].pitch;
        const u32 texel_size = table->texel_size;
        const u8* data = table->areas[arg.index].levels[0];
        if (s8(data[sead::Mathu::min(nx, max) * texel_size + sead::Mathu::min(ny, max) * pitch + 6]) <
            0) {
            *out_height = 0.0f;
            out_normal->set(0.0f, 1.0f, 0.0f);
            result = -1;
        } else {
            const u32 row0 = sead::Mathu::min(texel.y, max) * pitch;
            const u32 col0 = sead::Mathu::min(texel.x, max) * texel_size;
            const u32 col1 = sead::Mathu::min(texel.x + 1, max) * texel_size;
            const u32 row1 = sead::Mathu::min(texel.y + 1, max) * pitch;
            const f32 h00 = texelChannelMaybe(data, row0 + col0);
            const f32 h01 = texelChannelMaybe(data, row0 + col1);
            const f32 h10 = texelChannelMaybe(data, row1 + col0);
            const f32 h11 = texelChannelMaybe(data, row1 + col1);
            const f32 dx0 = h01 - h00;
            const f32 dx1 = h11 - h10;
            const f32 top = h00 + texel.fx * dx0;
            const f32 dz0 = h10 - h00;
            const f32 dz1 = h11 - h01;
            out_normal->set(-(dx0 + (dx1 - dx0) * 0.0f), 1.0f, -(dz0 + (dz1 - dz0) * 0.0f));
            const f32 scale = static_cast<f32>(info_20->_e) / info->mAreas[area].size;
            out_normal->x = scale * out_normal->x;
            out_normal->y = 1.0f / (b - a);
            out_normal->z = scale * out_normal->z;
            out_normal->normalize();
            *out_height = (b - a) * (top + texel.fy * ((h10 + texel.fx * dx1) - top)) + a;
        }
    }
    return result;
}

// NON_MATCHING: scheduling and register allocation (as in sub_710110B38C).
u32 sub_710110B0E8(f32 scale, sead::Vector2f* out, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info) {
    s32 area = 0;
    sead::Vector2f pos = sead::Vector2f::zero;
    const u32 result = sub_7101108AE8(&pos, &area, *xz, *info_20, *info, -1);
    if (result != 0) {
        Unk_7101108C44Arg arg;
        arg.table = info_20->table;
        arg.index = area;
        arg._c = false;
        TexelPosMaybe texel;
        sub_710110AC74(pos.x, pos.y, &arg, &texel, 0);
        const Unk_710110AC74Table* table = arg.table;
        const u32 max = table->levels[0].size - 1;
        const u32 row0 = sead::Mathu::min(texel.y, max) * table->levels[0].pitch;
        const u32 col0 = sead::Mathu::min(texel.x, max) * table->texel_size;
        const u32 col1 = sead::Mathu::min(texel.x + 1, max) * table->texel_size;
        const u8* data = table->areas[arg.index].levels[0];
        const u8* p00 = data + (row0 + col0);
        const u8* p01 = data + (row0 + col1);
        const u32 row1 = sead::Mathu::min(texel.y + 1, max) * table->levels[0].pitch;
        const u8* p10 = data + (row1 + col0);
        const u8* p11 = data + (row1 + col1);

        f32 x0 = texelChannelMaybe(p00, 2);
        f32 x1 = texelChannelMaybe(p10, 2);
        x0 = x0 + (texelChannelMaybe(p01, 2) - x0) * texel.fx;
        f32 y0 = texelChannelMaybe(p00, 4);
        y0 = y0 + (texelChannelMaybe(p01, 4) - y0) * texel.fx;
        const f32 vx = x0 + texel.fy * ((x1 + (texelChannelMaybe(p11, 2) - x1) * texel.fx) - x0);
        const f32 y1 = texelChannelMaybe(p10, 4);
        const f32 vy = y0 + texel.fy * ((y1 + texel.fx * (texelChannelMaybe(p11, 4) - y1)) - y0);

        out->x = vx + vx + -1.0f;
        out->y = vy + vy + -1.0f;
        if (sead::Mathf::abs(out->x) < 1.0f / 65535.0f)
            out->x = 0.0f;
        if (sead::Mathf::abs(out->y) < 1.0f / 65535.0f)
            out->y = 0.0f;
        out->x *= scale;
        out->y *= scale;
    }
    return result;
}

// NON_MATCHING: stack layout and the table is kept in a register (the original reloads it from `arg`).
u32 sub_710110B38C(u32* out, const sead::Vector2f* xz, const Unk_7101108AE8Flags* info_20,
                   const Unk_71010FEDBC* info) {
    s32 area = 0;
    sead::Vector2f pos = sead::Vector2f::zero;
    const u32 result = sub_7101108AE8(&pos, &area, *xz, *info_20, *info, -1);
    if (result != 0) {
        Unk_7101108C44Arg arg;
        arg.table = info_20->table;
        arg.index = area;
        arg._c = false;
        TexelPosMaybe texel;
        sub_710110AC74(pos.x, pos.y, &arg, &texel, 0);
        const u32 x = texel.fx < 0.5f ? texel.x : texel.x + 1;
        const u32 y = texel.fy < 0.5f ? texel.y : texel.y + 1;
        const Unk_710110AC74Table* table = arg.table;
        const u32 max = table->levels[0].size - 1;
        const u8* data = table->areas[arg.index].levels[0] +
                         (sead::Mathu::min(y, max) * table->levels[0].pitch +
                          sead::Mathu::min(x, max) * table->texel_size);
        *out = data[7] << 8 | data[6];
    }
    return result;
}

u32 sub_710110B52C(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    auto* info = system->sub_710111F504();
    return sub_710110ADF8(0.0f, Terrain::instance()->_3cc, out_height, out_normal, xz, &info->_20,
                          info);
}

u32 sub_710110B5BC(sead::Vector2f* out, const sead::Vector2f* xz, System* system) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    auto* info = system->sub_710111F504();
    return sub_710110B0E8(50.0f, out, xz, &info->_20, info);
}

u32 sub_710110B634(u32* out, const sead::Vector2f* xz, System* system) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    auto* info = system->sub_710111F504();
    return sub_710110B38C(out, xz, &info->_20, info);
}

// NON_MATCHING: register allocation.
Unk_7101106F44* System::sub_7101115218(sead::Vector2f* out_center, f32* out_size,
                                       const sead::Vector2f& pos, u32 levels) {
    Unk_7101106F44* node = _8;
    if (!node)
        return nullptr;

    sead::Vector2f center = _1c;
    f32 size = _24;
    while (true) {
        const f32 half = size * 0.5f;
        if (center.x - half <= pos.x && pos.x < half + center.x && center.y - half <= pos.y &&
            pos.y < half + center.y) {
            break;
        }
        center.x += node->_1 == 1 || node->_1 == 3 ? -half : half;
        center.y += node->_1 == 2 || node->_1 == 3 ? -half : half;
        size += size;
        node = node->mParent;
        ++levels;
        if (!node)
            return nullptr;
    }

    for (u32 i = 0; i < levels; ++i) {
        const s32 index = (pos.x >= center.x) | (pos.y >= center.y) << 1;
        Unk_7101106F44* child = node->mChildren[index];
        if (!child)
            break;
        size *= 0.5f;
        center.y += size * sUnk_7101EC503C[index].y;
        center.x += size * sUnk_7101EC503C[index].x;
        node = child;
    }

    *out_center = center;
    *out_size = size;
    return node;
}

// NON_MATCHING: bit 7 of the debug byte is tested through a sign-extending load in ours.
void System::sub_7101115584(s32 index, Unk_7101115584Arg* arg) {
    if (!_8)
        return;
    mLock.readLock();
    SceneSlot& slot = mScenes[index];
    slot._88 = true;
    slot.collector->sub_7101100F08(this, arg,
                               (_1338 & 2) || (Terrain::instance()->_a50->_1d >> 4 & 1));
    if (arg->_198) {
        auto* debug = Terrain::instance()->_a50;
        if (!debug || !(debug->_18 >> 7 & 1))
            sub_7101115338(arg->_0, _8, _1c, _24);
    }
    sub_7101115674(arg);
    mLock.readUnlock();
}

// NON_MATCHING: the original copies `pos` as two words and stores it once before the call; ours
// stores it early and again after the loop.
void System::sub_7101115338(const agl::cull::ViewFrustumCulling* culling, Unk_7101106F44* area,
                            const sead::Vector2f& center, f32 size) {
    {
        sead::Vector2f pos = center;
        sead::BoundBox3f box;
        if (area->mParent) {
            f32 scale = size / (1 << area->mDepth);
            f32 x = pos.x;
            f32 y = pos.y;
            for (Unk_7101106F44* node = area; node->mParent; node = node->mParent) {
                y += scale * sUnk_7101EC503C[node->_1].y;
                x += scale * sUnk_7101EC503C[node->_1].x;
                scale += scale;
            }
            pos = {x, y};
        }
        area->sub_7101107E98(&box, pos, size / (1 << area->mDepth));
        if (!culling->isInside(box.getMin(), box.getMax()))
            return;
    }

    _1008[area->mIndex] |= 1;
    size *= 0.5f;
    for (s32 i = 0; i < 4; ++i) {
        if (Unk_7101106F44* child = area->mChildren[i]) {
            const sead::Vector2f child_center(size * sUnk_7101EC503C[i].x + center.x,
                                              size * sUnk_7101EC503C[i].y + center.y);
            sub_7101115338(culling, child, child_center, size);
        }
    }
}

// NON_MATCHING: regalloc and operand order in the inlined sub_7101115218 (which is m itself).
void System::sub_7101115674(Unk_7101115584Arg* arg) {
    sead::Vector2f center;
    f32 size;
    for (Unk_7101106F44* node = sub_7101115218(&center, &size, {arg->_14.x, arg->_14.z}, 0xffff); node;
         node = node->mParent) {
        _1008[node->mIndex] |= 2;
    }
}

// NON_MATCHING: the original loads the offset pair with one ldp before multiplying.
void Unk_7101106F44::sub_7101120374(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                                    const ImageTypeMaybe& type) {
    Unk_7101106F44* area = *node;
    while (area) {
        if (area->hasImageMaybe(type)) {
            const Unk_710250dcd8* image = area->getImageMaybe(type);
            if (image && image->_8 & 4)
                break;
        }
        Unk_7101106F44* parent = area->mParent;
        const s32 slot = parent ? area->_1 : 0;
        *center -= sUnk_7101EC503C[slot] * *size;
        *size += *size;
        area = parent;
    }
    *node = area;
}

// NON_MATCHING: the original loads the offset pair with one ldp before multiplying.
void Unk_7101106F44::sub_7101120598(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                                    const ImageTypeMaybe& type) {
    Unk_7101106F44* area = *node;
    while (area && !area->hasImageMaybe(type)) {
        Unk_7101106F44* parent = area->mParent;
        const s32 slot = parent ? area->_1 : 0;
        *center -= sUnk_7101EC503C[slot] * *size;
        *size += *size;
        area = parent;
    }
    *node = area;
}

void Unk_7101106F44::sub_7101120594(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                                    const ImageTypeMaybe& type) {
    sub_7101120374(node, center, size, type);
}

void Unk_7101106F44::sub_71011206E4(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                                    const ImageTypeMaybe& type) {
    sub_7101120598(node, center, size, type);
}

// 0x71010816d0 (unnamed): sets the buffer index of every tree type and of both draw commands.
// 0x71012e899c (unnamed): the model-unit record destructor is empty in this release. Kept out of
// teraCore.cpp so that Buffer::freeBuffer calls it out of line, as the original does.
Core::ModelUnitRecord::~ModelUnitRecord() {}

void Core::Unk_140::sub_71010816D0(u32 value) {
    Terrain* terrain = Terrain::instance();
    if (terrain) {
        if (terrain->_a50) {
            if (terrain->_a50->_18 & 0x20)
                return;
        }
    }
    if (!(_8 & 1))
        return;

    const u32 count = mTreeTypes.size();
    TreeTypeMaybe* type = mTreeTypes.getBufferPtr();
    for (u32 i = 0; i != count; ++i)
        type[i].mBlock.setBufferIndexMaybe(u8(value));

    _14cd[0]->sub_7101085198(value);
    _14cd[1]->sub_7101085198(value);
}

void Core::Unk_140::sub_71010827DC() {
    if (_8 & 4)
        _8 &= ~4u;
    _14cd[0]->sub_7101084D04();
    _14cd[1]->sub_7101084D04();
}

namespace {

// The tree-placement record 0x7101082878 builds on its stack: position and rotation, the scale and
// the command index. It writes the index as an integer where the scale's z would be (the command
// still receives the three floats), so the two share their storage.
struct TreePlacementMaybe {
    sead::Vector3f mPosition;
    sead::Vector3f mRotate;
    struct Parts {
        f32 mScaleX;
        f32 mScaleY;
        s32 mIndex;
    };
    union {
        sead::Vector3f mScale;
        Parts mParts;
    };
    u32 _24;
    u32 _28;
    f32 _2c;
};
static_assert(sizeof(TreePlacementMaybe) == 0x30);

// The stack placer objects the two entry points hand to the shared dispatcher; each has one virtual
// (vtable 0x7102504400 / 0x7102504418). Both classes are local to Core's TU in the original, which
// reaches the vtables with a plain adrp + add.
class TreePlacer {
public:
    virtual s32 m0(const TreePlacementMaybe& record) = 0;
};

// 0x7101084008: counts the record in the tree type selected by its index.
class Unk_7102504400 : public TreePlacer {
public:
    explicit Unk_7102504400(sead::SafeArray<Unk_71025046d0*, 2>* cmds) : mCmds(cmds) {}
    s32 m0(const TreePlacementMaybe& record) override;
    sead::SafeArray<Unk_71025046d0*, 2>* mCmds;
};

// 0x7101084034: counts the record in the tile its position falls in, then adds it to the command
// selected by its index.
class Unk_7102504418 : public TreePlacer {
public:
    Unk_7102504418(Core::Unk_140::TableEntry (*tables)[8],
                   sead::SafeArray<Unk_71025046d0*, 2>* cmds)
        : mTables(tables), mCmds(cmds) {}
    s32 m0(const TreePlacementMaybe& record) override;
    Core::Unk_140::TableEntry (*mTables)[8];
    sead::SafeArray<Unk_71025046d0*, 2>* mCmds;
};

// 0x7101082878 (declared only): builds the placement record and runs `placer.m0` on it.
s32 sub_7101082878(TreePlacer& placer, const sead::SafeString& name, const sead::Vector3f& pos,
                   const sead::Vector3f& a, const sead::Vector3f& b);

s32 Unk_7102504400::m0(const TreePlacementMaybe& record) {
    (*mCmds)[record.mParts.mIndex]->sub_7101084D9C(record.mPosition);
    return 0;
}

// NON_MATCHING: the tile clamp keeps `cmp (floor + K), #0` in the original; our clang folds it to
// `cmn floor, #K` and hoists the 9 / 7 constants (the same difference as 0x710107f9c4 / fa0c).
s32 Unk_7102504418::m0(const TreePlacementMaybe& record) {
    const s32 table = sead::Mathi::clamp(sead::Mathf::floor(record.mPosition.x / 1000.0f) + 5, 0, 9);
    const s32 entry = sead::Mathi::clamp(sead::Mathf::floor(record.mPosition.z / 1000.0f) + 4, 0, 7);
    mTables[table][entry].sub_7101083D50(record.mParts.mIndex, &record.mPosition);
    return (*mCmds)[record.mParts.mIndex]->sub_7101084FB8(
        record.mPosition, record.mScale, record.mRotate, record._24, record._28, record._2c);
}

}  // namespace

// 0x7101082824 (unnamed): counts a tree placed at `pos` in the command-array placer.
void Core::Unk_140::sub_7101082824(const sead::SafeString& name, const sead::Vector3f& pos) {
    if (_8 & 4)
        return;
    Unk_7102504400 placer(&_14cd);
    sub_7101082878(placer, name, pos, sead::Vector3f::zero, sead::Vector3f::ones);
}

// 0x71010832b0 (unnamed): counts a tree placed with `rotate` / `scale`; -1 unless (_8 & 6) == 2.
s32 Core::Unk_140::sub_71010832B0(const sead::SafeString& name, const sead::Vector3f& pos,
                                  const sead::Vector3f& rotate, const sead::Vector3f& scale,
                                  f32 unk) {
    if ((_8 & 6) != 2)
        return -1;
    Unk_7102504418 placer(mTables, &_14cd);
    return sub_7101082878(placer, name, pos, rotate, scale);
}

// NON_MATCHING: the original peels five boxes out of the 21-box reset loop, our clang unrolls the loop
// differently (same stores, different split).
// 0x71010831f0 (unnamed): stores the table / entry indices and resets the 21 boxes.
void Core::Unk_140::TableEntry::sub_71010831F0(u8 table, u8 index) {
    if (_19c & 1)
        _19c &= 0xfe;
    _190->mTable = table;
    _190->mIndex = index;
    State* state = _190;
    state->_4 = 0;
    state->_8 = 0;
    for (s32 i = 0; i < 21; ++i) {
        _190->mBoxes[i].set(sead::Vector3f(3.4028235e38f, 3.4028235e38f, 3.4028235e38f),
                            sead::Vector3f(-3.4028235e38f, -3.4028235e38f, -3.4028235e38f));
    }
    _190->mCounts[0] = 0;
    state->mCounts[1] = 0;
}

void Core::Unk_140::sub_7101083028() {
    _14cd[0]->sub_7101084E78();
    _14cd[1]->sub_7101084E78();
}

// 0x7101080a08: empty in this release (a four-byte body); Core's teardown calls it before deleting
// the tree object.
void Core::Unk_140::sub_7101080A08() {}

// 0x71010819d4: empty in this release (a four-byte body); Core::sub_710130241C calls it for the
// tree draw.
void Core::Unk_140::sub_71010819D4(agl::DrawContext* context, s32 index, const DrawArgMaybe* arg) {}

// 0x7101080a0c (placeholder name): clears the low flag bits and advances the 0..15 counter unless the
// terrain debug flag or _8 bit 0 stops it.
void Core::Unk_140::sub_7101080A0C() {
    Terrain* terrain = Terrain::instance();
    if (terrain && terrain->_a50 && (terrain->_a50->_18 & 0x20))
        return;
    if (!(_8 & 1))
        return;
    if ((_c & 3) == 3)
        _c &= ~u32(3);
    if (++_14ccc > 15)
        _14ccc = 0;
}

// NON_MATCHING: the guard's branch layout differs (our epilogue is placed before the main body and the
// debug-bit test is inverted); the instruction multiset is identical.
// 0x7101083c98 (unnamed): runs slot 37 on both draw commands unless the debug flag or _8 bit 0 stops it.
void Core::Unk_140::sub_7101083C98(u32 index, void* p, f32 value) {
    Terrain* terrain = Terrain::instance();
    if (terrain) {
        if (terrain->_a50) {
            if (terrain->_a50->_18 & 0x20)
                return;
        }
    }
    if (!(_8 & 1))
        return;
    _14cd[0]->m37(index, p, value);
    _14cd[1]->m37(index, p, value);
}

// NON_MATCHING: the low tile bit is combined with an OR instead of a bit insert, the constant box
// offsets (1 / 5) are added to the index rather than kept in the load immediate, and the float
// temporaries use different registers.
// 0x7101083d50 (unnamed): counts a tree at `pos` and expands the overall box and the 500 / 250-unit
// tile boxes the position falls in.
void Core::Unk_140::TableEntry::sub_7101083D50(u32 index, const sead::Vector3f* pos) {
    _190->mCounts[index]++;
    _190->mBoxes[0].addPoint(*pos);

    const f32 x = pos->x;
    const f32 z = pos->z;
    const f32 local_x = x - f32(sead::Mathf::floor(x / 1000.0f)) * 1000.0f;
    const f32 local_z = z - f32(sead::Mathf::floor(z / 1000.0f)) * 1000.0f;

    const bool right = local_x >= 500.0f;
    const bool far = local_z >= 500.0f;
    const f32 offset_x = right ? 500.0f : 0.0f;
    const f32 offset_z = far ? 500.0f : 0.0f;
    const bool fine_x = local_x - offset_x >= 250.0f;
    const bool fine_z = local_z - offset_z >= 250.0f;

    const u32 tiles = u32(right) << 2 | u32(far) << 3;
    _190->mBoxes[1 + (tiles >> 2)].addPoint(*pos);
    _190->mBoxes[5 + (tiles | u32(fine_x) | u32(fine_z) << 1)].addPoint(*pos);
}

// 0x7101083c20 (unnamed): the first non-negative tree value of the two draw commands, or -1.
f32 Core::Unk_140::sub_7101083C20(u32 index, const sead::Vector3f& pos) {
    for (s32 i = 0; i <= 1; ++i) {
        const f32 value = _14cd[i]->m36(index, pos);
        if (value >= 0.0f)
            return value;
    }
    return -1.0f;
}

// 0x71010839fc (unnamed): whether either draw command reports slot 30.
bool Core::Unk_140::sub_71010839FC() {
    if (_14cd[0]->m30())
        return true;
    return _14cd[1]->m30();
}

// NON_MATCHING: the guard's branch layout differs (our epilogue is placed before the main body and the
// debug-bit test is inverted) and the flag word is read as a byte; the instruction multiset is the same.
// 0x7101083b78 (unnamed): runs slot 34 on the draw commands until one returns true.
void Core::Unk_140::sub_7101083B78(u32 index, const sead::Vector3f& pos, bool b) {
    Terrain* terrain = Terrain::instance();
    if (terrain) {
        if (terrain->_a50) {
            if (terrain->_a50->_18 & 0x20)
                return;
        }
    }
    if (index == 0xffff)
        return;
    if (!(_8 & 1))
        return;
    for (s32 i = 0; i <= 1; ++i) {
        if (_14cd[i]->m34(index, &pos, b))
            break;
    }
}

// 0x7101083aa8 (unnamed): runs slot 33 on both draw commands unless the debug flag or _8 bit 0 stops it.
void Core::Unk_140::sub_7101083AA8(s32 index, void* p, u32 a, u32 b) {
    Terrain* terrain = Terrain::instance();
    if (terrain) {
        if (terrain->_a50) {
            if (terrain->_a50->_18 & 0x20)
                return;
        }
    }
    if (index == 0xffff)
        return;
    if (!(_8 & 1))
        return;
    _14cd[0]->m33(index, p, a & 1, b & 1);
    _14cd[1]->m33(index, p, a & 1, b & 1);
}

// 0x7101083a58 (placeholder name): runs slot 31 of draw command `index`.
s32 Core::Unk_140::sub_7101083A58(s32 index) {
    return _14cd[index]->m31();
}

// 0x7101083a80 (placeholder name): runs slot 32 of draw command `index`.
s32 Core::Unk_140::sub_7101083A80(s32 index) {
    return _14cd[index]->m32();
}

// 0x71010839c4 (placeholder name): stores value (clamped to 0..1) scaled to 4000..8000 at +0x14cb8.
void Core::Unk_140::sub_71010839C4(f32 value) {
    const f32 clamped = sead::Mathf::clamp(value, 0.0f, 1.0f);
    _14cb8 = clamped * 4000.0f + 4000.0f;
}

// NON_MATCHING: the two induction variables (entry index and byte offset) are initialised in the
// opposite order from the original.
void Core::Unk_140::sub_7101083060() {
    if (!(_8 & 4)) {
        _8 |= 2;
        for (s32 index = 0; index < 8; ++index) {
            for (s32 table = 0; table < 10; ++table)
                mTables[table][index].init(table, index);
        }
        _14cd[0]->sub_7101084F6C();
        _14cd[1]->sub_7101084F6C();
    }
}

void Core::Unk_140::sub_710108330C() {
    if (!(_8 & 4)) {
        _8 &= ~2u;
        for (s32 index = 0; index < 8; ++index) {
            for (s32 table = 0; table < 10; ++table)
                mTables[table][index].setup(_28);
        }
        _14cd[0]->sub_710108515C(_28);
        _14cd[1]->sub_710108515C(_28);
        _8 |= 4;
    }
}

Unk_7101088B24::Unk_7101088B24() : mNumPending(0), _22_0(0), mAdded(false) {}

// Empty in this release (S7EventFlow's destructor calls it before freeing the object).
Unk_7101088B24::~Unk_7101088B24() {}

bool Unk_7101088B24::sub_7101088654(const InitArg& arg) {
    if (!mEntries.tryAllocBuffer(arg.count, arg.heap))
        return false;
    _22_0 |= 1;
    return true;
}

void Unk_7101088B24::sub_710108872C() {
    mEntries.freeBuffer();
    _22_0 &= ~1u;
}

void Unk_7101088B24::sub_7101088820(Unk_7101106F44* area, const ImageTypeMaybe& type, bool climb) {
    auto* entry = mEntries.emplaceBack();
    entry->area = area;
    entry->type = type;
    if (climb) {
        sead::Vector2f center{0.0f, 0.0f};
        f32 size = 0.0f;
        Unk_7101106F44::sub_7101120598(&entry->area, &center, &size, entry->type);
    }
}

void Unk_7101088B24::sub_71010887CC() {
    mEntries.clear();
    mNumPending = 0;
    _22_0 &= ~2u;
}

void Unk_7101088B24::sub_7101088B24(System* system, bool add) {
    if (add) {
        for (auto& entry : mEntries)
            system->sub_71011171D8(entry.area, entry.type);
    } else {
        for (auto& entry : mEntries)
            system->sub_710111731C(entry.area, entry.type);
    }
    mAdded = add;
}

// NON_MATCHING: the original's swap skips out-of-range positions (two unsigned compares against the
// size; our sead PtrArray::swap has no checks), which also changes the block layout.
bool Unk_7101088B24::sub_7101088BB4() {
    u32 count = mNumPending;
    if (count == 0)
        return true;

    for (u32 i = 0; i < count; ++i) {
        auto* entry = mEntries(i);
        const Unk_710250dcd8* image = entry->area->getImageMaybe(entry->type);
        if (image && (image->_8 & 4)) {
            --count;
            mEntries.swap(i, count);
            --i;
        }
    }
    mNumPending = count;
    return mNumPending == 0;
}

// NON_MATCHING: the original keeps the child loop counter as a 32-bit value (sign-extended for the
// index, compared with != 4); ours uses a 64-bit counter.
bool Unk_7101106F44::sub_710111FAFC(const ImageTypeMaybe& type, bool no_child) const {
    switch (type.type) {
    case 0:
    case 1:
        break;
    case 3:
        if (!hasImageMaybe(type))
            return false;
        break;
    case 2: {
        const Unk_7101108460* node = findNodeMaybe(type.index);
        if (!node)
            return false;
        return node->sub_7101108624();
    }
    default:
        return false;
    }

    if (no_child) {
        for (s32 i = 0; i < 4; ++i) {
            if (mChildren[i] && mChildren[i]->hasImageMaybe(type))
                return false;
        }
        return true;
    }

    for (s32 i = 0; i < 4; ++i) {
        if (!mChildren[i] || !mChildren[i]->hasImageMaybe(type))
            return true;
    }
    return false;
}

// NON_MATCHING: the original keeps a separate ".extm" store for the type-2 case (block layout).
s32 Unk_7101106F44::sub_710111FD70(sead::BufferedSafeString* out, const ImageTypeMaybe& type) const {
    if (!getImageMaybe(type))
        return 0;

    char* buffer = out->getBuffer();
    const u8 name_length = mNameLength;
    std::memcpy(buffer, mName, name_length);
    char* end = buffer + name_length;
    switch (type.type) {
    case 0:
        std::memcpy(end, ".hght", sizeof(".hght"));
        end += sizeof(".hght") - 1;
        break;
    case 1:
        std::memcpy(end, ".mate", sizeof(".mate"));
        end += sizeof(".mate") - 1;
        break;
    case 2: {
        sead::BufferedSafeString str(end, out->getBufferSize() - name_length);
        end += str.format(".%d", type.index);
        std::memcpy(end, ".extm", sizeof(".extm"));
        end += sizeof(".extm") - 1;
        break;
    }
    case 3: {
        const char* name;
        s32 length;
        if (type.index == 1) {
            name = "water";
            length = 5;
        } else if (type.index == 0) {
            name = "grass";
            length = 5;
        } else {
            name = "";
            length = 0;
        }
        *end++ = '.';
        std::memcpy(end, name, length);
        end += length;
        std::memcpy(end, ".extm", sizeof(".extm"));
        end += sizeof(".extm") - 1;
        break;
    }
    }
    return end - out->cstr();
}

// NON_MATCHING: stack slot layout and register allocation in the sampler call (the 12 zero bytes of
// the cleared mip table and the half size are the same).
// Placeholder name: the material record at `xz`, sampled from the material image (type 1) of the
// neighbouring area; the reference taken by sub_7101108860 is released again.
u32 sub_710110BD78(MaterialRecordMaybe* out, const sead::Vector2f* xz, System* system, bool flag) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;

    const ImageTypeMaybe& type = sUnk_7101EC54B4;
    const auto* collector = system->mScenes(0).collector;
    if (collector->_0[6]._20._0 & 4) {
        if ((~collector->_0[6]._20._0 & 3) != 0)
            return 0;
        sead::Vector2f pos = sead::Vector2f::zero;
        s32 index;
        const u32 result =
            sub_7101108AE8(&pos, &index, *xz, collector->_0[6]._20, collector->_0[6], 0xffffffff);
        if (result != 0) {
            Unk_7101108C44Arg arg;
            arg.table = collector->_0[6]._20.table;
            arg.index = index;
            arg._c = false;
            out->raw = sub_710110BA6C(pos.x, pos.y, &arg, 0);
        }
        return result;
    }

    const u32 index =
        flag ? collector->_0[6].sub_71010FEDBC(*xz, collector->_0[6]._20._2, 0.0f) : 0xffffffff;
    Unk_7101106F44* area;
    sead::Vector2f center;
    f32 size;
    const u32 result =
        Unk_7101106F44::sub_7101108860(&area, &center, &size, *xz, system, type, index);
    if (result == 0)
        return result;

    const f32 map_size = size;
    const f32 half = map_size * 0.5f;
    const f32 u = xz->x - (center.x - half);
    const f32 v = xz->y - (center.y - half);
    TextureMipTableMaybe table;
    table.clearMaybe();
    sub_710110DE64(&table, area->mImage1.getTextureDataMaybe());
    TextureSamplerArgMaybe arg;
    arg.table = &table;
    arg._8 = 0;
    arg._c = true;
    const f32 inv = 1.0f / map_size;
    out->raw = sub_710110B814(u * inv, v * inv, &arg, 0);

    area->releaseImageMaybe(type);
    return result;
}

u32 sub_710110C02C(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                   System* system, bool flag) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    MaterialRecordMaybe record;
    record.raw = 0xff;
    const u32 result = sub_710110BD78(&record, xz, system, flag);
    if (result == 0)
        return result;

    const u32 index = record._1 >= 0 ? record._3 : record._2;
    const auto* data = &Terrain::instance()->_370->_4ae0->_10;
    *material = data->_738.isIndexValid(index) ? data->_738(index).a : -1;
    data = &Terrain::instance()->_370->_4ae0->_10;
    *submaterial = data->_738.isIndexValid(index) ? data->_738(index).b : -1;
    return int(*material) == -1 ? 0 : result;
}

void sub_710110C134(s32* out_a, s32* out_b, s32 index) {
    const auto* data = &Terrain::instance()->_370->_4ae0->_10;
    *out_a = data->_738.isIndexValid(index) ? data->_738(index).a : -1;
    data = &Terrain::instance()->_370->_4ae0->_10;
    *out_b = data->_738.isIndexValid(index) ? data->_738(index).b : -1;
}

u32 sub_710110B6A4(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                   System* system) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    auto* info = system->sub_710111F504();
    u32 value;
    const u32 result = sub_710110B38C(&value, xz, &info->_20, info);
    value >>= 8;
    if (result == 0)
        return result;

    const auto* data = Terrain::instance()->_370->_4ae0;
    *material = data->_3910 > value ? data->_3918[value].a : -1;
    data = Terrain::instance()->_370->_4ae0;
    *submaterial = data->_3910 > value ? data->_3918[value].b : -1;
    return int(*material) == -1 ? 0 : result;
}

void sub_710110B7A4(s32* out_a, s32* out_b, s32 index) {
    const auto* data = Terrain::instance()->_370->_4ae0;
    *out_a = index < data->_3910 ? data->_3918[index].a : -1;
    data = Terrain::instance()->_370->_4ae0;
    *out_b = index < data->_3910 ? data->_3918[index].b : -1;
}

bool sub_710110C1A4(u32* out, u32 index) {
    const auto* data = Terrain::instance()->_370->_4ae0;
    if (u32(data->_10._700) <= index)
        return false;
    *out = data->_10._720->mValues[index];
    return true;
}

// NON_MATCHING: the two-byte reads are combined differently (and converted unsigned in the original);
// scheduling.
sead::Vector3f sub_710110C930(const Unk_7101108C44Arg* arg, const TexelPosMaybe* texel, u32 level) {
    const Unk_710110AC74Table* table = arg->table;
    const u32 max = table->levels[level].size - 1;
    const u32 pitch = table->levels[level].pitch;
    const u32 texel_size = table->texel_size;
    const u8* data = table->areas[arg->index].levels[level];
    const auto read = [](const u8* texel) { return u16(texel[0] | texel[1] << 8) / 65535.0f; };
    const u32 row0 = sead::Mathu::min(texel->y, max) * pitch;
    const u32 col0 = sead::Mathu::min(texel->x, max) * texel_size;
    const f32 h00 = read(data + (row0 + col0));
    const u32 col1 = sead::Mathu::min(texel->x + 1, max) * texel_size;
    const f32 h01 = read(data + (row0 + col1));
    const u32 row1 = sead::Mathu::min(texel->y + 1, max) * pitch;
    const f32 h10 = read(data + (row1 + col0));
    const f32 h11 = read(data + (row1 + col1));
    const f32 dx0 = h01 - h00;
    const f32 dx1 = h11 - h10;
    const f32 dz0 = h10 - h00;
    const f32 dz1 = h11 - h01;
    const f32 top = h00 + texel->fx * dx0;
    return {dx0 + (dx1 - dx0) * 0.0f, dz0 + (dz1 - dz0) * 0.0f,
            top + texel->fy * ((h10 + texel->fx * dx1) - top)};
}

// NON_MATCHING: register allocation; the not-found return is a separate block in ours.
bool sub_710110C1E4(u32* out, const sead::SafeString& name) {
    const u32 count = Terrain::instance()->_370->_4ae0->_10._700;
    for (s32 i = 0; i < count; ++i) {
        if (sead::SafeString(Terrain::instance()->_370->_4ae0->_10._718->mNames[s32(i)]->name) == name) {
            *out = Terrain::instance()->_370->_4ae0->_10._720->mValues[i];
            return true;
        }
    }
    return false;
}

// NON_MATCHING: the original keeps the list node and reloads the found node from it.
bool System::sub_7101118B34(sead::Heap* heap, Unk_7101106F44* area,
                                    Unk_710110d278::Key* key, bool check) {
    Unk_7101108460* found = nullptr;
    for (Unk_7101108460* node : area->mNodes) {
        if (node->getB()->_8 == key) {
            found = node;
            break;
        }
    }

    if (found) {
        if (!check || !(Terrain::instance()->_a58 & 0x400) || found->getA()->_8 & 1)
            return true;
        return false;
    }

    if (area->mParent && !sub_7101118B34(heap, area->mParent, key, check))
        return false;

    Unk_7101108460* node = area->sub_7101108460(heap, key);
    if (!node)
        return false;
    if (check)
        node->getA()->_8 |= 1;
    return true;
}

// NON_MATCHING: two registers swapped in the type-3 loop.
void System::sub_71011176BC(Unk_7101106F44* area, bool flag) {
    void (System::*fn)(Unk_7101106F44*, const ImageTypeMaybe&) =
        flag ? &System::sub_71011171D8 : &System::sub_710111731C;

    (this->*fn)(area, sUnk_7101EC54AC);
    (this->*fn)(area, sUnk_7101EC54B4);
    for (Unk_7101108460* node : area->mNodes)
        (this->*fn)(area, node->getImageType());
    for (Unk_710250db28* image : area->mImages)
        (this->*fn)(area, image->getImageType());
}

// NON_MATCHING: `area` and `type` swap callee-saved registers.
// NON_MATCHING: register allocation (the _1050 address is kept in a callee-saved register here).
void System::sub_7101119278(const sead::SafeString& path, bool split) {
    if (!split)
        _1050.copy(path);
    else
        sub_7101123258(&_1050, path, '/', false);
    const s32 slash = _1050.rfindIndex("/");
    _1168 = _1050.getPart(slash + 1);
    if (_1050.findIndex(":") == -1)
        _1338 &= ~0x80000000;
    else
        _1338 |= 0x80000000;
}

void System::sub_7101117048(s32 index, const sead::Vector3f* arg, bool request_all) {
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return;
    mLock.writeLock();
    mScenes[index].collector->sub_71011021E4(this, arg, request_all);
    sub_7101115BAC();
    mLock.writeUnlock();
}

bool System::sub_71011170F4(s32 index, u32 level) {
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return true;
    return mScenes[index].collector->sub_71011020C0(level);
}

sead::Vector3f* System::sub_710111713C(s32 index) {
    return &mScenes[index].collector->_276c;
}

void System::sub_710111718C(s32 index) {
    mScenes[index].collector->sub_71011066F0();
}

// 0x7101116d44 (placeholder name): flips the patch-buffer parity, points every scene's block at the
// new buffer and swaps the buffers of the registered map patchers.
void System::sub_7101116D44() {
    _1328 = 1 - _1328;

    // NON_MATCHING: in the inlined block update the original keeps the parity byte in a second
    // zero-extended register for the multiply, while ours masks it in place after the flag store
    // (the same instructions in a different order).
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i) {
        mScenes[i].block.setBufferIndexMaybe(_1328);
        mScenes[i].collector->sub_71011016F4();
    }

    mPatcherCS.lock();
    for (MapPatcher& patcher : mPatchers)
        patcher.sub_710107E060();
    mPatcherCS.unlock();
}

// 0x7101118710 (placeholder name): marks the collector image flag that corresponds to each type
// in `types`.
void System::sub_7101118710(const s32* types, u32 count) {
    for (s32 i = 0; i < count; ++i) {
        const s32 type = types[i];
        if (type == s32(sUnk_7101EC54AC.raw)) {
            for (s32 j = 0; j < mScenes.size(); ++j)
                mScenes[j].collector->_2998 |= 0x1100;
        } else if (type == s32(sUnk_7101EC54B4.raw)) {
            for (s32 j = 0; j < mScenes.size(); ++j)
                mScenes[j].collector->_2998 |= 0x2200;
        } else if (type == s32(sUnk_7101EC54B8.raw)) {
            for (s32 j = 0; j < mScenes.size(); ++j)
                mScenes[j].collector->_2998 |= 0x4400;
        } else if (type == s32(sUnk_7101EC54BC.raw)) {
            for (s32 j = 0; j < mScenes.size(); ++j)
                mScenes[j].collector->_2998 |= 0x8800;
        }
    }
}

// 0x71011191bc (placeholder name): binds a map patcher to this system and pushes it onto the
// +0xc0 list under the +0x80 lock.
void System::sub_71011191BC(MapPatcher* patcher) {
    auto lock = sead::makeScopedLock(mPatcherCS);
    patcher->sub_710107E098(this);
    mPatchers.pushBack(patcher);
}

// 0x710111921c (placeholder name): unbinds and removes a map patcher.
void System::sub_710111921C(MapPatcher* patcher) {
    patcher->sub_710107E098(nullptr);
    auto lock = sead::makeScopedLock(mPatcherCS);
    mPatchers.erase(patcher);
}

// 0x71011190c8 (placeholder name): registers an image user in the system's +0x68 list. The
// element type is not recoverable from the callers (mapPlacementMap stores the routes as void*).
void sub_71011190C8(void* tera_system, void* route) {
    auto* system = static_cast<System*>(tera_system);
    auto lock = sead::makeScopedLock(system->mImageUsersCS);
    system->mImageUsers.pushBack(static_cast<ImageUser*>(route));
}

// 0x710111911c (placeholder name): marks all four image types for an update and unregisters the
// route from the system's +0x68 list.
void sub_710111911C(void* tera_system, void* route) {
    auto* system = static_cast<System*>(tera_system);
    {
        const s32 types[4] = {s32(sUnk_7101EC54AC.raw), s32(sUnk_7101EC54B4.raw),
                              s32(sUnk_7101EC54B8.raw), s32(sUnk_7101EC54BC.raw)};
        system->sub_7101118710(types, 4);
    }
    auto lock = sead::makeScopedLock(system->mImageUsersCS);
    system->mImageUsers.erase(static_cast<ImageUser*>(route));
}

// 0x7101116bbc (unnamed in the CSV): the material texture scale record of the terrain. x is the mip
// scale from the frame's factor and Terrain::_34c; y / z / w are the three half-texel offsets of the
// material textures 0 / 1 / 2, the last two scaled by log2 of their width ratio.
void System::sub_7101116BBC(sead::Vector4f* out, f32 factor) {
    auto* textures = &Terrain::instance()->_370->_4ae0->_10;
    const MaterialTextureMaybe* tex0 = textures->m12(0);
    textures = &Terrain::instance()->_370->_4ae0->_10;
    const MaterialTextureMaybe* tex1 = textures->m12(1);
    textures = &Terrain::instance()->_370->_4ae0->_10;
    const MaterialTextureMaybe* tex2 = textures->m12(2);

    if (!tex0->material || !tex1->material || !tex2->material) {
        out->set(1.0f, 0.0f, 0.0f, 0.0f);
        return;
    }

    const u32 width0 = tex0->getWidthMaybe();
    const u32 width1 = tex1->getWidthMaybe();
    const u32 width2 = tex2->getWidthMaybe();

    out->x = 1.0f / (0.5f / factor * Terrain::instance()->_34c);
    out->y = tex0->sub_7101140644() - 1.25f;
    out->z = (tex1->sub_7101140644() - 1.25f) +
             logf(f32(width1) / f32(width0)) * 1.4426950f;
    out->w = (tex2->sub_7101140644() - 1.25f) +
             logf(f32(width2) / f32(width0)) * 1.4426950f;
}

// 0x7101116e74 (placeholder name): under the read lock, updates scene `index`'s uniform block from
// the culling frustum and runs the collector's per-scene update.
// NON_MATCHING: the inline flush's loads and stores are scheduled differently (the same
// instructions, e.g. the block pointer is loaded and stored before the offset is computed); the
// calls, values, stack records and branches are the same.
void System::sub_7101116E74(s32 index, Unk_7101115584Arg* arg) {
    mLock.readLock();

    SceneSlot& slot = mScenes[index];
    {
        auto* terrain = Terrain::instance();
        if (terrain->sub_710107EC48() && (terrain->_a58 & 0x10))
            sub_71011167AC(index, false);
    }

    if (arg->_0) {
        {
            struct Data7 {
                u32 _0;
                sead::Vector3f _4;
            } data7;
            sead::Vector4f scale;
            sub_7101116BBC(&scale, arg->_0->get_f4());

            struct Data6 {
                u32 _0;
                u32 _4;
                f32 _8;
                f32 _c;
            } data6;
            data6._0 = 0;
            {
                auto* terrain = Terrain::instance();
                data6._4 = terrain->_3f0;
                data6._8 = terrain->sub_710107EC48() && (terrain->_a58 & 0x10) ? 1.0f : 0.0f;
            }
            {
                auto* terrain = Terrain::instance();
                data6._c = terrain->sub_710107EC48() && (terrain->_a58 & 0x10) ? 0.0f : 1.0f;
            }

            slot.block.setData(5, &scale, 0, 1);
            slot.block.setData(6, &data6, 0, 1);

            data7._0 = Terrain::instance()->_3f8;
            data7._4.set(0.0f, 0.0f, 0.0f);
            slot.block.setData(7, &data7, 0, 1);
        }

        slot.block.flushCPUCache();
    }

    slot.collector->sub_7101101704(this, arg);
    mLock.readUnlock();
}

void System::sub_7101117164(void* arg, s32 index, const sead::Vector3f* pos, u32 level) {
    mScenes[index].collector->sub_710110235C(arg, this, pos, level);
}

// NON_MATCHING: the original indexes _e8 with a sign-extended multiply each iteration; ours walks a pointer.
void System::x_2() {
    f32 width;
    auto* materials = Terrain::instance()->_370->_4ae0;
    if (materials->_10._8) {
        // called through a pointer in the original (not devirtualised)
        width = (&materials->_10)->m12(0)->getWidthMaybe();
    } else {
        width = 1024.0f;
        if (auto* debug = Terrain::instance()->_a50) {
            auto entry = debug->_70.log(
                "マテリアルが読み込まれていないのに Scene::setMaterialUVWInfo が処理されました！");
            if (entry.buffer)
                entry.buffer->setDisplayTime(10.0f);
        }
    }

    const u32 count = Terrain::instance()->_370->_4ae0->_10._700;
    for (s32 i = 0; i < count; ++i) {
        MaterialUVWMaybe& entry = _e8[i];
        entry.value = Terrain::instance()->_370->_4ae0->_10._720->mValues[i];
        entry.scale = width * sead::Mathf::max(entry._4, entry._8);
    }
}

void System::sub_71011171D8(Unk_7101106F44* area, const ImageTypeMaybe& type) {
    Unk_710250dcd8* image = area->getImageMaybe(type);
    if (!image)
        return;
    if (image->_18._0.increment() == 0)
        pushEntryMaybe(area, type);
}

// NON_MATCHING: `area` and `type` swap callee-saved registers.
void System::sub_710111731C(Unk_7101106F44* area, const ImageTypeMaybe& type) {
    Unk_710250dcd8* image = area->getImageMaybe(type);
    if (!image)
        return;
    if (image->_18._0.decrement() == 1)
        pushEntryMaybe(area, type);
}

void System::sub_7101118908(Unk_7101106F44* area, u16 id) {
    const Unk_7101108460* node = area->findNodeMaybe(id);
    if (!node->sub_7101108624())
        return;

    s32 count = 0;
    for (const Unk_7101106F44* child : area->mChildren) {
        if (!child)
            continue;
        const Unk_7101108460* child_node = child->findNodeMaybe(id);
        if (child_node)
            count += child_node->sub_7101108624();
    }

    if (count == 4) {
        Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, makeImageTypeMaybe(2, id),
                                                               false, nullptr);
        area->sub_7101108298(const_cast<Unk_7101108460*>(node));
    }
}

// NON_MATCHING: register allocation; the control flow matches.
bool System::sub_7101118C40(sead::Heap* heap, Unk_7101106F44* area,
                                    Unk_710110d278::Key* key, u32 size, bool check, f32 value) {
    const u16 id = key->id;
    Unk_7101108460* node = const_cast<Unk_7101108460*>(area->findNodeMaybe(id));

    if (!node) {
        if (Unk_7101106F44* parent = area->mParent) {
            if (!parent->sub_7101108174(id)) {
                if (!sub_7101118B34(heap, parent, key, check))
                    return false;
            } else if (const Unk_7101108460* parent_node = parent->findNodeMaybe(id)) {
                if (check && Terrain::instance()->_a58 & 0x400 &&
                    !(const_cast<Unk_7101108460*>(parent_node)->getA()->_8 & 1)) {
                    return false;
                }
                sub_7101118908(parent, id);
            } else if (!sub_7101118C40(heap, parent, key, size, check, value)) {
                return false;
            }
        }
        node = area->sub_7101108334(heap, key, size, value);
    } else {
        if (check && Terrain::instance()->_a58 & 0x400) {
            const Unk_710250dcd8* image = area->getImageMaybe(makeImageTypeMaybe(2, id));
            if (!image || !(image->_8 & 1))
                return false;
        }

        if (node->sub_7101108624() && u32(node->getA()->mSize) == size)
            return false;

        s32 count = 0;
        for (Unk_7101106F44* child : area->mChildren) {
            if (!child)
                continue;
            const Unk_7101108460* child_node = child->findNodeMaybe(id);
            if (child_node && (child_node->sub_7101108624() ||
                               sub_7101118C40(heap, child, key, size, check, value))) {
                ++count;
            }
        }
        if (count == 4)
            return true;

        Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, makeImageTypeMaybe(2, id),
                                                               false, nullptr);
        area->sub_71011081D4(node, heap, size, value);
    }

    if (check) {
        node->getA()->_8 |= 0x10;
        node->getA()->_8 |= 0x20;
        node->getA()->_8 |= 1;
    }
    return true;
}

// NON_MATCHING: the index compare zero-extends the u16 (the original compares the full register).
bool System::sub_7101118FC0(sead::Heap* heap, Unk_7101106F44* area, u32 index, bool check,
                            Unk_7101112C94Listener* listener) {
    const Unk_710250dcd8* image = area->getImageMaybe(makeImageTypeMaybe(3, index));
    if (image) {
        if (check && Terrain::instance()->_a58 & 0x400)
            return image->_8 & 1;
        return true;
    }

    if (area->mParent && !sub_7101118FC0(heap, area->mParent, index, check, listener))
        return false;
    if (Unk_710250db28* created = area->sub_7101108564(heap, index, 1); created && check)
        created->_8 |= 1;
    if (listener)
        listener->m0(area, 3);
    return true;
}

// 0x71011501c0 / 0x71011501c8: the two world::ChemicalMgr cleanup paths forward the grass
// renderer at Core::Grass::_30.
void sub_71011501C0(Core::Grass* grass) {
    sub_71012DAFB8(grass->_30);
}

void sub_71011501C8(Core::Grass* grass) {
    sub_71012DC42C(grass->_30);
}

void sub_71011501D0(Core::Grass* grass) {
    sub_71012DC608(grass->_30);
}

}  // namespace ksys::tera


// Placeholder: the record 0x7100fddc28 writes (u64 at 0x60).
struct Unk_7100FDDC28Maybe {
    u8 _0[0x60];
    u64 _60;
};

void sub_7100FDDC28(Unk_7100FDDC28Maybe* record, u64 value) {
    record->_60 = value - 2;
}


s32 getSceneStatus() {
    return ksys::tera::sUnk_710260B220._10;
}

void setSceneFinalStatus(s32 status) {
    ksys::tera::sUnk_710260B220._10 = status;
}

void setIsGenStage(u32 value) {
    ksys::tera::sUnk_710260B184 = value & 1;
}

namespace uking {
void* sub_7100F41834() {
    return ksys::tera::sUnk_710260B220._f0;
}
}  // namespace uking

namespace ksys::frm {
Framework* Framework::instance() {
    return static_cast<Framework*>(ksys::tera::sUnk_710260B220._30);
}
}  // namespace ksys::frm

namespace uking {
void Root38::setInstance2(Root38* value) {
    ksys::tera::sUnk_710260B220._50 = value;
}
}  // namespace uking

// 0x7100F3F84C (CSV free function): records terrain bit index `index` in sUnk_710260B18C (indices 0..9
// come from the material callback 0x7101200AC0; resBfRes passes 9 for an Independence shape).
void sub_7100F3F84C(u32 index) {
    ksys::tera::sUnk_710260B18C |= 1u << index;
}
