#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <hostio/seadHostIONode.h>
#include <math/seadBoundBox.h>
#include <math/seadMathCalcCommon.h>
#include <nn/ui2d/DrawInfo.h>
#include "KingSystem/Utils/Types.h"
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include "Game/UI/euiButton.h"
#include "Game/UI/euiTypes.h"
#include "Game/UI/euiDynamicCapturePane.h"
#include "Game/UI/euiSharcArchive.h"

namespace sead {
class Heap;
class FrameBuffer;
class GraphicsContext;
class Viewport;
}

namespace agl {
class DrawContext;
}

namespace xlink2 {
class UserInstanceSLink;
}

namespace nn::ui2d {
class Pane;
class ResourceAccessor;
}  // namespace nn::ui2d

namespace eui {

class AnimButton;
class Animator;
class PartsEx;
class TagProcessor;
class UIController;
class LayoutEx;
class BoxCursorNode;
class BoxCursorMgr;
class ButtonGroup;
class ScreenMgr;
class ScreenTargetMgr;
class MessageMgr;
class FontMgr;
class ArcResourceMgr;
class ConstantBuffer;

// Per-screen draw information; the base contains the layout matrices.
struct DrawInfoEx : public nn::ui2d::DrawInfo {
    NN_RUNTIME_TYPEINFO(nn::ui2d::DrawInfo)
    // The screen passes this record to DrawInfoEx and pane drawing; the
    // original copies all five pointers when changing the scissor viewport.
    struct RenderBufferInfo {
        const sead::FrameBuffer* mFrameBuffer;
        const sead::GraphicsContext* mGraphicsContext;
        const sead::Viewport* mViewport;
        const sead::Viewport* mScissor;
        agl::DrawContext* mDrawContext;
    };
    static_assert(sizeof(RenderBufferInfo) == 0x28);
    ~DrawInfoEx() override = default;
    void freeDynamicTexture();
    static void applyRenderBufferInfo(const RenderBufferInfo* info);

    /* 0xf8 */ const RenderBufferInfo* _f8 = nullptr;
    /* 0x100 */ bool _100 = false;
    using DynamicTextureList = nn::util::IntrusiveList<
        DynamicCapturePane, nn::util::IntrusiveListMemberNodeTraits<
                                DynamicCapturePane, &DynamicCapturePane::mDynamicTextureNode>>;
    /* 0x108 */ DynamicTextureList mDynamicTextures;
    /* 0x118 */ u8 _118[8];
};
static_assert(sizeof(DrawInfoEx) == 0x120);

// The eui UI framework's screen base class (CSV: eui::Screen::*, mangled names). Only the parts that
// are needed so far are declared: the RTTI root (vtable slots 2 / 3 are checkDerivedRuntimeTypeInfo /
// getRuntimeTypeInfo) and the screen manager's screen table.
// eui::Screen derives from sead::IDisposer (offset 0) and sead::hostio::Node (offset 0x20: the vtable
// stored at 0x20 has Node::getNodeClassType first); its own data follows (0x28 - 0x108).
class Screen : public sead::IDisposer, public sead::hostio::Node {
public:
    Screen();
    ~Screen() override;
    SEAD_RTTI_BASE(Screen)

