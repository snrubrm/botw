#pragma once

#include <framework/seadTaskBase.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

#include <cstddef>

namespace gsys {

// The system task. Factory 0x7100f2a504 allocates 0x6a8 bytes and calls the constructor
// 0x7100c63644. sead::TaskBase is 0xd0 bytes; the constructor then installs a second vptr at
// +0xd0 (the sead::hostio::Node secondary vtable, a single getNodeClassType slot in the release
// build) and the first own byte at +0xd8, which is why the bases are ordered this way.
class SystemTask : public sead::TaskBase, public sead::hostio::Node {
public:
    // 0x7100c64ca4 (296 bytes): not modelled yet, so the destructor stays undefined.
    virtual ~SystemTask();

    // 0x7100c63578: called by the framework once the task exists.
    static void setInstance(SystemTask* task);
    static SystemTask* instance() { return sInstance; }

    // 0x7100c66d20: forwards to the application package.
    bool searchAglShaderFile(void** binary, void** source, const sead::SafeString& name) const;

    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<sead::TaskBase> typeInfo;
        return &typeInfo;
    }
    static bool checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* typeInfo) {
        const sead::RuntimeTypeInfo::Interface* clsTypeInfo = SystemTask::getRuntimeTypeInfoStatic();
        if (typeInfo == clsTypeInfo)
            return true;
        return sead::TaskBase::checkDerivedRuntimeTypeInfoStatic(typeInfo);
    }
    bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const override;
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override;

private:
    static SystemTask* sInstance;

    // Set to 1 by setInstance.
    u8 _d8;
    u8 _d9[0x578 - 0xd9];

public:
    // +0x578. Bit 0 is a frame-calc pause: WorldMgr::calc1 / calc2 / calc3 / calcEntryJob and
    // ksys::world::ChemicalMgr::sub_71010CC5B4 return early while it is set, Root38::x copies it
    // into its own byte at +0x2c, and GameTool::m7 / __auto0 change it with changeBit(0, ...).
    // The constructor zeroes the whole 32-bit word.
    sead::BitFlag32 mFlags;

    // 0x7100c6588c: stores the frame update scale at +0x5b8.
    void setFrameUpdateScale(f32 scale);
    // 0x7100c66850: the system task has no separate calc attachment.
    void attachCalcImpl() override;

private:
    u8 _57c[0x5b8 - 0x57c];
    f32 mFrameUpdateScale;
    u8 _5bc[0x6a8 - 0x5bc];
};

static_assert(sizeof(SystemTask) == 0x6a8);
// The constructor zeroes the word at +0x578; every reader loads that address.
static_assert(offsetof(SystemTask, mFlags) == 0x578);

}  // namespace gsys
