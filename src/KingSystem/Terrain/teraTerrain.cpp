#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Terrain/teraGrass.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/Terrain/teraVegeTeraMat.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <g3d/aglNW4FToNN.h>
#include "KingSystem/Terrain/teraResourceNode.h"
#include <cmath>
#include <prim/seadScopedLock.h>
#include <random/seadGlobalRandom.h>
#include <prim/seadBitUtil.h>
#include <filedevice/seadFileDevice.h>
#include <nn/gfx/gfx_ResTexture.h>
#include <nn/g3d/ResModel.h>
#include <nn/g3d/ResMaterial.h>
#include <math/seadMathCalcCommon.h>
#include <common/aglDrawContext.h>
#include <common/aglShaderProgram.h>
#include <utility/aglPrimitiveShape.h>
#include <utility/aglVertexAttributeHolder.h>
#include <gfx/seadViewport.h>
#include <gfx/seadProjection.h>
#include <mc/seadCoreInfo.h>
#include <thread/seadThread.h>
#include "KingSystem/Physics/System/physClosestPointQueryWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace ksys::tera {

const f32 sUnk_7101E79608[4] = {0.0f, 0.5f, 0.0f, 0.5f};
const f32 sUnk_7101E79618[4] = {0.0f, 0.0f, 0.5f, 0.5f};

// NON_MATCHING: bounded grid iteration and floor arithmetic differ in scheduling.
void Core::Grass::EntryPart::sub_7101076258(f32 diameter, f32, const sead::Vector2f* position) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    f32 radius = diameter * 0.5f;
    if (radius > 3.0f)
        radius = 3.0f;
    const s32 min_x = sead::Mathi::max(23 - mGridPosition.x +
        sead::Mathf::floor((position->x - radius) / 3.0f), 0);
    const s32 min_y = sead::Mathi::max(23 - mGridPosition.y +
        sead::Mathf::floor((position->y - radius) / 3.0f), 0);
    const s32 max_x = sead::Mathi::min(23 - mGridPosition.x +
        sead::Mathf::floor((position->x + radius) / 3.0f), 46);
    const s32 max_y = sead::Mathi::min(23 - mGridPosition.y +
        sead::Mathf::floor((position->y + radius) / 3.0f), 46);
    for (s32 y = min_y; y <= max_y; ++y) {
        for (s32 x = min_x; x <= max_x; ++x) {
            auto& cell = mCells[(y + mCellIndices.y) % 47][(x + mCellIndices.x) % 47];
            if (!(cell.mFlags & 1))
                continue;
            cell.mRecord->_3f = 3;
            cell.mFlags &= ~8u;
        }
    }
}

// NON_MATCHING: bounded grid iteration and floor arithmetic differ in scheduling.
void Core::Grass::EntryPart::sub_7101076488(f32 diameter, f32, const sead::Vector2f* position) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    f32 radius = diameter * 0.5f;
    if (radius > 3.0f)
        radius = 3.0f;
    const s32 min_x = sead::Mathi::max(23 - mGridPosition.x +
        sead::Mathf::floor((position->x - radius) / 3.0f), 0);
    const s32 min_y = sead::Mathi::max(23 - mGridPosition.y +
        sead::Mathf::floor((position->y - radius) / 3.0f), 0);
    const s32 max_x = sead::Mathi::min(23 - mGridPosition.x +
        sead::Mathf::floor((position->x + radius) / 3.0f), 46);
    const s32 max_y = sead::Mathi::min(23 - mGridPosition.y +
        sead::Mathf::floor((position->y + radius) / 3.0f), 46);
    for (s32 y = min_y; y <= max_y; ++y) {
        for (s32 x = min_x; x <= max_x; ++x) {
            auto& cell = mCells[(y + mCellIndices.y) % 47][(x + mCellIndices.x) % 47];
            if (!(cell.mFlags & 1))
                continue;
            cell.mRecord->_3f = 3;
            cell.mFlags &= ~16u;
        }
    }
}

