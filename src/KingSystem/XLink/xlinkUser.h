#pragma once

#include <xlink2/xlink2IUser.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::xlink {
class XLink;

// Native123D554 initializes this matrix from ident;123EC3C updates it.
// Its existing initialization body remains undecompiled.
extern sead::Matrix34f sUnk_7102652e40;

// Constructor123CB90 and allocation122EDB0 prove the whole 0x20-byte IUser implementation.
// Native vtable25168A0 has the fifteen IUser slots followed by this class's own D1/D0.
class Unk_71025168a0 : public xlink2::IUser {
public:
    explicit Unk_71025168a0(XLink* xlink);
    virtual ~Unk_71025168a0();
    void setExtraLabels(const char* const* labels, s32 count);

    sead::Matrix34f* getBoneWorldMtxPtr(const char* name) const override;
    char* getDebugUserName() const override;
    const char* getUserInformation() const override;
    void getReservedAssetName(xlink2::ToolConnectionContext* ctx) const override;
    u32 getNumBone() const override;
    const char* getBoneName(s32 index) const override;
    u32 getNumAction(s32 index) const override;
    char* getActionName(s32 slot, s32 index) const override;
    void captureScreen(const char* name) override;
    f32 getSortKey(const sead::Vector3f& position) const override;
    sead::Matrix34f getAutoInputMtxSource() const override;
    sead::Matrix34f getMtxCorrectingDrawBone() const override;

private:
    friend class XLink;
    XLink* mXLink;
    const char* const* mExtraLabels = nullptr;
    s32 mNumExtraLabels = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71025168a0, 0x20);
}  // namespace ksys::xlink
