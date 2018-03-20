#include "main.h"

using namespace std;

#define MAXEXP	308	
// number of precision for I/O
#define NDIGITS 17

void ierror(char* p)
{
	cout<<"CInterval: "<<p<<endl;
	abort();
}

bool signBit(long double x) // renvoie le signe du double passé en param
{
	return (x<0.0);
}

long double quiet_nan()  // infini
{
	return (NDIGITS * pow(10.0, MAXEXP));
}


CInterval::CInterval(void)
{Bi=0;Bs=0;}

CInterval::CInterval(long double a_Bi, long double a_Bs)
{
	Bi = a_Bi;
	Bs = a_Bs;
	Length = Bs - Bi;
}

CInterval::~CInterval()
{}

void CInterval::Set(long double a_Bi, long double a_Bs)
{
	Bi = a_Bi;
	Bs = a_Bs;
	Length = Bs - Bi;
}

void CInterval::Set_Bi(long double a_bi)
{
	Bi=a_bi;
}

void CInterval::Set_Bs(long double a_bs)
{
	Bs=a_bs;
}

long double CInterval::Get_Bi()
{
	return Bi;
}

long double CInterval::Get_Bs()
{
	return Bs;
}

long double CInterval::Get_Length()
{
	return Bs-Bi;
}

void CInterval::Display()
{
	printf("[%.12f, %.12f]\n", Bi, Bs);
}

int operator >= (long double x, CInterval i)
{
	return(x>=i.Bs);
}

int operator >= (CInterval i, long double x)
{
	return(i.Bi>=x);
}

int operator >= (CInterval i1, CInterval i2)
{
	return(i1.Bi>=i2.Bs);
}

int operator > (long double x, CInterval i)
{
	return(x>i.Bs);
}

int operator > (CInterval i, long double x)
{
	return(i.Bi>x);
}

int operator > (CInterval i1, CInterval i2)
{
	return(i1.Bi>i2.Bs);
}

int operator <= (long double x, CInterval i)
{
	return(x<=i.Bi);
}

int operator <= (CInterval i, long double x)
{
	return(i.Bs<=x);
}

int operator <= (CInterval i1, CInterval i2)
{
	return(i1.Bs<=i2.Bi);
}

int operator < (long double x, CInterval i)
{
	return(x<i.Bi);
}

int operator < (CInterval i, long double x)
{
	return(i.Bs<x);
}

int operator < (CInterval i1, CInterval i2)
{
	return(i1.Bs<i2.Bi);
}

int operator == (long double x, CInterval i)
{
	return ((i.Bi== x) && (i.Bs == x));
}

int operator == (CInterval i, long double x)
{
	return ((i.Bi == x) && (i.Bs == x));
}

int operator == (CInterval i1, CInterval i2)
{
	return ((i1.Bi == i2.Bi) && (i1.Bs == i2.Bs));
}

int operator & (long double x, CInterval i)
{
	return ((x>=i.Bi) && (x<=i.Bs));
}

int operator & (CInterval i, long double x)
{
	return ((x>=i.Bi) && (x<=i.Bs));
}

CInterval operator + (long double x, CInterval i)
{
	return CInterval(i.Bi +x, i.Bs+x);
}

CInterval operator + (CInterval i, long double x)
{
	return CInterval(i.Bi +x, i.Bs+x);
}

CInterval operator + (CInterval i1, CInterval i2)
{
	return CInterval(i1.Bi+i2.Bi, i1.Bs+i2.Bs);
}

CInterval operator - (CInterval i)
{
	return CInterval(-1*i.Bs, -1*i.Bi);
}

CInterval operator - (long double x, CInterval i)
{
	return CInterval(-1*i.Bs+x, -1*i.Bi+x);
}


CInterval operator - (CInterval i, long double x)
{
	return CInterval(i.Bi-x, i.Bs-x);
}


CInterval operator - (CInterval i1, CInterval i2)
{
	return CInterval(i1.Bi-i2.Bs, i1.Bs-i2.Bi);
}


