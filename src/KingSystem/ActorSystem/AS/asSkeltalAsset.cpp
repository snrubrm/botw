#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

bool SkeltalAsset::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    const int index = sub_71011653E8(resource);
    ctx->sub_7101258D68(index);
    ctx->sub_7101258CD4(index)->_2 = -1;
    if (sub_7101314BCC(state->_0, ctx, state->_4, resource))
        ctx->mFlags |= 0x400;
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    ElementParams* params = ctx->sub_7101258D4C(record, false);
    const f32 duration = params->sub_710130296C(true);
    record->_8 = duration > 0.0f ? params->_c / duration : 0.0f;
    return true;
}

// NON_MATCHING: the original stores the two halfwords of the default key (0x12 then 0x10) in the other order.
SkeltalAsset::SkeltalAsset(const CreateArg& arg, s32 value)
    : AnmAsset(arg, value, nullptr), _18(nullptr) {}

SkeltalAsset::~SkeltalAsset() {}

// NON_MATCHING: the filename address is computed after the virtual duration call.
void SkeltalAsset::m14(Context* ctx, void* state, EventState*, const res::ASResource* resource) {
    if (!mKey.isValid())
        return;

    auto* motion = static_cast<MotionState*>(state);
    auto* initial_record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    initial_record->_4 = motion->weight;
    sub_710125CB88(ctx, motion, resource);

    const auto* asset = sead::DynamicCast<const res::ASSkeltalAssetResource>(resource);
    if (!asset || !motion->_34)
        return;

    auto* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const f32 frame = ctx->sub_7101258D4C(record, false)->_4;
    ctx->sub_7101259274(frame, m4(), motion->weight, asset->getFileName());
}

// NON_MATCHING: the second key-half load uses a different base register.
void SkeltalAsset::m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) {
    if (!ctx->sub_7101258E2C()->getAnimation() || !mKey.isValid())
        return;
    const bool partial = _18 ? _18->_25 : false;
    const f32 frame = sub_7101315930(ctx, resource);
    state->sub_7101257884(&mKey, ctx->sub_7101258CD4(sub_71011653E8(resource)), partial, frame);
    if (state->_10)
        state->_10->mFlags |= 0x10;
}

bool SkeltalAsset::m10(Context* ctx, State* state, const res::ASResource* resource) {
    if (!mKey.isValid())
        return true;
    const bool result = AnmAsset::m10(ctx, state, resource);
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    record->_4 = state->weight;
    return result;
}

void SkeltalAsset::m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) {
    ctx->sub_7101258CD4(sub_71011653E8(resource));
    auto* out = static_cast<sead::Vector3f*>(a1);
    const sead::Vector3f* vec = _18 ? _18->_28 : nullptr;
    *out += (vec == nullptr ? sead::Vector3f::ones : *vec) * static_cast<State*>(a3)->weight;
}

f32 SkeltalAsset::m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) {
    const f32 result = AnmAsset::m18(ctx, a2, a3, a4, resource);
    if (result < 0.0f) {
        ctx->sub_7101258CD4(sub_71011653E8(resource))->_4 = a4;
        Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
        ElementParams* params = ctx->sub_7101258D4C(record, false);
        const f32 duration = params->sub_710130296C(true);
        record->_8 = duration > 0.0f ? params->_c / duration : 0.0f;
    }
    return result;
}

void SkeltalAsset::m28(f32* a1, Context* ctx, const res::ASResource* resource) {
    if (auto* skeltal = sead::DynamicCast<const res::ASSkeltalAssetResource>(resource)) {
        *a1 = sead::Mathf::clampMin(*a1, 0.0f);
        *a1 += ctx->sub_7101258CD4(sub_71011653E8(resource))->_4 * skeltal->getMorph();
    }
}

void SkeltalAsset::m29(f32* a1, Context* ctx, const res::ASResource* resource) {
    if (auto* skeltal = sead::DynamicCast<const res::ASSkeltalAssetResource>(resource))
        *a1 += ctx->sub_7101258CD4(sub_71011653E8(resource))->_4 * skeltal->getResetMorph();
}

void SkeltalAsset::m12(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    record->_4 = state->weight;
}

void SkeltalAsset::m13(Context* ctx, State* state, const res::ASResource* resource) {
    AnmAsset::m13(ctx, state, resource);
    if (state->_30 > 0) {
        ElementParams* params =
            ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
        const f32 weight = state->_30;
        params->_c = weight * params->sub_710130296C(true);
        params->sub_7101302948(nullptr);
    }
}

int SkeltalAsset::m30(f32* a1, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    if (record->_2 < 0)
        return -1;
    const f32 value = record->_4;
    if (value > *a1) {
        *a1 = value;
        return record->_2;
    }
    return -1;
}

}  // namespace ksys::as