    virtual bool isEnableControl() const;
    // Slots 5 / 6 (CSV Screen::open / Screen::close); the argument is an open / close option
    // (-1 / -4 are passed to close by the facade functions).
    virtual void open(s32 option);
    virtual void close(s32 option);
    // Slots 7-68 (names from the CSV; the return types of the factory functions and the boolean results are guesses)
    virtual void adjstBoxCursor(sead::BoundBox2<f32>* box, const BoxCursorNode* node) const;
    virtual BoxCursorNode* createBoxCursorNode(sead::Heap* heap);
    virtual void initialize(ScreenMgr* mgr, sead::Heap* heap, const char* name, s32 a, s8 b, bool c);
    virtual void update();
    virtual void draw(const DrawInfoEx::RenderBufferInfo* info);
    virtual const char* replacePartsLayoutName(const char* name, PartsEx* parts, LayoutEx* layout);
    virtual void m13();
    virtual void m14();
    virtual const char* getLayoutName_() const;  // returns the layout name (<Name>_00) in the leaf classes
    virtual const char* getMessageName_() const;
    virtual const char* getArchiveName_() const;
    virtual bool isPlayPartsInOut_() const;  // slot 18
    virtual bool isDisallowHitLowerScreenOnButtonHit_() const;
    virtual LayoutEx* doCreateLayout_(sead::Heap* heap);
    virtual DrawInfoEx* doCreateDrawInfoEx_(sead::Heap* heap);
    virtual ButtonGroup* doCreateButtonGroup_(sead::Heap* heap);
    virtual void doAfterBuildLayout_(sead::Heap* heap);
    virtual void doSetupDrawInfo_();
    virtual UIController* doCreateUIController_(sead::Heap* heap);
    virtual nn::ui2d::ResourceAccessor* doCreateResourceAccessor_(sead::Heap* heap);
    virtual TagProcessor* doCreateTagProcessor_(sead::Heap* heap);
    virtual void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor);
    virtual void doLoadResource_(sead::Heap* heap);
    virtual void doInitialize_(sead::Heap* heap);
    virtual void doUpdate_();
    virtual f32 getAnimationStep_() const;
    virtual void doDraw_(const DrawInfoEx::RenderBufferInfo* info);
    virtual void doOpenStart_();
    virtual void doOpenEnd_();
    virtual void doCloseStart_();
    virtual void doCloseEnd_();
    virtual void doButtonOnStart_(AnimButton* button);
    virtual void doButtonOnEnd_(AnimButton* button);
    virtual void doButtonOffStart_(AnimButton* button);
    virtual void doButtonOffEnd_(AnimButton* button);
    virtual void doButtonDownStart_(AnimButton* button);
    virtual void doButtonDownEnd_(AnimButton* button);
    virtual void doButtonCancelStart_(AnimButton* button);
    virtual void doButtonCancelEnd_(AnimButton* button);
    virtual void* getElinkSystem_() const;
    virtual void* getSlink2ResourceList_(xlink2::UserInstanceSLink* link) const;
    virtual s32 getSlink2LocalPropertyNum_() const;
    virtual void setSlink2PropertyDefinition_(xlink2::UserInstanceSLink* link);
    virtual void updateButton_();
    virtual void updateControl_();
    virtual void openStart_(s32 option);
    virtual bool isOpenEnd_();
    virtual void openEnd_();
    virtual void closeStart_(s32 option);
    virtual bool isCloseEnd_();
    virtual void closeEnd_();
    virtual bool isForceGlbMtxDirty_() const;
    virtual void updateAnimator_();
    virtual void registerController_();
    virtual void unregisterController_();
    virtual void setupPaneAfterBuild_(nn::ui2d::Pane* pane, LayoutEx* layout, u32* count);
    virtual void countEffectLinkPane_(nn::ui2d::Pane* pane, u32* count);
    virtual void createEffectLinkUser_(sead::Heap* heap, u32 count);
    virtual void createSoundLink2User_(sead::Heap* heap);
    virtual void invokeSoundLink2Event_(const char* name);
    virtual void invokeSoundLink2ButtonEvent_(AnimButton* button, const char* name);
    virtual void invokeSoundLink2AnimPlayEvent(Animator* animator, const char* name);

    // 0x7100be9768 / 0x7100be978c / 0x7100be934c / 0x7100be97c4 (CSV; the last two are named
    // Screen::isClosed / isClosedOrClosing there)
    bool isOpened() const;
    bool isOpening() const;
    bool isClosed() const;
    bool isClosedOrClosing() const;

    // 0x7100be99d4
    DrawTarget getDrawTarget() const;
    // 0x7100be97f4
    s32 getViewerType() const;
    // 0x7100be9da4
    f32 getOpenFrameSize() const;
    // 0x7100be9880
    void setOwnInitializeHeap(bool own);
    bool isOwnInitializeHeap() const { return _107 & 1; }
    sead::Heap* getInitializeHeap() const { return mInitializeHeap; }
    s32 getId() const { return mId; }
    bool hasFlag4() const { return _107 & 4; }

