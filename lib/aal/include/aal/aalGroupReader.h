#pragma once

#include <basis/seadTypes.h>
#include "aal/aalResourceHeader.h"

namespace aal {

/// Reads the binary resource of the sound group tree (signature "AGST", version 2): a tree of group nodes, a list of
/// group parameters and a string table. The nodes of the tree and the parameters are referenced by offsets.
class GroupReader {
public:
    /// A node of the tree. The children follow the node (`num_children` nodes, each `size` bytes).
    struct GroupTreeNode {
        s32 size;
        s32 _4;
        s32 num_children;
    };

    /// TODO: the layout of the parameters (default sound param, limiter, ducking) is not modeled.
    struct GroupParam;

    explicit GroupReader(const void* data);

    /// The name of the root group, nullptr if the resource is not valid.
    const char* getDefaultGroupName() const;
    /// The string at `offset` of the string table.
    const char* getString(s32 offset) const;
    /// The index-th child of `parent` (the first node if `parent` is nullptr), nullptr if there is none.
    const GroupTreeNode* getGroupTreeNode(const GroupTreeNode* parent, s32 index) const;
    const GroupParam* getGroupParam(s32 index) const;

private:
    struct TreeBlock {
        u32 _0;
        u32 _4;
        s32 default_group_name_offset;
        /// The first node follows.
    };

    struct ParamBlock {
        u32 _0;
        u32 _4;
        s32 num_params;
        s32 param_offsets[1];
    };

    struct Data {
        ResourceHeader header;
        u32 _8;
        u32 tree_block_offset;
        u32 param_block_offset;
        u32 string_block_offset;
    };

    const Data* mData = nullptr;
    const TreeBlock* mTreeBlock = nullptr;
    const ParamBlock* mParamBlock = nullptr;
    const u8* mStringBlock = nullptr;
};

}  // namespace aal
