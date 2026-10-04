#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

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

bool AnmAsset::m10(Context* ctx, State* state, const res::ASResource* resource) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    if (!(ctx->_920 & 8)) {
        params->sub_7101302764(state->_0);
    } else {
        const f32 saved = params->_8;
        params->sub_7101302764(state->_0);
        params->_8 = saved;
        params->sub_7101302940(nullptr);
    }
    return params->sub_7101302834();
}

bool AnmAsset::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    const int index = sub_71011653E8(resource);
    ctx->sub_7101258D68(index);
    ctx->sub_7101258CD4(index)->_2 = -1;
    sub_7101314BCC(state->_0, ctx, state->_4, resource);
    if (_c == 0.0f) {
        if (resource) {
            auto* parser = sead::DynamicCast<const res::ASFrameCtrlParser>(
                resource->getExtensions().getParser(res::ASParamParser::Type::FrameCtrl));
            if (parser && !(parser->getEndFrame() <= 0.0f))
                return true;
        }
        return false;
    }
    return true;
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

// NON_MATCHING: argument move scheduling and the final conditional offset branch polarity.
void AnmAsset::m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 from,
                   f32 to) {
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    if ((params->_0 & 2) && !(params->_1c >= 0.0f)) {
        if (from < 0.0f)
            from = f32(int(-from)) + 1.0f + from;
        if (from > 1.0f)
            from -= int(from);
        if (to < 0.0f)
            to = f32(int(-to)) + 1.0f + to;
        if (to > 1.0f)
            to -= int(to);
    }
    params->sub_7101302A1C(params->sub_71013029E4(a3 & 1, from));
    const f32 position = params->sub_71013029E4(a3 & 1, to);
    params->_8 = position - ((a2 & 1) ? params->_c : 0.0f);
    params->sub_7101302940(nullptr);
}

// NON_MATCHING: the two output locals occupy opposite stack slots.
f32 AnmAsset::m18(Context* ctx, bool restart, f32 time, f32 a4,
                  const res::ASResource* resource) {
    if (_c == 0.0f) {
        if (!resource)
            return time;
        auto* parser = sead::DynamicCast<const res::ASFrameCtrlParser>(
            resource->getExtensions().getParser(res::ASParamParser::Type::FrameCtrl));
        if (!parser || parser->getEndFrame() <= 0.0f)
            return time;
    }
    f32 start = 0.0f;
    s32 wraps = 0;
    ElementParams* params =
        ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
    return sub_7101315AD0(params, &start, &wraps, restart, resource, time);
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