CInterval operator * (long double x, CInterval i)
{
	if(x>=0)
		return CInterval(x*i.Bi, x*i.Bs);
	else return CInterval(x*i.Bs, x*i.Bi);
}


CInterval operator * (CInterval i, long double x)
{
	if(x>=0)
		return CInterval(x*i.Bi, x*i.Bs);
	else return CInterval(x*i.Bs, x*i.Bi);
}


CInterval operator * (CInterval i1, CInterval i2)
{
	long double x, y, z, w;
	x=i1.Bi*i2.Bi;
	y=i1.Bi*i2.Bs;
	z=i1.Bs*i2.Bi;
	w=i1.Bs*i2.Bs;

	return CInterval(min(x, min(y, min(z, w))), max(x, max(y, max(z, w))));
}


CInterval operator / (CInterval i, long double x)
{
	if(x>0)
		return CInterval(i.Bi/x, i.Bs/x);
	else if (x!=0)
		return CInterval(i.Bs/x, i.Bi/x);
	else //if (!(0&i))
		return CInterval(-HUGE_VAL, HUGE_VAL);
	// else erreur
}


CInterval operator / (CInterval i1, CInterval i2)
{
	CInterval i3;
	long double temp;

	// I/ cas où i2.Bi=i2.Bs (i2 est en fait un réel)
	//    on divise i1 par i2.Bi
	if (i2.Bi == i2.Bs)
	{
		return i1/i2.Bi;
	}

	// II/ cas où 0 n'appartient pas à i2
	//     on multiplie par l'inverse
	if (!(0&i2))
	{
		i3.Bi = 1/i2.Bs;
		i3.Bs = 1/i2.Bi;
		i3.Length = i3.Bs-i3.Bi;
		return i1*i3;
	}

	// III/ cas où 0 appartient aux deux CIntervalles
	//      l'CIntervalle obtenu est [-infini, +infini]
	if ((0&i1)&&(0&i2))
	{
		printf("coucouIII\n");
		return (CInterval(-HUGE_VAL, HUGE_VAL));
	}

	// IV/ cas où i1.Bs<0 et i2.Bi<i2.Bs=0
	//     l'CIntervalle obtenu est [i1.Bs/i2.Bi, +infini]
	if ((i1.Bs<0) && (i2.Bi<i2.Bs) && (i2.Bs==0))
	{
		temp = i1.Bs/i2.Bi;
		printf("coucouIV\n");
		return CInterval(temp, HUGE_VAL);
	}

	// V/ cas où i1.Bs<0 et 0=i2.Bi<i2.Bs
	//     l'CIntervalle obtenu est [-infini, i1.Bs/i2.Bs]
	if ((i1.Bs<0) && (0==i2.Bi) && (i2.Bi<i2.Bs))
	{
		temp = i1.Bs/i2.Bs;
		printf("coucouV\n");
		return CInterval(-HUGE_VAL, temp);
	}

	// VI/ cas où 0<i1.Bi et i2.Bi<i2.Bs=0
	//      l'CIntervalle obtenu est [-infini, i1.Bi/i2.Bi]
	if ((0<i1.Bi) && (i2.Bi<i2.Bs) && (i2.Bs==0))
	{
		temp = i1.Bi/i2.Bi;
		printf("coucouVI\n");
		return CInterval(-HUGE_VAL, temp);
	}

	// VII/ cas où 0<i1.Bi et 0=i2.Bi<i2.Bs
	//     l'CIntervalle obtenu est [i1.Bi/i2.Bs, +infini]
	if ((0<i1.Bi) && (0==i2.Bi) && (i2.Bi<i2.Bs))
	{
		temp = i1.Bi/i2.Bs;
		printf("coucouVII\n");
		return CInterval(temp, HUGE_VAL);
	}

	// VIII/ cas où i1.Bs<0 et 0 appartient à i2
	//    l'CIntervalle obtenu est [-infini, i1.Bs/i2.Bs]U[i1.Bs/i2.Bi, +infini]
	if ((i1.Bs<0) && (0&i2))
	{
		printf("Erreur, division par un CIntervalle contenant 0\n");
		return CInterval(quiet_nan(), quiet_nan());
	}

	// IX/ cas où 0<i1.Bi et 0 appartient à i2
	//       l'CIntervalle obtenu est [-infini, i1.Bi/i2.Bi]U[i1.Bi/i2.Bs, +infini]
	if ((0<i1.Bi) && (0&i2))
	{
		printf("Erreur, division par un CIntervalle contenant 0\n");
		return CInterval(quiet_nan(), quiet_nan());
	}

	// X/ cas où !(0&i1) et i2==[0, 0]
	//    fait dans le cas I/

	// XI/ cas non trouvé
	// message d'erreeur
	printf("Cas non implemente\n");
	return CInterval(quiet_nan(), quiet_nan());
}


