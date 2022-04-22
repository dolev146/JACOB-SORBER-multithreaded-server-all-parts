#!/bin/bash

for N in {1..50}
do
    ruby client.rb &
done
wait
# bash ./manyclients.bash