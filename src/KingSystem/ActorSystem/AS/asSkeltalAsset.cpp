#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/System/Patrol.h"
#include <nn/g3d/ResSkeletalAnim.h>
#include <gsys/gsysModelUnit.h>

namespace ksys::as {

SkeltalAsset::Unk18::~Unk18() {
    if (_24 && _28) {
        delete _28;
        _24 = false;
        _28 = nullptr;
    }
}

// NON_MATCHING: key validity checks and canonical resource access differ in scheduling.
const nn::g3d::ResBoneAnim* SkeltalAsset::sub_710125D3FC(Context* ctx,
                                                     const gsys::BoneAccessKey* key) {
    if (!key->isValid())
        return nullptr;
    auto* model = ctx->sub_7101258E2C();
    if (!model || !mKey.isValid())
        return nullptr;
    auto* current_model = ctx->sub_7101258E2C();
    if (!current_model)
        return nullptr;
    auto* animation = current_model->getAnimation();
    if (!animation)
        return nullptr;
    const auto& entry = animation->mSkeletalResources[mKey.index];
    const auto* resource = static_cast<const nn::g3d::ResSkeletalAnim*>(entry.resource->resource);
    if (!resource || resource->GetRotateMode() != 0x1000)
        return nullptr;
    const auto name = model->getUnits()[key->model_unit_index]->mModelUnit->getBoneName(key->bone_index);
    return sub_710115D55C(resource, name);
}

void SkeltalAsset::Unk18::sub_710125B118() {
    _8 = nullptr;
    _10 = nullptr;
}

// The animation-source tree of SkeltalAsset::m5 / m8 and ASList +0x168 / +0x178. The removal is the
// sead left-leaning red-black tree erase; nodes are heap-allocated and deleted by clear().
void Unk_710125af7c::clear() {
    if (!mRoot)
        return;
    SkeltalAsset::Unk18* node = startIterating(mRoot);
    while (node) {
        const Key key = node->mKey;
        mRoot = erase(mRoot, key);
        if (mRoot)
            mRoot->setColor(1);
        delete node;
        if (!mRoot)
            break;
        node = startIterating(mRoot);
    }
}

SkeltalAsset::Unk18* Unk_710125af7c::insert(SkeltalAsset::Unk18* root, SkeltalAsset::Unk18* node) {    if (!root) {
        node->setColor(0);
        node->_8 = nullptr;
        node->_10 = nullptr;
        return node;
    }

    const s32 cmp = node->mKey.index - root->mKey.index;
    if (cmp < 0) {
        root->_8 = insert(root->_8, node);
    } else if (cmp > 0) {
        root->_10 = insert(root->_10, node);
    } else if (root != node) {
        node->_10 = root->_10;
        node->_8 = root->_8;
        node->mColorAndPtr = root->mColorAndPtr;
        root->sub_710125B118();
        root = node;
    }

    if (isRed(root->_10) && !isRed(root->_8))
        root = rotateLeft(root);
    if (isRed(root->_8) && isRed(root->_8->_8))
        root = rotateRight(root);
    if (isRed(root->_8) && isRed(root->_10))
        flipColors(root);
    return root;
}

SkeltalAsset::Unk18* Unk_710125af7c::erase(SkeltalAsset::Unk18* root, const Key& key) {    if (compare(key, root->mKey) < 0) {
        if (!isRed(root->_8) && !isRed(root->_8->_8))
            root = moveRedLeft(root);
        root->_8 = erase(root->_8, key);
    } else {
        if (isRed(root->_8))
            root = rotateRight(root);
        if (compare(key, root->mKey) == 0 && !root->_10) {
            root->sub_710125B118();
            return nullptr;
        }
        if (!isRed(root->_10) && !isRed(root->_10->_8))
            root = moveRedRight(root);
        if (compare(key, root->mKey) == 0) {
            SkeltalAsset::Unk18* const min_node = findMin(root->_10);
            SkeltalAsset::Unk18* target = root->_10;
            if (root->_10)
                target = find(root->_10, min_node->mKey);
            target->_10 = eraseMin(root->_10);
            target->_8 = root->_8;
            target->mColorAndPtr = root->mColorAndPtr;
            root->sub_710125B118();
            root = target;
        } else {
            root->_10 = erase(root->_10, key);
        }
    }
    if (isRed(root->_10))
        root = rotateLeft(root);
    if (isRed(root->_8) && isRed(root->_8->_8))
        root = rotateRight(root);
    if (isRed(root->_8) && isRed(root->_10))
        flipColors(root);
    return root;
}

SkeltalAsset::Unk18* Unk_710125af7c::eraseMin(SkeltalAsset::Unk18* node) {
    if (!node->_8)
        return nullptr;
    if (!isRed(node->_8) && !isRed(node->_8->_8))
        node = moveRedLeft(node);
    node->_8 = eraseMin(node->_8);
    if (isRed(node->_10))
        node = rotateLeft(node);
    if (isRed(node->_8) && isRed(node->_8->_8))
        node = rotateRight(node);
    if (isRed(node->_8) && isRed(node->_10))
        flipColors(node);
    return node;
}

SkeltalAsset::Unk18* Unk_710125af7c::find(SkeltalAsset::Unk18* root, const Key& key) const {
    while (root) {
        const s32 cmp = compare(key, root->mKey);
        if (cmp < 0)
            root = root->_8;
        else if (cmp > 0)
            root = root->_10;
        else
            return root;
    }
    return nullptr;
}

// NON_MATCHING: the second key halfword uses the element pointer rather than the key pointer.
bool SkeltalAsset::m8(const InitArg& arg) {
    const CreateArg& create_arg = *arg.createArg;
    if (create_arg.model && mKey.isValid() && create_arg.model->getAnimation())
        if (!create_arg.partialSkeletalSources->sub_710125AF7C(
                &_18, &mKey, create_arg.model, create_arg.actor, create_arg.heap))
            return false;
    return true;
}


bool SkeltalAsset::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    const int index = sub_71011653E8(resource);
    ctx->sub_7101258D68(index);
    ctx->sub_7101258CD4(index)->_2 = -1;
    if (sub_7101314BCC(state->_0, ctx, state->_4, resource))
        ctx->mFlags |= 0x400;
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    ElementParams* params = ctx->sub_7101258D4C(record, false);
    const f32 duration = params->sub_710130296C(true);
    record->_8 = duration > 0.0f ? params->_c / duration : 0.0f;
    return true;
}

