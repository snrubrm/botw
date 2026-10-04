#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

namespace ksys::as {

// Original out-of-line blend threshold getter (0x71013180b4), shared constant 0.01f.
f32 sub_71013180B4() {
    return 0.01f;
}

AngleBlender::AngleBlender() {}

// NON_MATCHING: circular range loops use different induction variables and bounds checks.
f32 AngleBlender::m39(s32* first, s32* second, Context* ctx,
                      const res::ASResource* resource) {
    *first = 0;
    *second = -1;
    auto* parser = sead::DynamicCast<const res::ASRangesParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::Ranges));
    if (!parser)
        return 0.0f;
    const f32 period = m41() - m40();
    f32 value = ctx->sub_710125A164(sub_7101165408(resource));
    if (value > m41())
        value -= period;
    else if (value < m40())
        value = period + value;
    if (!(value > m41()))
        m40();
    const auto& ranges = parser->getRanges();
    const s32 count = ranges.size();
    s32 start = 0;
    while (count + start - 1 >= 0 && *ranges[count + start - 1].end > m41())
        --start;
    for (s32 i = start; i < ranges.size(); ++i) {
        s32 index;
        f32 lo, hi;
        if (i < 0) {
            index = ranges.size() + i;
            lo = *ranges[index].start - period;
            hi = *ranges[index].end - period;
        } else {
            index = i;
            lo = *ranges[i].start;
            hi = *ranges[i].end;
        }
        if (!(lo <= value && value < hi))
            continue;
        const s32 next = i + 1;
        s32 next_index;
        f32 next_lo, next_hi;
        if (i < -1) {
            next_index = ranges.size() + next;
            next_lo = *ranges[next_index].start - period;
            next_hi = *ranges[next_index].end - period;
        } else {
            if (next >= ranges.size()) {
                *first = index;
                return 0.0f;
            }
            next_index = next;
            next_lo = *ranges[next].start;
            next_hi = *ranges[next].end;
        }
        f32 weight = 0.0f;
        if (next_lo <= value && value < next_hi) {
            const f32 lower = sead::Mathf::max(lo, next_lo);
            const f32 upper = sead::Mathf::min(hi, next_hi);
            if (upper - lower <= 0.0f) {
                *first = hi < next_hi ? next_index : index;
                return 0.0f;
            }
            weight = (value - lower) / (upper - lower);
            if (weight < sub_71013180B4())
                weight = 0.0f;
            else if (weight > 1.0f - sub_71013180B4())
                weight = 1.0f;
            *second = next_index;
        }
        *first = i;
        if (i < 0)
            *first += ranges.size();
        return weight;
    }
    if (*ranges.front().start > value)
        return 0.0f;
    *first = mChildren.size() - 1;
    return 0.0f;
}


f32 AngleBlender::m40() {
    return -180;
}

f32 AngleBlender::m41() {
    return 180;
}

}  // namespace ksys::as
