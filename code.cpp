/*
	OR logic solution using a perceptron
	the algorithm solves an expression containing four atomic prepositions (OR connective is implicit) containing 0(F) or 1(V)
	it is trained with only five strategic samples
*/

#include <bits/stdc++.h>

#define MAX_TRAINING 5
#define threshold -1
#define MAXN 4
#define RATE 0.01
#define trueValue(x) x ? 'V' : 'F'
#define signalFunction(x) x > 0

#define LT_GRAY		"\x1b[30;1m"
#define LT_RED		"\x1b[31;1m"
#define LT_GREEN	"\x1b[32;1m"
#define CLR_RESET	"\x1b[0m"

const int sample[][MAXN + 1] = {{0,0,0,0,-1},{1,0,0,0,-1},{0,1,0,0,-1},{0,0,1,0,-1},{0,0,0,1,-1}}; // adds plus one because of the threshold
const int answer[MAX_TRAINING] = {0, 1, 1, 1, 1};

typedef struct neuron
{
	int epoch;
	long double weight[MAXN + 1];

	neuron()
	{
		epoch = 1000;

		for(int i=0; i<=MAXN; ++i)
			weight[i] = ((rand() % 101) * 2 - 100) / 100.0;
	}

	void training()
	{
		while(--epoch)
		{
			for(int k=0; k<MAX_TRAINING; ++k)
			{
				long double current = 0;

				for(int i=0; i<=MAXN; ++i)
					current += weight[i] * sample[k][i];

				int y = signalFunction(current);
				int error = answer[k] - y;

				if(error) {
					for(int i=0; i<=MAXN; ++i)
						weight[i] = weight[i] + RATE * error * sample[k][i];
				}
			}
		}
	}

	char predict(int *input)
	{
		input[MAXN] = threshold;
		long double current = 0;

		for(int i=0; i<=MAXN; ++i)
			current += weight[i] * input[i];

		return trueValue(signalFunction(current));
	}

} neuron;

void testOutput(neuron perceptron)
{
	int input[10];

	// for each input of size MAXN
	for(int i=0; i<MAXN; ++i)
		if(scanf("%d", &input[i]) == EOF) // while there is input
			return;

	for(int i=0; i<MAXN; ++i) {
		if(i)
			printf(LT_GRAY " v " CLR_RESET "%c", trueValue(input[i]));
		else
			printf("%c", trueValue(input[0]));
	}

	if(perceptron.predict(input) == 'V')
		printf(" = " LT_GREEN "V" CLR_RESET "\n");
	else
		printf(" = " LT_RED "F" CLR_RESET "\n");

	return testOutput(perceptron);
}

int main()
{
	neuron perceptron; 
	perceptron.training();
	testOutput(perceptron);
    
    return 0;
}
