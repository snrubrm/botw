#include "KingSystem/Terrain/teraResourceNode.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadSafeString.h>
#include <codec/seadHashCRC32.h>
#include <thread/seadThread.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

Unk_710110d278* Unk_7101108460::getB() const {
    return mB;
}

Unk_710250dbc8* Unk_7101108460::getA() {
    return mA;
}

const Unk_710250dbc8* Unk_7101108460::getA() const {
    return mA;
}

// NON_MATCHING: store order of mName / mNameLength / mNameHash.
Unk_7101106F44::Unk_7101106F44() {
    _8 = {1.0f, 0.0f};
    _10 = {1.0f, 0.0f};
    for (auto*& child : mChildren)
        child = nullptr;
}

Unk_7101106F44::~Unk_7101106F44() {
    for (auto& node : mNodes.robustRange()) {
        Unk_7101108460* data = node.mData;
        mNodes.erase(&node);
        delete data;
    }
    for (auto& node : mImages.robustRange()) {
        Unk_710250db28* data = node.mData;
        mImages.erase(&node);
        delete data;
    }
}

Unk_7101108460* Unk_7101106F44::sub_7101108460(sead::Heap* heap, Unk_710110d278::Key* key) {
    auto* node = new (heap) Unk_7101108460;
    node->mA = new (heap) Unk_710250dbc8;
    node->mA->init(ImageSizeMaybe(1));
    node->mB = new (heap) Unk_710110d278;
    node->mB->init({heap, node->mA, key, 0});
    mNodes.pushBack(node);
    return node;
}

// NON_MATCHING: two register moves swapped.
Unk_7101108460* Unk_7101106F44::sub_7101108334(sead::Heap* heap, Unk_710110d278::Key* key, u32 size,
                                               f32 value) {
    auto* node = new (heap) Unk_7101108460;
    const f32 scaled = value / static_cast<f32>(1 << mDepth);
    node->mA = new (heap) Unk_710250dbc8;
    node->mA->init(ImageSizeMaybe(size));
    node->mB = new (heap) Unk_710110d278;
    node->mB->init({heap, node->mA, key, scaled});
    mNodes.pushBack(node);
    return node;
}

Unk_710250db28* Unk_7101106F44::sub_7101108564(sead::Heap* heap, u32 index, u32 size) {
    auto* image = new (heap) Unk_710250db28;
    image->init({index, size});
    mImages.pushBack(image);
    return image;
}

u16 Unk_7101108460::sub_7101108614() const {
    return mB->_8->id;
}

bool Unk_7101108460::sub_7101108624() const {
    return mB->_a0 > sead::Mathf::epsilon();
}

u32 sub_7101108AE8(sead::Vector2f* out_pos, s32* out_index, const sead::Vector2f& pos,
                   const Unk_7101108AE8Flags& flags, const Unk_71010FEDBC& areas, u32 max_level) {
    if ((flags._0 & 3) != 3)
        return 0;

    const u32 count = flags._2 < max_level ? flags._2 : max_level;
    out_pos->x = 0.0f;
    out_pos->y = 0.0f;
    *out_index = 0;
    *out_index = areas.sub_71010FEDBC(pos, count, 0.0f);
    while (*out_index != -1) {
        Unk_71010FEDBC::Result result;
        while (!areas.sub_71010FE920(&result, pos, *out_index) || !result._16) {
            if (*out_index == 0)
                return 0;
            --*out_index;
        }

        out_pos->x = result.pos.x;
        out_pos->y = result.pos.y;
        if (result.pos.x >= -1.0f && result.pos.x < 2.0f && result.pos.y >= -1.0f &&
            result.pos.y < 2.0f) {
            return result._10 == 0 ? 2 : 1;
        }

        if (*out_index == 0)
            return 0;
        *out_index = areas.sub_71010FEDBC(pos, *out_index - 1, 0.0f);
    }
    return 0;
}

void Unk_7101106F44::sub_71011080D4(const ImageTypeMaybe& type) {
    getImageMaybe(type)->sub_710110DD3C();
}

