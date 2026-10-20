#include <gsys/gsysModelRenderUnitNodeArray.h>

namespace gsys {

ModelRenderUnitSortNode::ModelRenderUnitSortNode() = default;

ModelRenderUnitNodeArray::ModelRenderUnitNodeArray() = default;

ModelRenderUnitNodeArray::~ModelRenderUnitNodeArray() {
    mNodes.freeBuffer();
}

bool ModelRenderUnitNodeArray::initialize(int count, sead::Heap* heap) {
    mNodes.tryAllocBuffer(count, heap, 0x20);
    return true;
}

}  // namespace gsys
