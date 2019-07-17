#include <iostream>
#include <math.h>
#define pi 3.14159265358979323846264
#define tau 6.28318530717958647692529


int main(){
	printf("Enter number of latitude and longitude lines and radius: ");
	freopen("inputFiles/sphere.txt","w",stdout);
	int n;
	double radius;
	scanf("%d %lf", &n, &radius);
	printf("%d\n",n*n+2);
	printf("%.13f %.13f %.13f\n", 0.0, 0.0,radius);
	for(int i = 0;i < n;i ++){
		for(int j = 0;j < n;j ++){
			printf("%.13f %.13f %.13f\n",radius*sin( (i+1)*pi/(n+1))*sin(j*tau/n),radius*sin((i+1)*pi/(n+1))*cos(j*tau/n),radius*cos((i+1)*pi/(n+1)));
		}
	}
	printf("%.13f %.13f %.13f\n", 0.0, 0.0,-radius);
	printf("%d\n",3*n*n);
	for(int i = 1;i <= n;i ++){
		printf("0 %d\n",i);
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 0;j < n-1;j ++){
			printf("%d %d\n",i+j*n,i+j*n+n);
		}
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 0;j < n;j ++){
			printf("%d %d\n",i+j*n,(i%n+1)+j*n);
		}
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 0;j < n-1;j ++){
			printf("%d %d\n",i+j*n,(i%n+1)+j*n+n);
		}
	}
	for(int i = 1;i <= n;i ++){
		printf("%d %d\n",i+n*n-n,n*n+1);
	}
	fclose(stdout);
}