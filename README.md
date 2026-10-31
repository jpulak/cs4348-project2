# CS/SE 4348 Project 2 

## Team Information

Team Number: 21

Member 1: Jana Pulak
Member 2: Cristina Lu


## Project Overview

This project implements Dining Philosophers using:

1. A coarse-grained Tournament-Tree lock.
2. Fine-grained Peterson locks for individual chopsticks.

## Deadlock-Prevention Strategy

Planned strategy:

Each philosopher acquires the lower-numbered
required chopstick before the higher-numbered one.

TODO: Explain why this prevents circular wait.


## Tournament Tree

- Tree representation
- Thread-to-leaf mapping
- Non-power-of-two handling
- Acquire and release order


## Compilation
make

## Execution
./my-dining n
n must be an integer greater than or equal to 2.

## Cleanup
make clean

## Assumptions and Known Limitations
TODO: Document final assumptions and limitations.