#include <gsys/gsysXluZPrePass.h>

#include <gsys/gsysModelRenderContext.h>
#include <gsys/gsysModelRenderUnit.h>
#include <gsys/gsysModelRenderUnitNodeArray.h>
#include <gsys/gsysModelSceneContext.h>
#include <gsys/gsysModelUnit.h>
#include <math/seadMathCalcCommon.h>

namespace gsys {

// 0x7100c67a58
XluZPrePass::XluZPrePass() = default;

// 0x7100c67aa0 (D1) / 0x7100c67af8 (D0)
XluZPrePass::~XluZPrePass() {
    mNodes.freeBuffer();
    mSortNodes.freeBuffer();
}

// 0x7100c67b58
void XluZPrePass::initialize(sead::Heap* heap) {
    mQueues[0].initialize(0x800, heap);
    mQueues[1].initialize(0x800, heap);

    mQueues[0].mSortMode = 0;
    mQueues[1].mSortMode = 1;

    mNodes.allocBuffer(0x800, heap, sizeof(void*));
    mSortNodes.tryAllocBuffer(0x800, heap, sizeof(void*));
}

// 0x7100c67be8
void XluZPrePass::clear() {
    mQueues[0].clear();
    mQueues[1].clear();
}

// 0x7100c67c10
bool XluZPrePass::isValid(const sead::BitFlag32& mask) const {
    const u32 mask_bits = mask;
    if (mQueues[0].mSize >= 1 && (mQueues[0].mRenderMask & mask_bits))
        return true;
    if (mQueues[1].mSize >= 1)
        return (mask_bits | 0x91) & mQueues[1].mRenderMask;
    return false;
}

// 0x7100c68018
void XluZPrePass::draw(agl::DrawContext* context, const ModelSceneContext& scene_context,
                       const sead::BitFlag32& mask, bool flag) const {
    const s32 count = mNodes.size();
    if (count == 0)
        return;

    const u32 options = 0x20 | flag;
    const XluZPrePassSortNode* const* node = mNodes.data();
    const XluZPrePassSortNode* const* end = node + count;
    for (; node != end; ++node) {
        scene_context.draw(context, ModelRenderContext::DrawArg(
                                         "Model(XluZPrePass/ZOnly)", mQueues[0], mask, 4,
                                         ModelEnum::ShaderAssignType::_1, 0, options,
                                         (*node)->mIndex));
        scene_context.draw(context, ModelRenderContext::DrawArg(
                                         "Model(XluZPrePass/ZOnly/DepthFill)", mQueues[1],
                                         sead::BitFlag32(0x10), 4, ModelEnum::ShaderAssignType::_1,
                                         0, options, (*node)->mIndex));
        scene_context.draw(context, ModelRenderContext::DrawArg(
                                         "Model(XluZPrePass/Opa+AlphaMask)", mQueues[0], mask, 4,
                                         ModelEnum::ShaderAssignType::_9, 0, 0x220,
                                         (*node)->mIndex));
        scene_context.draw(context, ModelRenderContext::DrawArg(
                                         "Model(XluZPrePass/Xlu)", mQueues[1], mask, 4,
                                         ModelEnum::ShaderAssignType::_9, 0, 0x10220,
                                         (*node)->mIndex));
    }
}

// 0x7100c67c60
// NON_MATCHING: clang strength-reduces the two mark loops to a pointer countdown where the
// original keeps the array index (sxtw addressing). The rest, including the inlined heap sort,
// matches.
void XluZPrePass::sort() {
    mNodes.clear();

    u16 seen[0x800];
    for (s32 i = 0, n = mQueues[0].mSize; i != n; ++i) {
        const ModelRenderUnitSortNode* sort_node = mQueues[0].mSortNodes[i];
        const ModelRenderUnit* render_unit = sort_node->mRenderUnit;
        const u32 key =
            render_unit->getModelUnit()->getMaterialInfo()[render_unit->getMaterialIndex()]._4 &
            0x7ff;
        seen[key] = 0xffff;
    }
    for (s32 i = 0, n = mQueues[1].mSize; i != n; ++i) {
        const ModelRenderUnitSortNode* sort_node = mQueues[1].mSortNodes[i];
        const ModelRenderUnit* render_unit = sort_node->mRenderUnit;
        const u32 key =
            render_unit->getModelUnit()->getMaterialInfo()[render_unit->getMaterialIndex()]._4 &
            0x7ff;
        seen[key] = 0xffff;
    }

    for (s32 i = 0, n = mQueues[0].mSize; i != n; ++i) {
        ModelRenderUnitSortNode* sort_node = mQueues[0].mSortNodes[i];
        const ModelRenderUnit* render_unit = sort_node->mRenderUnit;
        const u32 key =
            render_unit->getModelUnit()->getMaterialInfo()[render_unit->getMaterialIndex()]._4 &
            0x7ff;
        const u16 entry = seen[key];
        if (entry != 0xffff) {
            sort_node->mMaterialIndex = entry;
            XluZPrePassSortNode& node = mSortNodes[entry];
            node.mDepth = sead::Mathf::max(node.mDepth, sort_node->mDepth);
        } else {
            const u16 index = mNodes.size();
            seen[key] = index;
            sort_node->mMaterialIndex = index;
            XluZPrePassSortNode& node = mSortNodes[mNodes.size()];
            node.mIndex = s16(index);
            node.mDepth = sort_node->mDepth;
            mNodes.pushBack(&node);
        }
    }
    for (s32 i = 0, n = mQueues[1].mSize; i != n; ++i) {
        ModelRenderUnitSortNode* sort_node = mQueues[1].mSortNodes[i];
        const ModelRenderUnit* render_unit = sort_node->mRenderUnit;
        const u32 key =
            render_unit->getModelUnit()->getMaterialInfo()[render_unit->getMaterialIndex()]._4 &
            0x7ff;
        const u16 entry = seen[key];
        if (entry != 0xffff) {
            sort_node->mMaterialIndex = entry;
            XluZPrePassSortNode& node = mSortNodes[entry];
            node.mDepth = sead::Mathf::max(node.mDepth, sort_node->mDepth);
        } else {
            const u16 index = mNodes.size();
            seen[key] = index;
            sort_node->mMaterialIndex = index;
            XluZPrePassSortNode& node = mSortNodes[mNodes.size()];
            node.mIndex = s16(index);
            node.mDepth = sort_node->mDepth;
            mNodes.pushBack(&node);
        }
    }

    // The original inlines sead's heap sort here, ordered by the node depths.
    const s32 n = mNodes.size();
    if (n > 1) {
        XluZPrePassSortNode** nodes = mNodes.data();
        s32 i = n / 2;
        do {
            XluZPrePassSortNode* top = nodes[i - 1];
            s32 j = i;
            while (j * 2 <= n) {
                s32 child = j * 2;
                if (child < n)
                    child = nodes[child - 1]->mDepth < nodes[child]->mDepth ? child + 1 : child;
                if (!(top->mDepth < nodes[child - 1]->mDepth))
                    break;
                nodes[j - 1] = nodes[child - 1];
                j = child;
            }
            nodes[j - 1] = top;
        } while (--i >= 1);

        for (s32 end = n; end >= 2; --end) {
            XluZPrePassSortNode* top = nodes[end - 1];
            nodes[end - 1] = nodes[0];
            s32 j = 1;
            while (j * 2 < end) {
                s32 child = j * 2;
                if (child < end - 1)
                    child = nodes[child - 1]->mDepth < nodes[child]->mDepth ? child + 1 : child;
                if (!(top->mDepth < nodes[child - 1]->mDepth))
                    break;
                nodes[j - 1] = nodes[child - 1];
                j = child;
            }
            nodes[j - 1] = top;
        }
    }
}

}  // namespace gsys