bool Unk_7101106F44::sub_71011074A0() {
    bool ok = true;
    if (!tryMarkImageUnusedMaybe(sUnk_7101EC54AC))
        ok = false;
    if (!tryMarkImageUnusedMaybe(sUnk_7101EC54B4))
        ok = false;
    for (Unk_7101108460* node : mNodes) {
        if (!tryMarkImageUnusedMaybe(node->getImageType()))
            ok = false;
    }
    for (Unk_710250db28* image : mImages) {
        if (!tryMarkImageUnusedMaybe(image->getImageType()))
            ok = false;
    }
    return ok;
}

void Unk_7101106F44::sub_7101107768() {
    while (!sub_71011074A0())
        sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(1));
}

void Unk_7101106F44::sub_7101107F40(u32* max_depth, s32* index) {
    mDepth = mParent ? mParent->mDepth + 1 : 0;
    if (*max_depth < mDepth)
        *max_depth = mDepth;
    mIndex = *index;
    ++*index;
    for (auto* child : mChildren) {
        if (child)
            child->sub_7101107F40(max_depth, index);
    }
}

void Unk_7101106F44::sub_7101108004(u32* max_depth, s32* index) {
    *index = 0;
    *max_depth = 0;
    Unk_7101106F44* root = this;
    while (root->mParent)
        root = root->mParent;
    root->sub_7101107F40(max_depth, index);
}

bool Unk_7101106F44::sub_7101108174(u16 id) const {
    const Unk_7101106F44* area = this;
    do {
        const Unk_7101108460* node = area->findNodeMaybe(id);
        if (node)
            return node->sub_7101108624();
        area = area->mParent;
    } while (area);
    return false;
}

void Unk_7101106F44::sub_7101108020(const ImageTypeMaybe& type, agl::TextureSampler* sampler,
                                    const agl::GPUMemVoidAddr& addr, s32 mip_offset, bool flag) {
    getImageMaybe(type)->m11(sampler, addr, mip_offset, flag);
}

bool Unk_7101106F44::sub_7101107318(s32 index, Unk_7101106F44* child) {
    Unk_7101106F44*& slot = mChildren[index];
    if (!child) {
        if (!slot)
            return false;
        slot->mParent = nullptr;
        slot->_1 = 4;
        slot = nullptr;
        return true;
    }
    if (slot)
        return false;
    slot = child;
    child->mParent = this;
    child->_1 = index;
    return true;
}

void Unk_7101106F44::sub_7101108298(Unk_7101108460* node) {
    Unk_710110d278::Key* key = node->mB->_8;
    node->mA = new (static_cast<sead::Heap*>(nullptr)) Unk_710250dbc8;
    node->mA->init(ImageSizeMaybe(1));
    node->mB = new (static_cast<sead::Heap*>(nullptr)) Unk_710110d278;
    node->mB->init({nullptr, node->mA, key, 0.0f});
}

void Unk_7101106F44::sub_71011081D4(Unk_7101108460* node, sead::Heap* heap, u32 size, f32 value) {
    Unk_710110d278::Key* key = node->mB->_8;
    const f32 scaled = value / static_cast<f32>(1 << mDepth);
    node->mA = new (heap) Unk_710250dbc8;
    node->mA->init(ImageSizeMaybe(size));
    node->mB = new (heap) Unk_710110d278;
    node->mB->init({heap, node->mA, key, scaled});
}

void Unk_7101106F44::sub_710110736C(const ImageTypeMaybe& type) {
    while (true) {
        Unk_710250dcd8* image = getImageMaybe(type);
        if (image && image->_18.tryMarkUnusedMaybe())
            return;
        sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(1));
    }
}

// NON_MATCHING: stack layout of the two strings and the order of the id load.
bool Unk_7101106F44::init(const InitArg& arg) {
    if (arg.parent && !arg.parent->sub_7101107318(arg.slot, this))
        return false;

    _4 = arg._18;
    mDepth = arg.depth;

    sead::FixedSafeString<32> name;
    u32 path = 0;
    s32 depth = -1;
    s32 shift = 0;
    for (const Unk_7101106F44* node = this; node; node = node->mParent) {
        path |= (node->_1 & 3) << shift;
        shift += 2;
        ++depth;
    }
    name.format("%X%X%08X", arg.id, depth, path);

    sead::BufferedSafeString name_buffer(mName, sizeof(mName));
    mNameLength = name_buffer.copy(name);
    mNameHash = sead::HashCRC32::calcHash(mName, mNameLength);
    mImage0.init(name);
    mImage1.init(ImageSizeMaybe(5));
    return true;
}


}  // namespace ksys::tera
