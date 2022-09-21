#include"shapes.h"
#include"Object.h"
/// <summary>
/// �����`��`��
/// </summary>
/// <param name="pos">�����`�̍���̍��W</param>
/// <param name="size">�����`�̑傫��</param>
/// <param name="col">�`��F</param>
void DrawRec(Vector2<int> pos, Vector2<int> size, Color col)
{
	SetAlpha(col.A);
	DrawLineBox(pos.x, pos.y, size.x, size.y, col.convert());
	EndAlpha();
}

/// <summary>
/// �ȉ~��`��
/// </summary>
/// <param name="pos">���S���W</param>
/// <param name="a">x�������̔��a</param>
/// <param name="b">y�������̔��a</param>
/// <param name="col">�`��F</param>
void DrawEllipse(Vector2<int> pos, int a, int b, Color col)
{
	SetAlpha(col.A);
	DrawOval(pos.x, pos.y, a, b, col.convert(), false);
	EndAlpha();
}

/// <summary>
/// �~��`��
/// </summary>
/// <param name="pos">���S���W</param>
/// <param name="radius">���a</param>
/// <param name="col">�`��F</param>
void DrawCircle(Vector2<int> pos, int radius, Color col)
{
	SetAlpha(col.A);
	DxLib::DrawCircle(pos.x, pos.y, radius, col.convert(), false);
	EndAlpha();
}

/// <summary>
/// �֐���`��
/// </summary>
/// <param name="_F">�`�悷��֐�(�}��ϐ��\��)</param>
/// <param name="tmin">�}��ϐ��̍ŏ��l</param>
/// <param name="tmax">�}��ϐ��̍ő�l</param>
/// <param name="col">�`��F</param>
void DrawFunc(std::function<Vector2<float>(int)> _F, int tmin, int tmax, Color col)
{
	if (tmin >= tmax)return;
	SetAlpha(col.A);
	Vector2<float> x = _F(tmin) + Vector2<float>(0.5, 0.5);
	Vector2<int> prev = { (int)x.x,(int)x.y };
	for (int t = tmin + 1; t <= tmax; ++t)
	{
		auto tmp = _F(t) + Vector2<float>(0.5f, 0.5f);
		DrawLine(prev.x, prev.y, (int)tmp.x, (int)tmp.y, col.convert());
		prev = { (int)(tmp.x),(int)(tmp.y) };
	}
	EndAlpha();
}