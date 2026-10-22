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
