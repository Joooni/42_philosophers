# 42_philosophers
A program to explore the hungry philosophers problem, an abstract exercise to learn about concurrent algorithm design and mutual exclusion principles.

A set of N hungry philosophers sit around a table, a big bowl of spaghetti in their midst. The goal of each philosopher is to not die from hunger, to sleep a certain time after eating and to think while neither sleeping nor eating. Inbetween each pair of philosophers is a fork that they use to consume the food. Each philosopher needs two forks to eat. After finishing their meal, they put it down again.

In this exercise, threads are used to depict each philosopher while different mutual exclusions are chosen to limit read or write access to certain shared resources.