    // 0x7100be9830 / 0x7100be9850 (placeholder names): link / unlink an animator in `mAnimators`
    void addAnimator(Animator* animator);
    void removeAnimator(Animator* animator);

    // 0x7100be9908
    bool moveBoxCursorByButton(const AnimButton* button);
    // 0x7100be9f60 (placeholder name)
    u8 sub_7100BE9F60() const;
    // 0x7100be989c
    void eraseBoxCursorNodeFromRouteNodes(const BoxCursorNode* node);
    // 0x7100beb570: the box cursor node whose button has the tag (null if none)
    BoxCursorNode* findBoxCursorNodeByTag(s32 tag);
    // 0x7100be9a04: name is a guess; the same lookup also appears inlined in cursor consumers.
    BoxCursorNode* findBoxCursorNodeByButton(const AnimButton* button);
    // 0x7100beb518 / 0x7100beb520 / 0x7100beb5bc (placeholder names)
    void setReservedBoxCursorNode(BoxCursorNode* node);
    void setReservedBoxCursorNodeByTag(s32 tag);
    void setReservedBoxCursorNodeByButton(const AnimButton* button);
    // 0x7100beaf98 / 0x7100beb608 / 0x7100beb624 / 0x7100beb690 (non-virtual helpers; names from the CSV)
    nn::ui2d::Pane* findPane_(const char* name);
    LayoutEx* sub_7100BEAFB0(const char* name);
    void x_2();
    ControlBase* findControlWithParentLayout_(const char* name, const LayoutEx* layout);
    ControlBase* findControlWithLayout_(const char* name, const LayoutEx* layout);
    void moveBoxCursor_(BoxCursorNode* node);
    void moveBoxCursorByTag_(s32 tag);
    void moveBoxCursorByButton_(const AnimButton* button);
    // 0x7100be9fa8 (the old / new button states are ButtonBase::State values)
    void buttonStateChangeCallback(AnimButton* button, ButtonBase::State old_state, ButtonBase::State new_state);

    /* 0x28 */ ScreenMgr* mMgr = nullptr;
    /* 0x30 */ LayoutEx* mLayout = nullptr;
    /* 0x38 */ ButtonGroup* mButtonGroup = nullptr;
    /* 0x40 */ ListNode mControls;  // the screen's controls (ControlBase::_8 nodes); updated by updateControl_
    /* 0x50 */ ListNode _50;
    /* 0x60 */ UIController* mUIController = nullptr;
    /* 0x68 */ DrawInfoEx* mDrawInfo = nullptr;
    /* 0x70 */ TagProcessor* mTagProcessor = nullptr;
    /* 0x78 */ ListNode mAnimators;  // the animators that are playing (Animator::_40 nodes)
    /* 0x88 */ sead::OffsetList<BoxCursorNode> mBoxCursorNodes;  // offset 8 (BoxCursorNode::mNode)
    /* 0xa0 */ ListNode _a0;
    /* 0xb0 */ u64 _b0 = 0;
    /* 0xb8 */ sead::Heap* mInitializeHeap = nullptr;  // destroyed with the screen if it is owned (_107 bit 0)
    /* 0xc0 */ s32 mId = -1;
    /* 0xc8 */ sead::SafeString _c8;
    /* 0xd8 */ BoxCursorNode* _d8 = nullptr;
    /* 0xe0 */ BoxCursorNode* mActiveCursorNode = nullptr;
    /* 0xe8 */ u64 _e8 = 0;
    /* 0xf0 */ void* _f0 = nullptr;  // Sound-user interface pointer; pointee type remains unresolved.
    /* 0xf8 */ f32 _f8 = sead::Mathf::pi() / 4;
    /* 0xfc */ u8 mDrawTarget = 0xff;
    /* 0xfd */ s8 _fd = 0;
    /* 0xfe */ u8 mState = 0;
    /* 0xff */ u8 _ff = 0;
    /* 0x100 */ u8 _100 = 0;
    /* 0x101 */ u8 _101 = 0;
    /* 0x102 */ u8 _102 = 0;
    /* 0x103 */ u8 _103 = 0;
    /* 0x104 */ bool _104 = false;  // read by AnimButton::Build / InactivateByBoxCursor (touch device?)
    /* 0x105 */ u8 _105 = 0;
    /* 0x106 */ u8 _106 = 1;
    /* 0x107 */ u8 _107 = 3;  // bit 0: own initialize heap (setOwnInitializeHeap), bit 2: has a box cursor
};
KSYS_CHECK_SIZE_NX150(Screen, 0x108);