CInterval operator / (long double x, CInterval i)
{
	CInterval temp(x, x);
	return x/i;
}


CInterval& CInterval::operator = (CInterval i)
{
	this->Bi = i.Bi;
	this->Bs = i.Bs;
	this->Length = i.Length;
	return *this;
}


CInterval& CInterval::operator = (long double x)
{
	this->Bi = x;
	this->Bs = x;
	this->Length = 0;
	return *this;
}


void CInterval::operator += (CInterval i)
{
	Bi += i.Bi;
	Bs += i.Bs;
	Length = Bs - Bi;
}


void CInterval::operator -= (CInterval i)
{
	Bi -= i.Bs;
	Bs -= i.Bi;
	Length = Bs - Bi;
}


void CInterval::operator *= (CInterval i)
{
	long double x, y, z, w;

	x = this->Bi * i.Bi;
	y = this->Bi * i.Bs;
	z = this->Bs * i.Bi;
	w = this->Bs * i.Bs;
	Bi = min(x, min(y, min(z, w)));
	Bs = max(x, max(y, max(z, w)));
	Length = Bs - Bi;
}


//void CInterval::operator /= (CInterval i2)
//{
//	CInterval i1(this->Bi, this->Bs);
//	CInterval i3;
//	long double temp;
//
//	// I/ cas où i2.Bi=i2.Bs (i2 est en fait un réel)
//	//    on divise i1 par i2.Bi
//	if (i2.Bi == i2.Bs)
//	{
//		this* = i1/i2.Bi;
//	}
//
//	// II/ cas où 0 n'appartient pas à i2
//	//     on multiplie par l'inverse
//	if (!(0&i2))
//	{
//		i3.Bi = 1/i2.Bs;
//		i3.Bs = 1/i2.Bi;
//		i3.Length = i3.Bs-i3.Bi;
//		this* = i1*i3;
//	}
//
//	// III/ cas où 0 appartient aux deux CIntervalles
//	//      l'CIntervalle obtenu est [-infini, +infini]
//	if ((0&i1)&&(0&i2))
//	{
//		printf("coucouIII\n");
//		this* = (CInterval(-HUGE_VAL, HUGE_VAL));
//	}
//
//	// IV/ cas où i1.Bs<0 et i2.Bi<i2.Bs=0
//	//     l'CIntervalle obtenu est [i1.Bs/i2.Bi, +infini]
//	if ((i1.Bs<0) && (i2.Bi<i2.Bs) && (i2.Bs==0))
//	{
//		temp = i1.Bs/i2.Bi;
//		printf("coucouIV\n");
//		this* = CInterval(temp, HUGE_VAL);
//	}
//
//	// V/ cas où i1.Bs<0 et 0=i2.Bi<i2.Bs
//	//     l'CIntervalle obtenu est [-infini, i1.Bs/i2.Bs]
//	if ((i1.Bs<0) && (0==i2.Bi) && (i2.Bi<i2.Bs))
//	{
//		temp = i1.Bs/i2.Bs;
//		printf("coucouV\n");
//		this* = CInterval(-HUGE_VAL, temp);
//	}
//
//	// VI/ cas où 0<i1.Bi et i2.Bi<i2.Bs=0
//	//      l'CIntervalle obtenu est [-infini, i1.Bi/i2.Bi]
//	if ((0<i1.Bi) && (i2.Bi<i2.Bs) && (i2.Bs==0))
//	{
//		temp = i1.Bi/i2.Bi;
//		printf("coucouVI\n");
//		this* = CInterval(-HUGE_VAL, temp);
//	}
//
//	// VII/ cas où 0<i1.Bi et 0=i2.Bi<i2.Bs
//	//     l'CIntervalle obtenu est [i1.Bi/i2.Bs, +infini]
//	if ((0<i1.Bi) && (0==i2.Bi) && (i2.Bi<i2.Bs))
//	{
//		temp = i1.Bi/i2.Bs;
//		printf("coucouVII\n");
//		this* = CInterval(temp, HUGE_VAL);
//	}
//
//	// VIII/ cas où i1.Bs<0 et 0 appartient à i2
//	//    l'CIntervalle obtenu est [-infini, i1.Bs/i2.Bs]U[i1.Bs/i2.Bi, +infini]
//	if ((i1.Bs<0) && (0&i2))
//	{
//		printf("Erreur, division par un CIntervalle contenant 0\n");
//		this* = CInterval(quiet_nan(), quiet_nan());
//	}
//
//	// IX/ cas où 0<i1.Bi et 0 appartient à i2
//	//       l'CIntervalle obtenu est [-infini, i1.Bi/i2.Bi]U[i1.Bi/i2.Bs, +infini]
//	if ((0<i1.Bi) && (0&i2))
//	{
//		printf("Erreur, division par un CIntervalle contenant 0\n");
//		this* = CInterval(quiet_nan(), quiet_nan());
//	}
//
//	// X/ cas où !(0&i1) et i2==[0, 0]
//	//    fait dans le cas I/
//
//	// XI/ cas non trouvé
//	// message d'erreeur
//	printf("Cas non implemente\n");
//	this* = CInterval(quiet_nan(), quiet_nan());
//}