// NON_MATCHING: handle selection, item iteration and transform scheduling differ.
void Core::Grass::EntryPart::sub_7101075788(const sead::Vector2f* position) {
    if (_384c8 < 17.777779f)
        return;
    _384c8 -= 17.777779f;
    act::BaseProcHandle* handle = nullptr;
    for (auto& candidate : mSpawnHandles) {
        if (!candidate.isAllocatedOrFailed()) {
            handle = &candidate;
            break;
        }
    }
    if (!handle || world::Manager::instance()->isAocField())
        return;
    eco::AreaItemSet items;
    const s32 area = eco::Ecosystem::instance()->getFieldMapArea(position->x, position->y);
    eco::Ecosystem::instance()->getAreaItems(area, eco::AreaItemType::GrassCut, &items);
    const eco::AreaItem* selected = nullptr;
    for (s32 i = 0; i < items.count; ++i) {
        const auto& item = items.items[i];
        if (act::shouldSkipSpawnFairy(item.name))
            continue;
        if (sead::GlobalRandom::instance()->getU32(1001) < u32(item.num) &&
            (!selected || item.num < selected->num)) {
            selected = &item;
        }
    }
    if (!selected)
        return;
    auto* entry = mEntry;
    f32 height = 0.0f;
    if (sub_71011094A0(&height, position, entry->mSystem, -1, 0) != 2)
        return;
    f32 water_height = 0.0f;
    if (sub_710110B4A4(&water_height, position, entry->mSystem) != 2)
        return;
    if (height <= water_height && act::hasTag(selected->name, 0x5ad0d068))
        return;
    const f32 angle = sead::GlobalRandom::instance()->getF32() * (2.0f * sead::Mathf::pi());
    sead::Matrix34f transform;
    transform.makeRT(sead::Vector3f(0.0f, angle, 0.0f),
                     sead::Vector3f(position->x, height + 0.15f, position->y));
    act::InstParamPack params;
    params->addMatrix(transform);
    act::ActorCreator::instance()->requestCreateActor(selected->name,
        map::PlacementMgr::instance()->mDynamicHeap, handle, &params, nullptr, 1);
}

// NON_MATCHING: the common mask-layer loop is merged and floating calculations are scheduled differently.
void Core::Grass::EntryPart::applyMaskBrush(f32 diameter, f32 blend,
                                            const sead::Vector2f* position,
                                            bool second_layer, bool spawn) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    const f32 radius = diameter * 0.5f;
    const s32 min_x = sead::Mathi::max(23 - mGridPosition.x +
        sead::Mathf::floor((position->x - radius) / 3.0f), 0);
    const s32 min_y = sead::Mathi::max(23 - mGridPosition.y +
        sead::Mathf::floor((position->y - radius) / 3.0f), 0);
    const s32 max_x = sead::Mathi::min(23 - mGridPosition.x +
        sead::Mathf::floor((position->x + radius) / 3.0f), 46);
    const s32 max_y = sead::Mathi::min(23 - mGridPosition.y +
        sead::Mathf::floor((position->y + radius) / 3.0f), 46);
    for (s32 y = min_y; y <= max_y; ++y) {
        for (s32 x = min_x; x <= max_x; ++x) {
            auto& cell = mCells[(y + mCellIndices.y) % 47][(x + mCellIndices.x) % 47];
            if (!(cell.mFlags & 1))
                continue;
            auto& record = *cell.mRecord;
            u16& mask = second_layer ? record._14 : record._12;
            for (s32 quadrant = 0; quadrant < 4; ++quadrant) {
                const f32 base_x = cell.mOriginX + sUnk_7101E79608[quadrant] * 3.0f + 0.375f;
                const f32 base_y = cell.mOriginZ + sUnk_7101E79618[quadrant] * 3.0f + 0.375f;
                for (s32 sub = 0; sub < 4; ++sub) {
                    const u32 bit = 1u << (quadrant * 4 + sub);
                    if (!(mask & bit))
                        continue;
                    const sead::Vector2f sample(base_x + sUnk_7101E79608[sub] * 3.0f * 0.5f,
                                                base_y + sUnk_7101E79618[sub] * 3.0f * 0.5f);
                    const f32 distance = (*position - sample).length();
                    const f32 weight = sead::Mathf::clamp((1.0f - blend) +
                                                         distance / radius * blend, 0.0f, 1.0f);
                    if (weight > 0.25f)
                        mask |= bit;
                    else
                        mask &= ~bit;
                    const f32 coverage = mEntry->mGrass->_28->sub_7101069C44(&sample);
                    if (spawn && weight <= 0.25f && coverage > 0.5f &&
                        f32(record._24) / 255.0f > 0.25f) {
                        _384c8 += 1.0f;
                        sub_7101075788(&sample);
                    }
                }
            }
        }
    }
}


