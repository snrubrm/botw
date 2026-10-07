#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"

namespace ksys::as {

ClearMatAnmAsset::ClearMatAnmAsset(const CreateArg&, s32, const res::ASResource*) {}

bool ClearMatAnmAsset::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    if (ctx->sub_7101258E2C()) {
        const u64 user_data = Unk_710260af28::instance()->sub_7100F1CD88(ctx->sub_7101258E2C());
        const f32 attribute = Unk_710260af28::instance()->sub_7100F1CE68(ctx->sub_7101258E2C());
        ctx->sub_7101258E2C()->sub_7100BF8738();
        Unk_710260af28::instance()->sub_7100F1CC38(ctx->sub_7101258E2C(), user_data);
        Unk_710260af28::instance()->sub_7100F1CEF4(ctx->sub_7101258E2C(), attribute);
    }
    return true;
}

bool ClearMatAnmAsset::m10(Context* ctx, State* state, const res::ASResource* resource) {
    return false;
}

}  // namespace ksys::as
