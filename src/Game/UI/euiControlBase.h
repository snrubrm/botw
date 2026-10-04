#pragma once

#include <basis/seadTypes.h>
#include <nn/font/font_Util.h>

namespace eui {

// Base of the eui controls (buttons, animators' owners, the screens' child components...). Only the first
// vtable slots are known: 0 / 1 are the class name and the nn-style runtime type info, 2 / 3 the destructor.
class ControlBase {
public:
    virtual const char* getClassName() const;
    virtual const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const;
    virtual ~ControlBase();
    virtual void m4();
};

}  // namespace eui