// NON_MATCHING: the original stores the two halfwords of the default key (0x12 then 0x10) in the other order.
SkeltalAsset::SkeltalAsset(const CreateArg& arg, s32 value)
    : AnmAsset(arg, value, nullptr), _18(nullptr) {}

SkeltalAsset::~SkeltalAsset() {}

// NON_MATCHING: key initialization order and typed key checks differ in scheduling.
SkeltalAsset::SkeltalAsset(const CreateArg& arg, s32 value, const res::ASResource* resource)
    : AnmAsset(arg, value, resource), _18(nullptr) {
    if (arg._28)
        return;
    const auto* asset = sead::DynamicCast<const res::ASSkeltalAssetResource>(resource);
    if (arg.model) {
        if (auto* animation = arg.model->getAnimation()) {
            if (animation->mSkeletalAnms.size() != 0) {
                mKey = animation->searchSkeletalKey(asset->getFileName());
                if (!mKey.isValid()) {
                    if (auto* patrol = Patrol::instance()) {
                        if (patrol->mField0)
                            asset->getFileName().findIndex("Demo");
                    }
                    return;
                }
                if (animation->mSkeletalResources[mKey.index].count != 0) {
                    _c = static_cast<const nn::g3d::ResSkeletalAnim*>(
                             animation->mSkeletalResources[mKey.index].resource->resource)
                             ->GetFrameCount();
                    sub_710131586C(static_cast<const nn::g3d::ResSkeletalAnim*>(
                                      animation->mSkeletalResources[mKey.index].resource->resource)
                                      ->IsLooped(),
                                  resource);
                    return;
                }
            }
        }
    }
    mKey = {};
}

