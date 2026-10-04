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

void AnmAsset::sub_7101315328(f32* position, f32* start, f32* end,
                           const res::ASResource* resource) {
    const res::ASFrameCtrlParser* parser = nullptr;
    if (resource) {
        parser = sead::DynamicCast<const res::ASFrameCtrlParser>(
            resource->getExtensions().getParser(res::ASParamParser::Type::FrameCtrl));
    }
    if (parser) {
        f32 first = parser->getStartFrame();
        if (!(first >= 0.0f))
            first = m4();
        *position = first;
        if (!_8) {
            *start = first;
            f32 last = parser->getEndFrame();
            if (!(last >= 0.0f))
                last = m4();
            *end = last;
            return;
        }
    } else {
        *position = 0.0f;
    }
    *start = 0.0f;
    *end = m4();
}

// NON_MATCHING: loop override branches appear in the opposite order.
void AnmAsset::sub_710131586C(bool loop, const res::ASResource* resource) {
    _9 = loop;
    _8 = loop;
    if (resource) {
        if (const auto* parser = sead::DynamicCast<const res::ASFrameCtrlParser>(
                resource->getExtensions().getParser(res::ASParamParser::Type::FrameCtrl))) {
            if (parser->getAnmLoop() == 2)
                _8 = true;
            else if (parser->getAnmLoop() == 1)
                _8 = false;
        }
    }
}

// NON_MATCHING: the compiler inlines the frame-range helper and reallocates its outputs.
f32 AnmAsset::sub_7101315AD0(ElementParams* params, f32* start, s32* wraps, bool restart,
                           const res::ASResource* resource, f32 time) {
    const res::ASFrameCtrlParser* parser = nullptr;
    if (resource) {
        parser = sead::DynamicCast<const res::ASFrameCtrlParser>(
            resource->getExtensions().getParser(res::ASParamParser::Type::FrameCtrl));
    }
    const bool loop = _8;
    f32 position;
    f32 first;
    f32 last;
    sub_7101315328(&position, &first, &last, resource);
    if (restart) {
        if (parser) {
            params->sub_71013028BC(loop, parser->getReversePlay(), position, parser->getRate(),
                                  first, last, parser->getLoopStopCount());
        } else {
            params->sub_71013028BC(loop, false, 0.0f, 1.0f, 0.0f, m4(), -1.0f);
        }
    }
    *start = parser ? first : 0.0f;
    *wraps = params->sub_7101302A70(time, *start);
    if ((params->_0 & 2) && !(params->_1c >= 0.0f))
        return -1.0f;
    if (params->_c <= 0.0f)
        return -1.0f;
    f32 end = params->_1c;
    const f32* begin = start;
    if (!(end >= 0.0f)) {
        end = params->_14;
        begin = &params->_10;
    }
    const f32 duration = (end - *begin) / params->_c;
    return duration > time ? -1.0f : time - duration;
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

// 0x710125a978: converts a resource event frame to playback space (start argument unused).
f32 sub_710125A978(f32 frame, f32 start, f32 end, bool hold);

// NON_MATCHING: duration fallback and event-loop registers are allocated differently.
int AnmAsset::m37(Context* ctx, EventState* state, const res::ASResource* resource) {
    if (ctx->_f4 != ctx->_f5 || !state->_1)
        return 0;
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    ElementParams* params = ctx->sub_7101258D4C(record, false);
    const f32 start = params->_10;
    const f32 end = params->_14;
    const f32 position = params->_4;
    const f32 weight = record->_4;
    const res::ASTriggerEventsParser* triggers = nullptr;
    const res::ASHoldEventsParser* holds = nullptr;
    if (resource) {
        triggers = sead::DynamicCast<const res::ASTriggerEventsParser>(
            resource->getExtensions().getParser(res::ASParamParser::Type::TriggerEvents));
        holds = sead::DynamicCast<const res::ASHoldEventsParser>(
            resource->getExtensions().getParser(res::ASParamParser::Type::HoldEvents));
    }
    const u8 flags = record->_3;
    record->_3 = flags & ~4u;
    if (triggers) {
        const auto& events = triggers->getEvents();
        for (u32 i = 0; i < events.size(); ++i) {
            const f32 frame = *events[i].frame;
            if (frame < -1.5f) {
                if (flags & 4)
                    ctx->sub_7101259DE8(weight, events[i].type_index, *events[i].value);
                continue;
            }
            const f32 event_position = sub_710125A978(frame, start, end, false);
            if (params->sub_7101302878(event_position)) {
                ctx->sub_7101259DE8(weight, events[i].type_index, *events[i].value);
                if (events[i].type_index == 0x3a) {
                    const f32 duration = params->sub_710130296C(false);
                    ctx->_e8 = duration > 0.0f ? event_position / duration : -1.0f;
                }
            }
        }
    }
    if (state->_0)
        return 1;
    if (holds) {
        const auto& events = holds->getEvents();
        for (u32 i = 0; i < events.size(); ++i) {
            const f32 event_start = sub_710125A978(*events[i].start_frame, start, end, true);
            const f32 event_end = sub_710125A978(*events[i].end_frame, start, end, true);
            if (event_start <= position && position < event_end)
                ctx->sub_7101259F94(event_end - position, weight, events[i].type_index,
                                     *events[i].value);
        }
    }
    return 3;
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
