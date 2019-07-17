#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <algorithm>


struct vertex{
	long double x, y, z;
};
vertex makeVertex(long double x, long double y, long double z){
	vertex returnValue;
	returnValue.x=x;
	returnValue.y=y;
	returnValue.z=z;
	return returnValue;
}
struct edge{
	int s, e;
};
edge makeEdge(int s, int e){
	edge returnValue;
	returnValue.s=s;
	returnValue.e=e;
	return returnValue;
}
edge flipEdge(edge a){
	return makeEdge(a.e,a.s);
}
int compareEdges(edge a, edge b){
	if(a.s<b.s){
		return 2;
	}
	if(a.s==b.s){
		if(a.e<b.e){
			return 2;
		}
		if(a.e==b.e){
			return 1;
		}
	}
	return 0;
}
//in the process of making the program faster, the following function went unused
bool compareEdgesForSort(edge a, edge b){
	if(a.s<b.s)
		return true;
	if(a.s==b.s)
		if(a.e<b.e)
			return true;
	return false;
}
std::vector<std::vector<int> > adjacencyList, edgeNumberOfAdjacencyList;
int findEdgeIndex(edge a){
	int po=adjacencyList[a.s].size()/2;
	int mo=(po+1)/2;
	for(unsigned i = 1;i <= adjacencyList[a.s].size();i <<= 1){
		switch(compareEdges(makeEdge(a.s,adjacencyList[a.s][po]),a)){
			case 0:
			po-=mo;
			if(po<0)po=0;
			break;
			case 1:
			return edgeNumberOfAdjacencyList[a.s][po];
			break;
			case 2:
			po+=mo;
			if(po>=adjacencyList[a.s].size())po=adjacencyList[a.s].size()-1;
			break;
		}
		mo=(mo+1)/2;
	}
	return -1;
}
struct face{
	int p[3];
};
face makeFace(int p1, int p2, int p3){
	face returnValue;
	returnValue.p[0]=p1;
	returnValue.p[1]=p2;
	returnValue.p[2]=p3;
	return returnValue;
}
face flipFace(face faceToFlip){
	return makeFace(faceToFlip.p[1],faceToFlip.p[0],faceToFlip.p[2]);
}
bool sameFace(face a, face b){
	return (a.p[0]==b.p[0]&&a.p[1]==b.p[1]&&a.p[2]==b.p[2]);
}
long double determinant(vertex p1, vertex p2, vertex p3){
	return 
	p1.x*p2.y*p3.z-
	p1.x*p2.z*p3.y-
	p1.y*p2.x*p3.z+
	p1.y*p2.z*p3.x+
	p1.z*p2.x*p3.y-
	p1.z*p2.y*p3.x;
}
int main(){
	//freopen("inputFiles/tetrahedron.txt","r",stdin);
	//freopen("inputFiles/octahedron.txt","r",stdin);
	//freopen("inputFiles/cube.txt","r",stdin);
	//freopen("inputFiles/mountains.txt","r",stdin);

	//You can create an input file similar to
	//those below using the other programs given
	//freopen("inputFiles/torus.txt","r",stdin);
	//freopen("inputFiles/sphere.txt","r",stdin);
	//freopen("inputFiles/dipyramid.txt","r",stdin);//worst-case scenario

	//This algorithm does: input vertex coordinates
	//Algorithm used: -
	//Additional memory complexity: O(1)
	//Time complexity: O(e)
	int v;
	std::vector <vertex> vertices;
	printf("Number of vertices: ");
	scanf("%d",&v);
	vertices.resize(v);
	printf("List the cartesian coordinates of the vertices: \n");
	for(int i = 0;i < v;i ++){
		printf("Coordinates of vertex %d (x y z): ", i);
		scanf("%Lf %Lf %Lf", &vertices[i].x, &vertices[i].y, &vertices[i].z);
	}

	//This algorithm does: input edges
	//Algorithm used: -
	//Additional memory complexity: O(1)
	//Time complexity: O(e)
	int e;
	std::vector <edge> edges;
	printf("Number of edges: ");
	scanf("%d",&e);
	edges.resize(e);
	printf("List the endpoints of the edges: \n");
	for(int i = 0;i < e;i ++){
		printf("Edge %d (starting vertex code   end vertex code): ", i);
		scanf("%d %d", &edges[i].s, &edges[i].e);
		if(edges[i].s>edges[i].e){
			std::swap(edges[i].s,edges[i].e);
		}
	}
	printf("Calculating...\n");

	//This algorithm does: adjacency list making
	//Algorithm used: -
	//Additional memory complexity: O(e)
	//Time complexity: O(e)
	adjacencyList.resize(v);
	edgeNumberOfAdjacencyList.resize(v);
	for(int i = 0;i < e;i ++){
		adjacencyList[edges[i].s].push_back(edges[i].e);
	}
	//printf("Index assigning complete\n");

	//This algorithm does: adjacency list sorting sorting
	//Algorithm used: STL sort
	//Additional memory complexity: O(1)
	//Time complexity: O(e log e)
	for(int i = 0;i < v;i ++){
		sort(adjacencyList[i].begin(),adjacencyList[i].end());
	}
	//printf("Sorting complete\n");

	//This algorithm does: edge number reassignment
	//Algorithm used: -
	//Additional memory complexity: O(e)
	//Time complexity: O(e)
	int edgeNumber=0;
	for(int i = 0;i < v;i ++){
		for(int j = 0;j < adjacencyList[i].size();j ++){
			edgeNumberOfAdjacencyList[i].push_back(edgeNumber);
			edgeNumber++;
		}
	}

	//This algorithm does: edge reassignment
	//Algorithm used: -
	//Additional memory complexity: O(1)
	//Time complexity: O(e)
	for(int i = 0;i < v;i ++){
		for(int j = 0;j < edgeNumberOfAdjacencyList[i].size();j ++){
			edges[edgeNumberOfAdjacencyList[i][j]].s=i;
			edges[edgeNumberOfAdjacencyList[i][j]].e=adjacencyList[i][j];
		}
	}
	//printf("Index reassigning complete\n");

	//This algorithm does: finding potential faces
	//Algorithm used: brute-force and binary search
	//Additional memory complexity: O(e)
	//Time complexity: O(e), worst case: O(e^2 log e)
	std::vector <face> potentialFaces;
	std::vector <std::vector<int> > usedBy(e);
	for(int i = 0;i < v;i ++){
		for(int j = 0;j < adjacencyList[i].size();j ++){
			for(int k = j+1;k < adjacencyList[i].size();k ++){
				edgeNumber=findEdgeIndex(makeEdge(adjacencyList[i][j],adjacencyList[i][k]));
				if(edgeNumber!=-1){
					usedBy[edgeNumberOfAdjacencyList[i][j]].push_back(potentialFaces.size());
					usedBy[edgeNumberOfAdjacencyList[i][k]].push_back(potentialFaces.size());
					usedBy[edgeNumber].push_back(potentialFaces.size());
					potentialFaces.push_back(makeFace(i,adjacencyList[i][j],adjacencyList[i][k]));
				}
			}
		}
	}
	//printf("Potential faces complete\n");

	//Initializing
	//Additional memory complexity: O(e)
	//Time complexity: O(e)
	std::vector <int> usedBySize(e);
	std::vector <int> actuallyUsedBy(e);
	for(int i = 0;i < e;i ++){
		usedBySize[i]=usedBy[i].size();
		if(usedBySize[i]<2){
			printf("Error! Invalid input\n");
			exit(1);
		}
		actuallyUsedBy[i]=0;
	}
	int remainingPotentialFaces=potentialFaces.size();
	face faceToAdd, faceToDelete;

	//This algorithm does: Find real faces
	//Algorithm used: binary search
	//Additional memory complexity: O(e)
	//Time complexity: O(e), worst case: O(e^2 log e)
	std::vector <face> realFaces;
	int loopCount=0, loopLimit=potentialFaces.size();
	while(remainingPotentialFaces){
		if(loopCount>loopLimit){
			printf("Error! Invalid input\n");
			exit(2);
		}
		loopCount++;
		for(int i = 0;i < e;i ++){
			if(actuallyUsedBy[i]==2){
				if(usedBySize[i]){
					for(int j = 0;j < usedBy[i].size();j ++){
						if(!sameFace(potentialFaces[usedBy[i][j]],makeFace(-1,-1,-1))){
							faceToDelete=potentialFaces[usedBy[i][j]];
							if(faceToDelete.p[0]!=edges[i].s||faceToDelete.p[1]!=edges[i].e){
								usedBySize[findEdgeIndex(makeEdge(faceToDelete.p[0],faceToDelete.p[1]))]--;
							}
							if(faceToDelete.p[0]!=edges[i].s||faceToDelete.p[2]!=edges[i].e){
								usedBySize[findEdgeIndex(makeEdge(faceToDelete.p[0],faceToDelete.p[2]))]--;
							}
							if(faceToDelete.p[1]!=edges[i].s||faceToDelete.p[2]!=edges[i].e){
								usedBySize[findEdgeIndex(makeEdge(faceToDelete.p[1],faceToDelete.p[2]))]--;
							}
							potentialFaces[usedBy[i][j]]=makeFace(-1,-1,-1);
							remainingPotentialFaces--;
						}
					}
				}
			}else if(usedBySize[i]==2-actuallyUsedBy[i]){
				usedBySize[i]=0;
				actuallyUsedBy[i]=2;
				for(int j = 0;j < usedBy[i].size();j ++){
					if(!sameFace(potentialFaces[usedBy[i][j]],makeFace(-1,-1,-1))){
						faceToAdd=potentialFaces[usedBy[i][j]];
						realFaces.push_back(faceToAdd);
						if(faceToAdd.p[0]!=edges[i].s||faceToAdd.p[1]!=edges[i].e){
							edgeNumber=findEdgeIndex(makeEdge(faceToAdd.p[0],faceToAdd.p[1]));
							actuallyUsedBy[edgeNumber]++;
							usedBySize[edgeNumber]--;
						}
						if(faceToAdd.p[0]!=edges[i].s||faceToAdd.p[2]!=edges[i].e){
							edgeNumber=findEdgeIndex(makeEdge(faceToAdd.p[0],faceToAdd.p[2]));
							actuallyUsedBy[edgeNumber]++;
							usedBySize[edgeNumber]--;
						}
						if(faceToAdd.p[1]!=edges[i].s||faceToAdd.p[2]!=edges[i].e){
							edgeNumber=findEdgeIndex(makeEdge(faceToAdd.p[1],faceToAdd.p[2]));
							actuallyUsedBy[edgeNumber]++;
							usedBySize[edgeNumber]--;
						}
						potentialFaces[usedBy[i][j]]=makeFace(-1,-1,-1);
						remainingPotentialFaces--;
					}
				}
			}
		}
	}
	potentialFaces.clear();
	actuallyUsedBy.clear();
	usedBySize.clear();
	edges.clear();
	//printf("Real faces complete\n");

	//This algorithm does: face reorientation
	//Algorithm used: BFS and binary search
	//Additional memory complexity: O(e)
	//Time complexity: O(e)
	std::vector <bool> explored(realFaces.size());
	for(int i = 0;i < realFaces.size();i ++){
		explored[i]=0;
	}
	for(int i = 0;i < e;i ++){
		usedBy[i].resize(0);
	}
	for(int i = 0;i < realFaces.size();i ++){
		usedBy[findEdgeIndex(makeEdge(realFaces[i].p[0],realFaces[i].p[1]))].push_back(i);
		usedBy[findEdgeIndex(makeEdge(realFaces[i].p[0],realFaces[i].p[2]))].push_back(i);
		usedBy[findEdgeIndex(makeEdge(realFaces[i].p[1],realFaces[i].p[2]))].push_back(i);
	}
	std::vector <face> reorientedFaces;
	std::queue <edge> edgesToExplore;
	if(!realFaces.empty()){
		loopCount++;
		reorientedFaces.push_back(realFaces[0]);
		explored[0]=1;
		edgesToExplore.push(makeEdge(realFaces[0].p[0],realFaces[0].p[1]));
		edgesToExplore.push(makeEdge(realFaces[0].p[1],realFaces[0].p[2]));
		edgesToExplore.push(makeEdge(realFaces[0].p[2],realFaces[0].p[0]));
		loopCount=0;
		loopLimit=realFaces.size();
		while(!edgesToExplore.empty()){
			if(loopCount>loopLimit){
				printf("Error! Invalid input\n");
				exit(3);
			}
			if(edgesToExplore.front().s>edgesToExplore.front().e){
				edgeNumber=findEdgeIndex(flipEdge(edgesToExplore.front()));
			}else{
				edgeNumber=findEdgeIndex(edgesToExplore.front());
			}
			for(int i = 0;i < usedBy[edgeNumber].size();i ++){
				if(!explored[usedBy[edgeNumber][i]]){
					explored[usedBy[edgeNumber][i]]=1;
					for(int j = 0;j < 3;j ++){
						if(realFaces[usedBy[edgeNumber][i]].p[j]==edgesToExplore.front().s&&realFaces[usedBy[edgeNumber][i]].p[(j+1)%3]==edgesToExplore.front().e){
							reorientedFaces.push_back(flipFace(realFaces[usedBy[edgeNumber][i]]));
							for(int k = 0;k < 3;k ++){
								edgesToExplore.push(makeEdge(realFaces[usedBy[edgeNumber][i]].p[(k+1)%3],realFaces[usedBy[edgeNumber][i]].p[k]));
							}
						}
					}
					for(int j = 0;j < 3;j ++){
						if(realFaces[usedBy[edgeNumber][i]].p[(j+1)%3]==edgesToExplore.front().s&&realFaces[usedBy[edgeNumber][i]].p[j]==edgesToExplore.front().e){
							reorientedFaces.push_back(realFaces[usedBy[edgeNumber][i]]);
							for(int k = 0;k < 3;k ++){
								edgesToExplore.push(makeEdge(realFaces[usedBy[edgeNumber][i]].p[k],realFaces[usedBy[edgeNumber][i]].p[(k+1)%3]));
							}
						}
					}
				}
			}
			edgesToExplore.pop();
		}
	}
	adjacencyList.clear();
	edgeNumberOfAdjacencyList.clear();
	explored.clear();
	//printf("Reorientation complete\n");

	//This algorithm does: calculate volume
	//Algorithm used: determinant calculation
	//Additional memory complexity: O(1)
	//Time complexity: O(e)
	long double result=0;
	for(int i = 0;i < reorientedFaces.size();i ++){
		result+=determinant(vertices[reorientedFaces[i].p[0]],vertices[reorientedFaces[i].p[1]],vertices[reorientedFaces[i].p[2]]);
	}
	if(result<0)result=-result;
	printf("\n\nVolume of polyhedron = %.6Lf\n",result/6);
	return 0;
}