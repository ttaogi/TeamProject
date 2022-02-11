#pragma once

#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"

class Image;

class RenderedImage : public Rendered
{
private:
	Image* image;
protected:
public:
	RenderedImage();
	virtual ~RenderedImage();

	virtual void Operation() override;

	virtual void Render(HDC _hdc) override;

	Image* GetImage() { return image; }
	void SetImage(Image* _image) { image = _image; }
};
