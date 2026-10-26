#pragma once

#include <framework/seadTaskBase.h>
#include <framework/seadMethodTree.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
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
    u8 _d9[0xe0 - 0xd9];
    // The method-tree nodes the calc and draw attach/detach entries walk (0x98 bytes each;
    // detachCalcImpl touches 0 and 1, detachDrawImpl 2 to 5).
    sead::MethodTreeNode mMethodTreeNodes[6];
    u8 _470[0x4c0 - 0x470];
    /* 0x4c0 */ sead::Vector2i mFrameBufferSize0;
    /* 0x4c8 */ sead::Vector2i mFrameBufferSize1;
    u8 _4d0[0x578 - 0x4d0];

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
    // 0x7100c66928 / 0x7100c66950: detach the calc / draw part of the method tree.
    void detachCalcImpl() override;
    void detachDrawImpl() override;
    // 0x7100c66988 / 0x7100c66a14: pause the two calc / four draw nodes.
    void pauseCalc(bool pause) override;
    void pauseDraw(bool pause) override;
    // 0x7100c66b08 / 0x7100c66b9c: the recursive variants pause the children too.
    void pauseCalcRec(bool pause) override;
    void pauseDrawRec(bool pause) override;
    // 0x7100c65894: writes the TV (0) or DRC (1) frame buffer size.
    void setFrameBufferSize(int index, const sead::Vector2i& size);
    // 0x7100c66cf4: the method-tree node of the calc/draw step `method_type`, or nullptr.
    sead::MethodTreeNode* getMethodTreeNode(s32 method_type) override;
    // 0x7100c658f8: the draw-done callback; runs the GPU update when the flag is set.
    static void waitDrawDoneCallback(bool flag);
    // 0x7100c65d90 (declared only): submits the GPU work of the task.
    void updateGPU_();

private:
    u8 _57c[0x5b8 - 0x57c];
    f32 mFrameUpdateScale;
    u8 _5bc[0x6a8 - 0x5bc];
};

static_assert(sizeof(SystemTask) == 0x6a8);
// The constructor zeroes the word at +0x578; every reader loads that address.
static_assert(offsetof(SystemTask, mFlags) == 0x578);

}  // namespace gsys
