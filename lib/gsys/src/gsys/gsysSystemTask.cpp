#include <gsys/gsysApplicationPackage.h>
#include <gsys/gsysSystemTask.h>

namespace gsys {

SystemTask* SystemTask::sInstance = nullptr;

void SystemTask::setInstance(SystemTask* task) {
    if (sInstance)
        return;
    sInstance = task;
    task->_d8 = true;
}

// 0x7100c6588c
void SystemTask::setFrameUpdateScale(f32 scale) {
    mFrameUpdateScale = scale;
}

// 0x7100c66850
void SystemTask::attachCalcImpl() {}

// 0x7100c66928
void SystemTask::detachCalcImpl() {
    mMethodTreeNodes[0].detachAll();
    mMethodTreeNodes[1].detachAll();
}

// 0x7100c66950
void SystemTask::detachDrawImpl() {
    mMethodTreeNodes[2].detachAll();
    mMethodTreeNodes[3].detachAll();
    mMethodTreeNodes[4].detachAll();
    mMethodTreeNodes[5].detachAll();
}

// 0x7100c65894
void SystemTask::setFrameBufferSize(int index, const sead::Vector2i& size) {
    if (index == 0)
        mFrameBufferSize0 = size;
    else if (index == 1)
        mFrameBufferSize1 = size;
}

// 0x7100c66cf4
sead::MethodTreeNode* SystemTask::getMethodTreeNode(s32 method_type) {
    static const s32 node_indices[] = {0, 1, 2, 2, 2};
    if (method_type >= 0 && method_type <= 4)
        return &mMethodTreeNodes[node_indices[method_type]];
    return nullptr;
}

// 0x7100c66988
void SystemTask::pauseCalc(bool pause) {
    const auto flag = pause ? sead::MethodTreeNode::cPause_Self : sead::MethodTreeNode::cPause_None;
    mMethodTreeNodes[0].setPauseFlag(flag);
    mMethodTreeNodes[1].setPauseFlag(flag);
}

// 0x7100c66a14
void SystemTask::pauseDraw(bool pause) {
    const auto flag = pause ? sead::MethodTreeNode::cPause_Self : sead::MethodTreeNode::cPause_None;
    mMethodTreeNodes[2].setPauseFlag(flag);
    mMethodTreeNodes[3].setPauseFlag(flag);
    mMethodTreeNodes[4].setPauseFlag(flag);
    mMethodTreeNodes[5].setPauseFlag(flag);
}

// 0x7100c66b08
void SystemTask::pauseCalcRec(bool pause) {
    const auto flag = pause ? sead::MethodTreeNode::cPause_Both : sead::MethodTreeNode::cPause_None;
    mMethodTreeNodes[0].setPauseFlag(flag);
    mMethodTreeNodes[1].setPauseFlag(flag);
}

// 0x7100c66b9c
void SystemTask::pauseDrawRec(bool pause) {
    const auto flag = pause ? sead::MethodTreeNode::cPause_Both : sead::MethodTreeNode::cPause_None;
    mMethodTreeNodes[2].setPauseFlag(flag);
    mMethodTreeNodes[3].setPauseFlag(flag);
    mMethodTreeNodes[4].setPauseFlag(flag);
    mMethodTreeNodes[5].setPauseFlag(flag);
}

// 0x7100c658f8
void SystemTask::waitDrawDoneCallback(bool flag) {
    if (flag)
        instance()->updateGPU_();
}

bool SystemTask::searchAglShaderFile(void** binary, void** source,
                                     const sead::SafeString& name) const {
    return ApplicationPackage::instance()->searchAglShaderFile(binary, source, name);
}

bool SystemTask::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* SystemTask::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

}  // namespace gsys
