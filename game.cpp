
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<string>
#include <conio.h>
#include "windows.h" // thu vi?n n�y b� d?o l?m nh� - ch?a nhi?u d? choi nek - c? t�m hi?u d?n d?n s
//======= l?y t?a d? x c?a con tr? hi?n t?i =============
#define KEY_NONE	-1
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= l?y t?a d? y c?a con tr? hi?n t?i =======
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//============== d?ch con tr? hi?n t?i d?n di?m c� t?a d? (x,y) ==========
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= d?t m�u cho ch? =========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== l�m ?n tr? chu?t ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= tr? v? m� ph�m ngu?i d�ng b?m =========
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}

	return KEY_NONE;
}

using namespace std;
void VeTuongTren();
void VeTuongDuoi();
void VeTuongTrai();
void VeTuongPhai();
void VeTuong()
{
	VeTuongTren();
	VeTuongDuoi();
	VeTuongTrai();
	VeTuongPhai();
}
class Snack
{
private:
	/*M?ng di?m*/
	int x[100]; // t?a d? 100 di?m x
	int y[100]; // t?a d? 100 di?m y;
	int soluong = 4;
public:
	void KhoiTaoSnack();
	void VeSnack();
	int Get_SoLuong();
	void Set_SoLuong();
	void Set_SoLuongGiam();
	void ThemViTriDau(int x,int y);
	void XuLiRan(int x,int y,int a,int b);
	void XoaViTriCuoi(int vitri);
	void XoaDuLieuCu();
	void DiChuyen(int &x,int &y,int &check);
	bool RanChamBien(int x, int y);
	bool RanChamThan(int x, int y);
	bool GameOver(int x, int y);
	void RanDomThucAn(int &x,int &y);
	bool KiemTraQuaNamTrungSnack(int tdx,int tdy);
	int Get_X0()
	{
		return this->x[0];
	}
	int Get_Y0()
	{
		return this->y[0];
	}
};
struct NguoiChoi
{
	string name;
	int point;
};
typedef struct NguoiChoi NguoiChoi;
void ChoiGame(vector <NguoiChoi> &ng)
{
	Snack a;
	NguoiChoi nv;
	cout << "\nNhap Ten: "; getchar(); getline(cin, nv.name);
	system("cls");
	VeTuong();
	a.KhoiTaoSnack();
	int thucanx;
	int thucany;
	SetColor(4);
	a.RanDomThucAn(thucanx, thucany);
	int x = 45, y = 12; // 2 t?a d? ban d?u c?a con r?n
	int check = 4; // r?n ch?m bi�n tr�i v� di qua ph?i th� x++;
	/*
	check = 1;     // r?n ch?m bi�n tr�n v� di xu?ng th� y++;
	check = 2;     // r?n ch?m bi�n du?i v� di l�n th� y--;
	check = 3;     // r?n ch?m bi�n ph?i v� di tr�i th� x--;
	check = 4;     // r?n ch?m bi�n tr�i v� di ph?i th� x++;
	*/
	while (true)
	{
		a.DiChuyen(x, y, check);
		a.XoaDuLieuCu();
		a.XuLiRan(x, y, thucanx, thucany);
		if (a.Get_X0() == thucanx && a.Get_Y0() == thucany)
		{
			a.Set_SoLuong();
			a.RanDomThucAn(thucanx, thucany);
		}
		if (a.GameOver(x, y) == true)
		{
			system("cls");
			SetColor(7);
			gotoXY(47, 12);
			cout << "Yeu TT";
			gotoXY(45, 13);
			cout << "Ban duoc " << a.Get_SoLuong()  << " diem";
			gotoXY(35, 14);
			cout << "Vui long nhap phim bat ki de tiep tuc";
			nv.point = a.Get_SoLuong();
			ng.push_back(nv);
			return;
		}
		Sleep(10);
	}
}
void Swap(NguoiChoi& a, NguoiChoi& b);
void SapXepGiamDan(vector<NguoiChoi> &ng);
void KiLuc(vector<NguoiChoi> &ng);
int main()
{
	vector <NguoiChoi> ng;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\t========== MENU ==========";
		cout << "\n\t\t\t      1. Choi game";
		cout << "\n\t\t\t      2. Ki luc";
		cout << "\n\t\t\t      0. Thoat";
		cout << "\n\t\t\t========== END  ==========";
		int i;
		cout << "\n\t\t\t\tLua chon: "; cin >> i;
		if (i < 0 || i>2)
		{
			cout << "\nKhong co lua chon nay";
		}
		else if (i == 1)
		{
			system("cls");
			ChoiGame(ng);
			_getch();
		}
		else if (i == 2)
		{
			KiLuc(ng);
			_getch();
		}
		else
		{
			return 0;
		}
	}
}
void VeTuongTren()
{
	for (int i = 2; i <= 100; i++)
	{
		gotoXY(i, 1);
		SetColor(1);
		cout << "+";
	}
}
void VeTuongDuoi()
{
	for (int i = 2; i <= 100; i++)
	{
		gotoXY(i, 26);
		SetColor(1);
		cout << "+";
	}
}
void VeTuongTrai()
{
	for (int i = 1; i <= 26; i++)
	{
		gotoXY(10, i);
		SetColor(1);
		cout << "+";
	}
}
void VeTuongPhai()
{
	for (int i = 1; i <= 26; i++)
	{
		SetColor(1);
		gotoXY(100, i);
		cout << "+";
	}
}
void Snack::KhoiTaoSnack()
{
	int x = 50;
	int y = 13;
	for (int i = 0; i < this->Get_SoLuong(); i++)
	{
		this->x[i] = x;
		this->y[i] = y;
		x--;
	}
}
void Snack::VeSnack()
{
	for (int i = 0; i < this->Get_SoLuong(); i++)
	{
		gotoXY(this->x[i], this->y[i]);
		if (i == 0)
		{
			SetColor(14);
			cout << "O";
		}
		else
		{
			SetColor(14);
			cout << "o";
		}
	}
}
int Snack::Get_SoLuong()
{
	return this->soluong;
}
void Snack::Set_SoLuong()
{
	this->soluong++;
}
void Snack::XoaDuLieuCu()
{
	for (int i = 0; i < this->Get_SoLuong(); i++)
	{
		gotoXY(this->x[i], this->y[i]);
		cout << " ";
	}
}
void Snack::XuLiRan(int x,int y,int thucanx,int thucany)
{
	// theem toa do moi vao dau mang
	this->ThemViTriDau(x, y);
	// x�a v? tr� cu?i m?ng
	this->XoaViTriCuoi(this->Get_SoLuong() - 1);
	this->VeSnack();
}
void Snack::ThemViTriDau(int x,int y)
{
	for (int i = this->Get_SoLuong(); i > 0; i--)
	{
		this->x[i] = this->x[i - 1];
		this->y[i] = this->y[i - 1];
	}
	this->x[0] = x;
	this->y[0] = y;
	this->Set_SoLuong();
}
void Snack::XoaViTriCuoi(int vitri)
{
	for (int i = vitri; i < this->Get_SoLuong(); i++)
	{
		this->x[i] = x[i + 1];
		this->y[i] = y[i + 1];
	}
	this->Set_SoLuongGiam();
}
void Snack::Set_SoLuongGiam()
{
	this->soluong--;
}
void Snack::DiChuyen(int& x, int& y, int& check)
{
	if (_kbhit())
	{
		char kitu = _getch();
		if (kitu == -32)
		{
			kitu = _getch();
			if (kitu == 72 && check != 1) // di l�n l� ch?m bi�n du?i 
			{
				check = 2;
			}
			else if (kitu == 80 && check != 2) // di xu?ng l� ch?m bi�n tr�n
			{
				check = 1;
			}
			else if (kitu == 77 && check != 3) // di ph?i ch?m bi�n tr�i
			{
				check = 4;
			}
			else if (kitu == 75 && check != 4) // di tr�i ch?m ph?i
			{
				check = 3;
			}
		}
	}
	if (check == 1)
	{
		y++;
	}
	else if (check == 2)
	{
		y--;
	}
	else if (check == 3)
	{
		x--;
	}
	else if (check == 4)
	{
		x++;
	}
}
bool Snack::RanChamBien(int x, int y)
{
	/*Ch?m bi�n tr�n*/
	if ((x >= 10 && x <= 100) && y == 1)
	{
		return true;
	}
	/*Ch?m bi�n du?i*/
	else if ((x >= 10 && x <= 100) && y == 26)
	{
		return true;
	}
	/*Ch?m bi�n tr�i*/
	else if ((y >= 1 && y <= 26) && x == 10)
	{
		return true;
	}
	/*Ch?m bi�n ph?i*/
	else if ((y >= 1 && y <= 26) && x == 100)
	{
		return true;
	}
	return false;
}
bool Snack::RanChamThan(int x = 0, int y = 0)
{
	for (int i = 1; i < this->Get_SoLuong(); i++)
	{
		if (this->x[i] == x && this->y[i] == y)
		{
			return true;
		}
	}
	return false;
}
bool Snack::GameOver(int x, int y)
{
	if (this->RanChamBien(x, y) == true)
	{
		return true;
	}
	else if (this->RanChamThan(x, y) == true)
	{
		return true;
	}
	return false;
}
void Snack::RanDomThucAn(int &x,int &y)
{
	int thucanx, thucany;
	do
	{
		srand(time(NULL));
		thucanx = rand() % (99 - 11 + 1) + 11;
		thucany = rand() % (25 - 2 + 1) + 2;
		gotoXY(thucanx, thucany);
		SetColor(4);
		cout << "T";
	} while (this->KiemTraQuaNamTrungSnack(thucanx, thucany) == true);
	x = thucanx;
	y = thucany;
}
bool Snack::KiemTraQuaNamTrungSnack(int tdx,int tdy)
{
	for (int i = 0; i < this->Get_SoLuong(); i++)
	{
		if (this->x[i] == tdx && this->y[i] == tdy)
		{
			return true;
		}
	}
	return false;
}
void Swap(NguoiChoi& a, NguoiChoi& b)
{
	NguoiChoi temp = a;
	a = b;
	b = temp;
}
void SapXepGiamDan(vector<NguoiChoi> &ng)
{
	for (int i = 0; i < ng.size() - 1; i++)
	{
		for (int j = i + 1; j < ng.size(); j++)
		{
			if (ng[i].point < ng[j].point)
			{
				Swap(ng[i], ng[j]);
			}
		}
	}
}
void KiLuc(vector<NguoiChoi> &ng)
{
	SapXepGiamDan(ng);
	cout << "\n\t\t\t ============== Danh sach nguoi choi ==============";
	for (int i = 0; i < ng.size(); i++)
	{cout << "\n\t\t\tNguoi choi co diem so cao thu " << i + 1 << "";
		cout << "\n\t\t\tHo va ten: " << ng[i].name;
		cout << "\n\t\t\tDiem: " << ng[i].point << endl;
	}
}
