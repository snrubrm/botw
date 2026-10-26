#include "Game/gameGraphics.h"
#include <g3d/aglNW4FToNN.h>
#include <g3d/aglTextureDataInitializerG3D.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <nn/g3d/ModelObj.h>
#include <nn/g3d/ResFile.h>
#include <nn/g3d/ResMaterial.h>
#include <nn/g3d/ResModel.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadDelegate.h>
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

// GrudgeRenderer's TU (0x710128d348 .. 0x71012915b8).

namespace {
// The TU's model-name table (0x710265f830). Only the two names 0x710128f88c tests are modelled.
struct GrudgeNames {
    u8 _0[0x58];
    sead::SafeString mGrudgeModelName;     // "MergedGanonGrudgeSolid"
    sead::SafeString mGrudgeMaterialName;  // "MasterMaterial"
};
GrudgeNames sUnk_710265f830 = {{}, "MergedGanonGrudgeSolid", "MasterMaterial"};
}  // namespace

// 0x710128f88c: whether `unit` is a grudge model whose material `material` is Mt_Grudge.
bool GrudgeRenderer::sub_710128F88C(gsys::ModelUnit* unit, s32 material) {
    if (!unit)
        return false;
    if (unit->getName().findIndex(sUnk_710265f830.mGrudgeModelName) == -1 &&
        unit->getName().findIndex(sUnk_710265f830.mGrudgeMaterialName) == -1)
        return false;
    const sead::SafeString name = unit->getMaterialName(material);
    return name == "Mt_Grudge";
}

bool sub_7101290034(const sead::Vector3f& start, const sead::Vector3f& displacement, sead::Vector3f* hit_pos) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.setGroundHit(ksys::phys::GroundHit::Grudge);
    query.setStartAndDisplacement(start, displacement);
    bool hit = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(hit_pos);
        hit = true;
    }
    return hit;
}

// 0x710128f4bc
void GrudgeRenderer::sub_710128F4BC(const sead::Camera* camera) {
    if ((_2ef8 & 1) == 0)
        return;
    camera->getWorldPosByMatrix(&_240);
    _264 = cGrudgeResetDistance;
    _268->requestDraw();
}

template class sead::Delegate1<GrudgeRenderer, ksys::res::TextureHandleList::Entry*>;

