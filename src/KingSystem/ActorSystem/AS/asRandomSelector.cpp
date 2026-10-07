#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

RandomSelector::RandomSelector(const CreateArg& arg, s32 value, const res::ASResource* resource)
    : FloatSelector() {}
PreExclusionRandomSelector::PreExclusionRandomSelector(const CreateArg& arg, s32 value,
                                                       const res::ASResource* resource)
    : RandomSelector(arg, value, resource) {}

f32 ASList::sub_710131D504() {
    return sead::GlobalRandom::instance()->getF32();
}

bool PreExclusionRandomSelector::m9(Context* ctx, PlayState* state,
                                    const res::ASResource* resource) {
    const bool result = Selector::m9(ctx, state, resource);
    const int index = sub_71011653E8(resource);
    ctx->sub_710125AAA0(index, ctx->sub_7101258CD4(index)->_0);
    return result;
}

void PreExclusionRandomSelector::m12(Context* ctx, State* state, const res::ASResource* resource) {
    Selector::m12(ctx, state, resource);
    const int index = sub_71011653E8(resource);
    ctx->sub_710125AAA0(index, ctx->sub_7101258CD4(index)->_0);
}

// NON_MATCHING: block layout (the original places the `a2 & 1` block directly after the test)
f32 RandomSelector::m40(Context* ctx, u32 a2, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    if (ctx->_921 & 2)
        return list->sub_710115EC98(0x1e, &ASList::sub_710131D504, 0);
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    if (!(a2 & 1))
        return record->_4;
    const f32 value = list->sub_710115EC98(0x1e, &ASList::sub_710131D504, 0);
    record->_4 = value;
    return value;
}

// NON_MATCHING: compiler lays out the cached/random branches and return block differently.
f32 PreExclusionRandomSelector::m40(Context* ctx, u32 a2,
                                   const res::ASResource* resource) {
    ASList* list = ctx->mList;
    f32 value;
    if (ctx->_921 & 2) {
        value = list->sub_710115EC98(0x1e, &ASList::sub_710131D504, 0);
        if (!(a2 & 1))
            return value;
    } else {
        Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
        if (!(a2 & 1))
            return record->_4;
        value = list->sub_710115EC98(0x1e, &ASList::sub_710131D504, 0);
        record->_4 = value;
    }
    if (ctx->_921 & 2)
        return value;
    const s32 previous = ctx->sub_710125AA38(sub_71011653E8(resource));
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    if (previous < 0)
        return value;
    auto* parser = sead::DynamicCast<const res::ASRangesParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::Ranges));
    if (!parser || u32(parser->getRanges().size()) < 2 ||
        u32(previous) >= u32(parser->getRanges().size())) {
        return value;
    }
    const auto& range = parser->getRanges()[previous];
    const f32 start = *range.start;
    const f32 length = *range.end - start;
    if (length > 0.0f) {
        value *= 1.0f - length;
        if (value >= start)
            value += length;
    } else if (value == start) {
        value = sead::GlobalRandom::instance()->getF32();
    }
    record->_4 = value;
    return value;
}

}  // namespace ksys::as
