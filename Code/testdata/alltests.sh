#!/bin/bash

# alltests.sh executable-or-.py

TIMEOUT=30
CYCLES=200

if [[ $# != 1 ]]
then
#  echo "Usage: $0 path-to-executable-program-or-main.py"
  echo "Usage: $0 path-to-executable-program"
  exit 0
fi

EXECMD="$1"
# if [[ ${EXECMD##*.} = "py" ]]
# then
#   EXECMD="python3 $EXECMD"
# fi

echo "Running $EXECMD ..."
echo "Differences to expected output in basic tests:"

# Go through all input data files
for i in *.in
do
  # ../cpp/model_solution/a.out <$i >$(basename $i .in)-cpp.out
  # python3 ../python/model_solution/main.py <$i >$(basename $i .in)-python.out
  echo $i ":"
  $EXECMD <$i | diff -w --unified - $(basename $i .in).out
done

echo ""
echo "Performance tests (timeout $TIMEOUT seconds):"

for n in tyoohje-esimerkki.txt zz-final_bus_liteN.txt zzz-final_bus_full.txt
do
  echo $n ":"
  echo -n "  Stops: "
  grep -e "^STOP;" $n | wc -l
  echo -n "  Routes: "
  grep -e "^ROUTE;" $n | wc -l
  echo -n "  Buses: "
  grep -e "^BUS;" $n | wc -l
  echo -n "  Total stops on routes: "
  grep -e "^ROUTEADDSTOP;" $n | wc -l
  echo -e "R $n\nF $CYCLES 3735;523;13;10 4078;6025;12;12\nQ\n" | timeout $TIMEOUT $EXECMD >/dev/null
  if [[ $? != 0 ]]
  then
    echo "Timeout!"
    break
  fi
done
echo ""
