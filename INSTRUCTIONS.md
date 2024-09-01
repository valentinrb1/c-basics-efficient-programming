Sistemas Operativos II - Laboratorio II IPC
###  Ingeniería en Computación - FCEFyN - UNC - 2023
# Laboratory 3 - Introduction to efficient and performant programming

## Introduction
Whether we are working on an embedded system with limited resources (cores, frequency, memory, etc.) or when we are working on service software that must be able to scale and respond in a given time, or when we are working on scientific computing, having efficient and performant software is our responsibility.

It is clear that, to meet this objective, we must know the architecture and resources that the software we are going to write will use.

### What do we mean by _efficient software_?
Intuitively we can say that efficient software (high performance) is one that runs faster than inefficient software, but this is not enough, because it may be faster, but both may not be efficient.

We must understand that efficiency is not the same as perforance, but they are related. Efficiency refers to the optimal use of resources and the waste of them. An efficient program makes good use of hardware resources, does not leave any resources in an idle state, or performs tasks that it does not have to do.

On the other hand, performance always refers to metrics. The most common metric is speed, that is, how fast the software is. The variable time can be used to measure this metric, but it is not the only one (clocks, instructions, etc.).

## Development
### Problem to solve
Given the laboratory3.c file in this repo, the student is asked to analyze it, study it and perform any optimization, efficiency and refactoring tasks that he considers so that the software is more optimal in resource consumption.

1 - All optimizations performed using the _time_ command and any other static analyzer must be measured and documented, using the software as it is presented as a base.

2 - Starting from scratch, all optimizations performed using the dynamic analyzer [valgrind](https://valgrind.org/) must be measured and documented.

3 - Compare both versions: your own and the one performed with valgrind:
- a: What are the differences?
- b: Which is better? Why?

4 - You must design and develop a unit test that validates the software (NOT using a framework, just a script).

### Restrictions
- Either GCC or another compiler can be used
- Compilation must be done without [compilation optimizations (-O0)](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)

### Correctness Criteria
- Code must be compiled with the compilation flags:
-Wall -Pedantic -Werror -Wextra -Wconversion -std=gnu11
- Correct memory management.
- Splitting code into modules judiciously.
- Code style.
- Error handling
- Code must not contain errors or warnings.
- Code must not contain cppcheck errors.

## Delivery
The delivery is made through the GitHub repository and the completion of the same must be demonstrated through correct use. The repository must provide the source files and any other files associated with the compilation, CMAKE project files and the correctly documented code. It must not contain any files associated with IDE projects and it must be assumed that the project can be compiled and run by a `tty` in a Linux distribution with the typical development tools. A report must also be delivered in _Markdown_ format documenting each change made to the code, what effect it has on it and why.
It must also be investigated what free profiling utilities exist and what each one provides (a chapter of the report), choosing one to perform the execution time measurements of the designed application.

The report must contain graphics and comparison analysis between procedural and distributed execution. The report must also contain the design of the solution and the comparison of profilers.

## Evaluation
This practical work is individual and must be submitted before 2:59 p.m. ART on April 20, 2023, leaving it recorded in the LEV with the ifnorme file.
