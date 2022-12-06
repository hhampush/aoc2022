FROM gcc:latest as BASE
COPY aoc.c input.txt ./
RUN  objcopy --input binary --output elf64-x86-64 input.txt input.o
RUN  gcc ./input.o ./aoc.c -std=c2x -Ofast -march=native -flto -Wall -o /bin/aoc
FROM debian:unstable-slim
COPY --from=BASE /bin/aoc /bin/aoc
COPY input.txt ./
ENTRYPOINT /bin/aoc
