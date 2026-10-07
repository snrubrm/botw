#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

namespace ksys::as {

AngleSelector::AngleSelector(const CreateArg&, s32, const res::ASResource*) {}

// NON_MATCHING: reverse-loop induction, Buffer fallback simplification and block layout differ.
int AngleSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    auto* parser = sead::DynamicCast<const res::ASRangesParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::Ranges));
    if (!parser || parser->getRanges().size() == 0)
        return -1;
    const f32 span = m42() - m41();
    f32 value = m40(ctx, a2 & 1, resource);
    if (value > m42())
        value -= span;
    else if (value < m41())
        value += span;
    if (!(value > m42()))
        m41();
    const auto& ranges = parser->getRanges();
    s32 first = 0;
    const s32 num_ranges = ranges.size();
    if (num_ranges - 1 >= 0 && *ranges[num_ranges - 1].end > m42()) {
        for (first = -1; num_ranges + first - 1 >= 0; --first) {
            if (!(*ranges[num_ranges + first - 1].end > m42()))
                break;
        }
    }
    const s32 count = ranges.size();
    for (s32 i = first; i < count; ++i) {
        s32 index;
        f32 start;
        f32 end;
        if (i < 0) {
            index = count + i;
            const auto& range = ranges[index];
            start = *range.start - span;
            end = *range.end - span;
        } else {
            index = i;
            const auto& range = ranges[index];
            start = *range.start;
            end = *range.end;
        }
        if (start <= value && value < end)
            return index;
        if (start == value && start == end)
            return index;
    }
    if (value == *ranges[count - 1].end)
        return count - 1;
    return -1;
}

f32 AngleSelector::m41() {
    return -180;
}

f32 AngleSelector::m42() {
    return 180;
}

}  // namespace ksys::as