// NON_MATCHING: the filename address is computed after the virtual duration call.
void SkeltalAsset::m14(Context* ctx, void* state, EventState*, const res::ASResource* resource) {
    if (!mKey.isValid())
        return;

    auto* motion = static_cast<MotionState*>(state);
    auto* initial_record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    initial_record->_4 = motion->weight;
    sub_710125CB88(ctx, motion, resource);

    const auto* asset = sead::DynamicCast<const res::ASSkeltalAssetResource>(resource);
    if (!asset || !motion->_34)
        return;

    auto* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const f32 frame = ctx->sub_7101258D4C(record, false)->_4;
    ctx->sub_7101259274(frame, m4(), motion->weight, asset->getFileName());
}

// NON_MATCHING: the second key-half load uses a different base register.
void SkeltalAsset::m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) {
    if (!ctx->sub_7101258E2C()->getAnimation() || !mKey.isValid())
        return;
    const bool partial = _18 ? _18->_25 : false;
    const f32 frame = sub_7101315930(ctx, resource);
    state->sub_7101257884(&mKey, ctx->sub_7101258CD4(sub_71011653E8(resource)), partial, frame);
    if (state->_10)
        state->_10->mFlags |= 0x10;
}

bool SkeltalAsset::m10(Context* ctx, State* state, const res::ASResource* resource) {
    if (!mKey.isValid())
        return true;
    const bool result = AnmAsset::m10(ctx, state, resource);
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    record->_4 = state->weight;
    return result;
}

void SkeltalAsset::m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) {
    ctx->sub_7101258CD4(sub_71011653E8(resource));
    auto* out = static_cast<sead::Vector3f*>(a1);
    const sead::Vector3f* vec = _18 ? _18->_28 : nullptr;
    *out += (vec == nullptr ? sead::Vector3f::ones : *vec) * static_cast<State*>(a3)->weight;
}

f32 SkeltalAsset::m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) {
    const f32 result = AnmAsset::m18(ctx, a2, a3, a4, resource);
    if (result < 0.0f) {
        ctx->sub_7101258CD4(sub_71011653E8(resource))->_4 = a4;
        Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
        ElementParams* params = ctx->sub_7101258D4C(record, false);
        const f32 duration = params->sub_710130296C(true);
        record->_8 = duration > 0.0f ? params->_c / duration : 0.0f;
    }
    return result;
}

void SkeltalAsset::m28(f32* a1, Context* ctx, const res::ASResource* resource) {
    if (auto* skeltal = sead::DynamicCast<const res::ASSkeltalAssetResource>(resource)) {
        *a1 = sead::Mathf::clampMin(*a1, 0.0f);
        *a1 += ctx->sub_7101258CD4(sub_71011653E8(resource))->_4 * skeltal->getMorph();
    }
}

void SkeltalAsset::m29(f32* a1, Context* ctx, const res::ASResource* resource) {
    if (auto* skeltal = sead::DynamicCast<const res::ASSkeltalAssetResource>(resource))
        *a1 += ctx->sub_7101258CD4(sub_71011653E8(resource))->_4 * skeltal->getResetMorph();
}

void SkeltalAsset::m12(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    record->_4 = state->weight;
}

void SkeltalAsset::m13(Context* ctx, State* state, const res::ASResource* resource) {
    AnmAsset::m13(ctx, state, resource);
    if (state->_30 > 0) {
        ElementParams* params =
            ctx->sub_7101258D4C(ctx->sub_7101258CD4(sub_71011653E8(resource)), false);
        const f32 weight = state->_30;
        params->_c = weight * params->sub_710130296C(true);
        params->sub_7101302948(nullptr);
    }
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
