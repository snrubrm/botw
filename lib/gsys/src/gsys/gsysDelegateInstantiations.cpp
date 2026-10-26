#include <prim/seadDelegate.h>

#include <gsys/gsysModelNW.h>
#include <gsys/gsysModelRenderContext.h>
#include <gsys/gsysModelSceneEnv.h>
#include <gsys/gsysModelUnit.h>
#include <gsys/gsysModelProceduralShape.h>
#include <gsys/gsysShaderContext.h>
#include <lighting/aglLightPrePass.h>

// These callback argument types are known only from the delegate symbols; the classes
// themselves are not modelled yet.
namespace gsys {
class ModelSceneGI
{
public:
    struct CalcLightPrePassCallbackArg;
};

class ModelScenePfx
{
public:
    struct HDRComposeReplacerArg;
};
}  // namespace gsys

namespace agl::lght {
class PlanarReflection
{
public:
    struct CallbackArg;
};

class SSSSS
{
public:
    struct CallbackArg;
};
}  // namespace agl::lght

namespace agl::sdw {
class DepthShadow
{
public:
    struct CallbackArg;
};
}  // namespace agl::sdw

namespace sead {
// The original binary emits these delegate interfaces and the nested UnbindDummy
// implementations once per callback type; the containing TUs are not decompiled yet.
template class IDelegate1<const gsys::ModelUnitCallbackArg&>;
template class IDelegate1<gsys::ModelNW::BoneCallbackArg*>;
template class IDelegate1<const gsys::ModelRenderContext::CallbackArg&>;
template class IDelegate1<const agl::lght::PlanarReflection::CallbackArg&>;
template class IDelegate1<gsys::ModelSceneGI::CalcLightPrePassCallbackArg&>;
template class IDelegate1<const agl::lght::LightPrePass::CallbackArg&>;
template class IDelegate1<const agl::lght::SSSSS::CallbackArg&>;
template class IDelegate1<const agl::sdw::DepthShadow::CallbackArg&>;
template class IDelegate1<const gsys::ShaderContext::CallbackArg&>;
template class IDelegate1<const gsys::ModelSceneEnv::ApplyCallbackArg&>;
template class IDelegate1<const gsys::ModelProceduralShape::ResetArg&>;
template class IDelegate2<agl::DrawContext*, const gsys::ModelScenePfx::HDRComposeReplacerArg&>;

template class AnyDelegate1<gsys::ModelNW::BoneCallbackArg*>;
template class AnyDelegate1<const gsys::ModelRenderContext::CallbackArg&>;
template class AnyDelegate1<gsys::ModelSceneGI::CalcLightPrePassCallbackArg&>;
template class AnyDelegate1<const gsys::ModelUnitCallbackArg&>;
template class AnyDelegate1<const gsys::ShaderContext::CallbackArg&>;
template class AnyDelegate1<const gsys::ModelProceduralShape::Arg&>;
template class AnyDelegate1<const gsys::ModelProceduralShape::ResetArg&>;
template class AnyDelegate2<agl::DrawContext*, const gsys::ModelScenePfx::HDRComposeReplacerArg&>;
}  // namespace sead
