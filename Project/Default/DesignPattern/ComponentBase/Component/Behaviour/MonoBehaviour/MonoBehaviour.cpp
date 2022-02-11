#include "Stdafx/stdafx.h"

#include "MonoBehaviour.h"

//bool MonoBehaviour::IsCollided(const RECT* _rc) const {
//	RECT tmpRc;
//	if (IntersectRect(&tmpRc, &rc, _rc) != 0)
//		return true;
//	else
//		return false;
//}
//
//// return value means collision position from this object¡¯s point of view.
//DIRECTION MonoBehaviour::MoveCollisionCheck(RECT* _rc) {
//	RECT tmpRc;
//	POINT tmpPos = pos.ToPoint();
//
//	if (IntersectRect(&tmpRc, &rc, _rc) != 0) {
//		::SetRect(&tmpRc, 0, 0, tmpRc.right - tmpRc.left, tmpRc.bottom - tmpRc.top);
//
//		if (tmpRc.right > tmpRc.bottom) { // vertical collision.
//			if ((rc.top + rc.bottom) < (_rc->top + _rc->bottom)) { // this is upper.
//				tmpPos.y -= (tmpRc.bottom + 1);
//				SetPos(tmpPos);
//				SetRect(MakeRectCWH(tmpPos, rc.right - rc.left, rc.bottom - rc.top));
//				return DIRECTION::BOTTOM;
//			}
//			else { // this is lower.
//				tmpPos.y += (tmpRc.bottom + 1);
//				SetPos(tmpPos);
//				SetRect(MakeRectCWH(tmpPos, rc.right - rc.left, rc.bottom - rc.top));
//				return DIRECTION::TOP;
//			}
//		}
//		else { // horizontal collision.
//			if ((rc.left + rc.right) < (_rc->left + _rc->right)) { // this is left.
//				tmpPos.x -= (tmpRc.right + 1);
//				SetPos(tmpPos);
//				SetRect(MakeRectCWH(tmpPos, rc.right - rc.left, rc.bottom - rc.top));
//				return DIRECTION::RIGHT;
//			}
//			else { // this is right.
//				tmpPos.x += (tmpRc.right + 1);
//				SetPos(tmpPos);
//				SetRect(MakeRectCWH(tmpPos, rc.right - rc.left, rc.bottom - rc.top));
//				return DIRECTION::LEFT;
//			}
//		}
//	}
//
//	return DIRECTION::DIRECTION_NUM;
//}

MonoBehaviour::MonoBehaviour()
	: Component((const Component_ID)typeid(MonoBehaviour).name()) { }

void MonoBehaviour::Operation() { }
