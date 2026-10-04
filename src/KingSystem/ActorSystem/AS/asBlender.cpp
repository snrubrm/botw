#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

namespace ksys::as {

Blender::Blender() {}

bool Blender::m10(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const f32 weight = state->weight;
    state->weight = weight * (1 - record->_4);
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    bool result = child->m10(ctx, state, child_resource);
    if (record->_1 != 0xff) {
        state->weight = weight * record->_4;
        Element* child2 = mChildren[static_cast<s8>(record->_1)];
        const res::ASResource* child2_resource =
            sub_71013031FC(resource, static_cast<s8>(record->_1));
        result &= child2->m10(ctx, state, child2_resource);
    }
    state->weight = weight;
    return result;
}

void Blender::m11(Context* ctx, EventState* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->sub_710116554C(ctx, state, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->sub_710116554C(ctx, state, child2_resource);
}

void Blender::m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m15(ctx, state, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m15(ctx, state, child2_resource);
}

void Blender::m16(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m19(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m20(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m21(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m22(Context* ctx, const res::ASResource* resource) {}

// NON_MATCHING: the compiler shares the first-child call and status update blocks.
void Blender::sub_7101316BC0(Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const auto* blender_resource = sead::DynamicCast<const res::ASBlenderResource>(resource);
    record->_2 = 0;
    const s8 second = record->_1;
    const s8 first = record->_0;
    if (second != -1) {
        Element* child = mChildren[first];
        const res::ASResource* child_resource = sub_71013031FC(resource, first);
        const f32 first_value = child->m26(ctx, child_resource);
        Element* child2 = mChildren[second];
        const res::ASResource* child2_resource = sub_71013031FC(resource, second);
        const f32 second_value = child2->m26(ctx, child2_resource);
        if (blender_resource && blender_resource->getTypeIndex() == 5) {
            record->_8 = first_value;
            if (second_value < 0.0f)
                record->_2 = 3;
        } else if (second_value <= 0.0f) {
            record->_8 = first_value;
            if (second_value < 0.0f) {
                record->_4 = 0.0f;
                record->_2 = 1;
            }
        } else if (first_value <= 0.0f) {
            record->_8 = second_value;
            if (first_value < 0.0f) {
                record->_4 = 1.0f;
                record->_2 = 2;
            }
        } else {
            record->_8 = second_value * record->_4 + first_value * (1.0f - record->_4);
        }
    } else {
        Element* child = mChildren[first];
        const res::ASResource* child_resource = sub_71013031FC(resource, first);
        record->_8 = child->m26(ctx, child_resource);
    }
}

f32 Blender::m26(Context* ctx, const res::ASResource* resource) {
    return ctx->sub_7101258CD4(sub_71011653E8(resource))->_8;
}

bool Blender::m27(Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    if (!child->m27(ctx, child_resource))
        return false;
    const s8 second = record->_1;
    if (second == -1)
        return true;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    return child2->m27(ctx, child2_resource);
}

void Blender::m28(f32* a1, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m28(a1, ctx, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m28(a1, ctx, child2_resource);
}

void Blender::m29(f32* a1, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m29(a1, ctx, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m29(a1, ctx, child2_resource);
}

int Blender::m30(f32* a1, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    int result = child->m30(a1, ctx, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return result;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    const int value = child2->m30(a1, ctx, child2_resource);
    if (value >= 0)
        result = value;
    return result;
}

int Blender::m31(Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    const int result = child->m31(ctx, child_resource);
    if (result >= 0)
        return result;
    const s8 second = record->_1;
    if (second == -1)
        return result;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    return child2->m31(ctx, child2_resource);
}

void Blender::m35(Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const s8 first = record->_0;
    if (first >= 0) {
        Element* child = mChildren[first];
        const res::ASResource* child_resource = sub_71013031FC(resource, first);
        child->sub_7101165E60(ctx, child_resource);
    }
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->sub_7101165E60(ctx, child2_resource);
}

void Blender::m36(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name,
                  const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const s8 first = record->_0;
    Element* child = mChildren[first];
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    child->sub_7101165EBC(ctx, out, name, first, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->sub_7101165EBC(ctx, out, name, second, child2_resource);
}

// NON_MATCHING: callee-saved register numbers / argument copy order at entry (the original copies the integer
// arguments before the float ones; see SelectorBase::m17)
void Blender::m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5, f32 a6) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m17(ctx, a2 & 1, a3 & 1, child_resource, a5, a6);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m17(ctx, a2 & 1, a3 & 1, child2_resource, a5, a6);
}

// NON_MATCHING: judge-once load and flag updates are scheduled differently; record branch order differs.
void Blender::m12(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    auto* blender_resource = sead::DynamicCast<const res::ASBlenderResource>(resource);
    if (!blender_resource)
        return;
    auto* sync_resource = sead::DynamicCast<const res::ASBlenderResource>(resource);
    bool no_sync;
    if (!sync_resource)
        no_sync = false;
    else if (!sync_resource->getNoSync())
        no_sync = sync_resource->getTypeIndex() == 5;
    else
        no_sync = true;
    if (!(ctx->mFlags & 1))
        ctx->mFlags |= 1;
    bool changed = false;
    if (!blender_resource->getJudgeOnce()) {
        const int key = sub_7101165408(resource);
        ctx->sub_710125A248(m38(ctx, resource), key, this, resource);
        if (!(ctx->mFlags & 2)) {
            s32 first, second;
            record->_4 = m39(&first, &second, ctx, resource);
            if (first == record->_0 && second == static_cast<s8>(record->_1)) {
                if (record->_2 == 2)
                    record->_4 = 1.0f;
                else if (record->_2 == 1)
                    record->_4 = 0.0f;
            } else {
                ctx->mFlags |= 2;
                f32 progress = 0.0f;
                if (!no_sync && record->_0 >= 0) {
                    Element* child = mChildren[record->_0];
                    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
                    if (const ElementParams* params = child->m25(ctx, child_resource))
                        progress = params->sub_710130298C(true);
                }
                m35(ctx, resource);
                record->_0 = first;
                record->_1 = second;
                PlayState play_state;
                play_state._0 = progress;
                play_state._4 = !no_sync;
                play_state._8 = ctx->sub_7101258D1C(sub_71011653E8(resource)) + 1;
                sub_71013166C4(record, ctx, &play_state, resource);
                if (no_sync)
                    ctx->_e8 = -1.0f;
                ctx->mFlags |= 4;
                changed = true;
            }
        }
    }
    const f32 weight = state->weight;
    state->weight = weight * (1.0f - record->_4);
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m12(ctx, state, child_resource);
    if (record->_1 != 0xff) {
        state->weight = weight * record->_4;
        Element* second_child = mChildren[static_cast<s8>(record->_1)];
        const res::ASResource* second_resource =
            sub_71013031FC(resource, static_cast<s8>(record->_1));
        second_child->m12(ctx, state, second_resource);
    }
    state->weight = weight;
    sub_7101316BC0(ctx, resource);
    if (changed)
        ctx->mFlags &= ~2u;
}

void Blender::m13(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    auto* blender_resource = sead::DynamicCast<const res::ASBlenderResource>(resource);
    bool has_value;
    if (!blender_resource)
        has_value = false;
    else if (!blender_resource->getNoSync())
        has_value = blender_resource->getTypeIndex() == 5;
    else
        has_value = true;
    const s8 first = record->_0;
    const u32 flags = ctx->mFlags;
    const bool reset = flags & 1;
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    if (reset) {
        ctx->mFlags &= ~1u;
        if (has_value)
            state->_30 = mChildren[first]->m26(ctx, child_resource);
        else
            state->_30 = record->_8;
    }
    mChildren[first]->m13(ctx, state, child_resource);
    const s8 second = record->_1;
    if (second != -1) {
        const res::ASResource* child2_resource = sub_71013031FC(resource, second);
        if (has_value && reset)
            state->_30 = mChildren[second]->m26(ctx, child2_resource);
        mChildren[second]->m13(ctx, state, child2_resource);
    }
    if (reset)
        state->_30 = -1.0f;
}

// NON_MATCHING: same child-index sign extension difference as m34
void Blender::m14(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const int first = record->_0;
    if (record->_1 == 0xff) {
        Element* child = mChildren[first];
        const res::ASResource* child_resource = sub_71013031FC(resource, first);
        child->sub_71011654E0(ctx, a2, a3, child_resource);
        return;
    }
    auto* state = static_cast<State*>(a2);
    const f32 weight = state->weight;
    state->weight = weight * (1 - record->_4);
    Element* child = mChildren[first];
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    child->sub_71011654E0(ctx, a2, a3, child_resource);
    const s8 second = record->_1;
    state->weight = weight * record->_4;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->sub_71011654E0(ctx, a2, a3, child2_resource);
    state->weight = weight;
}

// NON_MATCHING: the original folds the sign extension of the child index into the addressing mode in the
// two-child path (`w2, sxtw #3`) and keeps a separate `sxtw` in the single-child path; ours is the other way round
void Blender::m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const int first = record->_0;
    if (record->_1 == 0xff) {
        Element* child = mChildren[first];
        const res::ASResource* child_resource = sub_71013031FC(resource, first);
        child->m34(a1, ctx, a3, child_resource);
        return;
    }
    auto* state = static_cast<State*>(a3);
    const f32 weight = state->weight;
    state->weight = weight * (1 - record->_4);
    Element* child = mChildren[first];
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    child->m34(a1, ctx, a3, child_resource);
    const s8 second = record->_1;
    state->weight = weight * record->_4;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m34(a1, ctx, a3, child2_resource);
    state->weight = weight;
}

bool Blender::sub_71013166C4(Context::Record* record, Context* ctx, PlayState* state,
                             const res::ASResource* resource) {
    Element* first = mChildren[record->_0];
    if (!first->sub_710116541C(ctx, state, sub_71013031FC(resource, record->_0))) {
        record->_2 = 2;
        record->_4 = 1.0f;
    }
    const s8 second = record->_1;
    if (second == -1) {
        if (record->_2 == 2) {
            record->_4 = 0.0f;
            record->_2 = 0;
            return false;
        }
        return true;
    }
    Element* second_child = mChildren[second];
    if (!second_child->sub_710116541C(ctx, state, sub_71013031FC(resource, second))) {
        record->_4 = 0.0f;
        record->_2 = 1;
    }
    return true;
}

bool Blender::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    auto* blender_resource = sead::DynamicCast<const res::ASBlenderResource>(resource);
    const int key = sub_7101165408(resource);
    ctx->sub_710125A1F0(m38(ctx, resource), key, this, blender_resource);
    s32 first, second;
    record->_4 = m39(&first, &second, ctx, resource);
    const s8 old_second = record->_1;
    if (record->_0 >= 0 && (record->_0 != first || (old_second != -1 && old_second != second)))
        m35(ctx, resource);
    record->_0 = first;
    record->_1 = second;
    record->_2 = 0;
    return sub_71013166C4(record, ctx, state, blender_resource);
}

// NON_MATCHING: only the order of two register copies (`mov w23, w2` before `mov v8, v0` at entry; the two
// `orr` of the changed path swapped)
// NON_MATCHING: callee-saved register numbers / argument copy order at entry (the float is copied after the
// integer arguments in the original); the body is identical
bool Blender::m32(Context* ctx, void* a2, void* a3, void* a4, void* a5, const res::ASResource* resource,
                  f32 value) {
    s32 first, second;
    const f32 weight = m39(&first, &second, ctx, resource);
    Element* child = mChildren[first];
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    bool result = child->m32(ctx, a2, a3, a4, a5, child_resource, value);
    if (second != -1) {
        sead::Matrix34f other;
        Element* second_child = mChildren[second];
        const res::ASResource* second_resource = sub_71013031FC(resource, second);
        const bool second_result =
            second_child->m32(ctx, &other, a3, a4, a5, second_resource, value);
        auto* out = static_cast<sead::Matrix34f*>(a2);
        if (result & second_result) {
            sub_71011658C0(weight, out, out, &other);
        } else {
            if (!second_result)
                return result;
            *out = other;
        }
        result = true;
    }
    return result;
}

// NON_MATCHING: callee-saved register numbers / argument copy order at entry (see m32); the body is identical
bool Blender::m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource, f32 a5) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const u8 second = record->_1;
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    bool result = child->m33(ctx, a2, a3, child_resource, a5);
    if (second != 0xff) {
        sead::Matrix34f other;
        Element* second_child = mChildren[static_cast<s8>(record->_1)];
        const res::ASResource* second_resource = sub_71013031FC(resource, static_cast<s8>(record->_1));
        const bool second_result = second_child->m33(ctx, &other, a3, second_resource, a5);
        auto* out = static_cast<sead::Matrix34f*>(a2);
        if (result & second_result) {
            sub_71011658C0(record->_4, out, out, &other);
        } else {
            if (!second_result)
                return result;
            *out = other;
        }
        result = true;
    }
    return result;
}

f32 Blender::m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const int key = sub_7101165408(resource);
    ctx->sub_710125A1A4(m38(ctx, resource), key);
    s32 first, second;
    f32 weight = m39(&first, &second, ctx, resource);
    record->_4 = weight;
    bool changed;
    if (record->_0 == first && static_cast<s8>(record->_1) == second) {
        changed = false;
    } else {
        m35(ctx, resource);
        record->_0 = first;
        record->_1 = second;
        auto* blender_resource = sead::DynamicCast<const res::ASBlenderResource>(resource);
        bool flag;
        if (!blender_resource)
            flag = true;
        else if (!blender_resource->getNoSync())
            flag = blender_resource->getTypeIndex() != 5;
        else
            flag = false;
        PlayState state;
        state._4 = flag;
        state._0 = -1.0f;
        state._8 = ctx->sub_7101258D1C(sub_71011653E8(resource)) + 1;
        sub_71013166C4(record, ctx, &state, resource);
        weight = record->_4;
        a2 = true;
        changed = true;
    }
    Element* child = mChildren[first];
    const f32 first_a4 = (1 - weight) * a4;
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    const f32 result = child->m18(ctx, a2 & 1, a3, first_a4, child_resource);
    if (result >= 0.0f)
        return result;
    if (second != -1) {
        const f32 second_a4 = record->_4 * a4;
        Element* child2 = mChildren[second];
        const res::ASResource* child2_resource = sub_71013031FC(resource, second);
        child2->m18(ctx, a2 & 1, a3, second_a4, child2_resource);
    }
    if (changed) {
        ctx->mFlags |= 4;
        if (sub_71011654D8())
            ctx->mFlags |= 0x40;
    }
    return -1.0f;
}

f32 Blender::m39(s32* first, s32* second, Context* ctx, const res::ASResource* resource) {
    *first = 0;
    *second = -1;
    auto* parser = sead::DynamicCast<const res::ASRangesParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::Ranges));
    if (parser) {
        const f32 value = ctx->sub_710125A164(sub_7101165408(resource));
        const auto& ranges = parser->getRanges();
        for (u32 i = 0; i < ranges.size(); ++i) {
            if (*ranges[i].start <= value && value < *ranges[i].end) {
                f32 weight = 0.0f;
                if (i < ranges.size() - 1u) {
                    const u32 next = i + 1;
                    if (*ranges[next].start <= value && value < *ranges[next].end) {
                        const f32 lo = sead::Mathf::max(*ranges[i].start, *ranges[next].start);
                        const f32 hi = sead::Mathf::min(*ranges[i].end, *ranges[next].end);
                        if (hi - lo <= 0.0f) {
                            *first = next;
                            return 0.0f;
                        }
                        weight = (value - lo) / (hi - lo);
                        if (weight < 0.01f)
                            weight = 0.0f;
                        else if (0.99f < weight)
                            weight = 1.0f;
                        *second = next;
                    }
                }
                *first = i;
                return weight;
            }
        }
        if (*ranges.front().start > value)
            return 0.0f;
        *first = mChildren.size() - 1;
    }
    return 0.0f;
}

f32 Blender::m38(Context* ctx, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    return list->sub_710115EC98(sub_7101165408(resource), nullptr, 0);
}

}  // namespace ksys::as
