#include "Stdafx/stdafx.h"

#include "CommonMacroFunction.h"
#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

MonoBehaviour* IsDerivedFromMonoBehaviour(Component* _c) {
	return dynamic_cast<MonoBehaviour*>(_c);
	/*if (dynamic_cast<MonoBehaviour*>(_c) == NULL) return false;
	else return true;*/
}
