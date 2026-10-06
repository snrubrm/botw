#include "aal/aalGroupReader.h"

namespace aal {

// 0x7100b96a5c
GroupReader::GroupReader(const void* data) {
    auto* header = static_cast<const Data*>(data);
    if (!header->header.isValid(0x54534741))  // "AGST"
        return;
    if (header->header.version != 2)
        return;
    const uintptr_t base = reinterpret_cast<uintptr_t>(header);
    mTreeBlock = reinterpret_cast<const TreeBlock*>(header->tree_block_offset + base);
    mParamBlock = reinterpret_cast<const ParamBlock*>(header->param_block_offset + base);
    mStringBlock = reinterpret_cast<const u8*>(header->string_block_offset + base);
    mData = header;
}

// 0x7100b96b14
const char* GroupReader::getDefaultGroupName() const {
    if (!mData)
        return nullptr;
    return getString(mTreeBlock->default_group_name_offset);
}

// 0x7100b96b44
const char* GroupReader::getString(s32 offset) const {
    if (!mStringBlock)
        return nullptr;
    return reinterpret_cast<const char*>(mStringBlock + offset + 8);
}

// 0x7100b96b5c
const GroupReader::GroupTreeNode* GroupReader::getGroupTreeNode(const GroupTreeNode* parent,
                                                                s32 index) const {
    if (!mData)
        return nullptr;
    if (!parent)
        return reinterpret_cast<const GroupTreeNode*>(reinterpret_cast<const u8*>(mTreeBlock) + 0xc);
    if (parent->num_children <= index)
        return nullptr;

    auto* child = reinterpret_cast<const GroupTreeNode*>(reinterpret_cast<const u8*>(parent) + 0xc);
    for (s32 i = 0; i < parent->num_children; ++i) {
        if (i == index)
            return child;
        child = reinterpret_cast<const GroupTreeNode*>(reinterpret_cast<const u8*>(child) + child->size);
    }
    return nullptr;
}

// 0x7100b96bb8 (the original adds the offset to the address, not the address to the offset)
const GroupReader::GroupParam* GroupReader::getGroupParam(s32 index) const {
    if (!mData)
        return nullptr;
    if (mParamBlock->num_params <= index)
        return nullptr;
    return reinterpret_cast<const GroupParam*>(mParamBlock->param_offsets[index] +
                                               reinterpret_cast<intptr_t>(mData));
}

}  // namespace aal
