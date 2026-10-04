#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

f32 AnmAsset::m4() {
    return _c;
}

int AnmAsset::m6() {
    return _a;
}

int AnmAsset::m7() {
    return _a >= 0 ? _a : 1;
}

void AnmAsset::m13(Context* ctx, State* state, const res::ASResource* resource) {
    const f32 delta_time = ctx->_ec;
    if (delta_time > 0) {
        ElementParams* params =
            ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
        params->sub_7101302950(delta_time);
    }
}

void AnmAsset::m16(Context* ctx, const res::ASResource* resource, f32 value) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    params->sub_7101302A1C(value);
    params->_8 = params->_4 - params->_c;
    params->sub_7101302940(nullptr);
}

void AnmAsset::m19(Context* ctx, const res::ASResource* resource, f32 value) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    params->_c = value;
    params->sub_7101302948(nullptr);
}

void AnmAsset::m20(Context* ctx, const res::ASResource* resource, f32 value) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    params->_10 = value;
    params->sub_7101302930(nullptr);
}

void AnmAsset::m21(Context* ctx, const res::ASResource* resource, f32 value) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    params->_14 = value;
    params->sub_7101302938(nullptr);
}

void AnmAsset::m22(Context* ctx, const res::ASResource* resource) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    params->_0 &= ~2u;
}

const ElementParams* AnmAsset::m25(Context* ctx, const res::ASResource* resource) {
    return ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), true);
}

bool AnmAsset::m27(Context* ctx, const res::ASResource* resource) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), true);
    if (!(params->_0 & 2))
        return false;
    return !(params->_1c >= 0);
}

}  // namespace ksys::as
