#!/bin/sh
# (()) write   ==,   >， >=，  <， <=
# []   write  -eq，-gt，-ge，-lt，-le

macdec=$( printf "%d\n" 0xFC4AE9E2605D );
counter=2000;
while [ "$counter" -gt 0 ] ; do
let counter--;
macdec1=$( expr $macdec + $counter );
machex1=$( printf "%X\n" $macdec1 );
printf "$machex1\n" | sed -e 's/../&:/g' -e 's/:$//';
done

