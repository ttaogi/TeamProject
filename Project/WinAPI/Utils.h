#pragma once
//=================================================================
// # Utils # (����ȭ ��Ű�� ���� ����, Ȥ�� ������ ��ɵ��� ��Ƶ� ��)
//=================================================================

// ��׸� 1���� ���� ��
#define DEG_TO_RAD		0.017453f
#define PI				3.141592653f
// #define PI_2 (PI * 2) = �Ҽ����� ������ ���� �ϴ¹�ĺ��� ���� ���� ����� �ִ°� ������ �Ȼ����
#define PI_2			6.283185308f

/*
�ε��Ҽ��� -> �Ǽ��� ��Ȯ�� ǥ���� �� �ִ�? / ����? (����!)
why -> �Ǽ��� ���������� �����ϴ� -> ������ �Ǽ��� ������ ��Ʈ�� ǥ���Ϸ��� �ϴϱ�
�� ��ǻ�ʹ� ��¿�� ���� �ٻ簪���� ǥ���Ѵ�.
�� �ٻ簪�� �� ���� ���� Rounding Error
2D���� ����� ũ�� �ν��� �������� 3D��ǥ�� ���� ���� �ٸ� ����� �߻��Ѵ�.
*/

// ���� + ���п� ������ �۽Ƿ�
#define FLOAT_EPSILON	0.001f

//�Ǽ��� ���������� ��ȯ
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)

//�νǼ��� ������ ��
//�� fabs�� �Ҽ��� ���� ���밪 ��ȯ (abs -> int)
#define FLOAT_EQUAL(f1, f2) (fabs(f1 -f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	//���������� �Ÿ��� ���Ѵ�
	float getDistance(float startX, float startY, float endX, float endY);
	//Start���� End������ ���� �������� ���Ѵ�.
	float getAngle(float startX, float startY, float endX, float endY);
}

