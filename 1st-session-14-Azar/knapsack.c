#include <stdio.h>

const int INF = 1000000000;

int a[100], c[100], V;
int state[100];

int bt(int i, int n) {
	if(i == n) {
		printf("{");
		int sumA = 0, sumC = 0;
		for(int j = 0; j < n; j++)
			if(state[j] == 1) {
				sumA += a[j];
				sumC += c[j];
				printf("%d ", j);
			}
		printf("} =>  sumA = %d, sumC = %d\n", sumA, sumC);
		if(sumA <= V)
			return sumC;
		return -INF;
	}
	
	// state[i] ro moshakhas konim!
	state[i] = 0;
	int ans1 = bt(i + 1, n);
	state[i] = 1;
	int ans2 = bt(i + 1, n);
	if(ans1 > ans2)
		return ans1;
	return ans2;
}

int main() {
	int n;
	scanf("%d%d", &n, &V);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(int i = 0; i < n; i++)
		scanf("%d", &c[i]);
	
	printf("%d\n", bt(0, n));
}