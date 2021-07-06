---
layout: default
title: week2 lab1
nav_exclude: true
---
## Lab Assignment
week2 lab1

## Score
30

## Due
Tue, Jul-13-2021, 11:59 PM

## Problem
Copy the prime_count_omp.cpp into your working lab directory. Then, follow below things.

Q1. Set OMP_NUM_THREADS=1 in your terminal environment. Run the program with N=300000. What is the count of the prime numbers? What is the elapsed time (sec)?

Sol:

Q2. Set OMP_NUM_THREADS=2 in your terminal environment. Run the program with N=300000. Did you get the same count of the prime numbers as of Q1? What is the elapsed time (sec)? Did you get a shorter elapsed time compared to Q1?

Sol:

Q3. Test the program with "static with chunk size 100", the same N (300000), and the same threads (2). Then, report the wall-clock time. Compare your wall clock time to Q2. Did you get a better speed-up (shorter elapsed time)?

Sol:

Q4. Test the program with "dynamic", the same N (300000), and the same threads (2). Then, report the wall-clock time. Compare your wall clock time to Q2 (static default). Did you get a better speed-up (shorter elapsed time)?

Sol:

Q5. Test the program with "dynamic with chunk size 100", the same N (300000), and the same threads (2). Then, report the wall-clock time. Compare your wall clock time to Q4. Did you get a better speed-up (shorter elapsed time)?

Sol:

Q6. Test the program with "guided", the same N (300000), and the same threads (2). Then, report the wall-clock time. Compare your wall clock time to Q2 (static default) and Q4 (dynamic default). Did you get a better speed-up (shorter elapsed time)?

Sol:

Q7.  The code lines 49 and 50 report "Number of processors available" and "Number of threads". To get these value, I used omp_get_num_procs() and omp_get_max_threads() run-time library functions. Especially, I used omp_get_max_threads(), not omp_get_num_threads(). Why? Please describe your thoughts.

### Submit
Submit a doc (only pdf) by email (address: taehyuk.ahn@gist.ac.kr)
- Filename should be "HPC_week2_lab1_YourLastname_YourFirstName.pdf"
- Email title should be "HPC week2 lab1 submission"
