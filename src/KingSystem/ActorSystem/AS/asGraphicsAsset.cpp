#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

// The names the debug dump uses for the material animation types.
static const char* const sMaterialAnmTypeNames[] = {"fspb", "fclb", "ftsb", "ftpb", "fvbb",
                                                    "fvmb", "????"};

// NON_MATCHING: the two default key halfwords are stored in the opposite order.
GraphicsAsset::GraphicsAsset(const CreateArg& arg, s32 value, gsys::MaterialAnmType type)
    : AnmAsset(arg, value, nullptr), _14(type) {}



void GraphicsAsset::m5(act::Actor*, gsys::Model* model, const sead::SafeString& name,
                       sead::Heap*, const res::AS* as) {
    auto* animation = model->getAnimation();
    if (!animation) {
        mKey = {};
        return;
    }

    const res::ASResource* resource = nullptr;
    const sead::SafeString* animation_name = &name;
    if (as) {
        resource = as->getElementResources()[m6()];
        animation_name = &sead::DynamicCast<const res::ASAssetResource>(resource)->getFileName();
    }
    mKey = animation->searchMaterialAnmKey(_14, *animation_name);
    if (!mKey.isValid() || animation->getMaterialAnms().size() < 1)
        return;
    _c = animation->isMaterialAnmLooped(mKey);
    sub_710131586C(animation->sub_7100BFF158(mKey), resource);
}

bool GraphicsAsset::m10(Context* ctx, State* state, const res::ASResource* resource) {
    if (!mKey.isValid())
        return true;
    return AnmAsset::m10(ctx, state, resource);
}

// NON_MATCHING: the filename address is computed after the virtual duration call.
void GraphicsAsset::m14(Context* ctx, void* state, EventState*, const res::ASResource* resource) {
    if (!mKey.isValid())
        return;

    const auto* asset = sead::DynamicCast<const res::ASAssetResource>(resource);
    if (!asset || !static_cast<MotionState*>(state)->_34)
        return;

    auto* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const f32 frame = ctx->sub_7101258D4C(record, false)->_4;
    ctx->sub_710125930C(frame, m4(), asset->getFileName(), asset->getTypeIndex());
}

int GraphicsAsset::m31(Context* ctx, const res::ASResource* resource) {
    if (!mKey.isValid())
        return -1;
    return ctx->sub_7101258CD4(sub_71011653E8(resource))->_2;
}

// When no material animation slot is left, build the debug listing of the slots and the current
// animations. The result string is not used by the release build.
// NON_MATCHING: the original calls sead::Buffer<ASList::Unk1>::size() out of line (our model inlines
// it); the remaining residue is the frame size and the key word vs two halfword compares.
void GraphicsAsset::m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) {
    auto* animation = ctx->sub_7101258E2C()->getAnimation();
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    if (!animation || !mKey.isValid() || state->_18 != 0)
        return;
    if (state->_10) {
        if (state->_10->_48)
            return;
        if (!state->_10->_44[0])
            return;
    }

    const s32 num_anms = animation->getMaterialAnms().size();
    if (state->_0 < num_anms) {
        const s8 index = s8(state->_0++);
        record->_2 = index;
        const auto& anm = animation->getMaterialAnms()[index];
        const auto key = anm.getKey();
        const f32 frame = sub_7101315930(ctx, resource);
        if (key.index == mKey.index && key.type == mKey.type)
            animation->setMaterialAnmFrame(index, frame);
        else
            animation->setMaterialAnmByKey(index, mKey, frame);
        return;
    }

    record->_2 = -1;
    sead::FixedSafeString<0x800> msg;
    msg.format("");

    ASList* list = ctx->mList;
    const s32 num_slots = list->mSlots.size();
    for (s32 i = 0; i != num_slots; ++i) {
        ASList::Unk1& slot = list->mSlots[i];
        const s32 last = slot._20.size() - 1;
        for (s32 j = 0; j <= last; ++j) {
            // Empty in the release build; the emptiness tests stay because cstr() is virtual.
            sead::FixedSafeString<0x100> slot_name;
            sead::FixedSafeString<0x100> anm_name;
            if (!slot_name.isEmpty())
                msg.appendWithFormat("%s\n", slot_name.cstr());
            if (!anm_name.isEmpty())
                msg.appendWithFormat("%s\n", anm_name.cstr());

            const sead::SafeString* name = slot._20[j].sub_7101161CD8();
            msg.appendWithFormat("%d-%d:%s,\n", i, j, name->cstr());
        }
    }

    msg.appendWithFormat("セット中アニメ\n");
    for (s32 i = 0; i != num_anms; ++i) {
        msg.appendWithFormat("%s.%s\n", animation->getMaterialAnmSlotName(i).cstr(),
                             sMaterialAnmTypeNames[u32(animation->getMaterialAnms()[i]
                                                         .getKey()
                                                         .type)]);
    }
    msg.appendWithFormat("あぶれ %s.%s\n", animation->getMaterialAnmName(mKey).cstr(),
                         sMaterialAnmTypeNames[u32(_14)]);
}

}  // namespace ksys::as
