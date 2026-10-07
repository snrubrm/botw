#include <gsys/gsysPartialSkeletalAnm.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <nn/g3d/SkeletonObj.h>
#include <cstring>

namespace gsys {

PartialSkeletalAnmBase::~PartialSkeletalAnmBase() {
    mFlags.freeBuffer();
}

void PartialSkeletalAnmBase::initialize(s32 count, sead::Heap* heap) {
    if (count > 0) {
        u8* flags = new (heap, 8, std::nothrow) u8[count]();
        if (flags)
            mFlags.setBuffer(count, flags);
    }
    initializeImpl_(count, heap);
}

// NON_MATCHING: all 131 instructions agree except the scheduling of the count copy.
void PartialSkeletalAnmBase::sub_7100BFF4CC(Model* model,
                                              sead::Buffer<BoneMask>* masks) const {
    for (s32 unit_idx = 0; unit_idx < model->getUnits().size(); ++unit_idx) {
        std::memset(masks->get(unit_idx), 0xff, sizeof(BoneMask));
        auto* model_unit = model->getUnits()(unit_idx)->mModelUnit;
        const auto* type_info = ModelNW::getRuntimeTypeInfoStatic();
        const auto* unit = model_unit->checkDerivedRuntimeTypeInfo(type_info) ?
                               static_cast<const ModelNW*>(model_unit) : nullptr;
        const u32 count = std::min<u32>(mCount, mFlags.size());
        if (count == 0)
            continue;
        const u8* flags = mFlags.getBufferPtr();
        const auto* skeleton = unit->getSkeletonObj();
        for (u32 i = 0; i != count; ++i) {
            const auto* key = getBoneAccessKeyImpl_(i);
            if (u32(unit_idx) != u32(key->model_unit_index))
                continue;
            const s32 first = key->bone_index;
            const s32 end = flags[i] & 0x80 ? skeleton->GetRes()->GetBranchEndIndex(first) :
                                            first + 1;
            for (s32 bone = first; bone < end; ++bone) {
                const bool disabled = (flags[i] & 2) != 0;
                BoneMask* mask = masks->get(unit_idx);
                if (disabled) {
                    if (u32(bone) < 1024)
                        mask->words[u32(bone) / 32] &= ~(1u << (u32(bone) % 32));
                } else {
                    if (u32(bone) < 1024)
                        mask->words[u32(bone) / 32] |= 1u << (u32(bone) % 32);
                }
            }
        }
    }
}

PartialSkeletalAnmEx::PartialSkeletalAnmEx() = default;

PartialSkeletalAnmEx::~PartialSkeletalAnmEx() {
    mBoneKeys.freeBuffer();
}

void PartialSkeletalAnmEx::initializeImpl_(s32 count, sead::Heap* heap) {
    mBoneKeys.tryAllocBuffer(count, heap);
}

// NON_MATCHING: same 30 instructions; boolean-result masking and registers differ.
bool PartialSkeletalAnmEx::sub_7100BFF8E4(const Model* model, const sead::SafeString& name,
                                           u8 flag) {
    const bool found = mBoneKeys[mCount].search(model, name);
    mFlags[mCount++] = flag & 0x7f;
    _a |= 1;
    return found;
}

// NON_MATCHING: same 30 instructions; boolean-result masking and registers differ.
bool PartialSkeletalAnmEx::sub_7100BFF95C(const Model* model, const sead::SafeString& name,
                                           u8 flag) {
    const bool found = mBoneKeys[mCount].search(model, name);
    mFlags[mCount++] = flag | 0x80;
    _a |= 1;
    return found;
}

BoneAccessKey* PartialSkeletalAnmEx::getBoneAccessKeyImpl_(s32 index) {
    return &mBoneKeys[index].getKey();
}

const BoneAccessKey* PartialSkeletalAnmEx::getBoneAccessKeyImpl_(s32 index) const {
    return &mBoneKeys[index].getKey();
}

}  // namespace gsys
