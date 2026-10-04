#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

SkeltalAsset::~SkeltalAsset() {}

void SkeltalAsset::m12(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    record->_4 = state->weight;
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
