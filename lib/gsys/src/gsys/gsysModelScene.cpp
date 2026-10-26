#include <gsys/gsysModelScene.h>
#include <gsys/gsysLayer3D.h>
#include <gsys/gsysModelMgr.h>
#include <gsys/gsysModelSceneConfig.h>
#include <gsys/gsysModelRenderQueue.h>
#include <gsys/gsysParticleDrawArg.h>
#include <gsys/gsysParticleMgr.h>
#include <gsys/gsysShaderContext.h>
#include <gsys/gsysParticleDrawArg.h>

namespace gsys {

ModelScene::CreateArg::CreateArg()
    : _0(1), mName(sead::SafeString::cEmptyString), _18(0) {}


// 0x7100c10148
bool ModelScene::isSnapshotMgrEnabled() const {
    if (!mSnapshotMgr)
        return false;
    // The native body reads the OcclusionQeuery feature value at config +0x6c8; the CSV name
    // suggests a snapshot manager, whose type is unmodelled.
    return mConfig->isFeatureEnabled(ModelSceneConfig::Feature::OcclusionQeuery);
}

// 0x7100c13d40
bool ModelScene::isForceZPrePassEnabled(int index) const {
    if (!mBuffer.isZPrePassEnabled(mContexts[index]))
        return false;
    return mConfig->isZPrePassSelectable();
}

// NON_MATCHING: the original stores the 1000.0f / -1000.0f / -1000.0f fields with three 32-bit stores;
// our clang merges adjacent constant member initialisers into 64-bit stores (116 bytes against 120).
// 0x7100c20ec4
ModelSceneContext::ModelSceneContext() = default;

// 0x7100c20f3c
ModelSceneContext::~ModelSceneContext() {
    if (_398)
        _398->setModelScene(nullptr);
    if (mParticleDrawArg) {
        delete mParticleDrawArg;
        mParticleDrawArg = nullptr;
    }
}

// 0x7100c21368
void ModelSceneContext::calc(bool arg, bool, int value) {
    mFlags = (mFlags & 0xf8) | 2;
    if (!_398)
        return;

    ModelRenderContext::clear();
    _392 = 0xff;
    mRenderQueues = nullptr;
    mViewport = _398->getLogicalViewport();
    ModelRenderContext::mViewport = &mViewport;
    if (!_398->get_9a())
        return;
    bool skip = (_398->mFlags & 0x20) != 0;
    if (skip)
        skip = _398->_230 != nullptr;
    if (skip)
        return;
    if (!arg)
        return;

    mShaderContext->clear(getViewIndex(), value);
    mFlags |= 9;
}

// 0x7100c21514
bool ModelSceneContext::isDrawParticle(ParticlePass pass) const {
    if ((~mParticleFlags & 3) != 0)
        return false;
    ParticleMgr* mgr = ParticleMgr::instance();
    if (!mgr)
        return false;
    return mgr->isNeedDraw(mParticleDrawArg->mParticleGroups, mParticleDrawArg->mParticleGroupNum,
                           1u << int(pass));
}

// 0x7100c21490
ModelRenderQueue* ModelSceneContext::getRenderQueue(QueueType type) const {
    return &mRenderQueues[type];
}

// 0x7100c21450
bool ModelSceneContext::isQueueMaskValid(QueueType type, const sead::BitFlag32& mask) const {
    if (!mRenderQueues)
        return false;
    const ModelRenderQueue& queue = mRenderQueues[type];
    if (queue.mSize < 1)
        return false;
    return mask & queue.mRenderMask;
}

// 0x7100c214a0
void ModelSceneContext::drawQueue(agl::DrawContext* draw_context, const sead::SafeString& name,
                                  QueueType type, const sead::BitFlag32& mask, u32 value,
                                  ModelEnum::ShaderAssignType shader_assign_type,
                                  ViewProjType view_proj_type, u32 options, u32 material) const {
    ModelRenderContext::DrawArg arg(name, mRenderQueues[int(type)], mask, value,
                                    shader_assign_type, view_proj_type, options, material);
    draw(draw_context, arg);
}

// 0x7100c0fe14
void ModelScene::bindEnv_() {
    ModelMgr::instance()->rebindModelScene(this);
}

void ModelScene::skipDraw() {
    mJobQueue.changeRequestFlag(true, true, false);
}

void ModelScene::calcWorld_(sead::WorkerMgr* wm) {
    calc(wm, 3, 7, 0);
}

void ModelScene::calcRenderView_(sead::WorkerMgr* wm) {
    calc(wm, 0, 0xc, 0);
}

void ModelScene::calcModelUnit_(sead::WorkerMgr* wm) {
    mJobQueue.updateModelUnit(wm);
}

// 0x7100c10c94
void ModelScene::sortQueue_(sead::WorkerMgr* wm) {
    mJobQueue.preSort(wm);
    mShadow.calc(wm);
}

// 0x7100c12114
void ModelScene::calcDrawBackGround_(sead::WorkerMgr* wm) {
    calc(wm, 4, 3, 0);
    calc(wm, 1, 4, 3);
}

// 0x7100c13bfc
void ModelScene::addParticleGroup(int group, int index) {
    if (index >= 0) {
        ModelSceneContext& context = mContexts[index];
        context.mParticleDrawArg->addParticleGroup(group);
        if (group == 0)
            context.mParticleFlags |= 0x10;
        return;
    }

    for (auto& context : mContexts) {
        context.mParticleDrawArg->addParticleGroup(group);
        if (group == 0)
            context.mParticleFlags |= 0x10;
    }
}

// 0x7100c13cb4
void ModelScene::clearParticleGroup(int index) {
    if (index >= 0) {
        ModelSceneContext& context = mContexts[index];
        context.mParticleDrawArg->clearParticleGroup();
        context.mParticleFlags &= ~0x10;
        return;
    }

    for (auto& context : mContexts) {
        context.mParticleDrawArg->clearParticleGroup();
        context.mParticleFlags &= ~0x10;
    }
}

}  // namespace gsys
