#pragma once

#define MSG_SIZE 512*512

long int p, q, n, t, flag, j, i;
short int en[MSG_SIZE], e[MSG_SIZE], d[MSG_SIZE], temp[MSG_SIZE], m[MSG_SIZE], msg[MSG_SIZE];

int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();