#include <iostream>
#include <math.h>
#define pi 3.14159265358979323846264
#define tau 6.28318530717958647692529


int main(){
	printf("Enter number of horizontal edges, height, and radius of dipyramid: ");
	freopen("inputFiles/dipyramid.txt","w",stdout);
	int n;
	double radius;
	double height;
	scanf("%d %lf %lf", &n, &radius, &height);
	printf("%d\n",n+2);
	printf("%.13f %.13f %.13f\n",0.0,0.0,height);
	for(int i = 0;i < n;i ++){
		printf("%.13f %.13f %.13f\n",radius*sin(i/n*tau),radius*cos(i*tau/n),0.0);
	}
	printf("%.13f %.13f %.13f\n",0.0,0.0,-height);
	printf("%d\n",3*n);
	for(int i = 1;i <= n;i ++){
		printf("0 %d\n",i);
	}
	for(int i = 1;i <= n;i ++){
		printf("%d %d\n",i,i%n+1);
	}
	for(int i = 1;i <= n;i ++){
		printf("%d %d\n",i,n+1);
	}
	fclose(stdout);
}