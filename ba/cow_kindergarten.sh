#!/bin/bash

for num in {1..10}
do
    ./.cs.sh $num
done

./.fin.sh