#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"
#include "RenderedImage.h"

RenderedImage::RenderedImage()
	: Component((const Component_ID)typeid(RenderedImage).name())
{
	image = NULL;
}

RenderedImage::~RenderedImage() { }

void RenderedImage::Operation() { }

void RenderedImage::Render(HDC _hdc)
{
	if (enabled && image) {
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		RECT rc = rcT->GetScreenRect();
		image->Render(_hdc, rc.left, rc.top);
	}
}
