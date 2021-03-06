#include <iostream>

using namespace std;
const int MAX=109;
typedef long long LONG;

LONG acum[MAX][MAX];

LONG query(int startI,int endI,int startJ, int endJ){
	return acum[endI][endJ] - acum[startI-1][endJ] - acum[endI][startJ-1] + acum[startI-1][startJ-1];
}


int main(){
	int T,N,M,D,caso=1;
	cin >> T;
	while(T--){
		cin >> N >> M >> D;

		/*Leemos los datos ingresados*/
		for (int i = 1; i <= N; i++){
			for (int j = 1; j <= M; j++)
				cin >> acum[i][j];
		}

		/*Hacemos la suma de acumulados*/
		for (int i = 1; i <= N; i++){
			for (int j = 1; j <= M; j++)
				acum[i][j] += acum[i][j-1];
			
			for (int j = 1; j <= M; j++)
				acum[i][j] += acum[i-1][j];
		}


		/*for (int i = 1; i <= N; i++){
            for (int j = 1; j <=M; j++)
            	cout << acum[i][j] << " ";
            cout <<"\n";
        }*/

		LONG area=0, minCosto=((LONG)1)<<60;


		/*Empezamos con el barrido.*/
		for (int i = 1; i <= N; i++){
			for (int j = i;j <= N; j++){
				LONG tmpArea=0,costo=0;
				for (int k=1,l=1; l <= M; l++){
					costo += query(i,j,l,l);
					//cout << "costo: " << costo << "\n";
					while(k<=l && costo>D)
						costo -= query(i,j,k,k),k++;
					tmpArea = (j-i+1)*(l-k+1);
					if (tmpArea>area || (tmpArea==area && costo<minCosto))
						area = tmpArea, minCosto=costo;
				}
			}
		}
		cout << "Case #" << caso++ << ": " << area << " "<<minCosto<<"\n";
	}
}