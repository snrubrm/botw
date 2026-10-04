#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

SkeltalAsset::~SkeltalAsset() {}

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
