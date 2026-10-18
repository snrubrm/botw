#include <gsys/gsysModelRenderContext.h>
#include <gsys/gsysShaderContext.h>

namespace gsys {

// NON_MATCHING: buffer bounds selection and loop-count reload differ.
void ModelRenderContext::calcGPU(bool flag) const {
    for (int i = 0; i < mViewData.size(); ++i) {
        const ViewData& view = mViewData[i];
        mShaderContext->calcGpuViewFlush(i, view.view, view.frustum.getProjectionMatrix(),
                                       view.frustum, false, flag);
    }
}

}  // namespace gsys
