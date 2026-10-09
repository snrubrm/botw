#pragma once

#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Quest/qstStep.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::qst {

struct Step;
struct CameraTarget;

struct Quest {
public:
    Quest(const sead::SafeString& name, sead::Heap* heap);
    virtual ~Quest();

    bool isStepUnderCapacity() const { return (_140 >= 0 && _140 < mSteps.capacity()); }
    bool isStepUnderSize() const { return (_140 >= 0 && _140 < mSteps.size()); }
    bool isNextStepUnderSize() const { return (_140 + 1 >= 0 && _140 + 1 < mSteps.size()); }

    bool x_6(act::Actor* actor) const;
    void initFlags(gdt::Manager* gdm);
    bool flagStuff() const;
    void setField31();
    const CameraTarget* sub_7100FDA5F8(int idx);

    bool x_1() const;
    void x_3();
    bool x_7() const;
    bool x_8(act::Actor* actor);
    void x_9(act::Actor* actor);
    void x_10(const sead::SafeString& s);
    const char* x_11();
    // 0x0000007100fda5b8
    void formatQLNameKey(sead::BufferedSafeString* out) const;
    // 0x7100fda570: formats the QuestMsg/QL_ message file path.
    void sub_7100FDA570(sead::BufferedSafeString* out) const;
    // 0x0000007100fda734: the name of the current step, or an empty string
    sead::SafeString sub_7100FDA734() const;
    // 0x0000007100fda78c: whether the current step is named "Ready"
    bool sub_7100FDA78C() const;
    // 0x0000007100fda678
    bool sub_7100FDA678(sead::BufferedSafeString* out) const;

    u32 _8 = 0;
    u32 _c = 0;
    u32 _10;

    gdt::FlagHandle mReady = gdt::InvalidHandle;
    gdt::FlagHandle mCancelled = gdt::InvalidHandle;
    gdt::FlagHandle mDependencyFlag = gdt::InvalidHandle;
    const char* mQuestDependencyFlag = &sead::SafeString::cNullChar;

    u32 mQuestDependencyFlagType = 3;

    u32 mNameHash = 0;
    u8 mNotPostNote = 0;
    u8 _31 = 0;
    u8 _32 = 0;
    u8 _33 = 0;
    const char* mLocation = &sead::SafeString::cNullChar;
    sead::FixedSafeString<64> mName;
    const char* mOrderer = &sead::SafeString::cNullChar;
    sead::ObjArray<Step> mSteps;
    const char* mType = &sead::SafeString::cNullChar;
    sead::Heap* mHeap;
    al::ByamlIter* mDataIter = nullptr;
    u32 mAocVersionFlags = 0;
    u32 _dc = 0;
    u8 _e0 = 0;
    u8 mForceRunTelop = 0;
    u8 _e2 = 0;
    u8 _e3 = 0;
    u32 _e4 = 0;
    sead::FixedSafeString<64> _e8;
    s32 _140 = -1;  // current or next step?
    u8 _144 = 0;
    u32 _148 = 0;
    u32 _14c;
    void* _150 = nullptr;
};

}  // namespace ksys::qst
