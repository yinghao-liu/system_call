/*
 * Copyright (C) 2018 francis_hao <francis_hao@126.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _CONDITION_H_
#define _CONDITION_H_
#include <iostream>
#include <pthread.h>
using std::cin;
using std::cout;
using std::endl;

class condition{
public:
	static void *produce(void *);
	static void *consume(void *);
private:
	static pthread_mutex_t mutex;
	static pthread_cond_t cond;
	static int flag;
};

pthread_mutex_t condition::mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition::cond = PTHREAD_COND_INITIALIZER;
int condition::flag = 0;

void *condition::produce(void *nul)
{
	int a;
	cout<<"now in produce"<<endl;
	pthread_mutex_lock(&mutex);
	cout<<"produce got lock, press any key:";
	cin>>a;
	flag = 1;
	cout<<"now in produce.lock, flag is "<<flag<<endl;
	pthread_mutex_unlock(&mutex);

	cout<<"now in produce out of lock, flag is "<<flag<<endl;
	cout<<"press any key:";
	cin>>a;
	pthread_cond_signal(&cond);
}
void *condition::consume(void *nul)
{
	cout<<"now in consume, at the begining of the fun"<<endl;
	pthread_mutex_lock(&mutex);
	cout<<"consume got lock"<<endl;
	while (0 == flag){
		pthread_cond_wait(&cond, &mutex);
	}
	flag = 0;
	cout<<"now in consume, flag is "<<flag<<endl;
	pthread_mutex_unlock(&mutex);
}
#endif

