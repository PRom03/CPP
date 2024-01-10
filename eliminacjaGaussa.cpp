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
void elimStep(vector<vector<double>>&A,vector<double>&B,int n, int step)
{
	for(int i=step+1;i<n;i++)
	{
		double p=A[i][step]/A[step][step];
		for(int j=0;j<n;j++)
		{
			A[i][j]=A[i][j]-p*A[step][j];
		}
		B[i]=B[i]-p*B[step];
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
void rowSwap(vector<vector<double>>&A,vector<double>&B,int step,int i)
{
	swap(A[i],A[step]);
	swap(B[i],B[step]);
}
void colSwap(vector<vector<double>>&A,int step,int j,int n)
{
	for(int k=step;k<n;k++)
	{
		swap(A[k][step],A[k][j]);
	}
}
void swapX(vector<int>swappedX,double x[])
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
	vector<double>auxil;
	int n=4,dataChoose;
	cout<<"If you want to use default test data, choose 1. Else, if you want to put test data in, choose 2.\n";
	cin>>dataChoose;
	Max Max;
	double a,b,x[n];
	switch(dataChoose)
	{
		case 1:
			A={{2.25,-2.5,4,-5.25},{-3,-7.5,6.5,0},{-6.25,-12.5,0.25,5.25},{9,10,7,-21}};
			B={-1,17,24.25,-33};
			break;
		case 2:
			cout<<"Give matrix size:";
			cin>>n;
			cout<<"Give coefficients:"<<endl;
			for(int i=0;i<n;i++){
				A.push_back(auxil);
				for(int j=0;j<n;j++){
					cin>>a;
					A[i].push_back(a);			
				}
				cin>>b;
				B.push_back(b);		
			}		
			break;
	}
	cout<<"Choose Gauss elimination mode:\n1 - basic, 2 - with choose of max elem. in a column, 3 - with choose of max elem. in a row, 4 - with full choose of max elem.\n";
	int wybMetod;
	bool stepFail=false;
	cin>>wybMetod;
	for(int i=0;i<n-1;i++){
		if(abs(A[i][i])<=1e-7){
			cout<<"Cannot take a step."<<endl;
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
		cout<<"Cannot execute the back substitution."<<endl;
	}
	else{
		backSub(x,A,B,n);
		swapX(swappedX,x);
		cout<<"x=[";
		for(int i=0;i<n;i++){
			(i==0)?cout<<x[i]:cout<<","<<x[i];
		}
		cout<<"]T";
		}
	return 0;
}
