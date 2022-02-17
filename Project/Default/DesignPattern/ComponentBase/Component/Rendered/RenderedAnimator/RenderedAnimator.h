#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"
#include "Image/Animator/Animator.h"

class RenderedAnimator : public Rendered, public MonoBehaviour {
private:
	Animator* animator;

	virtual void Render(HDC _hdc) override { };
protected:
public:
	RenderedAnimator();
	virtual ~RenderedAnimator();

	virtual void Operation() override;

	void Render(HDC _hdc, POINT _pos);
	void Init();
	void Update(HWND _hWnd);
	void LateUpdate();

	void AddAnimation(CHARACTER_STATE _state, Animation* _animation);
	bool ChangeAnimation(CHARACTER_STATE _state);
	bool IsEnd() const;
	bool IsPlay() const;

	void AniStart();
	void AniStop();
	void AniPause();
	void AniResume();
};