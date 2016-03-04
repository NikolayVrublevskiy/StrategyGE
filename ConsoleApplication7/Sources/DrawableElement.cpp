#include "../Headers/DrawableElement.h"
#include <vector>


DrawableElement::DrawableElement()
: m_indicesCount(0),
m_VBO(0),
m_IBO(0),
m_verticiesCount(0),
m_isInited(false)
{
}

DrawableElement::~DrawableElement()
{
}