// Unknown object at ScreenMgr + 0x48; slot 5 maps a screen's draw target index to a DrawTarget.
class ScreenTargetMgr {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual DrawTarget getDrawTarget(u8 index) const;
};

// The screen manager singleton (CSV: eui::ScreenMgr::*, sInstance 0x71025fcc68). The table of loaded
// screens is a sead::Buffer (count at 0x28, pointer at 0x30) indexed by the screen id of
// uking::ui::ScreenFactory::create.
class ScreenMgr {
    SEAD_SINGLETON_DISPOSER(ScreenMgr)
    ScreenMgr();

public:
    virtual ~ScreenMgr();

    Screen* getScreen(s32 id) { return mScreens[id]; }
    f32 getAnimationStep() const { return mAnimationStep; }
    ArcResourceMgr* getArcResourceMgr() const { return mArcResourceMgr; }
    BoxCursorMgr* getBoxCursorMgr() const { return mBoxCursorMgr; }
    MessageMgr* getMessageMgr() const { return mMessageMgr; }
    FontMgr* getFontMgr() const { return mFontMgr; }
    const void* getMultiFilterParameterData(const sead::SafeString& path) const;
    // inline-only in the original; name is a guess (the draw target byte is loaded before the target manager)
    u8 getTargetFlag(u8 target_index) { return mTargetFlags[mTargetMgr->getDrawTarget(target_index)]; }
    ScreenTargetMgr* getTargetMgr() const { return mTargetMgr; }

    // 0x7100bec794 / 0x7100bec724 / 0x7100bec7e8 / 0x7100bec808
    void resetScreenId(s32 id);
    void unloadScreen(s32 id);
    void inactivateScreen(s32 id);
    void activateScreen(s32 id);
    // 0x7100bec4c0 / 0x7100bec534 / 0x7100bec690
    void update();
    void updateScreenAll();
    void draw(s8 target, const DrawInfoEx::RenderBufferInfo* info);
    // 0x7100bec840
    void eraseBoxCursorNodeFromRouteNodes(const BoxCursorNode* node);

private:
    // The singleton disposer is at 0x8 (CSV: createInstance 0x7100bec0a4, object size 0xb50).
    sead::Buffer<Screen*> mScreens;
    /* 0x38 */ sead::Buffer<s8> mScreenTargets;  // draw target of each screen (-1: inactive)
    /* 0x48 */ ScreenTargetMgr* mTargetMgr;
    u8 _50[0xb10 - 0x50];  // 0x50: nn::ui2d::GraphicsResource, 0xb08: unknown object, SharcArchive at 0xb28
    /* 0xb10 */ ArcResourceMgr* mArcResourceMgr;
    /* 0xb18 */ BoxCursorMgr* mBoxCursorMgr;
    /* 0xb20 */ f32 mAnimationStep;
    u8 _b24[4];
    /* 0xb28 */ SharcArchive mMultiFilterArchive;
    /* 0xb30 */ MessageMgr* mMessageMgr;
    /* 0xb38 */ FontMgr* mFontMgr;
    /* 0xb40 */ sead::SafeArray<u8, 2> mTargetFlags;  // indexed by DrawTarget (read by Screen::sub_7100BE9F60)
    u8 _b42[0xb48 - 0xb42];
    /* 0xb48 */ ConstantBuffer* mConstantBuffer;
};

}  // namespace eui
