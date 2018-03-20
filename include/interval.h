#ifndef __INTERVAL_H__
#define __INTERVAL_H__

#include <QVector3D>

class CInterval 
{
private:
	long double Bi;		
	long double Bs;		
	long double Length; 
public:
	CInterval(void);
	CInterval(long double a_bi, long double a_bs);
	~CInterval(void);
	
	void Set(long double a_bi, long double a_bs);
	void Set_Bi(long double a_bi);
	void Set_Bs(long double a_bs);
	long double Get_Bi(void);
	long double Get_Bs(void);
	long double Get_Length(void);
	void Display();

	/********** Opérateurs de comparaison ***********/
	friend int operator == (long double, CInterval);
	friend int operator == (CInterval, long double);
	friend int operator == (CInterval, CInterval);
	friend int operator >= (long double, CInterval);
	friend int operator >= (CInterval, long double);
	friend int operator >= (CInterval, CInterval);
	friend int operator <= (long double, CInterval);
	friend int operator <= (CInterval, long double);
	friend int operator <= (CInterval, CInterval);
	friend int operator > (long double, CInterval);
	friend int operator > (CInterval, long double);
	friend int operator > (CInterval, CInterval);
	friend int operator <(long double, CInterval);
	friend int operator < (CInterval, long double);
	friend int operator < (CInterval, CInterval);

	friend int operator & (long double, CInterval); // appartenance
	friend int operator & (CInterval, long double); // appartenance
	
	/********* Opérateurs d'arithmetique ***********/
	friend CInterval operator + (long double, CInterval);
	friend CInterval operator + (CInterval, long double);
	friend CInterval operator + (CInterval, CInterval);
	friend CInterval operator - (CInterval);
	friend CInterval operator - (long double, CInterval);
	friend CInterval operator - (CInterval, long double);
	friend CInterval operator - (CInterval, CInterval);
	friend CInterval operator * (long double, CInterval);
	friend CInterval operator * (CInterval, long double);
	friend CInterval operator * (CInterval, CInterval);
	friend CInterval operator / (CInterval, long double);
	friend CInterval operator / (CInterval, CInterval);
	friend CInterval operator / (long double, CInterval);


	/********* Opérateurs d'affectation ************/
	CInterval& operator = (CInterval);
	CInterval& operator = (long double);
	void operator += (CInterval);
	void operator -= (CInterval);
	void operator *= (CInterval);
	void operator /= (CInterval);

	/*********** Fonctions mathépatiques usuelles *************/
	friend CInterval sqrt(CInterval i); // !!!!!!!on ne prend que les valeurs résultats positives car on l'utilise pour des distances !!!!
	friend CInterval sqr(CInterval i);
	friend CInterval pow(CInterval i, int p);
friend class CInterval_3D;
};

class CInterval_3D 
{
protected:
	CInterval X,Y,Z;
public:
	CInterval_3D(void);
	CInterval_3D(CInterval,CInterval,CInterval);
	CInterval_3D(long double,long double,long double,long double,long double,long double);
        /*CInterval Get_X(void);
	CInterval Get_Y(void);
        CInterval Get_Z(void);*/
        CInterval& Get_X(void);
        CInterval& Get_Y(void);
        CInterval& Get_Z(void);
	long double Get_XLength(void);
	long double Get_YLength(void);
	long double Get_ZLength(void);
	void Set_X(CInterval);
	void Set_X(long double,long double);
	void Set_Y(CInterval);
	void Set_Y(long double,long double);
	void Set_Z(CInterval);
	void Set_Z(long double,long double);
	void Set(CInterval &,CInterval &,CInterval &);
	void Set(long double,long double,long double,long double,long double,long double);
	void Display();
        CInterval Distance(QVector3D);
        long double Distance_Min(QVector3D);
        long double Distance_Max(QVector3D);
	CInterval_3D& operator = (CInterval_3D);
	void operator += (CInterval_3D);
        friend int operator & (QVector3D, CInterval_3D);
	friend CInterval_3D operator + (CInterval_3D, CInterval_3D);
};

void iserror(char*);

#endif /* __INTERVAL_H__ */
