#include <string>

#include "dialog.h"

const unsigned DIALOG::max_amount = 255;
const float DIALOG::max_radius = 1;
const float DIALOG::max_mass = 100;
const float DIALOG::max_speed = 10;
const float DIALOG::max_dist_from_center = 10;
const float DIALOG::max_G = 10;
const float DIALOG::max_shell_size = 10;
const float DIALOG::max_horizontal_rotation_speed = 100;

bool DIALOG::UnsignedLimiter(char buffer[5]) noexcept
{
	for (unsigned i = 0; i < 5; i++)
		if (buffer[i] && (buffer[i] < '0' || buffer[i] > '9'))
			return true;

	return false;
}
bool DIALOG::FloatLimiter(char buffer[5]) noexcept
{
	for (unsigned i = 0; i < 5; i++)
		if (buffer[i] && (buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '.' && buffer[i] != '-')
			return true;

	return false;
}

void DIALOG::MassMode(HWND hwnd, const SCENE_PROPERTIES* sp) noexcept
{
	CheckDlgButton(hwnd, CTRL_CB_1, sp->mass_radius_equivalent);
	EnableWindow(GetDlgItem(hwnd, CTRL_EDIT_4), !sp->mass_radius_equivalent);
	EnableWindow(GetDlgItem(hwnd, CTRL_EDIT_5), !sp->mass_radius_equivalent);
}
void DIALOG::AnimMode(HWND hwnd, const SCENE_PROPERTIES* sp) noexcept
{
	CheckDlgButton(hwnd, CTRL_ST_ATOM, sp->sm == SM_ATOM);
	CheckDlgButton(hwnd, CTRL_ST_SHELL, sp->sm == SM_SHELL);

	EnableWindow(GetDlgItem(hwnd, CTRL_EDIT_8), sp->sm == SM_ATOM);
	EnableWindow(GetDlgItem(hwnd, CTRL_EDIT_9), sp->sm == SM_ATOM);
	EnableWindow(GetDlgItem(hwnd, CTRL_CB_2), sp->sm == SM_ATOM);

	EnableWindow(GetDlgItem(hwnd, CTRL_EDIT_A), sp->sm == SM_SHELL);
	EnableWindow(GetDlgItem(hwnd, CTRL_EDIT_B), sp->sm == SM_SHELL);
}
void DIALOG::InitiateSettingsControlStates(HWND hwnd, const SCENE_PROPERTIES* sp) noexcept
{
	using namespace std;

	const int limit = 4;

	string buffer;
	buffer = to_string(sp->amount);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_1, buffer.c_str());

	buffer = to_string(sp->radius_min);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_2, buffer.c_str());

	buffer = to_string(sp->radius_max);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_3, buffer.c_str());

	buffer = to_string(sp->mass_min);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_4, buffer.c_str());

	buffer = to_string(sp->mass_max);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_5, buffer.c_str());

	buffer = to_string(sp->speed_min);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_6, buffer.c_str());

	buffer = to_string(sp->speed_max);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_7, buffer.c_str());

	MassMode(hwnd, sp);

	buffer = to_string(sp->dist_from_center);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_8, buffer.c_str());

	buffer = to_string(sp->G);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_9, buffer.c_str());

	CheckDlgButton(hwnd, CTRL_CB_2, sp->center_balls);

	buffer = to_string(sp->shell_size);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_A, buffer.c_str());

	buffer = to_string(sp->shell_fill_factor);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_B, buffer.c_str());

	buffer = to_string(sp->horizontal_rotation_speed);
	buffer.resize(limit);
	SetDlgItemText(hwnd, CTRL_EDIT_C, buffer.c_str());

	AnimMode(hwnd, sp);
}
void DIALOG::CtrlEdit1(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_1), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_1, buffer, 5);

		if (UnsignedLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_1));
		else
		{
			unsigned amount = static_cast<unsigned>(atoi(buffer));

			if (amount > DIALOG::max_amount)
			{
				MessageBox(hwnd, "Liczba kulek musi byæ z zakresu 0-255.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_1));
			}
			else sp->amount = amount;
		}
	}
	}
}
void DIALOG::CtrlEdit2(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_2), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_2, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_2));
		else
		{
			float radius_min = static_cast<float>(atof(buffer));

			if (radius_min < sp->shell_fill_factor || sp->radius_max < radius_min)
			{
				MessageBox(hwnd, "Dolny zakres promienia kulki nie mo¿e byæ wiêkszy od górnego oraz nie mo¿e byæ mniejszy od marginesu œcian pow³oki.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_2));
			}
			else  sp->radius_min = radius_min;
		}
	}
	}
}
void DIALOG::CtrlEdit3(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_3), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_3, buffer, 5);
		
		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_3));
		else
		{
			float radius_max = static_cast<float>(atof(buffer));

			if (radius_max < sp->radius_min || DIALOG::max_radius < radius_max)
			{
				MessageBox(hwnd, "Górny zakres promienia kulki nie mo¿e byæ mniejszy od dolnego oraz nie mo¿e byæ wiêkszy od 1.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_3));
			}
			else  sp->radius_max = radius_max;
		}
	}
	}
}
void DIALOG::CtrlEdit4(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_4), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_4, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_4));
		else
		{
			float mass_min = static_cast<float>(atof(buffer));

			if (mass_min <= 0 || sp->mass_max < mass_min)
			{
				MessageBox(hwnd, "Dolny zakres masy kulki musi byæ dodatni i nie mo¿e byæ wiêkszy od górnego.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_4));
			}
			else sp->mass_min = mass_min;
		}
	}
	}
}
void DIALOG::CtrlEdit5(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_5), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_5, buffer, 5);
		
		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_5));
		else
		{
			float mass_max = static_cast<float>(atof(buffer));

			if (mass_max < sp->mass_min || DIALOG::max_mass < mass_max)
			{
				MessageBox(hwnd, "Górny zakres masy kulki nie mo¿e byæ mniejszy od dolnego i nie mo¿e byæ wiêkszy od 100.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_5));
			}
			else sp->mass_max = mass_max;
		}
	}
	}
}
void DIALOG::CtrlEdit6(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_6), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_6, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_6));
		else
		{
			float speed_min = static_cast<float>(atof(buffer));

			if (speed_min < 0 || sp->speed_max < speed_min)
			{
				MessageBox(hwnd, "Dolny zakres szybkoœci kulki musi byæ nieujemny i nie mo¿e byæ wiêkszy od górnego.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_6));
			}
			else sp->speed_min = speed_min;
		}
	}
	}
}
void DIALOG::CtrlEdit7(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_7), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_7, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_7));
		else
		{
			float speed_max = static_cast<float>(atof(buffer));

			if (speed_max < sp->speed_min || DIALOG::max_speed < speed_max)
			{
				MessageBox(hwnd, "Górny zakres szybkoœci kulki nie mo¿e byæ mniejszy od dolnego i nie mo¿e byæ wiêkszy od 10.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_7));
			}
			else sp->speed_max = speed_max;
		}
	}
	}
}
void DIALOG::CtrlEdit8(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_8), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_8, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_8));
		else
		{
			float dist_from_center = static_cast<float>(atof(buffer));

			if (dist_from_center < 0 || DIALOG::max_dist_from_center < dist_from_center)
			{
				MessageBox(hwnd, "Maksymalna odleg³oœæ pocz¹tkowa od œrodka uk³adu wspó³rzêdnych musi byæ z zakresu 0 - 10.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_8));
			}
			else sp->dist_from_center = dist_from_center;
		}
	}
	}
}
void DIALOG::CtrlEdit9(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_9), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_9, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_9));
		else
		{
			float G = static_cast<float>(atof(buffer));

			if (G < 0 || DIALOG::max_G < G)
			{
				MessageBox(hwnd, "Wartoœæ sta³ej grawitacji (G) musi byæ z zakresu 0 - 10.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_9));
			}
			else sp->G = G;
		}
	}
	}
}
void DIALOG::CtrlEditA(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_A), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_A, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_A));
		else
		{
			float shell_size = static_cast<float>(atof(buffer));

			if (shell_size < 0.0f || DIALOG::max_shell_size < shell_size || shell_size <= sp->radius_max)
			{
				MessageBox(hwnd, "Rozmiar pow³oki musi byæ z zakresu 0 - 10 i musi byæ wiêkszy od górnego zakresu promienia kulki.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_A));
			}
			else sp->shell_size = shell_size;
		}
	}
	}
}
void DIALOG::CtrlEditB(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_B), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_B, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_B));
		else
		{
			float shell_fill_factor = static_cast<float>(atof(buffer));

			if (shell_fill_factor < 0.0f || sp->radius_min < shell_fill_factor)
			{
				MessageBox(hwnd, "Margines œcian pow³oki nie mo¿e byæ ujemny i nie mo¿e byæ wiêkszy od dolnego zakresu promienia kulki.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_B));
			}
			else sp->shell_fill_factor = shell_fill_factor;
		}
	}
	}
}
void DIALOG::CtrlEditC(HWND hwnd, WPARAM wParam, SCENE_PROPERTIES* sp) noexcept
{
	switch(HIWORD(wParam))
	{
	case EN_SETFOCUS:
	{
		PostMessage(GetDlgItem(hwnd, CTRL_EDIT_C), EM_SETSEL, 0, -1);
		break;
	}
	case EN_KILLFOCUS:
	{
		char buffer[5];
		GetDlgItemText(hwnd, CTRL_EDIT_C, buffer, 5);

		if (FloatLimiter(buffer))
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT_C));
		else
		{
			float horizontal_rotation_speed = static_cast<float>(atof(buffer));

			if (horizontal_rotation_speed < -DIALOG::max_horizontal_rotation_speed || DIALOG::max_horizontal_rotation_speed < horizontal_rotation_speed)
			{
				MessageBox(hwnd, "Prêdkoœæ rotacji kamery w poziomie musi byæ z zakresu od -100 do 100.", "B³¹d", MB_OK);
				SetFocus(GetDlgItem(hwnd, CTRL_EDIT_B));
			}
			else sp->horizontal_rotation_speed = horizontal_rotation_speed;
		}
	}
	}
}

