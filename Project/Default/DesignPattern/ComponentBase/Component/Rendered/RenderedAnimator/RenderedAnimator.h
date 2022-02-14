#pragma once

#include "Image/Animator/Animator.h"
#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"

class RenderedAnimator : public Rendered {
private:
	Animator* animator;

	virtual void Render(HDC _hdc) override { };
protected:
public:
	RenderedAnimator();
	virtual ~RenderedAnimator();

	virtual void Operation() override;

	void Render(HDC _hdc, POINT _pos);

	void AddAnimation(CHARACTER_STATE _state, Animation* _animation);
	bool ChangeAnimation(CHARACTER_STATE _state);
	bool IsEnd() const;
};