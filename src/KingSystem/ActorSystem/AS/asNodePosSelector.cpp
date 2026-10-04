#include "KingSystem/ActorSystem/AS/asElement.h"
#include <gsys/gsysModelUnit.h>
#include <limits>

namespace ksys::as {

f32 sub_710131CA0C(const sead::Vector3f& value) {
    return value.x;
}

f32 sub_710131CA14(const sead::Vector3f& value) {
    return value.y;
}

f32 sub_710131CA1C(const sead::Vector3f& value) {
    return value.z;
}

NodePosSelector::NodePosSelector() {}

NodePosSelector::~NodePosSelector() {
    _18.freeBuffer();
}

// NON_MATCHING: transpose-vector arithmetic scheduling and paired loads/stores differ.
int NodePosSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    if (!ctx->sub_7101258E2C())
        return -1;
    auto* model = ctx->sub_7101258E2C();
    if (_18.size() == 0)
        return -1;
    const auto translation = model->getMatrix().getTranslation();
    f32 highest = std::numeric_limits<f32>::lowest();
    s32 index = -1;
    for (auto it = _18.begin(), end = _18.end(); it != end; ++it) {
        if (!it->_90)
            continue;
        sead::Matrix34f bone_matrix;
        const auto& key = it->_0.getKey();
        ctx->sub_7101258E2C()->getUnits()(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
            &bone_matrix, key.bone_index);
        const auto delta = bone_matrix.getTranslation() - translation;
        const auto& matrix = model->getMatrix();
        const sead::Vector3f position(delta.dot(matrix.getBase(0)), delta.dot(matrix.getBase(1)),
                                     delta.dot(matrix.getBase(2)));
        if (highest < it->_90(position)) {
            highest = it->_90(position);
            index = it.getIndex();
        }
    }
    return index;
}

}  // namespace ksys::as
