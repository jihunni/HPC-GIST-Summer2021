---
layout: default
title: week4 hw1
nav_exclude: true
---
## Homework Assignment
week4 hw1

## Score
50

## Due
Tue, Jul-27-2021, 11:59 PM 

## Problem 1
Implement a CUDA code for matrix multiplication A x B = C

- Consider matrices are squre and same size. For example, A(1024x1024) x B(1024x1024) = C(1024x1024).
- You can implement a naive method to assign one thread to compute one element of matrix C. E.g., each thread loads one row of matrix A and one column of matrix B from global memory, do the inner product, and store the result back to matrix C in the global memory. 
- You should assure that your CUDA code result is same as CPU code.
- Test it on Google Colab. 


## Submit
- Submit a zip file or ipyphone file by email to taehyuk.ahn@gist.ac.kr
- Filename should be "HPC_week4_hw1_YourLastname_YourFirstName.gz" or .ipython.
- Email title should be "HPC week4 hw1 submission"
