#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

FloatSelector::FloatSelector() {}

f32 FloatSelector::m40(Context* ctx, u32 a2, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    return list->sub_710115EC98(sub_7101165408(resource), nullptr, 0);
}

// NON_MATCHING: callee-saved register numbers (the original keeps `this` in x23, the parser in x22)
int FloatSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    auto* parser = sead::DynamicCast<const res::ASRangesParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::Ranges));
    if (parser && parser->getRanges().size() != 0) {
        const f32 value = m40(ctx, a2 & 1, resource);
        const auto& ranges = parser->getRanges();
        for (u32 i = 0; i < ranges.size(); ++i) {
            const auto& range = ranges[i];
            if (*range.start <= value && value < *range.end)
                return i;
            if (*range.start == value && *range.start == *range.end)
                return i;
        }
        if (value == *ranges[ranges.size() - 1].end)
            return ranges.size() - 1;
    }
    return -1;
}

}  // namespace ksys::as