BOOL CALLBACK DialogSettingsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static SCENE_PROPERTIES* sp = 0;

	switch(uMsg)
	{
	case WM_INITDIALOG:
	{
		sp = reinterpret_cast<SCENE_PROPERTIES*>(lParam);
		DIALOG::InitiateSettingsControlStates(hwnd, sp);
		break;
	}
	case WM_COMMAND:
	{
		switch(LOWORD(wParam))
		{
		case CTRL_EDIT_1: DIALOG::CtrlEdit1(hwnd, wParam, sp); break;
		case CTRL_EDIT_2: DIALOG::CtrlEdit2(hwnd, wParam, sp); break;
		case CTRL_EDIT_3: DIALOG::CtrlEdit3(hwnd, wParam, sp); break;
		case CTRL_EDIT_4: DIALOG::CtrlEdit4(hwnd, wParam, sp); break;
		case CTRL_EDIT_5: DIALOG::CtrlEdit5(hwnd, wParam, sp); break;
		case CTRL_EDIT_6: DIALOG::CtrlEdit6(hwnd, wParam, sp); break;
		case CTRL_EDIT_7: DIALOG::CtrlEdit7(hwnd, wParam, sp); break;
		case CTRL_EDIT_8: DIALOG::CtrlEdit8(hwnd, wParam, sp); break;
		case CTRL_EDIT_9: DIALOG::CtrlEdit9(hwnd, wParam, sp); break;
		case CTRL_EDIT_A: DIALOG::CtrlEditA(hwnd, wParam, sp); break;
		case CTRL_EDIT_B: DIALOG::CtrlEditB(hwnd, wParam, sp); break;
		case CTRL_EDIT_C: DIALOG::CtrlEditC(hwnd, wParam, sp); break;
		case CTRL_CB_1:
		{
			sp->mass_radius_equivalent = !sp->mass_radius_equivalent;
			DIALOG::MassMode(hwnd, sp);
			break;
		}
		case CTRL_CB_2:
		{
			sp->center_balls = !sp->center_balls;
			CheckDlgButton(hwnd, CTRL_CB_2, sp->center_balls);
			break;
		}
		case CTRL_ST_ATOM:
		{
			sp->sm = SM_ATOM;
			DIALOG::AnimMode(hwnd, sp);
			break;
		}
		case CTRL_ST_SHELL:
		{
			sp->sm = SM_SHELL;
			DIALOG::AnimMode(hwnd, sp);
			break;
		}
		case CTRL_OK:
		{
			EndDialog(hwnd, 1);
			return TRUE;
		}
		case CTRL_CANCEL:
		{
			EndDialog(hwnd, 0);
			return TRUE;
		}
		}
		break;
	}
	}
	return FALSE;
}