CInterval sqr(CInterval i)
{
	if((i.Bi<0) && (i.Bs<0)) // les deux bornes sont négatives on retourne [Bs², Bi²]
		return CInterval(i.Bs*i.Bs, i.Bi*i.Bi);

	else if((i.Bi>0) && (i.Bs>0)) // les deux bornes sont positives on retourne [Bi², Bs²]
		return CInterval(i.Bi*i.Bi, i.Bs*i.Bs);

	else // 0 appartient à l'CIntervalle on retourne [0, max(Bi², Bs²)]
		return CInterval(0, max((i.Bi*i.Bi), (i.Bs*i.Bs)));
}

CInterval sqrt(CInterval i)  // !!!!!!!on ne prend que les valeurs résultats positives car on l'utilise pour des distances
{
	if (!(0&i))
		return CInterval(sqrt(i.Bi), sqrt(i.Bs));
	else return CInterval (0, sqrt(i.Bs));
}

CInterval pow(CInterval i, int p)
{
	if ((p%2)==0)
	{
		if((i.Bi<0) && (i.Bs<0)) // les deux bornes sont négatives on retourne [Bs^p, Bi^p]
			return CInterval(pow(i.Bs, p), pow(i.Bi, p));

		else if((i.Bi>0) && (i.Bs>0)) // les deux bornes sont positives on retourne [Bi^p, Bs^p]
			return CInterval(pow(i.Bi, p), pow(i.Bs, p));

		else // 0 appartient à l'CIntervalle on retourne [0, max(Bi^p, Bs^p)]
			return CInterval(0, max(pow(i.Bi, p), pow(i.Bs, p)));
	} 
	else //(p%2)==1
	{
		return CInterval(pow(i.Bi, p), pow(i.Bs, p));
	}
}

///  NE PAS OUBLIER LES OPERATEUR /=, *=, -=, += AVEC DOUBLE
/// NE PAS OUBLIER DE FAIR LE CAS interval/double POUR !(0&interval) mais ne devrais pas arrivé car div par 0 impossible

