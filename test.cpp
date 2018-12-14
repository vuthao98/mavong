#include <iostream>
using namespace std;
typedef struct dathuc DT;
struct dathuc
{
	int bac;
	double *heso;
};
std::istream& operator >> (std::istream &is, DT *x)
{
	do
	{
		std::cout << "\nNhap so bac cua da thuc: ";
		is >> x->bac;
		if (x->bac < 1)
			std::cout << "\nSo bac cua da thuc khong hop le.\n";
	} while (x->bac < 1);
	std::cout << "\nNhap cac he so (an -> a0):\n";
	x->heso = new double[x->bac + 1];
	for (int i = x->bac; i >= 0; --i)
	{
		std::cout << "\nHe so a" << i << ": ";
		is >> x->heso[i];
	}
	return is;
}
std::ostream& operator << (std::ostream &os, DT *x)
{
	int count = 0;
	for (int i = x->bac; i >= 0; ++i, ++count)
	{
		os << x->heso[i];
	}
	os << std::endl;
	return os;
}
DT* TimxR(DT *a)
{
	DT *xR = new DT;
	xR->bac = a->bac;
	xR->heso = new double [xR->bac+1];
	for (int i =0; i<= xR->bac;++i)
		{
			xR->heso[i] = 0;
		}
	xR->heso[xR->bac]=1;
	return xR;
}
DT* Tong2DaThuc(DT *x, DT *y)
{
	int Max = x->bac > y->bac ? x->bac : y->bac;
	int Min = x->bac < y->bac ? x->bac : y->bac;
	DT *kq = new DT;
	kq->bac = Max;
	kq->heso = new double[kq->bac + 1];
	for (int i = 0; i <= Min; ++i)
	{
		if (x->heso[i] == y->heso[i])
		{
			kq->heso[i] = 0;
		}
		else
		{
			kq->heso[i] = x->heso[i] + y->heso[i];
		}
	}
	if (Max == x->bac)
	{
		for (int i = Min + 1; i <= Max; ++i)
		{
			kq->heso[i] = x->heso[i];
		}
	}
	else
	{
		for (int i = Min + 1; i <= Max; ++i)
		{
			kq->heso[i] = y->heso[i];
		}
	}
	return kq;
}
DT* Tich2DaThuc(DT *x, DT *y, int n)
{
	DT *kq = new DT;
	DT *kqMaVong = new DT;
	kq->bac = (x->bac + y->bac);
	kqMaVong->bac = n;
	kq->heso = new double[kq->bac+1];
	kqMaVong->heso = new double[kqMaVong->bac+1];
	for (int i =0; i<= kq->bac;++i)
	{
		kq->heso[i] = 0;
	}
	for (int i =0; i<= kqMaVong->bac;++i)
	{
		kqMaVong->heso[i] = 0;
	}
	for (int i = 0;i <= x->bac;++i)
	{
		for (int j =0;j <= y->bac;++j)
		{
			if (kq->heso[i+j] == x->heso[i]*y->heso[j])
			{
				kq->heso[i+j] = 0;
			}
			else
			{
				kq->heso[i+j] += x->heso[i]*y->heso[j];
			}
		}
	}
	for (int i =0; i<=kq->bac; ++i)
	{
		if (kqMaVong->heso[i%n] == kq->heso[i%n])
		{
			kqMaVong->heso[i%n] = 0;
		}
		else
		{
			kqMaVong->heso[i%n] += kq->heso[i%n];
		}
	}
	return kq;
}
DT* PhanDu2DaThuc(DT *a, DT *b)
{
	if (a->bac<b->bac)
	{
		return a;
	}
	else
	{
		int n = 10;
		int z,x;
		DT *c = new DT;
		//DT *xR = new DT;
		DT *kq = new DT;
		DT *du = new DT;
		int small = b->bac;
		//xR->bac = b->bac -1;
		//xR->heso = new double [xR->bac+1];
		kq->heso = new double [kq->bac+1];
		/*for (int i =0; i<= xR->bac;++i)
		{
			xR->heso[i] = 0;
		}
		xR->heso[xR->bac]=1;*/
		int big = Tich2DaThuc(a,TimxR(b),n)->bac;
		kq->bac = big - small;
		du->bac = big;
		du->heso = new double [big+1];
		for (int i = 0; i<= big;++i)
		{
			du->heso[i] = Tich2DaThuc(a,TimxR(b),n)->heso[i];
		}
		for (int i =0; i<= kq->bac;++i)
		{
			kq->heso[i] = 0;
		}
		if (big == small) {kq->heso[kq->bac+1]= Tich2DaThuc(a,TimxR(b),n)->heso[big]/b->heso[small];}
		else 
		{
			x = big;
			z = big - small;
			while (z>=0)
			{
				kq->heso[z] = du->heso[x]/b->heso[small];
				int y = small;
				for (int i = x;i>=x-small;--i)
				{
					if (du->heso[i] == kq->heso[z]*b->heso[y])
					{
						du->heso[i] = 0;
					}
					else
					{
						du->heso[i] = du->heso[i] + kq->heso[z]*b->heso[y];
					}
					y--;
				}
				x--;
				z--;
			}
		}
		int d = 0;
		for (int i = du->bac; i>=0; --i)
		{
			if (du->heso[i] == 0)
			{
				d++;
			}
			else {break;}
		}
		du->bac = du->bac - d;
		return du;
	}
}
int main()
{
	int n = 2;
	DT *x = new DT;
	std::cout << "\n\t------------ NHAP Q(x) ------------\t\n";
	std::cin >> x;
	std::cout << x;
	DT *y = new DT;
	std::cout << "\n\t------------ NHAP G(x) ------------\t\n";
	std::cin >> y;
	std::cout << y;
	std::cout << "\n\t----------------------------------------\t\n";
	std::cout << "\nTong 2 da thuc tren: " << Tong2DaThuc(x, y) << std::endl;
	std::cout << "\nP(x) Khong He Thong: " << Tich2DaThuc(x, y, n) << std::endl;
	std::cout << "\nR(x): " << PhanDu2DaThuc(x, y) << std::endl;

	std::cout << "\nP(x) Co He Thong: " << Tong2DaThuc(Tich2DaThuc(TimxR(y),x,n),PhanDu2DaThuc(x,y)) << std::endl;
	return 0;
}
