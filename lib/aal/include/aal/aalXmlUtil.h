#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace sead {
class Heap;
class XmlDocument;
class XmlElement;
}

namespace aal {
class XmlUtil {
public:
    static sead::XmlDocument* createTextDocument(void* data, u32 size, sead::Heap* heap);
    static sead::SafeString getElementContentString(sead::XmlElement* element,
                                                  const sead::SafeString& path);
};
}  // namespace aal
