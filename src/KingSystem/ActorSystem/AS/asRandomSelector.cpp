#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

RandomSelector::RandomSelector() {}
PreExclusionRandomSelector::PreExclusionRandomSelector() {}

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

}  // namespace ksys::as
