![poster](https://github.com/JiananYuan/FITing-Tree/assets/53621620/63940e14-fdcc-4414-828a-284d121df0b7)

## Intro
This is an implementation(easy demo) of FITing-Tree written in C++. For the original SIGMOD '19 paper, see also [FITing-Tree: A Data-aware Index Structure](https://dl.acm.org/doi/10.1145/3299869.3319860).

## Install and Run
- git clone this project and execute `mkdir build` in it
- enter the build directory and execute `cmake -DCMAKE\_BUILD\_TYPE=Release ..`, `make -j`
- back to the root directory of the project and execute `chmod +x ./exp.sh`, `./exp.sh`
- wait for the program to produce the experiment results
