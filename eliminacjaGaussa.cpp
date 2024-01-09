#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
class Max{
	public:
		double max;
		int p;
		int q;
		void colMax(vector<vector<double>>&A,int j,int n);
		void rowMax(vector<vector<double>>&A,int i,int n);
		void fullMax(vector<vector<double>>&A,int n,int krok);
		void swapX(vector<int>swappedX,double x[]);
};
void showEquationCoeffs(vector<vector<double>>A,vector<double>B, int n)
{
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<A[i][j]<<" ";			
		}
		cout<<B[i]<<endl;
	}
}
void elimStep(vector<vector<double>>&A,vector<double>&B,int n, int krok)
{
	for(int i=krok+1;i<n;i++)
	{
		double p=A[i][krok]/A[krok][krok];
		for(int j=0;j<n;j++)
		{
			A[i][j]=A[i][j]-p*A[krok][j];
		}
		B[i]=B[i]-p*B[krok];
	}
}
void backSub(double x[],vector<vector<double>>&A,vector<double>&B,int n)
{
	x[n-1]=B[n-1]/A[n-1][n-1];
	for(int i=n-2;i>=0;i--)
	{
		x[i]=B[i];
		for(int j=n-1;j>i;j--)
		{
			x[i]-=A[i][j]*x[j];
		}
		x[i]=x[i]/A[i][i];
	}
}
void Max::colMax(vector<vector<double>>&A,int j,int n)
{
	this->max=0;
	for(int i=j;i<n;i++)
	{
		if(abs(A[i][j])>abs(this->max)){
			this->max=A[i][j];
			this->p=i;
			this->q=j;
		}
	}
}
void Max::rowMax(vector<vector<double>>&A,int i,int n)
{
	this->max=0;
	for(int j=i;j<n;j++)
	{
		if(abs(A[i][j])>abs(this->max)){
			this->max=A[i][j];
			this->p=i;
			this->q=j;
		}
	}
}
void rowSwap(vector<vector<double>>&A,vector<double>&B,int krok,int i)
{
	swap(A[i],A[krok]);
	swap(B[i],B[krok]);
}
void colSwap(vector<vector<double>>&A,int krok,int j,int n)
{
	for(int k=krok;k<n;k++)
	{
		swap(A[k][krok],A[k][j]);
	}
}
void Max::fullMax(vector<vector<double>>&A,int n,int krok)
{
	this->max=0;
	for(int i=krok;i<n;i++)
	{
		for(int j=krok;j<n;j++)
		{
			if(abs(A[i][j])>abs(this->max)){
			this->max=A[i][j];
			this->p=i;
			this->q=j;
			}
		}
	}	
}
void Max::swapX(vector<int>swappedX,double x[])
{
	for(int i=0;i<swappedX.size();i=i+2)
	{
		swap(x[swappedX[i]],x[swappedX[i+1]]);
	}
}

int main()
{
	vector<vector<double>>A;
	vector<double>B;
	vector<int>swappedX;
	vector<double>pom;
	int n=4,wybDane;
	cout<<"Jesli chcesz uzyc domyslnych danych testowych, wybierz 1. Jesli chcesz wprowadzic dane testowe, wybierz 2.\n";
	cin>>wybDane;
	Max Max;
	double a,b,x[n];
	switch(wybDane)
	{
		case 1:
			A={{2.25,-2.5,4,-5.25},{-3,-7.5,6.5,0},{-6.25,-12.5,0.25,5.25},{9,10,7,-21}};
			B={-1,17,24.25,-33};
			break;
		case 2:
			cout<<"Podaj wymiar macierzy:";
			cin>>n;
			cout<<"Podaj wspolczynniki:"<<endl;
			for(int i=0;i<n;i++){
				A.push_back(pom);
				for(int j=0;j<n;j++){
					cin>>a;
					A[i].push_back(a);			
				}
				cin>>b;
				B.push_back(b);		
			}		
			break;
	}
	cout<<"Wybierz rodzaj eliminacji Gaussa:\n1 - podstawowy, 2 - z wyb. el. max. w kolumnie, 3 - z wyb. el. max w wierszu, 4 - z pelnym wyb. el. max.\n";
	int wybMetod;
	bool stepFail=false;
	cin>>wybMetod;
	for(int i=0;i<n-1;i++){
		if(abs(A[i][i])<=1e-7){
			cout<<"Nie mozna wykonac kroku eliminacji Gaussa."<<endl;
			stepFail=true;
			break;
		}
		else {
			switch(wybMetod)
			{
				case 1:
					break;
				case 2:
					Max.colMax(A,i,n);
					rowSwap(A,B,i,Max.p);
					break;
				case 3:
					Max.rowMax(A,i,n);
					colSwap(A,i,Max.q,n);
					swappedX.push_back(i);
					swappedX.push_back(Max.q);
					break;
				case 4:
					Max.colMax(A,i,n);
					rowSwap(A,B,i,Max.p);
					Max.rowMax(A,i,n);
					colSwap(A,i,Max.q,n);
					swappedX.push_back(i);
					swappedX.push_back(Max.q);
					break;					
				}
				elimStep(A,B,n,i);
		}
	}
	showEquationCoeffs(A,B,n);
	if((abs(A[n-1][n-1])<=1e-7)||stepFail==true){
		cout<<"Nie mozna wykonac postepowania odwrotnego."<<endl;
	}
	else{
		backSub(x,A,B,n);
		Max.swapX(swappedX,x);
		cout<<"x=[";
		for(int i=0;i<n;i++){
			(i==0)?cout<<x[i]:cout<<","<<x[i];
		}
		cout<<"]T";
		}
	return 0;
}