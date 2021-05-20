#!/bin/zsh

make -C process >/dev/null
make -C threads >/dev/null

old=$TIMEFMT
TIMEFMT="%J %U user %S system %P cpu %E total"

test -f numbers.txt || od -A n -t d -N 40000000 /dev/urandom > numbers.txt

i=0
while [[ i -lt $1 ]]; do
    (time process/map-reduce) <numbers.txt >>p_mpred.txt 2>>p_mpred.txt
    (time threads/map-reduce) <numbers.txt >>t_mpred.txt 2>>t_mpred.txt

    (time process/merge) <numbers.txt >>p_merge.txt 2>>p_merge.txt
    (time threads/merge) <numbers.txt >>t_merge.txt 2>>t_merge.txt

    (time process/quick) <numbers.txt >>p_quick.txt 2>>p_quick.txt
    (time threads/quick) <numbers.txt >>t_quick.txt 2>>t_quick.txt

    (( ++i ))
done