// 0x710128f9a4: sorts the grudge unit arrays by address (the compare callback of their sort).
s32 sub_710128F9A4(const void* a, const void* b) {
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

// 0x710128f41c: copies the view frustum of the render context and derives the grudge draw
// distances from its near plane and field of view.
// NON_MATCHING: constant-pool scheduling only: the original keeps the 1.01 multiply after the
// factor computation; ours hoists it (the four literals sit in different rodata pages).
void GrudgeRenderer::sub_710128F41C(const gsys::ModelRenderContext* context, f32 fov) {
    mFrustum = context->getViewData()->frustum;

    const f32 cos_atan =
        sead::Mathf::cos(sead::Mathf::atan(mFrustum.get_f4() * mFrustum.getAspect()));
    const f32 scale = mFrustum.getNear() / sead::Mathf::max(cos_atan, 0.0001f);

    const f32 factor = fov + 1.0f;
    _258 = factor * 200.0f;
    const f32 value = scale * 1.01f;
    _24c = value;
    _250 = value;
    _254 = value;
    _25c = factor * 60.0f;
}

// 0x710128d550: marks the renderer entry or the render record of a finished texture bind.
void GrudgeRenderer::sub_710128D550(ksys::res::TextureHandleList::Entry* entry) {
    const auto* result = static_cast<const TextureBindResult*>(entry->sub_71012BD4D8());
    const s32 table_index = result->mTableIndex;
    const s32 entry_index = result->mEntryIndex;
    const BindKind kind = result->mKind;
    switch (kind) {
    case BindKind::TextureSet: {
        TextureSet* set = _ed0[table_index];
        if (!set || (set->mFlags & 1) == 0)
            return;
        set->mFlags |= (1 << (entry_index + 3)) | 2;
        break;
    }
    case BindKind::Entry:
        mEntries[entry_index].mFlag |= 1;
        break;
    }
}

// 0x710128f2a4: refreshes the material entries that were marked for a texture rebind.
void GrudgeRenderer::sub_710128F2A4() {
    if ((_2ef8 & 1) == 0)
        return;

    for (s32 i = 0; i < 3; ++i) {
        Entry& entry = mEntries[i];
        if ((entry.mFlag & 1) != 0) {
            nn::g3d::ResMaterial* material =
                &_280->getResFile()->mModels->mMaterials[entry.mMaterialIndex];
            nn::gfx::ResTexture* texture =
                agl::g3d::ResMaterial::GetTexture(material, entry.mTextureIndex);
            agl::g3d::TextureDataInitializerG3D::initialize(&entry.mTextureData, *texture);
            entry.mSampler.applyTextureData(entry.mTextureData);

            const nn::g3d::ResMaterial::TextureRecord& record =
                material->mTextureRecords[entry.mTextureIndex];
            entry.mSampler.setLOD(record._8, record._c, record._10);
            entry.mFlag &= ~1;
        }

        mUnitArrays[i].clear();

        _288->enableRenderViewOption(i, static_cast<gsys::ModelEnum::RenderViewOption>(4), false,
                                     -1);
        // Hide the entry's material and mark it as changed (the render-option bit 15 and the
        // material change flag).
        gsys::ModelUnit* unit = _288;
        unit->getMaterialInfo()[i].renderOptions &= ~0x8000;
        unit->getFlags().set(gsys::ModelUnit::Flag::Changed);
        unit->getMaterialInfo()[i].flags.setBit(1);
    }

    _260 = 1 - _260;
}

// 0x710128f698: binds the textures of the three texture records of `set` on `model`.
void GrudgeRenderer::sub_710128F698(gsys::ModelNW* model, TextureSet* set) {
    if (set->mMaterialIndex == -1)
        return;

    nn::g3d::MaterialObj* material = model->getModelObj()->GetMaterial(set->mMaterialIndex);
    for (s32 i = 0; i < 3; ++i) {
        const u32 mask = 1u << (i + 3);
        if (!sead::BitFlag8(set->mFlags).isOnBit(i + 3))
            continue;

        TextureSet::TextureEntry& entry = set->mEntries[i];
        const s32 texture_index = entry.mTextureIndex;
        if (texture_index != -1) {
            nn::gfx::ResTexture* texture =
                agl::g3d::MaterialObj::GetResTexture(material, texture_index);
            agl::g3d::TextureDataInitializerG3D::initialize(&entry.mTextureData, *texture);
            entry.mSampler.applyTextureData(entry.mTextureData);

            const nn::g3d::ResMaterial::TextureRecord& record =
                material->GetResource()->mTextureRecords[texture_index];
            entry.mSampler.setLOD(record._8, record._c, record._10);
        }

        _2ef8 &= ~mask;
    }
}

// 0x710128f888: the final-image pass calls this debug draw of the renderer; the original body is empty.
void GrudgeRenderer::sub_710128F888(agl::DrawContext* context,
                                    gsys::ModelRenderContext* render_context) {}

// NON_MATCHING: the original keeps the unit count in a register across the loop; ours rematerialises
// the load for the latch (register pressure from the loop-invariant compare string). One extra
// load and a `b.lt` instead of `b.ne`.
// 0x710128fcb8
// NON_MATCHING: only the position of the _108 store and the constant used for the
// -1.0 / max float pair differ (scheduling and constant materialisation).
Unk_71025191c8::Unk_71025191c8() {
    _108 = 0;
}

// 0x710128fedc: declares and creates the unit's uniform block, names the unit and copies
// its parameters.
void Unk_71025191c8::sub_710128FEDC(const CreateArg& arg) {
    sead::Heap* const heap = arg.mHeap;
    mUniformBlock.startDeclare(3, heap);
    mUniformBlock.declare_(agl::UniformBlock::cType_6, 4, 0, 1);
    mUniformBlock.declare_(agl::UniformBlock::cType_6, 3, 0, 1);
    mUniformBlock.declare_(agl::UniformBlock::cType_6, 1, 0, 1);
    mUniformBlock.create(heap, 2, 1);
    mUniformBlock.setBufferIndexMaybe(0);

    _120 = 8;
    _120 = arg._1c ? 0x28 : _120;
    mName.appendWithFormat("%u", arg._14);

    _10c = arg._10;
    _110 = arg._14;
    _114 = arg._18;
    _118 = arg._20;
    _11c = arg._24;

    if (arg._1c)
        _120 |= 5;
}

// 0x710128fd48: destroys the unit's uniform block and, when it owns one, its GPU buffer.
Unk_71025191c8::~Unk_71025191c8() {
    mUniformBlock.destroy();
    if (_120 & 0x100)
        sub_710128FD94();
}

// 0x7101290010: scales the unit's stored sizes by the reciprocal of `n`.
void Unk_71025191c8::sub_7101290010(s32 n) {
    const f32 scale = 1.0f / f32(n);
    _100 = scale;
    _104 = scale * f32(_11c);
}

// 0x710128f9e0: marks the renderer when the model has the GrudgeSlimeMold unit.
void GrudgeRenderer::sub_710128F9E0(gsys::Model* model) {
    if (!model)
        return;
    const auto& units = model->getUnits();
    for (s32 i = 0; i < units.size(); ++i) {
        gsys::ModelInfo* info = units[i];
        gsys::ModelUnit* unit = info->mModelUnit;
        if (!sead::IsDerivedFrom<gsys::ModelUnit>(unit))
            continue;
        const sead::SafeString name = unit->getName();
        if (name == "GrudgeSlimeMold")
            _2ef8 |= 4;
    }
}
