#pragma once

#include "Game/UI/uiControlCreator.h"

namespace uking::ui {

// Native tables call these factories with (ControlSrc&, LayoutEx*).
ScreenChild* sub_71009D7198(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009D7294(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009DE3F4(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009DE4F0(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E7F60(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E805C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E8158(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E8254(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E8350(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E844C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17160(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A1725C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17358(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17454(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17550(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A1764C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17748(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17844(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A233EC(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A2C3D8(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A2C4D4(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A32F3C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A33038(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A33134(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A513A4(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A514A0(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A5159C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);

// Native creator vtable 0x71024803b8.
class Unk_71024803b8 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_71024803b8() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x7102480ab0.
class Unk_7102480ab0 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_7102480ab0() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x7102481078.
class Unk_7102481078 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_7102481078() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x7102481828.
class Unk_7102481828 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_7102481828() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x710248d2a8.
class Unk_710248d2a8 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_710248d2a8() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x710248e4e0.
class Unk_710248e4e0 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_710248e4e0() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x710248ea90.
class Unk_710248ea90 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_710248ea90() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x710248f740.
class Unk_710248f740 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_710248f740() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x71024923e0.
class Unk_71024923e0 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_71024923e0() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x71024934f8.
class Unk_71024934f8 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_71024934f8() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x7102496f20.
class Unk_7102496f20 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_7102496f20() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x7102498248.
class Unk_7102498248 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_7102498248() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x7102498858.
class Unk_7102498858 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_7102498858() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

// Native creator vtable 0x7102498e18.
class Unk_7102498e18 : public Unk_7102485000 {
public:
    using Unk_7102485000::Unk_7102485000;
    ~Unk_7102498e18() override;
    const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const override;
};

}  // namespace uking::ui