// Clears newly exposed rows and columns while shifting the 47 x 47 rolling grid.
void shiftGrassCellGrid(Core::Grass::EntryPart::Cell (*cells)[47],
                        sead::Vector2i* indices, sead::Vector2i* previous,
                        sead::Vector2i position,
                        Core::Grass::EntryPart::CellState (*states)[47]) {
    const s32 dx = position.x - previous->x;
    if (dx > 0) {
        for (s32 i = 0; i < dx; ++i) {
            const s32 x = (indices->x + i) % 47;
            for (s32 y = 0; y < 47; ++y) {
                cells[y][x].reset();
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dx < 0) {
        for (s32 i = -1; i >= dx; --i) {
            s32 x = (indices->x + i) % 47;
            if (x < 0)
                x += 47;
            for (s32 y = 0; y < 47; ++y) {
                cells[y][x].reset();
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dx != 0) {
        previous->x += dx;
        indices->x = (indices->x + dx) % 47;
        if (indices->x < 0)
            indices->x += 47;
    }
    const s32 dy = position.y - previous->y;
    if (dy > 0) {
        for (s32 i = 0; i < dy; ++i) {
            const s32 y = (indices->y + i) % 47;
            for (s32 x = 0; x < 47; ++x) {
                cells[y][x].reset();
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dy < 0) {
        for (s32 i = -1; i >= dy; --i) {
            s32 y = (indices->y + i) % 47;
            if (y < 0)
                y += 47;
            for (s32 x = 0; x < 47; ++x) {
                cells[y][x].reset();
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dy != 0) {
        previous->y += dy;
        indices->y = (indices->y + dy) % 47;
        if (indices->y < 0)
            indices->y += 47;
    }
}

// NON_MATCHING: the compiler inlines the cell reset and unrolls the state clearing loop.
void Core::Grass::EntryPart::resetCells() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    _68 = 0;
    _878 = 0;
    for (auto& row : mCells)
        for (auto& cell : row)
            cell.reset();
    for (auto& row : mCellStates) {
        for (auto& state : row) {
            state._0 = 0;
            state._2 = 0;
        }
    }
    _384c8 = 0.0f;
    _384d0 = -1;
}

// NON_MATCHING: the first record stores reload its pointer once more.
void Core::Grass::EntryPart::Cell::reset() {
    mRecord->_0 = 0;
    mRecord->_4 = 0;
    _1c = 0xff0000;
    mFlags = 0;
    mRecord->_7 = 0;
    mRecord->_8 = 0;
    mRecord->_9 = 0;
    mRecord->_a = 0;
    _1a = 0;
    mRecord->_c = 0;
    mRecord->_e = 0;
    mRecord->_10 = 0;
    mRecord->_12 = 0xffff;
    mRecord->_14 = 0xffff;
    mRecord->_16 = 0;
    mRecord->_17 = 0;
    mRecord->_18 = 0xff;
    mRecord->_19 = 0;
    mRecord->_1c = 0;
    mRecord->_20 = 0;
    mRecord->_3f = 0;
    _18 = 0;
    mRecord->_24 = 0;
    mRecord->_25 = 0;
    mRecord->_26 = 0;
    mRecord->_27 = 0;
    mRecord->_28 = 0;
    mRecord->_2c = 0;
    mRecord->_30 = sead::GlobalRandom::instance()->getF32();
    mRecord->_5 = sead::GlobalRandom::instance()->getU32(255);
    mRecord->_6 = sead::GlobalRandom::instance()->getU32(255);
    mRecord->_34 = 0;
    mRecord->_35 = -1;
    mRecord->_36 = -1;
    mRecord->_37 = -1;
    mRecord->_3c = 0;
    mRecord->_3d = 0;
    mRecord->_3e = 0;
}

// NON_MATCHING: index stream reads and the native buffer-address call are scheduled differently.
void Terrain::sub_710114CE48(agl::DrawContext* context, const agl::ShaderProgram* program,
                            const agl::TextureSampler* sampler, const sead::Vector4f* a,
                            const sead::Vector4f* b, const sead::Vector4f* c) {
    const auto& c_location = program->getUniformLocation(2);
    if (c_location.getLocation() != -1)
        c_location.setUniformNVN(context, 4, c);
    const auto& a_location = program->getUniformLocation(0);
    if (a_location.getLocation() != -1)
        a_location.setUniformNVN(context, 4, a);
    const auto& b_location = program->getUniformLocation(1);
    if (b_location.getLocation() != -1)
        b_location.setUniformNVN(context, 4, b);
    sampler->activate(context, program->getSamplerLocation(0), -1, false);
    agl::utl::VertexAttributeHolder::instance()->getVertexAttribute(7).activate(context);
    auto& stream = agl::utl::PrimitiveShape::instance()->getIndexStream();
    if (stream.getIndexCount())
        nvnCommandBufferDrawElements(context->getCommandBuffer()->ToData()->pNvnCommandBuffer,
            stream.getPrimitiveType(), NVNindexType(stream.getFormat()), stream.getIndexCount(),
            stream.getBufferAddress());
}

// NON_MATCHING: variation-data loads and uniform temporary stores are scheduled differently.
u32 Terrain::sub_710114CBF4(agl::DrawContext* context, const DrawArg* arg) {
    const auto* texture = arg->texture;
    const auto* sampler = arg->sampler;
    if (arg->bind_target)
        sub_710114C3C4(context, *texture, arg->mip, arg->layer, 0, 3);
    auto* root_program = _370->_478;
    const u32 variation =
        (sampler->getTextureData().getType() == agl::TextureType::cTextureType_2D_Array ? root_program->getVariationMacroMultiplier(0) : 0) +
        (!(arg->_3c < 0.0f) ? root_program->getVariationMacroMultiplier(1) : 0);
    auto* program = root_program->getVariation(variation);
    const u32 id = variation + 0xf0000;
    if (arg->program_id != id)
        program->activate(context, !(_a58 & 0x8000) || !sub_710114D7C8());
    sead::Vector4f uniform_data{f32(sead::Mathu::max(texture->getWidth(), 1u)), arg->_14, 0, 0};
    const auto& dimensions_location = program->getUniformLocation(3);
    if (dimensions_location.getLocation() != -1)
        dimensions_location.setUniformNVN(context, 4, &uniform_data);
    uniform_data = {arg->_38, arg->_3c, 0, 0};
    const auto& params_location = program->getUniformLocation(4);
    if (params_location.getLocation() != -1)
        params_location.setUniformNVN(context, 4, &uniform_data);
    sub_710114CE48(context, program, sampler, &arg->a, &arg->b, &arg->c);
    if (arg->invalidate)
        sub_710114C9D0(context);
    return id;
}


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

// NON_MATCHING: the original has a dmb ish and reloads mImageResourceMgr before the resume test
// (an atomic read of the manager); ours reads it once.
void Terrain::sub_710114DFAC(bool resume) {
    if (!mImageResourceMgr || (_a58 & 0x10000) != 0)
        return;

    sead::CriticalSection* outer_lock = nullptr;
    if (!resume) {
        outer_lock = &mImageResourceMgr->mCS28;
        outer_lock->lock();
    }

    mImageResourceMgr->_6473 &= ~4;

    auto& lock = mImageResourceMgr->mCS28;
    lock.lock();
    if (resume) {
        mImageResourceMgr->sub_71011311BC();
        _a58 |= 0x20000;
    } else {
        _a58 &= ~0x20000;
    }
    _a58 |= 0x10000;
    lock.unlock();

    if (outer_lock)
        outer_lock->unlock();
}

void Terrain::startImageResourceMgrMaybe() {
    if (!mImageResourceMgr)
        return;
    auto& lock = mImageResourceMgr->mCS28;
    lock.lock();
    ImageResourceMgr* mgr = mImageResourceMgr;
    mgr->_6473 |= 4;
    mgr->sub_71011315BC();
    lock.unlock();
}

// NON_MATCHING: the original walks the entry buffer with a pointer and a bounds-checked record
// index; ours indexes both buffers, so the loop shapes and the prologue differ.
void Core::Grass::sub_71011509EC() {
    for (u32 i = 0; i < mEntries.size(); ++i)
        _28->mRecords[i]._1c &= ~1u;
    for (u32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        sub_710106BC54(entry._0);
        sub_71012E258C(entry._8);
    }
}

void Core::Grass::sub_7101151A1C() {
    _c |= 1;
}

// 0x7101151a14 (unnamed in the CSV): forwards to the _28 object's near-set query result.
bool Core::Grass::sub_7101151A14() {
    return _28->sub_710106A2C4();
}

// 0x7101150a70 (unnamed in the CSV): marks the first grass entry's vegetation material dirty.
void Core::Grass::sub_7101150A70() {
    mEntries.getBufferPtr()->_10->setDirty();
}

// 0x71011501d8 (unnamed in the CSV): hands entry `index` and the position to the vegetation manager.
void Core::Grass::sub_71011501D8(s32 index, const sead::Vector3f* pos) {
    if (!(mFlags & 2))
        return;
    if (!_28)
        return;
    if (mEntries.size() <= index)
        return;
    _28->sub_71010658E8(index, &mEntries[index], *pos);
}

// 0x7101150a7c (unnamed in the CSV): fades the grass around `pos` by `radius`, scaled by `value`
// (the second float), using the terrain height at the position unless the debug flag is set.
void Core::Grass::sub_7101150A7C(const sead::Vector3f* pos, f32 radius, f32 value) {
    if (!(mFlags & 1))
        return;
    if (const auto* terrain = Terrain::instance()) {
        if (const auto* debug = terrain->_a50) {
            if ((debug->_18 & 8) != 0)
                return;
        }
    }

    const sead::Vector2f xz(pos->x, pos->z);
    bool flag = false;
    mEntries.getBufferPtr()->_0->sub_7101075F10(&flag, &xz);
    System* system = mEntries.getBufferPtr()->mSystem;
    f32 scale = 1.0f;
    if (system) {
        f32 height = 0.0f;
        if (flag) {
            height = sub_7101159054(pos, radius);
        } else if (!sub_71011094A0(&height, &xz, system, -1, 0)) {
            return;
        }

        f32 t = (pos->y - radius - height) * 2.0f;
        t = sead::Mathf::clamp(t, 0.0f, 1.0f);
        scale = 1.0f - t;
        if (scale <= 0.0f)
            return;
    }
    _28->sub_71010657DC(pos, radius * scale, value * scale);
}

// NON_MATCHING: vector normalization and matrix stores are scheduled differently.
void Core::Grass::sub_7101152B3C(f32 fovy, const sead::Vector3f* position,
                                    const sead::Vector3f* target) {
    mFlags |= 0x20000;
    if (fovy <= 0.0f)
        fovy = 0.7f;

    auto& entry = *mEntries.getBufferPtr();
    sead::Vector3f direction = *position - *target;
    direction.normalize();
    sead::Vector3f right = sead::Vector3f::ey.cross(direction);
    right.normalize();
    sead::Vector3f up = direction.cross(right);
    up.normalize();
    sead::Matrix34f camera;
    camera.setBase(0, right);
    camera.setBase(1, up);
    camera.setBase(2, direction);
    camera.setBase(3, *position);
    sead::PerspectiveProjection projection;
    projection.set(1.0f, 10000.0f, fovy, 1.7777778f);
    entry.mFrustum.update(camera, projection);
    entry.mCamera = camera;
    entry.mPosition = *position;
}

sead::Vector3f* Core::Grass::sub_7101152DA0(s32 index) {
    return &mEntries[index].mPosition;
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

void Terrain::sub_7101149AF0(bool on) {
    if (((u32(on) ^ (_a58 >> 18)) & 1) == 0)
        return;
    if (mImageResourceMgr) {
        auto& lock = mImageResourceMgr->mCS28;
        lock.lock();
        const u32 value = _a58;
        _a58 = on ? value | 0x40000 : value & ~0x40000u;
        lock.unlock();
        return;
    }
    if (on)
        _a58 |= 0x40000;
    else
        _a58 &= ~0x40000u;
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
void* Terrain::sub_710114D8D0() { return _360 ? &_360->mSystems : nullptr; }
sead::Vector2f Terrain::sub_710114D8E4(const System* system) {
    return system->_10 * _3c8;
}
f32 Terrain::sub_710114D8F8(const System* system) { return system->_18 * _3c8; }

// NON_MATCHING: stack slot layout only: the original keeps the position copy at sp+0x20 and the query at sp+0x30;
// ours puts the copy in the red zone and the query at sp+0x20.
bool teraGrassQueryForGroundObject(const sead::Vector3f* pos, f32 radius) {
    const sead::Vector3f position = *pos;
    phys::SphereBasedClosestPointQuery query(position, radius, phys::ContactLayer::EntityGroundObject,
                                             phys::GroundHit::HitAll, nullptr, 1,
                                             "teraGrass IsThereGroundObject", 1, phys::LowPriority::No);
    query.getContactPointInfo()->subscribeLayer(phys::ContactLayer::EntityGroundObject);
    return query.execute(false);
}

f32 sub_7101159054(const sead::Vector3f* pos, f32 depth) {
    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    query.setGroundHit(phys::GroundHit::HitAll);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityGroundSmooth);
    sead::Vector3f end = *pos;
    end.y -= depth;
    query.setStart(*pos);
    query.setEnd(end);
    if (query.worldRayCast(phys::ContactLayerType::Entity)) {
        sead::Vector3f hit;
        query.getHitPosition(&hit);
        return hit.y;
    }
    return end.y;
}

bool Core::Grass::sub_7101150BA4(const sead::Vector3f* pos, f32 radius) {
    auto* manager = _28;
    const sead::Vector2f xz(pos->x, pos->z);
    return (manager->sub_7101069DB8(&xz, radius) & 1) != 0;
}

// 0x7101150bd8 (unnamed in the CSV): forwards to the _28 object's near-set query.
u32 Core::Grass::sub_7101150BD8(const sead::Vector2f* position, f32 radius) {
    return _28->sub_7101069DB8(position, radius);
}

void Core::Grass::sub_7101150990(bool enabled) {
    const u32 flags = mFlags;
    const u32 set = flags | 0x4000;
    const u32 clear = flags & ~0x4000u;
    mFlags = enabled ? clear : set;
    for (auto& entry : mEntries) {
        sub_710106BC54(entry._0);
        sub_71012E258C(entry._8);
    }
}

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

// 0x7101150fcc (unnamed in the CSV): forwards to the _28 object's near-set query.
bool Core::Grass::sub_7101150FCC(f32 a, f32 b, const sead::Vector2f* position) {
    return _28->sub_710106A0C8(a, b, position);
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

// 0x7101140414 (placeholder name): appends `name` to the pool and returns the allocated copy. The
// "allocated" flag lives at the start of the *next* record (the 8-byte tail holds the last one); the
// System cleanup at 0x710113ecf4 reads it the same way.
// NON_MATCHING: the original tests the buffer size itself and stores the flag through the advanced
// record pointer; ours folds the test to the length's sign and recomputes the flag address.
char* ExtraInfoNamePoolMaybe::addName(sead::Heap* heap, const sead::SafeString& name) {
    const s32 index = s32(count++);
    const s32 length = name.calcLength();
    const s32 size = length + 1;
    // sead's negative alignment: 1 << 4 = 16 bytes.
    char* buffer = new (heap, -4) char[size];
    sead::BufferedSafeString copy(buffer, size);
    copy.copy(name, length);
    names[index].name = buffer;
    names[index + 1]._0[0] = 1;
    return buffer;
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
    for (Unk_710110d278::Key& item : mList.robustRange()) {
        mList.erase(&item);
        mFreeList.free(&item);
    }
}

Unk_710110d278::Key* Terrain::Unk_380::sub_7101138494(const sead::SafeString& name) {
    for (Unk_710110d278::Key& item : mList) {
        if (item.mName == name)
            return &item;
    }
    return nullptr;
}

}  // namespace ksys::tera

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


// 0x7101147b24 / 0x7101147c34 (placeholder names): a 0x170-byte record at a negative offset.


// NON_MATCHING: stack reuse, clamp scheduling and the normal-query result test differ.
u32 Core::Grass::sub_71011516D0(f32* out, const sead::Vector2f* xz) {
    if (!mEntries(0).mSystem)
        return 0;
    if (mFlags & 0x4000) {
        *out = 0.0f;
        return 2;
    }

    f32 height = 0.0f;
    const sead::Vector2f position(xz->x, xz->y);
    const u32 result = sub_7101109BD8(&height, &position, mEntries(0).mSystem, true);
    const f32 level = height * 10.0f;
    const f32 weight = sead::Mathf::clamp(level - 4.5f, 0.0f, 1.0f) * 0.3f +
                       sead::Mathf::clamp(level - 6.5f, 0.0f, 1.0f) * 0.3f +
                       sead::Mathf::clamp(level - 8.5f, 0.0f, 1.0f) * 0.4f;
    const f32 first = _28->sub_7101069760(xz);
    const f32 second = _28->sub_71010699D0(xz);
    *out = weight * (first * second);
    sead::Vector3f normal;
    if (*out > 0.0f && sub_71011096D0(&height, &normal, xz, mEntries(0).mSystem, -1, 0) > 0)
        *out *= sead::Mathf::clamp((normal.y - 0.62f) * 10.0f, 0.0f, 1.0f);
    return result;
}

}

namespace ksys::tera {

// 0x7101152000 (placeholder name): the grass amount of sub_71011516D0 with the ground normal
// correction and the grass scale; returns 2 when the grass is disabled and 1 without terrain data.
// NON_MATCHING: the position copy and the normal share one stack slot in the original, ours gives
// them separate slots, and the original reloads *out after the normal clamp; the rest follows.
u32 Core::Grass::sub_7101152000(f32* out, const sead::Vector2f* xz) {
    if (mFlags & 0x4000) {
        *out = 0.0f;
        return 2;
    }

    if (!mEntries(0).mSystem) {
        *out = 0.0f;
        return 1;
    }

    f32 height = 0.0f;
    const sead::Vector2f position(xz->x, xz->y);
    const u32 result = sub_7101109BD8(&height, &position, mEntries(0).mSystem, true);
    const f32 level = height * 10.0f;
    const f32 weight = sead::Mathf::clamp(level - 4.5f, 0.0f, 1.0f) * 0.3f +
                       sead::Mathf::clamp(level - 6.5f, 0.0f, 1.0f) * 0.3f +
                       sead::Mathf::clamp(level - 8.5f, 0.0f, 1.0f) * 0.4f;
    *out = _17b0 * weight * _28->sub_71010699D0(xz);

    if (*out > 0.0f) {
        f32 normal_height = 0.0f;
        sead::Vector3f normal;
        const s32 hit = sub_71011096D0(&normal_height, &normal, xz, mEntries(0).mSystem, -1, 0);
        if (hit > 0)
            *out *= sead::Mathf::clamp((normal.y - 0.62f) * 10.0f, 0.0f, 1.0f);
    }
    return result;
}

// 0x71011521c0 (placeholder name): the plain terrain height of `xz`; returns 2 when the grass is
// disabled and 0 without terrain data.
u32 Core::Grass::sub_71011521C0(f32* out, const sead::Vector2f* xz) {
    System* system = mEntries(0).mSystem;
    if (!system)
        return 0;

    if (mFlags & 0x4000) {
        *out = 0.0f;
        return 2;
    }

    const sead::Vector2f position(xz->x, xz->y);
    return sub_7101109BD8(out, &position, system, true);
}

// NON_MATCHING: the original has a dmb ish after the lock (an atomic read of the manager); ours reads
// the flags directly.
void Terrain::resumeImageResourceMgrMaybe() {
    if (!mImageResourceMgr || (_a58 & 0x10000) == 0)
        return;
    auto& lock = mImageResourceMgr->mCS28;
    lock.lock();
    if ((_a58 & 0x20000) != 0 && _360)
        _360->sub_7101301068(true);
    mImageResourceMgr->_6473 |= 4;
    mImageResourceMgr->sub_71011315BC();
    _a58 &= ~0x30000u;
    lock.unlock();
}

}  // namespace ksys::tera
