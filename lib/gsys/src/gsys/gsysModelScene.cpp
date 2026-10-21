#include <gsys/gsysModelScene.h>
#include <gsys/gsysModelMgr.h>
#include <gsys/gsysModelSceneConfig.h>
#include <gsys/gsysModelRenderQueue.h>
#include <gsys/gsysParticleDrawArg.h>
#include <gsys/gsysParticleMgr.h>
#include <gsys/gsysParticleDrawArg.h>

namespace gsys {

ModelScene::CreateArg::CreateArg()
    : _0(1), mName(sead::SafeString::cEmptyString), _18(0) {}


// 0x7100c13d40
bool ModelScene::isForceZPrePassEnabled(int index) const {
    if (!mBuffer.isZPrePassEnabled(mContexts[index]))
        return false;
    return mConfig->isZPrePassSelectable();
}

// 0x7100c21514
bool ModelSceneContext::isDrawParticle(ParticlePass pass) const {
    if ((~_391 & 3) != 0)
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
            context._391 |= 0x10;
        return;
    }

    for (auto& context : mContexts) {
        context.mParticleDrawArg->addParticleGroup(group);
        if (group == 0)
            context._391 |= 0x10;
    }
}

// 0x7100c13cb4
void ModelScene::clearParticleGroup(int index) {
    if (index >= 0) {
        ModelSceneContext& context = mContexts[index];
        context.mParticleDrawArg->clearParticleGroup();
        context._391 &= ~0x10;
        return;
    }

    for (auto& context : mContexts) {
        context.mParticleDrawArg->clearParticleGroup();
        context._391 &= ~0x10;
    }
}

}  // namespace gsys