CInterval_3D::CInterval_3D(void)
{}

CInterval_3D::CInterval_3D(CInterval x,CInterval y,CInterval z)
{X=x;Y=y;Z=z;}

CInterval_3D::CInterval_3D(long double ix,long double sx,long double iy,long double sy,long double iz,long double sz)
{X.Set(ix,sx);Y.Set(iy,sy);Z.Set(iz,sz);}

/*CInterval CInterval_3D::Get_X(void)
{return X;}

CInterval CInterval_3D::Get_Y(void)
{return Y;}

CInterval CInterval_3D::Get_Z(void)
{return Z;}*/

CInterval& CInterval_3D::Get_X(void)
{return X;}

CInterval& CInterval_3D::Get_Y(void)
{return Y;}

CInterval& CInterval_3D::Get_Z(void)
{return Z;}


long double CInterval_3D::Get_XLength(void)
{return X.Length;}

long double CInterval_3D::Get_YLength(void)
{return Y.Length;}

long double CInterval_3D::Get_ZLength(void)
{return Z.Length;}

void CInterval_3D::Set_X(CInterval x)
{X=x;}

void CInterval_3D::Set_X(long double a,long double b)
{X.Set_Bi(a);X.Set_Bs(b);}

void CInterval_3D::Set_Y(CInterval y)
{Y=y;}

void CInterval_3D::Set_Y(long double a,long double b)
{Y.Set_Bi(a);Y.Set_Bs(b);}

void CInterval_3D::Set_Z(CInterval z)
{Z=z;}

void CInterval_3D::Set_Z(long double a,long double b)
{Z.Set_Bi(a);Z.Set_Bs(b);}

void CInterval_3D::Set(CInterval &x,CInterval &y,CInterval &z)
{X=x;Y=y;Z=z;}

void CInterval_3D::Set(long double ix,long double sx,long double iy,long double sy,long double iz,long double sz)
{X.Set(ix,sx);Y.Set(iy,sy);Z.Set(iz,sz);}

void CInterval_3D::Display()
{
	printf("X = ");X.Display();
	printf("Y = ");Y.Display();
	printf("Z = ");Z.Display();
	printf("\n");
}

CInterval CInterval_3D::Distance(CPoint_3D p)
{
	CInterval_3D temp;

	temp.Set_X(sqr(X-p.Get_x()));temp.Set_Y(sqr(Y-p.Get_y()));temp.Set_Z(sqr(Z-p.Get_z()));
		
	return (sqrt(temp.Get_X()+temp.Get_Y()+temp.Get_Z()));
}

long double CInterval_3D::Distance_Min(CPoint_3D p)
{
	CInterval_3D InterNewCoord;
	CPoint_3D Nearest;
	
	// Changement de repere pour l'intervalle => Origine devient centre du blob
	InterNewCoord.Set(X-p.Get_x(),Y-p.Get_y(),Z-p.Get_z());

	if (0<InterNewCoord.Get_X().Get_Bi())
		Nearest.Put_x(InterNewCoord.Get_X().Get_Bi());
	else 
		if (0<=InterNewCoord.Get_X().Get_Bs())
			Nearest.Put_x(0);
		else 
			Nearest.Put_x(InterNewCoord.Get_X().Get_Bs());

	if (0<InterNewCoord.Get_Y().Get_Bi())
		Nearest.Put_y(InterNewCoord.Get_Y().Get_Bi());
	else 
		if (0<=InterNewCoord.Get_Y().Get_Bs())
			Nearest.Put_y(0);
		else 
			Nearest.Put_y(InterNewCoord.Get_Y().Get_Bs());

	if (0<InterNewCoord.Get_Z().Get_Bi())
		Nearest.Put_z(InterNewCoord.Get_Z().Get_Bi());
	else 
		if (0<=InterNewCoord.Get_Z().Get_Bs())
			Nearest.Put_z(0);
		else 
			Nearest.Put_z(InterNewCoord.Get_Z().Get_Bs());
	
	return (sqrt(Nearest.Get_x()*Nearest.Get_x()+Nearest.Get_y()*Nearest.Get_y()+Nearest.Get_z()*Nearest.Get_z()));

}

