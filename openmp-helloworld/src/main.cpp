#include <iostream>
#include <omp.h>
#include <stdio.h>


void calcualtePi()
{
	static long num_steps = 100000;
	int threads = 4;
	double step;
	double pi = 0.0;
	step = 1.0/(double) num_steps;

	omp_set_num_threads(threads);
	omp_get_wtime();
	#pragma omp parallel
	{
		double	numStepThread 	= num_steps / omp_get_num_threads();
		double 	startStep 		= numStepThread * omp_get_thread_num();
		double 	endStep 		= startStep + numStepThread;

		double x, sum = 0.0;
		for(double i = startStep; i < endStep; i++)
		{
			x = ( i + 0.5 ) * step;
			sum = sum + 4.0/(1.0+x*x);
		}

		pi += step * sum;
	}
	std::cout << "threads " << threads << "\t";
	std::cout << "time: " << omp_get_wtime() << "\t";
	std::cout << "pi = " << pi << std::endl;
}

void calculatePi2()
{
	//USES padding to avoid false sharing

	for(int j = 1; j < 6; j++)
	{
	static long num_steps = 10000000;
	int nthreadsRequested  = j;
	int nthreads;

	double step;
	double pi = 0.0;
	step = 1.0/(double) num_steps;

	int pad = 8;
	double sum[nthreadsRequested][pad];

	for(int i = 0; i < nthreadsRequested; i++)
		sum[i][0] = 0.0;

	omp_set_num_threads(nthreadsRequested);
	double timestart = omp_get_wtime();
	#pragma omp parallel
	{
		double x;
		int nThreadsActual = omp_get_num_threads();
		int id = omp_get_thread_num();
		if(id == 0) nthreads = nThreadsActual;

		for(int i = id; i < num_steps; i+=nThreadsActual)
		{
			x = ( i + 0.5 ) * step;
			sum[omp_get_thread_num()][0] += 4.0/(1.0+x*x);
		}
	}

	for(int i = 0; i < nthreads; i++)
		pi += sum[i][0]*step;

	std::cout << "threads " << nthreads << "\t";
	std::cout << "time: " << (omp_get_wtime() - timestart)*1000 << "\t";
	std::cout << "pi = " << pi << std::endl;
	}
}


void calculatePi3()
{
	for(int j = 1; j < 6; j++)
	{
	static long num_steps = 10000000;
	int nthreadsRequested  = j;
	int nthreads;

	double step;
	double pi = 0.0;
	step = 1.0/(double) num_steps;

	omp_set_num_threads(nthreadsRequested);
	double timestart = omp_get_wtime();
	#pragma omp parallel
	{
		double x;
		int nThreadsActual = omp_get_num_threads();
		int id = omp_get_thread_num();
		if(id == 0) nthreads = nThreadsActual;

		double sum = 0.0;
		for(int i = id; i < num_steps; i+=nThreadsActual)
		{
			x = ( i + 0.5 ) * step;
			sum += 4.0/(1.0+x*x);
		}
		#pragma omp critical
		pi +=sum*step;
	}

	std::cout << "threads " << nthreads << "\t";
	std::cout << "time: " << (omp_get_wtime() - timestart)*1000 << "\t";
	std::cout << "pi = " << pi << std::endl;
	}
}


void calculatePi4()
{
	for(int j = 1; j < 10; j++)
	{
		static long num_steps = 100000;
		double step;
		int i; double pi, sum = 0.0;
		int nthreadsRequested  = j;
		int nthreads;


		step = 1.0/(double) num_steps;
		omp_set_num_threads(nthreadsRequested);

		//omp_set_schedule(omp_sched_dynamic);
		double timestart = omp_get_wtime();
		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			if(id == 0) nthreads = omp_get_num_threads();
			double x;

			#pragma omp for reduction (+:sum) schedule(static)
				for (i=0;i< num_steps; i++){
					x = (i+0.5)*step;
					sum = sum + 4.0/(1.0+x*x);
				}
		}
		pi = step * sum;
		std::cout << "threads " << nthreads << "\t";
		std::cout << "time: " << (omp_get_wtime() - timestart)*1000 << "\t";
		std::cout << "pi = " << pi << std::endl;
	}
}

void writeThreads()
{
	#pragma omp parallel
	{
		int ID = omp_get_thread_num(); 
			printf("hello(%d) ", ID);
			printf(" world(%d) \n", ID);
			//std::cout << "test3" << std::endl;
		//std::cout << "Hello concurrent world" << std::endl;
	}
}

int main(int argc, char *argv[])
{
	//calcualtePi();
	//calculatePi2();
	//calculatePi3();
	calculatePi4();

	//writeThreads();
	//return 0;
}
