#include "Stdafx/stdafx.h"

#include "CommonMacroFunction.h"
#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

MonoBehaviour* IsDerivedFromMonoBehaviour(Component* _c)
{
	return dynamic_cast<MonoBehaviour*>(_c);
}