long double CInterval_3D::Distance_Max(CPoint_3D p)
{
	CInterval_3D InterNewCoord;
	CPoint_3D Farthest;
	
	// Changement de repere pour l'intervalle => Origine devient centre du blob
	InterNewCoord.Set(X-p.Get_x(),Y-p.Get_y(),Z-p.Get_z());

	if (0<InterNewCoord.Get_X().Get_Bi())
		Farthest.Put_x(InterNewCoord.Get_X().Get_Bs());
	else 
		if (0<=InterNewCoord.Get_X().Get_Bs())
			if (fabs(InterNewCoord.Get_X().Get_Bs())>fabs(InterNewCoord.Get_X().Get_Bi()))
				Farthest.Put_x(InterNewCoord.Get_X().Get_Bs());
			else 
				Farthest.Put_x(InterNewCoord.Get_X().Get_Bi());
		else 
			Farthest.Put_x(InterNewCoord.Get_X().Get_Bi());

	if (0<InterNewCoord.Get_Y().Get_Bi())
		Farthest.Put_y(InterNewCoord.Get_Y().Get_Bs());
	else 
		if (0<=InterNewCoord.Get_Y().Get_Bs())
			if (fabs(InterNewCoord.Get_Y().Get_Bs())>fabs(InterNewCoord.Get_Y().Get_Bi()))
				Farthest.Put_y(InterNewCoord.Get_Y().Get_Bs());
			else 
				Farthest.Put_y(InterNewCoord.Get_Y().Get_Bi());
		else 
			Farthest.Put_y(InterNewCoord.Get_Y().Get_Bi());

	if (0<InterNewCoord.Get_Z().Get_Bi())
		Farthest.Put_z(InterNewCoord.Get_Z().Get_Bs());
	else 
		if (0<=InterNewCoord.Get_Z().Get_Bs())
			if (fabs(InterNewCoord.Get_Z().Get_Bs())>fabs(InterNewCoord.Get_Z().Get_Bi()))
				Farthest.Put_z(InterNewCoord.Get_Z().Get_Bs());
			else 
				Farthest.Put_z(InterNewCoord.Get_Z().Get_Bi());
		else 
			Farthest.Put_z(InterNewCoord.Get_Z().Get_Bi());

	
	return (sqrt(Farthest.Get_x()*Farthest.Get_x()+Farthest.Get_y()*Farthest.Get_y()+Farthest.Get_z()*Farthest.Get_z()));
}

CInterval_3D& CInterval_3D::operator = (CInterval_3D i)
{
	this->X = i.X;
	this->Y = i.Y;
	this->Z = i.Z;
	return *this;
}

void CInterval_3D::operator += (CInterval_3D i)
{
	X.Bi += i.X.Bi;
	X.Bs += i.X.Bs;
	X.Length = X.Bs - X.Bi;

	Y.Bi += i.Y.Bi;
	Y.Bs += i.Y.Bs;
	Y.Length = Y.Bs - Y.Bi;

	Z.Bi += i.Z.Bi;
	Z.Bs += i.Z.Bs;
	Z.Length = Z.Bs - Z.Bi;
}

int operator & (CPoint_3D p, CInterval_3D i)
{
	return (
		(p.Get_x()>=i.Get_X().Get_Bi()) && (p.Get_x()<=i.Get_X().Get_Bs()) &&
		(p.Get_y()>=i.Get_Y().Get_Bi()) && (p.Get_y()<=i.Get_Y().Get_Bs()) &&
		(p.Get_z()>=i.Get_Z().Get_Bi()) && (p.Get_z()<=i.Get_Z().Get_Bs())
		
		);
}

CInterval_3D operator + (CInterval_3D i1, CInterval_3D i2)
{
	return CInterval_3D(i1.X+i2.X, i1.Y+i2.Y, i1.Z+i2.Z);
}
