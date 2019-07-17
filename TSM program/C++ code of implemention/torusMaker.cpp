#include <iostream>
#include <math.h>
#define dc (double)
#define pi 3.14159265358979323846264
#define tau 6.28318530717958647692529


int main(){
	printf("Accuracy of torus, inner and outer radii: ");
	freopen("inputFiles/torus.txt","w",stdout);
	int n;
	double innerRadius, outerRadius;
	scanf("%d %lf %lf", &n, &innerRadius, &outerRadius);
	printf("%d\n",n*n);
	for(int i = 0;i < n;i ++){
		for(int j = 0;j < n;j ++){
			printf("%.13f %.13f %.13f\n", (innerRadius+outerRadius+sin(j*tau/n)*(outerRadius-innerRadius))*sin(i*tau/n)/2, (innerRadius+outerRadius+sin(j*tau/n)*(outerRadius-innerRadius))*cos(i*tau/n)/2, cos(j*tau/n)*(outerRadius-innerRadius)/2);
		}
	}
	printf("%d\n",3*n*n);
	for(int i = 0;i < n;i ++){
		for(int j = 0;j < n;j ++){
			printf("%d %d\n", i*n+j, (i+1)%n*n+j);
			printf("%d %d\n", i*n+j, i*n+(j+1)%n);
			printf("%d %d\n", i*n+j, (i+1)%n*n+(j+1)%n);
		}
	}
	fclose(stdout);
}